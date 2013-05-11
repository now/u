require 'mkmf'
require 'optparse'

$CFLAGS = $CFLAGS.sub('$(cflags) ', '')

have_header 'assert.h'
have_header 'limits.h'
have_header 'locale.h'
have_header 'stdarg.h'
have_header 'stdbool.h'
have_header 'stddef.h'
have_header 'stdint.h'
have_header 'stdio.h'
have_header 'stdlib.h'
have_header 'string.h'
have_header 'sys/types.h'
have_header 'locale.h'
$xlocale_h = have_header('xlocale.h')

checking_for 'broken RMATCH_REGS' do
  $defs.push '-DHAVE_BROKEN_RMATCH_REGS' unless try_compile <<EOC
#include <ruby.h>
#ifdef HAVE_RUBY_RE_H
#  include <ruby/re.h>
#else
#  include <re.h>
#endif
int
main(void)
{
        struct re_registers *registers = RMATCH_REGS(Qnil);
        struct re_registers *registers2 = registers;
        registers = registers2;
        return 0;
}
EOC
end

$defs.push '-D__USE_XOPEN2K'
$defs.push '-D__USE_XOPEN2K8'

headers = []
headers << 'xlocale.h' if $xlocale_h
have_func 'strcoll_l', headers
have_func 'strxfrm_l', headers

checking_for 'nl_langinfo and CODESET' do
  $defs.push '-DHAVE_NL_LANGINFO_CODESET' if try_compile <<EOC
#include <langinfo.h>
int
main(void)
{
        char *cs = nl_langinfo(CODESET);
        return 0;
}
EOC
end
have_func 'nl_langinfo_l', %w'langinfo.h' + headers
have_library 'iconv', 'iconv', 'iconv.h'
have_func 'iconv', 'iconv.h'

have_func 'rb_errinfo', 'ruby.h'
have_func 'rb_long2int', 'ruby.h'
have_func 'rb_hash_lookup2', 'ruby.h'
have_func 'rb_reg_backref_number', 'ruby.h'
have_func 'rb_memhash', 'ruby.h'
checking_for 'number of arguments to rb_reg_regsub' do
  $defs.push '-DHAVE_RB_REG_REGSUB4' if try_compile <<EOC
#include <ruby.h>
#ifdef HAVE_RUBY_RE_H
#  include <ruby/re.h>
#else
#  include <re.h>
#endif
int
main(void)
{
    rb_reg_regsub(Qnil, Qnil, NULL, Qnil);
    return 0;
}
EOC
end
have_func 'rb_vsprintf', 'ruby.h'

have_var 'rb_eKeyError', 'ruby.h'

$enable_gcc_warnings = false
OptionParser.new{ |opts|
  opts.banner = 'Usage: ruby extconf.rb [OPTION]...'

  opts.on '--enable-gcc-warnings', 'turn on lots of GCC warnings' do
    $enable_gcc_warnings = true
  end

  opts.on '--disable-gcc-warnings', 'turn off lots of GCC warnings' do
    $enable_gcc_warnings = false
  end
}.parse!

def try_compiler_option(opt, &block)
  result = false
  checking_for "#{opt} option to compiler" do
    $CFLAGS += " #{opt}" if result = try_cpp('', opt, &block)
  end
  result
end

try_compiler_option '-std=c99'
try_compiler_option '-finline-functions'
try_compiler_option '-fno-common'
try_compiler_option '-fvisibility=hidden'

if $enable_gcc_warnings
  try_compiler_option '-Werror'
  try_compiler_option '-Wall'
  try_compiler_option '-Waggregate-return'
  try_compiler_option '-Wcast-align'
  try_compiler_option '-Wextra'
  try_compiler_option '-Wformat=2'
  try_compiler_option '-Winit-self'
  try_compiler_option '-Winline'
  try_compiler_option '-Wmissing-declarations'
  try_compiler_option '-Wmissing-format-attribute'
  try_compiler_option '-Wmissing-include-dirs'
  try_compiler_option '-Wmissing-noreturn'
  try_compiler_option '-Wmissing-prototypes'
  try_compiler_option '-Wnested-externs'
  try_compiler_option '-Wold-style-definition'
  try_compiler_option '-Wpacked'
  try_compiler_option '-Wp,-D_FORTIFY_SOURCE=2'
  try_compiler_option '-Wpointer-arith'
  try_compiler_option '-Wsign-compare'
  try_compiler_option '-Wstrict-aliasing=2'
#  try_compiler_option '-Wsuggest-attribute=const'
  try_compiler_option '-Wsuggest-attribute=noreturn'
#  try_compiler_option '-Wsuggest-attribute=pure'
  try_compiler_option '-Wundef'
  try_compiler_option '-Wunsafe-loop-optimizations'
  try_compiler_option '-Wwrite-strings'
  try_compiler_option '-Wshorten-64-to-32'
end

$defs.push '-DU_COMPILATION'

create_header
create_makefile 'u/u'
File.open('Makefile', 'ab') do |f|
  f.puts <<EOF
TAGS: $(SRCS)
	ctags -f $@ -I UNUSED,HIDDEN,_ $^

tags: TAGS

.PHONY: tags

DISTCLEANFILES += TAGS
EOF
end

puts File.open('mkmf.log', 'rb', &:read)
