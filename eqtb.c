#include "print.h" // MAX_SELECTOR
#include "global.h" // mem, depth_threshold, breadth_max
#include "hash.h"   // [func] sprint_cs, fontidtext
#include "printout.h" // [func] printcmdchr, printparam, printlengthparam
#include "texfunc.h"  // [func] printspec, shownodelist
#include "texmath.h"  // [func] print_scaled
#include "box.h"      // gluerefcount
#include "eqtb.h"

/** @addtogroup S220x255_P81x101
 * @{
 */

/// [ #220~255: THE TABLE OF EQUIVALENTS ]
UChar diag_oldsetting; // [0, MAX_SELECTOR=21]
static_assert(UMAXOF(UChar) >= MAX_SELECTOR,
              "diag_oldsetting = [0, MAX_SELECTOR=21]");

/// #253
MemoryWord eqtb[EQTB_SIZE - ACTIVE_BASE + 1]; // equivalents table
// store the eq level information
QuarterWord xeqlevel[EQTB_SIZE - INT_BASE + 1];


/// [#222, #228, #232, #240, #250]
void eqtb_init() {
    size_t k;

    /** [p82#222] */
    eq_type(UNDEFINED_CONTROL_SEQUENCE) = UNDEFINED_CS;
    equiv(UNDEFINED_CONTROL_SEQUENCE) = 0;
    eq_level(UNDEFINED_CONTROL_SEQUENCE) = LEVEL_ZERO;
    for (k = ACTIVE_BASE; k < UNDEFINED_CONTROL_SEQUENCE; k++) {
        /// TODO: need check
        /// eqtb[k] = eqtb[UNDEFINED_CONTROL_SEQUENCE];
        eqtb[k - ACTIVE_BASE] = eqtb[UNDEFINED_CONTROL_SEQUENCE - ACTIVE_BASE];
    }

    /** [p85#228] */
    equiv(GLUE_BASE) = zeroglue;
    eq_level(GLUE_BASE) = LEVEL_ONE;
    eq_type(GLUE_BASE) = GLUE_REF;
    for (k = GLUE_BASE + 1; k < LOCAL_BASE; k++) {
        eqtb[k - ACTIVE_BASE] = eqtb[GLUE_BASE - ACTIVE_BASE];
    }
    gluerefcount(zeroglue) += LOCAL_BASE - GLUE_BASE;

    /** [p88#232] */
    parshapeptr = 0;
    eq_type(PAR_SHAPE_LOC) = SHAPE_REF;
    eq_level(PAR_SHAPE_LOC) = LEVEL_ONE;
    for (k = OUTPUT_ROUTINE_LOC; k <= TOKS_BASE + 255; k++) {
        eqtb[k - ACTIVE_BASE] = eqtb[UNDEFINED_CONTROL_SEQUENCE - ACTIVE_BASE];
    }

    box(0) = 0;
    eq_type(BOX_BASE) = BOX_REF;
    eq_level(BOX_BASE) = LEVEL_ONE;
    for (k = BOX_BASE + 1; k <= BOX_BASE + 255; k++) {
        eqtb[k - ACTIVE_BASE] = eqtb[BOX_BASE - ACTIVE_BASE];
    }

    cur_font = NULL_FONT;
    eq_type(CUR_FONT_LOC) = DATA;
    eq_level(CUR_FONT_LOC) = LEVEL_ONE;
    for (k = MATH_FONT_BASE; k <= MATH_FONT_BASE + 47; k++) {
        eqtb[k - ACTIVE_BASE] = eqtb[CUR_FONT_LOC - ACTIVE_BASE];
    }

    equiv(CAT_CODE_BASE) = 0;
    eq_type(CAT_CODE_BASE) = DATA;
    eq_level(CAT_CODE_BASE) = LEVEL_ONE;
    for (k = CAT_CODE_BASE + 1; k < INT_BASE; k++) {
        eqtb[k - ACTIVE_BASE] = eqtb[CAT_CODE_BASE - ACTIVE_BASE];
    }

    // CatCode init
    for (k = 0; k <= 255; k++) {
        cat_code(k) = OTHER_CHAR; // 默认值 cat_12
        math_code(k) = k;
        sf_code(k) = 1000;
    }
    cat_code('\\') = ESCAPE;
    // TODO: 为什么忽略了一部分 catcode？
    // ? cat_1 LEFT_BRACE
    // ? cat_2 RIGHT_BRACE
    // ? cat_3 MATH_SHIFT
    // ? cat_4 TAB_MARK
    cat_code(CARRIAGE_RETURN) = CAR_RET; // cat_5
    // ? cat_6 MAC_PARAM
    // ? cat_7 SUP_MARK
    // ? cat_8 SUB_MARK
    cat_code(NULL_CODE) = IGNORE; // cat_9
    cat_code(' ') = SPACER;       // cat_10
    // cat_11 见下方
    // cat_12 为默认值
    // ? cat_13
    cat_code('%') = COMMENT;               // cat_14
    cat_code(INVALID_CODE) = INVALID_CHAR; // cat_15

    for (k = '0'; k <= '9'; k++) {
        math_code(k) = k + VAR_CODE;
    }
    for (k = 'A'; k <= 'Z'; k++) {
        cat_code(k) = LETTER; // cat_11
        cat_code(k + 'a' - 'A') = LETTER;
        math_code(k) = k + VAR_CODE + 256;
        math_code(k + 'a' - 'A') = k + 'a' - 'A' + VAR_CODE + 256;
        lc_code(k) = k + 'a' - 'A';
        lc_code(k + 'a' - 'A') = k + 'a' - 'A';
        uc_code(k) = k;
        uc_code(k + 'a' - 'A') = k;
        sf_code(k) = 999;
    } // for (k = 'A'; k <= 'Z'; k++)


    /** [p97#240] */
    for (k = INT_BASE; k < DEL_CODE_BASE; k++) {
        eqtb[k - ACTIVE_BASE].int_ = 0;
    }
    mag = 1000;
    tolerance = 10000;
    hangafter = 1;
    maxdeadcycles = 25;
    ESCAPE_CHAR = '\\';
    end_line_char = CARRIAGE_RETURN;
    for (k = 0; k <= 255; k++) {
        del_code(k) = -1;
    }
    del_code('.') = 0; // this null delimiter is used in error recovery


    /** [p101#250] */
    for (k = DIMEN_BASE; k <= EQTB_SIZE; k++) {
        eqtb[k - ACTIVE_BASE].sc = 0;
    }
}

