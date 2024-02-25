/*$file${.::qmsmtst.c} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*
* Model: qmsmtst.qm
* File:  ${.::qmsmtst.c}
*
* This code has been generated by QM 5.2.1 <www.state-machine.com/qm>.
* DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
*
* This code is covered by the following QP license:
* License #    : QM-EVAL-QPC
* Issued to    : Users of QP/C Real-Time Embedded Framework (RTEF)
* Framework(s) : qpc
* Support ends : 2023-12-31
* License scope:
*
* SPDX-License-Identifier: GPL-3.0-or-later
*
* This generated code is free software: you can redistribute it under
* the terms of the GNU General Public License as published by the Free
* Software Foundation.
*
* This code is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* NOTE:
* Alternatively, this generated code may be distributed under the terms
* of Quantum Leaps commercial licenses, which expressly supersede the GNU
* General Public License and are specifically designed for licensees
* interested in retaining the proprietary status of their code.
*
* Contact information:
* <www.state-machine.com/licensing>
* <info@state-machine.com>
*/
/*$endhead${.::qmsmtst.c} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#include "qpc.h"
#include "qmsmtst.h"

/*$declare${SMs::QMsmTst} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/

/*${SMs::QMsmTst} ..........................................................*/
typedef struct {
/* protected: */
    QMsm super;

/* private: */
    uint8_t foo;
} QMsmTst;

/* protected: */
static QState QMsmTst_initial(QMsmTst * const me, void const * const par);
static QState QMsmTst_s  (QMsmTst * const me, QEvt const * const e);
static QState QMsmTst_s_e(QMsmTst * const me);
static QState QMsmTst_s_x(QMsmTst * const me);
static QState QMsmTst_s_i(QMsmTst * const me);
static QMState const QMsmTst_s_s = {
    QM_STATE_NULL, /* superstate (top) */
    Q_STATE_CAST(&QMsmTst_s),
    Q_ACTION_CAST(&QMsmTst_s_e),
    Q_ACTION_CAST(&QMsmTst_s_x),
    Q_ACTION_CAST(&QMsmTst_s_i)
};
static QState QMsmTst_s1  (QMsmTst * const me, QEvt const * const e);
static QState QMsmTst_s1_e(QMsmTst * const me);
static QState QMsmTst_s1_x(QMsmTst * const me);
static QState QMsmTst_s1_i(QMsmTst * const me);
static QMState const QMsmTst_s1_s = {
    &QMsmTst_s_s, /* superstate */
    Q_STATE_CAST(&QMsmTst_s1),
    Q_ACTION_CAST(&QMsmTst_s1_e),
    Q_ACTION_CAST(&QMsmTst_s1_x),
    Q_ACTION_CAST(&QMsmTst_s1_i)
};
static QState QMsmTst_s11  (QMsmTst * const me, QEvt const * const e);
static QState QMsmTst_s11_e(QMsmTst * const me);
static QState QMsmTst_s11_x(QMsmTst * const me);
static QMState const QMsmTst_s11_s = {
    &QMsmTst_s1_s, /* superstate */
    Q_STATE_CAST(&QMsmTst_s11),
    Q_ACTION_CAST(&QMsmTst_s11_e),
    Q_ACTION_CAST(&QMsmTst_s11_x),
    Q_ACTION_NULL  /* no initial tran. */
};
static QState QMsmTst_s2  (QMsmTst * const me, QEvt const * const e);
static QState QMsmTst_s2_e(QMsmTst * const me);
static QState QMsmTst_s2_x(QMsmTst * const me);
static QState QMsmTst_s2_i(QMsmTst * const me);
static QMState const QMsmTst_s2_s = {
    &QMsmTst_s_s, /* superstate */
    Q_STATE_CAST(&QMsmTst_s2),
    Q_ACTION_CAST(&QMsmTst_s2_e),
    Q_ACTION_CAST(&QMsmTst_s2_x),
    Q_ACTION_CAST(&QMsmTst_s2_i)
};
static QState QMsmTst_s21  (QMsmTst * const me, QEvt const * const e);
static QState QMsmTst_s21_e(QMsmTst * const me);
static QState QMsmTst_s21_x(QMsmTst * const me);
static QState QMsmTst_s21_i(QMsmTst * const me);
static QMState const QMsmTst_s21_s = {
    &QMsmTst_s2_s, /* superstate */
    Q_STATE_CAST(&QMsmTst_s21),
    Q_ACTION_CAST(&QMsmTst_s21_e),
    Q_ACTION_CAST(&QMsmTst_s21_x),
    Q_ACTION_CAST(&QMsmTst_s21_i)
};
static QState QMsmTst_s211  (QMsmTst * const me, QEvt const * const e);
static QState QMsmTst_s211_e(QMsmTst * const me);
static QState QMsmTst_s211_x(QMsmTst * const me);
static QMState const QMsmTst_s211_s = {
    &QMsmTst_s21_s, /* superstate */
    Q_STATE_CAST(&QMsmTst_s211),
    Q_ACTION_CAST(&QMsmTst_s211_e),
    Q_ACTION_CAST(&QMsmTst_s211_x),
    Q_ACTION_NULL  /* no initial tran. */
};
/*$enddecl${SMs::QMsmTst} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

static QMsmTst l_sm; /* the only instance of the QMsmTst class */

