#!/usr/bin/env python3
import sys

file_to_open = sys.argv[1]

power_readings_file = open(file_to_open, 'r')
tokens = power_readings_file.readlines()

for line in tokens:
    trimmed_line = line[30:]
    if (trimmed_line.find("mW") != -1):
        trimmed_line = trimmed_line.strip().replace("mW","")
        print(trimmed_line)
    elif (line.find("-> -") != -1):
        print("")