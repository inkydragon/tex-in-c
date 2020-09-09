#pragma once
#ifndef TEX_FUNC_H
// tex.c 导出的函数
#define TEX_FUNC_H
#include "str.h" // StrNumber


// [tex], fonts, macro.h, printout
extern void print(StrNumber s);

// [tex], fonts, printout, str
extern void print_int(Integer n);

// [tex], fonts, printout
extern void print_esc(StrNumber s);

// [tex], fonts, str
extern void print_char(ASCIICode s); 
extern void println(void);

// [tex], printout
extern void print_hex(Integer n);
extern void print_size(Integer s);
extern void printstyle(Integer c);

// [tex], fonts
extern void print_file_name(StrNumber n, StrNumber a, StrNumber e);
extern void packfilename(StrNumber n, StrNumber a, StrNumber e);


// [tex]
extern void set_help(SChar k, ...);

// [tex] lexer
extern void print_mode(Integer m);
extern void openlogfile(void);

// [tex] expand
extern void startinput(void);
extern void eqdefine(HalfWord p, QuarterWord t, HalfWord e);
extern HalfWord strtoks(StrPoolPtr b);
extern HalfWord thetoks(void);

// [tex] scan
extern void preparemag(void);
extern Pointer newspec(Pointer p);

// [tex], error
extern void debughelp(void);
extern void jumpout(void);
extern void giveerrhelp(void);

// tex, box
extern void printsubsidiarydata(HalfWord p, ASCIICode c);
extern void printdelimiter(HalfWord p);
extern void print_write_whatsit(StrNumber s, Pointer p);
extern void printfamandchar(HalfWord p);

#endif // TEX_FUNC_H