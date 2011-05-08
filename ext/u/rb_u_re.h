#ifndef RB_U_RE_H
#define RB_U_RE_H


#include <re.h>


#ifdef HAVE_BROKEN_RMATCH_REGS
#  undef RMATCH_REGS
#  define RMATCH_REGS(obj) ((R_CAST(RMatch)(obj))->regs)
#endif


VALUE rb_u_pattern_argument(VALUE pattern, bool quote) HIDDEN;
VALUE rb_u_pattern_match_reference(VALUE reference) HIDDEN;


#endif