/* global-scope definitions ---------------------------------------*/
QHsm * const the_sm = &l_sm.super.super; /* the opaque pointer */

/*$skip${QP_VERSION} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/* Check for the minimum required QP version */
#if (QP_VERSION < 690U) || (QP_VERSION != ((QP_RELEASE^4294967295U) % 0x3E8U))
#error qpc version 6.9.0 or higher required
#endif
/*$endskip${QP_VERSION} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/*$define${SMs::QMsmTst_ctor} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/

/*${SMs::QMsmTst_ctor} .....................................................*/
void QMsmTst_ctor(void) {
    QMsmTst *me = &l_sm;
    QMsm_ctor(&me->super, Q_STATE_CAST(&QMsmTst_initial));
}
/*$enddef${SMs::QMsmTst_ctor} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*$define${SMs::QMsmTst} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/

/*${SMs::QMsmTst} ..........................................................*/

/*${SMs::QMsmTst::SM} ......................................................*/
static QState QMsmTst_initial(QMsmTst * const me, void const * const par) {
    static struct {
        QMState const *target;
        QActionHandler act[4];
    } const tatbl_ = { /* tran-action table */
        &QMsmTst_s2_s, /* target state */
        {
            Q_ACTION_CAST(&QMsmTst_s_e), /* entry */
            Q_ACTION_CAST(&QMsmTst_s2_e), /* entry */
            Q_ACTION_CAST(&QMsmTst_s2_i), /* initial tran. */
            Q_ACTION_NULL /* zero terminator */
        }
    };
    /*${SMs::QMsmTst::SM::initial} */
    (void)par; /* unused parameter */
    me->foo = 0U;
    BSP_display("top-INIT;");

    QS_FUN_DICTIONARY(&QMsmTst_s);
    QS_FUN_DICTIONARY(&QMsmTst_s1);
    QS_FUN_DICTIONARY(&QMsmTst_s11);
    QS_FUN_DICTIONARY(&QMsmTst_s2);
    QS_FUN_DICTIONARY(&QMsmTst_s21);
    QS_FUN_DICTIONARY(&QMsmTst_s211);

    return QM_TRAN_INIT(&tatbl_);
}

