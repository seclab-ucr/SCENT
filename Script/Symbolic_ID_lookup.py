#!/bin/bash

# --------------------------------------------------
# Filename:   Symbolic_ID_lookup.py
# Revision:   1.0
# Data:       2019/03/09
# Author:     Yue Cao
# Email:      ycao009@cs.ucr.edu
# Description: lookup Symbolic_ID from Symbolic_ID.log
# Claration:    Because we have filtered the old branches, even though SYM_ID is same, it's caused by a new branch. Therefore, we don't trim this modification.
# --------------------------------------------------
# TODO:  trim flipping path that current SYM_ID and its ancestor share same symbol variable. May cause conflict or redundency. Because it's rare and only add redundency, we didn't solve it so far.

import sys
import os
file1 = sys.argv[1]
file2 = sys.argv[2]

f = file(file1, "r") #FLIP.txt
f2 = file(file2, "r") #Symbolic_ID.log

count = 0
for target_sym in f:
    target_sym = target_sym.strip()
    pos = target_sym.find("|");
    target_sym = target_sym[pos:]
    for line in f2:
        if line == target_sym:
            print count
            quit()
        count = count+1
f.close()
f2.close()
os.system("echo \""+target_sym+"\" >> "+file2)
print count

