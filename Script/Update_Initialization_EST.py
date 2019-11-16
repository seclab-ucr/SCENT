#!/bin/bash

# --------------------------------------------------
# Filename:   Update_Initialization.py
# Revision:   1.0
# Data:       2018/12/09
# Author:     Yue Cao
# Email:      ycao009@cs.ucr.edu
# Description: Update the initialization of target variables at source code. Then compile codes and link the bc files with the others.
# --------------------------------------------------
# Update1.0:     update the script for 3whs. Basically change Model0_Server_Initialization.c to Model0_Listen_Server_Initialization.c
# --------------------------------------------------
import os
import sys

Ori_Prefix = sys.argv[1]
Dst_Prefix = sys.argv[2]
CODE_PATH = sys.argv[3] # Update1.0: CODE_PATH to generate command
CLANG_PATH = sys.argv[4]

f0 = file("FLIP.txt", "r")

def Initialization(file_name, target_map):
    #DEBUG
    print file_name
    #f1 = open("../Source_Code_abstracted2/"+Ori_Prefix+"_"+file_name+".c", "r")
    #f2 = open("../Source_Code_abstracted2/"+Dst_Prefix+"_"+file_name+".c", "w")
    f1 = open(Ori_Prefix+"_"+file_name+".c", "r")
    f2 = open(Dst_Prefix+"_"+file_name+".c", "w")
    Changed = False

    for line in f1:
        if line.find(";") == -1:
            f2.write(line)
        elif line.find("=") == -1:
            f2.write(line)
        else:
            tmp = line.strip()
            if tmp.startswith("//"):
                f2.write(line)
                continue
            pos = line.find("=")
            tmp_name = line[:pos].strip()
            if tmp_name in target_map:
                print "Equal"
                pos2 = line.find(";")
                tmp_value = unicode(line[pos+1:pos2].strip(), 'utf-8')
                if tmp_value[0] == '-':
                    tmp_value = tmp_value[1:]
                if tmp_value.isnumeric():
                    print tmp_name + ":" + target_map[tmp_name]
                    f2.write(line[:pos+1]+target_map[tmp_name]+line[pos2:])
                    Changed = True
                else:
                    f2.write(line)
            else:
                f2.write(line)
                #print "Not equal: " + target_map[tmp_name] + ":" + tmp_name
    f1.close()
    f2.close()
    if Changed:
        print "Successfully Changed"
        # Update1.0: update the statement below (use arg3 to generate the command)
        os.system(CLANG_PATH+"clang -c -emit-llvm -g -no-integrated-as -adce -O2 -I "+CODE_PATH+" -include " + CODE_PATH+"/TCP_Model.h -include-pch TCP_Model.pch "+Dst_Prefix+"_"+file_name+".c -o "+Dst_Prefix+"_"+file_name+".bc")
    else:
        print "Fail to Change"

#Update1.0:
Model0_Server_L_map = {}
Model1_Server_L_map = {}
Model0_Server_map = {}
Model1_Server_map = {}
Model0_Server_A_map = {}
Model1_Server_A_map = {}
Model0_Global_map = {}
Model1_Global_map = {}

for line in f0:
    line = line.strip()
    line = line[:-2] # remove the priority marks
    targets = line.split("|")
    for target in targets:
        if target.find("CY_Target") != -1:
            continue
        #add them in map, separete with Model0, Model1, Model
        keys = target.split("#")
        keys[0] = keys[0].strip()

        # Update1.0: since we only have Model0_Listen_Server_Initialization and Model1_Listen_Server_Initialization, we simplify the process below
        ## Model0 ##
        if target.find("Model0_Server_L") != -1:
            Model0_Server_L_map[keys[0]] = keys[1]
            Model1_Server_L_map[keys[0].replace("Model0", "Model1")] = keys[1]
        elif target.find("Model0_Server_A") != -1:
            Model0_Server_A_map[keys[0]] = keys[1]
            Model1_Server_A_map[keys[0].replace("Model0", "Model1")] = keys[1]
            keys[0] = keys[0].replace("Model0_Server_A", "Model0_Server")
            Model0_Server_map[keys[0]] = keys[1]
            Model1_Server_map[keys[0].replace("Model0", "Model1")] = keys[1]
        elif target.find("Model0_Server") != -1:
            Model0_Server_map[keys[0]] = keys[1]
            Model1_Server_map[keys[0].replace("Model0", "Model1")] = keys[1]
            keys[0] = keys[0].replace("Model0_Server", "Model0_Server_A")
            Model0_Server_A_map[keys[0]] = keys[1]
            Model1_Server_A_map[keys[0].replace("Model0", "Model1")] = keys[1]
        ## Model1 ##
        elif target.find("Model1_Server_L") != -1:
            Model1_Server_L_map[keys[0]] = keys[1]
            Model0_Server_L_map[keys[0].replace("Model1", "Model0")] = keys[1]
        elif target.find("Model1_Server_A") != -1:
            Model1_Server_A_map[keys[0]] = keys[1]
            Model0_Server_A_map[keys[0].replace("Model1", "Model0")] = keys[1]
            keys[0] = keys[0].replace("Model1_Server_A", "Model1_Server")
            Model1_Server_map[keys[0]] = keys[1]
            Model0_Server_map[keys[0].replace("Model1", "Model0")] = keys[1]
        elif target.find("Model1_Server") != -1:
            Model1_Server_map[keys[0]] = keys[1]
            Model0_Server_map[keys[0].replace("Model1", "Model0")] = keys[1]
            keys[0] = keys[0].replace("Model1_Server", "Model1_Server_A")
            Model1_Server_A_map[keys[0]] = keys[1]
            Model0_Server_A_map[keys[0].replace("Model1", "Model0")] = keys[1]
        ## Model0 Global ##
        elif target.find("Model0") != -1:
            Model0_Global_map[keys[0]] = keys[1]
            Model1_Global_map[keys[0].replace("Model0", "Model1")] = keys[1]
        ## Model1_Global ##
        else:
            Model1_Global_map[keys[0]] = keys[1]
            Model0_Global_map[keys[0].replace("Model1", "Model0")] = keys[1]

