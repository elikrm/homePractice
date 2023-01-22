import os
import argparse
import subprocess
from typing import List


# Use linesep of this file instead of os.linesep or any other hardcoded line ending
linesep = """
"""


def get_make_output(makefile: str, target: str, release: bool = False) -> str:
    dirname = os.path.dirname(makefile)
    filename = os.path.basename(makefile)
    command = ['make', '-C', dirname, '-f', filename, '--quiet', '--no-print-directory', target]
    if release:
        command += ["RELEASE=1"]
    result = subprocess.check_output(command, encoding='utf-8').strip().split("\n")
    return result[-1]


def print_src_files(debug: List[str], release: List[str], base_depth: int = 0) -> str:
    depth = 0
    lines = []
    current_folder = "."
    src_files = list(set(debug + release))
    for file in sorted(src_files):
        if len(file) == 0:
            # empty files/lines happens when appending source files in the Makefile
            continue

        folder = os.path.dirname(file)
        while folder.startswith("../"):
            # Strip away ../ from folder because it is outside of project directory.
            # This brings the folder to the same level as other folders in the project directory.
            folder = folder[3:]

        if folder != current_folder:
            relpath = os.path.relpath(folder, start=current_folder)
            for s in relpath.split(os.path.sep):
                if s == "..":
                    if depth > 0:
                        depth -= 1
                        lines.append('    ' * (base_depth + depth) + '</folder>')
                else:
                    lines.append('    ' * (base_depth + depth) + f'<folder Name="{s}">')
                    depth += 1
            current_folder = folder

        if file in debug and file in release:
            lines.append('    ' * (base_depth + depth) + f'<file file_name="{file}" />')
        else:
            excluded_config = "Release" if file not in release else "Debug"
            lines.append('    ' * (base_depth + depth) + f'<file file_name="{file}">')
            lines.append('    ' * (base_depth + depth) + f'    <configuration Name="{excluded_config}" build_exclude_from_build="Yes" />')
            lines.append('    ' * (base_depth + depth) + f'</file>')

    while depth > 0:
        depth -= 1
        lines.append('    ' * (base_depth + depth) + '</folder>')

    return linesep.join(lines)


def print_inc_folders(debug: List[str], release: List[str], base_depth: int = 0) -> str:
    depth = 0
    lines = []

    lines.append('    ' * (base_depth + depth) + f'<folder Name=".Header files">')
    depth += 1

    last_folder = "."
    inc_folders = list(set(debug + release))
    for folder in sorted(inc_folders):
        if len(folder) == 0:
            # empty folders/lines happens when appending include folders in the Makefile
            continue

        clean_folder = folder.replace('..', '_')  # assumption: There won't be a folder just called '_'

        if last_folder.startswith("_") and not clean_folder.startswith(last_folder):
            while depth > 1:
                depth -= 1
                lines.append('    ' * (base_depth + depth) + '</folder>')
            last_folder = "."

        relpath = os.path.relpath(clean_folder, start=last_folder)
        split = relpath.split(os.path.sep)
        dots = 0
        for s in split[:-1]:
            if s == "..":
                if depth > 1:
                    depth -= 1
                    lines.append('    ' * (base_depth + depth) + '</folder>')
            elif s == "_":
                dots += 1
            else:
                if dots > 0:
                    s = "../" * dots + s
                    dots = 0
                lines.append('    ' * (base_depth + depth) + f'<folder Name="{s}">')
                depth += 1

        s = split[-1]
        if dots > 0:
            s = "../" * dots + s
            dots = 0

        if folder in debug and folder in release:
            lines.append('    ' * (base_depth + depth) + f'<folder Name="{s}" filter="*.h" path="{folder}">')
            depth += 1
        else:
            excluded_config = "Release" if folder not in release else "Debug"
            lines.append('    ' * (base_depth + depth) + f'<folder Name="{s}" filter="*.h" path="{folder}">')
            depth += 1
            lines.append('    ' * (base_depth + depth) + f'<configuration Name="{excluded_config}" build_exclude_from_build="Yes" />')

        last_folder = clean_folder

    while depth > 0:
        depth -= 1
        lines.append('    ' * (base_depth + depth) + '</folder>')

    return linesep.join(lines)


