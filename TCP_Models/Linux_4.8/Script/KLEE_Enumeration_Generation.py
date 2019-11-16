#!/bin/bash

# -------------------------
# Filename: KLEE_Enumeration_Generation.py
# Revision: 1.0
# Data:     11/20/2018
# Author:   Yue Cao
# Description:  Generate all interations for klee test functions in klee_main.c
# -------------------------

f = file("klee_main_part2.c", "w")


f.write("int main(int argc, char* argv[]){\n")
f.write("\tPreProcess();\n")
f.write("\tModel0_Symbolize();\n")
f.write("\tPKT_Prepare();\n")

#f.write("\tModel0_tcp_hdr(&Model0_Skb_In[0])->Model0_ack = 0; Model1_tcp_hdr(&Model1_Skb_In[0])->Model1_ack = 0; Model0_Src_sk = true; Model1_Src_sk = true; Execution(0, 0);\n")
#f.write("\tModel0_tcp_hdr(&Model0_Skb_In[0])->Model0_ack = 0; Model1_tcp_hdr(&Model1_Skb_In[0])->Model1_ack = 0; Model0_Src_sk = false; Model1_Src_sk = false; Execution(0, 0);\n")
#f.write("\tModel0_tcp_hdr(&Model0_Skb_In[0])->Model0_ack = 1; Model1_tcp_hdr(&Model1_Skb_In[0])->Model1_ack = 1;\n")


f.write("\tint packet_num = strtol(argv[1], NULL, 10);\n")
f.write("\tfor (int packet_dep = 0; packet_dep < packet_num; packet_dep++){\n")
f.write("\t\tint tmp = strtol(argv[2+packet_dep], NULL, 10);\n")
f.write("\t\tswitch(tmp){\n")

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
                                    f.write("\t\t\tcase " + str(count) + ":\n\t\t\t\tModel0_th = (struct Model0_tcphdr *)(&Model0_Skb_In[packet_dep])->Model0_data; Model0_th->Model0_seq = Model0_htonl(seq_val-2+"+str(seq)+"); Model0_th->Model0_ack_seq = Model0_htonl(ack_val-2+"+str(ack_seq)+"); Model0_th->Model0_ack = " + str(ack) + "; Model0_th->Model0_rst = " + str(rst) + "; Model0_th->Model0_syn = " + str(syn) + "; Model0_th->Model0_urg = " + str(urg) + "; Model0_th->Model0_psh = " + str(psh) + "; Spoofed(" + str(spoofed)+", "+str(has_payload)+", packet_dep); Execution(packet_dep, " + str(count) + ");\n\t\t\t\tbreak;\n");
                                    count = count+1
f.write("\t\t}\n")
f.write("\t}\n")
f.write("}\n")