# Update1.0: replace Server/Server_A by Listen_Server
    if len(Model0_Server_L_map) > 0: #include the case that Model1_Server_L_map not empty
        Initialization("Model0_Listen_Server_Initialize", Model0_Server_L_map)
        Initialization("Model1_Listen_Server_Initialize", Model1_Server_L_map)
    else:
        # bc files
        os.system("cp "+Ori_Prefix+"_Model0_Listen_Server_Initialize.bc "+Dst_Prefix+"_Model0_Listen_Server_Initialize.bc&")
        os.system("cp "+Ori_Prefix+"_Model1_Listen_Server_Initialize.bc "+Dst_Prefix+"_Model1_Listen_Server_Initialize.bc&")
        # c files
        os.system("cp "+Ori_Prefix+"_Model0_Listen_Server_Initialize.c "+Dst_Prefix+"_Model0_Listen_Server_Initialize.c&")
        os.system("cp "+Ori_Prefix+"_Model1_Listen_Server_Initialize.c "+Dst_Prefix+"_Model1_Listen_Server_Initialize.c&")

    if len(Model0_Server_map) > 0:
        Initialization("Model0_Server_Initialize", Model0_Server_map)
        Initialization("Model1_Server_Initialize", Model1_Server_map)
    else:
        # bc files
        os.system("cp "+Ori_Prefix+"_Model0_Server_Initialize.bc "+Dst_Prefix+"_Model0_Server_Initialize.bc&")
        os.system("cp "+Ori_Prefix+"_Model1_Server_Initialize.bc "+Dst_Prefix+"_Model1_Server_Initialize.bc&")
        # c files
        os.system("cp "+Ori_Prefix+"_Model0_Server_Initialize.c "+Dst_Prefix+"_Model0_Server_Initialize.c&")
        os.system("cp "+Ori_Prefix+"_Model1_Server_Initialize.c "+Dst_Prefix+"_Model1_Server_Initialize.c&")
    if len(Model0_Server_A_map) > 0:
        Initialization("Model0_Server_A_Initialize", Model0_Server_A_map)
        Initialization("Model1_Server_A_Initialize", Model1_Server_A_map)
    else:
        # bc files
        os.system("cp "+Ori_Prefix+"_Model0_Server_A_Initialize.bc "+Dst_Prefix+"_Model0_Server_A_Initialize.bc&")
        os.system("cp "+Ori_Prefix+"_Model1_Server_A_Initialize.bc "+Dst_Prefix+"_Model1_Server_A_Initialize.bc&")
        # c files
        os.system("cp "+Ori_Prefix+"_Model0_Server_A_Initialize.c "+Dst_Prefix+"_Model0_Server_A_Initialize.c&")
        os.system("cp "+Ori_Prefix+"_Model1_Server_A_Initialize.c "+Dst_Prefix+"_Model1_Server_A_Initialize.c&")

# Update1.0: we don't need to change global's file, since we have "cp $CODE_PATH/Model0_global2.c CY_0_Model0_global.c"
    if len(Model0_Global_map) > 0:
        Initialization("Model0_global", Model0_Global_map)
        Initialization("Model1_global", Model1_Global_map)
    else:
        # bc files
        os.system("cp "+Ori_Prefix+"_Model0_global.bc "+Dst_Prefix+"_Model0_global.bc&")
        os.system("cp "+Ori_Prefix+"_Model1_global.bc "+Dst_Prefix+"_Model1_global.bc&")
        # c files
        os.system("cp "+Ori_Prefix+"_Model0_global.c "+Dst_Prefix+"_Model0_global.c&")
        os.system("cp "+Ori_Prefix+"_Model1_global.c "+Dst_Prefix+"_Model1_global.c&")