/*${SMs::QMsmTst::SM::s} ...................................................*/
/*${SMs::QMsmTst::SM::s} */
static QState QMsmTst_s_e(QMsmTst * const me) {
    BSP_display("s-ENTRY;");
    (void)me; /* unused parameter */
    return QM_ENTRY(&QMsmTst_s_s);
}
/*${SMs::QMsmTst::SM::s} */
static QState QMsmTst_s_x(QMsmTst * const me) {
    BSP_display("s-EXIT;");
    (void)me; /* unused parameter */
    return QM_EXIT(&QMsmTst_s_s);
}
/*${SMs::QMsmTst::SM::s::initial} */
static QState QMsmTst_s_i(QMsmTst * const me) {
    static struct {
        QMState const *target;
        QActionHandler act[3];
    } const tatbl_ = { /* tran-action table */
        &QMsmTst_s11_s, /* target state */
        {
            Q_ACTION_CAST(&QMsmTst_s1_e), /* entry */
            Q_ACTION_CAST(&QMsmTst_s11_e), /* entry */
            Q_ACTION_NULL /* zero terminator */
        }
    };
    /*${SMs::QMsmTst::SM::s::initial} */
    BSP_display("s-INIT;");
    return QM_TRAN_INIT(&tatbl_);
}
/*${SMs::QMsmTst::SM::s} */
static QState QMsmTst_s(QMsmTst * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${SMs::QMsmTst::SM::s::I} */
        case I_SIG: {
            /*${SMs::QMsmTst::SM::s::I::[me->foo]} */
            if (me->foo) {
                me->foo = 0U;
                BSP_display("s-I;");
                status_ = QM_HANDLED();
            }
            else {
                status_ = QM_UNHANDLED();
            }
            break;
        }
        /*${SMs::QMsmTst::SM::s::E} */
        case E_SIG: {
            static struct {
                QMState const *target;
                QActionHandler act[3];
            } const tatbl_ = { /* tran-action table */
                &QMsmTst_s11_s, /* target state */
                {
                    Q_ACTION_CAST(&QMsmTst_s1_e), /* entry */
                    Q_ACTION_CAST(&QMsmTst_s11_e), /* entry */
                    Q_ACTION_NULL /* zero terminator */
                }
            };
            BSP_display("s-E;");
            status_ = QM_TRAN(&tatbl_);
            break;
        }
        /*${SMs::QMsmTst::SM::s::TERMINATE} */
        case TERMINATE_SIG: {
            BSP_exit();
            status_ = QM_HANDLED();
            break;
        }
        default: {
            status_ = QM_SUPER();
            break;
        }
    }
    (void)me; /* unused parameter */
    return status_;
}

