#include "tex_constant.h" // [enum] CatCode, TexCommandCode, CmdCode, hvSkipDiff
#include "str.h" // [func] slow_print
#include "fonts.h" 
    // [func] get_fontsize, get_fontdsize, get_fontname
#include "texmath.h"  // [func] print_scaled
#include "expand.h" // [macro] IF_EOF_CODE, splitbotmark, splitfirstmark, botmark
#include "scan.h"     // [macro] INT_VAL
#include "print.h"    // [func] print_esc_str
#include "eqtb.h"     // [func] print_skip_param
#include "box.h"      // widthoffset, heightoffset, NORMAL
#include "error.h"
#include "mmode.h"
#include "align.h"
#include "extension.h"
#include "main_ctrl.h" // [const] boxcode, atopcode, atopcode, delimitedcode
#include "printout.h" // [export]

/// #247: 
void printlengthparam(long n) {
#ifndef USE_REAL_STR
    switch (n) {
        case parindentcode: print_esc(S(1089)); break;
        case mathsurroundcode: print_esc(S(1090)); break;
        case lineskiplimitcode: print_esc(S(1091)); break;
        case hsizecode: print_esc(S(1092)); break;
        case vsizecode: print_esc(S(1093)); break;
        case maxdepthcode: print_esc(S(1094)); break;
        case splitmaxdepthcode: print_esc(S(1095)); break;
        case boxmaxdepthcode: print_esc(S(1096)); break;
        case hfuzzcode: print_esc(S(1097)); break;
        case vfuzzcode: print_esc(S(1098)); break;
        case delimitershortfallcode: print_esc(S(1099)); break;
        case nulldelimiterspacecode: print_esc(S(1100)); break;
        case scriptspacecode: print_esc(S(1101)); break;
        case predisplaysizecode: print_esc(S(1102)); break;
        case displaywidthcode: print_esc(S(1103)); break;
        case displayindentcode: print_esc(S(1104)); break;
        case overfullrulecode: print_esc(S(1105)); break;
        case hangindentcode: print_esc(S(1106)); break;
        case hoffsetcode: print_esc(S(1107)); break;
        case voffsetcode: print_esc(S(1108)); break;
        case emergencystretchcode: print_esc(S(1109)); break;

        default: print(S(1254)); break;
    } // switch (n)
#else
    switch (n) {
        case parindentcode: print_esc_str("parindent"); break;
        case mathsurroundcode: print_esc_str("mathsurround"); break;
        case lineskiplimitcode: print_esc_str("lineskiplimit"); break;
        case hsizecode: print_esc_str("hsize"); break;
        case vsizecode: print_esc_str("vsize"); break;
        case maxdepthcode: print_esc_str("maxdepth"); break;
        case splitmaxdepthcode: print_esc_str("splitmaxdepth"); break;
        case boxmaxdepthcode: print_esc_str("boxmaxdepth"); break;
        case hfuzzcode: print_esc_str("hfuzz"); break;
        case vfuzzcode: print_esc_str("vfuzz"); break;
        case delimitershortfallcode: print_esc_str("delimitershortfall"); break;
        case nulldelimiterspacecode: print_esc_str("nulldelimiterspace"); break;
        case scriptspacecode: print_esc_str("scriptspace"); break;
        case predisplaysizecode: print_esc_str("predisplaysize"); break;
        case displaywidthcode: print_esc_str("displaywidth"); break;
        case displayindentcode: print_esc_str("displayindent"); break;
        case overfullrulecode: print_esc_str("overfullrule"); break;
        case hangindentcode: print_esc_str("hangindent"); break;
        case hoffsetcode: print_esc_str("hoffset"); break;
        case voffsetcode: print_esc_str("voffset"); break;
        case emergencystretchcode: print_esc_str("emergencystretch"); break;

        default: print_str("[unknown dimen parameter!]"); break;
    } // switch (n)
#endif /* USE_REAL_STR */
} // #247: printlengthparam

