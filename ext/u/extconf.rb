require 'mkmf'

def try_compiler_option(opt, &block)
  checking_for "#{opt} option to compiler" do
    $CFLAGS += " #{opt}" if try_compile '', opt, &block
  end
end

try_compiler_option '-std=c99'
try_compiler_option '-finline-functions'
try_compiler_option '-fno-common'
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
try_compiler_option '-Wswitch-default'
try_compiler_option '-Wswitch-enum'
try_compiler_option '-Wundef'
try_compiler_option '-Wunsafe-loop-optimizations'
try_compiler_option '-Wwrite-strings'

checking_for 'GNUC visibility attribute' do
  $defs.push('-DHAVE_GNUC_VISIBILITY') if try_compile <<EOC, '-Werror'
void f_hidden(void);
void __attribute__((visibility("hidden")))
f_hidden(void)
{
}
int main(void)
{
  f_hidden();
  return 0;
}
EOC
end

have_header 'assert.h'
have_header 'limits.h'
have_header 'locale.h'
have_header 'stdbool.h'
have_header 'stddef.h'
have_header 'stdint.h'
have_header 'stdio.h'
have_header 'stdlib.h'
have_header 'string.h'
have_header 'sys/types.h'
have_header 'wchar.h'

have_func 'rb_long2int', 'ruby.h'
have_func 'rb_hash_lookup2', 'ruby.h'
# TODO: Do we need to include encoding.h?
have_func 'rb_intern3', 'ruby.h'
have_func 'rb_reg_backref_number', 'ruby.h'
have_func 'rb_memhash', 'ruby.h'
# TODO: Do we need to include encoding.h?
have_func 'rb_utf8_encoding', 'ruby.h'
checking_for 'number of arguments to rb_reg_regsub' do
  $defs.push '-DHAVE_RB_REG_REGSUB4' if try_compile <<EOC
#include <ruby.h>
#include <re.h>
int
main(void)
{
    rb_reg_regsub(Qnil, Qnil, NULL, Qnil);
    return 0;
}
EOC
end

have_var 'rb_eKeyError', 'ruby.h'

$INSTALLFILES ||= []
$INSTALLFILES << ['u.h', '$(RUBYARCHDIR)', 'lib']

create_header
create_makefile 'u/u'
File.open('Makefile', 'ab') do |f|
  f.puts <<EOF
Makefile: extconf.rb depend
	ruby $<

TAGS: $(SRCS)
	ctags -f $@ -I UNUSED,HIDDEN,_ $^

tags: TAGS

.PHONY: tags
EOF
end
