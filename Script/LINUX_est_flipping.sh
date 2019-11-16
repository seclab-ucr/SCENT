#!/bin/bash

# --------------------------------------------------
# Author:     Yue Cao
# Email:      ycao009@cs.ucr.edu
# Description: Use BFS to visit all transformed programs.
# --------------------------------------------------

#Configurable
INDEX=Linux_EST_PORT_Listen #set name of the folder to store all results
Debug=true
Debug0=true
Handshake=false
PROCESS_LIMIT=30 # the number of processes used to run concolic execution

SCENT_PATH=~/Work/SCENT
CODE_PATH=${SCENT_PATH}/TCP_Models/Linux_4.8
BIN_PATH=${SCENT_PATH}/Execution_Results/${INDEX}
LLVM_PATH=/data/home/yue/Work/LLVM-6.0/build/bin/
KLEE_BUILD_PATH=${SCENT_PATH}/Tools/klee_build/bin
KLEE_NOPATH_BUILD_PATH=${SCENT_PATH}/Tools/klee_no_path_build/bin
#KLEE_BUILD_PATH=~/Work/KLEE_Platform/klee_build_dir2/bin
#KLEE_NOPATH_BUILD_PATH=~/Work/KLEE_Platform/klee_build_dir3/bin

# function that process klee parallel
process_klee ()
{
    index=$1
    rm klee_result_${index}_0.txt
    touch klee_result_${index}_0.txt
    rm klee_result_${index}_1.txt
    touch klee_result_${index}_1.txt

    while IFS='' read -r line || [[ -n "$line" ]]
    do
        echo $line
        argument=$line
        # check if current path would cause conflict TODO: change klee's path
        ${KLEE_BUILD_PATH}/klee -only-replay-seeds -seed-out file.bout -flipping-condition-file UNCONSTANT_CONDITION_${index}.txt klee_test.bc $line 1> cy_tmp.txt  2>${index}_klee_result.txt

        if [ ! -s klee_result_${index}_0.txt ]
        then
            cat ${index}_klee_result.txt | grep "CY_Target0|" > klee_result_${index}_0.txt
        fi
        if [ ! -s klee_result_${index}_1.txt ]
        then
            cat ${index}_klee_result.txt | grep "CY_Target1|" > klee_result_${index}_1.txt
        fi


        if [ -s klee_result_${index}_0.txt ] && [ -s klee_result_${index}_1.txt ]
        then
            break
        fi
    done < "TARGET_TRACK_${index}.txt"
    if [ ! -s klee_result_${index}_0.txt ] && [ -s klee_result_${index}_1.txt ]
    then
        # klee_build_dir3/bin/klee won't consider constraints alone the path
        echo "Without constraints alone the path:"$argument
        ${KLEE_NOPATH_BUILD_PATH}/klee -only-replay-seeds -seed-out file.bout -flipping-condition-file UNCONSTANT_CONDITION_${index}.txt klee_test.bc $argument 1> cy_tmp.txt  2>${index}_klee_result.txt

        if [ ! -s klee_result_${index}_0.txt ]
        then
            cat ${index}_klee_result.txt | grep "CY_Target0|" > klee_result_${index}_0.txt
        fi
        if [ ! -s klee_result_${index}_1.txt ]
        then
            cat ${index}_klee_result.txt | grep "CY_Target1|" > klee_result_${index}_1.txt
        fi
    fi

    # PRIORITY has been marked at the end
    # check duplication and get the sym_id

    cat klee_result_${index}_0.txt >> klee_target.txt
    cat klee_result_${index}_1.txt >> klee_target.txt
}

echo $BIN_PATH

mkdir $BIN_PATH
cd $BIN_PATH
cp ${CODE_PATH}/Makefile_build_EST ./Makefile
mkdir ERROR_DEBUG
rm Edge_set.log
touch Edge_set.log
rm Branches_set.log
touch Branches_set.log
rm Branches_BB_set.log
touch Branches_BB_set.log
rm Symbolic_ID.log
touch Symbolic_ID.log