/// 237
void printparam(long n) {
#ifndef USE_REAL_STR
    switch (n) {
        case pretolerancecode: print_esc(S(1035)); break;
        case tolerancecode: print_esc(S(1036)); break;
        case linepenaltycode: print_esc(S(1037)); break;
        case hyphenpenaltycode: print_esc(S(1038)); break;
        case exhyphenpenaltycode: print_esc(S(1039)); break;
        case clubpenaltycode: print_esc(S(1040)); break;
        case widowpenaltycode: print_esc(S(1041)); break;
        case displaywidowpenaltycode: print_esc(S(1042)); break;
        case brokenpenaltycode: print_esc(S(1043)); break;
        case binoppenaltycode: print_esc(S(1044)); break;
        case relpenaltycode: print_esc(S(1045)); break;
        case predisplaypenaltycode: print_esc(S(1046)); break;
        case postdisplaypenaltycode: print_esc(S(1047)); break;
        case interlinepenaltycode: print_esc(S(1048)); break;
        case doublehyphendemeritscode: print_esc(S(1049)); break;
        case finalhyphendemeritscode: print_esc(S(1050)); break;
        case adjdemeritscode: print_esc(S(1051)); break;
        case magcode: print_esc(S(1052)); break;
        case delimiterfactorcode: print_esc(S(1053)); break;
        case loosenesscode: print_esc(S(1054)); break;
        case timecode: print_esc(S(1055)); break;
        case daycode: print_esc(S(1056)); break;
        case monthcode: print_esc(S(1057)); break;
        case yearcode: print_esc(S(1058)); break;
        case showboxbreadthcode: print_esc(S(1059)); break;
        case showboxdepthcode: print_esc(S(1060)); break;
        case hbadnesscode: print_esc(S(1061)); break;
        case vbadnesscode: print_esc(S(1062)); break;
        case pausingcode: print_esc(S(1063)); break;
        case tracingonlinecode: print_esc(S(1064)); break;
        case tracingmacroscode: print_esc(S(1065)); break;
        case tracingstatscode: print_esc(S(1066)); break;
        case tracingparagraphscode: print_esc(S(1067)); break;
        case tracingpagescode: print_esc(S(1068)); break;
        case tracingoutputcode: print_esc(S(1069)); break;
        case tracinglostcharscode: print_esc(S(1070)); break;
        case tracingcommandscode: print_esc(S(1071)); break;
        case tracingrestorescode: print_esc(S(1072)); break;
        case uchyphcode: print_esc(S(1073)); break;
        case outputpenaltycode: print_esc(S(1074)); break;
        case maxdeadcyclescode: print_esc(S(1075)); break;
        case hangaftercode: print_esc(S(1076)); break;
        case floatingpenaltycode: print_esc(S(1077)); break;
        case globaldefscode: print_esc(S(1078)); break;
        case curfamcode: print_esc(S(333)); break;
        case ESCAPE_CHARcode: print_esc(S(1079)); break;
        case defaulthyphencharcode: print_esc(S(1080)); break;
        case defaultskewcharcode: print_esc(S(1081)); break;
        case endlinecharcode: print_esc(S(1082)); break;
        case newlinecharcode: print_esc(S(1083)); break;
        case languagecode: print_esc(S(1084)); break;
        case lefthyphenmincode: print_esc(S(1085)); break;
        case righthyphenmincode: print_esc(S(1086)); break;
        case holdinginsertscode: print_esc(S(1087)); break;
        case errorcontextlinescode: print_esc(S(1088)); break;

        default: print(S(1255)); break;
    } // switch (n)
#else
    switch (n) {
        case pretolerancecode: print_esc_str("pretolerance"); break;
        case tolerancecode: print_esc_str("tolerance"); break;

        case linepenaltycode: print_esc_str("linepenalty"); break;
        case hyphenpenaltycode: print_esc_str("hyphenpenalty"); break;
        case exhyphenpenaltycode: print_esc_str("exhyphenpenalty"); break;
        case clubpenaltycode: print_esc_str("clubpenalty"); break;
        case widowpenaltycode: print_esc_str("widowpenalty"); break;
        case displaywidowpenaltycode: print_esc_str("displaywidowpenalty"); break;
        case brokenpenaltycode: print_esc_str("brokenpenalty"); break;
        case binoppenaltycode: print_esc_str("binoppenalty"); break;
        case relpenaltycode: print_esc_str("relpenalty"); break;
        case predisplaypenaltycode: print_esc_str("predisplaypenalty"); break;
        case postdisplaypenaltycode: print_esc_str("postdisplaypenalty"); break;
        case interlinepenaltycode: print_esc_str("interlinepenalty"); break;

        case doublehyphendemeritscode: print_esc_str("doublehyphendemerits"); break;
        case finalhyphendemeritscode: print_esc_str("finalhyphendemerits"); break;
        case adjdemeritscode: print_esc_str("adjdemerits"); break;
        case magcode: print_esc_str("mag"); break;
        case delimiterfactorcode: print_esc_str("delimiterfactor"); break;
        case loosenesscode: print_esc_str("looseness"); break;
        case timecode: print_esc_str("time"); break;
        case daycode: print_esc_str("day"); break;
        case monthcode: print_esc_str("month"); break;
        case yearcode: print_esc_str("year"); break;
        case showboxbreadthcode: print_esc_str("showboxbreadth"); break;
        case showboxdepthcode: print_esc_str("showboxdepth"); break;
        case hbadnesscode: print_esc_str("hbadness"); break;
        case vbadnesscode: print_esc_str("vbadness"); break;
        case pausingcode: print_esc_str("pausing"); break;

        case tracingonlinecode: print_esc_str("tracingonline"); break;
        case tracingmacroscode: print_esc_str("tracingmacros"); break;
        case tracingstatscode: print_esc_str("tracingstats"); break;
        case tracingparagraphscode: print_esc_str("tracingparagraphs"); break;
        case tracingpagescode: print_esc_str("tracingpages"); break;
        case tracingoutputcode: print_esc_str("tracingoutput"); break;
        case tracinglostcharscode: print_esc_str("tracinglostchars"); break;
        case tracingcommandscode: print_esc_str("tracingcommands"); break;
        case tracingrestorescode: print_esc_str("tracingrestores"); break;

        case uchyphcode: print_esc_str("uchyph"); break;
        case outputpenaltycode: print_esc_str("outputpenalty"); break;
        case maxdeadcyclescode: print_esc_str("maxdeadcycles"); break;
        case hangaftercode: print_esc_str("hangafter"); break;
        case floatingpenaltycode: print_esc_str("floatingpenalty"); break;
        case globaldefscode: print_esc_str("globaldefs"); break;
        case curfamcode: print_esc_str("fam"); break;
        case ESCAPE_CHARcode: print_esc_str("escapechar"); break;
        case defaulthyphencharcode: print_esc_str("defaulthyphenchar"); break;
        case defaultskewcharcode: print_esc_str("defaultskewchar"); break;
        case endlinecharcode: print_esc_str("endlinechar"); break;
        case newlinecharcode: print_esc_str("newlinechar"); break;
        case languagecode: print_esc_str("language"); break;
        case lefthyphenmincode: print_esc_str("lefthyphenmin"); break;
        case righthyphenmincode: print_esc_str("righthyphenmin"); break;
        case holdinginsertscode: print_esc_str("holdinginserts"); break;
        case errorcontextlinescode: print_esc_str("errorcontextlines"); break;

        default: print_str("[unknown integer parameter!]"); break;
    } // switch (n)
#endif /* USE_REAL_STR */
    
} // 237: printparam

