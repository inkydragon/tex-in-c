#include <stdio.h>  // FILE
#include <string.h> // memcpy, strlen, strcpy, strchr, strcmp, strcat, strncmp 
#include <stdlib.h> // malloc, exit, getenv,
#include <time.h>   // tm_struct, time, localtime
#include "tex.h"    // [macro] BUF_SIZE, FILE_NAME_SIZE
#include "str.h"    // [type] StrNumber
#include "funcs.h"  // [export]
#include "global.h" // [var] buffer, last, first, name_of_file

static char my_buff[256];

static int pos = 0; 
static Boolean in_c_flag = false;
Boolean need_to_load_format = false;

#define MY_BUFSIZE 512
static char mybuff[MY_BUFSIZE];

// static char name_buf[MY_BUFSIZE]; // _not_use_
// static int nlen; // _not_use_
static Boolean use_independence_date = false;


void fix_date_and_time(long* tex_time_p,
                    long* day_p,
                    long* month_p,
                    long* year_p) {
    if (use_independence_date) {
        *year_p = 1776;
        *month_p = 7;
        *day_p = 4;
        *tex_time_p = 12 * 60;
    } else {
        time_t pt = time(0);
        struct tm* tm_struct = localtime(&pt);
        /* Correct effect of the brain-demaged defintion */
        *year_p = tm_struct->tm_year + 1900;
        *month_p = tm_struct->tm_mon + 1;
        *day_p = tm_struct->tm_mday;
        *tex_time_p = 60 * tm_struct->tm_hour + tm_struct->tm_min;
    }
}

// _not_use_
// void beginname(void) {
//     nlen = 0;
//     name_buf[0] = 0;
// }

// _not_use_
// Boolean morename(int c) {
//     if (c == ' ') return 0;
//     if (nlen + 1 < MY_BUFSIZE) {
//         name_buf[nlen] = c;
//         name_buf[nlen + 1] = 0;
//     }
//     return 1;
// }

// void endname(void) {} // _not_use_

static char* format_name;

static char** font_path;
static char* font_path_buf;
static char** input_path;
static char* input_path_buf;
static char** format_path;
static char* format_path_buf;

static char* font_path_default[] = {
    "/usr/share/texmf/fonts/tfm/public/cm/",
    "/usr/share/texmf/fonts/tfm/public/latex/",
    "/usr/share/texmf/fonts/tfm/public/ae/",
    "/usr/share/texmf/fonts/tfm/public/cmextra/",
    "/usr/share/texmf/fonts/tfm/public/mflogo",
    "/usr/share/texmf/fonts/tfm/public/misc/",
    "/usr/share/texmf/fonts/tfm/ams/cmextra/",
    "/usr/share/texmf/fonts/tfm/ams/cyrillic/",
    "/usr/share/texmf/fonts/tfm/ams/euler/",
    "/usr/share/texmf/fonts/tfm/ams/symbols/",
    "/var/lib/texmf/tfm/public/plfonts/",
    "/var/lib/texmf/tfm/jknappen/ec/",
    "",
    0};

char* p_path[] = {"", 0};

Boolean initinc(int _not_use_) {
    if (in_c_flag) {
        last = first;
        memcpy(&(buffer[first]), mybuff, pos);
        last += pos;
        return true;
    } else {
        return false;
    }
}

static void env_to_path(char*** path, char** buf, char* env_var) {
    char** my_path;
    char* my_path_buf;
    char* pp;
    int k;
    int i = strlen(env_var);
    my_path_buf = (char*)malloc(i + 1);
    my_path = (char**)malloc(sizeof(char*) * (i + 2));
    if (!my_path_buf || !my_path) {
        fprintf(stderr, "Out of memory\n");
        exit(11);
    }
    strcpy(my_path_buf, env_var);
    my_path[0] = pp = my_path_buf;
    k = 1;
    while ((pp = strchr(pp, ':'))) {
        *pp = 0;
        pp++;
        my_path[k++] = pp;
    }
    my_path[k] = 0;
    *path = my_path;
    *buf = my_path_buf;
}

