# -*- coding: utf-8 -*-

untrust = Object.respond_to?(:untrust)

Expectations do
  expect U::String do ''.u end
  expect U::String.new('abc') do 'abc'.u end
  expect result.tainted? do ''.taint.u end
  expect result.untrusted? do ''.untrust.u end if untrust
end
