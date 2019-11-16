#------
# Based on
#------

#Address_Global.py

import sys
file1 = sys.argv[1]
file2 = sys.argv[2]

f_in = file(file1, "r")
f_out = file(file2, "w")

for line in f_in:
    line = line.strip()
    pos = line.find("//")
    if (pos != -1):
        line = line[:pos]

    if line.find(";") == -1:
        continue

    if line.find("=") == -1:
        pos0 =  line.find("__attribute__")
        if pos0 == -1:
            output = "extern " + line + "\n"
        else:
            output = "extern " + line[:pos0-1] + ";\n"
        f_out.write(output)
    else:
        pos0 =  line.find("__attribute__")
        pos = line.find("=")-1
        if pos0 == -1:
            target = line[:pos]
        else:
            if line[:pos0-1].find("Model") != -1:
                target = line[:pos0-1]
            else:
                pos1 = line[:pos].rfind(" ")
                print pos1
                target = line[:pos0-1] + line[pos1: pos]
                print target

        output = "extern " + target + ";\n"
        f_out.write(output)
f_in.close()
f_out.close()
