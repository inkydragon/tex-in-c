#pragma once
#ifndef MACROS_H
/// 全局常用的宏
#define MACROS_H

// fonts, str, tex
#define pget(x) fread(&x, 8, 1, fmtfile)
#define pput(x) fwrite(&x, 8, 1, fmtfile)

// fonts, tex

/// a |halfword| code that can't match a real character}
#define NON_CHAR 256

/// [p199#545]
#define opbyte(x) (x.b2)
#define rembyte(x) (x.b3)

/// [p203#554]
#define chartag(x) (((x).b2) % 4)
#define charexists(x) ((x).b0 > MIN_QUARTER_WORD)

#endif // #ifndef MACROS_H