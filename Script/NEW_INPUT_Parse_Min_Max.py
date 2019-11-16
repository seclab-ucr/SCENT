'''
1. Extract targets that have one fixed variable and one varied variable
2. Generate its target value, based on (1. predicate, 2. existed values)

input: NEW_INPUT.txt
'''

import sys
file_in = sys.argv[1]

f_in = file(file_in, "r")

for line in f_in:
    #if line.find("Model0") == -1:
    #    continue
    if line.find("|") == -1: #happen only when we run with multi-cores
        continue
    keys = line.strip().split("#")

    Firsts = keys[1].strip().split(" ")
    Seconds = keys[2].strip().split(" ")

    FirstLen = len(Firsts)
    SecondLen = len(Seconds)

    if FirstLen > 1 and SecondLen > 1:
        continue
    if FirstLen == 1 and SecondLen == 1:
        continue

    Prefixs = keys[0].strip().split("|")

    # Modify First Operand
    if FirstLen == 1:
        # TODO: so far we ignore eq and ne
        if Prefixs[1] == "eq" or Prefixs[1] == "ne":
            continue
        SecondSum = 0
        for i in range(SecondLen):
            Cur = int(Seconds[i])

            if i == 0:
                SecondMin = Cur
                SecondMax = Cur
            else:
                SecondMin = min(SecondMin, Cur)
                SecondMax = max(SecondMax, Cur)

            SecondSum = SecondSum + Cur

        #SecondAve = (SecondMin+SecondMax)/2
        SecondAve = SecondSum/SecondLen

        if Prefixs[1] == "slt" or Prefixs[1] == "sge" or Prefixs[1] == "ult" or Prefixs[1] == "uge":
            #if SecondMax-SecondMin > 1:
            #    target_ave = SecondAve
            #else:
            #    target_ave = SecondMax-1

            target_min = SecondMin-1
            target_max = SecondMax

        elif Prefixs[1] == "sgt" or Prefixs[1] == "sle" or Prefixs[1] == "ugt" or Prefixs[1] == "ule":
            #if SecondMax-SecondMin > 1:
            #    target_ave = SecondAve
            #else:
            #    target_ave = SecondMax

            target_min = SecondMin
            target_max = SecondMax+1

        Cur = int(Firsts[0])
        # always return min and max, and let KLEE to calculate the target value
        final_target_0 = target_min
        final_target_1 = target_max

        if Cur <= target_min:
            OpID = 0
            #final_target_0 = target_ave
            #final_target_1 = target_max
        elif Cur >= target_max:
            OpID = 1
            #final_target_0 = target_min
            #final_target_1 = target_ave
        else:
            OpID = 2
            #final_target_0 = target_min
            #final_target_1 = target_max


        # 0 in |0# means we are changing left operand
        print Prefixs[0] + "|0#" + str(final_target_0) + "#" + str(final_target_1) + "#" + str(OpID)

    # Modify Second Operand
    if SecondLen == 1:
        FirstSum = 0
        # TODO: so far we ignore eq and ne
        if Prefixs[1] == "eq" or Prefixs[1] == "ne":
            continue
        for i in range(FirstLen):
            Cur = int(Firsts[i])

            if i == 0:
                FirstMin = Cur
                FirstMax = Cur
            else:
                FirstMin = min(FirstMin, Cur)
                FirstMax = max(FirstMax, Cur)

            FirstSum = FirstSum + Cur

        #FirstAve = (FirstMin+FirstMax)/2
        FirstAve = FirstSum/FirstLen

        if Prefixs[1] == "slt" or Prefixs[1] == "sge" or Prefixs[1] == "ult" or Prefixs[1] == "uge":
            #if FirstMax-FirstMin > 1:
            #    target_ave = FirstAve
            #else:
            #    target_ave = FirstMax

            target_min = FirstMin
            target_max = FirstMax+1

        elif Prefixs[1] == "sgt" or Prefixs[1] == "sle" or Prefixs[1] == "ugt" or Prefixs[1] == "ule":
            #if FirstMax-FirstMin > 1:
            #    target_ave = FirstAve
            #else:
            #    target_ave = FirstMax-1

            target_min = FirstMin-1
            target_max = FirstMax

        Cur = int(Seconds[0])
        # always return min and max, and let KLEE to calculate the target value
        final_target_0 = target_min
        final_target_1 = target_max
        if Cur <= target_min:
            OpID = 0
            #final_target_0 = target_ave
            #final_target_1 = target_max
        elif Cur >= target_max:
            OpID = 1
            #final_target_0 = target_min
            #final_target_1 = target_ave
        else:
            OpID = 2
            #final_target_0 = target_min
            #final_target_1 = target_max

        # change the right operand
        print Prefixs[0] + "|1#" + str(final_target_0) + "#" + str(final_target_1) + "#" + str(OpID)
