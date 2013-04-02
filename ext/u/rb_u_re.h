#ifdef HAVE_RUBY_RE_H
#  include <ruby/re.h>
#else
#  include <re.h>
#endif


#ifdef HAVE_BROKEN_RMATCH_REGS
#  undef RMATCH_REGS
#  define RMATCH_REGS(obj) ((R_CAST(RMatch)(obj))->regs)
#endif


HIDDEN VALUE rb_u_pattern_argument(VALUE pattern, bool quote);
HIDDEN VALUE rb_u_pattern_match_reference(VALUE reference);
