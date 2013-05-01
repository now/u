# -*- coding: utf-8 -*-

untrust = Object.respond_to?(:untrust)

Expectations do
  expect U::Buffer do U::Buffer.new end
  expect U::Buffer do U::Buffer.new(128) end
  expect U::Buffer do U::Buffer.new(nil) end
  expect TypeError do U::Buffer.new('abc') end

  expect U::Buffer.new(5).append('abc') do |buffer| buffer.dup end
  expect false do
    original = U::Buffer.new(5).append('abc')
    original.dup.object_id == original.object_id
  end
  expect false do
    original = U::Buffer.new(5).append('abc')
    original.dup.append('de').object_id == original.object_id
  end

  expect ArgumentError.new('wrong number of arguments (0 for at least 1)') do U::Buffer.new.append end
  expect 'abcde'.u do U::Buffer.new.append('abc', 'de').to_u end
  expect 'abcde'.u do (U::Buffer.new << 'abc' << 'de').to_u end
  expect "abc\0def".u do U::Buffer.new.append('abc', 0, 'def'.u).to_u end
  expect result.tainted? do U::Buffer.new.taint.to_u end
  expect result.tainted? do U::Buffer.new.append(U::Buffer.new.taint).to_u end
  expect result.tainted? do U::Buffer.new.append(''.taint).to_u end
  expect result.untrusted? do U::Buffer.new.untrust.to_u end if untrust
  expect result.untrusted? do U::Buffer.new.append(U::Buffer.new.untrust).to_u end if untrust
  expect result.untrusted? do U::Buffer.new.append(''.untrust).to_u end if untrust

  expect 'äbc'.u do U::Buffer.new.append_format('%cbc'.u, 'ä').to_u end
  expect result.tainted? do U::Buffer.new.append_format('abc'.taint).to_u end
  expect result.tainted? do U::Buffer.new.append_format('%s', 'abc'.taint).to_u end
  expect result.tainted? do U::Buffer.new.append_format('%p', 'abc'.taint).to_u end

  expect ''.u do U::Buffer.new.to_u! end
  expect 'äbc'.u do U::Buffer.new.append('äbc').to_u! end
  expect ''.u do U::Buffer.new.append('äbc').tap(&:to_u!).to_u! end

  expect '#<U::Buffer äbc>' do U::Buffer.new.append('äbc'.u).inspect end
  expect '#<U::Buffer äbcdëwvxÿz>' do U::Buffer.new.append('äbcdëwvxÿz'.u).inspect end
  expect '#<U::Buffer äbcdëfwvxÿz>' do U::Buffer.new.append('äbcdëfwvxÿz'.u).inspect end
  expect '#<U::Buffer äbcdë…wvxÿz>' do U::Buffer.new.append('äbcdëfgwvxÿz'.u).inspect end

  expect 3 do U::Buffer.new.append('äbc'.u).length end
  expect 3 do U::Buffer.new.append('äbc'.u).size end
  expect 4 do U::Buffer.new.append('äbc'.u).bytesize end
  expect 4 do U::Buffer.new.append('あbc'.u).width end

  expect result.tainted? do U::Buffer.new.taint.to_s end
end
