# -*- coding: utf-8 -*-

Expectations do
  expect ''.u[0, -2].to.be.nil?
  expect ''.u[0, -1].to.be.nil?

  expect ''.u do ''.u[0, 0] end
  expect ''.u do ''.u[0, 1] end
  expect ''.u do ''.u[0, 2] end

  expect ''.u[-1, -2].to.be.nil?
  expect ''.u[-1, -1].to.be.nil?
  expect ''.u[-1, 0].to.be.nil?
  expect ''.u[-1, 1].to.be.nil?
  expect ''.u[-1, 2].to.be.nil?
  expect ''.u[1, -2].to.be.nil?
  expect ''.u[1, -1].to.be.nil?
  expect ''.u[1, 0].to.be.nil?
  expect ''.u[1, 1].to.be.nil?
  expect ''.u[1, 2].to.be.nil?

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
  expect nil do 'hëllö'.u['other'.u] end

  expect 'hë'.u do 'hëllö'.u[/(..)(..)/u, 1] end
  expect 'll'.u do 'hëllö'.u[/(..)(..)/u, 2] end
  expect nil do 'hëllö'.u[/(..)(..)/u, 3] end
  expect 'll'.u do 'hëllö'.u[/(..)(..)/u, -1] end
  expect 'hë'.u do 'hëllö'.u[/(..)(..)/u, -2] end
  expect nil do 'hëllö'.u[/(..)(..)/u, -3] end

  expect 'l'.u do 'hëllö'.u[stub(:to_int => 2)] end

  expect ArgumentError do 'hëllö'.u[] end

  # TODO: Should <=>, ==, ===, eql?, and casecmp use collation or not?  When
  # should collation be used?  #collate and #collation_key?

  expect 1 do 'あB'.u.casecmp('あa') end
  expect 1 do 'あB'.u.casecmp('あa'.u) end

  expect 'hëllö'.u do 'hëllö'.u.center(4) end
  expect '   hëllö   '.u do 'hëllö'.u.center(11) end
  expect 'ababaababa'.u do ''.u.center(10, 'ab') end
  expect 'ababaababab'.u do ''.u.center(11, 'ab') end
  # TODO: Adjust this to LONG_MAX in Ruby
#  expect ArgumentError do ''.u.center(9223372036854775807) end

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

  expect 'hell'.u do 'hellö'.u.chop end
  expect 'hellö'.u do "hellö\r\n".u.chop end
  expect "hellö\n".u do "hellö\n\r".u.chop end
  expect ''.u do ''.u.chop end
  expect ''.u do "\r\n".u.chop end

  expect 5 do 'hëllö wörld'.u.count('lö') end
  expect 3 do 'hëllö wörld'.u.count('l', 'lö') end
  expect 2 do 'hëllö wörld'.u.count('lö', 'ö') end
  expect 4 do 'hëllö wörld'.u.count('hëllö', '^l') end
  expect 3 do 'hëllö wörld'.u.count('ej-m') end
  expect 0 do 'y'.u.count('a\\-z') end
  expect 5 do 'abcあいう'.u.count('^a') end
  expect 5 do 'abcあいう'.u.count('^あ') end
  expect 2 do 'abcあいう'.u.count('a-z', '^a') end
  expect ArgumentError do 'föö'.u.count end

  expect 'hë wrd'.u do 'hëllö wörld'.u.delete('lö') end
  expect 'hëö wörd'.u do 'hëllö wörld'.u.delete('l', 'lö') end
  expect 'hëll wrld'.u do 'hëllö wörld'.u.delete('lö', 'ö') end
  expect 'hëll wrld'.u do 'hëllö wörld'.u.delete('aëiöu', '^ë') end
  expect 'hö wörd'.u do 'hëllö wörld'.u.delete('ëj-m') end
  expect 'a'.u do 'aā'.u.delete('ā') end
  expect 'a'.u do 'abcあいう'.u.delete('^a') end
  expect 'bcあいう'.u do 'abcあいう'.u.delete('a') end
  expect 'あ'.u do 'abcあいう'.u.delete('^あ') end
  expect ArgumentError do 'föö'.u.delete end

  expect 'hëllö'.u do 'hëlLÖ'.u.downcase end
  expect 'hëllö'.u do 'hëllö'.u.downcase end
  expect 'hëllö'.u do 'HËLLÖ'.u.downcase end
  expect "abc\0dëf".u do "ABC\0DËF".u.downcase end

  expect %w[h ë l l ö] do
    'hëllö'.u.chars.entries
  end

  expect "abc\0ss".u do "abc\0ß".u.foldcase end

  expect 255 do '0xff'.u.hex end
  expect(-255) do '-0xff'.u.hex end
  expect 255 do 'ff'.u.hex end
  expect(-255) do '-ff'.u.hex end
  expect 0 do '-ralph'.u.hex end
  expect(-15) do '-fred'.u.hex end
  expect 15 do 'fred'.u.hex end
  # TODO: Add tests for Unicode digit values

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

  expect 0 do ''.u.length end
  expect 4 do '1234'.u.length end
  expect 6 do "1234\r\n".u.length end
  expect 7 do "\0011234\r\n".u.length end
  expect 5 do 'hëllö'.u.length end
  expect 6 do "\0hëllö".u.length end
  # TODO: Why not throw an error here?
  expect 11 do "hëllö\0agäin\303".u.length end

  # TODO: Add tests for Unicode whitespace characters
  expect 'あ'.u do 'あ'.u.lstrip end
  expect 'あ'.u do '     あ'.u.lstrip end
  expect 'あ     '.u do 'あ     '.u.lstrip end

  # TODO: Add tests for Unicode digit values
  expect 255 do '0377'.u.oct end
  expect 255 do '377'.u.oct end
  expect(-255) do '-0377'.u.oct end
  expect(-255) do '-377'.u.oct end
  expect 0 do '00'.u.oct end
  expect 24 do '030OO'.u.oct end

  expect 'ateb'.u do 'beta'.u.reverse end
  expect 'madamImadam'.u do 'madamImadam'.u.reverse end
  expect "alpha\0beta".u do "ateb\0ahpla".u.reverse end

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

  expect 'äbc'.u do 'äääbbbbccc'.u.squeeze end
  expect 'ää bb cc'.u do 'ää   bb   cc'.u.squeeze(' ') end
  expect 'BxTÿWz'.u do 'BxTÿÿÿWzzz'.u.squeeze('a-zä-ÿ') end

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

  # TODO: Add tests for Unicode whitespace characters
  expect 'あ'.u do 'あ'.u.strip end
  expect 'あ'.u do '     あ'.u.strip end
  expect 'あ'.u do 'あ     '.u.strip end
  expect 'あ'.u do '     あ     '.u.strip end

  expect 'hïppö' do 'hëllö'.u.tr('ël', 'ïp') end
  expect '*ë**ö' do 'hëllö'.u.tr('^aëiöu', '*') end
  expect 'hal' do 'ibm'.u.tr('b-z', 'a-z') end
  expect 'hal' do 'hal'.u.tr('a-z', 'a-z') end
  expect true do a = 'hal'.u; a.tr('a-z', 'a-z').object_id == a.object_id end

  expect 'HËLLÖ'.u do 'hëlLÖ'.u.upcase end
  expect 'HËLLÖ'.u do 'hëllö'.u.upcase end
  expect 'HËLLÖ'.u do 'HËLLÖ'.u.upcase end
  expect "ABC\0DËF".u do "abc\0dëF".u.upcase end
end
