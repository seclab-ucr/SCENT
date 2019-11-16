#!/bin/bash

# -------------------------
# Filename: Address_Initialization.py
# Revision: 1.0
# Data:     long ago
# Author:   Yue Cao
# Description:  Generate codes that print out variables' name and their addresses, so we can bind dynamic address to its IR form.
# Process:
# 1. Based on initialization of global variable and socket fields, use regular expression to filter variable name
# 2. Add instrumentation to print variable and their address
# -------------------------
# Address_Initialization.py

from sets import Set

#import sys
#file1 = sys.argv[1]
filted_var = ["_sk_userlocks", "_do_early_retrans", "_frto", "_is_cwnd_limited", "_nonagle", "_repair", "_thin_dupack", "_skc_prot"]
def SYMBOLIZE_INIT(f_in, f_out, count):
    #f_in = file(file1, "r")
    #f_out = file(file2, "a")
    filter_mark = False

    Inside_Target_Function = False

    for line in f_in:
        if line.startswith("void Model0_Listen_Server_Initialize(){") or line.startswith("void Model0_Server_A_Initialize(){") or line.startswith("void Model0_Server_Initialize(){") or line.startswith("void Model1_Listen_Server_Initialize(){") or line.startswith("void Model1_Server_A_Initialize(){") or line.startswith("void Model1_Server_Initialize(){"):
            print "Matched"
            print line
            Inside_Target_Function = True
            continue

        if Inside_Target_Function == False:
            continue
        elif line.find("}") != -1:
            Inside_Target_Function = False;

        line = line.strip()
        if line.find(";") == -1:
            continue
        pos = line.find("//")
        if (pos != -1):
            line = line[:pos]
        pos = line.find("=")
        if pos == -1:
            continue
        line = line[:pos]
        if (line.find("*((long long *)") > 1): # meanings they are stored in other heap, i.e., skc_prot-> .., skc_net->...
            print line
            continue

        '''
        for var in filted_var:
            if line.find(var) != -1:
                filter_mark = True
                break
        if filter_mark:
            filter_mark = False
            continue
        '''
        target = line
        pos0 = target.find("unsigned")
        pos1 = target[pos0:].find("*")
        if pos1 == -1: #skc_prot case, since it doesn't use offset to locate its field
            continue
        if line.find("+48)") != -1: #skc_net case //Be careful!! Solver is hard to resolve address, so don't symbolize address, such as skc_prot and skc_net
            continue

        cur_type = target[pos0:pos0+pos1]
        count = count+1
        line0 = "\t"+cur_type+" symbol_a"+str(count)+";\n"
        line1 = "\tklee_make_symbolic(&symbol_a"+str(count)+", sizeof(symbol_a"+str(count)+"), \""+ target+"\");\n"
        line2 = "\t"+target+"=symbol_a"+str(count)+";\n"
        f_out.write(line0)
        f_out.write(line1)
        f_out.write(line2)

        #TODO: because Model0_Req_A has different struct (out_of_memory issue), we will find its fields specifically
        '''
        target1 = target.replace("Model0_Server_L", "Model0_Req_A")
        count = count+1
        line0 = "\t"+cur_type+" symbol_a"+str(count)+";\n"
        line1 = "\tklee_make_symbolic(&symbol_a"+str(count)+", sizeof(symbol_a"+str(count)+"), \""+ target1+"\");\n"
        line2 = "\t"+target1+"=symbol_a"+str(count)+";\n"
        f_out.write(line0)
        f_out.write(line1)
        f_out.write(line2)
        '''

        '''
        target2 = target.replace("Model0_Server_L", "Model0_Server_A")
        count = count+1
        line0 = "\t"+cur_type+" symbol_a"+str(count)+";\n"
        line1 = "\tklee_make_symbolic(&symbol_a"+str(count)+", sizeof(symbol_a"+str(count)+"), \""+ target2+"\");\n"
        line2 = "\t"+target2+"=symbol_a"+str(count)+";\n"
        f_out.write(line0)
        f_out.write(line1)
        f_out.write(line2)
        '''
    #f_in.close()
    #f_out.close()
    return count
