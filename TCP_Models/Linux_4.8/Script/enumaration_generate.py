#!/bin/bash

# -------------------------
# Filename: enumeration_generation.py
# Revision: 1.0
# Data:     long ago
# Author:   Yue Cao
# Description:  Generate all interations for model used in model checking
# -------------------------
import os
#f = file("../model_part.txt", "w")
f_head = file("../new_model_head", "r")
f_tail = file("../new_model_tail", "r")
f = file("../new_model", "w")


for line in f_head:
    f.write(line)

count = 0;
for seq in range(5):
    for ack_seq in range(5):
        for ack in range(2):
            for rst in range(2):
                for syn in range(2):
                    for urg in range(2):
                        for psh in range(2):
                            for spoofed in range(2):
                                for has_payload in range(3):
                                    #with data
                                    f.write("\t\t::c_code{Model0_th = (struct Model0_tcphdr *)(&Model0_Skb_In[packet_dep])->Model0_data; Model0_th->Model0_seq = Model0_htonl(seq_val-2+"+str(seq)+"); Model0_th->Model0_ack_seq = Model0_htonl(ack_val-2+"+str(ack_seq)+"); Model0_th->Model0_ack = " + str(ack) + "; Model0_th->Model0_rst = " + str(rst) + "; Model0_th->Model0_syn = " + str(syn) + "; Model0_th->Model0_urg = " + str(urg) + "; Model0_th->Model0_psh = " + str(psh) + "; Spoofed(" + str(spoofed)+", "+str(has_payload)+", packet_dep); Execution(packet_dep, " + str(count) + "); }; assert( c_expr { Verify() }) \n");
                                    count = count+1

for line in f_tail:
    f.write(line)
#os.system("cat ../model_part.txt > ../new_model_tmp")
#os.system("cat ../new_model_head ../model_part.txt > ../new_model_tmp")
#os.system("cat ../new_model_tmp ../new_model_tail > ../new_model")
'''
count = 0;
for seq in range(5):
    for ack_seq in range(5):
        for rst in range(2):
            for syn in range(2):
                for spoofed in range(2):
                    for has_payload in range(3):
                        #with data
                        f.write("\t\t::c_code{Model0_th = (struct Model0_tcphdr *)(&Model0_Skb_In[now.packet_dep])->Model0_data; Model0_th->Model0_seq = Model0_htonl("+str(seq)+"); Model0_th->Model0_ack_seq = Model0_htonl("+str(ack_seq)+"); Model0_th->Model0_rst = " + str(rst) + "; Model0_th->Model0_syn = " + str(syn) + "; Spoofed(" + str(spoofed)+", "+str(has_payload)+", now.packet_dep); Execution(now.packet_dep, " + str(count) + "); }; assert( c_expr { Verify() }) \n");
                        #f.write("\t\t::c_code{Model0_tcb = ((struct Model0_tcp_skb_cb *)&((&Model0_Skb_In[now.packet_dep])->Model0_cb[0])); Model0_th->Model0_seq = Model0_htonl("+str(seq)+"); Model0_th->Model0_ack_seq = Model0_htonl("+str(ack_seq)+"); Model0_th->Model0_rst = " + str(rst) + "; Model0_th->Model0_syn = " + str(syn) + "; Spoofed(" + str(spoofed)+", "+str(has_payload)+", now.packet_dep); Execution(now.packet_dep, " + str(count) + "); }; assert( c_expr { Verify() }) \n");
                        count = count+1
                        #f.write("\t\t::c_code{Model0_tcb = ((struct Model0_tcp_skb_cb *)&((&Model0_Skb_In[now.packet_dep])->Model0_cb[0])); Model0_tcb->Model0_seq = " + str(seq+2) + "; Model0_tcb->Model0_end_seq = " + str(seq+2) + "; Model0_tcb->Model0_ack_seq = " + str(ack_seq) + "; Model0_th->Model0_rst = " + str(rst) + "; Model0_th->Model0_syn = " + str(syn) + "; Spoofed(" + str(spoofed)+", "+str(has_payload)+", now.packet_dep); Execution(now.packet_dep); }; assert( c_expr { Verify() }) \n");
                        #f.write("\t\t::c_code{ tcb->seq = " + str(seq) + "; tcb->end_seq = " + str(seq) + "; tcb->ack_seq = " + str(ack_seq) + "; th->rst = " + str(rst) + "; th->syn = " + str(syn) + "; Spoofed(" + str(spoofed)+", "+str(has_payload)+"); Execution(); }; assert( c_expr { Verify() }) \n");
                        #without data
                        #f.write("\t\t::c_code{ Model0_tcb->Model0_seq = " + str(seq) + "; Model0_tcb->Model0_end_seq = " + str(seq) + "; Model0_tcb->Model0_ack_seq = " + str(ack_seq) + "; Model0_th->Model0_rst = " + str(rst) + "; Model0_th->Model0_syn = " + str(syn) + "; Spoofed(" + str(spoofed)+"); Execution(); }; assert( c_expr { Verify() }) \n");
                        #f.write("\t\t::assert( c_expr { Verify("+str(seq)+", "+str(ack_seq)+", "+str(rst)+", "+str(syn)+", "+str(spoofed)+", "+str(has_payload)+") }) \n");
                        #f.write("\t\t::c_code { Verify("+str(seq)+", "+str(ack_seq)+", "+str(rst)+", "+str(syn)+", "+str(spoofed)+", "+str(has_payload)+"); } \n");
'''
