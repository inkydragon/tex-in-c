#include <string.h> // [func] memcpy
#include "tex_constant.h" // [const] TEX_BANNER
#include "charset.h" // [var] xord, xchr
#include "str.h"
#include "print.h"  // [type] Selector [var] selector
#include "eqtb.h"   // [var] day, month, year, tex_time
#include "expand.h" // [func] get_x_token
#include "error.h"  // [func] print_err [var] interaction
#include "lexer.h"  // [macro] end_line_char_inactive
#include "dump.h"   // [var] format_ident
#include "scan.h"   // [func] skip_spaces
#include "io.h"


/** @addtogroup S511x538_P188x195
 * @{
 */
/// [#512] name of file just scanned.
StrNumber cur_name;
/// [#512] file area just scanned, or "".
StrNumber cur_area;
/// [#512] file extension just scanned, or "".
StrNumber cur_ext;

/// [#513] the most recent ‘>’ or ‘:’, if any.
StrNumber area_delimiter;
/// [#513] the relevant ‘.’, if any.
StrNumber ext_delimiter;

/// [#520] _not_use_
Char TEX_format_default[FORMAT_DEFAULT_LENGTH];

/// [#527] is a file name being scanned?
/// xref: scan_file_name, newfont, expand
Boolean name_in_progress;
/// [#527] principal file name.
/// contains the file name that was first `\\input` by the user.
/// This name is extended by `.log` and `.dvi` and `.fmt`
///     in the names of TEX’s output files.
StrNumber job_name;
/// [#527] has the transcript file been opened?
Boolean log_opened;

/// [#532] full name of the output file.
StrNumber output_file_name;
/// [#532] full name of the log file.
StrNumber log_name;


/// [ #511. File names. ] 

/// [#521]
void fname_init() {
    memcpy(TEX_format_default, "TeXformats:plain.fmt", FORMAT_DEFAULT_LENGTH);
}

/// [#515]
void begin_name(void) {
    area_delimiter = 0;
    ext_delimiter = 0;
}

/// [#516]
Boolean more_name(ASCIICode c) {
    if (c == ' ') {
        return false;
    } else {
        str_room(1);
        append_char(c); // contribute c to the current string
        if (c == '.' || c == ':') {
            area_delimiter = makestring();
            ext_delimiter = 0;
        } else if (c == '.' && ext_delimiter == 0) {
            ext_delimiter = makestring();
        }
        return true;
    }
} /* more_name */

/// [#517]
void end_name(void) {
    if (area_delimiter == 0) {
        cur_area = S(385); // ""
    } else {
        /// TODO: check
    }
    
    if (ext_delimiter == 0) {
        cur_ext = S(385); // ""
        cur_name = makestring();
    } else {
        cur_name = ext_delimiter;
        cur_ext = makestring();
    }
} /* end_name */

/// [#518]
void print_file_name(StrNumber n, StrNumber a, StrNumber e) {
    slow_print(a);
    slow_print(n);
    slow_print(e);
} // #518: print_file_name


Static Integer _tmp_fname_len;
/// [#519]
void append_to_name(ASCIICode x) {
    _tmp_fname_len++;
    if (_tmp_fname_len <= FILE_NAME_SIZE) {
        name_of_file[_tmp_fname_len - 1] = xchr[x];
    }
}

/// [#519] 打包文件名.
/// @param[in] fname    文件名
/// @param[in] prefix   前缀
/// @param[in] ext      后缀
void pack_file_name(StrNumber fname, StrNumber prefix, StrNumber ext) {
    Integer k;

    k = 0;
    _tmp_fname_len = 0;
    /// TODO: 让 str_map 返回打印的字符个数。消除 _tmp_fname_len
    str_map(prefix, append_to_name);
    str_map(fname, append_to_name);
    str_map(ext, append_to_name);

    k = _tmp_fname_len;
    if (k <= FILE_NAME_SIZE) {
        namelength = k;
    } else {
        namelength = FILE_NAME_SIZE;
    }

    /// MOD: 直接中止字符串
    name_of_file[k] = '\0';
    // for (k = namelength; k < FILE_NAME_SIZE; k++) {
    //     name_of_file[k] = ' ';
    // }
} /* [#519] pack_file_name */

/// [#525]
Static StrNumber make_name_string() {
    for (int k = 0; k < namelength; k++) {
        append_char(xord[name_of_file[k]]);
    }
    return makestring();
} /* make_name_string */
StrNumber a_make_name_string() { return make_name_string(); }
StrNumber b_make_name_string() { return make_name_string(); }
StrNumber w_make_name_string() { return make_name_string(); }

