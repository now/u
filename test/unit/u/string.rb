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
  expect 'hëllo' do 'hëllö'.u.delete('ö') end
end
