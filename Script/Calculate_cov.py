import sys
file0 = "Edge_set.log"
file1 = sys.argv[1]
file2 = "Edge_set_bak.log"

f0 = file(file0, "r")
f = file(file1, "r")
f2 = file(file2, "w")

tot = 0
succ = 0

Edge_dict = {}
for line in f0:
    line = line.strip()
    keys = line.split(",")
    Edge_dict[(keys[0], keys[1])] = int(keys[2])

for line in f:
    if line.find(" -> ") != -1:
        p0 = line.find(":")
        value = int(line[p0+2:])
        line = line[:p0]
        keys = line.split(" -> ")
        if (keys[0], keys[1]) not in Edge_dict:
            Edge_dict[(keys[0], keys[1])] = value
        elif Edge_dict[(keys[0], keys[1])] == 0 and value > 0:
            Edge_dict[(keys[0], keys[1])] = value
            print "New added, ",
            print (keys[0], keys[1]),
            print " value: ",
            print value
        ''' #Previously covered but uncover this time
        elif value == 0 and Edge_dict[(keys[0], keys[1])] > 0:
            print "Uncovered, ",
            print (keys[0], keys[1]),
            print " value: ",
            print value
        '''

for keys, value in Edge_dict.items():
    if value != 0:
        succ = succ+1
    tot = tot+1
    f2.write(str(keys[0])+','+str(keys[1])+','+str(value)+'\n')

print "Succ:",
print succ,
print " Tot:",
print tot,
print " Coverage: ",
print succ*100.0/tot