/// [#526]
void scan_file_name(void) {
    name_in_progress = true;
    begin_name();
    skip_spaces();
    while (true) {
        if (curcmd > OTHER_CHAR || curchr > 255) {
            backinput();
            break;
        }
        if (!more_name(curchr)) break;
        get_x_token();
    }
    end_name();
    name_in_progress = false;
}


/// [#529] s = ".log" , ".dvi" , or format extension.
void pack_job_name(StrNumber s) {
    cur_area = S(385); // ""
    cur_ext = s;
    cur_name = job_name;
    pack_file_name(cur_name, cur_area, cur_ext);
}

/// [#530]
void prompt_file_name(StrNumber s, StrNumber e) {
    short k; ///< index into buffer.

    if (s == S(665)) { // "input file name"
        print_err(S(666)); // "I can't find file `"
    } else {
        print_err(S(667)); // "I can't write on file `"
    }

    print_file_name(cur_name, cur_area, cur_ext);
    print(S(668)); // "'."

    // ".tex"
    if (e == S(669)) showcontext();
    printnl(S(670)); // "Please type another "
    print(s);

    // "*** (job aborted file error in nonstop mode)"
    if (interaction < SCROLL_MODE) fatalerror(S(671));
    clear_terminal();
    print(S(488)); // ": "
    term_input();

    /// [#531] Scan file name in the buffer.
    begin_name();
    k = first;
    while (buffer[k] == ' ' && k < last) k++;

    while (true) {
        if (k == last) break;
        if (!more_name(buffer[k])) break;
        k++;
    }
    end_name();

    // ""
    if (cur_ext == S(385)) cur_ext = e;
    pack_file_name(cur_name, cur_area, cur_ext);
} /* [#530] prompt_file_name */

/// [#534]
void open_log_file(void) {
    Selector old_setting;
    short k;
    short l;
    Char months[36];
    short FORLIM;

    old_setting = selector;
    if (job_name == 0) job_name = S(672); // "texput"
    pack_job_name(S(673)); // ".log"
    while (!a_open_out(&log_file)) { /*535:*/
        selector = TERM_ONLY;
        // "transcript file name" ".log"
        prompt_file_name(S(674), S(673));
    }
    /*:535*/
    log_name = a_make_name_string();
    selector = LOG_ONLY;
    log_opened = true;

    /*536:*/
    fprintf(log_file, "%s", TEX_BANNER);
    slow_print(format_ident);
    print(S(675)); // "  "
    print_int(day);
    print_char(' ');
    memcpy(months, "JANFEBMARAPRMAYJUNJULAUGSEPOCTNOVDEC", 36);
    FORLIM = month * 3;
    for (k = month * 3 - 3; k < FORLIM; k++) {
        fwrite(&months[k], 1, 1, log_file);
    }
    print_char(' ');
    print_int(year);
    print_char(' ');
    print_two(tex_time / 60);
    print_char(':');
    print_two(tex_time % 60); /*:536*/
    inputstack[inputptr] = cur_input;

    printnl(S(676)); // "**"
    l = inputstack[0].limitfield;
    if (buffer[l] == end_line_char) l--;
    for (k = 1; k <= l; k++) {
        print(buffer[k]);
    }
    println();

    selector = old_setting + 2;
}

/// [#p195#537] TeX will \\input something.
void start_input(void) {
    scan_file_name(); //  set cur_name to desired file name

    //            ""               ".tex"
    if (cur_ext == S(385)) cur_ext = S(669);
    pack_file_name(cur_name, cur_area, cur_ext);

    while (true) {
        // set up cur_file and new level of input
        beginfilereading();
        if (a_open_in(&curfile)) break;
        if (cur_area == S(385)) { // ""
            // 
            pack_file_name(cur_name, S(677), cur_ext);
            if (a_open_in(&curfile)) break;
        }
        // remove the level that didn’t work
        endfilereading();
        //             "input file name" ".tex"
        prompt_file_name(S(665), S(669));
    } // end inf loop

    NAME = a_make_name_string();
    if (job_name == 0) {
        job_name = cur_name;
        open_log_file();
    }

    newline_or_space(str_length(NAME));

    print_char('(');
    openparens++;
    slow_print(NAME);
    update_terminal();
    STATE = NEW_LINE;

#if 0
    if (NAME == str_ptr - 1) {
        flush_string();
        NAME = cur_name;
    }
#else
    NAME = cur_name;
#endif

    /** [#538] Read the first line of the new file. */
    line = 1;
    inputln(curfile, false);
    firm_up_the_line();
    if (end_line_char_inactive) {
        LIMIT--;
    } else {
        buffer[LIMIT] = end_line_char;
    }
    first = LIMIT + 1;
    LOC = START;
} /* start_input*/

/** @}*/ // end group S511x538_P188x195