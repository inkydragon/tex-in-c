#pragma once
#ifndef INC_BOX_H
/// [133] Data structures for boxes and their friends.
#define INC_BOX_H

/** @addtogroup S133x161_P50x57
 * @{
 */
// PART 10: DATA STRUCTURES FOR BOXES AND THEIR FRIENDS

/// [p50#133] identifies what kind of node this is.
#define type(x)     (mem[(x)].hh.UU.U2.b0)
/// [p50#133] secondary identification in some cases.
#define subtype(x)  (mem[(x)].hh.UU.U2.b1)

/// [p50#134] does the argument point to a char node?
#define ischarnode(x)   ((x) >= hi_mem_min)
/// [50#134] the character code in a `charnode`.
#define character(x)    subtype(x)

#ifdef BIG_CHARNODE
/// [50#134] the font code in a `charnode`.
#define font(x)         link(x + 1)
/* #define font(x)	info(x+1) */

#else
#define font(x)         type(x)
#endif // #ifdef BIG_CHARNODE

/// [p51#135] number of words to allocate for a box node.
#define boxnodesize     7
/// [p51#135] position of width field in a box node.
#define widthoffset     1
/// [p51#135] position of depth field in a box node.
#define depthoffset     2
/// [p51#135] position of height field in a box node.
#define heightoffset    3

/// [p51#135] width of the box, in sp.
#define width(x)        mem[x + widthoffset].sc
/// [p51#135] depth of the box, in sp.
#define depth(x)        mem[x + depthoffset].sc
/// [p51#135] height of the box, in sp.
#define height(x)       mem[x + heightoffset].sc
/// [p51#135] repositioning distance, in sp.

#define shiftamount(x)  mem[x + 4].sc
/// [p51#135] position of list ptr field in a box node.
#define listoffset      5
/// [p51#135] beginning of the list inside the box.
#define listptr(x)      link(x + listoffset)
/// [p51#135] applicable order of INFINITY.
#define glueorder(x)    subtype(x + listoffset)
/// [p51#135] stretching or shrinking.
#define gluesign(x)     type(x + listoffset)

/// [p51#135] the most common case when several cases are named.
#define NORMAL      0
/// [p51#135] glue setting applies to the stretch components.
#define stretching  1
/// [p51#135] glue setting applies to the shrink components.
#define shrinking   2
/// [p51#135]  position of #glueset in a box node.
#define glueoffset  6
/// [p51#135] a word of type |glueratio| for glue setting.
#define glueset(x)  mem[x + glueoffset].gr

/// [p51#138] tests for a running dimension.
#define isrunning(x)    ((x) == nullflag)

/// [p52#140] the |floatingpenalty| to be used.
#define floatcost(x)    mem[x + 1].int_
/// [p52#140] the vertical list to be inserted.
#define insptr(x)       info(x + 4)
/// [p52#140] the |splittopskip| to be used.
#define splittopptr(x)  link(x + 4)

/// [p52#141] head of the token list for a mark.
#define markptr(x)      mem[x + 1].int_

/// [p52#142] vertical list to be moved out of horizontal list.
#define adjustptr       markptr

/// [p52#143] the word where the ligature is to be found.
#define ligchar(x)      ((x) + 1)
/// [p52#143] the list of characters.
#define ligptr(x)       link(ligchar(x))

/// [p53#145] how many subsequent nodes to replace.
#define replacecount    subtype 
/// [p53#145] text that precedes a discretionary break.
#define prebreak        llink   
/// [p53#145] text that follows a discretionary break.
#define postbreak       rlink

/// [p54#148] 
#define precedesbreak(x)    (type(x) < MATH_NODE)
/// [p54#148] 
#define nondiscardable(x)   (type(x) < MATH_NODE)

/// [p54#149] pointer to a glue specification.
#define glueptr     llink   
/// [p54#149] pointer to box or rule node for leaders.
#define leaderptr   rlink 

/// [p55#150] reference count of a glue specification.
#define gluerefcount(x)     link(x)  
/// [p55#150] the stretchability of this glob of glue.
#define stretch(x)          mem[x + 2].sc 
/// [p55#150] the shrinkability of this glob of glue.
#define shrink(x)           mem[x + 3].sc   
/// [p55#150] order of INFINITY for stretching.
#define stretchorder(x)     type(x)   
/// [p55#150] order of INFINITY for shrinking.
#define shrinkorder(x)      subtype(x) 

/// [p56#157] the added cost of breaking a list here.
#define penalty(x)      mem[x + 1].int_ 

/// [p57#159] total stretch in an unset node.
#define gluestretch(x)  mem[x + glueoffset].sc    
/// [p57#159] total shrink in an unset node.
#define glueshrink      shiftamount 
/// [p57#159] indicates the number of spanned columns.
#define spancount       subtype



/** @} end group S133x161_P50x57 */

// tex, scan
extern Pointer newnullbox(void);
extern Pointer newrule(void);
extern Pointer newligature(QuarterWord f, QuarterWord c, Pointer q);
extern Pointer newligitem(QuarterWord c);
extern Pointer newdisc(void);
extern Pointer newmath(long w, SmallNumber s);
extern Pointer newspec(Pointer p);
extern Pointer newparamglue(SmallNumber n);
extern Pointer newglue(Pointer q);
extern Pointer newskipparam(SmallNumber n);
extern Pointer newkern(long w);
extern Pointer newpenalty(long m);

#endif /* INC_BOX_H */