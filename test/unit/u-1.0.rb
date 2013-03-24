# -*- coding: utf-8 -*-

Expectations do
  expect result.tainted? do ''.taint.u end
  expect result.untrusted? do ''.untrust.u end
end
