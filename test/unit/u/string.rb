# -*- coding: utf-8 -*-

Expectations do
  expect nil do ''.u[0, -2] end
  expect nil do ''.u[0, -1] end

  expect ''.u do ''.u[0, 0] end
  expect ''.u do ''.u[0, 1] end
  expect ''.u do ''.u[0, 2] end

  expect nil do ''.u[-1, -2] end
  expect nil do ''.u[-1, -1] end
  expect nil do ''.u[-1, 0] end
  expect nil do ''.u[-1, 1] end
  expect nil do ''.u[-1, 2] end
  expect nil do ''.u[1, -2] end
  expect nil do ''.u[1, -1] end
  expect nil do ''.u[1, 0] end
  expect nil do ''.u[1, 1] end
  expect nil do ''.u[1, 2] end

  expect nil do ''.u[0] end

  expect 'h'.u do 'hëllö'.u[0] end
  expect 'ö'.u do 'hëllö'.u[-1] end
  expect nil do 'hëllö'.u[5] end
  expect nil do 'hëllö'.u[-6] end

  expect 'hë'.u do 'hëllö'.u[0, 2] end
  expect 'lö'.u do 'hëllö'.u[-2, 2] end
  expect 'lö'.u do 'hëllö'.u[3, 2] end

  expect 'hël'.u do 'hëllö'.u[0..2] end
  expect 'hël'.u do 'hëllö'.u[0...3] end
  expect 'lö'.u do 'hëllö'.u[-2..-1] end

  expect 'hë'.u do 'hëllö'.u[/\Ah./u] end
  expect 'lö'.u do 'hëllö'.u[/.ö\z/u] end
  expect nil do 'hëllö'.u[/other/u] end

  expect 'hë'.u do 'hëllö'.u['hë'.u] end
  expect 'lö'.u do 'hëllö'.u['lö'.u] end
  expect 'hë'.u do 'hëllö'.u['hë'] end
  expect 'lö'.u do 'hëllö'.u['lö'] end
  expect nil do 'hëllö'.u['other'.u] end
  expect nil do 'hëllö'.u['other'] end

  expect 'hë'.u do 'hëllö'.u[/(..)(..)/u, 1] end
  expect 'll'.u do 'hëllö'.u[/(..)(..)/u, 2] end
  expect nil do 'hëllö'.u[/(..)(..)/u, 3] end
  expect 'll'.u do 'hëllö'.u[/(..)(..)/u, -1] end
  expect 'hë'.u do 'hëllö'.u[/(..)(..)/u, -2] end
  expect nil do 'hëllö'.u[/(..)(..)/u, -3] end

  expect 'l'.u do 'hëllö'.u[stub(:to_int => 2)] end

  expect ArgumentError do 'hëllö'.u[1, 2, 3] end
  expect ArgumentError do 'hëllö'.u[] end

  expect result.tainted? do 'a'.u.taint[0] end
  expect result.untrusted? do 'a'.u.untrust[0] end
  expect result.tainted? do 'a'.u.taint[0, 1] end
  expect result.untrusted? do 'a'.u.untrust[0, 1] end
  expect result.tainted? do 'a'.u.taint[0...1] end
  expect result.untrusted? do 'a'.u.untrust[0...1] end
  expect result.tainted? do 'a'.u.taint[/a/] end
  expect result.untrusted? do 'a'.u.untrust[/a/] end
  expect result.tainted? do 'a'.u[/a/.taint] end
  expect result.untrusted? do 'a'.u[/a/.untrust] end
  expect result.tainted? do 'a'.u[/(a)/.taint, 1] end
  expect result.untrusted? do 'a'.u[/(a)/.untrust, 1] end
  expect result.not.tainted? do 'a'.u.taint['a'.u] end
  expect result.not.untrusted? do 'a'.u.untrust['a'.u] end
  expect result.not.tainted? do 'a'.u.taint['a'] end
  expect result.not.untrusted? do 'a'.u.untrust['a'] end
  expect result.tainted? do 'a'.u['a'.u.taint] end
  expect result.untrusted? do 'a'.u['a'.u.untrust] end
  expect result.tainted? do 'a'.u['a'.taint] end
  expect result.untrusted? do 'a'.u['a'.untrust] end

  expect ArgumentError do '*'.u * -1 end
  expect ''.u do ''.u * 10 end
  expect '**********'.u do '*'.u * 10 end
  # TODO: Test LONG_MAX.
  expect result.tainted? do ''.u.taint * 10 end
  expect result.untrusted? do ''.u.untrust * 10 end

  expect 'hëll'.u do 'hëll'.u + ''.u end
  expect 'ö'.u do ''.u + 'ö'.u end
  expect 'hëllö'.u do 'hëll'.u + 'ö'.u end
  expect result.tainted? do ''.u.taint + ''.u end
  expect result.tainted? do ''.u + ''.u.taint end
  expect result.not.untrusted? do ''.u.untrust + ''.u end
  expect result.not.untrusted? do ''.u + ''.u.untrust end

  expect TypeError do 'abc'.u =~ 'abc' end
  expect TypeError do 'abc'.u =~ 'abc'.u end
  expect 10 do 'FëëFiëFöö-Fum'.u =~ /Fum$/u end
  expect nil do 'FëëFiëFöö-Fum'.u =~ /FUM$/u end
  expect 'fööbar' do 'föö'.u =~ stub(:=~ => proc{ |t| t + 'bar'.u }) end

  expect 'a' do 'abc'.u.match(/a/)[0] end
  expect nil do 'abc'.u.match(/d/) end
  expect 'a' do 'abc'.u.match('a')[0] end
  expect nil do 'abc'.u.match('d') end
  expect result.tainted? do 'abc'.u.taint.match(/a/) end
  expect result.untrusted? do 'abc'.u.untrust.match(/a/) end
  expect result.tainted? do 'abc'.u.taint.match('a') end
  expect result.untrusted? do 'abc'.u.untrust.match('a') end
  expect result.tainted? do 'abc'.u.match(/a/.taint) end
  expect result.untrusted? do 'abc'.u.match(/a/.untrust) end
  expect result.tainted? do 'abc'.u.match('a'.taint) end
  expect result.untrusted? do 'abc'.u.match('a'.untrust) end

  # TODO: Should <=>, ==, ===, eql?, and casecmp use collation or not?  When
  # should collation be used?  #collate and #collation_key?

  expect true do ''.u.alnum? end
  expect true do 'a'.u.alnum? end
  expect true do 'ab'.u.alnum? end
  expect false do '/'.u.alnum? end

  expect true do ''.u.alpha? end
  expect true do 'a'.u.alpha? end
  expect true do 'ab'.u.alpha? end
  expect false do 'a0'.u.alpha? end

  expect true do ''.u.assigned? end
  expect true do 'a'.u.assigned? end
  expect true do 'ab'.u.assigned? end
  expect false do [0x0588].pack('U').u.assigned? end

  expect true do 'abc'.u.ascii_only? end
  expect false do 'äbc'.u.ascii_only? end

  expect :open_punctuation do '('.u.line_break end
  expect :close_parenthesis do ')'.u.line_break end

  expect :cr do "\r".u.grapheme_break end
  expect :other do 'a'.u.grapheme_break end

  expect 4 do 'äbc'.u.bytesize end
  expect 9 do "äbc\0dëf".u.bytesize end

  expect nil do ''.u.byteslice(0, -2) end
  expect nil do ''.u.byteslice(0, -1) end

  expect ''.u do ''.u.byteslice(0, 0) end
  expect ''.u do ''.u.byteslice(0, 1) end
  expect ''.u do ''.u.byteslice(0, 2) end

  expect nil do ''.u.byteslice(-1, -2) end
  expect nil do ''.u.byteslice(-1, -1) end
  expect nil do ''.u.byteslice(-1, 0) end
  expect nil do ''.u.byteslice(-1, 1) end
  expect nil do ''.u.byteslice(-1, 2) end
  expect nil do ''.u.byteslice(1, -2) end
  expect nil do ''.u.byteslice(1, -1) end
  expect nil do ''.u.byteslice(1, 0) end
  expect nil do ''.u.byteslice(1, 1) end
  expect nil do ''.u.byteslice(1, 2) end

  expect nil do ''.u.byteslice(0) end

  expect 'h'.u do 'hëllö'.u.byteslice(0) end
  expect "\xb6".u do 'hëllö'.u.byteslice(-1) end
  expect nil do 'hëllö'.u.byteslice(7) end
  expect nil do 'hëllö'.u.byteslice(-8) end

  expect "h\xc3".u do 'hëllö'.u.byteslice(0, 2) end
  expect 'ö'.u do 'hëllö'.u.byteslice(-2, 2) end
  expect 'll'.u do 'hëllö'.u.byteslice(3, 2) end

  expect 'hë'.u do 'hëllö'.u.byteslice(0..2) end
  expect 'hë'.u do 'hëllö'.u.byteslice(0...3) end
  expect 'ö'.u do 'hëllö'.u.byteslice(-2..-1) end

  expect 'l'.u do 'hëllö'.u.byteslice(stub(:to_int => 3)) end

  expect ArgumentError do 'hëllö'.u.byteslice(1, 2, 3) end
  expect ArgumentError do 'hëllö'.u.byteslice() end

  expect result.tainted? do 'a'.u.taint.byteslice(0) end
  expect result.untrusted? do 'a'.u.untrust.byteslice(0) end
  expect result.tainted? do 'a'.u.taint.byteslice(0, 1) end
  expect result.untrusted? do 'a'.u.untrust.byteslice(0, 1) end
  expect result.tainted? do 'a'.u.taint.byteslice(0...1) end
  expect result.untrusted? do 'a'.u.untrust.byteslice(0...1) end

  expect 1 do 'あB'.u.casecmp('あa') end
  expect 1 do 'あB'.u.casecmp('あa'.u) end

  expect true do ''.u.cased? end
  expect true do 'a'.u.cased? end
  expect true do 'ab'.u.cased? end
  expect false do '0'.u.cased? end

  expect true do ''.u.case_ignorable? end
  expect true do "'".u.case_ignorable? end
  expect true do "'’".u.case_ignorable? end
  expect true do [0x0307].pack('U').u.case_ignorable? end
  expect false do 'a'.u.case_ignorable? end

  expect 'hëllö'.u do 'hëllö'.u.center(4) end
  expect '   hëllö   '.u do 'hëllö'.u.center(11) end
  expect 'ababaababa'.u do ''.u.center(10, 'ab') end
  expect 'ababaababab'.u do ''.u.center(11, 'ab') end
  expect 'あ3あ'.u do '3'.u.center(5, 'あ') end
  expect ArgumentError.new('zero-width padding') do '3'.u.center(2, '') end
  expect 'あ3あ'.u do '3'.u.center(5, 'あ ') end
  expect 'あ3あ '.u do '3'.u.center(6, 'あ ') end
  expect 'あ 3あ '.u do '3'.u.center(7, 'あ ') end
  expect ArgumentError.new('padding is too wide to complete rounding (2 > 1)') do '3'.u.center(4, 'あ') end
  # TODO: Adjust this to LONG_MAX in Ruby
