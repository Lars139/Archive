#! /usr/bin/env pyhon
import os

home = os.path.expanduser('~')

print os.getcwd()

max = 0

for root, sub_dir, files in os.walk(home):
	p_l = root.split(os.sep)
	length = len(p_l)
	if length>=max:
		max = length
	
for root, sub_dir, files in os.walk(home):
	p_l = root.split(os.sep)
	length = len(p_l)
	if length==max:
		print root