/*${SMs::QMsmTst::SM::s::s1} ...............................................*/
/*${SMs::QMsmTst::SM::s::s1} */
static QState QMsmTst_s1_e(QMsmTst * const me) {
    BSP_display("s1-ENTRY;");
    (void)me; /* unused parameter */
    return QM_ENTRY(&QMsmTst_s1_s);
}
/*${SMs::QMsmTst::SM::s::s1} */
static QState QMsmTst_s1_x(QMsmTst * const me) {
    BSP_display("s1-EXIT;");
    (void)me; /* unused parameter */
    return QM_EXIT(&QMsmTst_s1_s);
}
/*${SMs::QMsmTst::SM::s::s1::initial} */
static QState QMsmTst_s1_i(QMsmTst * const me) {
    static struct {
        QMState const *target;
        QActionHandler act[2];
    } const tatbl_ = { /* tran-action table */
        &QMsmTst_s11_s, /* target state */
        {
            Q_ACTION_CAST(&QMsmTst_s11_e), /* entry */
            Q_ACTION_NULL /* zero terminator */
        }
    };
    /*${SMs::QMsmTst::SM::s::s1::initial} */
    BSP_display("s1-INIT;");
    return QM_TRAN_INIT(&tatbl_);
}
/*${SMs::QMsmTst::SM::s::s1} */
static QState QMsmTst_s1(QMsmTst * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${SMs::QMsmTst::SM::s::s1::I} */
        case I_SIG: {
            BSP_display("s1-I;");
            status_ = QM_HANDLED();
            break;
        }
        /*${SMs::QMsmTst::SM::s::s1::D} */
        case D_SIG: {
            /*${SMs::QMsmTst::SM::s::s1::D::[!me->foo]} */
            if (!me->foo) {
                static struct {
                    QMState const *target;
                    QActionHandler act[3];
                } const tatbl_ = { /* tran-action table */
                    &QMsmTst_s_s, /* target state */
                    {
                        Q_ACTION_CAST(&QMsmTst_s1_x), /* exit */
                        Q_ACTION_CAST(&QMsmTst_s_i), /* initial tran. */
                        Q_ACTION_NULL /* zero terminator */
                    }
                };
                me->foo = 1U;
                BSP_display("s1-D;");
                status_ = QM_TRAN(&tatbl_);
            }
            else {
                status_ = QM_UNHANDLED();
            }
            break;
        }
        /*${SMs::QMsmTst::SM::s::s1::A} */
        case A_SIG: {
            static struct {
                QMState const *target;
                QActionHandler act[4];
            } const tatbl_ = { /* tran-action table */
                &QMsmTst_s1_s, /* target state */
                {
                    Q_ACTION_CAST(&QMsmTst_s1_x), /* exit */
                    Q_ACTION_CAST(&QMsmTst_s1_e), /* entry */
                    Q_ACTION_CAST(&QMsmTst_s1_i), /* initial tran. */
                    Q_ACTION_NULL /* zero terminator */
                }
            };
            BSP_display("s1-A;");
            status_ = QM_TRAN(&tatbl_);
            break;
        }
        /*${SMs::QMsmTst::SM::s::s1::B} */
        case B_SIG: {
            static struct {
                QMState const *target;
                QActionHandler act[2];
            } const tatbl_ = { /* tran-action table */
                &QMsmTst_s11_s, /* target state */
                {
                    Q_ACTION_CAST(&QMsmTst_s11_e), /* entry */
                    Q_ACTION_NULL /* zero terminator */
                }
            };
            BSP_display("s1-B;");
            status_ = QM_TRAN(&tatbl_);
            break;
        }
        /*${SMs::QMsmTst::SM::s::s1::F} */
        case F_SIG: {
            static struct {
                QMState const *target;
                QActionHandler act[5];
            } const tatbl_ = { /* tran-action table */
                &QMsmTst_s211_s, /* target state */
                {
                    Q_ACTION_CAST(&QMsmTst_s1_x), /* exit */
                    Q_ACTION_CAST(&QMsmTst_s2_e), /* entry */
                    Q_ACTION_CAST(&QMsmTst_s21_e), /* entry */
                    Q_ACTION_CAST(&QMsmTst_s211_e), /* entry */
                    Q_ACTION_NULL /* zero terminator */
                }
            };
            BSP_display("s1-F;");
            status_ = QM_TRAN(&tatbl_);
            break;
        }
        /*${SMs::QMsmTst::SM::s::s1::C} */
        case C_SIG: {
            static struct {
                QMState const *target;
                QActionHandler act[4];
            } const tatbl_ = { /* tran-action table */
                &QMsmTst_s2_s, /* target state */
                {
                    Q_ACTION_CAST(&QMsmTst_s1_x), /* exit */
                    Q_ACTION_CAST(&QMsmTst_s2_e), /* entry */
                    Q_ACTION_CAST(&QMsmTst_s2_i), /* initial tran. */
                    Q_ACTION_NULL /* zero terminator */
                }
            };
            BSP_display("s1-C;");
            status_ = QM_TRAN(&tatbl_);
            break;
        }
        default: {
            status_ = QM_SUPER();
            break;
        }
    }
    return status_;
}

