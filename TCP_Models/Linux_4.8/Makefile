export C_INCLUDE_PATH=.:~/Work/Linux_kernel/Replace/Target_Model/LLVM_Version/Linux_Source_Code/abstracted_source_code/Linux_3WHS/
CC=clang
DIR=~/Work/Linux_kernel/Replace/Target_Model/LLVM_Version/Linux_Source_Code/abstracted_source_code/Linux_3WHS/
DEPS=${DIR}TCP_Model.h ${DIR}Model0_tcp_input_defconfig.h ${DIR}Define.h TCP_Model.pch ${DIR}Model1_tcp_input_defconfig.h ${DIR}Model0_tcp_input.c ${DIR}Model1_tcp_input.c
CFLAGS= -c -emit-llvm -g -no-integrated-as -adce -O2 -include ${DIR}TCP_Model.h -include-pch TCP_Model.pch


target.o: TCP_Core.o pan.o $(DEPS)
	clang -o target TCP_Core.o pan.o
TCP_Core.o: TCP_Core.bc $(DEPS)
	llc -filetype=obj -O0 -relocation-model=pic TCP_Core.bc

TCP_Core.bc: Init.bc Model0_TCP_Core.bc Model0_Init.bc Model1_TCP_Core.bc Model1_Init.bc $(DEPS) #Main.bc 
	llvm-link -o TCP_Core.bc Init.bc Model0_TCP_Core.bc Model0_Init.bc Model1_TCP_Core.bc Model1_Init.bc #Main.bc Model1_Init.bc

TCP_Model.pch: ${DIR}TCP_Model.h ${DIR}Define.h ${DIR}Model0_tcp_input_defconfig.h ${DIR}Model1_tcp_input_defconfig.h
	clang -c -g -no-integrated-as -adce -O2 -o TCP_Model.pch ${DIR}TCP_Model.h

Main.bc: ${DIR}main.c $(DEPS)
	clang $(CFLAGS) ${DIR}main.c -o Main.bc

Init.bc: Initialization.bc Initialization0.bc $(DEPS) #Packet_Address.bc
	llvm-link -o Init.bc Initialization.bc Initialization0.bc #Packet_Address.bc

Model0_Init.bc:  Model0_global.bc Model0_Listen_Server_Initialize.bc Model0_SKB_Initialize.bc Model0_Server_A_Initialize.bc Model0_Server_Initialize.bc $(DEPS)
	llvm-link -o Model0_Init.bc Model0_global.bc Model0_Listen_Server_Initialize.bc Model0_SKB_Initialize.bc Model0_Server_A_Initialize.bc Model0_Server_Initialize.bc 

Model1_Init.bc:  Model1_global.bc Model1_Listen_Server_Initialize.bc Model1_SKB_Initialize.bc Model1_Server_A_Initialize.bc Model1_Server_Initialize.bc $(DEPS)
	llvm-link -o Model1_Init.bc Model1_global.bc Model1_Listen_Server_Initialize.bc Model1_SKB_Initialize.bc Model1_Server_A_Initialize.bc Model1_Server_Initialize.bc 

Model0_TCP_Core.bc: Model0_bytes_order.bc Model0_tcp_input.bc $(DEPS) #Model0_extern.bc Model0_tcp_ipv4.bc
	llvm-link -o Model0_TCP_Core.bc Model0_bytes_order.bc Model0_tcp_input.bc #Model0_extern.bc Model0_tcp_ipv4.bc

Model1_TCP_Core.bc: Model1_bytes_order.bc Model1_tcp_input.bc $(DEPS) #Model1_extern.bc Model1_tcp_ipv4.bc
	llvm-link -o Model1_TCP_Core.bc Model1_bytes_order.bc Model1_tcp_input.bc #Model1_extern.bc Model1_tcp_ipv4.bc

# Initialization
Initialization0.bc: ${DIR}Initialization0.c $(DEPS)
	clang $(CFLAGS) ${DIR}Initialization0.c
	#Model0
Model0_global.bc: ${DIR}Model0_global2.c $(DEPS)
	clang $(CFLAGS) ${DIR}Model0_global2.c -o Model0_global.bc
Model0_Listen_Server_Initialize.bc: ${DIR}Model0_Listen_Server_Initialize5.c $(DEPS)
	clang $(CFLAGS) ${DIR}Model0_Listen_Server_Initialize5.c -o Model0_Listen_Server_Initialize.bc 
	clang -E -no-integrated-as -adce -O0 -include ${DIR}TCP_Model.h -include-pch TCP_Model.pch Model0_Listen_Server_Initialize5.c -o Model0_Listen_Server_Initialize5.i
	#Model1
Model1_global.bc: ${DIR}Model1_global2.c $(DEPS)
	clang $(CFLAGS) ${DIR}Model1_global2.c -o Model1_global.bc
Model1_Listen_Server_Initialize.bc: ${DIR}Model1_Listen_Server_Initialize5.c $(DEPS)
	clang $(CFLAGS) ${DIR}Model1_Listen_Server_Initialize5.c -o Model1_Listen_Server_Initialize.bc

## is enabled only in EST Mode
Model0_Server_A_Initialize.bc: ${DIR}Model0_Server_A_Initialize_EST.c $(DEPS)
	clang $(CFLAGS) ${DIR}Model0_Server_A_Initialize_EST.c -o Model0_Server_A_Initialize.bc
