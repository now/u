# -*- coding: utf-8 -*-

Expectations do
  expect ''.u[0, -2].to.be.nil?
  expect ''.u[0, -1].to.be.nil?

  expect '' do ''.u[0, 0] end
  expect '' do ''.u[0, 1] end
  expect '' do ''.u[0, 2] end

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

  expect 'hë' do 'hëllö'.u[0, 2] end
  expect 'lö' do 'hëllö'.u[3, 2] end

  expect 0 do ''.u.count('whatever') end
  expect 1 do 'helo'.u.count('l') end
  expect 1 do 'helo'.u.count('wrld') end
  expect 2 do 'helo'.u.count('world') end
  expect 3 do 'hello'.u.count('world') end

  expect ''.u.delete('whatever').to.be.empty?
  expect 'hëll' do 'hëllö'.u.delete('ö') end

  expect 0 do
    i = 0
    ''.u.each_char{ i += 1 }
    i
  end

  expect %w[h ë l l ö] do
    [].tap{ |cs| 'hëllö'.u.each_char{ |c| cs << c } }
  end

  expect 0 do ''.u.index('') end
  expect nil do ''.u.index('', 1) end
  expect nil do ''.u.index('', -1) end
  expect 0 do 'hëllö'.u.index('hë') end
  expect 3 do 'hëllö'.u.index('lö') end
  expect 3 do 'hëllö'.u.index('lö', 3) end

  expect '' do ''.u.insert(0, '') end
  expect IndexError do ''.u.insert(1, '') end
  expect 'äbc' do ''.u.insert(0, 'äbc') end
  expect 'hëöll' do 'hëö'.u.insert(3, 'll') end
  expect 'hëöll' do 'hëö'.u.insert(-1, 'll') end
  expect 'hëllö' do 'hëö'.u.insert(2, 'll') end
  expect 'hëllö' do 'hëö'.u.insert(-2, 'll') end
  expect 'llhëö' do 'hëö'.u.insert(0, 'll') end
  #expect 'llhëö' do 'hëö'.u.insert(-4, 'll') end

  expect 0 do ''.u.length end
  expect 5 do 'hëllö'.u.length end
  expect 11 do "hëllö\0agäin".u.length end
  # TODO: Why not throw an error here?
  expect 11 do "hëllö\0agäin\303".u.length end

  expect 0 do ''.u.rindex('') end
  expect 0 do 'hëllö'.u.rindex('hë') end
  expect 3 do 'hëllö'.u.rindex('lö') end
  expect 3 do 'hëllö'.u.rindex('lö', 3) end
  expect 5 do 'hëllölö'.u.rindex('lö') end
  expect 5 do 'hëllölö'.u.rindex('lö', 5) end
  expect 3 do 'hëllölö'.u.rindex('lö', 4) end

  expect ''.u.squeeze.to.be.empty?
  expect 'hëlö' do 'hëllö'.u.squeeze end

  expect 0 do ''.u.to_i end
  expect 0 do ''.u.to_i(0) end
  expect ArgumentError do ''.u.to_i(-1) end
  expect ArgumentError do ''.u.to_i(1) end
  expect ArgumentError do ''.u.to_i(37) end
  expect 1 do '1'.u.to_i end
  expect 1 do '1'.u.to_i(2) end
  expect 1 do '١'.u.to_i end

  expect ''.u.tr('abc', 'def').to.be.empty?
  expect 'abcde' do 'äbcdë'.u.tr('äë', 'ae') end
  expect 'ëëëëë' do 'äbcdë'.u.tr('a-zäë', 'ë') end
  expect 'ëëëëë' do 'aaaaa'.u.tr('a', 'ä-ë') end

  expect "ABC\0DËF" do "abc\0dëF".u.upcase end
end
