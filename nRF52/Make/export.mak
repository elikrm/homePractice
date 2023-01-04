# This file provides a few make targets that export certain Makefile variables
# for use by external tools. Currently, the make2segger.py script is the only
# tool that is using this interface.

MAKE_DIRECTORY := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
#include $(MAKE_DIRECTORY)/tools.mak

MAKE2SEGGER := python $(MAKE_DIRECTORY)/make2segger.py
SEGGER_PROJECT_FILE ?= $(PROJECT_NAME).emProject

# Initialise SEGGER_FLAGS with something to avoid using other messages as flags
SEGGER_FLAGS ?= \
  debug_additional_load_file=""

segger:
	@$(MAKE2SEGGER) $(abspath $(firstword $(MAKEFILE_LIST))) $(SEGGER_PROJECT_FILE)


# Using $(info ...) to print flags because @echo ... can't print an empty string

project_name:
	$(info $(PROJECT_NAME))

cflags:
	$(info $(CFLAGS))

ldflags:
	$(info $(LDFLAGS))

segger_flags:
	$(info $(SEGGER_FLAGS))

src_files:
	$(info $(SRC_FILES))

inc_folders:
	$(info $(INC_FOLDERS))

elf_file:
	$(info $(OUTPUT_FILE).out)

linker_script:
	$(info $(LINKER_SCRIPT))

targets:
	$(info $(TARGETS))