/*${SMs::QMsmTst::SM::s::s1::s11} ..........................................*/
/*${SMs::QMsmTst::SM::s::s1::s11} */
static QState QMsmTst_s11_e(QMsmTst * const me) {
    BSP_display("s11-ENTRY;");
    (void)me; /* unused parameter */
    return QM_ENTRY(&QMsmTst_s11_s);
}
/*${SMs::QMsmTst::SM::s::s1::s11} */
static QState QMsmTst_s11_x(QMsmTst * const me) {
    BSP_display("s11-EXIT;");
    (void)me; /* unused parameter */
    return QM_EXIT(&QMsmTst_s11_s);
}
/*${SMs::QMsmTst::SM::s::s1::s11} */
static QState QMsmTst_s11(QMsmTst * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${SMs::QMsmTst::SM::s::s1::s11::H} */
        case H_SIG: {
            static struct {
                QMState const *target;
                QActionHandler act[4];
            } const tatbl_ = { /* tran-action table */
                &QMsmTst_s_s, /* target state */
                {
                    Q_ACTION_CAST(&QMsmTst_s11_x), /* exit */
                    Q_ACTION_CAST(&QMsmTst_s1_x), /* exit */
                    Q_ACTION_CAST(&QMsmTst_s_i), /* initial tran. */
                    Q_ACTION_NULL /* zero terminator */
                }
            };
            BSP_display("s11-H;");
            status_ = QM_TRAN(&tatbl_);
            break;
        }
        /*${SMs::QMsmTst::SM::s::s1::s11::D} */
        case D_SIG: {
            /*${SMs::QMsmTst::SM::s::s1::s11::D::[me->foo]} */
            if (me->foo) {
                static struct {
                    QMState const *target;
                    QActionHandler act[3];
                } const tatbl_ = { /* tran-action table */
                    &QMsmTst_s1_s, /* target state */
                    {
                        Q_ACTION_CAST(&QMsmTst_s11_x), /* exit */
                        Q_ACTION_CAST(&QMsmTst_s1_i), /* initial tran. */
                        Q_ACTION_NULL /* zero terminator */
                    }
                };
                me->foo = 0U;
                BSP_display("s11-D;");
                status_ = QM_TRAN(&tatbl_);
            }
            else {
                status_ = QM_UNHANDLED();
            }
            break;
        }
        /*${SMs::QMsmTst::SM::s::s1::s11::G} */
        case G_SIG: {
            static struct {
                QMState const *target;
                QActionHandler act[6];
            } const tatbl_ = { /* tran-action table */
                &QMsmTst_s211_s, /* target state */
                {
                    Q_ACTION_CAST(&QMsmTst_s11_x), /* exit */
                    Q_ACTION_CAST(&QMsmTst_s1_x), /* exit */
                    Q_ACTION_CAST(&QMsmTst_s2_e), /* entry */
                    Q_ACTION_CAST(&QMsmTst_s21_e), /* entry */
                    Q_ACTION_CAST(&QMsmTst_s211_e), /* entry */
                    Q_ACTION_NULL /* zero terminator */
                }
            };
            BSP_display("s11-G;");
            status_ = QM_TRAN(&tatbl_);
            break;
        }
        default: {
            status_ = QM_SUPER();
            break;
        }
    }
    return status_;
}

