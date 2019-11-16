#!/bin/bash
split -l 10000000 -d --additional-suffix=.txt new_input0_v4.txt text_test
rm new_input0_v4.txt
PROCESS_LIMIT=$1
echo $1
SCENT_PATH=${2}
TOTAL=$(ls -dq text_test* | wc -l)
echo $TOTAL
Count=0
for file in text_test*;
do
    python ${SCENT_PATH}/Script/input_generation_step1.py $file \&> new_test_$Count &
    Count=$((Count+1))
    if [ $(expr $Count % $PROCESS_LIMIT) -eq 0 ];
    then
        wait
        echo "Processed File Num: "$Count
    fi
done
wait
echo "Done"

cat new_test_* >> final.txt
python ${SCENT_PATH}/Script/input_generation_step2.py final.txt \&> NEW_INPUT_v4.txt
rm final.txt
rm text_test*
rm new_test_*
