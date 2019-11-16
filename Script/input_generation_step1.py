'''
Prefix = BBOffset|Predicate|
Collect all instrumented cmp lines and merge their result
'''
import sys

f_in = sys.argv[1]
file0 = file(f_in, "r") # input
#file1 = file("input1.txt", "r")

Target = set()
Op1 = {}
Op2 = {}
#for line in file1:
#    Target.add(line.strip())

for line in file0:
    line = line.strip()
    p0 = line.find("CMP")
    if p0 == -1:
        continue
    Prefix = line[:p0-1]

    p1 = line.find("with")
    Value_L = line[p0+4:p1-1]
    Value_R = line[p1+5:]
    if Prefix not in Op1:
        Op1[Prefix] = set()
        Op2[Prefix] = set()

    Op1[Prefix].add(Value_L)
    Op2[Prefix].add(Value_R)
    #print Value

for key in Op1:
    #if len(Op1[key]) > 1 and len(Op2[key]) > 1:
    #    continue
    print key + " #",
    #print Output[key]
    for key2 in Op1[key]:
        print key2,
    print "#",
    for key2 in Op2[key]:
        print key2,
    print