def get_target_settings(target: str) -> str:
    if target == "nrf52833_xxaa":
        return """
            arm_architecture="v7EM"
            arm_core_type="Cortex-M4"
            arm_endian="Little"
            arm_fpu_type="FPv4-SP-D16"
            arm_target_device_name="nRF52833_xxAA"
            debug_register_definition_file="../nRF5_SDK_17.1.0_ddde560/modules/nrfx/mdk/nrf52840.svd"
"""
    elif target == "samc21j18a":
        return """
            arm_architecture="v6M"
            arm_core_type="Cortex-M0"
            arm_endian="Little"
            arm_fpu_type=""
            arm_target_device_name="ATSAMC21J18A"
"""
    elif target == "stm32l4r9aiix_flash":
        return """
            arm_architecture="v7EM"
            arm_core_type="Cortex-M4"
            arm_endian="Little"
            arm_fpu_type="FPv4-SP-D16"
            arm_target_device_name="STM32L4R9AI"
"""
    else:
        return ""


def get_rel_to_proj_dir(path: str, project_dir: str) -> str:
    if len(path) == 0:
        return ""
    else:
        if not os.path.exists(path):
            # relative path that does not exist here
            path = os.path.join(project_dir, path)
        rel = os.path.relpath(path, start=project_dir).replace("\\", "/")
        return f"$(ProjectDir)/{rel}"


def main():
    parser = argparse.ArgumentParser(description='Convert project make files into a SEGGER Embedded Studio project file')
    parser.add_argument('in_file', metavar='MAKE_FILE', nargs="+", help='Path to multiple Makefiles')
    parser.add_argument('out_file', metavar='SEGGER_PROJECT', help='Path to output SEGGER project file')

    args = parser.parse_args()

    out_dir = os.path.dirname(args.out_file)
    with open(args.out_file, "w") as f:
        f.write("""<!DOCTYPE CrossStudio_Project_File>
<solution Name="snake firmware" target="8" version="2">
""")

        for makefile in args.in_file:
            makefile = os.path.abspath(makefile)
            if not os.path.exists(makefile):
                print(f"ERROR: Makefile {makefile} does not exist")
                return

            xml = makefile_to_segger_project_xml(makefile, out_dir)
            f.write(xml)

        f.write("""
    <configuration Name="Common" />
    <configuration Name="Debug" />
    <configuration Name="Release" />
</solution>
""")