/// #298
void printcmdchr(QuarterWord cmd, HalfWord chrcode) {
    switch (cmd) {
        case LEFT_BRACE: chrcmd(S(1256)); break;  // "begin−group character "
        case RIGHT_BRACE: chrcmd(S(1257)); break; // "end−group character "
        case MATH_SHIFT: chrcmd(S(1258)); break;  // "math shift character "
        case MAC_PARAM: chrcmd(S(1259)); break;   // "macro parameter character "
        case SUP_MARK: chrcmd(S(1260)); break;    // "superscript character "
        case SUB_MARK: chrcmd(S(1261)); break;    // "subscript character "
        case ENDV: print(S(1262)); break;         // "subscript character "
        case SPACER: chrcmd(S(1263)); break;      // "blank space "
        case LETTER: chrcmd(S(1264)); break;      // "the letter "
        case OTHER_CHAR: chrcmd(S(1265)); break;  // "the character "
    
        /*227:*/
        case ASSIGN_GLUE:
        case ASSIGN_MU_GLUE: /*:227*/
            if (chrcode < SKIP_BASE)
                print_skip_param(chrcode - GLUE_BASE);
            else if (chrcode < MU_SKIP_BASE) {
                print_esc(S(460));
                print_int(chrcode - SKIP_BASE);
            } else {
                print_esc(S(461));
                print_int(chrcode - MU_SKIP_BASE);
            }
            break;

        /// [988#231]
        case ASSIGN_TOKS:
            if (chrcode >= TOKS_BASE) {
                #ifndef USE_REAL_STR
                    print_esc(S(463));
                #else
                    print_esc_str("toks");
                #endif /* USE_REAL_STR */
                print_int(chrcode - TOKS_BASE);
            } else {
                #ifndef USE_REAL_STR
                    switch (chrcode) {
                        case OUTPUT_ROUTINE_LOC: print_esc(S(1026)); break;
                        case EVERY_PAR_LOC: print_esc(S(1027)); break;
                        case EVERY_MATH_LOC: print_esc(S(1028)); break;
                        case EVERY_DISPLAY_LOC: print_esc(S(1029)); break;
                        case EVERY_HBOX_LOC: print_esc(S(1030)); break;
                        case EVERY_VBOX_LOC: print_esc(S(1031)); break;
                        case EVERY_JOB_LOC: print_esc(S(1032)); break;
                        case EVERY_CR_LOC: print_esc(S(1033)); break;
                        default: print_esc(S(1034)); break;
                    }
                #else
                    switch (chrcode) {
                        case OUTPUT_ROUTINE_LOC: print_esc_str("output"); break;
                        case EVERY_PAR_LOC: print_esc_str("everypar"); break;
                        case EVERY_MATH_LOC: print_esc_str("everymath"); break;
                        case EVERY_DISPLAY_LOC: print_esc_str("everydisplay"); break;
                        case EVERY_HBOX_LOC: print_esc_str("everyhbox"); break;
                        case EVERY_VBOX_LOC: print_esc_str("everyvbox"); break;
                        case EVERY_JOB_LOC: print_esc_str("everyjob"); break;
                        case EVERY_CR_LOC: print_esc_str("everycr"); break;
                        default: print_esc_str("errhelp"); break;
                    }
                #endif /* USE_REAL_STR */
            }
            break;
            /*239:*/
        case ASSIGN_INT:
            if (chrcode < COUNT_BASE)
                printparam(chrcode - INT_BASE);
            else {
                print_esc(S(472));
                print_int(chrcode - COUNT_BASE);
            } /*:239*/
            break;
            /*249:*/
        case ASSIGN_DIMEN: /*:249*/
            if (chrcode < SCALED_BASE)
                printlengthparam(chrcode - DIMEN_BASE);
            else {
                print_esc(S(474));
                print_int(chrcode - SCALED_BASE);
            }
            break;
            /*266:*/
        case ACCENT: print_esc(S(417)); break;
        case ADVANCE: print_esc(S(1110)); break;
        case AFTER_ASSIGNMENT: print_esc(S(1111)); break;
        case AFTER_GROUP: print_esc(S(1112)); break;
        case ASSIGN_FONT_DIMEN: print_esc(S(1119)); break;
        case BEGIN_GROUP: print_esc(S(1113)); break;
        case BREAK_PENALTY: print_esc(S(761)); break;
        case CHAR_NUM: print_esc(S(1114)); break;
        case CS_NAME: print_esc(S(262)); break;
        case DEF_FONT: print_esc(S(1118)); break;
        case DELIM_NUM: print_esc(S(1115)); break;
        case DIVIDE: print_esc(S(1116)); break;
        case END_CS_NAME: print_esc(S(263)); break;
        case END_GROUP: print_esc(S(836)); break;
        case EX_SPACE: print_esc(' '); break;
        case EXPAND_AFTER: print_esc(S(1117)); break;
        case HALIGN: print_esc(S(724)); break;
        case HRULE: print_esc(S(863)); break;
        case IGNORE_SPACES: print_esc(S(1120)); break;
        case INSERT: print_esc(S(374)); break;
        case ITAL_CORR: print_esc('/'); break;
        case MARK: print_esc(S(402)); break;
        case MATH_ACCENT: print_esc(S(913)); break;
        case MATH_CHAR_NUM: print_esc(S(1121)); break;
        case MATH_CHOICE: print_esc(S(404)); break;
        case MULTIPLY: print_esc(S(1122)); break;
        case NO_ALIGN: print_esc(S(897)); break;
        case NO_BOUNDARY: print_esc(S(1123)); break;
        case NO_EXPAND: print_esc(S(1124)); break;
        case NON_SCRIPT: print_esc(S(388)); break;
        case OMIT: print_esc(S(900)); break;
        case RADICAL: print_esc(S(416)); break;
        case READ_TO_CS: print_esc(S(656)); break;
        case RELAX: print_esc(S(1125)); break;
        case SET_BOX: print_esc(S(970)); break;
        case SET_PREV_GRAF: print_esc(S(948)); break;
        case SET_SHAPE: print_esc(S(462)); break;
        case THE: print_esc(S(604)); break;
        case TOKS_REGISTER: print_esc(S(463)); break;
        case VADJUST: print_esc(S(403)); break;
        case VALIGN: print_esc(S(1126)); break;
        case VCENTER: print_esc(S(415)); break;
        case VRULE: print_esc(S(1127)); break;
        /*:266*/
        /*335:*/
        case PAR_END: print_esc(S(760)); break;
        /*:335*/
        /*377:*/
        case INPUT: /*:377*/
            if (chrcode == 0)
                print_esc(S(1128));
            else
                print_esc(S(1129));
            break;
            /*385:*/
        case TOP_BOT_MARK: /*:385*/
            switch (chrcode) {
                case firstmarkcode: print_esc(S(1131)); break;
                case botmarkcode: print_esc(S(1132)); break;
                case splitfirstmarkcode: print_esc(S(1133)); break;
                case splitbotmarkcode: print_esc(S(1134)); break;
                default: print_esc(S(1130)); break;
            }
            break;
            /*412:*/
        case REGISTER: /*:412*/
            if (chrcode == INT_VAL)
                print_esc(S(472));
            else if (chrcode == DIMEN_VAL)
                print_esc(S(474));
            else if (chrcode == GLUE_VAL)
                print_esc(S(460));
            else
                print_esc(S(461));
            break;
            /*417:*/
        case SET_AUX:
            if (chrcode == V_MODE)
                print_esc(S(1136));
            else
                print_esc(S(1135));
            break;
        case SET_PAGE_INT:
            if (chrcode == 0)
                print_esc(S(1137));
            else
                print_esc(S(1138));
            break;
        case SET_BOX_DIMEN:
            if (chrcode == widthoffset)
                print_esc(S(1139));
            else {
                if (chrcode == heightoffset)
                    print_esc(S(1140));
                else
                    print_esc(S(1141));
            }
            break;
        case LAST_ITEM: /*:417*/
            switch (chrcode) {
                case INT_VAL: print_esc(S(1142)); break;
                case DIMEN_VAL: print_esc(S(1143)); break;
                case GLUE_VAL: print_esc(S(1144)); break;
                case INPUT_LINE_NO_CODE: print_esc(S(1145)); break;
                default: print_esc(S(1146)); break;
            }
            break;
            /*469:*/
        case CONVERT: /*:469*/
            switch (chrcode) {
                case numbercode: print_esc(S(1147)); break;
                case romannumeralcode: print_esc(S(1148)); break;
                case stringcode: print_esc(S(1149)); break;
                case meaningcode: print_esc(S(1150)); break;
                case fontnamecode: print_esc(S(1151)); break;
                default: print_esc(S(1152)); break;
            }
            break;
            /*488:*/
        case IF_TEST: /*:488*/
            switch (chrcode) {
                case IF_CAT_CODE: print_esc(S(1153)); break;
                case IF_INT_CODE: print_esc(S(1154)); break;
                case IF_DIM_CODE: print_esc(S(1155)); break;
                case IF_ODD_CODE: print_esc(S(1156)); break;
                case IF_VMODE_CODE: print_esc(S(1157)); break;
                case IF_HMODE_CODE: print_esc(S(1158)); break;
                case IF_MMODE_CODE: print_esc(S(1159)); break;
                case IF_INNER_CODE: print_esc(S(1160)); break;
                case IF_VOID_CODE: print_esc(S(1161)); break;
                case IF_HBOX_CODE: print_esc(S(1162)); break;
                case IF_VBOX_CODE: print_esc(S(1163)); break;
                case IF_X_CODE: print_esc(S(1164)); break;
                case IF_EOF_CODE: print_esc(S(1165)); break;
                case IF_TRUE_CODE: print_esc(S(1166)); break;
                case IF_FALSE_CODE: print_esc(S(1167)); break;
                case IF_CASE_CODE: print_esc(S(1168)); break;
                default: print_esc(S(658)); break;
            }
            break;
            /*492:*/
        case FI_OR_ELSE: /*:492*/
            if (chrcode == ficode)
                print_esc(S(1169));
            else if (chrcode == orcode)
                print_esc(S(664));
            else
                print_esc(S(1170));
            break;
            /*781:*/
        case TAB_MARK:
            if (chrcode == spancode)
                print_esc(S(1172));
            else {
                chrcmd(S(1266));
            }
            break;
        case CAR_RET: /*:781*/
            if (chrcode == crcode)
                print_esc(S(737));
            else
                print_esc(S(1173));
            break;
            /*984:*/
        case SET_PAGE_DIMEN: /*:984*/
            switch (chrcode) {
                case 0: print_esc(S(1175)); break;
                case 1: print_esc(S(1176)); break;
                case 2: print_esc(S(1177)); break;
                case 3: print_esc(S(1178)); break;
                case 4: print_esc(S(1179)); break;
                case 5: print_esc(S(1180)); break;
                case 6: print_esc(S(1181)); break;
                default: print_esc(S(1182)); break;
            }
            break;
            /*1053:*/
        case STOP: /*:1053*/
            if (chrcode == 1)
                print_esc(S(1184));
            else
                print_esc(S(1183));
            break;
            /*1059:*/
        case HSKIP:
            switch (chrcode) {
                case SKIP_CODE: print_esc(S(1185)); break;
                case FIL_CODE: print_esc(S(1186)); break;
                case FILL_CODE: print_esc(S(1187)); break;
                case SS_CODE: print_esc(S(1188)); break;
                default: print_esc(S(1189)); break;
            }
            break;
        case VSKIP:
            switch (chrcode) {
                case SKIP_CODE: print_esc(S(1190)); break;
                case FIL_CODE: print_esc(S(1191)); break;
                case FILL_CODE: print_esc(S(1192)); break;
                case SS_CODE: print_esc(S(1193)); break;
                default: print_esc(S(1194)); break;
            }
            break;
        case MSKIP: print_esc(S(389)); break;
        case KERN: print_esc(S(391)); break;
        case MKERN: /*:1059*/
            print_esc(S(393));
            break;
            /*1072:*/
        case HMOVE:
            if (chrcode == 1)
                print_esc(S(1195));
            else
                print_esc(S(1196));
            break;
        case VMOVE:
            if (chrcode == 1)
                print_esc(S(1197));
            else
                print_esc(S(1198));
            break;
        case MAKE_BOX:
            switch (chrcode) {
                case boxcode: print_esc(S(464)); break;
                case copycode: print_esc(S(1199)); break;
                case lastboxcode: print_esc(S(1200)); break;
                case vsplitcode: print_esc(S(797)); break;
                case vtopcode: print_esc(S(1201)); break;
                case vtopcode + V_MODE: print_esc(S(799)); break;
                default: print_esc(S(1202)); break;
            }
            break;
        case LEADER_SHIP: /*:1072*/
            if (chrcode == aleaders)
                print_esc(S(1204));
            else if (chrcode == cleaders)
                print_esc(S(1205));
            else if (chrcode == xleaders)
                print_esc(S(1206));
            else
                print_esc(S(1203));
            break;
            /*1089:*/
        case START_PAR: /*:1089*/
            if (chrcode == 0)
                print_esc(S(1208));
            else
                print_esc(S(1207));
            break;
            /*1108:*/
        case REMOVE_ITEM:
            if (chrcode == GLUE_NODE)
                print_esc(S(1211));
            else if (chrcode == KERN_NODE)
                print_esc(S(1210));
            else
                print_esc(S(1209));
            break;
        case UN_HBOX:
            if (chrcode == copycode)
                print_esc(S(1213));
            else
                print_esc(S(1212));
            break;
        case UN_VBOX: /*:1108*/
            if (chrcode == copycode)
                print_esc(S(1215));
            else
                print_esc(S(1214));
            break;
            /*1115:*/
        case DISCRETIONARY: /*:1115*/
            if (chrcode == 1)
                print_esc('-');
            else
                print_esc(S(400));
            break;
            /*1143:*/
        case EQ_NO: /*:1143*/
            if (chrcode == 1)
                print_esc(S(1217));
            else
                print_esc(S(1216));
            break;
            /*1157:*/
        case MATH_COMP:
            switch (chrcode) {
                case ordnoad: print_esc(S(405)); break;
                case opnoad: print_esc(S(406)); break;
                case binnoad: print_esc(S(407)); break;
                case relnoad: print_esc(S(408)); break;
                case opennoad: print_esc(S(409)); break;
                case closenoad: print_esc(S(410)); break;
                case punctnoad: print_esc(S(411)); break;
                case innernoad: print_esc(S(412)); break;
                case undernoad: print_esc(S(414)); break;
                default: print_esc(S(413)); break;
            }
            break;
        case LIMIT_SWITCH: /*:1157*/
            if (chrcode == limits)
                print_esc(S(420));
            else if (chrcode == nolimits)
                print_esc(S(421));
            else
                print_esc(S(1218));
            break;
            /*1170:*/
        case MATH_STYLE: /*:1170*/
            printstyle(chrcode);
            break;
            /*1179:*/
        case ABOVE: /*:1179*/
            switch (chrcode) {
                case overcode: print_esc(S(1220)); break;
                case atopcode: print_esc(S(1221)); break;
                case delimitedcode: print_esc(S(1222)); break;
                case delimitedcode + overcode: print_esc(S(1223)); break;
                case delimitedcode + atopcode: print_esc(S(1224)); break;
                default: print_esc(S(1219)); break;
            }
            break;
            /*1189:*/
        case LEFT_RIGHT: /*:1189*/
            if (chrcode == leftnoad)
                print_esc(S(418));
            else
                print_esc(S(419));
            break;
            /*1209:*/
        case PREFIX:
            if (chrcode == 1)
                print_esc(S(959));
            else if (chrcode == 2)
                print_esc(S(961));
            else
                print_esc(S(1225));
            break;
        case DEF: /*:1209*/
            if (chrcode == 0)
                print_esc(S(1226));
            else if (chrcode == 1)
                print_esc(S(1227));
            else if (chrcode == 2)
                print_esc(S(1228));
            else
                print_esc(S(1229));
            break;
            /*1220:*/
        case LET: /*:1220*/
            if (chrcode != NORMAL)
                print_esc(S(1231));
            else
                print_esc(S(1230));
            break;
            /*1223:*/
        case SHORTHAND_DEF:
            switch (chrcode) {
                case chardefcode: print_esc(S(1232)); break;
                case mathchardefcode: print_esc(S(1233)); break;
                case countdefcode: print_esc(S(1234)); break;
                case dimendefcode: print_esc(S(1235)); break;
                case skipdefcode: print_esc(S(1236)); break;
                case muskipdefcode: print_esc(S(1237)); break;
                default: print_esc(S(1238)); break;
            }
            break;
        case CHAR_GIVEN:
            print_esc(S(1114));
            print_hex(chrcode);
            break;
        case MATH_GIVEN:
            print_esc(S(1121));
            print_hex(chrcode);
            break;
            /*:1223*/
            /*1231:*/
        case DEF_CODE:
            if (chrcode == CAT_CODE_BASE)
                print_esc(S(467));
            else if (chrcode == MATH_CODE_BASE)
                print_esc(S(471));
            else if (chrcode == LC_CODE_BASE)
                print_esc(S(468));
            else if (chrcode == UC_CODE_BASE)
                print_esc(S(469));
            else if (chrcode == SF_CODE_BASE)
                print_esc(S(470));
            else
                print_esc(S(473));
            break;
        case DEF_FAMILY: /*:1231*/
            print_size(chrcode - MATH_FONT_BASE);
            break;
            /*1251:*/
        case HYPH_DATA: /*:1251*/
            if (chrcode == 1)
                print_esc(S(774));
            else
                print_esc(S(787));
            break;
            /*1255:*/
        case ASSIGN_FONT_INT: /*:1255*/
            if (chrcode == 0)
                print_esc(S(1239));
            else
                print_esc(S(1240));
            break;
            /*1261:*/
        case SET_FONT:
            print(S(1267));
            slow_print(get_fontname(chrcode));
            if (get_fontsize(chrcode) != get_fontdsize(chrcode)) {
                print(S(642));
                print_scaled(get_fontsize(chrcode));
                print(S(459));
            }
            break;
            /*:1261*/
            /*1263:*/
        case SET_INTERACTION: /*:1263*/
            switch (chrcode) {
                case BATCH_MODE: print_esc(S(281)); break;
                case NON_STOP_MODE: print_esc(S(282)); break;
                case SCROLL_MODE: print_esc(S(283)); break;
                default: print_esc(S(1241)); break;
            }
            break;
            /*1273:*/
        case IN_STREAM: /*:1273*/
            if (chrcode == 0)
                print_esc(S(1243));
            else
                print_esc(S(1242));
            break;
            /*1278:*/
        case MESSAGE: /*:1278*/
            if (chrcode == 0)
                print_esc(S(1244));
            else
                print_esc(S(1245));
            break;
            /*1287:*/
        case CASE_SHIFT: /*:1287*/
            if (chrcode == LC_CODE_BASE)
                print_esc(S(1246));
            else
                print_esc(S(1247));
            break;
            /*1292:*/
        case XRAY: /*:1292*/
            switch (chrcode) {
                case showboxcode: print_esc(S(1249)); break;
                case showthecode: print_esc(S(1250)); break;
                case showlists: print_esc(S(1251)); break;
                default: print_esc(S(1248)); break;
            }
            break;
            /*1295:*/
        case UNDEFINED_CS: print(S(1268)); break;
        case CALL: print(S(1269)); break;
        case LONG_CALL: print_esc(S(1270)); break;
        case OUTER_CALL: print_esc(S(1271)); break;
        case LONG_OUTER_CALL:
            print_esc(S(959));
            print_esc(S(1271));
            break;
        case END_TEMPLATE: /*:1295*/
            print_esc(S(1272));
            break;
            /*1346:*/
        case EXTENSION:
            switch (chrcode) {
                case opennode: print_esc(S(378)); break;
                case writenode: print_esc(S(379)); break;
                case closenode: print_esc(S(380)); break;
                case specialnode: print_esc(S(381)); break;
                case immediatecode: print_esc(S(1252)); break;
                case setlanguagecode: print_esc(S(382)); break;
                default: print(S(1273)); break;
            } /*:1346*/
            break;

        default: print(S(1274)); break;
    } // switch (cmd)
} // #298: printcmdchr
