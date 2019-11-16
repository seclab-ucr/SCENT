cp ${2}_Model0_Listen_Server_Initialize.c ${1}_Model0_Listen_Server_Initialize.c
cp ${2}_Model1_Listen_Server_Initialize.c ${1}_Model1_Listen_Server_Initialize.c
cp ${2}_Model0_Server_Initialize.c ${1}_Model0_Server_Initialize.c
cp ${2}_Model1_Server_Initialize.c ${1}_Model1_Server_Initialize.c
cp ${2}_Model0_Server_A_Initialize.c ${1}_Model0_Server_A_Initialize.c
cp ${2}_Model1_Server_A_Initialize.c ${1}_Model1_Server_A_Initialize.c
cp ${2}_Model0_global.c ${1}_Model0_global.c
cp ${2}_Model1_global.c ${1}_Model1_global.c

cp ${2}_Model0_Listen_Server_Initialize.bc ${1}_Model0_Listen_Server_Initialize.bc
cp ${2}_Model1_Listen_Server_Initialize.bc ${1}_Model1_Listen_Server_Initialize.bc
cp ${2}_Model0_Server_Initialize.bc ${1}_Model0_Server_Initialize.bc
cp ${2}_Model1_Server_Initialize.bc ${1}_Model1_Server_Initialize.bc
cp ${2}_Model0_Server_A_Initialize.bc ${1}_Model0_Server_A_Initialize.bc
cp ${2}_Model1_Server_A_Initialize.bc ${1}_Model1_Server_A_Initialize.bc
cp ${2}_Model0_global.bc ${1}_Model0_global.bc
cp ${2}_Model1_global.bc ${1}_Model1_global.bc

cp ${2}_Model0_Init.bc ${1}_Model0_Init.bc
cp ${2}_Model1_Init.bc ${1}_Model1_Init.bc
llvm-link -o ${1}.bc ${1}_core.bc ${1}_Model0_Init.bc ${1}_Model1_Init.bc
llc -filetype=obj -O0 -relocation-model=pic ${1}.bc -o ${1}.o
clang -o ${1} ${1}.o pan.o