/** [#225]: 打印 `glue` 参数的名称
 * 
 * \param[in] n
 * \return void 无返回值
 * 
 * 函数会打印参数对应的字符串。
 * 如果没有对应的字符串，则打印 `"[unknown glue parameter!]"`
 */
void print_skip_param(Integer code) {
#ifndef USE_REAL_STR
    switch (code) {
        case LINE_SKIP_CODE: print_esc(S(341)); break;
        case BASELINE_SKIP_CODE: print_esc(S(342)); break;
        case PAR_SKIP_CODE: print_esc(S(343)); break;
        case ABOVE_DISPLAY_SKIP_CODE: print_esc(S(344)); break;
        case BELOW_DISPLAY_SKIP_CODE: print_esc(S(345)); break;
        case ABOVE_DISPLAY_SHORT_SKIP_CODE: print_esc(S(346)); break;
        case BELOW_DISPLAY_SHORT_SKIP_CODE: print_esc(S(347)); break;
        case LEFT_SKIP_CODE: print_esc(S(348)); break;
        case RIGHT_SKIP_CODE: print_esc(S(349)); break;
        case TOP_SKIP_CODE: print_esc(S(350)); break;
        case SPLIT_TOP_SKIP_CODE: print_esc(S(351)); break;
        case TAB_SKIP_CODE: print_esc(S(352)); break;
        case SPACE_SKIP_CODE: print_esc(S(353)); break;
        case XSPACE_SKIP_CODE: print_esc(S(354)); break;
        case PAR_FILL_SKIP_CODE: print_esc(S(355)); break;
        case THIN_MU_SKIP_CODE: print_esc(S(356)); break;
        case MED_MU_SKIP_CODE: print_esc(S(357)); break;
        case THICK_MU_SKIP_CODE: print_esc(S(358)); break;

        default: print(S(359)); break;
    } /* switch (code) */
#else // use real string
    switch (code) {
        case LINE_SKIP_CODE: print_esc_str("lineskip"); break;
        case BASELINE_SKIP_CODE: print_esc_str("baselineskip"); break;
        case PAR_SKIP_CODE: print_esc_str("parskip"); break;
        case ABOVE_DISPLAY_SKIP_CODE: print_esc_str("abovedisplayskip"); break;
        case BELOW_DISPLAY_SKIP_CODE: print_esc_str("belowdisplayskip"); break;
        case ABOVE_DISPLAY_SHORT_SKIP_CODE: print_esc_str("abovedisplayshortskip"); break;
        case BELOW_DISPLAY_SHORT_SKIP_CODE: print_esc_str("belowdisplayshortskip"); break;
        case LEFT_SKIP_CODE: print_esc_str("leftskip"); break;
        case RIGHT_SKIP_CODE: print_esc_str("rightskip"); break;
        case TOP_SKIP_CODE: print_esc_str("topskip"); break;
        case SPLIT_TOP_SKIP_CODE: print_esc_str("splittopskip"); break;
        case TAB_SKIP_CODE: print_esc_str("tabskip"); break;
        case SPACE_SKIP_CODE: print_esc_str("spaceskip"); break;
        case XSPACE_SKIP_CODE: print_esc_str("xspaceskip"); break;
        case PAR_FILL_SKIP_CODE: print_esc_str("parfillskip"); break;
        case THIN_MU_SKIP_CODE: print_esc_str("thinmuskip"); break;
        case MED_MU_SKIP_CODE: print_esc_str("medmuskip"); break;
        case THICK_MU_SKIP_CODE: print_esc_str("thickmuskip"); break;

        default: print_str("[unknown glue parameter!]"); break;
    } /* switch (code) */ 
#endif /* USE_REAL_STR */
} // #225: print_skip_param

