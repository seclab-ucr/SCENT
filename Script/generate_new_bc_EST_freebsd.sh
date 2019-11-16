cp ${2}_core.bc ${1}_core.bc
llvm-link -o ${1}_Model0_Init.bc ${1}_Model0_global.bc ${1}_Model0_Listen_Server_Initialize.bc ${1}_Model0_Server_Initialize.bc ${1}_Model0_Server_A_Initialize.bc Model0_SKB_Initialize.bc Model0_SKB0_Initialize.bc
llvm-link -o ${1}_Model1_Init.bc ${1}_Model1_global.bc ${1}_Model1_Listen_Server_Initialize.bc ${1}_Model1_Server_Initialize.bc ${1}_Model1_Server_A_Initialize.bc Model1_SKB_Initialize.bc Model1_SKB0_Initialize.bc
llvm-link -o ${1}.bc ${1}_core.bc ${1}_Model0_Init.bc ${1}_Model1_Init.bc
llc -filetype=obj -O0 -relocation-model=pic ${1}.bc -o ${1}.o
clang -o ${1} ${1}.o pan.o

