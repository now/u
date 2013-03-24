# -*- coding: utf-8 -*-

Expectations do
  expect ArgumentError.new('wrong number of arguments (0 for at least 1)') do U::Buffer.new.append end
  expect 'abcde'.u do U::Buffer.new.append('abc', 'de').to_u end
  expect 'abcde'.u do (U::Buffer.new << 'abc' << 'de').to_u end

  expect 'äbc'.u do U::Buffer.new.append_format('%cbc'.u, 'ä').to_u end

  expect U::Buffer.new(5).append('abc') do |buffer| buffer.dup end
  expect false do
    original = U::Buffer.new(5).append('abc')
    original.dup.object_id == original.object_id
  end
  expect false do
    original = U::Buffer.new(5).append('abc')
    original.dup.append('de') == original.object_id
  end

  expect "abc\0def".u do U::Buffer.new.append('abc', 0, 'def'.u).to_u end

  expect '#<U::Buffer äbc>' do U::Buffer.new.append('äbc'.u).inspect end
  expect '#<U::Buffer äbcdëwvxÿz>' do U::Buffer.new.append('äbcdëwvxÿz'.u).inspect end
  expect '#<U::Buffer äbcdëfwvxÿz>' do U::Buffer.new.append('äbcdëfwvxÿz'.u).inspect end
  expect '#<U::Buffer äbcdë…wvxÿz>' do U::Buffer.new.append('äbcdëfgwvxÿz'.u).inspect end

  expect result.tainted? do U::Buffer.new.taint.to_s end
  expect result.tainted? do U::Buffer.new.taint.to_u end
end