/*${SMs::QMsmTst::SM::s::s2} ...............................................*/
/*${SMs::QMsmTst::SM::s::s2} */
static QState QMsmTst_s2_e(QMsmTst * const me) {
    BSP_display("s2-ENTRY;");
    (void)me; /* unused parameter */
    return QM_ENTRY(&QMsmTst_s2_s);
}
/*${SMs::QMsmTst::SM::s::s2} */
static QState QMsmTst_s2_x(QMsmTst * const me) {
    BSP_display("s2-EXIT;");
    (void)me; /* unused parameter */
    return QM_EXIT(&QMsmTst_s2_s);
}
/*${SMs::QMsmTst::SM::s::s2::initial} */
static QState QMsmTst_s2_i(QMsmTst * const me) {
    static struct {
        QMState const *target;
        QActionHandler act[3];
    } const tatbl_ = { /* tran-action table */
        &QMsmTst_s211_s, /* target state */
        {
            Q_ACTION_CAST(&QMsmTst_s21_e), /* entry */
            Q_ACTION_CAST(&QMsmTst_s211_e), /* entry */
            Q_ACTION_NULL /* zero terminator */
        }
    };
    /*${SMs::QMsmTst::SM::s::s2::initial} */
    BSP_display("s2-INIT;");
    return QM_TRAN_INIT(&tatbl_);
}
/*${SMs::QMsmTst::SM::s::s2} */
static QState QMsmTst_s2(QMsmTst * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${SMs::QMsmTst::SM::s::s2::I} */
        case I_SIG: {
            /*${SMs::QMsmTst::SM::s::s2::I::[!me->foo]} */
            if (!me->foo) {
                me->foo = 1U;
                BSP_display("s2-I;");
                status_ = QM_HANDLED();
            }
            else {
                status_ = QM_UNHANDLED();
            }
            break;
        }
        /*${SMs::QMsmTst::SM::s::s2::F} */
        case F_SIG: {
            static struct {
                QMState const *target;
                QActionHandler act[4];
            } const tatbl_ = { /* tran-action table */
                &QMsmTst_s11_s, /* target state */
                {
                    Q_ACTION_CAST(&QMsmTst_s2_x), /* exit */
                    Q_ACTION_CAST(&QMsmTst_s1_e), /* entry */
                    Q_ACTION_CAST(&QMsmTst_s11_e), /* entry */
                    Q_ACTION_NULL /* zero terminator */
                }
            };
            BSP_display("s2-F;");
            status_ = QM_TRAN(&tatbl_);
            break;
        }
        /*${SMs::QMsmTst::SM::s::s2::C} */
        case C_SIG: {
            static struct {
                QMState const *target;
                QActionHandler act[4];
            } const tatbl_ = { /* tran-action table */
                &QMsmTst_s1_s, /* target state */
                {
                    Q_ACTION_CAST(&QMsmTst_s2_x), /* exit */
                    Q_ACTION_CAST(&QMsmTst_s1_e), /* entry */
                    Q_ACTION_CAST(&QMsmTst_s1_i), /* initial tran. */
                    Q_ACTION_NULL /* zero terminator */
                }
            };
            BSP_display("s2-C;");
            status_ = QM_TRAN(&tatbl_);
            break;
        }
        default: {
            status_ = QM_SUPER();
            break;
        }
    }
    return status_;
}

/*${SMs::QMsmTst::SM::s::s2::s21} ..........................................*/
/*${SMs::QMsmTst::SM::s::s2::s21} */
static QState QMsmTst_s21_e(QMsmTst * const me) {
    BSP_display("s21-ENTRY;");
    (void)me; /* unused parameter */
    return QM_ENTRY(&QMsmTst_s21_s);
}
/*${SMs::QMsmTst::SM::s::s2::s21} */
static QState QMsmTst_s21_x(QMsmTst * const me) {
    BSP_display("s21-EXIT;");
    (void)me; /* unused parameter */
    return QM_EXIT(&QMsmTst_s21_s);
}
/*${SMs::QMsmTst::SM::s::s2::s21::initial} */
static QState QMsmTst_s21_i(QMsmTst * const me) {
    static struct {
        QMState const *target;
        QActionHandler act[2];
    } const tatbl_ = { /* tran-action table */
        &QMsmTst_s211_s, /* target state */
        {
            Q_ACTION_CAST(&QMsmTst_s211_e), /* entry */
            Q_ACTION_NULL /* zero terminator */
        }
    };
    /*${SMs::QMsmTst::SM::s::s2::s21::initial} */
    BSP_display("s21-INIT;");
    return QM_TRAN_INIT(&tatbl_);
}
/*${SMs::QMsmTst::SM::s::s2::s21} */
static QState QMsmTst_s21(QMsmTst * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${SMs::QMsmTst::SM::s::s2::s21::G} */
        case G_SIG: {
            static struct {
                QMState const *target;
                QActionHandler act[5];
            } const tatbl_ = { /* tran-action table */
                &QMsmTst_s1_s, /* target state */
                {
                    Q_ACTION_CAST(&QMsmTst_s21_x), /* exit */
                    Q_ACTION_CAST(&QMsmTst_s2_x), /* exit */
                    Q_ACTION_CAST(&QMsmTst_s1_e), /* entry */
                    Q_ACTION_CAST(&QMsmTst_s1_i), /* initial tran. */
                    Q_ACTION_NULL /* zero terminator */
                }
            };
            BSP_display("s21-G;");
            status_ = QM_TRAN(&tatbl_);
            break;
        }
        /*${SMs::QMsmTst::SM::s::s2::s21::A} */
        case A_SIG: {
            static struct {
                QMState const *target;
                QActionHandler act[4];
            } const tatbl_ = { /* tran-action table */
                &QMsmTst_s21_s, /* target state */
                {
                    Q_ACTION_CAST(&QMsmTst_s21_x), /* exit */
                    Q_ACTION_CAST(&QMsmTst_s21_e), /* entry */
                    Q_ACTION_CAST(&QMsmTst_s21_i), /* initial tran. */
                    Q_ACTION_NULL /* zero terminator */
                }
            };
            BSP_display("s21-A;");
            status_ = QM_TRAN(&tatbl_);
            break;
        }
        /*${SMs::QMsmTst::SM::s::s2::s21::B} */
        case B_SIG: {
            static struct {
                QMState const *target;
                QActionHandler act[2];
            } const tatbl_ = { /* tran-action table */
                &QMsmTst_s211_s, /* target state */
                {
                    Q_ACTION_CAST(&QMsmTst_s211_e), /* entry */
                    Q_ACTION_NULL /* zero terminator */
                }
            };
            BSP_display("s21-B;");
            status_ = QM_TRAN(&tatbl_);
            break;
        }
        default: {
            status_ = QM_SUPER();
            break;
        }
    }
    return status_;
}

