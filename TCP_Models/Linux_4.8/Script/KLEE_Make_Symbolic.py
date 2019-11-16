#!/bin/bash

# -------------------------
# Filename: KLEE_Make_Symbolic.py
# Revision: 1.0
# Data:     2018/11/17
# Author:   Yue Cao
# Description:  Generate codes that automatic call klee_make_symbolic for all global variables, socket fields and pkt fields
# Process:
# 1. Based on initialization of global variable and socket fields, use regular expression to filter variable name
# 2. Add instrumentation to generate callsites
# -------------------------
# Run:
# python KLEE_Make_Symbolic.py

import sys
import SYMBOLIZE_GLOBAL
import SYMBOLIZE_INIT

#file0 = sys.argv[1] #Model0_Global_Temp.c
#file1 = sys.argv[2] #Model0_Server_Temp.c
#file2 = sys.argv[3] #Model0_Server_A_Temp.c
#file3 = sys.argv[4] #KLEE_main_part1.c
#
#f0 = file(file0, "r")
#f1 = file(file1, "r")
#f2 = file(file2, "r")
#f3 = file(file3, "w")

if len(sys.argv) == 3: #Listen
    file0 = sys.argv[1]
    file1 = sys.argv[2]
    f0 = file(file0, "r")
    f1 = file(file1, "r")
    #f0 = file("/home/ubuntu/TCP_Project/Linux_3WHS/Model0_global2.c", "r")
    #f1 = file("Model0_Listen_Server_Initialize.i", "r") # use preprocessed version to avoid #if #else directives  (condition compilation)

    #f2 = file("../Source_Code_abstracted2/Model0_Server_A_Initialize.c", "r")
    fw = file("klee_main_part1.c", "w")
    ## For symbolic execution purpose, we target at Model0 (Only Model0 has BB offset signatures)

    count = 0

    fw.write("#include <stdlib.h>\n#include \"new_model.h\"\n#include \"klee/klee.h\"\n")
    fw.write("void Model0_Symbolize(){\n")
    fw.write("\tprintf(\"Symbolic\\n\");\n")

    count = SYMBOLIZE_GLOBAL.SYMBOLIZE_GLOBAL(f0, fw, count)
    count = SYMBOLIZE_INIT.SYMBOLIZE_INIT(f1, fw, count)
    #count = SYMBOLIZE_INIT.SYMBOLIZE_INIT(f2, fw, count)

    fw.write("}\n")

elif len(sys.argv) == 5: #EST
    file0 = sys.argv[1]
    file1 = sys.argv[2]
    file2 = sys.argv[3]
    file3 = sys.argv[4]
    f0 = file(file0, "r")
    f1 = file(file1, "r")
    f2 = file(file2, "r")
    f3 = file(file3, "r")
    #f0 = file("/home/ubuntu/TCP_Project/Linux_3WHS/Model0_global2.c", "r")
    #f1 = file("Model0_Listen_Server_Initialize.i", "r") # use preprocessed version to avoid #if #else directives  (condition compilation)

    #f2 = file("../Source_Code_abstracted2/Model0_Server_A_Initialize.c", "r")
    fw = file("klee_main_part1.c", "w")
    ## For symbolic execution purpose, we target at Model0 (Only Model0 has BB offset signatures)

    count = 0

    fw.write("#include <stdlib.h>\n#include \"new_model.h\"\n#include \"klee/klee.h\"\n")
    fw.write("void Model0_Symbolize(){\n")
    fw.write("\tprintf(\"Symbolic\\n\");\n")

    count = SYMBOLIZE_GLOBAL.SYMBOLIZE_GLOBAL(f0, fw, count)
    count = SYMBOLIZE_INIT.SYMBOLIZE_INIT(f1, fw, count)
    count = SYMBOLIZE_INIT.SYMBOLIZE_INIT(f2, fw, count)
    count = SYMBOLIZE_INIT.SYMBOLIZE_INIT(f3, fw, count)

    fw.write("}\n")


elif len(sys.argv) == 9: #EST Guess Port
    file0 = sys.argv[1]
    file1 = sys.argv[2]
    file2 = sys.argv[3]
    file3 = sys.argv[4]
    file4 = sys.argv[5]
    file5 = sys.argv[6]
    file6 = sys.argv[7]
    file7 = sys.argv[8]

    f0 = file(file0, "r")
    f1 = file(file1, "r")
    f2 = file(file2, "r")
    f3 = file(file3, "r")
    f4 = file(file4, "r")
    f5 = file(file5, "r")
    f6 = file(file6, "r")
    f7 = file(file7, "r")
    #f0 = file("/home/ubuntu/TCP_Project/Linux_3WHS/Model0_global2.c", "r")
    #f1 = file("Model0_Listen_Server_Initialize.i", "r") # use preprocessed version to avoid #if #else directives  (condition compilation)

    #f2 = file("../Source_Code_abstracted2/Model0_Server_A_Initialize.c", "r")
    fw = file("klee_main_part1.c", "w")
    ## For symbolic execution purpose, we target at Model0 (Only Model0 has BB offset signatures)

    count = 0

    fw.write("#include <stdlib.h>\n#include \"new_model.h\"\n#include \"klee/klee.h\"\n")
    fw.write("void Model0_Symbolize(){\n")
    fw.write("\tprintf(\"Symbolic\\n\");\n")

    count = SYMBOLIZE_GLOBAL.SYMBOLIZE_GLOBAL(f0, fw, count)
    count = SYMBOLIZE_INIT.SYMBOLIZE_INIT(f1, fw, count)
    count = SYMBOLIZE_INIT.SYMBOLIZE_INIT(f2, fw, count)
    count = SYMBOLIZE_INIT.SYMBOLIZE_INIT(f3, fw, count)
    count = SYMBOLIZE_GLOBAL.SYMBOLIZE_GLOBAL(f4, fw, count)
    count = SYMBOLIZE_INIT.SYMBOLIZE_INIT(f5, fw, count)
    count = SYMBOLIZE_INIT.SYMBOLIZE_INIT(f6, fw, count)
    count = SYMBOLIZE_INIT.SYMBOLIZE_INIT(f7, fw, count)

    fw.write("}\n")
