#include <stdio.h>  // FILE, EOF, stderr
#include "tex.h"    // [type] Boolean, [macro] true, false, bufsize
#include "global.h"
    // [var] buffer, last, first, maxbufstack
    //  _JLfinalend, formatident, curinput, xord
#include "texfunc.h" // [func] overflow
#include "inputln.h" // [export] inputln


Boolean inputln(FILE* f, Boolean bypasseoln) {
    short lastnonblank;
    if (bypasseoln) {
        int c = getc(f);
        if (c != '\n') ungetc(c, f);
    }
    last = first;
    {
        int c = getc(f);
        if (c == EOF) return false;
        ungetc(c, f);
    }
    {
        int inp_c;
        lastnonblank = first;
        while ((inp_c = getc(f)) != EOF && inp_c != '\n') {
            if (last >= maxbufstack) {
                maxbufstack = last + 1;
                if (maxbufstack == bufsize) { /*35:*/
                    if (formatident == 0) {
                        fprintf(stderr, "Buffer size exceeded!\n");
                        longjmp(_JLfinalend, 1);
                    } else { /*:35*/
                        curinput.locfield = first;
                        curinput.limitfield = last - 1;
                        overflow(S(511), bufsize);
                    }
                }
            }
            buffer[last] = xord[inp_c];
            last++;
            if (buffer[last - 1] != 32) lastnonblank = last;
        }
        ungetc(inp_c, f);
        last = lastnonblank;
        return true;
    }
}