#  expect ArgumentError do ''.u.center(9223372036854775807) end

  expect result.tainted? do 'a'.u.taint.center(1) end
  expect result.untrusted? do 'a'.u.untrust.center(1) end
  expect result.tainted? do 'a'.u.taint.center(3) end
  expect result.untrusted? do 'a'.u.untrust.center(3) end
  expect result.not.tainted? do 'a'.u.center(1, ' '.taint) end
  expect result.not.untrusted? do 'a'.u.center(1, ' '.untrust) end
  expect result.tainted? do 'a'.u.taint.center(3, ' '.taint) end
  expect result.untrusted? do 'a'.u.untrust.center(3, ' '.untrust) end

  expect 'hello'.u do 'hello'.u.chomp("\n") end
  expect 'hello'.u do "hello\n".u.chomp("\n") end
  expect 'hello'.u do
    saved_rs = $/; $/ = "\n"; begin 'hello'.u.chomp ensure; $/ = saved_rs end
  end
  expect 'hello'.u do
    saved_rs = $/; $/ = "\n"; begin "hello\n".u.chomp ensure; $/ = saved_rs end
  end
  expect 'hello'.u do
    saved_rs = $/; $/ = '!'; begin "hello".u.chomp ensure; $/ = saved_rs end
  end
  expect 'hello'.u do
    saved_rs = $/; $/ = '!'; begin "hello!".u.chomp ensure; $/ = saved_rs end
  end
  expect 'hello!!'.u do "hello!!!".u.chomp('!') end
  expect "hello\r\n".u do "hello\r\n\r\n".u.chomp("\n") end
  expect 'hello'.u do "hello\r".u.chomp("\n") end
  expect 'hello'.u do "hello\r\n".u.chomp('') end
  expect "hello".u do "hello\r\n\r\n".u.chomp('') end
  # NOTE: This differs from Ruby because U treats \r as a newline character and
  # thus removes it.
  expect 'hello'.u do "hello\r".u.chomp('') end
  expect 'a'.u do 'aā'.u.chomp('ā') end
  expect result.tainted? do 'hello'.u.taint.chomp end
  expect result.untrusted? do 'hello'.u.untrust.chomp end

  expect 'hell'.u do 'hellö'.u.chop end
  expect 'hellö'.u do "hellö\r\n".u.chop end
  expect "hellö\n".u do "hellö\n\r".u.chop end
  expect ''.u do ''.u.chop end
  expect ''.u do "\r\n".u.chop end
  expect result.tainted? do 'hello'.u.taint.chop end
  expect result.untrusted? do 'hello'.u.untrust.chop end

  expect ''.u do ''.u.chr end
  expect 'ä'.u do 'ä'.u.chr end
  expect 'ä'.u do 'äbc'.u.chr end
  expect result.tainted? do ''.u.taint.chr end
  expect result.untrusted? do ''.u.untrust.chr end

  expect true do ''.u.cntrl? end
  expect true do "\0".u.cntrl? end
  expect true do "\0\1".u.cntrl? end
  expect false do "a".u.cntrl? end

  expect 0 do 'a'.u.combining_class end
  expect 230 do [0x0307].pack('U').u.combining_class end

  expect 5 do 'hëllö wörld'.u.count('lö') end
  expect 3 do 'hëllö wörld'.u.count('l', 'lö') end
  expect 2 do 'hëllö wörld'.u.count('lö', 'ö') end
  expect 4 do 'hëllö wörld'.u.count('hëllö', '^l') end
  expect 3 do 'hëllö wörld'.u.count('ej-m') end
  expect 0 do 'y'.u.count('a\\-z') end
  expect 5 do 'abcあいう'.u.count('^a') end
  expect 5 do 'abcあいう'.u.count('^あ') end
  expect 2 do 'abcあいう'.u.count('a-z', '^a') end
  expect ArgumentError.new('wrong number of arguments (0 for at least 1)') do 'föö'.u.count end

  expect true do ''.u.defined? end
  expect true do 'a'.u.defined? end
  expect true do 'ab'.u.defined? end
  expect false do [0x0588].pack('U').u.defined? end
  # TODO: This raises an error, as we’re using u_aref_char_validated_n for
  # these functions.  Perhaps use u_aref_char_n and don’t raise errors on
  # invalid input.
  # expect false do [0xD800].pack('U').u.defined? end

  expect 'hë wrd'.u do 'hëllö wörld'.u.delete('lö') end
  expect 'hëö wörd'.u do 'hëllö wörld'.u.delete('l', 'lö') end
  expect 'hëll wrld'.u do 'hëllö wörld'.u.delete('lö', 'ö') end
  expect 'hëll wrld'.u do 'hëllö wörld'.u.delete('aëiöu', '^ë') end
  expect 'hö wörd'.u do 'hëllö wörld'.u.delete('ëj-m') end
  expect 'a'.u do 'aā'.u.delete('ā') end
  expect 'a'.u do 'abcあいう'.u.delete('^a') end
  expect 'bcあいう'.u do 'abcあいう'.u.delete('a') end
  expect 'あ'.u do 'abcあいう'.u.delete('^あ') end
  expect ArgumentError.new('wrong number of arguments (0 for at least 1)') do 'föö'.u.delete end
  expect result.tainted? do 'a'.u.taint.delete('a') end
  expect result.untrusted? do 'a'.u.untrust.delete('a') end

  expect true do ''.u.digit? end
  expect true do '0'.u.digit? end
  expect true do '01'.u.digit? end
  expect false do '0a'.u.digit? end

  expect 'hëllö'.u do 'hëlLÖ'.u.downcase end
  expect 'hëllö'.u do 'hëllö'.u.downcase end
  expect 'hëllö'.u do 'HËLLÖ'.u.downcase end
  expect "abc\0dëf".u do "ABC\0DËF".u.downcase end

  expect 'σ'.u do 'Σ'.u.downcase end
  expect 'ας'.u do 'ΑΣ'.u.downcase end
  expect 'ασβ'.u do 'ΑΣΒ'.u.downcase end
  expect 'ας '.u do 'ΑΣ '.u.downcase end
  expect 'ας’'.u do 'ΑΣ’'.u.downcase end
  expect '’σ'.u do '’Σ'.u.downcase end

  expect 'i'.u do 'I'.u.downcase('lt') end

  expect "i\xcc\x87\xcc\x80\xcc\x87".u do "I\xcc\x80\xcc\x87".u.downcase('lt') end
  expect "i\xcc\x87\xcc\x87".u do "I\xcc\x87".u.downcase('lt') end

  expect "i\xcc\x87\xcc\x80".u do "I\xcc\x80".u.downcase('lt') end
  expect "j\xcc\x87\xcc\x80".u do "J\xcc\x80".u.downcase('lt') end
  expect "į\xcc\x87\xcc\x80".u do "Į\xcc\x80".u.downcase('lt') end
  expect "i\xcc\x87\xcc\x80".u do 'Ì'.u.downcase('lt') end
  expect "i\xcc\x87\xcc\x81".u do 'Í'.u.downcase('lt') end
  expect "i\xcc\x87\xcc\x83".u do 'Ĩ'.u.downcase('lt') end

  expect 'i'.u do 'İ'.u.downcase('tr') end
  expect 'i'.u do 'İ'.u.downcase('az') end

  expect 'i'.u do 'İ'.u.downcase('tr') end
  expect 'i'.u do 'İ'.u.downcase('az') end

  expect 'ı'.u do 'I'.u.downcase('tr') end
  expect 'ı'.u do 'I'.u.downcase('az') end

  expect result.tainted? do 'A'.u.taint.downcase end
  expect result.untrusted? do 'A'.u.untrust.downcase end

  expect 'Ab Iς Ssσ/Ffi'.u do 'aB iς ßσ/ﬃ'.u.titlecase end

  expect 'Ijssel Igloo Ijssel'.u do 'ijssEl iglOo IJSSEL'.u.titlecase end
  expect 'IJssel Igloo IJssel'.u do 'ijssEl iglOo IJSSEL'.u.titlecase('nl') end

  expect '"\xC3bc\u{e4}bc".u'.u do "\xC3bcäbc".u.dump end
  expect result.tainted? do ''.u.taint.dump end
  expect result.untrusted? do ''.u.untrust.dump end

  expect [0x61, 0x62, 0x63, 0x00, 0x64, 0xc3, 0xab, 0x66] do
    "abc\0dëf".u.bytes.entries
  end

  expect ['h'.u, 'ë'.u, 'l'.u, 'l'.u, 'ö'.u] do
    'hëllö'.u.chars.entries
  end

  expect result.tainted? do 'a'.u.taint.chars.first end
  expect result.untrusted? do 'a'.u.untrust.chars.first end

  expect [0x0068, 0x00eb, 0x006c, 0x006c, 0x00f6] do
    'hëllö'.u.codepoints.entries
  end

  expect ["hello\n".u, 'world'.u] do
    saved_rs = $/
    begin
      $/ = "\n"
      "hello\nworld".u.lines.entries
    ensure
      $/ = saved_rs
    end
  end

  expect ["hello\n\n\n".u, 'world'.u] do
      "hello\n\n\nworld".u.lines('').entries
  end

  expect ['hello!'.u, 'world'.u] do
    saved_rs = $/
    begin
      $/ = '!'
      'hello!world'.u.lines.entries
    ensure
      $/ = saved_rs
    end
  end

  expect ["hello\nworld".u] do
    saved_rs = $/
    begin
      $/ = nil
      "hello\nworld".u.lines.entries
    ensure
      $/ = saved_rs
    end
  end

  expect ['hëll hëllö'.u, ' world'.u] do
    'hëll hëllö world'.u.lines('llö').entries
  end

  expect ["hello\0".u, 'world'.u] do
    "hello\0world".u.lines("\0").entries
  end

  expect result.tainted? do 'a'.u.taint.lines.first end
  expect result.untrusted? do 'a'.u.untrust.lines.first end

  expect result.to.be.empty? do ''.u end
  expect result.not.to.be.empty? do 'not'.u end

  expect result.to.end_with?('c') do 'abc'.u end
  expect result.not.to.end_with?('d') do 'abc'.u end
  expect result.to.end_with?('ä') do 'cbä'.u end
  expect result.not.to.end_with?('äb') do 'cbä'.u end
  expect result.to.end_with?('a', 'ä') do 'cbä'.u end
  expect result.not.to.end_with? do 'cbä'.u end

  expect "abc\0ss".u do "abc\0ß".u.foldcase end
  expect result.tainted? do 'a'.u.taint.foldcase end
  expect result.untrusted? do 'a'.u.untrust.foldcase end

  expect true do 'ss'.u.folded? end
  expect false do 'ß'.u.folded? end
  expect true do 'abc\0ß'.u.foldcase.folded? end

  expect 'äbc'.u do 'äbc'.u % [] end

  expect ArgumentError.new('invalid flag ‘ ’ given to directive ‘%’') do '% %'.u % [] end
  expect ArgumentError.new('invalid flags “ #” given to directive ‘%’') do '% #%'.u % [] end
  expect ArgumentError.new('invalid flags “ #+-0” given to directive ‘%’') do '% #+-0%'.u % [] end
  expect ArgumentError.new('directive does not take an argument: %') do '%1$%'.u % [1] end
  expect '%'.u do '%%'.u % [] end
  expect 'ä%c'.u do 'ä%%c'.u % [] end

  expect "%\nb".u do "%\nb".u % [] end
  expect "%\0b".u do "%\0b".u % [] end
  expect "%\0%".u do "%\0%".u % [] end
  expect ArgumentError.new('directive does not allow specifying a width: %') do "%12\nb".u % [] end
  expect 'b%'.u do "b%".u % [] end
  expect ArgumentError.new('directive missing after absolute argument number') do "b%12".u % [] end
  expect ArgumentError.new('directive missing after flags') do "b%#".u % [] end
  expect ArgumentError.new('directive missing after absolute argument number') do "b%1$".u % [] end
  expect ArgumentError.new('directive missing after argument name') do "b%<a>".u % [] end

  expect ArgumentError.new('invalid flag ‘ ’ given to directive ‘c’') do '% c'.u % 0x00e4 end
  expect ArgumentError.new('directive does not allow specifying a precision: c') do '%.1c'.u % [0x00e4] end
  expect ArgumentError.new('wrong number of arguments (0 for at least 1)') do '%cbc'.u % [] end
  expect 'äbc'.u do '%cbc'.u % 0x00e4 end
  expect ' äbc'.u do '%2cbc'.u % 0x00e4 end
  expect 'ä bc'.u do '%-2cbc'.u % 0x00e4 end
  expect ArgumentError.new('wrong number of arguments (1 for at least 2)') do '%*cbc'.u % 0x00e4 end
  expect ' äbc'.u do '%*cbc'.u % [2, 0x00e4] end
  expect ArgumentError.new('cannot use positional argument numbers after absolute argument numbers') do '%*1$cbc'.u % [2, 0x00e4] end
  expect ' äbc'.u do '%2$*1$cbc'.u % [2, 0x00e4] end
  expect 'äbc'.u do '%<a>cbc'.u % { :a => 0x00e4 } end
  expect ' äbc'.u do '%<a>2cbc'.u % { :a => 0x00e4 } end
  expect 'あ'.u do '%c'.u % 0x3042 end
  expect 'あ'.u do '%2c'.u % 0x3042 end
  expect ' あ'.u do '%3c'.u % 0x3042 end
  expect '   ​'.u do '%3c'.u % 0x200b end
  expect ArgumentError.new('cannot use absolute argument number 1: relative argument number already used') do '%c%1$c'.u % [0x00e4] end
  expect ArgumentError.new('cannot use absolute argument number 1: named argument already used') do '%<a>c%1$c'.u % { :a => 0x00e4 } end
  expect ArgumentError.new('absolute argument number beyond end of argument list: 1 > 0') do '%1$%'.u % [] end
  expect ArgumentError.new('cannot use named argument “a”: relative argument number already used') do '%c%<a>c'.u % [0x00e4] end
  expect ArgumentError.new('cannot use named argument “a”: absolute argument number already used') do '%1$c%<a>c'.u % [0x00e4] end
  expect ArgumentError.new('one Hash argument required when using named arguments in format') do '%<a>cbc'.u % 0x00e4 end
  expect((defined?(KeyError) ? KeyError : ArgumentError).new('named argument not found: a')){ '%<a>cbc'.u % { :b => 0x00e4 } }
  expect ArgumentError.new('cannot use positional argument numbers after absolute argument numbers') do '%1$c%c'.u % [0x00e4] end
  expect ArgumentError.new('cannot use positional argument numbers after named arguments') do '%<a>c%c'.u % { :a => 0x00e4 } end
  expect ArgumentError.new('wrong number of arguments (0 for at least 1)') do '%c'.u % [] end

  # TODO: Add flag checks?
  expect 'äbc'.u do '%sc'.u % ['äb'.u] end
  expect 'äc'.u do '%.1sc'.u % ['äb'.u] end
  expect ' äbc'.u do '%3sc'.u % ['äb'.u] end
  expect 'äb c'.u do '%-3sc'.u % ['äb'.u] end
  expect '  äc'.u do '%3.1sc'.u % ['äb'.u] end
  expect 'ä  c'.u do '%-3.1sc'.u % ['äb'.u] end
  expect 'äbc'.u do '%{a}c'.u % { :a => 'äb'.u } end
  expect 'äb3.3c'.u do '%{a}3.3c'.u % { :a => 'äb'.u } end
  expect 'あ'.u do '%.1s'.u % ['あbc'.u] end
  expect 'あ'.u do '%.2s'.u % ['あbc'.u] end
  expect 'あb'.u do '%.3s'.u % ['あbc'.u] end
  expect 'あbc'.u do '%.4s'.u % ['あbc'.u] end
  expect ' あbc'.u do '%5s'.u % ['あbc'.u] end

  # TODO: Add flag checks?
  expect '"äbc".u'.u do '%p'.u % ['äbc'.u] end

  expect '123'.u do '%d'.u % 123 end
  expect '123'.u do '%d'.u % 123.to_f end
  expect '123'.u do '%d'.u % '123' end
  expect '123'.u do '%d'.u % '123'.u end
  expect '123'.u do '%d'.u % [stub(:to_int => 123)] end
  expect ArgumentError do '%d'.u % '123.0' end
  expect ArgumentError do '%d'.u % '123.0'.u end

  expect ' 123'.u do '% d'.u % 123 end
  expect '+123'.u do '%+d'.u % 123 end
  expect '-123'.u do '%d'.u % -123 end

  expect '   123'.u do '%6d'.u % 123 end
  expect '   123'.u do '% 6d'.u % 123 end
  expect '  +123'.u do '%+6d'.u % 123 end
  expect '  -123'.u do '%6d'.u % -123 end

  expect '000123'.u do '%06d'.u % 123 end
  expect ' 00123'.u do '% 06d'.u % 123 end
  expect '+00123'.u do '%+06d'.u % 123 end
  expect '-00123'.u do '%06d'.u % -123 end

  expect '123   '.u do '%-6d'.u % 123 end
  expect ' 123  '.u do '%- 6d'.u % 123 end
  expect '+123  '.u do '%-+6d'.u % 123 end
  expect '-123  '.u do '%-6d'.u % -123 end

  expect '123   '.u do
    saved_verbose = $VERBOSE
    $VERBOSE = nil
    begin
      '%-06d'.u % 123
    ensure
      $VERBOSE = saved_verbose
    end
  end

  expect '000123'.u do '%.6d'.u % 123 end
  expect ' 000123'.u do '% .6d'.u % 123 end
  expect '+000123'.u do '%+.6d'.u % 123 end
  expect '-000123'.u do '%.6d'.u % -123 end

  expect '   000123'.u do with_verbose(nil){ '%09.6d'.u % 123 } end
  expect '   000123'.u do '%9.6d'.u % 123 end
  expect '   000123'.u do '% 9.6d'.u % 123 end
  expect '  +000123'.u do '%+9.6d'.u % 123 end
  expect '  -000123'.u do '%9.6d'.u % -123 end

  expect '000123   '.u do '%-9.6d'.u % 123 end
  expect ' 000123  '.u do '%- 9.6d'.u % 123 end
  expect '+000123  '.u do '%-+9.6d'.u % 123 end
  expect '-000123  '.u do '%-9.6d'.u % -123 end

  # TODO: Need a lot more tests for Bignum code-paths.
  expect Bignum do 12345678901234567890 end
  expect '12345678901234567890'.u do '%d'.u % 12345678901234567890 end

  expect '173'.u do '%o'.u % 123 end

  expect ' 173'.u do '% o'.u % 123 end
  expect '+173'.u do '%+o'.u % 123 end
  expect '-173'.u do '%+o'.u % -123 end

  expect '   173'.u do '%6o'.u % 123 end
  expect '   173'.u do '% 6o'.u % 123 end
  expect '  +173'.u do '%+6o'.u % 123 end
  expect '  -173'.u do '%+6o'.u % -123 end

  expect '000173'.u do '%06o'.u % 123 end
  expect ' 00173'.u do '% 06o'.u % 123 end
  expect '+00173'.u do '%+06o'.u % 123 end
  expect '-00173'.u do '%+06o'.u % -123 end

  expect '173   '.u do '%-6o'.u % 123 end
  expect ' 173  '.u do '%- 6o'.u % 123 end
  expect '+173  '.u do '%-+6o'.u % 123 end
  expect '-173  '.u do '%-+6o'.u % -123 end

  expect '000173'.u do '%.6o'.u % 123 end
  expect ' 000173'.u do '% .6o'.u % 123 end
  expect '+000173'.u do '%+.6o'.u % 123 end
  expect '-000173'.u do '%+.6o'.u % -123 end

  expect '   000173'.u do '%9.6o'.u % 123 end
  expect '   000173'.u do '% 9.6o'.u % 123 end
  expect '  +000173'.u do '%+9.6o'.u % 123 end
  expect '  -000173'.u do '%+9.6o'.u % -123 end

  expect '+173'.u do with_verbose(nil){ '%+ o'.u % 123 } end
  expect warning('‘o’ directive ignores ‘ ’ flag when ‘+’ flag has been specified') do '%+ o'.u % 123 end
  expect '-173'.u do with_verbose(nil){ '%+ o'.u % -123 } end
  expect '0173'.u do '%#o'.u % 123 end
  expect '..7605'.u do '%o'.u % -123 end
  expect '..7605'.u do with_verbose(nil){ '%#o'.u % -123 } end
  expect warning('‘o’ directive ignores ‘#’ flag when given a negative argument') do '%#o'.u % -123 end

  expect '   ..7777605'.u do '%12.9o'.u % -123 end
  expect '   000000173'.u do '%#12.9o'.u % 123 end
  expect '   ..7777605'.u do with_verbose(nil){ '%#12.9o'.u % -123 } end

  expect '0' do '%o'.u % 0 end
  expect '0' do '%#o'.u % 0 end
  expect '  0' do '%3o'.u % 0 end
  expect '  0' do '%#3o'.u % 0 end
  expect '000' do '%03o'.u % 0 end
  expect '000' do '%#03o'.u % 0 end
  expect '     0' do '%6o'.u % 0 end
  expect '     0' do '%#6o'.u % 0 end
  expect '   000' do '%6.3o'.u % 0 end
  expect '   000' do '%#6.3o'.u % 0 end
  expect '   000' do with_verbose(nil){ '%06.3o'.u % 0 } end
  expect '   000' do with_verbose(nil){ '%#06.3o'.u % 0 } end

  # TODO: Need a lot more Bignum tests
  expect Bignum do 01255245230635307605322 end
  expect '1255245230635307605322'.u do '%o'.u % 01255245230635307605322 end

  expect '10e'.u do '%x'.u % 0x10e end

  expect '0x10e'.u do '%#x'.u % 0x10e end

  expect '0'.u do '%#x'.u % 0x0 end

  expect ' 10e'.u do '% x'.u % +0x10e end
  expect '+10e'.u do '%+x'.u % +0x10e end
  expect '-10e'.u do '%+x'.u % -0x10e end

  expect ' 0x10e'.u do '%# x'.u % +0x10e end
  expect '+0x10e'.u do '%#+x'.u % +0x10e end
  expect '-0x10e'.u do '%#+x'.u % -0x10e end

  expect '   10e'.u do '%6x'.u % 0x10e end
  expect '   10e'.u do '% 6x'.u % 0x10e end
  expect '  +10e'.u do '%+6x'.u % 0x10e end
  expect '  -10e'.u do '%+6x'.u % -0x10e end

  expect ' 0x10e'.u do '%#6x'.u % 0x10e end
  expect ' 0x10e'.u do '%# 6x'.u % 0x10e end
  expect '+0x10e'.u do '%#+6x'.u % 0x10e end
  expect '-0x10e'.u do '%#+6x'.u % -0x10e end

  expect '00010e'.u do '%06x'.u % 0x10e end
  expect ' 0010e'.u do '% 06x'.u % 0x10e end
  expect '+0010e'.u do '%+06x'.u % 0x10e end
  expect '-0010e'.u do '%+06x'.u % -0x10e end

  expect '0x010e'.u do '%#06x'.u % 0x10e end
  expect ' 0x10e'.u do '%# 06x'.u % 0x10e end
  expect '+0x10e'.u do '%#+06x'.u % 0x10e end
  expect '-0x10e'.u do '%#+06x'.u % -0x10e end

  expect '10e   '.u do '%-6x'.u % 0x10e end
  expect ' 10e  '.u do '%- 6x'.u % 0x10e end
  expect '+10e  '.u do '%-+6x'.u % 0x10e end
  expect '-10e  '.u do '%-+6x'.u % -0x10e end

  expect '0x10e '.u do '%#-6x'.u % 0x10e end
  expect ' 0x10e'.u do '%#- 6x'.u % 0x10e end
  expect '+0x10e'.u do '%#-+6x'.u % 0x10e end
  expect '-0x10e'.u do '%#-+6x'.u % -0x10e end

  expect '00010e'.u do '%.6x'.u % 0x10e end
  expect ' 00010e'.u do '% .6x'.u % 0x10e end
  expect '+00010e'.u do '%+.6x'.u % 0x10e end
  expect '-00010e'.u do '%+.6x'.u % -0x10e end

  expect '0x00010e'.u do '%#.6x'.u % 0x10e end
  expect ' 0x00010e'.u do '%# .6x'.u % 0x10e end
  expect '+0x00010e'.u do '%#+.6x'.u % 0x10e end
  expect '-0x00010e'.u do '%#+.6x'.u % -0x10e end

  expect '   00010e'.u do '%9.6x'.u % 0x10e end
  expect '   00010e'.u do '% 9.6x'.u % 0x10e end
  expect '  +00010e'.u do '%+9.6x'.u % 0x10e end
  expect '  -00010e'.u do '%+9.6x'.u % -0x10e end

  expect ' 0x00010e'.u do '%#9.6x'.u % 0x10e end
  expect ' 0x00010e'.u do '%# 9.6x'.u % 0x10e end
  expect '+0x00010e'.u do '%#+9.6x'.u % 0x10e end
  expect '-0x00010e'.u do '%#+9.6x'.u % -0x10e end

  expect '+10e'.u do with_verbose(nil){ '%+ x'.u % 0x10e } end
  expect warning('‘x’ directive ignores ‘ ’ flag when ‘+’ flag has been specified') do '%+ x'.u % 0x10e end
  expect '-10e'.u do with_verbose(nil){ '%+ x'.u % -0x10e } end
  expect '..fef2'.u do '%x'.u % -0x10e end
  expect '0x..fef2'.u do '%#x'.u % -0x10e end
  expect '   ..ffffef2'.u do '%12.9x'.u % -0x10e end
  expect ' 0x00000010e'.u do '%#12.9x'.u % 0x10e end
  expect ' 0x..ffffef2'.u do '%#12.9x'.u % -0x10e end

  expect '10E'.u do '%X'.u % 0x10e end
  expect '0X10E'.u do '%#X'.u % 0x10e end
  expect '-10E'.u do '%+X'.u % -0x10e end
  expect '-0X10E'.u do '%#+X'.u % -0x10e end
  expect '..FEF2'.u do '%-X'.u % -0x10e end
  expect '0X..FEF2'.u do '%#-X'.u % -0x10e end

  expect '101'.u do '%b'.u % 0b101 end

  expect '0b101'.u do '%#b'.u % 0b101 end

  expect '0'.u do '%#b'.u % 0b0 end

  expect ' 101'.u do '% b'.u % +0b101 end
  expect '+101'.u do '%+b'.u % +0b101 end
  expect '-101'.u do '%+b'.u % -0b101 end

  expect ' 0b101'.u do '%# b'.u % +0b101 end
  expect '+0b101'.u do '%#+b'.u % +0b101 end
  expect '-0b101'.u do '%#+b'.u % -0b101 end

  expect '   101'.u do '%6b'.u % 0b101 end
  expect '   101'.u do '% 6b'.u % 0b101 end
  expect '  +101'.u do '%+6b'.u % 0b101 end
  expect '  -101'.u do '%+6b'.u % -0b101 end


  expect ' 0b101'.u do '%#6b'.u % 0b101 end
  expect ' 0b101'.u do '%# 6b'.u % 0b101 end
  expect '+0b101'.u do '%#+6b'.u % 0b101 end
  expect '-0b101'.u do '%#+6b'.u % -0b101 end

  expect '000101'.u do '%06b'.u % 0b101 end
  expect ' 00101'.u do '% 06b'.u % 0b101 end
  expect '+00101'.u do '%+06b'.u % 0b101 end
  expect '-00101'.u do '%+06b'.u % -0b101 end

  expect '0b0101'.u do '%#06b'.u % 0b101 end
  expect ' 0b101'.u do '%# 06b'.u % 0b101 end
  expect '+0b101'.u do '%#+06b'.u % 0b101 end
  expect '-0b101'.u do '%#+06b'.u % -0b101 end

  expect '101   '.u do '%-6b'.u % 0b101 end
  expect ' 101  '.u do '%- 6b'.u % 0b101 end
  expect '+101  '.u do '%-+6b'.u % 0b101 end
  expect '-101  '.u do '%-+6b'.u % -0b101 end

  expect '0b101 '.u do '%#-6b'.u % 0b101 end
  expect ' 0b101'.u do '%#- 6b'.u % 0b101 end
  expect '+0b101'.u do '%#-+6b'.u % 0b101 end
  expect '-0b101'.u do '%#-+6b'.u % -0b101 end

  expect '000101'.u do '%.6b'.u % 0b101 end
  expect ' 000101'.u do '% .6b'.u % 0b101 end
  expect '+000101'.u do '%+.6b'.u % 0b101 end
  expect '-000101'.u do '%+.6b'.u % -0b101 end

  expect '0b000101'.u do '%#.6b'.u % 0b101 end
  expect ' 0b000101'.u do '%# .6b'.u % 0b101 end
  expect '+0b000101'.u do '%#+.6b'.u % 0b101 end
  expect '-0b000101'.u do '%#+.6b'.u % -0b101 end

  expect '   000101'.u do '%9.6b'.u % 0b101 end
  expect '   000101'.u do '% 9.6b'.u % 0b101 end
  expect '  +000101'.u do '%+9.6b'.u % 0b101 end
  expect '  -000101'.u do '%+9.6b'.u % -0b101 end

  expect ' 0b000101'.u do '%#9.6b'.u % 0b101 end
  expect ' 0b000101'.u do '%# 9.6b'.u % 0b101 end
  expect '+0b000101'.u do '%#+9.6b'.u % 0b101 end
  expect '-0b000101'.u do '%#+9.6b'.u % -0b101 end

  expect '+101'.u do with_verbose(nil){ '%+ b'.u % 0b101 } end
  expect warning('‘b’ directive ignores ‘ ’ flag when ‘+’ flag has been specified') do '%+ b'.u % 0b101 end
  expect '-101'.u do with_verbose(nil){ '%+ b'.u % -0b101 } end
  expect '..1011'.u do '%b'.u % -0b101 end
  expect '0b..1011'.u do '%#b'.u % -0b101 end
  expect '   ..1111011'.u do '%12.9b'.u % -0b101 end
  expect ' 0b000000101'.u do '%#12.9b'.u % 0b101 end
  expect ' 0b..1111011'.u do '%#12.9b'.u % -0b101 end

  expect '0B101'.u do '%#B'.u % 0b101 end

  expect 'NaN'.u do '%f'.u % (0.0/0.0) end
  expect 'NaN'.u do '%-f'.u % (0.0/0.0) end
  expect '+NaN'.u do '%+f'.u % (0.0/0.0) end
  expect ' NaN'.u do '% f'.u % (0.0/0.0) end

  expect '   NaN'.u do '%6f'.u % (0.0/0.0) end
  expect '  +NaN'.u do '%+6f'.u % (0.0/0.0) end
  expect '   NaN'.u do '% 6f'.u % (0.0/0.0) end
  expect '  +NaN'.u do with_verbose(nil){ '%+ 6f'.u % (0.0/0.0) } end

  expect '   NaN'.u do '%06f'.u % (0.0/0.0) end
  expect '  +NaN'.u do '%+06f'.u % (0.0/0.0) end
  expect '   NaN'.u do '% 06f'.u % (0.0/0.0) end
  expect '  +NaN'.u do with_verbose(nil){ '%+ 06f'.u % (0.0/0.0) } end

  expect 'NaN   '.u do '%-6f'.u % (0.0/0.0) end
  expect 'NaN   '.u do '%-06f'.u % (0.0/0.0) end
  expect '+NaN  '.u do '%-+6f'.u % (0.0/0.0) end
  expect '+NaN  '.u do '%-+06f'.u % (0.0/0.0) end
  expect ' NaN  '.u do '%- 6f'.u % (0.0/0.0) end
  expect ' NaN  '.u do '%- 06f'.u % (0.0/0.0) end

  expect 'Inf'.u do '%f'.u % (1.0/0.0) end
  expect 'Inf'.u do '%-f'.u % (1.0/0.0) end
  expect '+Inf'.u do '%+f'.u % (1.0/0.0) end
  expect '-Inf'.u do '%+f'.u % -(1.0/0.0) end
  expect ' Inf'.u do '% f'.u % (1.0/0.0) end

  expect '   Inf'.u do '%6f'.u % (1.0/0.0) end
  expect '  +Inf'.u do '%+6f'.u % (1.0/0.0) end
  expect '  -Inf'.u do '%+6f'.u % -(1.0/0.0) end
  expect '   Inf'.u do '% 6f'.u % (1.0/0.0) end
  expect '  +Inf'.u do with_verbose(nil){ '%+ 6f'.u % (1.0/0.0) } end

  expect '   Inf'.u do '%06f'.u % (1.0/0.0) end
  expect '  +Inf'.u do '%+06f'.u % (1.0/0.0) end
  expect '  -Inf'.u do '%+06f'.u % -(1.0/0.0) end
  expect '   Inf'.u do '% 06f'.u % (1.0/0.0) end
  expect '  +Inf'.u do with_verbose(nil){ '%+ 06f'.u % (1.0/0.0) } end

  expect 'Inf   '.u do '%-6f'.u % (1.0/0.0) end
  expect 'Inf   '.u do '%-06f'.u % (1.0/0.0) end
  expect '+Inf  '.u do '%-+6f'.u % (1.0/0.0) end
  expect '+Inf  '.u do '%-+06f'.u % (1.0/0.0) end
  expect '-Inf  '.u do '%-+6f'.u % -(1.0/0.0) end
  expect '-Inf  '.u do '%-+06f'.u % -(1.0/0.0) end
  expect ' Inf  '.u do '%- 6f'.u % (1.0/0.0) end
  expect ' Inf  '.u do '%- 06f'.u % (1.0/0.0) end

  # TODO: Probably sizeof(double)-dependent
  expect '179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368'.u do '%.0f'.u % 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368 end

  expect '       -0.'.u do '%#10.0f'.u % -0.5 end

  # NOTE: This needs to be fixed.
  # expect U::String do '%#+-0 .2147483638f'.u % 1 end

  # TODO: These two give different results in Ruby 1.8 and Ruby 1.9.
  # expect '0x2p+1'.u do '%.0a'.u % 3.875 end
  # expect '-0x2.0p+1'.u do '%.1a'.u % -3.9921875 end
  expect '0x0p+0'.u do '%a'.u % 0.0 end
  expect '-0x0p+0'.u do '%a'.u % -0.0 end
  expect '0x1p+1'.u do '%a'.u % 2.0 end
  expect '0x1p+0'.u do '%a'.u % 1.0 end
  expect '0x1p-1'.u do '%a'.u % 0.5 end
  expect '0x1p+10'.u do '%a'.u % 1024 end
  # TODO: Probably sizeof(double)-dependent
  expect '0x1.23456p+789'.u do '%a'.u % 3.704450999893983e+237 end
  # TODO: This is sizeof(double)-dependent
  # expect '0x0.0000000000001p-1022'.u do '%a'.u % 4.9e-324 end

  expect '   -0x1p+0'.u do '%10a'.u % -1 end
  expect ' -0x1.8p+0'.u do '%10a'.u % -1.5 end
  expect ' -0x1.4p+0'.u do '%10a'.u % -1.25 end
  expect ' -0x1.2p+0'.u do '%10a'.u % -1.125 end
  expect ' -0x1.1p+0'.u do '%10a'.u % -1.0625 end
  expect '-0x1.08p+0'.u do '%10a'.u % -1.03125 end

  expect '-0x0001p+0'.u do '%010a'.u % -1 end
  expect '-0x01.8p+0'.u do '%010a'.u % -1.5 end
  expect '-0x01.4p+0'.u do '%010a'.u % -1.25 end
  expect '-0x01.2p+0'.u do '%010a'.u % -1.125 end
  expect '-0x01.1p+0'.u do '%010a'.u % -1.0625 end
  expect '-0x1.08p+0'.u do '%010a'.u % -1.03125 end

  expect '1.000000e+06'.u do '%e' % 1.000000e+06 end
  expect '1.000000E+06'.u do '%E' % 1.000000E+06 end

  expect '1e+06'.u do '%g' % 1e+06 end
  expect '1E+06'.u do '%G' % 1E+06 end

  expect result.tainted? do '%s'.u.taint % ['abc'] end
  expect result.not.untrusted? do '%s'.u.untrust % ['abc'] end
  expect result.tainted? do '%s'.u.taint % ['abc'.taint] end
  expect result.not.untrusted? do '%s'.u.untrust % ['abc'.untrust] end
  expect result.not.tainted? do '%c'.u % ['a'.taint] end
  expect result.not.untrusted? do '%c'.u % ['a'.untrust] end
  expect result.tainted? do '%s'.u % ['abc'.taint] end
  expect result.not.untrusted? do '%s'.u % ['abc'.untrust] end
  expect result.tainted? do '%p'.u % ['abc'.taint] end
  expect result.not.untrusted? do '%p'.u % ['abc'.untrust] end

  expect 0x00c3 do 'äbc'.u.getbyte(0) end
  expect 0x00a4 do 'äbc'.u.getbyte(1) end
  expect nil do 'äbc'.u.getbyte(4) end
  expect 0x00a4 do 'äbc'.u.getbyte(-3) end
  expect 0x00c3 do 'äbc'.u.getbyte(-4) end
  expect nil do 'äbc'.u.getbyte(-5) end

  expect true do ''.u.graph? end
  expect true do '0'.u.graph? end
  expect true do '01'.u.graph? end
  expect false do "\0".u.graph? end

  expect 'bbc'.u do 'abc'.u.gsub('a', 'b') end
  expect 'h*ll*'.u do 'hello'.u.gsub(/[aeiou]/u, '*'.u) end
  expect 'h*ll*'.u do 'hëllö'.u.gsub(/[äëïöü]/u, '*'.u) end
  expect 'h<ë>ll<ö>'.u do 'hëllö'.u.gsub(/([äëïöü])/u, '<\\1>'.u) end
  expect 'h<ë>ll<ö>'.u do 'hëllö'.u.gsub(/([ëö])/u, 'ë'.u => '<ë>'.u, 'ö'.u => '<ö>'.u) end
  expect 'h ë l l ö '.u do 'hëllö'.u.gsub(/./u){ |s| s[0].to_s + ' ' } end
  expect 'HËLL-ö'.u do 'hëllö'.u.gsub(/(hëll)(.)/u){ |s| $1.u.upcase + '-'.u + $2.u } end
  expect ArgumentError do 'hëllö'.gsub end
  expect result.tainted? do 'a'.u.taint.gsub(/a/, 'b') end
  expect result.untrusted? do 'a'.u.untrust.gsub(/a/, 'b') end
  expect result.not.tainted? do 'a'.u.gsub(/a/.taint, 'b') end
  expect result.not.untrusted? do 'a'.u.gsub(/a/.untrust, 'b') end
  expect result.tainted? do 'a'.u.gsub(/a/, 'b'.taint) end
  expect result.untrusted? do 'a'.u.gsub(/a/, 'b'.untrust) end
  expect result.tainted? do 'a'.u.gsub(/a/, {'a'.u => 'b'}.taint) end
  expect result.not.untrusted? do 'a'.u.gsub(/a/, {'a'.u => 'b'}.untrust) end
  expect result.tainted? do 'a'.u.gsub(/a/, {'a'.u => 'b'.taint}) end
  expect result.untrusted? do 'a'.u.gsub(/a/, {'a'.u => 'b'.untrust}) end
  expect result.tainted? do 'a'.u.gsub(/a/, Hash.new{ 'b'.taint }) end
  expect result.untrusted? do 'a'.u.gsub(/a/, Hash.new{ 'b'.untrust }) end
  expect result.tainted? do 'a'.u.gsub(/a/){ 'b'.taint } end
  expect result.untrusted? do 'a'.u.gsub(/a/){ 'b'.untrust } end

  expect 'bbc'.u do 'abc'.u.sub('a', 'b') end
  expect 'h*llo'.u do 'hello'.u.sub(/[aeiou]/u, '*'.u) end
  expect 'h*llö'.u do 'hëllö'.u.sub(/[äëïöü]/u, '*'.u) end
  expect 'h<ë>llö'.u do 'hëllö'.u.sub(/([äëïöü])/u, '<\\1>'.u) end
  expect 'h<ë>llö'.u do 'hëllö'.u.sub(/([ëö])/u, 'ë'.u => '<ë>'.u, 'ö'.u => '<ö>'.u) end
  expect 'h ëllö'.u do 'hëllö'.u.sub(/./u){ |s| s[0].to_s + ' ' } end
  expect 'HËLL-ö'.u do 'hëllö'.u.sub(/(hëll)(.)/u){ |s| $1.u.upcase + '-'.u + $2.u } end
  expect ArgumentError do 'hëllö'.sub end
  expect result.tainted? do 'a'.u.taint.sub(/a/, 'b') end
  expect result.untrusted? do 'a'.u.untrust.sub(/a/, 'b') end
  expect result.not.tainted? do 'a'.u.sub(/a/.taint, 'b') end
  expect result.not.untrusted? do 'a'.u.sub(/a/.untrust, 'b') end
  expect result.tainted? do 'a'.u.sub(/a/, 'b'.taint) end
  expect result.untrusted? do 'a'.u.sub(/a/, 'b'.untrust) end
  expect result.tainted? do 'a'.u.sub(/a/, {'a'.u => 'b'}.taint) end
  expect result.untrusted? do 'a'.u.sub(/a/, {'a'.u => 'b'}.untrust) end
  expect result.tainted? do 'a'.u.sub(/a/, {'a'.u => 'b'.taint}) end
  expect result.untrusted? do 'a'.u.sub(/a/, {'a'.u => 'b'.untrust}) end
  expect result.tainted? do 'a'.u.sub(/a/, Hash.new{ 'b'.taint }) end
  expect result.untrusted? do 'a'.u.sub(/a/, Hash.new{ 'b'.untrust }) end
  expect result.tainted? do 'a'.u.sub(/a/){ 'b'.taint } end
  expect result.untrusted? do 'a'.u.sub(/a/){ 'b'.untrust } end

  expect true do 'hëllö'.u.hash == 'hëllö'.u.hash end
  expect false do 'hëllö'.u.hash == 'hëlLÖ'.u.hash end
  expect false do 'a'.u.hash == "a\0".u.hash end

  expect 255 do '0xff'.u.hex end
  expect(-255) do '-0xff'.u.hex end
  expect 255 do 'ff'.u.hex end
  expect(-255) do '-ff'.u.hex end
  expect 0 do '-ralph'.u.hex end
  expect(-15) do '-fred'.u.hex end
  expect 15 do 'fred'.u.hex end
  # TODO: Add tests for Unicode digit values

  expect result.to.include?('f'.u) do 'fööbär'.u end
  expect result.to.include?('föö'.u) do 'fööbär'.u end
  expect result.to.include?('bär'.u) do 'fööbär'.u end
  expect result.not.to.include?('bäz'.u) do 'fööbär'.u end
  expect result.not.to.include?('z'.u) do 'fööbär'.u end

  expect 0 do 'hëllö'.u.index('') end
  expect 0 do 'hëllö'.u.index('h') end
  expect 4 do 'hëllö'.u.index('ö') end
  expect 1 do 'hëllö'.u.index('ëll') end
  expect 2 do 'hëllö'.u.index(/ll/u) end

  expect nil do 'hëllö'.u.index('hëllö!') end

  expect nil do 'hëllö'.u.index('z') end
  expect nil do 'hëllö'.u.index(/z./u) end

  expect 3 do 'hëllö'.u.index('l', 3) end
  expect 3 do 'hëllö'.u.index(/l./u, 3) end

  expect nil do 'hëllö'.u.index('hëllö!', 3) end

  expect nil do 'hëllö'.u.index('z', 3) end
  expect nil do 'hëllö'.u.index(/z./u, 3) end

  expect 2 do 'hëllö'.u.index(stub(:to_str => 'llö')) end
  expect TypeError do 'hëllö'.u.index(Object.new) end

  expect nil do 'föö'.u.index(//, -100) end
  expect nil do 'föö'.u.index(//, -100); $~ end

  expect :koala do 'koala'.u.intern end
  expect :'köälä' do 'köälä'.u.intern end

  expect 0 do ''.u.length end
  expect 4 do '1234'.u.length end
  expect 6 do "1234\r\n".u.length end
  expect 7 do "\0011234\r\n".u.length end
  expect 5 do 'hëllö'.u.length end
  expect 6 do "\0hëllö".u.length end
  # TODO: Why not throw an error here?
  expect 11 do "hëllö\0agäin\303".u.length end

  expect true do 'i'.u.lower? end
  expect true do 'i'.u.lower?('lt') end
  expect false do 'I'.u.lower? end
  expect false do 'I'.u.lower?('lt') end

  # TODO: Add tests for Unicode whitespace characters
  expect 'あ'.u do 'あ'.u.lstrip end
  expect 'あ'.u do '     あ'.u.lstrip end
  expect 'あ     '.u do 'あ     '.u.lstrip end
  expect result.tainted? do 'あ'.u.taint.lstrip end
  expect result.untrusted? do 'あ'.u.untrust.lstrip end

  expect true do ''.u.newline? end
  expect true do [0x2028].pack('U').u.newline? end
  expect true do "\r\n".u.newline? end
  expect false do 'a'.u.newline? end

  expect ''.u do ''.u.mirror end
  expect ')'.u do '('.u.mirror end
  expect ')('.u do '()'.u.mirror end
  expect result.tainted? do ''.u.taint.mirror end
  expect result.untrusted? do ''.u.untrust.mirror end

  expect TypeError.new('not a symbol: 1') do ''.u.normalize(1) end
  expect ArgumentError.new('unknown normalization mode: :ufc') do ''.u.normalize(:ufc) end
  expect 'Ḋ'.u do "D\xcc\x87".u.normalize(:nfc) end
  expect result.tainted? do ''.u.taint.normalize end
  expect result.untrusted? do ''.u.untrust.normalize end

  # TODO: Add tests for Unicode digit values
  expect 255 do '0377'.u.oct end
  expect 255 do '377'.u.oct end
  expect(-255) do '-0377'.u.oct end
  expect(-255) do '-377'.u.oct end
  expect 0 do '00'.u.oct end
  expect 24 do '030OO'.u.oct end

  expect ArgumentError.new('String is empty') do ''.u.ord end
  expect 0x00e4 do 'ä'.u.ord end
  expect 0x00e4 do 'äbc'.u.ord end

  expect ['hë'.u, 'l'.u, 'lö'.u] do 'hëllö'.u.partition(/l/u) end
  expect ['hë'.u, 'l'.u, 'lö'.u] do 'hëllö'.u.partition('l'.u) end
  expect ['hë'.u, 'l'.u, 'lö'.u] do 'hëllö'.u.partition('l') end
  expect TypeError do 'hëllö'.u.partition(0) end
  expect ['föö'.u, '-'.u, 'bär'.u] do 'föö-bär'.u.partition(stub(:to_str => '-')) end
  expect [true, true, true] do 'abc'.u.taint.partition(/b/).map(&:tainted?) end
  expect [true, true, true] do 'abc'.u.untrust.partition(/b/).map(&:untrusted?) end
  expect [false, true, false] do 'abc'.u.partition(/b/.taint).map(&:tainted?) end
  expect [false, true, false] do 'abc'.u.partition(/b/.untrust).map(&:untrusted?) end
  expect [true, true, true] do 'abc'.u.taint.partition(/b/.taint).map(&:tainted?) end
  expect [true, true, true] do 'abc'.u.untrust.partition(/b/.untrust).map(&:untrusted?) end
  expect [true, false, true] do 'abc'.u.taint.partition('b').map(&:tainted?) end
  expect [true, false, true] do 'abc'.u.untrust.partition('b').map(&:untrusted?) end
  expect [false, true, false] do 'abc'.u.partition('b'.taint).map(&:tainted?) end
  expect [false, true, false] do 'abc'.u.partition('b'.untrust).map(&:untrusted?) end
  expect [true, true, true] do 'abc'.u.taint.partition('b'.taint).map(&:tainted?) end
  expect [true, true, true] do 'abc'.u.untrust.partition('b'.untrust).map(&:untrusted?) end

  expect ['hël'.u, 'l'.u, 'ö'.u] do 'hëllö'.u.rpartition(/l/u) end
  expect ['hël'.u, 'l'.u, 'ö'.u] do 'hëllö'.u.rpartition('l'.u) end
  expect ['hël'.u, 'l'.u, 'ö'.u] do 'hëllö'.u.rpartition('l') end
  expect TypeError do 'hëllö'.u.rpartition(0) end
  expect ['föö'.u, '-'.u, 'bär'.u] do 'föö-bär'.u.rpartition(stub(:to_str => '-')) end
  expect [true, true, true] do 'abc'.u.taint.rpartition(/b/).map(&:tainted?) end
  expect [true, true, true] do 'abc'.u.untrust.rpartition(/b/).map(&:untrusted?) end
  expect [false, true, false] do 'abc'.u.rpartition(/b/.taint).map(&:tainted?) end
  expect [false, true, false] do 'abc'.u.rpartition(/b/.untrust).map(&:untrusted?) end
  expect [true, true, true] do 'abc'.u.taint.rpartition(/b/.taint).map(&:tainted?) end
  expect [true, true, true] do 'abc'.u.untrust.rpartition(/b/.untrust).map(&:untrusted?) end
  expect [true, false, true] do 'abc'.u.taint.rpartition('b').map(&:tainted?) end
  expect [true, false, true] do 'abc'.u.untrust.rpartition('b').map(&:untrusted?) end
  expect [false, true, false] do 'abc'.u.rpartition('b'.taint).map(&:tainted?) end
  expect [false, true, false] do 'abc'.u.rpartition('b'.untrust).map(&:untrusted?) end
  expect [true, true, true] do 'abc'.u.taint.rpartition('b'.taint).map(&:tainted?) end
  expect [true, true, true] do 'abc'.u.untrust.rpartition('b'.untrust).map(&:untrusted?) end

  expect true do ''.u.print? end
  expect true do 'a'.u.print? end
  expect true do 'ab'.u.print? end
  expect false do "\n".u.print? end

  expect true do ''.u.punct? end
  expect true do '.'.u.punct? end
  expect true do '()'.u.punct? end
  expect false do 'a'.u.punct? end

  expect 'ateb'.u do 'beta'.u.reverse end
  expect 'madamImadam'.u do 'madamImadam'.u.reverse end
  expect "alpha\0beta".u do "ateb\0ahpla".u.reverse end
  expect result.tainted? do 'a'.u.taint.reverse end
  expect result.untrusted? do 'a'.u.untrust.reverse end

  expect 5 do 'hëllö'.u.rindex('') end
  expect 3 do 'hëllö'.u.rindex('l') end
  expect 6 do 'ëll, hëllö'.u.rindex('ëll') end
  expect 7 do 'ëll, hëllö'.u.rindex(/ll./u) end

  expect nil do 'hëllö'.u.rindex('hëllö!') end

  expect nil do 'hëllö'.u.rindex('z') end
  expect nil do 'hëllö'.u.rindex(/z./u) end

  expect 3 do 'hëllö,lö'.u.rindex('l', 3) end
  expect 3 do 'hëllö,lö'.u.rindex(/l./u, 3) end

  expect nil do 'hëllö,lö'.u.rindex('hëllö!', 3) end

  expect nil do 'hëllö,lö'.u.rindex('z', 3) end
  expect nil do 'hëllö,lö'.u.rindex(/z./u, 3) end

  expect 6 do 'fööbarbarbaz'.u.rindex(stub(:to_str => 'bar')) end
  expect TypeError do 'hëllö'.u.rindex(Object.new) end

  expect nil do 'föö'.u.rindex(//, -100) end
  expect nil do 'föö'.u.rindex(//, -100); $~ end

  # TODO: Add tests for Unicode whitespace characters
  expect 'あ'.u do 'あ'.u.rstrip end
  expect '     あ'.u do '     あ'.u.rstrip end
  expect 'あ'.u do 'あ     '.u.rstrip end
  expect result.tainted? do 'あ'.u.taint.rstrip end
  expect result.untrusted? do 'あ'.u.untrust.rstrip end

  expect ['crüel'.u, 'wörld'.u] do 'crüel wörld'.u.scan(/[[:word:]]+/u) end
  expect ['crü'.u, 'el '.u, 'wör'.u] do 'crüel wörld'.u.scan(/.../u) end
  expect [['crü'.u], ['el '.u], ['wör'.u]] do 'crüel wörld'.u.scan(/(...)/u) end
  expect ['crüel'.u, 'wörld'.u] do
    [].tap{ |result|
      'crüel wörld'.u.scan(/[[:word:]]+/u) do |word|
        result << word
      end
    }
  end

  expect ['crü'.u, 'el '.u, 'wör'.u] do
    [].tap{ |result|
      'crüel wörld'.u.scan(/.../u) do |word|
        result << word
      end
    }
  end

  expect [['crü'.u], ['el '.u], ['wör'.u]] do
    [].tap{ |result|
      'crüel wörld'.u.scan(/(...)/u) do |word|
        result << word
      end
    }
  end

  expect [true, true] do 'crüel wörld'.u.taint.scan(/[[:word:]]+/u).map(&:tainted?) end
  expect [true, true] do 'crüel wörld'.u.untrust.scan(/[[:word:]]+/u).map(&:untrusted?) end
  expect [true, true] do 'crüel wörld'.u.scan(/[[:word:]]+/u.taint).map(&:tainted?) end
  expect [true, true] do 'crüel wörld'.u.scan(/[[:word:]]+/u.untrust).map(&:untrusted?) end
  expect [true] do 'crüel wörld'.u.taint.scan(' ').map(&:tainted?) end
  expect [true] do 'crüel wörld'.u.untrust.scan(' ').map(&:untrusted?) end
  expect [false] do 'crüel wörld'.u.scan(' '.taint).map(&:tainted?) end
  expect [false] do 'crüel wörld'.u.scan(' '.untrust).map(&:untrusted?) end

  expect [''.u, ''.u, ''.u, ''.u, ''.u, ''.u, ''.u, ''.u, ''.u, ''.u, ''.u, ''.u] do 'crüel wörld'.u.scan(//u) end

  expect ArgumentError do [0x002A, 0x1CED].pack('U*').u.script end
  expect :common do [0x002A].pack('U').u.script end
  expect :inherited do [0x1CED].pack('U').u.script end
  expect :inherited do [0x0670].pack('U').u.script end
  expect :arabic do [0x060D].pack('U').u.script end
  expect :armenian do [0x0559].pack('U').u.script end
  expect :bengali do [0x09CD].pack('U').u.script end
  expect :bopomofo do [0x31B6].pack('U').u.script end
  expect :cherokee do [0x13A2].pack('U').u.script end
  expect :coptic do [0x2CFD].pack('U').u.script end
  expect :cyrillic do [0x0482].pack('U').u.script end
  expect :deseret do [0x10401].pack('U').u.script end
  expect :devanagari do [0x094D].pack('U').u.script end
  expect :ethiopic do [0x1258].pack('U').u.script end
  expect :georgian do [0x10FC].pack('U').u.script end
  expect :gothic do [0x10341].pack('U').u.script end
  expect :greek do [0x0375].pack('U').u.script end
  expect :gujarati do [0x0A83].pack('U').u.script end
  expect :gurmukhi do [0x0A3C].pack('U').u.script end
  expect :han do [0x3005].pack('U').u.script end
  expect :hangul do [0x1100].pack('U').u.script end
  expect :hebrew do [0x05BF].pack('U').u.script end
  expect :hiragana do [0x309F].pack('U').u.script end
  expect :kannada do [0x0CBC].pack('U').u.script end
  expect :katakana do [0x30FF].pack('U').u.script end
  expect :khmer do [0x17DD].pack('U').u.script end
  expect :lao do [0x0EDD].pack('U').u.script end
  expect :latin do [0x0061].pack('U').u.script end
  expect :malayalam do [0x0D3D].pack('U').u.script end
  expect :mongolian do [0x1843].pack('U').u.script end
  expect :myanmar do [0x1031].pack('U').u.script end
  expect :ogham do [0x169C].pack('U').u.script end
  expect :old_italic do [0x10322].pack('U').u.script end
  expect :oriya do [0x0B3C].pack('U').u.script end
  expect :runic do [0x16EF].pack('U').u.script end
  expect :sinhala do [0x0DBD].pack('U').u.script end
  expect :syriac do [0x0711].pack('U').u.script end
  expect :tamil do [0x0B82].pack('U').u.script end
  expect :telugu do [0x0C03].pack('U').u.script end
  expect :thaana do [0x07B1].pack('U').u.script end
  expect :thai do [0x0E31].pack('U').u.script end
  expect :tibetan do [0x0FD4].pack('U').u.script end
  expect :canadian_aboriginal do [0x1400].pack('U').u.script end
  expect :canadian_aboriginal do [0x1401].pack('U').u.script end
  expect :yi do [0xA015].pack('U').u.script end
  expect :tagalog do [0x1700].pack('U').u.script end
  expect :hanunoo do [0x1720].pack('U').u.script end
  expect :buhid do [0x1740].pack('U').u.script end
  expect :tagbanwa do [0x1760].pack('U').u.script end
  expect :braille do [0x2800].pack('U').u.script end
  expect :cypriot do [0x10808].pack('U').u.script end
  expect :limbu do [0x1932].pack('U').u.script end
  expect :osmanya do [0x10480].pack('U').u.script end
  expect :shavian do [0x10450].pack('U').u.script end
  expect :linear_b do [0x10000].pack('U').u.script end
  expect :tai_le do [0x1950].pack('U').u.script end
  expect :ugaritic do [0x1039F].pack('U').u.script end
  expect :new_tai_lue do [0x1980].pack('U').u.script end
  expect :buginese do [0x1A1F].pack('U').u.script end
  expect :glagolitic do [0x2C00].pack('U').u.script end
  expect :tifinagh do [0x2D6F].pack('U').u.script end
  expect :syloti_nagri do [0xA800].pack('U').u.script end
  expect :old_persian do [0x103D0].pack('U').u.script end
  expect :kharoshthi do [0x10A3F].pack('U').u.script end
  expect :unknown do [0x1111111].pack('U').u.script end
  expect :balinese do [0x1B04].pack('U').u.script end
  expect :cuneiform do [0x12000].pack('U').u.script end
  expect :phoenician do [0x10900].pack('U').u.script end
  expect :phags_pa do [0xA840].pack('U').u.script end
  expect :nko do [0x07C0].pack('U').u.script end
  expect :kayah_li do [0xA900].pack('U').u.script end
  expect :lepcha do [0x1C00].pack('U').u.script end
  expect :rejang do [0xA930].pack('U').u.script end
  expect :sundanese do [0x1B80].pack('U').u.script end
  expect :saurashtra do [0xA880].pack('U').u.script end
  expect :cham do [0xAA00].pack('U').u.script end
  expect :ol_chiki do [0x1C50].pack('U').u.script end
  expect :vai do [0xA500].pack('U').u.script end
  expect :carian do [0x102A0].pack('U').u.script end
  expect :lycian do [0x10280].pack('U').u.script end
  expect :lydian do [0x1093F].pack('U').u.script end
  expect :avestan do [0x10B00].pack('U').u.script end
  expect :bamum do [0xA6A0].pack('U').u.script end
  expect :egyptian_hieroglyphs do [0x13000].pack('U').u.script end
  expect :imperial_aramaic do [0x10840].pack('U').u.script end
  expect :inscriptional_pahlavi do [0x10B60].pack('U').u.script end
  expect :inscriptional_parthian do [0x10B40].pack('U').u.script end
  expect :javanese do [0xA980].pack('U').u.script end
  expect :kaithi do [0x11082].pack('U').u.script end
  expect :lisu do [0xA4D0].pack('U').u.script end
  expect :meetei_mayek do [0xABE5].pack('U').u.script end
  expect :old_south_arabian do [0x10A60].pack('U').u.script end
  expect :old_turkic do [0x10C00].pack('U').u.script end
  expect :samaritan do [0x0800].pack('U').u.script end
  expect :tai_tham do [0x1A20].pack('U').u.script end
  expect :tai_viet do [0xAA80].pack('U').u.script end
  expect :batak do [0x1BC0].pack('U').u.script end
  expect :brahmi do [0x11000].pack('U').u.script end
  expect :mandaic do [0x0840].pack('U').u.script end

  expect :aletter do 'a'.u.word_break end

  expect 0 do ''.u.size end
  expect 4 do '1234'.u.size end
  expect 6 do "1234\r\n".u.size end
  expect 7 do "\0011234\r\n".u.size end
  expect 5 do 'hëllö'.u.size end
  expect 6 do "\0hëllö".u.size end
  # TODO: Why not throw an error here?
  expect 11 do "hëllö\0agäin\303".u.size end

  expect true do ''.u.soft_dotted? end
  expect true do 'i'.u.soft_dotted? end
  expect true do 'ij'.u.soft_dotted? end
  expect false do 'a'.u.soft_dotted? end

  expect true do ''.u.space? end
  expect true do ' '.u.space? end
  expect true do " \t\n".u.space? end
  expect false do 'a'.u.space? end

  expect [] do ''.u.split(''.u, 1) end
  expect ['abc'.u] do 'abc'.u.split(''.u, 1) end
  expect [true, true] do 'abc'.u.taint.split(/b/).map(&:tainted?) end
  expect [true, true] do 'abc'.u.untrust.split(/b/).map(&:untrusted?) end
  expect [false, false] do 'abc'.u.split(/b/.taint).map(&:tainted?) end
  expect [false, false] do 'abc'.u.split(/b/.untrust).map(&:untrusted?) end
  expect [true, true] do 'abc'.u.taint.split('b').map(&:tainted?) end
  expect [true, true] do 'abc'.u.untrust.split('b').map(&:untrusted?) end
  expect [false, false] do 'abc'.u.split('b'.taint).map(&:tainted?) end
  expect [false, false] do 'abc'.u.split('b'.untrust).map(&:untrusted?) end

  expect [' ä '.u, ' b '.u, ' c '.u] do ' ä | b | c '.u.split('|'.u) end
  expect ['ä|b|c'.u] do 'ä|b|c'.u.split('|'.u, 1) end
  expect ['ä'.u, 'b|c'.u] do 'ä|b|c'.u.split('|'.u, 2) end
  expect ['ä'.u, 'b'.u, 'c'.u] do 'ä|b|c'.u.split('|'.u, 3) end
  expect ['ä'.u, 'b'.u, 'c'.u, ''.u] do 'ä|b|c|'.u.split('|'.u, -1) end
  expect ['ä'.u, 'b'.u, 'c'.u, ''.u, ''.u] do 'ä|b|c||'.u.split('|'.u, -1) end
  expect ['ä'.u, ''.u, 'b'.u, 'c'.u] do 'ä||b|c|'.u.split('|'.u) end
  expect ['ä'.u, ''.u, 'b'.u, 'c'.u, ''.u] do 'ä||b|c|'.u.split('|'.u, -1) end

  expect [] do
    saved_rs = $;
    $; = nil
    begin
      '  '.u.split
    ensure
      $; = saved_rs
    end
  end

  expect [''.u] do
    saved_rs = $;
    $; = nil
    begin
      '  '.u.split(nil, -1)
    ensure
      $; = saved_rs
    end
  end

  expect ['ä'.u, 'b c'.u] do
    saved_rs = $;
    $; = nil
    begin
      'ä b c'.u.split(nil, 2)
    ensure
      $; = saved_rs
    end
  end

  # TODO: Test this with limits
  expect ['ä'.u, 'b'.u, 'c'.u] do
    saved_rs = $;
    $; = nil
    begin
      " ä  b\t c ".u.split
    ensure
      $; = saved_rs
    end
  end

  expect ['ä'.u, 'b'.u, 'c'.u] do
    saved_rs = $;
    $; = nil
    begin
      " ä  b\t c".u.split
    ensure
      $; = saved_rs
    end
  end

  expect ['ä'.u, 'b'.u, 'c'.u] do
    saved_rs = $;
    $; = nil
    begin
      " ä  b\t c ".u.split(' ')
    ensure
      $; = saved_rs
    end
  end

  expect [] do ''.split(//u, 1) end
  expect ['ä'.u, 'b'.u, 'c'.u] do 'äXXbXXcXX'.u.split(/X./u) end
  expect ['ä'.u, 'b'.u, 'c'.u] do 'äbc'.u.split(//u) end
  expect ['b'.u, 'c'.u] do 'bäc'.u.split(/ä?/u) end

  expect 'äbc'.u do 'äääbbbbccc'.u.squeeze end
  expect 'ää bb cc'.u do 'ää   bb   cc'.u.squeeze(' ') end
  expect 'BxTÿWz'.u do 'BxTÿÿÿWzzz'.u.squeeze('a-zä-ÿ') end
  expect result.tainted? do 'abc'.u.taint.squeeze end
  expect result.untrusted? do 'abc'.u.untrust.squeeze end
  expect result.not.tainted? do 'abc'.u.squeeze('b'.taint) end
  expect result.not.untrusted? do 'abc'.u.squeeze('b'.untrust) end

  expect result.to.start_with?('a') do 'abc'.u end
  expect result.not.to.start_with?('b') do 'abc'.u end
  expect result.to.start_with?('ä') do 'äbc'.u end
  expect result.not.to.start_with?('bc') do 'äbc'.u end
  expect result.to.start_with?('a', 'ä') do 'äbc'.u end
  expect result.not.to.start_with? do 'äbc'.u end

  # TODO: Add tests for Unicode whitespace characters
  expect 'あ'.u do 'あ'.u.strip end
  expect 'あ'.u do '     あ'.u.strip end
  expect 'あ'.u do 'あ     '.u.strip end
  expect 'あ'.u do '     あ     '.u.strip end
  expect result.tainted? do 'あ'.u.taint.strip end
  expect result.untrusted? do 'あ'.u.untrust.strip end

  expect 1480 do '1480ft/sec'.u.to_i end
  expect 0 do 'speed of sound in water @20C = 1480ft/sec'.u.to_i end
  expect 0 do ' 0'.u.to_i end
  expect 0 do '+0'.u.to_i end
  expect 0 do '-0'.u.to_i end
  expect 0 do '--0'.u.to_i end
  expect 16 do '0x10'.u.to_i(0) end
  expect 16 do '0X10'.u.to_i(0) end
  expect 2 do '0b10'.u.to_i(0) end
  expect 2 do '0B10'.u.to_i(0) end
  expect 8 do '0o10'.u.to_i(0) end
  expect 8 do '0O10'.u.to_i(0) end
  expect 10 do '0d10'.u.to_i(0) end
  expect 10 do '0D10'.u.to_i(0) end
  expect 8 do '010'.u.to_i(0) end
  expect ArgumentError do '010'.u.to_i(-10) end
  expect ArgumentError do '0'.u.to_i(1) end
  expect ArgumentError do '0'.u.to_i(37) end
  expect 0 do 'z'.u.to_i(10) end
  expect 35 do 'z'.u.to_i(36) end
  expect 12 do '1_2'.u.to_i(10) end
  expect 0x4000_0000 do '1073741824'.u.to_i(10) end
  expect 0x4000_0000_0000_0000 do '4611686018427387904'.u.to_i(10) end
  expect 1 do '1__2'.u.to_i(10) end
  expect 1 do '1_z'.u.to_i(10) end
  expect 1 do '١'.u.to_i end

  expect :koala do 'koala'.u.to_sym end
  expect :'köälä' do 'köälä'.u.to_sym end

  expect 'hïppö' do 'hëllö'.u.tr('ël', 'ïp') end
  expect '*ë**ö' do 'hëllö'.u.tr('^aëiöu', '*') end
  expect 'hal' do 'ibm'.u.tr('b-z', 'a-z') end
  expect 'hal' do 'hal'.u.tr('a-z', 'a-z') end
  expect true do a = 'hal'.u; a.tr('a-z', 'a-z').object_id == a.object_id end
  expect result.tainted? do 'abc'.u.taint.tr('a', 'b') end
  expect result.untrusted? do 'abc'.u.untrust.tr('a', 'b') end
  expect result.not.tainted? do 'abc'.u.tr('a'.taint, 'b') end
  expect result.not.untrusted? do 'abc'.u.tr('a'.untrust, 'b') end
  expect result.not.tainted? do 'abc'.u.tr('a', 'b'.taint) end
  expect result.not.untrusted? do 'abc'.u.tr('a', 'b'.untrust) end

  expect :letter_uppercase do 'A'.u.general_category end
  expect :punctuation_other do '.'.u.general_category end
  expect :symbol_currency do '$'.u.general_category end
  expect :separator_space do ' '.u.general_category end

  expect 'HËLLÖ'.u do 'hëlLÖ'.u.upcase end
  expect 'HËLLÖ'.u do 'hëllö'.u.upcase end
  expect 'HËLLÖ'.u do 'HËLLÖ'.u.upcase end
  expect "ABC\0DËF".u do "abc\0dëF".u.upcase end

  expect "I\xcc\x87".u do "i\xcc\x87".u.upcase end
  expect 'I'.u do "i\xcc\x87".u.upcase('lt') end
  expect "K\xcc\x87".u do "k\xcc\x87".u.upcase('lt') end

  expect "A\xcc\x81Ι".u do "a\xcd\x85\xcc\x81".u.upcase end
  expect 'I'.u do 'i'.u.upcase end
  expect 'İ'.u do 'i'.u.upcase('tr') end

  expect result.tainted? do 'a'.u.taint.upcase end
  expect result.untrusted? do 'a'.u.untrust.upcase end

  expect false do 'i'.u.title? end
  expect false do 'I'.u.title? end
  expect false do 'Ǳ'.u.title? end
  expect true do 'ǲ'.u.title? end

  expect false do 'i'.u.upper? end
  expect false do 'i'.u.upper?('lt') end
  expect false do 'i'.u.upper?('tr') end
  expect true do 'I'.u.upper? end
  expect true do 'I'.u.upper?('lt') end
  expect true do 'I'.u.upper?('tr') end

  expect true do 'äbc'.u.valid_encoding? end
  expect true do "äbc\0def".u.valid_encoding? end
  expect false do "\xc3bc".u.valid_encoding? end

  expect true do ''.u.wide? end
  expect true do '豈'.u.wide? end
  expect true do '豈豈'.u.wide? end
  expect false do 'a'.u.wide? end

  expect true do ''.u.wide_cjk? end
  expect true do '豈'.u.wide_cjk? end
  expect true do '豈豈'.u.wide_cjk? end
  expect true do '豈♣'.u.wide_cjk? end
  expect false do 'a'.u.wide_cjk? end

  expect 0 do ''.u.width end
  expect 1 do 'a'.u.width end
  expect 1 do "a\xcc\x87".u.width end
  expect 2 do '豈'.u.width end
  expect 3 do 'a豈'.u.width end

  expect true do ''.u.xdigit? end
  expect true do '0'.u.xdigit? end
  expect true do '0a'.u.xdigit? end
  expect false do 'g'.u.xdigit? end

  expect true do ''.u.zero_width? end
  expect true do [0x200b].pack('U').u.zero_width? end
  expect true do [0x200b, 0x1160].pack('U*').u.zero_width? end
  expect false do 'a'.u.zero_width? end

  expect ''.u do "\0".u.collate_key end
  expect 'äbcdëf'.u do 'äbcdëf'.u.collate_key end
  expect 'äbcdëf'.u do "äbc\0dëf".u.collate_key end
  expect result.tainted? do ''.u.taint.collate_key end
  expect result.untrusted? do ''.u.untrust.collate_key end

  if defined? ::Encoding
    expect Encoding::ASCII_8BIT do ''.u.b.encoding end
  end
end
