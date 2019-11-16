#!/bin/bash

# -------------------------
# Filename: RUN_KLEE.sh
# Revision: 1.0
# Data:     11/20/2018
# Author:   Yue Cao
# Description:  shell script to run prepare bc file for klee, then run it
# -------------------------

#clang -c ../Initialization0.c
#clang -c ../Initialization3.c
#clang -c ../Initialization.c
#clang -c ../Model0_global.c
##clang -c ../Model1_global.c
#clang -c ../Model0_Address.c
##clang -c ../Model1_Address.c
#clang -c ../Packet_Address.c
#clang -c ../Model0_Server_Temp.c
#clang -c ../Model0_Server_A_Temp.c
#clang -c ../Model0_Client_Initialize.c
#clang -c ../Model0_bytes_order.c
#clang -c ../dfsan.c
#clang -O2 -DVECTORSZ=80000 -DSAFETY -DNOFAIR -DNOBOUNDCHECK -DNOCOMP -c ../pan.c


#clang -emit-llvm -g -O2 -no-integrated-as -adce -fPIC -c ../Model0_tcp_input.c
#clang -emit-llvm -g -O2 -no-integrated-as -adce -fPIC -c ../Initialization.c
#clang -emit-llvm -g -O2 -no-integrated-as -adce -fPIC -c ../Initialization0.c
#clang -emit-llvm -g -O2 -no-integrated-as -adce -fPIC -c ../Model0_Address.c
#clang -emit-llvm -g -O2 -no-integrated-as -adce -fPIC -c ../Model0_global.c
#clang -emit-llvm -g -O2 -no-integrated-as -adce -fPIC -c ../Model0_Server_Temp.c
#clang -emit-llvm -g -O2 -no-integrated-as -adce -fPIC -c ../Model0_Server_A_Temp.c
#clang -emit-llvm -g -O2 -no-integrated-as -adce -fPIC -c ../Model0_Client_Initialize.c
#clang -emit-llvm -g -O2 -no-integrated-as -adce -fPIC -c ../Model0_bytes_order.c
#clang -emit-llvm -g -O2 -no-integrated-as -adce -fPIC -c ../Packet_Address.c
#clang -emit-llvm -g -O2 -no-integrated-as -adce -fPIC -c ../dfsan.c
cat ../klee_main_part1.c ../klee_main_part2.c > ../klee_main.c
clang -emit-llvm -g -O0 -no-integrated-as -adce -fPIC -I ~/Work/KLEE_Platform/klee/include/ -c ../klee_main.c -o ../klee_main.bc
#
#
#llvm-link Model0_tcp_input.bc Initialization.bc Initialization0.bc Model0_Address.bc Model0_global.bc Model0_Server_Temp.bc Model0_Server_A_Temp.bc Model0_Client_Initialize.bc Model0_bytes_order.bc Packet_Address.bc -o new_pan.bc
llvm-link ../new_v4_old.bc ../klee_main.bc -o ../new_cy.bc

# Generate Seed
python KLEE_Seed_Meta.py
clang -O2 -c ../KLEE_Seed_Generation.c -o ../KLEE_Seed_Generation.o

llc -filetype=obj -O0 -relocation-model=pic ../new_v4_old.bc -o ../new_v4_old.o
clang -o ../klee_seed ../new_v4_old.o ../KLEE_Seed_Generation.o
../klee_seed 1>../Seed_Temp.txt
python KLEE_Seed_Parse.py
cy_gen-bout ../Seed_Temp2.txt
mv file.bout ../
# Use seed to run KLEE
klee -only-replay-seeds -seed-out ../file.bout ../new_cy.bc 1 92