rm BFS_QUEUE_FIRST.txt
touch BFS_QUEUE_FIRST.txt
rm BFS_QUEUE_SECOND.txt
touch BFS_QUEUE_SECOND.txt

if ${Debug0}; then
    cd ${CODE_PATH}
    spin -a new_model_EST_new
    python Script/PAN_INSTRUMENT.py pan.c
    cp new_model_EST_new ${BIN_PATH}/
    cd ${BIN_PATH}
fi

if ${Debug}; then
# Compile shared files
make
mkdir Source_Code_Analysis
cp -r ${CODE_PATH}/*.c Source_Code_Analysis/
cp -r ${CODE_PATH}/*.h Source_Code_Analysis/
# Prepare KLEE main file
#python ../Source_Code_abstracted2/Script/KLEE_Make_Symbolic.py
#python ../Source_Code_abstracted2/Script/KLEE_Enumeration_Generation.py
#cat klee_main_part1.c klee_main_part2.c > klee_main.c
#clang -emit-llvm -g -O0 -no-integrated-as -adce -fPIC -I ~/Work/KLEE_Platform/klee/include/ -c klee_main.c  -o klee_main.bc

# Prepare KLEE Seed generation code (../klee_seed)
#python ../Source_Code_abstracted2/Script/KLEE_Seed_Meta.py
#clang -O2 -c KLEE_Seed_Generation.c -o KLEE_Seed_Generation.o

fi

echo ${Handshake}
echo $Handshake
Model1_offset=$(head -n 1 bb2line_v2.txt | awk '{print $3}')
Model0_end=$(head -n 4 bb2line_v2.txt | tail -1 | awk '{print $2}')
echo "--Basic Instrumentation Done--"
Left=0
#Right=1
if [ "$Handshake" = "true" ] ; then
    echo "3whs true"
    cp $CODE_PATH/Model0_global2.c CY_Model0_global.c
    cp $CODE_PATH/Model1_global2.c CY_Model1_global.c
    cp $CODE_PATH/Model0_Listen_Server_Initialize5.c CY_Model0_Listen_Server_Initialize.c
    cp $CODE_PATH/Model1_Listen_Server_Initialize5.c CY_Model1_Listen_Server_Initialize.c

    cp Model0_global.bc CY_Model0_global.bc
    cp Model1_global.bc CY_Model1_global.bc
    cp Model0_Listen_Server_Initialize.bc CY_Model0_Listen_Server_Initialize.bc
    cp Model1_Listen_Server_Initialize.bc CY_Model1_Listen_Server_Initialize.bc
    cp Model0_Init.bc CY_Model0_Init.bc
    cp Model1_Init.bc CY_Model1_Init.bc
else
    echo ${Handshake}
    echo "3whs false"
    cp $CODE_PATH/Model0_global2.c CY_Model0_global.c
    cp $CODE_PATH/Model1_global2.c CY_Model1_global.c
    cp $CODE_PATH/Model0_Listen_Server_Initialize5.c CY_Model0_Listen_Server_Initialize.c
    cp $CODE_PATH/Model1_Listen_Server_Initialize5.c CY_Model1_Listen_Server_Initialize.c
    cp $CODE_PATH/Model0_Server_Initialize_EST.c CY_Model0_Server_Initialize.c
    cp $CODE_PATH/Model0_Server_A_Initialize_EST.c CY_Model0_Server_A_Initialize.c
    cp $CODE_PATH/Model1_Server_Initialize_EST.c CY_Model1_Server_Initialize.c
    cp $CODE_PATH/Model1_Server_A_Initialize_EST.c CY_Model1_Server_A_Initialize.c

    cp Model0_global.bc CY_Model0_global.bc
    cp Model1_global.bc CY_Model1_global.bc
    cp Model0_Listen_Server_Initialize.bc CY_Model0_Listen_Server_Initialize.bc
    cp Model1_Listen_Server_Initialize.bc CY_Model1_Listen_Server_Initialize.bc
    cp Model0_Server_Initialize.bc CY_Model0_Server_Initialize.bc
    cp Model0_Server_A_Initialize.bc CY_Model0_Server_A_Initialize.bc
    cp Model1_Server_Initialize.bc CY_Model1_Server_Initialize.bc
    cp Model1_Server_A_Initialize.bc CY_Model1_Server_A_Initialize.bc
    cp Model0_Init.bc CY_Model0_Init.bc
    cp Model1_Init.bc CY_Model1_Init.bc
fi

cp TCP_Core_v4.bc CY_core.bc
llvm-link -o CY.bc CY_core.bc CY_Model0_Init.bc CY_Model1_Init.bc
llc -filetype=obj -O0 -relocation-model=pic CY.bc -o CY.o
clang -o CY CY.o pan.o
#add CY to queue
echo "CY" >> BFS_QUEUE_FIRST.txt

#while  [ $Left -lt $Right ]
while  true
do
    echo "Inside Loop"
    if [ $(wc -c < BFS_QUEUE_FIRST.txt) -gt 1 ] #since it may ends at newline (i.e., $)
    then
        CUR=$(head -n 1 BFS_QUEUE_FIRST.txt)
        echo "$(tail -n +2 BFS_QUEUE_FIRST.txt)" > BFS_QUEUE_FIRST.txt
    elif [ $(wc -c < BFS_QUEUE_SECOND.txt) -gt 1 ]
    then
        CUR=$(head -n 1 BFS_QUEUE_SECOND.txt)
        echo "$(tail -n +2 BFS_QUEUE_SECOND.txt)" > BFS_QUEUE_SECOND.txt
    else
        echo "Program End"
        break
    fi

    echo "Current Executig File: "$CUR
    if [ "$CUR" == "" ]
    then
        continue
    fi
    echo "---Start processing ${Left}th Program---"
    #time ./$CUR -z12 1> new_input0_v4.txt 2> new_v4.txt
    time ./$CUR 1> new_input0_v4.txt 2> new_v4.txt

    echo "  >>Model Checking is done"
    #parse output, the new result will be used as input
    #cat ../new_v4.txt | grep "^File" > ../new_input0_v4.txt #current value in cmp condition

    tail -n 50000 new_input0_v4.txt > meta_info.txt
    if cat meta_info.txt | grep -q "errors: 1"; then
        echo " == Error found at $CUR == "
        cp $CUR ERROR_DEBUG/$CUR
        Left=$((Left+1))
        continue
    fi

    if cat meta_info.txt | grep -q "errors: "; then
        echo "$CUR runs normally"
    else
        echo "$CUR is crushed "
        Left=$((Left+1))
        continue
    fi

    ${SCENT_PATH}/Script/TEXTFILE_PROCESS.sh $PROCESS_LIMIT ${SCENT_PATH}

    ### DEBUG PURPOSE: check why no new coverage rate ###
    cp Edge_set.log ${CUR}_Edge_set.log
    ### Update Covered Edge INFO and calculate cumulative edge coverage rate ###
    python ${SCENT_PATH}/Script/Calculate_cov.py meta_info.txt \&> coverage.txt
    mv Edge_set_bak.log Edge_set.log

    Cur=$(cat coverage.txt | grep "Coverage: ")
    echo "  >>Current Culmutative Coverage: $Cur"

    python ${SCENT_PATH}/Script/NEW_INPUT_Parse_Min_Max.py NEW_INPUT_v4.txt > NEW_INPUT_v2.txt
    cp NEW_INPUT_v4.txt ${CUR}_NEW_INPUT_v4.txt
    cp NEW_INPUT_v2.txt ${CUR}_NEW_INPUT_v2.txt

    # greedy strategy: parse new flipping target to NEW_INPUT_v5.txt
    # otherwise, we also need to parse old flipping target, as soon as it doesn't appear in its ancestor [TODO]
    echo "  >>Check if there are new flipping target"
    ### Update Flipped Branches ###
    python ${SCENT_PATH}/Script/Calculate_BBs.py NEW_INPUT_v2.txt  Branches_BB_set.log Branches_BB_set_bak.log $Model1_offset $Model0_end > NEW_INPUT_v5.txt
    mv Branches_BB_set_bak.log Branches_BB_set.log
    cp NEW_INPUT_v5.txt ${CUR}_NEW_INPUT_v5.txt

    if [ ! -s NEW_INPUT_v5.txt ] ; then
        Left=$((Left+1))
        echo "  >>No new flipping basic blocks"
        continue
    fi

    echo "   === Start Symbolic Execution Analysis === "

    llvm-link ${CUR}.bc klee_main.bc -o klee_test.bc
    echo " Generate seed_v1 "
    clang -o klee_seed ${CUR}.o KLEE_Seed_Generation.o
    ./klee_seed 1>Seed_Temp.txt
    echo " Generate seed_v2 "
    python ${CODE_PATH}/Script/KLEE_Seed_Parse.py Seed_Temp.txt Seed_Temp2.txt
    cy_gen-bout Seed_Temp2.txt &> temp.txt
    #mv file.bout ../

    # filter only constants to ../NEW_INPUT_v6.txt
    opt -load IsConstantLib.so -IsConstant ${CUR}.bc 1> temp.bc 2> debug_v4.txt #temp.bc is just used to store output without any other purpose
    cat debug_v4.txt | grep "Constant" > NEW_INPUT_v6.txt

    Line_Count1="$(wc -l < NEW_INPUT_v5.txt)"
    Line_Count2="$(wc -l < NEW_INPUT_v6.txt)"

    if [ $Line_Count1 -ne $(( $Line_Count2/2 )) ]; then
        ### DEBUG Purpose: check when v5 == v6  ###
        echo "Size of NEW_INPUT_v5: "${Line_Count1}
        echo "Size of NEW_INPUT_v6: "${Line_Count2}
        cp NEW_INPUT_v5.txt ${CUR}_NEW_INPUT_v5.txt
        #####################

        echo " Start KLEE "
        #rm HASHED_NEW_INPUT_v5.txt
        #touch HASHED_NEW_INPUT_v5.txt

        # only capture unconstant branches for symbolic execution
        BRANCH_LIMIT=$(python ${SCENT_PATH}/Script/KLEE_Target_Filter_new.py NEW_INPUT_v5.txt NEW_INPUT_v6.txt PACKET_TRACK.txt 2>&1) #TARGET_TRACKS.txt
        echo "BRANCH_LIMIT:"$BRANCH_LIMIT

        if [ $BRANCH_LIMIT -eq 0 ]; then
            echo "BRANCH_LIMIT == 0?!"
            Left=$((Left+1))
            continue
        fi

        rm klee_target.txt
        touch klee_target.txt # change of initialization for each branch flipping
        ## TODO: set the limit of maximal number of process each time

        TEMP=$(expr ${BRANCH_LIMIT} - 1 )
        LOOP_NUM=$(expr $TEMP / $PROCESS_LIMIT + 1 )
        echo Loop_num: $LOOP_NUM

        #for ((j=0; j<$LOOP_NUM;))
        for j in `seq 0 $LOOP_NUM`
        do
            start_num=$(expr $j \* $PROCESS_LIMIT)
            end_num=$(expr $start_num + $PROCESS_LIMIT)
            echo "start_num:"$start_num
            echo "end_num:"$end_num
            if [ $end_num -gt $BRANCH_LIMIT ];
            then
                end_num=$BRANCH_LIMIT
            fi

            for i in `seq $start_num $(($end_num-1))`;
            do
                # TODO: append branch to NEW_INPUT_V6.txt if the target variable is not tainted [need double confirm]
                echo "${i} is under testing"
                process_klee $i &
            done
            wait
            echo "wait"
        done

        cat klee_target.txt | sort -u > ${CUR}_current_klee_target.txt
        Read_File="${CUR}_current_klee_target.txt"

        echo "Read file: "$Read_File
        echo "  >>Start Flip Initialization One By One"
            while IFS='' read -r line || [[ -n "$line" ]]
            do
                name="$line"
                echo "  >>>$name"
                echo "$name" > "FLIP.txt"
                #python Codes_consistency.py ../FLIP.txt
                #echo "  >> Modified Target"
                #cat ../FLIP.txt
                echo "  >>>>>"
                tmp_index=$((${#name}-1))
                echo $tmp_index
                PRIORITY=${name:$tmp_index:1}
                echo $PRIORITY
                SYM_ID=$(python ${SCENT_PATH}/Script/Symbolic_ID_lookup.py FLIP.txt Symbolic_ID.log 2>&1)
                echo SYM$SYM_ID
                NEXT=${CUR}_SYM${SYM_ID}
                python ${SCENT_PATH}/Script/Update_Initialization_EST.py $CUR $NEXT ${CODE_PATH} ${LLVM_PATH} > tmp.txt
                #opt -load changeInitializationLib.so -changeInitialization ../CY_$Left.bc 1>../CY_$Right.bc 2>../temp.log
                #Temp=$(cat ../temp.log | grep "Success")
                #if [ "$Temp" = "Success" ]; then
                if cat tmp.txt | grep -q "Success"; then
                    sh ${SCENT_PATH}/Script/generate_new_bc_EST.sh $NEXT $CUR &
                    #sh test3.sh CY_$Right &
                    ${NEXT}=$!
                    echo "${NEXT} is generated"
                    if [ $PRIORITY -eq 0 ]; then
                        echo ${NEXT} >> BFS_QUEUE_FIRST.txt
                    else
                        echo ${NEXT} >> BFS_QUEUE_SECOND.txt
                    fi
                    #Right=$((Right+1))
                fi

            done < "$Read_File"
        echo "Symbolic Execution is finished"
    fi
    #Process Constants
    Read_File="NEW_INPUT_v6.txt"
    echo "  >>Start Flip Constants One By One"
    while IFS='' read -r line || [ -n "$line" ]
    do
        name="$line"
        echo "  >>>$name"
        echo "$name" > "FLIP.txt"
        #python Codes_consistency.py ../FLIP.txt
        echo "  >>>>>"
        #Model0,b1043:8|1#-1#1#1
        #TEMP=$(echo $name| cut -d'|' -f 1)
        TEMP=${name#*,}
        TEMP2=${TEMP%|*}
        echo ${TEMP2}
        tmp_index=$((${#name}-1))
        PRIORITY=${name:$tmp_index:1}
        NEXT=${CUR}_$TEMP2@${PRIORITY}
        opt -load changeConstantsLib.so -changeConstants ${CUR}_core.bc 1>${NEXT}_core.bc 2>temp.log #TODO test
        #Temp=$(cat ../temp.log | grep "Success")
        #if [ "$Temp" = "Success" ]; then
        if cat temp.log | grep -q "Success"; then # If it's always successful, then we can include opt inside test3.sh
            sh ${SCENT_PATH}/Script/generate_new_bc_constant_EST.sh $NEXT $CUR &
            #P_$Right=$!
            echo "$NEXT is generated"
            if [ $PRIORITY -eq 0 ]; then
                echo ${NEXT} >> BFS_QUEUE_FIRST.txt
            else
                echo ${NEXT} >> BFS_QUEUE_SECOND.txt
            fi
            #Right=$((Right+1))
        fi
    done < "$Read_File"
    #fi
    echo " === Start Flipping the rest branches === "
    echo "============== $Left th program is done ================"
    Left=$((Left+1))
done
