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
    keys = line.split("#")
    Prefix = keys[0]

    if Prefix not in Op1:
        Op1[Prefix] = set()
        Op2[Prefix] = set()

    values = keys[1].strip().split()
    for value in values:
        Op1[Prefix].add(value)

    values = keys[2].strip().split()
    for value in values:
        Op2[Prefix].add(value)

for key in Op1:
    if len(Op1[key]) > 1000 or len(Op2[key]) > 1000:
        continue
    if len(Op1[key]) > 1 and len(Op2[key]) > 1:
        continue
    print key + "#",
    #print Output[key]
    for key2 in Op1[key]:
        print key2,
    print "#",
    for key2 in Op2[key]:
        print key2,
    print