def makefile_to_segger_project_xml(makefile: str, out_dir: str) -> str:
    abs_project_dir = os.path.dirname(makefile)
    project_dir = os.path.relpath(abs_project_dir, start=out_dir).replace("\\", "/")
    if project_dir == ".":
        project_dir = ""
    makefile_name = os.path.basename(makefile)

    project_name = get_make_output(makefile, 'project_name').strip()

    targets = get_make_output(makefile, 'targets').strip()
    target_settings = get_target_settings(targets)

    elf_file_debug = get_make_output(makefile, 'elf_file').strip()
    elf_file_debug = get_rel_to_proj_dir(elf_file_debug, abs_project_dir)
    elf_file_release = get_make_output(makefile, 'elf_file', release=True).strip()
    elf_file_release = get_rel_to_proj_dir(elf_file_release, abs_project_dir)

    map_file_debug = os.path.splitext(elf_file_debug)[0] + ".map"
    map_file_release = os.path.splitext(elf_file_release)[0] + ".map"

    hex_file_debug = os.path.splitext(elf_file_debug)[0] + ".hex"
    hex_file_release = os.path.splitext(elf_file_release)[0] + ".hex"

    linker_script_debug = get_make_output(makefile, 'linker_script').strip()
    linker_script_debug = get_rel_to_proj_dir(linker_script_debug, abs_project_dir)
    linker_script_release = get_make_output(makefile, 'linker_script', release=True).strip()
    linker_script_release = get_rel_to_proj_dir(linker_script_release, abs_project_dir)

    # Source files
    src_files_debug = get_make_output(makefile, 'src_files').strip().split(' ')
    src_files_release = get_make_output(makefile, 'src_files', release=True).strip().split(' ')
    src_files_debug.append(f"./{makefile_name}")
    src_files_release.append(f"./{makefile_name}")
    files = print_src_files(src_files_debug, src_files_release, base_depth=2)

    # Include directories
    inc_folders_debug = get_make_output(makefile, 'inc_folders').strip().split(' ')
    inc_folders_release = get_make_output(makefile, 'inc_folders', release=True).strip().split(' ')
    folders = print_inc_folders(inc_folders_debug, inc_folders_release, base_depth=2)

    inc_folders_debug = set(inc_folders_debug)
    inc_folders_release = set(inc_folders_release)
    inc_folders_common = inc_folders_debug.intersection(inc_folders_release)
    c_user_include_directories_debug = ";".join(sorted(list(inc_folders_debug - inc_folders_common)))
    c_user_include_directories_release = ";".join(sorted(list(inc_folders_release - inc_folders_common)))
    c_user_include_directories_common = ";".join(sorted(list(inc_folders_common)))

    # Definitions
    cflags_debug = get_make_output(makefile, 'cflags')
    cflags_release = get_make_output(makefile, 'cflags', release=True)

    definitions = []
    for flag in cflags_debug.strip().split(' '):
        if flag.startswith("-D"):
            definitions.append(flag[2:])
    c_preprocessor_definitions_debug = ';'.join(definitions)

    definitions = []
    for flag in cflags_release.strip().split(' '):
        if flag.startswith("-D"):
            definitions.append(flag[2:])
    c_preprocessor_definitions_release = ';'.join(definitions)

    # Additional SEGGER settings
    segger_flags = get_make_output(makefile, 'segger_flags')
    if len(segger_flags) > 0:
        segger_flags = " " * 12 + segger_flags

    return f"""    <project Name="{project_name}">
        <configuration
            Name="Common"
            arm_target_interface_type="SWD"
            debug_target_connection="J-Link"
            debug_start_from_entry_point_symbol="No"
            project_directory="{project_dir}"
{target_settings}
{segger_flags}
            c_user_include_directories="{c_user_include_directories_common}"
            project_type="Externally Built Executable" />

        <configuration
            Name="Debug"
            external_build_command="make -C $(ProjectDir) -f {makefile_name} all"
            external_clean_command="make -C $(ProjectDir) -f {makefile_name} clean"
            external_build_file_name="{hex_file_debug}"
            external_load_file_type="ihex"
            external_debug_symbols_file_name="{elf_file_debug}"
            link_linker_script_file="{linker_script_debug}"
            linker_memory_map_file="{map_file_debug}"
            c_preprocessor_definitions="{c_preprocessor_definitions_debug}"
            c_user_include_directories="{c_user_include_directories_debug}"
            project_type="Externally Built Executable" />

        <configuration
            Name="Release"
            external_build_command="make -C $(ProjectDir) -f {makefile_name} RELEASE=1 all"
            external_clean_command="make -C $(ProjectDir) -f {makefile_name} RELEASE=1 clean"
            external_build_file_name="{hex_file_release}"
            external_load_file_type="ihex"
            external_debug_symbols_file_name="{elf_file_release}"
            link_linker_script_file="{linker_script_release}"
            linker_memory_map_file="{map_file_release}"
            c_preprocessor_definitions="{c_preprocessor_definitions_release}"
            c_user_include_directories="{c_user_include_directories_release}"
            project_type="Externally Built Executable" />

{folders}
{files}
    </project>
"""


if __name__ == "__main__":
    main()

