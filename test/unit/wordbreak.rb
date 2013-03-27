# -*- coding: utf-8 -*-
# Automatically generated, so don’t edit!

Expectations do
  expect ["\x01".u, "\x01".u] do "\x01\x01".u.words.to_a end
  expect ["\x01\u{308}".u, "\x01".u] do "\x01\u{308}\x01".u.words.to_a end
  expect ["\x01".u, "\r".u] do "\x01\r".u.words.to_a end
  expect ["\x01\u{308}".u, "\r".u] do "\x01\u{308}\r".u.words.to_a end
  expect ["\x01".u, "\n".u] do "\x01\n".u.words.to_a end
  expect ["\x01\u{308}".u, "\n".u] do "\x01\u{308}\n".u.words.to_a end
  expect ["\x01".u, "\v".u] do "\x01\v".u.words.to_a end
  expect ["\x01\u{308}".u, "\v".u] do "\x01\u{308}\v".u.words.to_a end
  expect ["\x01".u, "\u{3031}".u] do "\x01\u{3031}".u.words.to_a end
  expect ["\x01\u{308}".u, "\u{3031}".u] do "\x01\u{308}\u{3031}".u.words.to_a end
  expect ["\x01".u, "A".u] do "\x01A".u.words.to_a end
  expect ["\x01\u{308}".u, "A".u] do "\x01\u{308}A".u.words.to_a end
  expect ["\x01".u, ":".u] do "\x01:".u.words.to_a end
  expect ["\x01\u{308}".u, ":".u] do "\x01\u{308}:".u.words.to_a end
  expect ["\x01".u, ",".u] do "\x01,".u.words.to_a end
  expect ["\x01\u{308}".u, ",".u] do "\x01\u{308},".u.words.to_a end
  expect ["\x01".u, "'".u] do "\x01'".u.words.to_a end
  expect ["\x01\u{308}".u, "'".u] do "\x01\u{308}'".u.words.to_a end
  expect ["\x01".u, "0".u] do "\x010".u.words.to_a end
  expect ["\x01\u{308}".u, "0".u] do "\x01\u{308}0".u.words.to_a end
  expect ["\x01".u, "_".u] do "\x01_".u.words.to_a end
  expect ["\x01\u{308}".u, "_".u] do "\x01\u{308}_".u.words.to_a end
  expect ["\x01".u, "\u{1f1e6}".u] do "\x01\u{1f1e6}".u.words.to_a end
  expect ["\x01\u{308}".u, "\u{1f1e6}".u] do "\x01\u{308}\u{1f1e6}".u.words.to_a end
  expect ["\x01\u{ad}".u] do "\x01\u{ad}".u.words.to_a end
  expect ["\x01\u{308}\u{ad}".u] do "\x01\u{308}\u{ad}".u.words.to_a end
  expect ["\x01\u{300}".u] do "\x01\u{300}".u.words.to_a end
  expect ["\x01\u{308}\u{300}".u] do "\x01\u{308}\u{300}".u.words.to_a end
  expect ["\x01".u, "a\u{2060}".u] do "\x01a\u{2060}".u.words.to_a end
  expect ["\x01\u{308}".u, "a\u{2060}".u] do "\x01\u{308}a\u{2060}".u.words.to_a end
  expect ["\x01".u, "a".u, ":".u] do "\x01a:".u.words.to_a end
  expect ["\x01\u{308}".u, "a".u, ":".u] do "\x01\u{308}a:".u.words.to_a end
  expect ["\x01".u, "a".u, "'".u] do "\x01a'".u.words.to_a end
  expect ["\x01\u{308}".u, "a".u, "'".u] do "\x01\u{308}a'".u.words.to_a end
  expect ["\x01".u, "a".u, "'\u{2060}".u] do "\x01a'\u{2060}".u.words.to_a end
  expect ["\x01\u{308}".u, "a".u, "'\u{2060}".u] do "\x01\u{308}a'\u{2060}".u.words.to_a end
  expect ["\x01".u, "a".u, ",".u] do "\x01a,".u.words.to_a end
  expect ["\x01\u{308}".u, "a".u, ",".u] do "\x01\u{308}a,".u.words.to_a end
  expect ["\x01".u, "1".u, ":".u] do "\x011:".u.words.to_a end
  expect ["\x01\u{308}".u, "1".u, ":".u] do "\x01\u{308}1:".u.words.to_a end
  expect ["\x01".u, "1".u, "'".u] do "\x011'".u.words.to_a end
  expect ["\x01\u{308}".u, "1".u, "'".u] do "\x01\u{308}1'".u.words.to_a end
  expect ["\x01".u, "1".u, ",".u] do "\x011,".u.words.to_a end
  expect ["\x01\u{308}".u, "1".u, ",".u] do "\x01\u{308}1,".u.words.to_a end
  expect ["\x01".u, "1".u, ".\u{2060}".u] do "\x011.\u{2060}".u.words.to_a end
  expect ["\x01\u{308}".u, "1".u, ".\u{2060}".u] do "\x01\u{308}1.\u{2060}".u.words.to_a end
  expect ["\r".u, "\x01".u] do "\r\x01".u.words.to_a end
  expect ["\r".u, "\u{308}".u, "\x01".u] do "\r\u{308}\x01".u.words.to_a end
  expect ["\r".u, "\r".u] do "\r\r".u.words.to_a end
  expect ["\r".u, "\u{308}".u, "\r".u] do "\r\u{308}\r".u.words.to_a end
  expect ["\r\n".u] do "\r\n".u.words.to_a end
  expect ["\r".u, "\u{308}".u, "\n".u] do "\r\u{308}\n".u.words.to_a end
  expect ["\r".u, "\v".u] do "\r\v".u.words.to_a end
  expect ["\r".u, "\u{308}".u, "\v".u] do "\r\u{308}\v".u.words.to_a end
  expect ["\r".u, "\u{3031}".u] do "\r\u{3031}".u.words.to_a end
  expect ["\r".u, "\u{308}".u, "\u{3031}".u] do "\r\u{308}\u{3031}".u.words.to_a end
  expect ["\r".u, "A".u] do "\rA".u.words.to_a end
  expect ["\r".u, "\u{308}".u, "A".u] do "\r\u{308}A".u.words.to_a end
  expect ["\r".u, ":".u] do "\r:".u.words.to_a end
  expect ["\r".u, "\u{308}".u, ":".u] do "\r\u{308}:".u.words.to_a end
  expect ["\r".u, ",".u] do "\r,".u.words.to_a end
  expect ["\r".u, "\u{308}".u, ",".u] do "\r\u{308},".u.words.to_a end
  expect ["\r".u, "'".u] do "\r'".u.words.to_a end
  expect ["\r".u, "\u{308}".u, "'".u] do "\r\u{308}'".u.words.to_a end
  expect ["\r".u, "0".u] do "\r0".u.words.to_a end
  expect ["\r".u, "\u{308}".u, "0".u] do "\r\u{308}0".u.words.to_a end
  expect ["\r".u, "_".u] do "\r_".u.words.to_a end
  expect ["\r".u, "\u{308}".u, "_".u] do "\r\u{308}_".u.words.to_a end
  expect ["\r".u, "\u{1f1e6}".u] do "\r\u{1f1e6}".u.words.to_a end
  expect ["\r".u, "\u{308}".u, "\u{1f1e6}".u] do "\r\u{308}\u{1f1e6}".u.words.to_a end
  expect ["\r".u, "\u{ad}".u] do "\r\u{ad}".u.words.to_a end
  expect ["\r".u, "\u{308}\u{ad}".u] do "\r\u{308}\u{ad}".u.words.to_a end
  expect ["\r".u, "\u{300}".u] do "\r\u{300}".u.words.to_a end
  expect ["\r".u, "\u{308}\u{300}".u] do "\r\u{308}\u{300}".u.words.to_a end
  expect ["\r".u, "a\u{2060}".u] do "\ra\u{2060}".u.words.to_a end
  expect ["\r".u, "\u{308}".u, "a\u{2060}".u] do "\r\u{308}a\u{2060}".u.words.to_a end
  expect ["\r".u, "a".u, ":".u] do "\ra:".u.words.to_a end
  expect ["\r".u, "\u{308}".u, "a".u, ":".u] do "\r\u{308}a:".u.words.to_a end
  expect ["\r".u, "a".u, "'".u] do "\ra'".u.words.to_a end
  expect ["\r".u, "\u{308}".u, "a".u, "'".u] do "\r\u{308}a'".u.words.to_a end
  expect ["\r".u, "a".u, "'\u{2060}".u] do "\ra'\u{2060}".u.words.to_a end
  expect ["\r".u, "\u{308}".u, "a".u, "'\u{2060}".u] do "\r\u{308}a'\u{2060}".u.words.to_a end
  expect ["\r".u, "a".u, ",".u] do "\ra,".u.words.to_a end
  expect ["\r".u, "\u{308}".u, "a".u, ",".u] do "\r\u{308}a,".u.words.to_a end
  expect ["\r".u, "1".u, ":".u] do "\r1:".u.words.to_a end
  expect ["\r".u, "\u{308}".u, "1".u, ":".u] do "\r\u{308}1:".u.words.to_a end
  expect ["\r".u, "1".u, "'".u] do "\r1'".u.words.to_a end
  expect ["\r".u, "\u{308}".u, "1".u, "'".u] do "\r\u{308}1'".u.words.to_a end
  expect ["\r".u, "1".u, ",".u] do "\r1,".u.words.to_a end
  expect ["\r".u, "\u{308}".u, "1".u, ",".u] do "\r\u{308}1,".u.words.to_a end
  expect ["\r".u, "1".u, ".\u{2060}".u] do "\r1.\u{2060}".u.words.to_a end
  expect ["\r".u, "\u{308}".u, "1".u, ".\u{2060}".u] do "\r\u{308}1.\u{2060}".u.words.to_a end
  expect ["\n".u, "\x01".u] do "\n\x01".u.words.to_a end
  expect ["\n".u, "\u{308}".u, "\x01".u] do "\n\u{308}\x01".u.words.to_a end
  expect ["\n".u, "\r".u] do "\n\r".u.words.to_a end
  expect ["\n".u, "\u{308}".u, "\r".u] do "\n\u{308}\r".u.words.to_a end
  expect ["\n".u, "\n".u] do "\n\n".u.words.to_a end
  expect ["\n".u, "\u{308}".u, "\n".u] do "\n\u{308}\n".u.words.to_a end
  expect ["\n".u, "\v".u] do "\n\v".u.words.to_a end
  expect ["\n".u, "\u{308}".u, "\v".u] do "\n\u{308}\v".u.words.to_a end
  expect ["\n".u, "\u{3031}".u] do "\n\u{3031}".u.words.to_a end
  expect ["\n".u, "\u{308}".u, "\u{3031}".u] do "\n\u{308}\u{3031}".u.words.to_a end
  expect ["\n".u, "A".u] do "\nA".u.words.to_a end
  expect ["\n".u, "\u{308}".u, "A".u] do "\n\u{308}A".u.words.to_a end
  expect ["\n".u, ":".u] do "\n:".u.words.to_a end
  expect ["\n".u, "\u{308}".u, ":".u] do "\n\u{308}:".u.words.to_a end
  expect ["\n".u, ",".u] do "\n,".u.words.to_a end
  expect ["\n".u, "\u{308}".u, ",".u] do "\n\u{308},".u.words.to_a end
  expect ["\n".u, "'".u] do "\n'".u.words.to_a end
  expect ["\n".u, "\u{308}".u, "'".u] do "\n\u{308}'".u.words.to_a end
  expect ["\n".u, "0".u] do "\n0".u.words.to_a end
  expect ["\n".u, "\u{308}".u, "0".u] do "\n\u{308}0".u.words.to_a end
  expect ["\n".u, "_".u] do "\n_".u.words.to_a end
  expect ["\n".u, "\u{308}".u, "_".u] do "\n\u{308}_".u.words.to_a end
  expect ["\n".u, "\u{1f1e6}".u] do "\n\u{1f1e6}".u.words.to_a end
  expect ["\n".u, "\u{308}".u, "\u{1f1e6}".u] do "\n\u{308}\u{1f1e6}".u.words.to_a end
  expect ["\n".u, "\u{ad}".u] do "\n\u{ad}".u.words.to_a end
  expect ["\n".u, "\u{308}\u{ad}".u] do "\n\u{308}\u{ad}".u.words.to_a end
  expect ["\n".u, "\u{300}".u] do "\n\u{300}".u.words.to_a end
  expect ["\n".u, "\u{308}\u{300}".u] do "\n\u{308}\u{300}".u.words.to_a end
  expect ["\n".u, "a\u{2060}".u] do "\na\u{2060}".u.words.to_a end
  expect ["\n".u, "\u{308}".u, "a\u{2060}".u] do "\n\u{308}a\u{2060}".u.words.to_a end
  expect ["\n".u, "a".u, ":".u] do "\na:".u.words.to_a end
  expect ["\n".u, "\u{308}".u, "a".u, ":".u] do "\n\u{308}a:".u.words.to_a end
  expect ["\n".u, "a".u, "'".u] do "\na'".u.words.to_a end
  expect ["\n".u, "\u{308}".u, "a".u, "'".u] do "\n\u{308}a'".u.words.to_a end
  expect ["\n".u, "a".u, "'\u{2060}".u] do "\na'\u{2060}".u.words.to_a end
  expect ["\n".u, "\u{308}".u, "a".u, "'\u{2060}".u] do "\n\u{308}a'\u{2060}".u.words.to_a end
  expect ["\n".u, "a".u, ",".u] do "\na,".u.words.to_a end
  expect ["\n".u, "\u{308}".u, "a".u, ",".u] do "\n\u{308}a,".u.words.to_a end
  expect ["\n".u, "1".u, ":".u] do "\n1:".u.words.to_a end
  expect ["\n".u, "\u{308}".u, "1".u, ":".u] do "\n\u{308}1:".u.words.to_a end
  expect ["\n".u, "1".u, "'".u] do "\n1'".u.words.to_a end
  expect ["\n".u, "\u{308}".u, "1".u, "'".u] do "\n\u{308}1'".u.words.to_a end
  expect ["\n".u, "1".u, ",".u] do "\n1,".u.words.to_a end
  expect ["\n".u, "\u{308}".u, "1".u, ",".u] do "\n\u{308}1,".u.words.to_a end
  expect ["\n".u, "1".u, ".\u{2060}".u] do "\n1.\u{2060}".u.words.to_a end
  expect ["\n".u, "\u{308}".u, "1".u, ".\u{2060}".u] do "\n\u{308}1.\u{2060}".u.words.to_a end
  expect ["\v".u, "\x01".u] do "\v\x01".u.words.to_a end
  expect ["\v".u, "\u{308}".u, "\x01".u] do "\v\u{308}\x01".u.words.to_a end
  expect ["\v".u, "\r".u] do "\v\r".u.words.to_a end
  expect ["\v".u, "\u{308}".u, "\r".u] do "\v\u{308}\r".u.words.to_a end
  expect ["\v".u, "\n".u] do "\v\n".u.words.to_a end
  expect ["\v".u, "\u{308}".u, "\n".u] do "\v\u{308}\n".u.words.to_a end
  expect ["\v".u, "\v".u] do "\v\v".u.words.to_a end
  expect ["\v".u, "\u{308}".u, "\v".u] do "\v\u{308}\v".u.words.to_a end
  expect ["\v".u, "\u{3031}".u] do "\v\u{3031}".u.words.to_a end
  expect ["\v".u, "\u{308}".u, "\u{3031}".u] do "\v\u{308}\u{3031}".u.words.to_a end
  expect ["\v".u, "A".u] do "\vA".u.words.to_a end
  expect ["\v".u, "\u{308}".u, "A".u] do "\v\u{308}A".u.words.to_a end
  expect ["\v".u, ":".u] do "\v:".u.words.to_a end
  expect ["\v".u, "\u{308}".u, ":".u] do "\v\u{308}:".u.words.to_a end
  expect ["\v".u, ",".u] do "\v,".u.words.to_a end
  expect ["\v".u, "\u{308}".u, ",".u] do "\v\u{308},".u.words.to_a end
  expect ["\v".u, "'".u] do "\v'".u.words.to_a end
  expect ["\v".u, "\u{308}".u, "'".u] do "\v\u{308}'".u.words.to_a end
  expect ["\v".u, "0".u] do "\v0".u.words.to_a end
  expect ["\v".u, "\u{308}".u, "0".u] do "\v\u{308}0".u.words.to_a end
  expect ["\v".u, "_".u] do "\v_".u.words.to_a end
  expect ["\v".u, "\u{308}".u, "_".u] do "\v\u{308}_".u.words.to_a end
  expect ["\v".u, "\u{1f1e6}".u] do "\v\u{1f1e6}".u.words.to_a end
  expect ["\v".u, "\u{308}".u, "\u{1f1e6}".u] do "\v\u{308}\u{1f1e6}".u.words.to_a end
  expect ["\v".u, "\u{ad}".u] do "\v\u{ad}".u.words.to_a end
  expect ["\v".u, "\u{308}\u{ad}".u] do "\v\u{308}\u{ad}".u.words.to_a end
  expect ["\v".u, "\u{300}".u] do "\v\u{300}".u.words.to_a end
  expect ["\v".u, "\u{308}\u{300}".u] do "\v\u{308}\u{300}".u.words.to_a end
  expect ["\v".u, "a\u{2060}".u] do "\va\u{2060}".u.words.to_a end
  expect ["\v".u, "\u{308}".u, "a\u{2060}".u] do "\v\u{308}a\u{2060}".u.words.to_a end
  expect ["\v".u, "a".u, ":".u] do "\va:".u.words.to_a end
  expect ["\v".u, "\u{308}".u, "a".u, ":".u] do "\v\u{308}a:".u.words.to_a end
  expect ["\v".u, "a".u, "'".u] do "\va'".u.words.to_a end
  expect ["\v".u, "\u{308}".u, "a".u, "'".u] do "\v\u{308}a'".u.words.to_a end
  expect ["\v".u, "a".u, "'\u{2060}".u] do "\va'\u{2060}".u.words.to_a end
  expect ["\v".u, "\u{308}".u, "a".u, "'\u{2060}".u] do "\v\u{308}a'\u{2060}".u.words.to_a end
  expect ["\v".u, "a".u, ",".u] do "\va,".u.words.to_a end
  expect ["\v".u, "\u{308}".u, "a".u, ",".u] do "\v\u{308}a,".u.words.to_a end
  expect ["\v".u, "1".u, ":".u] do "\v1:".u.words.to_a end
  expect ["\v".u, "\u{308}".u, "1".u, ":".u] do "\v\u{308}1:".u.words.to_a end
  expect ["\v".u, "1".u, "'".u] do "\v1'".u.words.to_a end
  expect ["\v".u, "\u{308}".u, "1".u, "'".u] do "\v\u{308}1'".u.words.to_a end
  expect ["\v".u, "1".u, ",".u] do "\v1,".u.words.to_a end
  expect ["\v".u, "\u{308}".u, "1".u, ",".u] do "\v\u{308}1,".u.words.to_a end
  expect ["\v".u, "1".u, ".\u{2060}".u] do "\v1.\u{2060}".u.words.to_a end
  expect ["\v".u, "\u{308}".u, "1".u, ".\u{2060}".u] do "\v\u{308}1.\u{2060}".u.words.to_a end
  expect ["\u{3031}".u, "\x01".u] do "\u{3031}\x01".u.words.to_a end
  expect ["\u{3031}\u{308}".u, "\x01".u] do "\u{3031}\u{308}\x01".u.words.to_a end
  expect ["\u{3031}".u, "\r".u] do "\u{3031}\r".u.words.to_a end
  expect ["\u{3031}\u{308}".u, "\r".u] do "\u{3031}\u{308}\r".u.words.to_a end
  expect ["\u{3031}".u, "\n".u] do "\u{3031}\n".u.words.to_a end
  expect ["\u{3031}\u{308}".u, "\n".u] do "\u{3031}\u{308}\n".u.words.to_a end
  expect ["\u{3031}".u, "\v".u] do "\u{3031}\v".u.words.to_a end
  expect ["\u{3031}\u{308}".u, "\v".u] do "\u{3031}\u{308}\v".u.words.to_a end
  expect ["\u{3031}\u{3031}".u] do "\u{3031}\u{3031}".u.words.to_a end
  expect ["\u{3031}\u{308}\u{3031}".u] do "\u{3031}\u{308}\u{3031}".u.words.to_a end
  expect ["\u{3031}".u, "A".u] do "\u{3031}A".u.words.to_a end
  expect ["\u{3031}\u{308}".u, "A".u] do "\u{3031}\u{308}A".u.words.to_a end
  expect ["\u{3031}".u, ":".u] do "\u{3031}:".u.words.to_a end
  expect ["\u{3031}\u{308}".u, ":".u] do "\u{3031}\u{308}:".u.words.to_a end
  expect ["\u{3031}".u, ",".u] do "\u{3031},".u.words.to_a end
  expect ["\u{3031}\u{308}".u, ",".u] do "\u{3031}\u{308},".u.words.to_a end
  expect ["\u{3031}".u, "'".u] do "\u{3031}'".u.words.to_a end
  expect ["\u{3031}\u{308}".u, "'".u] do "\u{3031}\u{308}'".u.words.to_a end
  expect ["\u{3031}".u, "0".u] do "\u{3031}0".u.words.to_a end
  expect ["\u{3031}\u{308}".u, "0".u] do "\u{3031}\u{308}0".u.words.to_a end
  expect ["\u{3031}_".u] do "\u{3031}_".u.words.to_a end
  expect ["\u{3031}\u{308}_".u] do "\u{3031}\u{308}_".u.words.to_a end
  expect ["\u{3031}".u, "\u{1f1e6}".u] do "\u{3031}\u{1f1e6}".u.words.to_a end
  expect ["\u{3031}\u{308}".u, "\u{1f1e6}".u] do "\u{3031}\u{308}\u{1f1e6}".u.words.to_a end
  expect ["\u{3031}\u{ad}".u] do "\u{3031}\u{ad}".u.words.to_a end
  expect ["\u{3031}\u{308}\u{ad}".u] do "\u{3031}\u{308}\u{ad}".u.words.to_a end
  expect ["\u{3031}\u{300}".u] do "\u{3031}\u{300}".u.words.to_a end
  expect ["\u{3031}\u{308}\u{300}".u] do "\u{3031}\u{308}\u{300}".u.words.to_a end
  expect ["\u{3031}".u, "a\u{2060}".u] do "\u{3031}a\u{2060}".u.words.to_a end
  expect ["\u{3031}\u{308}".u, "a\u{2060}".u] do "\u{3031}\u{308}a\u{2060}".u.words.to_a end
  expect ["\u{3031}".u, "a".u, ":".u] do "\u{3031}a:".u.words.to_a end
  expect ["\u{3031}\u{308}".u, "a".u, ":".u] do "\u{3031}\u{308}a:".u.words.to_a end
  expect ["\u{3031}".u, "a".u, "'".u] do "\u{3031}a'".u.words.to_a end
  expect ["\u{3031}\u{308}".u, "a".u, "'".u] do "\u{3031}\u{308}a'".u.words.to_a end
  expect ["\u{3031}".u, "a".u, "'\u{2060}".u] do "\u{3031}a'\u{2060}".u.words.to_a end
  expect ["\u{3031}\u{308}".u, "a".u, "'\u{2060}".u] do "\u{3031}\u{308}a'\u{2060}".u.words.to_a end
  expect ["\u{3031}".u, "a".u, ",".u] do "\u{3031}a,".u.words.to_a end
  expect ["\u{3031}\u{308}".u, "a".u, ",".u] do "\u{3031}\u{308}a,".u.words.to_a end
  expect ["\u{3031}".u, "1".u, ":".u] do "\u{3031}1:".u.words.to_a end
  expect ["\u{3031}\u{308}".u, "1".u, ":".u] do "\u{3031}\u{308}1:".u.words.to_a end
  expect ["\u{3031}".u, "1".u, "'".u] do "\u{3031}1'".u.words.to_a end
  expect ["\u{3031}\u{308}".u, "1".u, "'".u] do "\u{3031}\u{308}1'".u.words.to_a end
  expect ["\u{3031}".u, "1".u, ",".u] do "\u{3031}1,".u.words.to_a end
  expect ["\u{3031}\u{308}".u, "1".u, ",".u] do "\u{3031}\u{308}1,".u.words.to_a end
  expect ["\u{3031}".u, "1".u, ".\u{2060}".u] do "\u{3031}1.\u{2060}".u.words.to_a end
  expect ["\u{3031}\u{308}".u, "1".u, ".\u{2060}".u] do "\u{3031}\u{308}1.\u{2060}".u.words.to_a end
  expect ["A".u, "\x01".u] do "A\x01".u.words.to_a end
  expect ["A\u{308}".u, "\x01".u] do "A\u{308}\x01".u.words.to_a end
  expect ["A".u, "\r".u] do "A\r".u.words.to_a end
  expect ["A\u{308}".u, "\r".u] do "A\u{308}\r".u.words.to_a end
  expect ["A".u, "\n".u] do "A\n".u.words.to_a end
  expect ["A\u{308}".u, "\n".u] do "A\u{308}\n".u.words.to_a end
  expect ["A".u, "\v".u] do "A\v".u.words.to_a end
  expect ["A\u{308}".u, "\v".u] do "A\u{308}\v".u.words.to_a end
  expect ["A".u, "\u{3031}".u] do "A\u{3031}".u.words.to_a end
  expect ["A\u{308}".u, "\u{3031}".u] do "A\u{308}\u{3031}".u.words.to_a end
  expect ["AA".u] do "AA".u.words.to_a end
  expect ["A\u{308}A".u] do "A\u{308}A".u.words.to_a end
  expect ["A".u, ":".u] do "A:".u.words.to_a end
  expect ["A\u{308}".u, ":".u] do "A\u{308}:".u.words.to_a end
  expect ["A".u, ",".u] do "A,".u.words.to_a end
  expect ["A\u{308}".u, ",".u] do "A\u{308},".u.words.to_a end
  expect ["A".u, "'".u] do "A'".u.words.to_a end
  expect ["A\u{308}".u, "'".u] do "A\u{308}'".u.words.to_a end
  expect ["A0".u] do "A0".u.words.to_a end
  expect ["A\u{308}0".u] do "A\u{308}0".u.words.to_a end
  expect ["A_".u] do "A_".u.words.to_a end
  expect ["A\u{308}_".u] do "A\u{308}_".u.words.to_a end
  expect ["A".u, "\u{1f1e6}".u] do "A\u{1f1e6}".u.words.to_a end
  expect ["A\u{308}".u, "\u{1f1e6}".u] do "A\u{308}\u{1f1e6}".u.words.to_a end
  expect ["A\u{ad}".u] do "A\u{ad}".u.words.to_a end
  expect ["A\u{308}\u{ad}".u] do "A\u{308}\u{ad}".u.words.to_a end
  expect ["A\u{300}".u] do "A\u{300}".u.words.to_a end
  expect ["A\u{308}\u{300}".u] do "A\u{308}\u{300}".u.words.to_a end
  expect ["Aa\u{2060}".u] do "Aa\u{2060}".u.words.to_a end
  expect ["A\u{308}a\u{2060}".u] do "A\u{308}a\u{2060}".u.words.to_a end
  expect ["Aa".u, ":".u] do "Aa:".u.words.to_a end
  expect ["A\u{308}a".u, ":".u] do "A\u{308}a:".u.words.to_a end
  expect ["Aa".u, "'".u] do "Aa'".u.words.to_a end
  expect ["A\u{308}a".u, "'".u] do "A\u{308}a'".u.words.to_a end
  expect ["Aa".u, "'\u{2060}".u] do "Aa'\u{2060}".u.words.to_a end
  expect ["A\u{308}a".u, "'\u{2060}".u] do "A\u{308}a'\u{2060}".u.words.to_a end
  expect ["Aa".u, ",".u] do "Aa,".u.words.to_a end
  expect ["A\u{308}a".u, ",".u] do "A\u{308}a,".u.words.to_a end
  expect ["A1".u, ":".u] do "A1:".u.words.to_a end
  expect ["A\u{308}1".u, ":".u] do "A\u{308}1:".u.words.to_a end
  expect ["A1".u, "'".u] do "A1'".u.words.to_a end
  expect ["A\u{308}1".u, "'".u] do "A\u{308}1'".u.words.to_a end
  expect ["A1".u, ",".u] do "A1,".u.words.to_a end
  expect ["A\u{308}1".u, ",".u] do "A\u{308}1,".u.words.to_a end
  expect ["A1".u, ".\u{2060}".u] do "A1.\u{2060}".u.words.to_a end
  expect ["A\u{308}1".u, ".\u{2060}".u] do "A\u{308}1.\u{2060}".u.words.to_a end
  expect [":".u, "\x01".u] do ":\x01".u.words.to_a end
  expect [":\u{308}".u, "\x01".u] do ":\u{308}\x01".u.words.to_a end
  expect [":".u, "\r".u] do ":\r".u.words.to_a end
  expect [":\u{308}".u, "\r".u] do ":\u{308}\r".u.words.to_a end
  expect [":".u, "\n".u] do ":\n".u.words.to_a end
  expect [":\u{308}".u, "\n".u] do ":\u{308}\n".u.words.to_a end
  expect [":".u, "\v".u] do ":\v".u.words.to_a end
  expect [":\u{308}".u, "\v".u] do ":\u{308}\v".u.words.to_a end
  expect [":".u, "\u{3031}".u] do ":\u{3031}".u.words.to_a end
  expect [":\u{308}".u, "\u{3031}".u] do ":\u{308}\u{3031}".u.words.to_a end
  expect [":".u, "A".u] do ":A".u.words.to_a end
  expect [":\u{308}".u, "A".u] do ":\u{308}A".u.words.to_a end
  expect [":".u, ":".u] do "::".u.words.to_a end
  expect [":\u{308}".u, ":".u] do ":\u{308}:".u.words.to_a end
  expect [":".u, ",".u] do ":,".u.words.to_a end
  expect [":\u{308}".u, ",".u] do ":\u{308},".u.words.to_a end
  expect [":".u, "'".u] do ":'".u.words.to_a end
  expect [":\u{308}".u, "'".u] do ":\u{308}'".u.words.to_a end
  expect [":".u, "0".u] do ":0".u.words.to_a end
  expect [":\u{308}".u, "0".u] do ":\u{308}0".u.words.to_a end
  expect [":".u, "_".u] do ":_".u.words.to_a end
  expect [":\u{308}".u, "_".u] do ":\u{308}_".u.words.to_a end
  expect [":".u, "\u{1f1e6}".u] do ":\u{1f1e6}".u.words.to_a end
  expect [":\u{308}".u, "\u{1f1e6}".u] do ":\u{308}\u{1f1e6}".u.words.to_a end
  expect [":\u{ad}".u] do ":\u{ad}".u.words.to_a end
  expect [":\u{308}\u{ad}".u] do ":\u{308}\u{ad}".u.words.to_a end
  expect [":\u{300}".u] do ":\u{300}".u.words.to_a end
  expect [":\u{308}\u{300}".u] do ":\u{308}\u{300}".u.words.to_a end
  expect [":".u, "a\u{2060}".u] do ":a\u{2060}".u.words.to_a end
  expect [":\u{308}".u, "a\u{2060}".u] do ":\u{308}a\u{2060}".u.words.to_a end
  expect [":".u, "a".u, ":".u] do ":a:".u.words.to_a end
  expect [":\u{308}".u, "a".u, ":".u] do ":\u{308}a:".u.words.to_a end
  expect [":".u, "a".u, "'".u] do ":a'".u.words.to_a end
  expect [":\u{308}".u, "a".u, "'".u] do ":\u{308}a'".u.words.to_a end
  expect [":".u, "a".u, "'\u{2060}".u] do ":a'\u{2060}".u.words.to_a end
  expect [":\u{308}".u, "a".u, "'\u{2060}".u] do ":\u{308}a'\u{2060}".u.words.to_a end
  expect [":".u, "a".u, ",".u] do ":a,".u.words.to_a end
  expect [":\u{308}".u, "a".u, ",".u] do ":\u{308}a,".u.words.to_a end
  expect [":".u, "1".u, ":".u] do ":1:".u.words.to_a end
  expect [":\u{308}".u, "1".u, ":".u] do ":\u{308}1:".u.words.to_a end
  expect [":".u, "1".u, "'".u] do ":1'".u.words.to_a end
  expect [":\u{308}".u, "1".u, "'".u] do ":\u{308}1'".u.words.to_a end
  expect [":".u, "1".u, ",".u] do ":1,".u.words.to_a end
  expect [":\u{308}".u, "1".u, ",".u] do ":\u{308}1,".u.words.to_a end
  expect [":".u, "1".u, ".\u{2060}".u] do ":1.\u{2060}".u.words.to_a end
  expect [":\u{308}".u, "1".u, ".\u{2060}".u] do ":\u{308}1.\u{2060}".u.words.to_a end
  expect [",".u, "\x01".u] do ",\x01".u.words.to_a end
  expect [",\u{308}".u, "\x01".u] do ",\u{308}\x01".u.words.to_a end
  expect [",".u, "\r".u] do ",\r".u.words.to_a end
  expect [",\u{308}".u, "\r".u] do ",\u{308}\r".u.words.to_a end
  expect [",".u, "\n".u] do ",\n".u.words.to_a end
  expect [",\u{308}".u, "\n".u] do ",\u{308}\n".u.words.to_a end
  expect [",".u, "\v".u] do ",\v".u.words.to_a end
  expect [",\u{308}".u, "\v".u] do ",\u{308}\v".u.words.to_a end
  expect [",".u, "\u{3031}".u] do ",\u{3031}".u.words.to_a end
  expect [",\u{308}".u, "\u{3031}".u] do ",\u{308}\u{3031}".u.words.to_a end
  expect [",".u, "A".u] do ",A".u.words.to_a end
  expect [",\u{308}".u, "A".u] do ",\u{308}A".u.words.to_a end
  expect [",".u, ":".u] do ",:".u.words.to_a end
  expect [",\u{308}".u, ":".u] do ",\u{308}:".u.words.to_a end
  expect [",".u, ",".u] do ",,".u.words.to_a end
  expect [",\u{308}".u, ",".u] do ",\u{308},".u.words.to_a end
  expect [",".u, "'".u] do ",'".u.words.to_a end
  expect [",\u{308}".u, "'".u] do ",\u{308}'".u.words.to_a end
  expect [",".u, "0".u] do ",0".u.words.to_a end
  expect [",\u{308}".u, "0".u] do ",\u{308}0".u.words.to_a end
  expect [",".u, "_".u] do ",_".u.words.to_a end
  expect [",\u{308}".u, "_".u] do ",\u{308}_".u.words.to_a end
  expect [",".u, "\u{1f1e6}".u] do ",\u{1f1e6}".u.words.to_a end
  expect [",\u{308}".u, "\u{1f1e6}".u] do ",\u{308}\u{1f1e6}".u.words.to_a end
  expect [",\u{ad}".u] do ",\u{ad}".u.words.to_a end
  expect [",\u{308}\u{ad}".u] do ",\u{308}\u{ad}".u.words.to_a end
  expect [",\u{300}".u] do ",\u{300}".u.words.to_a end
  expect [",\u{308}\u{300}".u] do ",\u{308}\u{300}".u.words.to_a end
  expect [",".u, "a\u{2060}".u] do ",a\u{2060}".u.words.to_a end
  expect [",\u{308}".u, "a\u{2060}".u] do ",\u{308}a\u{2060}".u.words.to_a end
  expect [",".u, "a".u, ":".u] do ",a:".u.words.to_a end
  expect [",\u{308}".u, "a".u, ":".u] do ",\u{308}a:".u.words.to_a end
  expect [",".u, "a".u, "'".u] do ",a'".u.words.to_a end
  expect [",\u{308}".u, "a".u, "'".u] do ",\u{308}a'".u.words.to_a end
  expect [",".u, "a".u, "'\u{2060}".u] do ",a'\u{2060}".u.words.to_a end
  expect [",\u{308}".u, "a".u, "'\u{2060}".u] do ",\u{308}a'\u{2060}".u.words.to_a end
  expect [",".u, "a".u, ",".u] do ",a,".u.words.to_a end
  expect [",\u{308}".u, "a".u, ",".u] do ",\u{308}a,".u.words.to_a end
  expect [",".u, "1".u, ":".u] do ",1:".u.words.to_a end
  expect [",\u{308}".u, "1".u, ":".u] do ",\u{308}1:".u.words.to_a end
  expect [",".u, "1".u, "'".u] do ",1'".u.words.to_a end
  expect [",\u{308}".u, "1".u, "'".u] do ",\u{308}1'".u.words.to_a end
  expect [",".u, "1".u, ",".u] do ",1,".u.words.to_a end
  expect [",\u{308}".u, "1".u, ",".u] do ",\u{308}1,".u.words.to_a end
  expect [",".u, "1".u, ".\u{2060}".u] do ",1.\u{2060}".u.words.to_a end
  expect [",\u{308}".u, "1".u, ".\u{2060}".u] do ",\u{308}1.\u{2060}".u.words.to_a end
  expect ["'".u, "\x01".u] do "'\x01".u.words.to_a end
  expect ["'\u{308}".u, "\x01".u] do "'\u{308}\x01".u.words.to_a end
  expect ["'".u, "\r".u] do "'\r".u.words.to_a end
  expect ["'\u{308}".u, "\r".u] do "'\u{308}\r".u.words.to_a end
  expect ["'".u, "\n".u] do "'\n".u.words.to_a end
  expect ["'\u{308}".u, "\n".u] do "'\u{308}\n".u.words.to_a end
  expect ["'".u, "\v".u] do "'\v".u.words.to_a end
  expect ["'\u{308}".u, "\v".u] do "'\u{308}\v".u.words.to_a end
  expect ["'".u, "\u{3031}".u] do "'\u{3031}".u.words.to_a end
  expect ["'\u{308}".u, "\u{3031}".u] do "'\u{308}\u{3031}".u.words.to_a end
  expect ["'".u, "A".u] do "'A".u.words.to_a end
  expect ["'\u{308}".u, "A".u] do "'\u{308}A".u.words.to_a end
  expect ["'".u, ":".u] do "':".u.words.to_a end
  expect ["'\u{308}".u, ":".u] do "'\u{308}:".u.words.to_a end
  expect ["'".u, ",".u] do "',".u.words.to_a end
  expect ["'\u{308}".u, ",".u] do "'\u{308},".u.words.to_a end
  expect ["'".u, "'".u] do "''".u.words.to_a end
  expect ["'\u{308}".u, "'".u] do "'\u{308}'".u.words.to_a end
  expect ["'".u, "0".u] do "'0".u.words.to_a end
  expect ["'\u{308}".u, "0".u] do "'\u{308}0".u.words.to_a end
  expect ["'".u, "_".u] do "'_".u.words.to_a end
  expect ["'\u{308}".u, "_".u] do "'\u{308}_".u.words.to_a end
  expect ["'".u, "\u{1f1e6}".u] do "'\u{1f1e6}".u.words.to_a end
  expect ["'\u{308}".u, "\u{1f1e6}".u] do "'\u{308}\u{1f1e6}".u.words.to_a end
  expect ["'\u{ad}".u] do "'\u{ad}".u.words.to_a end
  expect ["'\u{308}\u{ad}".u] do "'\u{308}\u{ad}".u.words.to_a end
  expect ["'\u{300}".u] do "'\u{300}".u.words.to_a end
  expect ["'\u{308}\u{300}".u] do "'\u{308}\u{300}".u.words.to_a end
  expect ["'".u, "a\u{2060}".u] do "'a\u{2060}".u.words.to_a end
  expect ["'\u{308}".u, "a\u{2060}".u] do "'\u{308}a\u{2060}".u.words.to_a end
  expect ["'".u, "a".u, ":".u] do "'a:".u.words.to_a end
  expect ["'\u{308}".u, "a".u, ":".u] do "'\u{308}a:".u.words.to_a end
  expect ["'".u, "a".u, "'".u] do "'a'".u.words.to_a end
  expect ["'\u{308}".u, "a".u, "'".u] do "'\u{308}a'".u.words.to_a end
  expect ["'".u, "a".u, "'\u{2060}".u] do "'a'\u{2060}".u.words.to_a end
  expect ["'\u{308}".u, "a".u, "'\u{2060}".u] do "'\u{308}a'\u{2060}".u.words.to_a end
  expect ["'".u, "a".u, ",".u] do "'a,".u.words.to_a end
  expect ["'\u{308}".u, "a".u, ",".u] do "'\u{308}a,".u.words.to_a end
  expect ["'".u, "1".u, ":".u] do "'1:".u.words.to_a end
  expect ["'\u{308}".u, "1".u, ":".u] do "'\u{308}1:".u.words.to_a end
  expect ["'".u, "1".u, "'".u] do "'1'".u.words.to_a end
  expect ["'\u{308}".u, "1".u, "'".u] do "'\u{308}1'".u.words.to_a end
  expect ["'".u, "1".u, ",".u] do "'1,".u.words.to_a end
  expect ["'\u{308}".u, "1".u, ",".u] do "'\u{308}1,".u.words.to_a end
  expect ["'".u, "1".u, ".\u{2060}".u] do "'1.\u{2060}".u.words.to_a end
  expect ["'\u{308}".u, "1".u, ".\u{2060}".u] do "'\u{308}1.\u{2060}".u.words.to_a end
  expect ["0".u, "\x01".u] do "0\x01".u.words.to_a end
  expect ["0\u{308}".u, "\x01".u] do "0\u{308}\x01".u.words.to_a end
  expect ["0".u, "\r".u] do "0\r".u.words.to_a end
  expect ["0\u{308}".u, "\r".u] do "0\u{308}\r".u.words.to_a end
  expect ["0".u, "\n".u] do "0\n".u.words.to_a end
  expect ["0\u{308}".u, "\n".u] do "0\u{308}\n".u.words.to_a end
  expect ["0".u, "\v".u] do "0\v".u.words.to_a end
  expect ["0\u{308}".u, "\v".u] do "0\u{308}\v".u.words.to_a end
  expect ["0".u, "\u{3031}".u] do "0\u{3031}".u.words.to_a end
  expect ["0\u{308}".u, "\u{3031}".u] do "0\u{308}\u{3031}".u.words.to_a end
  expect ["0A".u] do "0A".u.words.to_a end
  expect ["0\u{308}A".u] do "0\u{308}A".u.words.to_a end
  expect ["0".u, ":".u] do "0:".u.words.to_a end
  expect ["0\u{308}".u, ":".u] do "0\u{308}:".u.words.to_a end
  expect ["0".u, ",".u] do "0,".u.words.to_a end
  expect ["0\u{308}".u, ",".u] do "0\u{308},".u.words.to_a end
  expect ["0".u, "'".u] do "0'".u.words.to_a end
  expect ["0\u{308}".u, "'".u] do "0\u{308}'".u.words.to_a end
  expect ["00".u] do "00".u.words.to_a end
  expect ["0\u{308}0".u] do "0\u{308}0".u.words.to_a end
  expect ["0_".u] do "0_".u.words.to_a end
  expect ["0\u{308}_".u] do "0\u{308}_".u.words.to_a end
  expect ["0".u, "\u{1f1e6}".u] do "0\u{1f1e6}".u.words.to_a end
  expect ["0\u{308}".u, "\u{1f1e6}".u] do "0\u{308}\u{1f1e6}".u.words.to_a end
  expect ["0\u{ad}".u] do "0\u{ad}".u.words.to_a end
  expect ["0\u{308}\u{ad}".u] do "0\u{308}\u{ad}".u.words.to_a end
  expect ["0\u{300}".u] do "0\u{300}".u.words.to_a end
  expect ["0\u{308}\u{300}".u] do "0\u{308}\u{300}".u.words.to_a end
  expect ["0a\u{2060}".u] do "0a\u{2060}".u.words.to_a end
  expect ["0\u{308}a\u{2060}".u] do "0\u{308}a\u{2060}".u.words.to_a end
  expect ["0a".u, ":".u] do "0a:".u.words.to_a end
  expect ["0\u{308}a".u, ":".u] do "0\u{308}a:".u.words.to_a end
  expect ["0a".u, "'".u] do "0a'".u.words.to_a end
  expect ["0\u{308}a".u, "'".u] do "0\u{308}a'".u.words.to_a end
  expect ["0a".u, "'\u{2060}".u] do "0a'\u{2060}".u.words.to_a end
  expect ["0\u{308}a".u, "'\u{2060}".u] do "0\u{308}a'\u{2060}".u.words.to_a end
  expect ["0a".u, ",".u] do "0a,".u.words.to_a end
  expect ["0\u{308}a".u, ",".u] do "0\u{308}a,".u.words.to_a end
  expect ["01".u, ":".u] do "01:".u.words.to_a end
  expect ["0\u{308}1".u, ":".u] do "0\u{308}1:".u.words.to_a end
  expect ["01".u, "'".u] do "01'".u.words.to_a end
  expect ["0\u{308}1".u, "'".u] do "0\u{308}1'".u.words.to_a end
  expect ["01".u, ",".u] do "01,".u.words.to_a end
  expect ["0\u{308}1".u, ",".u] do "0\u{308}1,".u.words.to_a end
  expect ["01".u, ".\u{2060}".u] do "01.\u{2060}".u.words.to_a end
  expect ["0\u{308}1".u, ".\u{2060}".u] do "0\u{308}1.\u{2060}".u.words.to_a end
  expect ["_".u, "\x01".u] do "_\x01".u.words.to_a end
  expect ["_\u{308}".u, "\x01".u] do "_\u{308}\x01".u.words.to_a end
  expect ["_".u, "\r".u] do "_\r".u.words.to_a end
  expect ["_\u{308}".u, "\r".u] do "_\u{308}\r".u.words.to_a end
  expect ["_".u, "\n".u] do "_\n".u.words.to_a end
  expect ["_\u{308}".u, "\n".u] do "_\u{308}\n".u.words.to_a end
  expect ["_".u, "\v".u] do "_\v".u.words.to_a end
  expect ["_\u{308}".u, "\v".u] do "_\u{308}\v".u.words.to_a end
  expect ["_\u{3031}".u] do "_\u{3031}".u.words.to_a end
  expect ["_\u{308}\u{3031}".u] do "_\u{308}\u{3031}".u.words.to_a end
  expect ["_A".u] do "_A".u.words.to_a end
  expect ["_\u{308}A".u] do "_\u{308}A".u.words.to_a end
  expect ["_".u, ":".u] do "_:".u.words.to_a end
  expect ["_\u{308}".u, ":".u] do "_\u{308}:".u.words.to_a end
  expect ["_".u, ",".u] do "_,".u.words.to_a end
  expect ["_\u{308}".u, ",".u] do "_\u{308},".u.words.to_a end
  expect ["_".u, "'".u] do "_'".u.words.to_a end
  expect ["_\u{308}".u, "'".u] do "_\u{308}'".u.words.to_a end
  expect ["_0".u] do "_0".u.words.to_a end
  expect ["_\u{308}0".u] do "_\u{308}0".u.words.to_a end
  expect ["__".u] do "__".u.words.to_a end
  expect ["_\u{308}_".u] do "_\u{308}_".u.words.to_a end
  expect ["_".u, "\u{1f1e6}".u] do "_\u{1f1e6}".u.words.to_a end
  expect ["_\u{308}".u, "\u{1f1e6}".u] do "_\u{308}\u{1f1e6}".u.words.to_a end
  expect ["_\u{ad}".u] do "_\u{ad}".u.words.to_a end
  expect ["_\u{308}\u{ad}".u] do "_\u{308}\u{ad}".u.words.to_a end
  expect ["_\u{300}".u] do "_\u{300}".u.words.to_a end
  expect ["_\u{308}\u{300}".u] do "_\u{308}\u{300}".u.words.to_a end
  expect ["_a\u{2060}".u] do "_a\u{2060}".u.words.to_a end
  expect ["_\u{308}a\u{2060}".u] do "_\u{308}a\u{2060}".u.words.to_a end
  expect ["_a".u, ":".u] do "_a:".u.words.to_a end
  expect ["_\u{308}a".u, ":".u] do "_\u{308}a:".u.words.to_a end
  expect ["_a".u, "'".u] do "_a'".u.words.to_a end
  expect ["_\u{308}a".u, "'".u] do "_\u{308}a'".u.words.to_a end
  expect ["_a".u, "'\u{2060}".u] do "_a'\u{2060}".u.words.to_a end
  expect ["_\u{308}a".u, "'\u{2060}".u] do "_\u{308}a'\u{2060}".u.words.to_a end
  expect ["_a".u, ",".u] do "_a,".u.words.to_a end
  expect ["_\u{308}a".u, ",".u] do "_\u{308}a,".u.words.to_a end
  expect ["_1".u, ":".u] do "_1:".u.words.to_a end
  expect ["_\u{308}1".u, ":".u] do "_\u{308}1:".u.words.to_a end
  expect ["_1".u, "'".u] do "_1'".u.words.to_a end
  expect ["_\u{308}1".u, "'".u] do "_\u{308}1'".u.words.to_a end
  expect ["_1".u, ",".u] do "_1,".u.words.to_a end
  expect ["_\u{308}1".u, ",".u] do "_\u{308}1,".u.words.to_a end
  expect ["_1".u, ".\u{2060}".u] do "_1.\u{2060}".u.words.to_a end
  expect ["_\u{308}1".u, ".\u{2060}".u] do "_\u{308}1.\u{2060}".u.words.to_a end
  expect ["\u{1f1e6}".u, "\x01".u] do "\u{1f1e6}\x01".u.words.to_a end
  expect ["\u{1f1e6}\u{308}".u, "\x01".u] do "\u{1f1e6}\u{308}\x01".u.words.to_a end
  expect ["\u{1f1e6}".u, "\r".u] do "\u{1f1e6}\r".u.words.to_a end
  expect ["\u{1f1e6}\u{308}".u, "\r".u] do "\u{1f1e6}\u{308}\r".u.words.to_a end
  expect ["\u{1f1e6}".u, "\n".u] do "\u{1f1e6}\n".u.words.to_a end
  expect ["\u{1f1e6}\u{308}".u, "\n".u] do "\u{1f1e6}\u{308}\n".u.words.to_a end
  expect ["\u{1f1e6}".u, "\v".u] do "\u{1f1e6}\v".u.words.to_a end
  expect ["\u{1f1e6}\u{308}".u, "\v".u] do "\u{1f1e6}\u{308}\v".u.words.to_a end
  expect ["\u{1f1e6}".u, "\u{3031}".u] do "\u{1f1e6}\u{3031}".u.words.to_a end
  expect ["\u{1f1e6}\u{308}".u, "\u{3031}".u] do "\u{1f1e6}\u{308}\u{3031}".u.words.to_a end
  expect ["\u{1f1e6}".u, "A".u] do "\u{1f1e6}A".u.words.to_a end
  expect ["\u{1f1e6}\u{308}".u, "A".u] do "\u{1f1e6}\u{308}A".u.words.to_a end
  expect ["\u{1f1e6}".u, ":".u] do "\u{1f1e6}:".u.words.to_a end
  expect ["\u{1f1e6}\u{308}".u, ":".u] do "\u{1f1e6}\u{308}:".u.words.to_a end
  expect ["\u{1f1e6}".u, ",".u] do "\u{1f1e6},".u.words.to_a end
  expect ["\u{1f1e6}\u{308}".u, ",".u] do "\u{1f1e6}\u{308},".u.words.to_a end
  expect ["\u{1f1e6}".u, "'".u] do "\u{1f1e6}'".u.words.to_a end
  expect ["\u{1f1e6}\u{308}".u, "'".u] do "\u{1f1e6}\u{308}'".u.words.to_a end
  expect ["\u{1f1e6}".u, "0".u] do "\u{1f1e6}0".u.words.to_a end
  expect ["\u{1f1e6}\u{308}".u, "0".u] do "\u{1f1e6}\u{308}0".u.words.to_a end
  expect ["\u{1f1e6}".u, "_".u] do "\u{1f1e6}_".u.words.to_a end
  expect ["\u{1f1e6}\u{308}".u, "_".u] do "\u{1f1e6}\u{308}_".u.words.to_a end
  expect ["\u{1f1e6}\u{1f1e6}".u] do "\u{1f1e6}\u{1f1e6}".u.words.to_a end
  expect ["\u{1f1e6}\u{308}\u{1f1e6}".u] do "\u{1f1e6}\u{308}\u{1f1e6}".u.words.to_a end
  expect ["\u{1f1e6}\u{ad}".u] do "\u{1f1e6}\u{ad}".u.words.to_a end
  expect ["\u{1f1e6}\u{308}\u{ad}".u] do "\u{1f1e6}\u{308}\u{ad}".u.words.to_a end
  expect ["\u{1f1e6}\u{300}".u] do "\u{1f1e6}\u{300}".u.words.to_a end
  expect ["\u{1f1e6}\u{308}\u{300}".u] do "\u{1f1e6}\u{308}\u{300}".u.words.to_a end
  expect ["\u{1f1e6}".u, "a\u{2060}".u] do "\u{1f1e6}a\u{2060}".u.words.to_a end
  expect ["\u{1f1e6}\u{308}".u, "a\u{2060}".u] do "\u{1f1e6}\u{308}a\u{2060}".u.words.to_a end
  expect ["\u{1f1e6}".u, "a".u, ":".u] do "\u{1f1e6}a:".u.words.to_a end
  expect ["\u{1f1e6}\u{308}".u, "a".u, ":".u] do "\u{1f1e6}\u{308}a:".u.words.to_a end
  expect ["\u{1f1e6}".u, "a".u, "'".u] do "\u{1f1e6}a'".u.words.to_a end
  expect ["\u{1f1e6}\u{308}".u, "a".u, "'".u] do "\u{1f1e6}\u{308}a'".u.words.to_a end
  expect ["\u{1f1e6}".u, "a".u, "'\u{2060}".u] do "\u{1f1e6}a'\u{2060}".u.words.to_a end
  expect ["\u{1f1e6}\u{308}".u, "a".u, "'\u{2060}".u] do "\u{1f1e6}\u{308}a'\u{2060}".u.words.to_a end
  expect ["\u{1f1e6}".u, "a".u, ",".u] do "\u{1f1e6}a,".u.words.to_a end
  expect ["\u{1f1e6}\u{308}".u, "a".u, ",".u] do "\u{1f1e6}\u{308}a,".u.words.to_a end
  expect ["\u{1f1e6}".u, "1".u, ":".u] do "\u{1f1e6}1:".u.words.to_a end
  expect ["\u{1f1e6}\u{308}".u, "1".u, ":".u] do "\u{1f1e6}\u{308}1:".u.words.to_a end
  expect ["\u{1f1e6}".u, "1".u, "'".u] do "\u{1f1e6}1'".u.words.to_a end
  expect ["\u{1f1e6}\u{308}".u, "1".u, "'".u] do "\u{1f1e6}\u{308}1'".u.words.to_a end
  expect ["\u{1f1e6}".u, "1".u, ",".u] do "\u{1f1e6}1,".u.words.to_a end
  expect ["\u{1f1e6}\u{308}".u, "1".u, ",".u] do "\u{1f1e6}\u{308}1,".u.words.to_a end
  expect ["\u{1f1e6}".u, "1".u, ".\u{2060}".u] do "\u{1f1e6}1.\u{2060}".u.words.to_a end
  expect ["\u{1f1e6}\u{308}".u, "1".u, ".\u{2060}".u] do "\u{1f1e6}\u{308}1.\u{2060}".u.words.to_a end
  expect ["\u{ad}".u, "\x01".u] do "\u{ad}\x01".u.words.to_a end
  expect ["\u{ad}\u{308}".u, "\x01".u] do "\u{ad}\u{308}\x01".u.words.to_a end
  expect ["\u{ad}".u, "\r".u] do "\u{ad}\r".u.words.to_a end
  expect ["\u{ad}\u{308}".u, "\r".u] do "\u{ad}\u{308}\r".u.words.to_a end
  expect ["\u{ad}".u, "\n".u] do "\u{ad}\n".u.words.to_a end
  expect ["\u{ad}\u{308}".u, "\n".u] do "\u{ad}\u{308}\n".u.words.to_a end
  expect ["\u{ad}".u, "\v".u] do "\u{ad}\v".u.words.to_a end
  expect ["\u{ad}\u{308}".u, "\v".u] do "\u{ad}\u{308}\v".u.words.to_a end
  expect ["\u{ad}".u, "\u{3031}".u] do "\u{ad}\u{3031}".u.words.to_a end
  expect ["\u{ad}\u{308}".u, "\u{3031}".u] do "\u{ad}\u{308}\u{3031}".u.words.to_a end
  expect ["\u{ad}".u, "A".u] do "\u{ad}A".u.words.to_a end
  expect ["\u{ad}\u{308}".u, "A".u] do "\u{ad}\u{308}A".u.words.to_a end
  expect ["\u{ad}".u, ":".u] do "\u{ad}:".u.words.to_a end
  expect ["\u{ad}\u{308}".u, ":".u] do "\u{ad}\u{308}:".u.words.to_a end
  expect ["\u{ad}".u, ",".u] do "\u{ad},".u.words.to_a end
  expect ["\u{ad}\u{308}".u, ",".u] do "\u{ad}\u{308},".u.words.to_a end
  expect ["\u{ad}".u, "'".u] do "\u{ad}'".u.words.to_a end
  expect ["\u{ad}\u{308}".u, "'".u] do "\u{ad}\u{308}'".u.words.to_a end
  expect ["\u{ad}".u, "0".u] do "\u{ad}0".u.words.to_a end
  expect ["\u{ad}\u{308}".u, "0".u] do "\u{ad}\u{308}0".u.words.to_a end
  expect ["\u{ad}".u, "_".u] do "\u{ad}_".u.words.to_a end
  expect ["\u{ad}\u{308}".u, "_".u] do "\u{ad}\u{308}_".u.words.to_a end
  expect ["\u{ad}".u, "\u{1f1e6}".u] do "\u{ad}\u{1f1e6}".u.words.to_a end
  expect ["\u{ad}\u{308}".u, "\u{1f1e6}".u] do "\u{ad}\u{308}\u{1f1e6}".u.words.to_a end
  expect ["\u{ad}\u{ad}".u] do "\u{ad}\u{ad}".u.words.to_a end
  expect ["\u{ad}\u{308}\u{ad}".u] do "\u{ad}\u{308}\u{ad}".u.words.to_a end
  expect ["\u{ad}\u{300}".u] do "\u{ad}\u{300}".u.words.to_a end
  expect ["\u{ad}\u{308}\u{300}".u] do "\u{ad}\u{308}\u{300}".u.words.to_a end
  expect ["\u{ad}".u, "a\u{2060}".u] do "\u{ad}a\u{2060}".u.words.to_a end
  expect ["\u{ad}\u{308}".u, "a\u{2060}".u] do "\u{ad}\u{308}a\u{2060}".u.words.to_a end
  expect ["\u{ad}".u, "a".u, ":".u] do "\u{ad}a:".u.words.to_a end
  expect ["\u{ad}\u{308}".u, "a".u, ":".u] do "\u{ad}\u{308}a:".u.words.to_a end
  expect ["\u{ad}".u, "a".u, "'".u] do "\u{ad}a'".u.words.to_a end
  expect ["\u{ad}\u{308}".u, "a".u, "'".u] do "\u{ad}\u{308}a'".u.words.to_a end
  expect ["\u{ad}".u, "a".u, "'\u{2060}".u] do "\u{ad}a'\u{2060}".u.words.to_a end
  expect ["\u{ad}\u{308}".u, "a".u, "'\u{2060}".u] do "\u{ad}\u{308}a'\u{2060}".u.words.to_a end
  expect ["\u{ad}".u, "a".u, ",".u] do "\u{ad}a,".u.words.to_a end
  expect ["\u{ad}\u{308}".u, "a".u, ",".u] do "\u{ad}\u{308}a,".u.words.to_a end
  expect ["\u{ad}".u, "1".u, ":".u] do "\u{ad}1:".u.words.to_a end
  expect ["\u{ad}\u{308}".u, "1".u, ":".u] do "\u{ad}\u{308}1:".u.words.to_a end
  expect ["\u{ad}".u, "1".u, "'".u] do "\u{ad}1'".u.words.to_a end
  expect ["\u{ad}\u{308}".u, "1".u, "'".u] do "\u{ad}\u{308}1'".u.words.to_a end
  expect ["\u{ad}".u, "1".u, ",".u] do "\u{ad}1,".u.words.to_a end
  expect ["\u{ad}\u{308}".u, "1".u, ",".u] do "\u{ad}\u{308}1,".u.words.to_a end
  expect ["\u{ad}".u, "1".u, ".\u{2060}".u] do "\u{ad}1.\u{2060}".u.words.to_a end
  expect ["\u{ad}\u{308}".u, "1".u, ".\u{2060}".u] do "\u{ad}\u{308}1.\u{2060}".u.words.to_a end
  expect ["\u{300}".u, "\x01".u] do "\u{300}\x01".u.words.to_a end
  expect ["\u{300}\u{308}".u, "\x01".u] do "\u{300}\u{308}\x01".u.words.to_a end
  expect ["\u{300}".u, "\r".u] do "\u{300}\r".u.words.to_a end
  expect ["\u{300}\u{308}".u, "\r".u] do "\u{300}\u{308}\r".u.words.to_a end
  expect ["\u{300}".u, "\n".u] do "\u{300}\n".u.words.to_a end
  expect ["\u{300}\u{308}".u, "\n".u] do "\u{300}\u{308}\n".u.words.to_a end
  expect ["\u{300}".u, "\v".u] do "\u{300}\v".u.words.to_a end
  expect ["\u{300}\u{308}".u, "\v".u] do "\u{300}\u{308}\v".u.words.to_a end
  expect ["\u{300}".u, "\u{3031}".u] do "\u{300}\u{3031}".u.words.to_a end
  expect ["\u{300}\u{308}".u, "\u{3031}".u] do "\u{300}\u{308}\u{3031}".u.words.to_a end
  expect ["\u{300}".u, "A".u] do "\u{300}A".u.words.to_a end
  expect ["\u{300}\u{308}".u, "A".u] do "\u{300}\u{308}A".u.words.to_a end
  expect ["\u{300}".u, ":".u] do "\u{300}:".u.words.to_a end
  expect ["\u{300}\u{308}".u, ":".u] do "\u{300}\u{308}:".u.words.to_a end
  expect ["\u{300}".u, ",".u] do "\u{300},".u.words.to_a end
  expect ["\u{300}\u{308}".u, ",".u] do "\u{300}\u{308},".u.words.to_a end
  expect ["\u{300}".u, "'".u] do "\u{300}'".u.words.to_a end
  expect ["\u{300}\u{308}".u, "'".u] do "\u{300}\u{308}'".u.words.to_a end
  expect ["\u{300}".u, "0".u] do "\u{300}0".u.words.to_a end
  expect ["\u{300}\u{308}".u, "0".u] do "\u{300}\u{308}0".u.words.to_a end
  expect ["\u{300}".u, "_".u] do "\u{300}_".u.words.to_a end
  expect ["\u{300}\u{308}".u, "_".u] do "\u{300}\u{308}_".u.words.to_a end
  expect ["\u{300}".u, "\u{1f1e6}".u] do "\u{300}\u{1f1e6}".u.words.to_a end
  expect ["\u{300}\u{308}".u, "\u{1f1e6}".u] do "\u{300}\u{308}\u{1f1e6}".u.words.to_a end
  expect ["\u{300}\u{ad}".u] do "\u{300}\u{ad}".u.words.to_a end
  expect ["\u{300}\u{308}\u{ad}".u] do "\u{300}\u{308}\u{ad}".u.words.to_a end
  expect ["\u{300}\u{300}".u] do "\u{300}\u{300}".u.words.to_a end
  expect ["\u{300}\u{308}\u{300}".u] do "\u{300}\u{308}\u{300}".u.words.to_a end
  expect ["\u{300}".u, "a\u{2060}".u] do "\u{300}a\u{2060}".u.words.to_a end
  expect ["\u{300}\u{308}".u, "a\u{2060}".u] do "\u{300}\u{308}a\u{2060}".u.words.to_a end
  expect ["\u{300}".u, "a".u, ":".u] do "\u{300}a:".u.words.to_a end
  expect ["\u{300}\u{308}".u, "a".u, ":".u] do "\u{300}\u{308}a:".u.words.to_a end
  expect ["\u{300}".u, "a".u, "'".u] do "\u{300}a'".u.words.to_a end
  expect ["\u{300}\u{308}".u, "a".u, "'".u] do "\u{300}\u{308}a'".u.words.to_a end
  expect ["\u{300}".u, "a".u, "'\u{2060}".u] do "\u{300}a'\u{2060}".u.words.to_a end
  expect ["\u{300}\u{308}".u, "a".u, "'\u{2060}".u] do "\u{300}\u{308}a'\u{2060}".u.words.to_a end
  expect ["\u{300}".u, "a".u, ",".u] do "\u{300}a,".u.words.to_a end
  expect ["\u{300}\u{308}".u, "a".u, ",".u] do "\u{300}\u{308}a,".u.words.to_a end
  expect ["\u{300}".u, "1".u, ":".u] do "\u{300}1:".u.words.to_a end
  expect ["\u{300}\u{308}".u, "1".u, ":".u] do "\u{300}\u{308}1:".u.words.to_a end
  expect ["\u{300}".u, "1".u, "'".u] do "\u{300}1'".u.words.to_a end
  expect ["\u{300}\u{308}".u, "1".u, "'".u] do "\u{300}\u{308}1'".u.words.to_a end
  expect ["\u{300}".u, "1".u, ",".u] do "\u{300}1,".u.words.to_a end
  expect ["\u{300}\u{308}".u, "1".u, ",".u] do "\u{300}\u{308}1,".u.words.to_a end
  expect ["\u{300}".u, "1".u, ".\u{2060}".u] do "\u{300}1.\u{2060}".u.words.to_a end
  expect ["\u{300}\u{308}".u, "1".u, ".\u{2060}".u] do "\u{300}\u{308}1.\u{2060}".u.words.to_a end
  expect ["a\u{2060}".u, "\x01".u] do "a\u{2060}\x01".u.words.to_a end
  expect ["a\u{2060}\u{308}".u, "\x01".u] do "a\u{2060}\u{308}\x01".u.words.to_a end
  expect ["a\u{2060}".u, "\r".u] do "a\u{2060}\r".u.words.to_a end
  expect ["a\u{2060}\u{308}".u, "\r".u] do "a\u{2060}\u{308}\r".u.words.to_a end
  expect ["a\u{2060}".u, "\n".u] do "a\u{2060}\n".u.words.to_a end
  expect ["a\u{2060}\u{308}".u, "\n".u] do "a\u{2060}\u{308}\n".u.words.to_a end
  expect ["a\u{2060}".u, "\v".u] do "a\u{2060}\v".u.words.to_a end
  expect ["a\u{2060}\u{308}".u, "\v".u] do "a\u{2060}\u{308}\v".u.words.to_a end
  expect ["a\u{2060}".u, "\u{3031}".u] do "a\u{2060}\u{3031}".u.words.to_a end
  expect ["a\u{2060}\u{308}".u, "\u{3031}".u] do "a\u{2060}\u{308}\u{3031}".u.words.to_a end
  expect ["a\u{2060}A".u] do "a\u{2060}A".u.words.to_a end
  expect ["a\u{2060}\u{308}A".u] do "a\u{2060}\u{308}A".u.words.to_a end
  expect ["a\u{2060}".u, ":".u] do "a\u{2060}:".u.words.to_a end
  expect ["a\u{2060}\u{308}".u, ":".u] do "a\u{2060}\u{308}:".u.words.to_a end
  expect ["a\u{2060}".u, ",".u] do "a\u{2060},".u.words.to_a end
  expect ["a\u{2060}\u{308}".u, ",".u] do "a\u{2060}\u{308},".u.words.to_a end
  expect ["a\u{2060}".u, "'".u] do "a\u{2060}'".u.words.to_a end
  expect ["a\u{2060}\u{308}".u, "'".u] do "a\u{2060}\u{308}'".u.words.to_a end
  expect ["a\u{2060}0".u] do "a\u{2060}0".u.words.to_a end
  expect ["a\u{2060}\u{308}0".u] do "a\u{2060}\u{308}0".u.words.to_a end
  expect ["a\u{2060}_".u] do "a\u{2060}_".u.words.to_a end
  expect ["a\u{2060}\u{308}_".u] do "a\u{2060}\u{308}_".u.words.to_a end
  expect ["a\u{2060}".u, "\u{1f1e6}".u] do "a\u{2060}\u{1f1e6}".u.words.to_a end
  expect ["a\u{2060}\u{308}".u, "\u{1f1e6}".u] do "a\u{2060}\u{308}\u{1f1e6}".u.words.to_a end
  expect ["a\u{2060}\u{ad}".u] do "a\u{2060}\u{ad}".u.words.to_a end
  expect ["a\u{2060}\u{308}\u{ad}".u] do "a\u{2060}\u{308}\u{ad}".u.words.to_a end
  expect ["a\u{2060}\u{300}".u] do "a\u{2060}\u{300}".u.words.to_a end
  expect ["a\u{2060}\u{308}\u{300}".u] do "a\u{2060}\u{308}\u{300}".u.words.to_a end
  expect ["a\u{2060}a\u{2060}".u] do "a\u{2060}a\u{2060}".u.words.to_a end
  expect ["a\u{2060}\u{308}a\u{2060}".u] do "a\u{2060}\u{308}a\u{2060}".u.words.to_a end
  expect ["a\u{2060}a".u, ":".u] do "a\u{2060}a:".u.words.to_a end
  expect ["a\u{2060}\u{308}a".u, ":".u] do "a\u{2060}\u{308}a:".u.words.to_a end
  expect ["a\u{2060}a".u, "'".u] do "a\u{2060}a'".u.words.to_a end
  expect ["a\u{2060}\u{308}a".u, "'".u] do "a\u{2060}\u{308}a'".u.words.to_a end
  expect ["a\u{2060}a".u, "'\u{2060}".u] do "a\u{2060}a'\u{2060}".u.words.to_a end
  expect ["a\u{2060}\u{308}a".u, "'\u{2060}".u] do "a\u{2060}\u{308}a'\u{2060}".u.words.to_a end
  expect ["a\u{2060}a".u, ",".u] do "a\u{2060}a,".u.words.to_a end
  expect ["a\u{2060}\u{308}a".u, ",".u] do "a\u{2060}\u{308}a,".u.words.to_a end
  expect ["a\u{2060}1".u, ":".u] do "a\u{2060}1:".u.words.to_a end
  expect ["a\u{2060}\u{308}1".u, ":".u] do "a\u{2060}\u{308}1:".u.words.to_a end
  expect ["a\u{2060}1".u, "'".u] do "a\u{2060}1'".u.words.to_a end
  expect ["a\u{2060}\u{308}1".u, "'".u] do "a\u{2060}\u{308}1'".u.words.to_a end
  expect ["a\u{2060}1".u, ",".u] do "a\u{2060}1,".u.words.to_a end
  expect ["a\u{2060}\u{308}1".u, ",".u] do "a\u{2060}\u{308}1,".u.words.to_a end
  expect ["a\u{2060}1".u, ".\u{2060}".u] do "a\u{2060}1.\u{2060}".u.words.to_a end
  expect ["a\u{2060}\u{308}1".u, ".\u{2060}".u] do "a\u{2060}\u{308}1.\u{2060}".u.words.to_a end
  expect ["a".u, ":".u, "\x01".u] do "a:\x01".u.words.to_a end
  expect ["a".u, ":\u{308}".u, "\x01".u] do "a:\u{308}\x01".u.words.to_a end
  expect ["a".u, ":".u, "\r".u] do "a:\r".u.words.to_a end
  expect ["a".u, ":\u{308}".u, "\r".u] do "a:\u{308}\r".u.words.to_a end
  expect ["a".u, ":".u, "\n".u] do "a:\n".u.words.to_a end
  expect ["a".u, ":\u{308}".u, "\n".u] do "a:\u{308}\n".u.words.to_a end
  expect ["a".u, ":".u, "\v".u] do "a:\v".u.words.to_a end
  expect ["a".u, ":\u{308}".u, "\v".u] do "a:\u{308}\v".u.words.to_a end
  expect ["a".u, ":".u, "\u{3031}".u] do "a:\u{3031}".u.words.to_a end
  expect ["a".u, ":\u{308}".u, "\u{3031}".u] do "a:\u{308}\u{3031}".u.words.to_a end
  expect ["a:A".u] do "a:A".u.words.to_a end
  expect ["a:\u{308}A".u] do "a:\u{308}A".u.words.to_a end
  expect ["a".u, ":".u, ":".u] do "a::".u.words.to_a end
  expect ["a".u, ":\u{308}".u, ":".u] do "a:\u{308}:".u.words.to_a end
  expect ["a".u, ":".u, ",".u] do "a:,".u.words.to_a end
  expect ["a".u, ":\u{308}".u, ",".u] do "a:\u{308},".u.words.to_a end
  expect ["a".u, ":".u, "'".u] do "a:'".u.words.to_a end
  expect ["a".u, ":\u{308}".u, "'".u] do "a:\u{308}'".u.words.to_a end
  expect ["a".u, ":".u, "0".u] do "a:0".u.words.to_a end
  expect ["a".u, ":\u{308}".u, "0".u] do "a:\u{308}0".u.words.to_a end
  expect ["a".u, ":".u, "_".u] do "a:_".u.words.to_a end
  expect ["a".u, ":\u{308}".u, "_".u] do "a:\u{308}_".u.words.to_a end
  expect ["a".u, ":".u, "\u{1f1e6}".u] do "a:\u{1f1e6}".u.words.to_a end
  expect ["a".u, ":\u{308}".u, "\u{1f1e6}".u] do "a:\u{308}\u{1f1e6}".u.words.to_a end
  expect ["a".u, ":\u{ad}".u] do "a:\u{ad}".u.words.to_a end
  expect ["a".u, ":\u{308}\u{ad}".u] do "a:\u{308}\u{ad}".u.words.to_a end
  expect ["a".u, ":\u{300}".u] do "a:\u{300}".u.words.to_a end
  expect ["a".u, ":\u{308}\u{300}".u] do "a:\u{308}\u{300}".u.words.to_a end
  expect ["a:a\u{2060}".u] do "a:a\u{2060}".u.words.to_a end
  expect ["a:\u{308}a\u{2060}".u] do "a:\u{308}a\u{2060}".u.words.to_a end
  expect ["a:a".u, ":".u] do "a:a:".u.words.to_a end
  expect ["a:\u{308}a".u, ":".u] do "a:\u{308}a:".u.words.to_a end
  expect ["a:a".u, "'".u] do "a:a'".u.words.to_a end
  expect ["a:\u{308}a".u, "'".u] do "a:\u{308}a'".u.words.to_a end
  expect ["a:a".u, "'\u{2060}".u] do "a:a'\u{2060}".u.words.to_a end
  expect ["a:\u{308}a".u, "'\u{2060}".u] do "a:\u{308}a'\u{2060}".u.words.to_a end
  expect ["a:a".u, ",".u] do "a:a,".u.words.to_a end
  expect ["a:\u{308}a".u, ",".u] do "a:\u{308}a,".u.words.to_a end
  expect ["a".u, ":".u, "1".u, ":".u] do "a:1:".u.words.to_a end
  expect ["a".u, ":\u{308}".u, "1".u, ":".u] do "a:\u{308}1:".u.words.to_a end
  expect ["a".u, ":".u, "1".u, "'".u] do "a:1'".u.words.to_a end
  expect ["a".u, ":\u{308}".u, "1".u, "'".u] do "a:\u{308}1'".u.words.to_a end
  expect ["a".u, ":".u, "1".u, ",".u] do "a:1,".u.words.to_a end
  expect ["a".u, ":\u{308}".u, "1".u, ",".u] do "a:\u{308}1,".u.words.to_a end
  expect ["a".u, ":".u, "1".u, ".\u{2060}".u] do "a:1.\u{2060}".u.words.to_a end
  expect ["a".u, ":\u{308}".u, "1".u, ".\u{2060}".u] do "a:\u{308}1.\u{2060}".u.words.to_a end
  expect ["a".u, "'".u, "\x01".u] do "a'\x01".u.words.to_a end
  expect ["a".u, "'\u{308}".u, "\x01".u] do "a'\u{308}\x01".u.words.to_a end
  expect ["a".u, "'".u, "\r".u] do "a'\r".u.words.to_a end
  expect ["a".u, "'\u{308}".u, "\r".u] do "a'\u{308}\r".u.words.to_a end
  expect ["a".u, "'".u, "\n".u] do "a'\n".u.words.to_a end
  expect ["a".u, "'\u{308}".u, "\n".u] do "a'\u{308}\n".u.words.to_a end
  expect ["a".u, "'".u, "\v".u] do "a'\v".u.words.to_a end
  expect ["a".u, "'\u{308}".u, "\v".u] do "a'\u{308}\v".u.words.to_a end
  expect ["a".u, "'".u, "\u{3031}".u] do "a'\u{3031}".u.words.to_a end
  expect ["a".u, "'\u{308}".u, "\u{3031}".u] do "a'\u{308}\u{3031}".u.words.to_a end
  expect ["a'A".u] do "a'A".u.words.to_a end
  expect ["a'\u{308}A".u] do "a'\u{308}A".u.words.to_a end
  expect ["a".u, "'".u, ":".u] do "a':".u.words.to_a end
  expect ["a".u, "'\u{308}".u, ":".u] do "a'\u{308}:".u.words.to_a end
  expect ["a".u, "'".u, ",".u] do "a',".u.words.to_a end
  expect ["a".u, "'\u{308}".u, ",".u] do "a'\u{308},".u.words.to_a end
  expect ["a".u, "'".u, "'".u] do "a''".u.words.to_a end
  expect ["a".u, "'\u{308}".u, "'".u] do "a'\u{308}'".u.words.to_a end
  expect ["a".u, "'".u, "0".u] do "a'0".u.words.to_a end
  expect ["a".u, "'\u{308}".u, "0".u] do "a'\u{308}0".u.words.to_a end
  expect ["a".u, "'".u, "_".u] do "a'_".u.words.to_a end
  expect ["a".u, "'\u{308}".u, "_".u] do "a'\u{308}_".u.words.to_a end
  expect ["a".u, "'".u, "\u{1f1e6}".u] do "a'\u{1f1e6}".u.words.to_a end
  expect ["a".u, "'\u{308}".u, "\u{1f1e6}".u] do "a'\u{308}\u{1f1e6}".u.words.to_a end
  expect ["a".u, "'\u{ad}".u] do "a'\u{ad}".u.words.to_a end
  expect ["a".u, "'\u{308}\u{ad}".u] do "a'\u{308}\u{ad}".u.words.to_a end
  expect ["a".u, "'\u{300}".u] do "a'\u{300}".u.words.to_a end
  expect ["a".u, "'\u{308}\u{300}".u] do "a'\u{308}\u{300}".u.words.to_a end
  expect ["a'a\u{2060}".u] do "a'a\u{2060}".u.words.to_a end
  expect ["a'\u{308}a\u{2060}".u] do "a'\u{308}a\u{2060}".u.words.to_a end
  expect ["a'a".u, ":".u] do "a'a:".u.words.to_a end
  expect ["a'\u{308}a".u, ":".u] do "a'\u{308}a:".u.words.to_a end
  expect ["a'a".u, "'".u] do "a'a'".u.words.to_a end
  expect ["a'\u{308}a".u, "'".u] do "a'\u{308}a'".u.words.to_a end
  expect ["a'a".u, "'\u{2060}".u] do "a'a'\u{2060}".u.words.to_a end
  expect ["a'\u{308}a".u, "'\u{2060}".u] do "a'\u{308}a'\u{2060}".u.words.to_a end
  expect ["a'a".u, ",".u] do "a'a,".u.words.to_a end
  expect ["a'\u{308}a".u, ",".u] do "a'\u{308}a,".u.words.to_a end
  expect ["a".u, "'".u, "1".u, ":".u] do "a'1:".u.words.to_a end
  expect ["a".u, "'\u{308}".u, "1".u, ":".u] do "a'\u{308}1:".u.words.to_a end
  expect ["a".u, "'".u, "1".u, "'".u] do "a'1'".u.words.to_a end
  expect ["a".u, "'\u{308}".u, "1".u, "'".u] do "a'\u{308}1'".u.words.to_a end
  expect ["a".u, "'".u, "1".u, ",".u] do "a'1,".u.words.to_a end
  expect ["a".u, "'\u{308}".u, "1".u, ",".u] do "a'\u{308}1,".u.words.to_a end
  expect ["a".u, "'".u, "1".u, ".\u{2060}".u] do "a'1.\u{2060}".u.words.to_a end
  expect ["a".u, "'\u{308}".u, "1".u, ".\u{2060}".u] do "a'\u{308}1.\u{2060}".u.words.to_a end
  expect ["a".u, "'\u{2060}".u, "\x01".u] do "a'\u{2060}\x01".u.words.to_a end
  expect ["a".u, "'\u{2060}\u{308}".u, "\x01".u] do "a'\u{2060}\u{308}\x01".u.words.to_a end
  expect ["a".u, "'\u{2060}".u, "\r".u] do "a'\u{2060}\r".u.words.to_a end
  expect ["a".u, "'\u{2060}\u{308}".u, "\r".u] do "a'\u{2060}\u{308}\r".u.words.to_a end
  expect ["a".u, "'\u{2060}".u, "\n".u] do "a'\u{2060}\n".u.words.to_a end
  expect ["a".u, "'\u{2060}\u{308}".u, "\n".u] do "a'\u{2060}\u{308}\n".u.words.to_a end
  expect ["a".u, "'\u{2060}".u, "\v".u] do "a'\u{2060}\v".u.words.to_a end
  expect ["a".u, "'\u{2060}\u{308}".u, "\v".u] do "a'\u{2060}\u{308}\v".u.words.to_a end
  expect ["a".u, "'\u{2060}".u, "\u{3031}".u] do "a'\u{2060}\u{3031}".u.words.to_a end
  expect ["a".u, "'\u{2060}\u{308}".u, "\u{3031}".u] do "a'\u{2060}\u{308}\u{3031}".u.words.to_a end
  expect ["a'\u{2060}A".u] do "a'\u{2060}A".u.words.to_a end
  expect ["a'\u{2060}\u{308}A".u] do "a'\u{2060}\u{308}A".u.words.to_a end
  expect ["a".u, "'\u{2060}".u, ":".u] do "a'\u{2060}:".u.words.to_a end
  expect ["a".u, "'\u{2060}\u{308}".u, ":".u] do "a'\u{2060}\u{308}:".u.words.to_a end
  expect ["a".u, "'\u{2060}".u, ",".u] do "a'\u{2060},".u.words.to_a end
  expect ["a".u, "'\u{2060}\u{308}".u, ",".u] do "a'\u{2060}\u{308},".u.words.to_a end
  expect ["a".u, "'\u{2060}".u, "'".u] do "a'\u{2060}'".u.words.to_a end
  expect ["a".u, "'\u{2060}\u{308}".u, "'".u] do "a'\u{2060}\u{308}'".u.words.to_a end
  expect ["a".u, "'\u{2060}".u, "0".u] do "a'\u{2060}0".u.words.to_a end
  expect ["a".u, "'\u{2060}\u{308}".u, "0".u] do "a'\u{2060}\u{308}0".u.words.to_a end
  expect ["a".u, "'\u{2060}".u, "_".u] do "a'\u{2060}_".u.words.to_a end
  expect ["a".u, "'\u{2060}\u{308}".u, "_".u] do "a'\u{2060}\u{308}_".u.words.to_a end
  expect ["a".u, "'\u{2060}".u, "\u{1f1e6}".u] do "a'\u{2060}\u{1f1e6}".u.words.to_a end
  expect ["a".u, "'\u{2060}\u{308}".u, "\u{1f1e6}".u] do "a'\u{2060}\u{308}\u{1f1e6}".u.words.to_a end
  expect ["a".u, "'\u{2060}\u{ad}".u] do "a'\u{2060}\u{ad}".u.words.to_a end
  expect ["a".u, "'\u{2060}\u{308}\u{ad}".u] do "a'\u{2060}\u{308}\u{ad}".u.words.to_a end
  expect ["a".u, "'\u{2060}\u{300}".u] do "a'\u{2060}\u{300}".u.words.to_a end
  expect ["a".u, "'\u{2060}\u{308}\u{300}".u] do "a'\u{2060}\u{308}\u{300}".u.words.to_a end
  expect ["a'\u{2060}a\u{2060}".u] do "a'\u{2060}a\u{2060}".u.words.to_a end
  expect ["a'\u{2060}\u{308}a\u{2060}".u] do "a'\u{2060}\u{308}a\u{2060}".u.words.to_a end
  expect ["a'\u{2060}a".u, ":".u] do "a'\u{2060}a:".u.words.to_a end
  expect ["a'\u{2060}\u{308}a".u, ":".u] do "a'\u{2060}\u{308}a:".u.words.to_a end
  expect ["a'\u{2060}a".u, "'".u] do "a'\u{2060}a'".u.words.to_a end
  expect ["a'\u{2060}\u{308}a".u, "'".u] do "a'\u{2060}\u{308}a'".u.words.to_a end
  expect ["a'\u{2060}a".u, "'\u{2060}".u] do "a'\u{2060}a'\u{2060}".u.words.to_a end
  expect ["a'\u{2060}\u{308}a".u, "'\u{2060}".u] do "a'\u{2060}\u{308}a'\u{2060}".u.words.to_a end
  expect ["a'\u{2060}a".u, ",".u] do "a'\u{2060}a,".u.words.to_a end
  expect ["a'\u{2060}\u{308}a".u, ",".u] do "a'\u{2060}\u{308}a,".u.words.to_a end
  expect ["a".u, "'\u{2060}".u, "1".u, ":".u] do "a'\u{2060}1:".u.words.to_a end
  expect ["a".u, "'\u{2060}\u{308}".u, "1".u, ":".u] do "a'\u{2060}\u{308}1:".u.words.to_a end
  expect ["a".u, "'\u{2060}".u, "1".u, "'".u] do "a'\u{2060}1'".u.words.to_a end
  expect ["a".u, "'\u{2060}\u{308}".u, "1".u, "'".u] do "a'\u{2060}\u{308}1'".u.words.to_a end
  expect ["a".u, "'\u{2060}".u, "1".u, ",".u] do "a'\u{2060}1,".u.words.to_a end
  expect ["a".u, "'\u{2060}\u{308}".u, "1".u, ",".u] do "a'\u{2060}\u{308}1,".u.words.to_a end
  expect ["a".u, "'\u{2060}".u, "1".u, ".\u{2060}".u] do "a'\u{2060}1.\u{2060}".u.words.to_a end
  expect ["a".u, "'\u{2060}\u{308}".u, "1".u, ".\u{2060}".u] do "a'\u{2060}\u{308}1.\u{2060}".u.words.to_a end
  expect ["a".u, ",".u, "\x01".u] do "a,\x01".u.words.to_a end
  expect ["a".u, ",\u{308}".u, "\x01".u] do "a,\u{308}\x01".u.words.to_a end
  expect ["a".u, ",".u, "\r".u] do "a,\r".u.words.to_a end
  expect ["a".u, ",\u{308}".u, "\r".u] do "a,\u{308}\r".u.words.to_a end
  expect ["a".u, ",".u, "\n".u] do "a,\n".u.words.to_a end
  expect ["a".u, ",\u{308}".u, "\n".u] do "a,\u{308}\n".u.words.to_a end
  expect ["a".u, ",".u, "\v".u] do "a,\v".u.words.to_a end
  expect ["a".u, ",\u{308}".u, "\v".u] do "a,\u{308}\v".u.words.to_a end
  expect ["a".u, ",".u, "\u{3031}".u] do "a,\u{3031}".u.words.to_a end
  expect ["a".u, ",\u{308}".u, "\u{3031}".u] do "a,\u{308}\u{3031}".u.words.to_a end
  expect ["a".u, ",".u, "A".u] do "a,A".u.words.to_a end
  expect ["a".u, ",\u{308}".u, "A".u] do "a,\u{308}A".u.words.to_a end
  expect ["a".u, ",".u, ":".u] do "a,:".u.words.to_a end
  expect ["a".u, ",\u{308}".u, ":".u] do "a,\u{308}:".u.words.to_a end
  expect ["a".u, ",".u, ",".u] do "a,,".u.words.to_a end
  expect ["a".u, ",\u{308}".u, ",".u] do "a,\u{308},".u.words.to_a end
  expect ["a".u, ",".u, "'".u] do "a,'".u.words.to_a end
  expect ["a".u, ",\u{308}".u, "'".u] do "a,\u{308}'".u.words.to_a end
  expect ["a".u, ",".u, "0".u] do "a,0".u.words.to_a end
  expect ["a".u, ",\u{308}".u, "0".u] do "a,\u{308}0".u.words.to_a end
  expect ["a".u, ",".u, "_".u] do "a,_".u.words.to_a end
  expect ["a".u, ",\u{308}".u, "_".u] do "a,\u{308}_".u.words.to_a end
  expect ["a".u, ",".u, "\u{1f1e6}".u] do "a,\u{1f1e6}".u.words.to_a end
  expect ["a".u, ",\u{308}".u, "\u{1f1e6}".u] do "a,\u{308}\u{1f1e6}".u.words.to_a end
  expect ["a".u, ",\u{ad}".u] do "a,\u{ad}".u.words.to_a end
  expect ["a".u, ",\u{308}\u{ad}".u] do "a,\u{308}\u{ad}".u.words.to_a end
  expect ["a".u, ",\u{300}".u] do "a,\u{300}".u.words.to_a end
  expect ["a".u, ",\u{308}\u{300}".u] do "a,\u{308}\u{300}".u.words.to_a end
  expect ["a".u, ",".u, "a\u{2060}".u] do "a,a\u{2060}".u.words.to_a end
  expect ["a".u, ",\u{308}".u, "a\u{2060}".u] do "a,\u{308}a\u{2060}".u.words.to_a end
  expect ["a".u, ",".u, "a".u, ":".u] do "a,a:".u.words.to_a end
  expect ["a".u, ",\u{308}".u, "a".u, ":".u] do "a,\u{308}a:".u.words.to_a end
  expect ["a".u, ",".u, "a".u, "'".u] do "a,a'".u.words.to_a end
  expect ["a".u, ",\u{308}".u, "a".u, "'".u] do "a,\u{308}a'".u.words.to_a end
  expect ["a".u, ",".u, "a".u, "'\u{2060}".u] do "a,a'\u{2060}".u.words.to_a end
  expect ["a".u, ",\u{308}".u, "a".u, "'\u{2060}".u] do "a,\u{308}a'\u{2060}".u.words.to_a end
  expect ["a".u, ",".u, "a".u, ",".u] do "a,a,".u.words.to_a end
  expect ["a".u, ",\u{308}".u, "a".u, ",".u] do "a,\u{308}a,".u.words.to_a end
  expect ["a".u, ",".u, "1".u, ":".u] do "a,1:".u.words.to_a end
  expect ["a".u, ",\u{308}".u, "1".u, ":".u] do "a,\u{308}1:".u.words.to_a end
  expect ["a".u, ",".u, "1".u, "'".u] do "a,1'".u.words.to_a end
  expect ["a".u, ",\u{308}".u, "1".u, "'".u] do "a,\u{308}1'".u.words.to_a end
  expect ["a".u, ",".u, "1".u, ",".u] do "a,1,".u.words.to_a end
  expect ["a".u, ",\u{308}".u, "1".u, ",".u] do "a,\u{308}1,".u.words.to_a end
  expect ["a".u, ",".u, "1".u, ".\u{2060}".u] do "a,1.\u{2060}".u.words.to_a end
  expect ["a".u, ",\u{308}".u, "1".u, ".\u{2060}".u] do "a,\u{308}1.\u{2060}".u.words.to_a end
  expect ["1".u, ":".u, "\x01".u] do "1:\x01".u.words.to_a end
  expect ["1".u, ":\u{308}".u, "\x01".u] do "1:\u{308}\x01".u.words.to_a end
  expect ["1".u, ":".u, "\r".u] do "1:\r".u.words.to_a end
  expect ["1".u, ":\u{308}".u, "\r".u] do "1:\u{308}\r".u.words.to_a end
  expect ["1".u, ":".u, "\n".u] do "1:\n".u.words.to_a end
  expect ["1".u, ":\u{308}".u, "\n".u] do "1:\u{308}\n".u.words.to_a end
  expect ["1".u, ":".u, "\v".u] do "1:\v".u.words.to_a end
  expect ["1".u, ":\u{308}".u, "\v".u] do "1:\u{308}\v".u.words.to_a end
  expect ["1".u, ":".u, "\u{3031}".u] do "1:\u{3031}".u.words.to_a end
  expect ["1".u, ":\u{308}".u, "\u{3031}".u] do "1:\u{308}\u{3031}".u.words.to_a end
  expect ["1".u, ":".u, "A".u] do "1:A".u.words.to_a end
  expect ["1".u, ":\u{308}".u, "A".u] do "1:\u{308}A".u.words.to_a end
  expect ["1".u, ":".u, ":".u] do "1::".u.words.to_a end
  expect ["1".u, ":\u{308}".u, ":".u] do "1:\u{308}:".u.words.to_a end
  expect ["1".u, ":".u, ",".u] do "1:,".u.words.to_a end
  expect ["1".u, ":\u{308}".u, ",".u] do "1:\u{308},".u.words.to_a end
  expect ["1".u, ":".u, "'".u] do "1:'".u.words.to_a end
  expect ["1".u, ":\u{308}".u, "'".u] do "1:\u{308}'".u.words.to_a end
  expect ["1".u, ":".u, "0".u] do "1:0".u.words.to_a end
  expect ["1".u, ":\u{308}".u, "0".u] do "1:\u{308}0".u.words.to_a end
  expect ["1".u, ":".u, "_".u] do "1:_".u.words.to_a end
  expect ["1".u, ":\u{308}".u, "_".u] do "1:\u{308}_".u.words.to_a end
  expect ["1".u, ":".u, "\u{1f1e6}".u] do "1:\u{1f1e6}".u.words.to_a end
  expect ["1".u, ":\u{308}".u, "\u{1f1e6}".u] do "1:\u{308}\u{1f1e6}".u.words.to_a end
  expect ["1".u, ":\u{ad}".u] do "1:\u{ad}".u.words.to_a end
  expect ["1".u, ":\u{308}\u{ad}".u] do "1:\u{308}\u{ad}".u.words.to_a end
  expect ["1".u, ":\u{300}".u] do "1:\u{300}".u.words.to_a end
  expect ["1".u, ":\u{308}\u{300}".u] do "1:\u{308}\u{300}".u.words.to_a end
  expect ["1".u, ":".u, "a\u{2060}".u] do "1:a\u{2060}".u.words.to_a end
  expect ["1".u, ":\u{308}".u, "a\u{2060}".u] do "1:\u{308}a\u{2060}".u.words.to_a end
  expect ["1".u, ":".u, "a".u, ":".u] do "1:a:".u.words.to_a end
  expect ["1".u, ":\u{308}".u, "a".u, ":".u] do "1:\u{308}a:".u.words.to_a end
  expect ["1".u, ":".u, "a".u, "'".u] do "1:a'".u.words.to_a end
  expect ["1".u, ":\u{308}".u, "a".u, "'".u] do "1:\u{308}a'".u.words.to_a end
  expect ["1".u, ":".u, "a".u, "'\u{2060}".u] do "1:a'\u{2060}".u.words.to_a end
  expect ["1".u, ":\u{308}".u, "a".u, "'\u{2060}".u] do "1:\u{308}a'\u{2060}".u.words.to_a end
  expect ["1".u, ":".u, "a".u, ",".u] do "1:a,".u.words.to_a end
  expect ["1".u, ":\u{308}".u, "a".u, ",".u] do "1:\u{308}a,".u.words.to_a end
  expect ["1".u, ":".u, "1".u, ":".u] do "1:1:".u.words.to_a end
  expect ["1".u, ":\u{308}".u, "1".u, ":".u] do "1:\u{308}1:".u.words.to_a end
  expect ["1".u, ":".u, "1".u, "'".u] do "1:1'".u.words.to_a end
  expect ["1".u, ":\u{308}".u, "1".u, "'".u] do "1:\u{308}1'".u.words.to_a end
  expect ["1".u, ":".u, "1".u, ",".u] do "1:1,".u.words.to_a end
  expect ["1".u, ":\u{308}".u, "1".u, ",".u] do "1:\u{308}1,".u.words.to_a end
  expect ["1".u, ":".u, "1".u, ".\u{2060}".u] do "1:1.\u{2060}".u.words.to_a end
  expect ["1".u, ":\u{308}".u, "1".u, ".\u{2060}".u] do "1:\u{308}1.\u{2060}".u.words.to_a end
  expect ["1".u, "'".u, "\x01".u] do "1'\x01".u.words.to_a end
  expect ["1".u, "'\u{308}".u, "\x01".u] do "1'\u{308}\x01".u.words.to_a end
  expect ["1".u, "'".u, "\r".u] do "1'\r".u.words.to_a end
  expect ["1".u, "'\u{308}".u, "\r".u] do "1'\u{308}\r".u.words.to_a end
  expect ["1".u, "'".u, "\n".u] do "1'\n".u.words.to_a end
  expect ["1".u, "'\u{308}".u, "\n".u] do "1'\u{308}\n".u.words.to_a end
  expect ["1".u, "'".u, "\v".u] do "1'\v".u.words.to_a end
  expect ["1".u, "'\u{308}".u, "\v".u] do "1'\u{308}\v".u.words.to_a end
  expect ["1".u, "'".u, "\u{3031}".u] do "1'\u{3031}".u.words.to_a end
  expect ["1".u, "'\u{308}".u, "\u{3031}".u] do "1'\u{308}\u{3031}".u.words.to_a end
  expect ["1".u, "'".u, "A".u] do "1'A".u.words.to_a end
  expect ["1".u, "'\u{308}".u, "A".u] do "1'\u{308}A".u.words.to_a end
  expect ["1".u, "'".u, ":".u] do "1':".u.words.to_a end
  expect ["1".u, "'\u{308}".u, ":".u] do "1'\u{308}:".u.words.to_a end
  expect ["1".u, "'".u, ",".u] do "1',".u.words.to_a end
  expect ["1".u, "'\u{308}".u, ",".u] do "1'\u{308},".u.words.to_a end
  expect ["1".u, "'".u, "'".u] do "1''".u.words.to_a end
  expect ["1".u, "'\u{308}".u, "'".u] do "1'\u{308}'".u.words.to_a end
  expect ["1'0".u] do "1'0".u.words.to_a end
  expect ["1'\u{308}0".u] do "1'\u{308}0".u.words.to_a end
  expect ["1".u, "'".u, "_".u] do "1'_".u.words.to_a end
  expect ["1".u, "'\u{308}".u, "_".u] do "1'\u{308}_".u.words.to_a end
  expect ["1".u, "'".u, "\u{1f1e6}".u] do "1'\u{1f1e6}".u.words.to_a end
  expect ["1".u, "'\u{308}".u, "\u{1f1e6}".u] do "1'\u{308}\u{1f1e6}".u.words.to_a end
  expect ["1".u, "'\u{ad}".u] do "1'\u{ad}".u.words.to_a end
  expect ["1".u, "'\u{308}\u{ad}".u] do "1'\u{308}\u{ad}".u.words.to_a end
  expect ["1".u, "'\u{300}".u] do "1'\u{300}".u.words.to_a end
  expect ["1".u, "'\u{308}\u{300}".u] do "1'\u{308}\u{300}".u.words.to_a end
  expect ["1".u, "'".u, "a\u{2060}".u] do "1'a\u{2060}".u.words.to_a end
  expect ["1".u, "'\u{308}".u, "a\u{2060}".u] do "1'\u{308}a\u{2060}".u.words.to_a end
  expect ["1".u, "'".u, "a".u, ":".u] do "1'a:".u.words.to_a end
  expect ["1".u, "'\u{308}".u, "a".u, ":".u] do "1'\u{308}a:".u.words.to_a end
  expect ["1".u, "'".u, "a".u, "'".u] do "1'a'".u.words.to_a end
  expect ["1".u, "'\u{308}".u, "a".u, "'".u] do "1'\u{308}a'".u.words.to_a end
  expect ["1".u, "'".u, "a".u, "'\u{2060}".u] do "1'a'\u{2060}".u.words.to_a end
  expect ["1".u, "'\u{308}".u, "a".u, "'\u{2060}".u] do "1'\u{308}a'\u{2060}".u.words.to_a end
  expect ["1".u, "'".u, "a".u, ",".u] do "1'a,".u.words.to_a end
  expect ["1".u, "'\u{308}".u, "a".u, ",".u] do "1'\u{308}a,".u.words.to_a end
  expect ["1'1".u, ":".u] do "1'1:".u.words.to_a end
  expect ["1'\u{308}1".u, ":".u] do "1'\u{308}1:".u.words.to_a end
  expect ["1'1".u, "'".u] do "1'1'".u.words.to_a end
  expect ["1'\u{308}1".u, "'".u] do "1'\u{308}1'".u.words.to_a end
  expect ["1'1".u, ",".u] do "1'1,".u.words.to_a end
  expect ["1'\u{308}1".u, ",".u] do "1'\u{308}1,".u.words.to_a end
  expect ["1'1".u, ".\u{2060}".u] do "1'1.\u{2060}".u.words.to_a end
  expect ["1'\u{308}1".u, ".\u{2060}".u] do "1'\u{308}1.\u{2060}".u.words.to_a end
  expect ["1".u, ",".u, "\x01".u] do "1,\x01".u.words.to_a end
  expect ["1".u, ",\u{308}".u, "\x01".u] do "1,\u{308}\x01".u.words.to_a end
  expect ["1".u, ",".u, "\r".u] do "1,\r".u.words.to_a end
  expect ["1".u, ",\u{308}".u, "\r".u] do "1,\u{308}\r".u.words.to_a end
  expect ["1".u, ",".u, "\n".u] do "1,\n".u.words.to_a end
  expect ["1".u, ",\u{308}".u, "\n".u] do "1,\u{308}\n".u.words.to_a end
  expect ["1".u, ",".u, "\v".u] do "1,\v".u.words.to_a end
  expect ["1".u, ",\u{308}".u, "\v".u] do "1,\u{308}\v".u.words.to_a end
  expect ["1".u, ",".u, "\u{3031}".u] do "1,\u{3031}".u.words.to_a end
  expect ["1".u, ",\u{308}".u, "\u{3031}".u] do "1,\u{308}\u{3031}".u.words.to_a end
  expect ["1".u, ",".u, "A".u] do "1,A".u.words.to_a end
  expect ["1".u, ",\u{308}".u, "A".u] do "1,\u{308}A".u.words.to_a end
  expect ["1".u, ",".u, ":".u] do "1,:".u.words.to_a end
  expect ["1".u, ",\u{308}".u, ":".u] do "1,\u{308}:".u.words.to_a end
  expect ["1".u, ",".u, ",".u] do "1,,".u.words.to_a end
  expect ["1".u, ",\u{308}".u, ",".u] do "1,\u{308},".u.words.to_a end
  expect ["1".u, ",".u, "'".u] do "1,'".u.words.to_a end
  expect ["1".u, ",\u{308}".u, "'".u] do "1,\u{308}'".u.words.to_a end
  expect ["1,0".u] do "1,0".u.words.to_a end
  expect ["1,\u{308}0".u] do "1,\u{308}0".u.words.to_a end
  expect ["1".u, ",".u, "_".u] do "1,_".u.words.to_a end
  expect ["1".u, ",\u{308}".u, "_".u] do "1,\u{308}_".u.words.to_a end
  expect ["1".u, ",".u, "\u{1f1e6}".u] do "1,\u{1f1e6}".u.words.to_a end
  expect ["1".u, ",\u{308}".u, "\u{1f1e6}".u] do "1,\u{308}\u{1f1e6}".u.words.to_a end
  expect ["1".u, ",\u{ad}".u] do "1,\u{ad}".u.words.to_a end
  expect ["1".u, ",\u{308}\u{ad}".u] do "1,\u{308}\u{ad}".u.words.to_a end
  expect ["1".u, ",\u{300}".u] do "1,\u{300}".u.words.to_a end
  expect ["1".u, ",\u{308}\u{300}".u] do "1,\u{308}\u{300}".u.words.to_a end
  expect ["1".u, ",".u, "a\u{2060}".u] do "1,a\u{2060}".u.words.to_a end
  expect ["1".u, ",\u{308}".u, "a\u{2060}".u] do "1,\u{308}a\u{2060}".u.words.to_a end
  expect ["1".u, ",".u, "a".u, ":".u] do "1,a:".u.words.to_a end
  expect ["1".u, ",\u{308}".u, "a".u, ":".u] do "1,\u{308}a:".u.words.to_a end
  expect ["1".u, ",".u, "a".u, "'".u] do "1,a'".u.words.to_a end
  expect ["1".u, ",\u{308}".u, "a".u, "'".u] do "1,\u{308}a'".u.words.to_a end
  expect ["1".u, ",".u, "a".u, "'\u{2060}".u] do "1,a'\u{2060}".u.words.to_a end
  expect ["1".u, ",\u{308}".u, "a".u, "'\u{2060}".u] do "1,\u{308}a'\u{2060}".u.words.to_a end
  expect ["1".u, ",".u, "a".u, ",".u] do "1,a,".u.words.to_a end
  expect ["1".u, ",\u{308}".u, "a".u, ",".u] do "1,\u{308}a,".u.words.to_a end
  expect ["1,1".u, ":".u] do "1,1:".u.words.to_a end
  expect ["1,\u{308}1".u, ":".u] do "1,\u{308}1:".u.words.to_a end
  expect ["1,1".u, "'".u] do "1,1'".u.words.to_a end
  expect ["1,\u{308}1".u, "'".u] do "1,\u{308}1'".u.words.to_a end
  expect ["1,1".u, ",".u] do "1,1,".u.words.to_a end
  expect ["1,\u{308}1".u, ",".u] do "1,\u{308}1,".u.words.to_a end
  expect ["1,1".u, ".\u{2060}".u] do "1,1.\u{2060}".u.words.to_a end
  expect ["1,\u{308}1".u, ".\u{2060}".u] do "1,\u{308}1.\u{2060}".u.words.to_a end
  expect ["1".u, ".\u{2060}".u, "\x01".u] do "1.\u{2060}\x01".u.words.to_a end
  expect ["1".u, ".\u{2060}\u{308}".u, "\x01".u] do "1.\u{2060}\u{308}\x01".u.words.to_a end
  expect ["1".u, ".\u{2060}".u, "\r".u] do "1.\u{2060}\r".u.words.to_a end
  expect ["1".u, ".\u{2060}\u{308}".u, "\r".u] do "1.\u{2060}\u{308}\r".u.words.to_a end
  expect ["1".u, ".\u{2060}".u, "\n".u] do "1.\u{2060}\n".u.words.to_a end
  expect ["1".u, ".\u{2060}\u{308}".u, "\n".u] do "1.\u{2060}\u{308}\n".u.words.to_a end
  expect ["1".u, ".\u{2060}".u, "\v".u] do "1.\u{2060}\v".u.words.to_a end
  expect ["1".u, ".\u{2060}\u{308}".u, "\v".u] do "1.\u{2060}\u{308}\v".u.words.to_a end
  expect ["1".u, ".\u{2060}".u, "\u{3031}".u] do "1.\u{2060}\u{3031}".u.words.to_a end
  expect ["1".u, ".\u{2060}\u{308}".u, "\u{3031}".u] do "1.\u{2060}\u{308}\u{3031}".u.words.to_a end
  expect ["1".u, ".\u{2060}".u, "A".u] do "1.\u{2060}A".u.words.to_a end
  expect ["1".u, ".\u{2060}\u{308}".u, "A".u] do "1.\u{2060}\u{308}A".u.words.to_a end
  expect ["1".u, ".\u{2060}".u, ":".u] do "1.\u{2060}:".u.words.to_a end
  expect ["1".u, ".\u{2060}\u{308}".u, ":".u] do "1.\u{2060}\u{308}:".u.words.to_a end
  expect ["1".u, ".\u{2060}".u, ",".u] do "1.\u{2060},".u.words.to_a end
  expect ["1".u, ".\u{2060}\u{308}".u, ",".u] do "1.\u{2060}\u{308},".u.words.to_a end
  expect ["1".u, ".\u{2060}".u, "'".u] do "1.\u{2060}'".u.words.to_a end
  expect ["1".u, ".\u{2060}\u{308}".u, "'".u] do "1.\u{2060}\u{308}'".u.words.to_a end
  expect ["1.\u{2060}0".u] do "1.\u{2060}0".u.words.to_a end
  expect ["1.\u{2060}\u{308}0".u] do "1.\u{2060}\u{308}0".u.words.to_a end
  expect ["1".u, ".\u{2060}".u, "_".u] do "1.\u{2060}_".u.words.to_a end
  expect ["1".u, ".\u{2060}\u{308}".u, "_".u] do "1.\u{2060}\u{308}_".u.words.to_a end
  expect ["1".u, ".\u{2060}".u, "\u{1f1e6}".u] do "1.\u{2060}\u{1f1e6}".u.words.to_a end
  expect ["1".u, ".\u{2060}\u{308}".u, "\u{1f1e6}".u] do "1.\u{2060}\u{308}\u{1f1e6}".u.words.to_a end
  expect ["1".u, ".\u{2060}\u{ad}".u] do "1.\u{2060}\u{ad}".u.words.to_a end
  expect ["1".u, ".\u{2060}\u{308}\u{ad}".u] do "1.\u{2060}\u{308}\u{ad}".u.words.to_a end
  expect ["1".u, ".\u{2060}\u{300}".u] do "1.\u{2060}\u{300}".u.words.to_a end
  expect ["1".u, ".\u{2060}\u{308}\u{300}".u] do "1.\u{2060}\u{308}\u{300}".u.words.to_a end
  expect ["1".u, ".\u{2060}".u, "a\u{2060}".u] do "1.\u{2060}a\u{2060}".u.words.to_a end
  expect ["1".u, ".\u{2060}\u{308}".u, "a\u{2060}".u] do "1.\u{2060}\u{308}a\u{2060}".u.words.to_a end
  expect ["1".u, ".\u{2060}".u, "a".u, ":".u] do "1.\u{2060}a:".u.words.to_a end
  expect ["1".u, ".\u{2060}\u{308}".u, "a".u, ":".u] do "1.\u{2060}\u{308}a:".u.words.to_a end
  expect ["1".u, ".\u{2060}".u, "a".u, "'".u] do "1.\u{2060}a'".u.words.to_a end
  expect ["1".u, ".\u{2060}\u{308}".u, "a".u, "'".u] do "1.\u{2060}\u{308}a'".u.words.to_a end
  expect ["1".u, ".\u{2060}".u, "a".u, "'\u{2060}".u] do "1.\u{2060}a'\u{2060}".u.words.to_a end
  expect ["1".u, ".\u{2060}\u{308}".u, "a".u, "'\u{2060}".u] do "1.\u{2060}\u{308}a'\u{2060}".u.words.to_a end
  expect ["1".u, ".\u{2060}".u, "a".u, ",".u] do "1.\u{2060}a,".u.words.to_a end
  expect ["1".u, ".\u{2060}\u{308}".u, "a".u, ",".u] do "1.\u{2060}\u{308}a,".u.words.to_a end
  expect ["1.\u{2060}1".u, ":".u] do "1.\u{2060}1:".u.words.to_a end
  expect ["1.\u{2060}\u{308}1".u, ":".u] do "1.\u{2060}\u{308}1:".u.words.to_a end
  expect ["1.\u{2060}1".u, "'".u] do "1.\u{2060}1'".u.words.to_a end
  expect ["1.\u{2060}\u{308}1".u, "'".u] do "1.\u{2060}\u{308}1'".u.words.to_a end
  expect ["1.\u{2060}1".u, ",".u] do "1.\u{2060}1,".u.words.to_a end
  expect ["1.\u{2060}\u{308}1".u, ",".u] do "1.\u{2060}\u{308}1,".u.words.to_a end
  expect ["1.\u{2060}1".u, ".\u{2060}".u] do "1.\u{2060}1.\u{2060}".u.words.to_a end
  expect ["1.\u{2060}\u{308}1".u, ".\u{2060}".u] do "1.\u{2060}\u{308}1.\u{2060}".u.words.to_a end
  expect ["can't".u] do "can't".u.words.to_a end
  expect ["can\u{2019}t".u] do "can\u{2019}t".u.words.to_a end
  expect ["ab\u{ad}by".u] do "ab\u{ad}by".u.words.to_a end
  expect ["a".u, "$".u, "-".u, "34,567.14".u, "%".u, "b".u] do "a$-34,567.14%b".u.words.to_a end
  expect ["3a".u] do "3a".u.words.to_a end
  expect ["\u{2060}".u, "c\u{2060}a\u{2060}n\u{2060}'\u{2060}t\u{2060}\u{2060}".u] do "\u{2060}c\u{2060}a\u{2060}n\u{2060}'\u{2060}t\u{2060}\u{2060}".u.words.to_a end
  expect ["\u{2060}".u, "c\u{2060}a\u{2060}n\u{2060}\u{2019}\u{2060}t\u{2060}\u{2060}".u] do "\u{2060}c\u{2060}a\u{2060}n\u{2060}\u{2019}\u{2060}t\u{2060}\u{2060}".u.words.to_a end
  expect ["\u{2060}".u, "a\u{2060}b\u{2060}\u{ad}\u{2060}b\u{2060}y\u{2060}\u{2060}".u] do "\u{2060}a\u{2060}b\u{2060}\u{ad}\u{2060}b\u{2060}y\u{2060}\u{2060}".u.words.to_a end
  expect ["\u{2060}".u, "a\u{2060}".u, "$\u{2060}".u, "-\u{2060}".u, "3\u{2060}4\u{2060},\u{2060}5\u{2060}6\u{2060}7\u{2060}.\u{2060}1\u{2060}4\u{2060}".u, "%\u{2060}".u, "b\u{2060}\u{2060}".u] do "\u{2060}a\u{2060}$\u{2060}-\u{2060}3\u{2060}4\u{2060},\u{2060}5\u{2060}6\u{2060}7\u{2060}.\u{2060}1\u{2060}4\u{2060}%\u{2060}b\u{2060}\u{2060}".u.words.to_a end
  expect ["\u{2060}".u, "3\u{2060}a\u{2060}\u{2060}".u] do "\u{2060}3\u{2060}a\u{2060}\u{2060}".u.words.to_a end
  expect ["a".u, "\u{1f1e6}".u, "b".u] do "a\u{1f1e6}b".u.words.to_a end
  expect ["\u{1f1f7}\u{1f1fa}".u] do "\u{1f1f7}\u{1f1fa}".u.words.to_a end
  expect ["\u{1f1f7}\u{1f1fa}\u{1f1f8}".u] do "\u{1f1f7}\u{1f1fa}\u{1f1f8}".u.words.to_a end
  expect ["\u{1f1f7}\u{1f1fa}\u{1f1f8}\u{1f1ea}".u] do "\u{1f1f7}\u{1f1fa}\u{1f1f8}\u{1f1ea}".u.words.to_a end
  expect ["\u{1f1f7}\u{1f1fa}".u, "\u{200b}".u, "\u{1f1f8}\u{1f1ea}".u] do "\u{1f1f7}\u{1f1fa}\u{200b}\u{1f1f8}\u{1f1ea}".u.words.to_a end
  expect ["\u{1f1e6}\u{1f1e7}\u{1f1e8}".u] do "\u{1f1e6}\u{1f1e7}\u{1f1e8}".u.words.to_a end
  expect ["\u{1f1e6}\u{200d}\u{1f1e7}\u{1f1e8}".u] do "\u{1f1e6}\u{200d}\u{1f1e7}\u{1f1e8}".u.words.to_a end
  expect ["\u{1f1e6}\u{1f1e7}\u{200d}\u{1f1e8}".u] do "\u{1f1e6}\u{1f1e7}\u{200d}\u{1f1e8}".u.words.to_a end
  expect [" \u{200d}".u, "\u{646}".u] do " \u{200d}\u{646}".u.words.to_a end
  expect ["\u{646}\u{200d}".u, " ".u] do "\u{646}\u{200d} ".u.words.to_a end
end
