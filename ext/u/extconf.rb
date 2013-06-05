require 'mkmf'
require 'optparse'

have_header 'assert.h'
have_header 'limits.h'
have_header 'langinfo.h'
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

headers = %w'locale.h'
headers << 'xlocale.h' if $xlocale_h
have_type 'locale_t', headers
have_func 'newlocale', headers
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

$warnflags = ''

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
    if result = try_cpp('', opt, &block)
      $CFLAGS += ' ' unless $CFLAGS.empty?
      $CFLAGS += opt
    end
  end
  result
end

try_compiler_option '-std=c99'
try_compiler_option '-finline-functions'
try_compiler_option '-fno-common'
try_compiler_option '-fvisibility=hidden'

def try_warning_option(opt, &block)
  result = false
  checking_for "#{opt} option to compiler" do
    if result = try_cpp('', opt, &block)
      $warnflags += ' ' unless $warnflags.empty?
      $warnflags += opt
    end
  end
  result
end

if $enable_gcc_warnings
  try_compiler_option '-Werror'
  try_warning_option '-Wall'
  try_warning_option '-Waggregate-return'
  try_warning_option '-Wcast-align'
  try_warning_option '-Wextra'
  try_warning_option '-Wformat=2'
  try_warning_option '-Winit-self'
  try_warning_option '-Winline'
  try_warning_option '-Wmissing-declarations'
  try_warning_option '-Wmissing-format-attribute'
  try_warning_option '-Wmissing-include-dirs'
  try_warning_option '-Wmissing-noreturn'
  try_warning_option '-Wmissing-prototypes'
  try_warning_option '-Wnested-externs'
  try_warning_option '-Wold-style-definition'
  try_warning_option '-Wpacked'
  try_warning_option '-Wp,-D_FORTIFY_SOURCE=2'
  try_warning_option '-Wpointer-arith'
  try_warning_option '-Wsign-compare'
  try_warning_option '-Wstrict-aliasing=2'
#  try_warning_option '-Wsuggest-attribute=const'
  try_warning_option '-Wsuggest-attribute=noreturn'
#  try_warning_option '-Wsuggest-attribute=pure'
  try_warning_option '-Wundef'
  try_warning_option '-Wunsafe-loop-optimizations'
  try_warning_option '-Wwrite-strings'
  try_warning_option '-Wshorten-64-to-32' unless RUBY_VERSION < '1.9'
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
