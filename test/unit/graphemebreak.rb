# -*- coding: utf-8 -*-
# Automatically generated, so don’t edit!

Expectations do
  expect ["\u{0020}".u, "\u{0020}".u] do "\u{0020}\u{0020}".u.grapheme_clusters.to_a end
  expect ["\u{0020}\u{0308}".u, "\u{0020}".u] do "\u{0020}\u{0308}\u{0020}".u.grapheme_clusters.to_a end
  expect ["\u{0020}".u, "\u{000D}".u] do "\u{0020}\u{000D}".u.grapheme_clusters.to_a end
  expect ["\u{0020}\u{0308}".u, "\u{000D}".u] do "\u{0020}\u{0308}\u{000D}".u.grapheme_clusters.to_a end
  expect ["\u{0020}".u, "\u{000A}".u] do "\u{0020}\u{000A}".u.grapheme_clusters.to_a end
  expect ["\u{0020}\u{0308}".u, "\u{000A}".u] do "\u{0020}\u{0308}\u{000A}".u.grapheme_clusters.to_a end
  expect ["\u{0020}".u, "\u{0001}".u] do "\u{0020}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{0020}\u{0308}".u, "\u{0001}".u] do "\u{0020}\u{0308}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{0020}\u{0300}".u] do "\u{0020}\u{0300}".u.grapheme_clusters.to_a end
  expect ["\u{0020}\u{0308}\u{0300}".u] do "\u{0020}\u{0308}\u{0300}".u.grapheme_clusters.to_a end
  expect ["\u{0020}\u{0903}".u] do "\u{0020}\u{0903}".u.grapheme_clusters.to_a end
  expect ["\u{0020}\u{0308}\u{0903}".u] do "\u{0020}\u{0308}\u{0903}".u.grapheme_clusters.to_a end
  expect ["\u{0020}".u, "\u{1100}".u] do "\u{0020}\u{1100}".u.grapheme_clusters.to_a end
  expect ["\u{0020}\u{0308}".u, "\u{1100}".u] do "\u{0020}\u{0308}\u{1100}".u.grapheme_clusters.to_a end
  expect ["\u{0020}".u, "\u{1160}".u] do "\u{0020}\u{1160}".u.grapheme_clusters.to_a end
  expect ["\u{0020}\u{0308}".u, "\u{1160}".u] do "\u{0020}\u{0308}\u{1160}".u.grapheme_clusters.to_a end
  expect ["\u{0020}".u, "\u{11A8}".u] do "\u{0020}\u{11A8}".u.grapheme_clusters.to_a end
  expect ["\u{0020}\u{0308}".u, "\u{11A8}".u] do "\u{0020}\u{0308}\u{11A8}".u.grapheme_clusters.to_a end
  expect ["\u{0020}".u, "\u{AC00}".u] do "\u{0020}\u{AC00}".u.grapheme_clusters.to_a end
  expect ["\u{0020}\u{0308}".u, "\u{AC00}".u] do "\u{0020}\u{0308}\u{AC00}".u.grapheme_clusters.to_a end
  expect ["\u{0020}".u, "\u{AC01}".u] do "\u{0020}\u{AC01}".u.grapheme_clusters.to_a end
  expect ["\u{0020}\u{0308}".u, "\u{AC01}".u] do "\u{0020}\u{0308}\u{AC01}".u.grapheme_clusters.to_a end
  expect ["\u{0020}".u, "\u{1F1E6}".u] do "\u{0020}\u{1F1E6}".u.grapheme_clusters.to_a end
  expect ["\u{0020}\u{0308}".u, "\u{1F1E6}".u] do "\u{0020}\u{0308}\u{1F1E6}".u.grapheme_clusters.to_a end
  expect ["\u{0020}".u, "\u{0378}".u] do "\u{0020}\u{0378}".u.grapheme_clusters.to_a end
  expect ["\u{0020}\u{0308}".u, "\u{0378}".u] do "\u{0020}\u{0308}\u{0378}".u.grapheme_clusters.to_a end
  expect ["\u{0020}".u, "\u{0001}".u] do "\u{0020}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{0020}\u{0308}".u, "\u{0001}".u] do "\u{0020}\u{0308}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{000D}".u, "\u{0020}".u] do "\u{000D}\u{0020}".u.grapheme_clusters.to_a end
  expect ["\u{000D}".u, "\u{0308}".u, "\u{0020}".u] do "\u{000D}\u{0308}\u{0020}".u.grapheme_clusters.to_a end
  expect ["\u{000D}".u, "\u{000D}".u] do "\u{000D}\u{000D}".u.grapheme_clusters.to_a end
  expect ["\u{000D}".u, "\u{0308}".u, "\u{000D}".u] do "\u{000D}\u{0308}\u{000D}".u.grapheme_clusters.to_a end
  expect ["\u{000D}\u{000A}".u] do "\u{000D}\u{000A}".u.grapheme_clusters.to_a end
  expect ["\u{000D}".u, "\u{0308}".u, "\u{000A}".u] do "\u{000D}\u{0308}\u{000A}".u.grapheme_clusters.to_a end
  expect ["\u{000D}".u, "\u{0001}".u] do "\u{000D}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{000D}".u, "\u{0308}".u, "\u{0001}".u] do "\u{000D}\u{0308}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{000D}".u, "\u{0300}".u] do "\u{000D}\u{0300}".u.grapheme_clusters.to_a end
  expect ["\u{000D}".u, "\u{0308}\u{0300}".u] do "\u{000D}\u{0308}\u{0300}".u.grapheme_clusters.to_a end
  expect ["\u{000D}".u, "\u{0903}".u] do "\u{000D}\u{0903}".u.grapheme_clusters.to_a end
  expect ["\u{000D}".u, "\u{0308}\u{0903}".u] do "\u{000D}\u{0308}\u{0903}".u.grapheme_clusters.to_a end
  expect ["\u{000D}".u, "\u{1100}".u] do "\u{000D}\u{1100}".u.grapheme_clusters.to_a end
  expect ["\u{000D}".u, "\u{0308}".u, "\u{1100}".u] do "\u{000D}\u{0308}\u{1100}".u.grapheme_clusters.to_a end
  expect ["\u{000D}".u, "\u{1160}".u] do "\u{000D}\u{1160}".u.grapheme_clusters.to_a end
  expect ["\u{000D}".u, "\u{0308}".u, "\u{1160}".u] do "\u{000D}\u{0308}\u{1160}".u.grapheme_clusters.to_a end
  expect ["\u{000D}".u, "\u{11A8}".u] do "\u{000D}\u{11A8}".u.grapheme_clusters.to_a end
  expect ["\u{000D}".u, "\u{0308}".u, "\u{11A8}".u] do "\u{000D}\u{0308}\u{11A8}".u.grapheme_clusters.to_a end
  expect ["\u{000D}".u, "\u{AC00}".u] do "\u{000D}\u{AC00}".u.grapheme_clusters.to_a end
  expect ["\u{000D}".u, "\u{0308}".u, "\u{AC00}".u] do "\u{000D}\u{0308}\u{AC00}".u.grapheme_clusters.to_a end
  expect ["\u{000D}".u, "\u{AC01}".u] do "\u{000D}\u{AC01}".u.grapheme_clusters.to_a end
  expect ["\u{000D}".u, "\u{0308}".u, "\u{AC01}".u] do "\u{000D}\u{0308}\u{AC01}".u.grapheme_clusters.to_a end
  expect ["\u{000D}".u, "\u{1F1E6}".u] do "\u{000D}\u{1F1E6}".u.grapheme_clusters.to_a end
  expect ["\u{000D}".u, "\u{0308}".u, "\u{1F1E6}".u] do "\u{000D}\u{0308}\u{1F1E6}".u.grapheme_clusters.to_a end
  expect ["\u{000D}".u, "\u{0378}".u] do "\u{000D}\u{0378}".u.grapheme_clusters.to_a end
  expect ["\u{000D}".u, "\u{0308}".u, "\u{0378}".u] do "\u{000D}\u{0308}\u{0378}".u.grapheme_clusters.to_a end
  expect ["\u{000D}".u, "\u{0001}".u] do "\u{000D}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{000D}".u, "\u{0308}".u, "\u{0001}".u] do "\u{000D}\u{0308}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{000A}".u, "\u{0020}".u] do "\u{000A}\u{0020}".u.grapheme_clusters.to_a end
  expect ["\u{000A}".u, "\u{0308}".u, "\u{0020}".u] do "\u{000A}\u{0308}\u{0020}".u.grapheme_clusters.to_a end
  expect ["\u{000A}".u, "\u{000D}".u] do "\u{000A}\u{000D}".u.grapheme_clusters.to_a end
  expect ["\u{000A}".u, "\u{0308}".u, "\u{000D}".u] do "\u{000A}\u{0308}\u{000D}".u.grapheme_clusters.to_a end
  expect ["\u{000A}".u, "\u{000A}".u] do "\u{000A}\u{000A}".u.grapheme_clusters.to_a end
  expect ["\u{000A}".u, "\u{0308}".u, "\u{000A}".u] do "\u{000A}\u{0308}\u{000A}".u.grapheme_clusters.to_a end
  expect ["\u{000A}".u, "\u{0001}".u] do "\u{000A}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{000A}".u, "\u{0308}".u, "\u{0001}".u] do "\u{000A}\u{0308}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{000A}".u, "\u{0300}".u] do "\u{000A}\u{0300}".u.grapheme_clusters.to_a end
  expect ["\u{000A}".u, "\u{0308}\u{0300}".u] do "\u{000A}\u{0308}\u{0300}".u.grapheme_clusters.to_a end
  expect ["\u{000A}".u, "\u{0903}".u] do "\u{000A}\u{0903}".u.grapheme_clusters.to_a end
  expect ["\u{000A}".u, "\u{0308}\u{0903}".u] do "\u{000A}\u{0308}\u{0903}".u.grapheme_clusters.to_a end
  expect ["\u{000A}".u, "\u{1100}".u] do "\u{000A}\u{1100}".u.grapheme_clusters.to_a end
  expect ["\u{000A}".u, "\u{0308}".u, "\u{1100}".u] do "\u{000A}\u{0308}\u{1100}".u.grapheme_clusters.to_a end
  expect ["\u{000A}".u, "\u{1160}".u] do "\u{000A}\u{1160}".u.grapheme_clusters.to_a end
  expect ["\u{000A}".u, "\u{0308}".u, "\u{1160}".u] do "\u{000A}\u{0308}\u{1160}".u.grapheme_clusters.to_a end
  expect ["\u{000A}".u, "\u{11A8}".u] do "\u{000A}\u{11A8}".u.grapheme_clusters.to_a end
  expect ["\u{000A}".u, "\u{0308}".u, "\u{11A8}".u] do "\u{000A}\u{0308}\u{11A8}".u.grapheme_clusters.to_a end
  expect ["\u{000A}".u, "\u{AC00}".u] do "\u{000A}\u{AC00}".u.grapheme_clusters.to_a end
  expect ["\u{000A}".u, "\u{0308}".u, "\u{AC00}".u] do "\u{000A}\u{0308}\u{AC00}".u.grapheme_clusters.to_a end
  expect ["\u{000A}".u, "\u{AC01}".u] do "\u{000A}\u{AC01}".u.grapheme_clusters.to_a end
  expect ["\u{000A}".u, "\u{0308}".u, "\u{AC01}".u] do "\u{000A}\u{0308}\u{AC01}".u.grapheme_clusters.to_a end
  expect ["\u{000A}".u, "\u{1F1E6}".u] do "\u{000A}\u{1F1E6}".u.grapheme_clusters.to_a end
  expect ["\u{000A}".u, "\u{0308}".u, "\u{1F1E6}".u] do "\u{000A}\u{0308}\u{1F1E6}".u.grapheme_clusters.to_a end
  expect ["\u{000A}".u, "\u{0378}".u] do "\u{000A}\u{0378}".u.grapheme_clusters.to_a end
  expect ["\u{000A}".u, "\u{0308}".u, "\u{0378}".u] do "\u{000A}\u{0308}\u{0378}".u.grapheme_clusters.to_a end
  expect ["\u{000A}".u, "\u{0001}".u] do "\u{000A}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{000A}".u, "\u{0308}".u, "\u{0001}".u] do "\u{000A}\u{0308}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0020}".u] do "\u{0001}\u{0020}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0308}".u, "\u{0020}".u] do "\u{0001}\u{0308}\u{0020}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{000D}".u] do "\u{0001}\u{000D}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0308}".u, "\u{000D}".u] do "\u{0001}\u{0308}\u{000D}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{000A}".u] do "\u{0001}\u{000A}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0308}".u, "\u{000A}".u] do "\u{0001}\u{0308}\u{000A}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0001}".u] do "\u{0001}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0308}".u, "\u{0001}".u] do "\u{0001}\u{0308}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0300}".u] do "\u{0001}\u{0300}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0308}\u{0300}".u] do "\u{0001}\u{0308}\u{0300}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0903}".u] do "\u{0001}\u{0903}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0308}\u{0903}".u] do "\u{0001}\u{0308}\u{0903}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{1100}".u] do "\u{0001}\u{1100}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0308}".u, "\u{1100}".u] do "\u{0001}\u{0308}\u{1100}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{1160}".u] do "\u{0001}\u{1160}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0308}".u, "\u{1160}".u] do "\u{0001}\u{0308}\u{1160}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{11A8}".u] do "\u{0001}\u{11A8}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0308}".u, "\u{11A8}".u] do "\u{0001}\u{0308}\u{11A8}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{AC00}".u] do "\u{0001}\u{AC00}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0308}".u, "\u{AC00}".u] do "\u{0001}\u{0308}\u{AC00}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{AC01}".u] do "\u{0001}\u{AC01}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0308}".u, "\u{AC01}".u] do "\u{0001}\u{0308}\u{AC01}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{1F1E6}".u] do "\u{0001}\u{1F1E6}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0308}".u, "\u{1F1E6}".u] do "\u{0001}\u{0308}\u{1F1E6}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0378}".u] do "\u{0001}\u{0378}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0308}".u, "\u{0378}".u] do "\u{0001}\u{0308}\u{0378}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0001}".u] do "\u{0001}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0308}".u, "\u{0001}".u] do "\u{0001}\u{0308}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{0300}".u, "\u{0020}".u] do "\u{0300}\u{0020}".u.grapheme_clusters.to_a end
  expect ["\u{0300}\u{0308}".u, "\u{0020}".u] do "\u{0300}\u{0308}\u{0020}".u.grapheme_clusters.to_a end
  expect ["\u{0300}".u, "\u{000D}".u] do "\u{0300}\u{000D}".u.grapheme_clusters.to_a end
  expect ["\u{0300}\u{0308}".u, "\u{000D}".u] do "\u{0300}\u{0308}\u{000D}".u.grapheme_clusters.to_a end
  expect ["\u{0300}".u, "\u{000A}".u] do "\u{0300}\u{000A}".u.grapheme_clusters.to_a end
  expect ["\u{0300}\u{0308}".u, "\u{000A}".u] do "\u{0300}\u{0308}\u{000A}".u.grapheme_clusters.to_a end
  expect ["\u{0300}".u, "\u{0001}".u] do "\u{0300}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{0300}\u{0308}".u, "\u{0001}".u] do "\u{0300}\u{0308}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{0300}\u{0300}".u] do "\u{0300}\u{0300}".u.grapheme_clusters.to_a end
  expect ["\u{0300}\u{0308}\u{0300}".u] do "\u{0300}\u{0308}\u{0300}".u.grapheme_clusters.to_a end
  expect ["\u{0300}\u{0903}".u] do "\u{0300}\u{0903}".u.grapheme_clusters.to_a end
  expect ["\u{0300}\u{0308}\u{0903}".u] do "\u{0300}\u{0308}\u{0903}".u.grapheme_clusters.to_a end
  expect ["\u{0300}".u, "\u{1100}".u] do "\u{0300}\u{1100}".u.grapheme_clusters.to_a end
  expect ["\u{0300}\u{0308}".u, "\u{1100}".u] do "\u{0300}\u{0308}\u{1100}".u.grapheme_clusters.to_a end
  expect ["\u{0300}".u, "\u{1160}".u] do "\u{0300}\u{1160}".u.grapheme_clusters.to_a end
  expect ["\u{0300}\u{0308}".u, "\u{1160}".u] do "\u{0300}\u{0308}\u{1160}".u.grapheme_clusters.to_a end
  expect ["\u{0300}".u, "\u{11A8}".u] do "\u{0300}\u{11A8}".u.grapheme_clusters.to_a end
  expect ["\u{0300}\u{0308}".u, "\u{11A8}".u] do "\u{0300}\u{0308}\u{11A8}".u.grapheme_clusters.to_a end
  expect ["\u{0300}".u, "\u{AC00}".u] do "\u{0300}\u{AC00}".u.grapheme_clusters.to_a end
  expect ["\u{0300}\u{0308}".u, "\u{AC00}".u] do "\u{0300}\u{0308}\u{AC00}".u.grapheme_clusters.to_a end
  expect ["\u{0300}".u, "\u{AC01}".u] do "\u{0300}\u{AC01}".u.grapheme_clusters.to_a end
  expect ["\u{0300}\u{0308}".u, "\u{AC01}".u] do "\u{0300}\u{0308}\u{AC01}".u.grapheme_clusters.to_a end
  expect ["\u{0300}".u, "\u{1F1E6}".u] do "\u{0300}\u{1F1E6}".u.grapheme_clusters.to_a end
  expect ["\u{0300}\u{0308}".u, "\u{1F1E6}".u] do "\u{0300}\u{0308}\u{1F1E6}".u.grapheme_clusters.to_a end
  expect ["\u{0300}".u, "\u{0378}".u] do "\u{0300}\u{0378}".u.grapheme_clusters.to_a end
  expect ["\u{0300}\u{0308}".u, "\u{0378}".u] do "\u{0300}\u{0308}\u{0378}".u.grapheme_clusters.to_a end
  expect ["\u{0300}".u, "\u{0001}".u] do "\u{0300}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{0300}\u{0308}".u, "\u{0001}".u] do "\u{0300}\u{0308}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{0903}".u, "\u{0020}".u] do "\u{0903}\u{0020}".u.grapheme_clusters.to_a end
  expect ["\u{0903}\u{0308}".u, "\u{0020}".u] do "\u{0903}\u{0308}\u{0020}".u.grapheme_clusters.to_a end
  expect ["\u{0903}".u, "\u{000D}".u] do "\u{0903}\u{000D}".u.grapheme_clusters.to_a end
  expect ["\u{0903}\u{0308}".u, "\u{000D}".u] do "\u{0903}\u{0308}\u{000D}".u.grapheme_clusters.to_a end
  expect ["\u{0903}".u, "\u{000A}".u] do "\u{0903}\u{000A}".u.grapheme_clusters.to_a end
  expect ["\u{0903}\u{0308}".u, "\u{000A}".u] do "\u{0903}\u{0308}\u{000A}".u.grapheme_clusters.to_a end
  expect ["\u{0903}".u, "\u{0001}".u] do "\u{0903}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{0903}\u{0308}".u, "\u{0001}".u] do "\u{0903}\u{0308}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{0903}\u{0300}".u] do "\u{0903}\u{0300}".u.grapheme_clusters.to_a end
  expect ["\u{0903}\u{0308}\u{0300}".u] do "\u{0903}\u{0308}\u{0300}".u.grapheme_clusters.to_a end
  expect ["\u{0903}\u{0903}".u] do "\u{0903}\u{0903}".u.grapheme_clusters.to_a end
  expect ["\u{0903}\u{0308}\u{0903}".u] do "\u{0903}\u{0308}\u{0903}".u.grapheme_clusters.to_a end
  expect ["\u{0903}".u, "\u{1100}".u] do "\u{0903}\u{1100}".u.grapheme_clusters.to_a end
  expect ["\u{0903}\u{0308}".u, "\u{1100}".u] do "\u{0903}\u{0308}\u{1100}".u.grapheme_clusters.to_a end
  expect ["\u{0903}".u, "\u{1160}".u] do "\u{0903}\u{1160}".u.grapheme_clusters.to_a end
  expect ["\u{0903}\u{0308}".u, "\u{1160}".u] do "\u{0903}\u{0308}\u{1160}".u.grapheme_clusters.to_a end
  expect ["\u{0903}".u, "\u{11A8}".u] do "\u{0903}\u{11A8}".u.grapheme_clusters.to_a end
  expect ["\u{0903}\u{0308}".u, "\u{11A8}".u] do "\u{0903}\u{0308}\u{11A8}".u.grapheme_clusters.to_a end
  expect ["\u{0903}".u, "\u{AC00}".u] do "\u{0903}\u{AC00}".u.grapheme_clusters.to_a end
  expect ["\u{0903}\u{0308}".u, "\u{AC00}".u] do "\u{0903}\u{0308}\u{AC00}".u.grapheme_clusters.to_a end
  expect ["\u{0903}".u, "\u{AC01}".u] do "\u{0903}\u{AC01}".u.grapheme_clusters.to_a end
  expect ["\u{0903}\u{0308}".u, "\u{AC01}".u] do "\u{0903}\u{0308}\u{AC01}".u.grapheme_clusters.to_a end
  expect ["\u{0903}".u, "\u{1F1E6}".u] do "\u{0903}\u{1F1E6}".u.grapheme_clusters.to_a end
  expect ["\u{0903}\u{0308}".u, "\u{1F1E6}".u] do "\u{0903}\u{0308}\u{1F1E6}".u.grapheme_clusters.to_a end
  expect ["\u{0903}".u, "\u{0378}".u] do "\u{0903}\u{0378}".u.grapheme_clusters.to_a end
  expect ["\u{0903}\u{0308}".u, "\u{0378}".u] do "\u{0903}\u{0308}\u{0378}".u.grapheme_clusters.to_a end
  expect ["\u{0903}".u, "\u{0001}".u] do "\u{0903}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{0903}\u{0308}".u, "\u{0001}".u] do "\u{0903}\u{0308}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{1100}".u, "\u{0020}".u] do "\u{1100}\u{0020}".u.grapheme_clusters.to_a end
  expect ["\u{1100}\u{0308}".u, "\u{0020}".u] do "\u{1100}\u{0308}\u{0020}".u.grapheme_clusters.to_a end
  expect ["\u{1100}".u, "\u{000D}".u] do "\u{1100}\u{000D}".u.grapheme_clusters.to_a end
  expect ["\u{1100}\u{0308}".u, "\u{000D}".u] do "\u{1100}\u{0308}\u{000D}".u.grapheme_clusters.to_a end
  expect ["\u{1100}".u, "\u{000A}".u] do "\u{1100}\u{000A}".u.grapheme_clusters.to_a end
  expect ["\u{1100}\u{0308}".u, "\u{000A}".u] do "\u{1100}\u{0308}\u{000A}".u.grapheme_clusters.to_a end
  expect ["\u{1100}".u, "\u{0001}".u] do "\u{1100}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{1100}\u{0308}".u, "\u{0001}".u] do "\u{1100}\u{0308}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{1100}\u{0300}".u] do "\u{1100}\u{0300}".u.grapheme_clusters.to_a end
  expect ["\u{1100}\u{0308}\u{0300}".u] do "\u{1100}\u{0308}\u{0300}".u.grapheme_clusters.to_a end
  expect ["\u{1100}\u{0903}".u] do "\u{1100}\u{0903}".u.grapheme_clusters.to_a end
  expect ["\u{1100}\u{0308}\u{0903}".u] do "\u{1100}\u{0308}\u{0903}".u.grapheme_clusters.to_a end
  expect ["\u{1100}\u{1100}".u] do "\u{1100}\u{1100}".u.grapheme_clusters.to_a end
  expect ["\u{1100}\u{0308}".u, "\u{1100}".u] do "\u{1100}\u{0308}\u{1100}".u.grapheme_clusters.to_a end
  expect ["\u{1100}\u{1160}".u] do "\u{1100}\u{1160}".u.grapheme_clusters.to_a end
  expect ["\u{1100}\u{0308}".u, "\u{1160}".u] do "\u{1100}\u{0308}\u{1160}".u.grapheme_clusters.to_a end
  expect ["\u{1100}".u, "\u{11A8}".u] do "\u{1100}\u{11A8}".u.grapheme_clusters.to_a end
  expect ["\u{1100}\u{0308}".u, "\u{11A8}".u] do "\u{1100}\u{0308}\u{11A8}".u.grapheme_clusters.to_a end
  expect ["\u{1100}\u{AC00}".u] do "\u{1100}\u{AC00}".u.grapheme_clusters.to_a end
  expect ["\u{1100}\u{0308}".u, "\u{AC00}".u] do "\u{1100}\u{0308}\u{AC00}".u.grapheme_clusters.to_a end
  expect ["\u{1100}\u{AC01}".u] do "\u{1100}\u{AC01}".u.grapheme_clusters.to_a end
  expect ["\u{1100}\u{0308}".u, "\u{AC01}".u] do "\u{1100}\u{0308}\u{AC01}".u.grapheme_clusters.to_a end
  expect ["\u{1100}".u, "\u{1F1E6}".u] do "\u{1100}\u{1F1E6}".u.grapheme_clusters.to_a end
  expect ["\u{1100}\u{0308}".u, "\u{1F1E6}".u] do "\u{1100}\u{0308}\u{1F1E6}".u.grapheme_clusters.to_a end
  expect ["\u{1100}".u, "\u{0378}".u] do "\u{1100}\u{0378}".u.grapheme_clusters.to_a end
  expect ["\u{1100}\u{0308}".u, "\u{0378}".u] do "\u{1100}\u{0308}\u{0378}".u.grapheme_clusters.to_a end
  expect ["\u{1100}".u, "\u{0001}".u] do "\u{1100}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{1100}\u{0308}".u, "\u{0001}".u] do "\u{1100}\u{0308}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{1160}".u, "\u{0020}".u] do "\u{1160}\u{0020}".u.grapheme_clusters.to_a end
  expect ["\u{1160}\u{0308}".u, "\u{0020}".u] do "\u{1160}\u{0308}\u{0020}".u.grapheme_clusters.to_a end
  expect ["\u{1160}".u, "\u{000D}".u] do "\u{1160}\u{000D}".u.grapheme_clusters.to_a end
  expect ["\u{1160}\u{0308}".u, "\u{000D}".u] do "\u{1160}\u{0308}\u{000D}".u.grapheme_clusters.to_a end
  expect ["\u{1160}".u, "\u{000A}".u] do "\u{1160}\u{000A}".u.grapheme_clusters.to_a end
  expect ["\u{1160}\u{0308}".u, "\u{000A}".u] do "\u{1160}\u{0308}\u{000A}".u.grapheme_clusters.to_a end
  expect ["\u{1160}".u, "\u{0001}".u] do "\u{1160}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{1160}\u{0308}".u, "\u{0001}".u] do "\u{1160}\u{0308}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{1160}\u{0300}".u] do "\u{1160}\u{0300}".u.grapheme_clusters.to_a end
  expect ["\u{1160}\u{0308}\u{0300}".u] do "\u{1160}\u{0308}\u{0300}".u.grapheme_clusters.to_a end
  expect ["\u{1160}\u{0903}".u] do "\u{1160}\u{0903}".u.grapheme_clusters.to_a end
  expect ["\u{1160}\u{0308}\u{0903}".u] do "\u{1160}\u{0308}\u{0903}".u.grapheme_clusters.to_a end
  expect ["\u{1160}".u, "\u{1100}".u] do "\u{1160}\u{1100}".u.grapheme_clusters.to_a end
  expect ["\u{1160}\u{0308}".u, "\u{1100}".u] do "\u{1160}\u{0308}\u{1100}".u.grapheme_clusters.to_a end
  expect ["\u{1160}\u{1160}".u] do "\u{1160}\u{1160}".u.grapheme_clusters.to_a end
  expect ["\u{1160}\u{0308}".u, "\u{1160}".u] do "\u{1160}\u{0308}\u{1160}".u.grapheme_clusters.to_a end
  expect ["\u{1160}\u{11A8}".u] do "\u{1160}\u{11A8}".u.grapheme_clusters.to_a end
  expect ["\u{1160}\u{0308}".u, "\u{11A8}".u] do "\u{1160}\u{0308}\u{11A8}".u.grapheme_clusters.to_a end
  expect ["\u{1160}".u, "\u{AC00}".u] do "\u{1160}\u{AC00}".u.grapheme_clusters.to_a end
  expect ["\u{1160}\u{0308}".u, "\u{AC00}".u] do "\u{1160}\u{0308}\u{AC00}".u.grapheme_clusters.to_a end
  expect ["\u{1160}".u, "\u{AC01}".u] do "\u{1160}\u{AC01}".u.grapheme_clusters.to_a end
  expect ["\u{1160}\u{0308}".u, "\u{AC01}".u] do "\u{1160}\u{0308}\u{AC01}".u.grapheme_clusters.to_a end
  expect ["\u{1160}".u, "\u{1F1E6}".u] do "\u{1160}\u{1F1E6}".u.grapheme_clusters.to_a end
  expect ["\u{1160}\u{0308}".u, "\u{1F1E6}".u] do "\u{1160}\u{0308}\u{1F1E6}".u.grapheme_clusters.to_a end
  expect ["\u{1160}".u, "\u{0378}".u] do "\u{1160}\u{0378}".u.grapheme_clusters.to_a end
  expect ["\u{1160}\u{0308}".u, "\u{0378}".u] do "\u{1160}\u{0308}\u{0378}".u.grapheme_clusters.to_a end
  expect ["\u{1160}".u, "\u{0001}".u] do "\u{1160}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{1160}\u{0308}".u, "\u{0001}".u] do "\u{1160}\u{0308}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{11A8}".u, "\u{0020}".u] do "\u{11A8}\u{0020}".u.grapheme_clusters.to_a end
  expect ["\u{11A8}\u{0308}".u, "\u{0020}".u] do "\u{11A8}\u{0308}\u{0020}".u.grapheme_clusters.to_a end
  expect ["\u{11A8}".u, "\u{000D}".u] do "\u{11A8}\u{000D}".u.grapheme_clusters.to_a end
  expect ["\u{11A8}\u{0308}".u, "\u{000D}".u] do "\u{11A8}\u{0308}\u{000D}".u.grapheme_clusters.to_a end
  expect ["\u{11A8}".u, "\u{000A}".u] do "\u{11A8}\u{000A}".u.grapheme_clusters.to_a end
  expect ["\u{11A8}\u{0308}".u, "\u{000A}".u] do "\u{11A8}\u{0308}\u{000A}".u.grapheme_clusters.to_a end
  expect ["\u{11A8}".u, "\u{0001}".u] do "\u{11A8}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{11A8}\u{0308}".u, "\u{0001}".u] do "\u{11A8}\u{0308}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{11A8}\u{0300}".u] do "\u{11A8}\u{0300}".u.grapheme_clusters.to_a end
  expect ["\u{11A8}\u{0308}\u{0300}".u] do "\u{11A8}\u{0308}\u{0300}".u.grapheme_clusters.to_a end
  expect ["\u{11A8}\u{0903}".u] do "\u{11A8}\u{0903}".u.grapheme_clusters.to_a end
  expect ["\u{11A8}\u{0308}\u{0903}".u] do "\u{11A8}\u{0308}\u{0903}".u.grapheme_clusters.to_a end
  expect ["\u{11A8}".u, "\u{1100}".u] do "\u{11A8}\u{1100}".u.grapheme_clusters.to_a end
  expect ["\u{11A8}\u{0308}".u, "\u{1100}".u] do "\u{11A8}\u{0308}\u{1100}".u.grapheme_clusters.to_a end
  expect ["\u{11A8}".u, "\u{1160}".u] do "\u{11A8}\u{1160}".u.grapheme_clusters.to_a end
  expect ["\u{11A8}\u{0308}".u, "\u{1160}".u] do "\u{11A8}\u{0308}\u{1160}".u.grapheme_clusters.to_a end
  expect ["\u{11A8}\u{11A8}".u] do "\u{11A8}\u{11A8}".u.grapheme_clusters.to_a end
  expect ["\u{11A8}\u{0308}".u, "\u{11A8}".u] do "\u{11A8}\u{0308}\u{11A8}".u.grapheme_clusters.to_a end
  expect ["\u{11A8}".u, "\u{AC00}".u] do "\u{11A8}\u{AC00}".u.grapheme_clusters.to_a end
  expect ["\u{11A8}\u{0308}".u, "\u{AC00}".u] do "\u{11A8}\u{0308}\u{AC00}".u.grapheme_clusters.to_a end
  expect ["\u{11A8}".u, "\u{AC01}".u] do "\u{11A8}\u{AC01}".u.grapheme_clusters.to_a end
  expect ["\u{11A8}\u{0308}".u, "\u{AC01}".u] do "\u{11A8}\u{0308}\u{AC01}".u.grapheme_clusters.to_a end
  expect ["\u{11A8}".u, "\u{1F1E6}".u] do "\u{11A8}\u{1F1E6}".u.grapheme_clusters.to_a end
  expect ["\u{11A8}\u{0308}".u, "\u{1F1E6}".u] do "\u{11A8}\u{0308}\u{1F1E6}".u.grapheme_clusters.to_a end
  expect ["\u{11A8}".u, "\u{0378}".u] do "\u{11A8}\u{0378}".u.grapheme_clusters.to_a end
  expect ["\u{11A8}\u{0308}".u, "\u{0378}".u] do "\u{11A8}\u{0308}\u{0378}".u.grapheme_clusters.to_a end
  expect ["\u{11A8}".u, "\u{0001}".u] do "\u{11A8}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{11A8}\u{0308}".u, "\u{0001}".u] do "\u{11A8}\u{0308}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{AC00}".u, "\u{0020}".u] do "\u{AC00}\u{0020}".u.grapheme_clusters.to_a end
  expect ["\u{AC00}\u{0308}".u, "\u{0020}".u] do "\u{AC00}\u{0308}\u{0020}".u.grapheme_clusters.to_a end
  expect ["\u{AC00}".u, "\u{000D}".u] do "\u{AC00}\u{000D}".u.grapheme_clusters.to_a end
  expect ["\u{AC00}\u{0308}".u, "\u{000D}".u] do "\u{AC00}\u{0308}\u{000D}".u.grapheme_clusters.to_a end
  expect ["\u{AC00}".u, "\u{000A}".u] do "\u{AC00}\u{000A}".u.grapheme_clusters.to_a end
  expect ["\u{AC00}\u{0308}".u, "\u{000A}".u] do "\u{AC00}\u{0308}\u{000A}".u.grapheme_clusters.to_a end
  expect ["\u{AC00}".u, "\u{0001}".u] do "\u{AC00}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{AC00}\u{0308}".u, "\u{0001}".u] do "\u{AC00}\u{0308}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{AC00}\u{0300}".u] do "\u{AC00}\u{0300}".u.grapheme_clusters.to_a end
  expect ["\u{AC00}\u{0308}\u{0300}".u] do "\u{AC00}\u{0308}\u{0300}".u.grapheme_clusters.to_a end
  expect ["\u{AC00}\u{0903}".u] do "\u{AC00}\u{0903}".u.grapheme_clusters.to_a end
  expect ["\u{AC00}\u{0308}\u{0903}".u] do "\u{AC00}\u{0308}\u{0903}".u.grapheme_clusters.to_a end
  expect ["\u{AC00}".u, "\u{1100}".u] do "\u{AC00}\u{1100}".u.grapheme_clusters.to_a end
  expect ["\u{AC00}\u{0308}".u, "\u{1100}".u] do "\u{AC00}\u{0308}\u{1100}".u.grapheme_clusters.to_a end
  expect ["\u{AC00}\u{1160}".u] do "\u{AC00}\u{1160}".u.grapheme_clusters.to_a end
  expect ["\u{AC00}\u{0308}".u, "\u{1160}".u] do "\u{AC00}\u{0308}\u{1160}".u.grapheme_clusters.to_a end
  expect ["\u{AC00}\u{11A8}".u] do "\u{AC00}\u{11A8}".u.grapheme_clusters.to_a end
  expect ["\u{AC00}\u{0308}".u, "\u{11A8}".u] do "\u{AC00}\u{0308}\u{11A8}".u.grapheme_clusters.to_a end
  expect ["\u{AC00}".u, "\u{AC00}".u] do "\u{AC00}\u{AC00}".u.grapheme_clusters.to_a end
  expect ["\u{AC00}\u{0308}".u, "\u{AC00}".u] do "\u{AC00}\u{0308}\u{AC00}".u.grapheme_clusters.to_a end
  expect ["\u{AC00}".u, "\u{AC01}".u] do "\u{AC00}\u{AC01}".u.grapheme_clusters.to_a end
  expect ["\u{AC00}\u{0308}".u, "\u{AC01}".u] do "\u{AC00}\u{0308}\u{AC01}".u.grapheme_clusters.to_a end
  expect ["\u{AC00}".u, "\u{1F1E6}".u] do "\u{AC00}\u{1F1E6}".u.grapheme_clusters.to_a end
  expect ["\u{AC00}\u{0308}".u, "\u{1F1E6}".u] do "\u{AC00}\u{0308}\u{1F1E6}".u.grapheme_clusters.to_a end
  expect ["\u{AC00}".u, "\u{0378}".u] do "\u{AC00}\u{0378}".u.grapheme_clusters.to_a end
  expect ["\u{AC00}\u{0308}".u, "\u{0378}".u] do "\u{AC00}\u{0308}\u{0378}".u.grapheme_clusters.to_a end
  expect ["\u{AC00}".u, "\u{0001}".u] do "\u{AC00}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{AC00}\u{0308}".u, "\u{0001}".u] do "\u{AC00}\u{0308}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{AC01}".u, "\u{0020}".u] do "\u{AC01}\u{0020}".u.grapheme_clusters.to_a end
  expect ["\u{AC01}\u{0308}".u, "\u{0020}".u] do "\u{AC01}\u{0308}\u{0020}".u.grapheme_clusters.to_a end
  expect ["\u{AC01}".u, "\u{000D}".u] do "\u{AC01}\u{000D}".u.grapheme_clusters.to_a end
  expect ["\u{AC01}\u{0308}".u, "\u{000D}".u] do "\u{AC01}\u{0308}\u{000D}".u.grapheme_clusters.to_a end
  expect ["\u{AC01}".u, "\u{000A}".u] do "\u{AC01}\u{000A}".u.grapheme_clusters.to_a end
  expect ["\u{AC01}\u{0308}".u, "\u{000A}".u] do "\u{AC01}\u{0308}\u{000A}".u.grapheme_clusters.to_a end
  expect ["\u{AC01}".u, "\u{0001}".u] do "\u{AC01}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{AC01}\u{0308}".u, "\u{0001}".u] do "\u{AC01}\u{0308}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{AC01}\u{0300}".u] do "\u{AC01}\u{0300}".u.grapheme_clusters.to_a end
  expect ["\u{AC01}\u{0308}\u{0300}".u] do "\u{AC01}\u{0308}\u{0300}".u.grapheme_clusters.to_a end
  expect ["\u{AC01}\u{0903}".u] do "\u{AC01}\u{0903}".u.grapheme_clusters.to_a end
  expect ["\u{AC01}\u{0308}\u{0903}".u] do "\u{AC01}\u{0308}\u{0903}".u.grapheme_clusters.to_a end
  expect ["\u{AC01}".u, "\u{1100}".u] do "\u{AC01}\u{1100}".u.grapheme_clusters.to_a end
  expect ["\u{AC01}\u{0308}".u, "\u{1100}".u] do "\u{AC01}\u{0308}\u{1100}".u.grapheme_clusters.to_a end
  expect ["\u{AC01}".u, "\u{1160}".u] do "\u{AC01}\u{1160}".u.grapheme_clusters.to_a end
  expect ["\u{AC01}\u{0308}".u, "\u{1160}".u] do "\u{AC01}\u{0308}\u{1160}".u.grapheme_clusters.to_a end
  expect ["\u{AC01}\u{11A8}".u] do "\u{AC01}\u{11A8}".u.grapheme_clusters.to_a end
  expect ["\u{AC01}\u{0308}".u, "\u{11A8}".u] do "\u{AC01}\u{0308}\u{11A8}".u.grapheme_clusters.to_a end
  expect ["\u{AC01}".u, "\u{AC00}".u] do "\u{AC01}\u{AC00}".u.grapheme_clusters.to_a end
  expect ["\u{AC01}\u{0308}".u, "\u{AC00}".u] do "\u{AC01}\u{0308}\u{AC00}".u.grapheme_clusters.to_a end
  expect ["\u{AC01}".u, "\u{AC01}".u] do "\u{AC01}\u{AC01}".u.grapheme_clusters.to_a end
  expect ["\u{AC01}\u{0308}".u, "\u{AC01}".u] do "\u{AC01}\u{0308}\u{AC01}".u.grapheme_clusters.to_a end
  expect ["\u{AC01}".u, "\u{1F1E6}".u] do "\u{AC01}\u{1F1E6}".u.grapheme_clusters.to_a end
  expect ["\u{AC01}\u{0308}".u, "\u{1F1E6}".u] do "\u{AC01}\u{0308}\u{1F1E6}".u.grapheme_clusters.to_a end
  expect ["\u{AC01}".u, "\u{0378}".u] do "\u{AC01}\u{0378}".u.grapheme_clusters.to_a end
  expect ["\u{AC01}\u{0308}".u, "\u{0378}".u] do "\u{AC01}\u{0308}\u{0378}".u.grapheme_clusters.to_a end
  expect ["\u{AC01}".u, "\u{0001}".u] do "\u{AC01}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{AC01}\u{0308}".u, "\u{0001}".u] do "\u{AC01}\u{0308}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}".u, "\u{0020}".u] do "\u{1F1E6}\u{0020}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}\u{0308}".u, "\u{0020}".u] do "\u{1F1E6}\u{0308}\u{0020}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}".u, "\u{000D}".u] do "\u{1F1E6}\u{000D}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}\u{0308}".u, "\u{000D}".u] do "\u{1F1E6}\u{0308}\u{000D}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}".u, "\u{000A}".u] do "\u{1F1E6}\u{000A}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}\u{0308}".u, "\u{000A}".u] do "\u{1F1E6}\u{0308}\u{000A}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}".u, "\u{0001}".u] do "\u{1F1E6}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}\u{0308}".u, "\u{0001}".u] do "\u{1F1E6}\u{0308}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}\u{0300}".u] do "\u{1F1E6}\u{0300}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}\u{0308}\u{0300}".u] do "\u{1F1E6}\u{0308}\u{0300}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}\u{0903}".u] do "\u{1F1E6}\u{0903}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}\u{0308}\u{0903}".u] do "\u{1F1E6}\u{0308}\u{0903}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}".u, "\u{1100}".u] do "\u{1F1E6}\u{1100}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}\u{0308}".u, "\u{1100}".u] do "\u{1F1E6}\u{0308}\u{1100}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}".u, "\u{1160}".u] do "\u{1F1E6}\u{1160}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}\u{0308}".u, "\u{1160}".u] do "\u{1F1E6}\u{0308}\u{1160}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}".u, "\u{11A8}".u] do "\u{1F1E6}\u{11A8}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}\u{0308}".u, "\u{11A8}".u] do "\u{1F1E6}\u{0308}\u{11A8}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}".u, "\u{AC00}".u] do "\u{1F1E6}\u{AC00}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}\u{0308}".u, "\u{AC00}".u] do "\u{1F1E6}\u{0308}\u{AC00}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}".u, "\u{AC01}".u] do "\u{1F1E6}\u{AC01}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}\u{0308}".u, "\u{AC01}".u] do "\u{1F1E6}\u{0308}\u{AC01}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}\u{1F1E6}".u] do "\u{1F1E6}\u{1F1E6}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}\u{0308}".u, "\u{1F1E6}".u] do "\u{1F1E6}\u{0308}\u{1F1E6}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}".u, "\u{0378}".u] do "\u{1F1E6}\u{0378}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}\u{0308}".u, "\u{0378}".u] do "\u{1F1E6}\u{0308}\u{0378}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}".u, "\u{0001}".u] do "\u{1F1E6}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}\u{0308}".u, "\u{0001}".u] do "\u{1F1E6}\u{0308}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{0378}".u, "\u{0020}".u] do "\u{0378}\u{0020}".u.grapheme_clusters.to_a end
  expect ["\u{0378}\u{0308}".u, "\u{0020}".u] do "\u{0378}\u{0308}\u{0020}".u.grapheme_clusters.to_a end
  expect ["\u{0378}".u, "\u{000D}".u] do "\u{0378}\u{000D}".u.grapheme_clusters.to_a end
  expect ["\u{0378}\u{0308}".u, "\u{000D}".u] do "\u{0378}\u{0308}\u{000D}".u.grapheme_clusters.to_a end
  expect ["\u{0378}".u, "\u{000A}".u] do "\u{0378}\u{000A}".u.grapheme_clusters.to_a end
  expect ["\u{0378}\u{0308}".u, "\u{000A}".u] do "\u{0378}\u{0308}\u{000A}".u.grapheme_clusters.to_a end
  expect ["\u{0378}".u, "\u{0001}".u] do "\u{0378}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{0378}\u{0308}".u, "\u{0001}".u] do "\u{0378}\u{0308}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{0378}\u{0300}".u] do "\u{0378}\u{0300}".u.grapheme_clusters.to_a end
  expect ["\u{0378}\u{0308}\u{0300}".u] do "\u{0378}\u{0308}\u{0300}".u.grapheme_clusters.to_a end
  expect ["\u{0378}\u{0903}".u] do "\u{0378}\u{0903}".u.grapheme_clusters.to_a end
  expect ["\u{0378}\u{0308}\u{0903}".u] do "\u{0378}\u{0308}\u{0903}".u.grapheme_clusters.to_a end
  expect ["\u{0378}".u, "\u{1100}".u] do "\u{0378}\u{1100}".u.grapheme_clusters.to_a end
  expect ["\u{0378}\u{0308}".u, "\u{1100}".u] do "\u{0378}\u{0308}\u{1100}".u.grapheme_clusters.to_a end
  expect ["\u{0378}".u, "\u{1160}".u] do "\u{0378}\u{1160}".u.grapheme_clusters.to_a end
  expect ["\u{0378}\u{0308}".u, "\u{1160}".u] do "\u{0378}\u{0308}\u{1160}".u.grapheme_clusters.to_a end
  expect ["\u{0378}".u, "\u{11A8}".u] do "\u{0378}\u{11A8}".u.grapheme_clusters.to_a end
  expect ["\u{0378}\u{0308}".u, "\u{11A8}".u] do "\u{0378}\u{0308}\u{11A8}".u.grapheme_clusters.to_a end
  expect ["\u{0378}".u, "\u{AC00}".u] do "\u{0378}\u{AC00}".u.grapheme_clusters.to_a end
  expect ["\u{0378}\u{0308}".u, "\u{AC00}".u] do "\u{0378}\u{0308}\u{AC00}".u.grapheme_clusters.to_a end
  expect ["\u{0378}".u, "\u{AC01}".u] do "\u{0378}\u{AC01}".u.grapheme_clusters.to_a end
  expect ["\u{0378}\u{0308}".u, "\u{AC01}".u] do "\u{0378}\u{0308}\u{AC01}".u.grapheme_clusters.to_a end
  expect ["\u{0378}".u, "\u{1F1E6}".u] do "\u{0378}\u{1F1E6}".u.grapheme_clusters.to_a end
  expect ["\u{0378}\u{0308}".u, "\u{1F1E6}".u] do "\u{0378}\u{0308}\u{1F1E6}".u.grapheme_clusters.to_a end
  expect ["\u{0378}".u, "\u{0378}".u] do "\u{0378}\u{0378}".u.grapheme_clusters.to_a end
  expect ["\u{0378}\u{0308}".u, "\u{0378}".u] do "\u{0378}\u{0308}\u{0378}".u.grapheme_clusters.to_a end
  expect ["\u{0378}".u, "\u{0001}".u] do "\u{0378}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{0378}\u{0308}".u, "\u{0001}".u] do "\u{0378}\u{0308}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0020}".u] do "\u{0001}\u{0020}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0308}".u, "\u{0020}".u] do "\u{0001}\u{0308}\u{0020}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{000D}".u] do "\u{0001}\u{000D}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0308}".u, "\u{000D}".u] do "\u{0001}\u{0308}\u{000D}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{000A}".u] do "\u{0001}\u{000A}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0308}".u, "\u{000A}".u] do "\u{0001}\u{0308}\u{000A}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0001}".u] do "\u{0001}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0308}".u, "\u{0001}".u] do "\u{0001}\u{0308}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0300}".u] do "\u{0001}\u{0300}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0308}\u{0300}".u] do "\u{0001}\u{0308}\u{0300}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0903}".u] do "\u{0001}\u{0903}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0308}\u{0903}".u] do "\u{0001}\u{0308}\u{0903}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{1100}".u] do "\u{0001}\u{1100}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0308}".u, "\u{1100}".u] do "\u{0001}\u{0308}\u{1100}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{1160}".u] do "\u{0001}\u{1160}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0308}".u, "\u{1160}".u] do "\u{0001}\u{0308}\u{1160}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{11A8}".u] do "\u{0001}\u{11A8}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0308}".u, "\u{11A8}".u] do "\u{0001}\u{0308}\u{11A8}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{AC00}".u] do "\u{0001}\u{AC00}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0308}".u, "\u{AC00}".u] do "\u{0001}\u{0308}\u{AC00}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{AC01}".u] do "\u{0001}\u{AC01}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0308}".u, "\u{AC01}".u] do "\u{0001}\u{0308}\u{AC01}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{1F1E6}".u] do "\u{0001}\u{1F1E6}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0308}".u, "\u{1F1E6}".u] do "\u{0001}\u{0308}\u{1F1E6}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0378}".u] do "\u{0001}\u{0378}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0308}".u, "\u{0378}".u] do "\u{0001}\u{0308}\u{0378}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0001}".u] do "\u{0001}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{0001}".u, "\u{0308}".u, "\u{0001}".u] do "\u{0001}\u{0308}\u{0001}".u.grapheme_clusters.to_a end
  expect ["\u{0061}".u, "\u{1F1E6}".u, "\u{0062}".u] do "\u{0061}\u{1F1E6}\u{0062}".u.grapheme_clusters.to_a end
  expect ["\u{1F1F7}\u{1F1FA}".u] do "\u{1F1F7}\u{1F1FA}".u.grapheme_clusters.to_a end
  expect ["\u{1F1F7}\u{1F1FA}\u{1F1F8}".u] do "\u{1F1F7}\u{1F1FA}\u{1F1F8}".u.grapheme_clusters.to_a end
  expect ["\u{1F1F7}\u{1F1FA}\u{1F1F8}\u{1F1EA}".u] do "\u{1F1F7}\u{1F1FA}\u{1F1F8}\u{1F1EA}".u.grapheme_clusters.to_a end
  expect ["\u{1F1F7}\u{1F1FA}".u, "\u{200B}".u, "\u{1F1F8}\u{1F1EA}".u] do "\u{1F1F7}\u{1F1FA}\u{200B}\u{1F1F8}\u{1F1EA}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}\u{1F1E7}\u{1F1E8}".u] do "\u{1F1E6}\u{1F1E7}\u{1F1E8}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}\u{200D}".u, "\u{1F1E7}\u{1F1E8}".u] do "\u{1F1E6}\u{200D}\u{1F1E7}\u{1F1E8}".u.grapheme_clusters.to_a end
  expect ["\u{1F1E6}\u{1F1E7}\u{200D}".u, "\u{1F1E8}".u] do "\u{1F1E6}\u{1F1E7}\u{200D}\u{1F1E8}".u.grapheme_clusters.to_a end
  expect ["\u{0020}\u{200D}".u, "\u{0646}".u] do "\u{0020}\u{200D}\u{0646}".u.grapheme_clusters.to_a end
  expect ["\u{0646}\u{200D}".u, "\u{0020}".u] do "\u{0646}\u{200D}\u{0020}".u.grapheme_clusters.to_a end
end