Model0_Server_Initialize.bc: ${DIR}Model0_Server_Initialize_EST.c $(DEPS)
	clang $(CFLAGS) ${DIR}Model0_Server_Initialize_EST.c -o Model0_Server_Initialize.bc
Model1_Server_A_Initialize.bc: ${DIR}Model1_Server_A_Initialize_EST.c $(DEPS)
	clang $(CFLAGS) ${DIR}Model1_Server_A_Initialize_EST.c -o Model1_Server_A_Initialize.bc
Model1_Server_Initialize.bc: ${DIR}Model1_Server_Initialize_EST.c $(DEPS)
	clang $(CFLAGS) ${DIR}Model1_Server_Initialize_EST.c -o Model1_Server_Initialize.bc


Model0_SKB_Initialize.bc: ${DIR}Model0_SKB_Initialize_EST.c $(DEPS)
	clang $(CFLAGS) ${DIR}Model0_SKB_Initialize_EST.c -o Model0_SKB_Initialize.bc
Model1_SKB_Initialize.bc: ${DIR}Model1_SKB_Initialize_EST.c $(DEPS)
	clang $(CFLAGS) ${DIR}Model1_SKB_Initialize_EST.c -o Model1_SKB_Initialize.bc

#Model0_Address.bc: Model0_Address.c $(DEPS)
#	clang $(CFLAGS) Model0_Address.c
#Packet_Address.bc: Packet_Address.c $(DEPS)
#	clang $(CFLAGS) Packet_Address.c
#Model0_Client_Initialize.bc: ${DIR}Model0_Client_Initialize.c $(DEPS)
#	clang $(CFLAGS) ${DIR}Model0_Client_Initialize.c
# TCP Core functions

Initialization.bc: ${DIR}Initialization_EST_Listen.c $(DEPS)
	clang $(CFLAGS) ${DIR}Initialization_EST_Listen.c -o Initialization.bc
	#Model0
Model0_bytes_order.bc: ${DIR}Model0_bytes_order.c $(DEPS)
	clang $(CFLAGS) ${DIR}Model0_bytes_order.c
Model0_tcp_input.bc: ${DIR}Model0_tcp_input.c $(DEPS)
	clang $(CFLAGS) ${DIR}Model0_tcp_input.c
#Model0_tcp_ipv4.bc: ${DIR}Model0_tcp_ipv4.c $(DEPS)
#	clang $(CFLAGS) ${DIR}Model0_tcp_ipv4.c
#Model0_extern.bc: ${DIR}Model0_extern.c $(DEPS)
#	clang $(CFLAGS) ${DIR}Model0_extern.c
	#Model1
Model1_bytes_order.bc: ${DIR}Model1_bytes_order.c $(DEPS)
	clang $(CFLAGS) ${DIR}Model1_bytes_order.c
Model1_tcp_input.bc: ${DIR}Model1_tcp_input.c $(DEPS)
	clang $(CFLAGS) ${DIR}Model1_tcp_input.c
#Model1_tcp_ipv4.bc: ${DIR}Model1_tcp_ipv4.c $(DEPS)
#	clang $(CFLAGS) ${DIR}Model1_tcp_ipv4.c
#Model1_extern.bc: ${DIR}Model1_extern.c $(DEPS)
#	clang $(CFLAGS) ${DIR}Model1_extern.c

pan.o: ${DIR}pan.c
	$(CC) -fPIC -O0 -g -no-integrated-as -adce -DVECTORSZ=180000 -DSAFETY -DNOFAIR -DNOBOUNDCHECK -DNOCOMP -DREACH -c ${DIR}pan.c 
	#$(CC) -fPIC -O0 -g -no-integrated-as -adce -DVECTORSZ=80000 -DSAFETY -DNOFAIR -DNOBOUNDCHECK -DNOCOMP -c ${DIR}pan.c 
	#$(CC) -fPIC -O0 -g -no-integrated-as -adce -DVECTORSZ=80000 -DSAFETY -DNOFAIR -DNOBOUNDCHECK -DNOCOMP -DBITSTATE -c ${DIR}pan.c 
	#$(CC) -fPIC -O0 -g -no-integrated-as -adce -DVECTORSZ=80000 -DSAFETY -DNOFAIR -DNOBOUNDCHECK -DNOCOMP -DBFS -c ${DIR}pan.c 

#klee_main.bc: klee_main.c
#	clang -emit-llvm -g -O0 -no-integrated-as -adce -fPIC -I ${DIR} -I ~/Work/KLEE_Platform/klee/include/ -c klee_main.c  -o klee_main.bc

#klee_main.c: klee_main_part1.c klee_main_part2.c
#	cat klee_main_part1.c klee_main_part2.c > klee_main.c

#klee_main_part1.c: ${DIR}Model0_global.c ${DIR}Model0_Server_Initialize.c ${DIR}Model0_Server_A_Initialize.c
#	python ../Source_Code_abstracted2/Script/KLEE_Make_Symbolic.py

#klee_main_part2.c: klee_main_part1.c
#	python ../Source_Code_abstracted2/Script/KLEE_Enumeration_Generation.py

#KLEE_Seed_Generation.o: KLEE_Seed_Generation.c
#	clang -I ${DIR} -O2 -c KLEE_Seed_Generation.c -o ../KLEE_Seed_Generation.o

#KLEE_Seed_Generation.c: klee_main.c
#	python ../Source_Code_abstracted2/Script/KLEE_Seed_Meta.py