int PASCAL_MAIN(int argc, char** argv) {
    char* pom;
    printf("%s\n", argv[0]);
    if ((pom = getenv("TEXINPUTS"))) {
        env_to_path(&input_path, &input_path_buf, pom);
    } else {
        input_path = p_path;
    }
    if ((pom = getenv("TEXFONTS"))) {
        env_to_path(&font_path, &font_path_buf, pom);
    } else {
        font_path = font_path_default;
    }
    if ((pom = getenv("TEXFORMATS"))) {
        env_to_path(&format_path, &format_path_buf, pom);
    } else {
        format_path = p_path;
    }
    if (argc > 1 && !strcmp(argv[1], "--indep")) {
        use_independence_date = true;
        argv++;
        argc--;
    }
    if (argc > 1) {
        if (argv[1][0] == '&') {
            need_to_load_format = true;
            format_name = &(argv[1][1]);
            argv++;
            argc--;
        }
    }
    if (argc <= 1) {
        in_c_flag = false;
    } else {
        int j = 1;
        pos = 0;
        for (; j < argc; j++) {
            if (strlen(argv[j]) + pos + 3 < BUF_SIZE) {
                strcpy(&(mybuff[pos]), argv[j]);
                pos += strlen(argv[j]);
                mybuff[pos++] = ' ';
            }
        }
        pos--;
        if (pos > 0) {
            in_c_flag = true;
        }
    }
    return 0;
}

static Boolean a_open_in1(char* name, char** path_lst, FILE** f);

Boolean open_fmt(FILE** fmt) {
    char* fmt_name;
    char name_buf[256] = "plain.fmt";
    fmt_name = format_name;
    printf("%s\n", format_name);
    if (!strchr(format_name, '.')) {
        if (strlen(format_name) + strlen(".fmt") < 255) {
            strcpy(name_buf, format_name);
            strcat(name_buf, ".fmt");
            fmt_name = name_buf;
        }
    }
    if (a_open_in1(fmt_name, format_path, fmt)) {
        return true;
    } else {
        fprintf(stdout, "Sorry, I can't find that format; will try PLAIN.\n");
        if (a_open_in1("plain.fmt", format_path, fmt)) {
            return true;
        } else {
            fprintf(stdout, "I can't find the PLAIN format file!\n");
            return false;
        }
    }
}

static void trimspaces(void) {
    char* pp;
    memcpy(my_buff, name_of_file, FILE_NAME_SIZE);
    my_buff[FILE_NAME_SIZE] = 0;
    my_buff[(pp = strchr(my_buff, ' ')) ? pp - my_buff : FILE_NAME_SIZE] = 0;
    fprintf(stderr, "%s", my_buff);
}

static Boolean a_open_in1(char* name, char** path_lst, FILE** f) {
    /* XXXX Fixed buffer size */
    char path_buff[512];
    char* path_dir;
    int ln = strlen(name);
    for (path_dir = *path_lst++; path_dir; path_dir = *path_lst++) {
        int lp = strlen(path_dir);
        if (lp > 512 - 2 - ln) break;
        strcpy(path_buff, path_dir);
        if (lp > 0 && path_buff[lp - 1] != '/') {
            path_buff[lp] = '/';
            path_buff[lp + 1] = 0;
        }
        strcat(path_buff, name);
        if (!*f)
            *f = fopen(path_buff, "rb");
        else
            *f = freopen(path_buff, "rb", *f);
        if (*f) return 1;
    }
    return *f != 0;
}

Boolean a_open_in(FILE** f) {
    char** path_lst;
    char* name;
    trimspaces();
    if (!strncmp(my_buff, "TeXfonts:", strlen("TeXfonts:"))) {
        name = my_buff + strlen("TeXfonts:");
        path_lst = font_path;
    } else if (!strncmp(my_buff, "TeXinputs:", strlen("TeXinputs:"))) {
        name = my_buff + strlen("TeXinputs:");
        path_lst = input_path;
    } else if (!strncmp(my_buff, "TeXformats:", strlen("TeXformats:"))) {
        name = my_buff + strlen("TeXformats:");
        path_lst = format_path;
    } else {
        name = my_buff;
        path_lst = p_path;
    }
    return a_open_in1(name, path_lst, f);
}

Boolean a_open_out(FILE** f) {
    trimspaces();
    if (!*f) {
        *f = fopen(my_buff, "wb");
    } else {
        *f = freopen(my_buff, "wb", *f);
    }
    return *f != 0;
}