/*${SMs::QMsmTst::SM::s::s2::s21::s211} ....................................*/
/*${SMs::QMsmTst::SM::s::s2::s21::s211} */
static QState QMsmTst_s211_e(QMsmTst * const me) {
    BSP_display("s211-ENTRY;");
    (void)me; /* unused parameter */
    return QM_ENTRY(&QMsmTst_s211_s);
}
/*${SMs::QMsmTst::SM::s::s2::s21::s211} */
static QState QMsmTst_s211_x(QMsmTst * const me) {
    BSP_display("s211-EXIT;");
    (void)me; /* unused parameter */
    return QM_EXIT(&QMsmTst_s211_s);
}
/*${SMs::QMsmTst::SM::s::s2::s21::s211} */
static QState QMsmTst_s211(QMsmTst * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${SMs::QMsmTst::SM::s::s2::s21::s211::H} */
        case H_SIG: {
            static struct {
                QMState const *target;
                QActionHandler act[5];
            } const tatbl_ = { /* tran-action table */
                &QMsmTst_s_s, /* target state */
                {
                    Q_ACTION_CAST(&QMsmTst_s211_x), /* exit */
                    Q_ACTION_CAST(&QMsmTst_s21_x), /* exit */
                    Q_ACTION_CAST(&QMsmTst_s2_x), /* exit */
                    Q_ACTION_CAST(&QMsmTst_s_i), /* initial tran. */
                    Q_ACTION_NULL /* zero terminator */
                }
            };
            BSP_display("s211-H;");
            status_ = QM_TRAN(&tatbl_);
            break;
        }
        /*${SMs::QMsmTst::SM::s::s2::s21::s211::D} */
        case D_SIG: {
            static struct {
                QMState const *target;
                QActionHandler act[3];
            } const tatbl_ = { /* tran-action table */
                &QMsmTst_s21_s, /* target state */
                {
                    Q_ACTION_CAST(&QMsmTst_s211_x), /* exit */
                    Q_ACTION_CAST(&QMsmTst_s21_i), /* initial tran. */
                    Q_ACTION_NULL /* zero terminator */
                }
            };
            BSP_display("s211-D;");
            status_ = QM_TRAN(&tatbl_);
            break;
        }
        default: {
            status_ = QM_SUPER();
            break;
        }
    }
    return status_;
}
/*$enddef${SMs::QMsmTst} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