/// [#245] prepare to do some tracing.
void begindiagnostic(void) {
    diag_oldsetting = selector;
    if (tracingonline > 0 || selector != TERM_AND_LOG) return;

    selector--;
    if (history == SPOTLESS) history = WARNING_ISSUED;
}

/// [#245] restore proper conditions after tracing.
void enddiagnostic(Boolean blankline) {
    printnl(S(385)); // ""
    if (blankline) println();
    selector = diag_oldsetting;
}

#ifdef tt_STAT
/// #252:
void showeqtb(HalfWord n) {
    if (n < ACTIVE_BASE) {
        print_char('?');
        return;
    }
    /// [#223] displays the current meaning of an eqtb entry in region 1 or 2.
    if (n < GLUE_BASE) {
        sprint_cs(n);
        print_char('=');
        printcmdchr(eq_type(n), equiv(n));
        if (eq_type(n) >= CALL) {
            print_char(':');
            showtokenlist(link(equiv(n)), 0, 32);
        }
        return;
    }

    if (n < LOCAL_BASE) { /*229:*/
        if (n < SKIP_BASE) {
            print_skip_param(n - GLUE_BASE);
            print_char('=');
            if (n < GLUE_BASE + THIN_MU_SKIP_CODE)
                printspec(equiv(n), S(459));
            else
                printspec(equiv(n), S(390));
            return;
        }
        if (n < MU_SKIP_BASE) {
            print_esc(S(460));
            print_int(n - SKIP_BASE);
            print_char('=');
            printspec(equiv(n), S(459));
            return;
        }
        print_esc(S(461));
        print_int(n - MU_SKIP_BASE);
        print_char('=');
        printspec(equiv(n), S(390));
        return;
    }
    if (n < INT_BASE) { /*233:*/
        if (n == PAR_SHAPE_LOC) {
            print_esc(S(462));
            print_char('=');
            if (parshapeptr == 0)
                print_char('0');
            else
                print_int(info(parshapeptr));
            return;
        }
        if (n < TOKS_BASE) {
            printcmdchr(ASSIGN_TOKS, n);
            print_char('=');
            if (equiv(n) != 0) showtokenlist(link(equiv(n)), 0, 32);
            return;
        }
        if (n < BOX_BASE) {
            print_esc(S(463));
            print_int(n - TOKS_BASE);
            print_char('=');
            if (equiv(n) != 0) showtokenlist(link(equiv(n)), 0, 32);
            return;
        }
        if (n < CUR_FONT_LOC) {
            print_esc(S(464));
            print_int(n - BOX_BASE);
            print_char('=');
            if (equiv(n) == 0) {
                print(S(465));
                return;
            }
            depth_threshold = 0;
            breadth_max = 1;
            shownodelist(equiv(n));
            return;
        }
        if (n < CAT_CODE_BASE) { /*234:*/
            if (n == CUR_FONT_LOC)
                print(S(466));
            else if (n < MATH_FONT_BASE + 16) {
                print_esc(S(266));
                print_int(n - MATH_FONT_BASE);
            } else if (n < MATH_FONT_BASE + 32) {
                print_esc(S(267));
                print_int(n - MATH_FONT_BASE - 16);
            } else {
                print_esc(S(268));
                print_int(n - MATH_FONT_BASE - 32);
            }
            print_char('=');
            print_esc(fontidtext(equiv(n)));
            return;
        }
        /*:234*/
        if (n < MATH_CODE_BASE) {
            if (n < LC_CODE_BASE) {
                print_esc(S(467));
                print_int(n - CAT_CODE_BASE);
            } else if (n < UC_CODE_BASE) {
                print_esc(S(468));
                print_int(n - LC_CODE_BASE);
            } else if (n < SF_CODE_BASE) {
                print_esc(S(469));
                print_int(n - UC_CODE_BASE);
            } else {
                print_esc(S(470));
                print_int(n - SF_CODE_BASE);
            }
            print_char('=');
            print_int(equiv(n));
            return;
        }
        print_esc(S(471));
        print_int(n - MATH_CODE_BASE);
        print_char('=');
        print_int(equiv(n));
        return;
    }
    if (n < DIMEN_BASE) { /*242:*/
        if (n < COUNT_BASE)
            printparam(n - INT_BASE);
        else if (n < DEL_CODE_BASE) {
            print_esc(S(472));
            print_int(n - COUNT_BASE);
        } else {
            print_esc(S(473));
            print_int(n - DEL_CODE_BASE);
        }
        print_char('=');
        print_int(eqtb[n - ACTIVE_BASE].int_);
        return;
    }                   /*:242*/
    if (n > EQTB_SIZE) { /*251:*/
        print_char('?');
        return;
    }
    /*:251*/
    if (n < SCALED_BASE)
        printlengthparam(n - DIMEN_BASE);
    else {
        print_esc(S(474));
        print_int(n - SCALED_BASE);
    }
    print_char('=');
    print_scaled(eqtb[n - ACTIVE_BASE].sc);
    print(S(459));

    /*:229*/
    /*235:*/
    /*:235*/
    /*:233*/
} // #252: showeqtb
#endif // #252: tt_STAT

/** @}*/ // end group S220x255_P81x101

// fonts
Integer get_defaulthyphenchar(void) { return defaulthyphenchar; }
Integer get_defaultskewchar(void) { return defaultskewchar; }