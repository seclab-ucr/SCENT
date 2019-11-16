#!/bin/bash

# -------------------------
# Filename: KLEE_Seed_Meta.py
# Revision: 1.0
# Data:     2018/11/29
# Author:   Yue Cao
# Description:  Generate new file to print information required to build seed (symbol name, symbol size, symbol value)
# Process:
# 1. Based on klee_make_symbolic callsite in klee_main2.c, find all symbols in the program
# 2. Generate new file "KLEE_Generate_Seed.c"

# Run: python KLEE_Seed_Meta.py

# Later on
# 1. gcc -c KLEE_Generate_Seed.c
# 2. clang -o KLEE_Generate_Seed new_v4.o KLEE_Generate_Seed.o
# 3. ./KLEE_Generate_Seed 1>Seed_Temp.txt      //generate meta data in Seed_Temp.txt (filtered by INPUT)
# 4. cy_gen-bout Seed_Temp.txt  //generate file.bout, which is final seed
# -------------------------
# State: done

import sys

#file1 = sys.argv[1]

f0 = file("klee_main.c", "r")
f1 = file("KLEE_Seed_Generation.c", "w")

count = 0
f1.write("#include <stdlib.h>\n#include \"new_model.h\"\n#include \"klee/klee.h\"\n");
f1.write("void input_print(){\n");
f1.write("\tprintf(\"============= KLEE INPUT ===============\\n\");\n");
for line in f0:
    if line.find("//") != -1:
        continue
    if line.find("klee_make_symbolic") == -1:
        continue
    else:
        count = count+1
        keys = line.strip().split("\"")
        target = keys[1].strip()
        line0 = "\tprintf(\""+str(target)+"|%d|%d\\n\", sizeof("+str(target)+"), "+str(target)+");\n"
        #line0 = "\ttypeof("+target+") symbol_a"+str(count)+";\n"
        #line1 = "\tklee_make_symbolic(&symbol_a"+str(count)+", sizeof(symbol_a"+str(count)+"), \""+target+"\");\n"
        #line2 = "\t"+target+"=symbol_a"+str(count)+";\n"
        f1.write(line0)
        #f1.write(line1)
        #f1.write(line2)
f1.write("\tprintf(\"============= KLEE INPUT ===============\\n\");\n}\n");
f1.write("int main(){\n")
f1.write("\tPreProcess();\n");
f1.write("\tinput_print();\n}");
