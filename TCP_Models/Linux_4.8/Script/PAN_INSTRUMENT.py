'''
Used to instrument function Instrument_Summary() in pan.c: r_ck function
So model checking can help print the path summary information
'''
import sys
import tempfile

t = tempfile.NamedTemporaryFile(mode="r+")

targetname = sys.argv[1] #"pan.c"
i = open(targetname, "r")

for line in i:
    t.write(line)
i.close()

t.seek(0)
o = open(targetname, "w")

flag = False
for line in t:
    o.write(line)
    if flag:
        o.write("\tInstrument_Summary();\n")
        flag = False
    if line.find("r_ck(uchar ") != -1:
        flag = True

t.close()
o.close()
