#!/bin/bash

# --------------------------------------------------
# Filename:   Calculate_BBs.py
# Revision:   1.0
# Data:       2018/9/13
# Author:     Yue Cao
# Email:      ycao009@cs.ucr.edu
# Description: Merge new flipping branches (Basic block form) with target value to the branch set, and print out all new ones.
# Purpose:    Check if there are new flipping targets. If there are no new flipping targets, no need to run Dynamic Taint Analysis.
# --------------------------------------------------
#Version 1.0
#Distint variables are considered new

import sys
#file0 = "../Branches_BB_set.log"
#file2 = "../Branches_BB_set_bak.log"
file1 = sys.argv[1]

if len(sys.argv) == 6:
    file0 = sys.argv[2]
    file2 = sys.argv[3]
    Model1_offset = int(sys.argv[4])
    Model0_end = int(sys.argv[5])

f0 = file(file0, "r")
f = file(file1, "r")
f2 = file(file2, "w")

new = 0

Branches_set = set()
for line in f0: #Branches_BB_set
    line = line.strip()
    keys = line.split("#")
    Branches_set.add(keys[0]) # currently only has one distinct BBOffset; which may miss cases if its min/max value is different
    f2.write(line+'\n')
    #keys = line.split(",")
    #Edge_dict[(keys[0], keys[1])] = int(keys[2])

for line in f:
    line = line.strip()
    # compare the whole
    # or compare the variable only
    keys = line.split("#")
    if keys[0] not in Branches_set:
        #sys.stderr.write("New added: " + keys[0]+"\n")
        f2.write(line+'\n')
        # If branch is flipped on Model0 or Model1, we don't flip the branch from the other model
        p0 = keys[0].find(",")
        p1 = keys[0].find(":")
        Model_index = keys[0][0:p0-1] #Model   0,b
        BB_index = keys[0][p0+2:p1] #bb_index
        Rest = keys[0][p1:]
        Branches_set.add(keys[0])
        #sys.stderr.write("Branches added: " + keys[0]+"\n")

        index = int(BB_index)
        if index <= Model0_end:
            index = index+Model1_offset
            new_BB_index = str(index)
            new_str = Model_index+"1,b"+new_BB_index+Rest+"#"+keys[1]+"#"+keys[2]+"#"+keys[3]
            f2.write(new_str+'\n')
            Branches_set.add(Model_index+"1,b"+new_BB_index+Rest)
            #sys.stderr.write("Branches added: " + Model_index+"1,b"+new_BB_index+Rest+"\n")
        else:
            index = index-Model1_offset
            new_BB_index = str(index)
            new_str = Model_index+"0,b"+new_BB_index+Rest+"#"+keys[1]+"#"+keys[2]+"#"+keys[3]
            f2.write(new_str+'\n')
            Branches_set.add(Model_index+"0,b"+new_BB_index+Rest)
            #sys.stderr.write("Branches added: " + Model_index+"0,b"+new_BB_index+Rest+"\n")

        new = new+1
        # remove operands that have huge values
        if len(keys[1]) > 10 or len(keys[2]) > 10:
            continue
        print line

