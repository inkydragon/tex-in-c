#pragma once
#ifndef FONTS_H
#define FONTS_H
#include <stdio.h> // FILE

// [fonts], dviout, tex
typedef unsigned short InternalFontNumber;
extern InternalFontNumber fontptr;
extern Boolean fontused[fontmax + 1];

// [fonts], dviout, printout, tex
extern Scaled get_fontsize(InternalFontNumber x);
extern Scaled get_fontdsize(InternalFontNumber x);
extern StrNumber get_fontname(InternalFontNumber x);

// [fonts], tex
typedef int FontIndex;
extern FourQuarters charinfo(InternalFontNumber f, EightBits p);
extern Scaled charwidth(InternalFontNumber x, FourQuarters y);
extern Scaled charitalic(InternalFontNumber x, FourQuarters y);
extern Scaled charheight(InternalFontNumber x, int y);
extern Scaled chardepth(InternalFontNumber x, int y);
extern Scaled charkern(InternalFontNumber x, FourQuarters y);
extern FourQuarters get_fontcheck(InternalFontNumber x);
extern void fonts_init(void);
extern InternalFontNumber
readfontinfo(HalfWord u, StrNumber nom, StrNumber aire, long s);
extern int fonts_undump(FILE* fmtfile, FILE* _not_use_);
extern void fonts_dump(FILE* fmtfile);
extern long get_hyphenchar(InternalFontNumber x); // texmac.h
extern void set_hyphenchar(InternalFontNumber x, long c);
extern long get_skewchar(InternalFontNumber x);
extern void set_skewchar(InternalFontNumber x, long c);

extern FontIndex fmemptr;
extern MemoryWord fontinfo[fontmemsize + 1];
extern FontIndex fontparams[fontmax + 1];
extern EightBits fontbc[fontmax + 1];
extern EightBits fontec[fontmax + 1];
extern Pointer fontglue[fontmax + 1];
extern FontIndex bcharlabel[fontmax + 1];
extern long fontbchar[fontmax + 1];
extern long fontfalsebchar[fontmax + 1];
extern long ligkernbase[fontmax + 1]; // texmac
extern long extenbase[fontmax + 1];
extern long parambase[fontmax + 1];

// [tex], fonts
extern StrNumber fontidtext(InternalFontNumber x);

#endif // #ifndef FONTS_H