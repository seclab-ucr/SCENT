#!/bin/bash

# ------------------
# Filename: DTA_Target_Filter.py
# Revision: 1.0
# Data:     2018/11/4
# Author:   Yue Cao
# Email:    ycao009@cs.ucr.edu
# Description: Generate model trail so all target branch condition will be reached during DTA
# Process:
# 1. Collect conditions that are not constant
# 2. Map each condition to its packet trace, then map packet trace to distinct model trail
# 3. Run model checker with each trail to its initialization
# ------------------

import sys
Tot_Condition = sys.argv[1]
Const_Condition = sys.argv[2]
Packet_Trace = sys.argv[3]
#Target_Traces = sys.argv[4]

tot_condition = file(Tot_Condition, "r")
const_condition = file(Const_Condition, "r")
packet_trace = file(Packet_Trace, "r")
#target_traces = file(Target_Traces, "w")

const_condition_set = set() # constant condition to remove
target_condition_list = []  # total condition in consideration
pkt_trace_map = {}          # map from int(bb_offset) to string(pkt_trace)
ori_trail_list = []         # list of orignal lines in model trail
Insert_pos = []             # line indexes that we are updating with packet index

# configuration
MAX_OFFSET = 200
RST_On = True
Last_State = 1204


# Load pkt trace to pkt_trace_map
for line in packet_trace:
    line = line.strip().strip(",")
    pos = line.find("#")
    key = int(line[:pos])
    pkt_trace_map[key] = line[pos+1:]
    #values = line[pos+1:].split(",")

    '''
    target = ""
    count = 0
    for value in values:
        tmp = int(value)
        target = target+str((tmp+1)*2)
    '''

# Load basic block offset from constant condition to const_condition_set
for line in const_condition:
    key = line[line.find(",")+1:line.rfind("|")]
    const_condition_set.add(key)

# Remove constant conditions from total conditions and map its bb_offset to new packet trail
collected_pkts = set()
condition_index = 0
for line in tot_condition:
    key = line[line.find(",")+1:line.rfind("|")] #bb_block

    if key not in const_condition_set:
        #print "Not Constant Condition:"
        #print key
        condition_file = file("UNCONSTANT_CONDITION_"+str(condition_index)+".txt", "w")
        condition_file.write(line)
        condition_file.close()

        tmps = key.split(":")
        bb_val = int(tmps[0][1:])
        off_val = int(tmps[1])
        index = bb_val*MAX_OFFSET+off_val
        if index not in pkt_trace_map:
            print str(index) + " not found"
            continue
        # map index with
        #collected_pkts.add(pkt_trace_map[index])
        #print line+"/"+pkt_trace_map[index]

        pkt_trace_str = pkt_trace_map[index].strip("|")
        pkt_trace_vectors = pkt_trace_str.split("|")

        #print "TARGET_TRACK_"+str(condition_index)
        target_traces = file("TARGET_TRACK_"+str(condition_index)+".txt", "w")
        condition_index = condition_index + 1
        for pkt_trace in pkt_trace_vectors:
            # for each pkt_trace
            targets = pkt_trace.split(",")
            count = 0
            for value in targets:
                if int(value) == -1:
                    break
                count = count+1

            if count == 0: # it means this branch is processed during initialization, so any other packet can visit this inst
                target_traces.write("1 0\n");
                continue
            target_traces.write(str(count))
            for i in range(count):
                target_traces.write(" "+str(targets[i]))
            target_traces.write("\n")
        target_traces.close()
print condition_index
