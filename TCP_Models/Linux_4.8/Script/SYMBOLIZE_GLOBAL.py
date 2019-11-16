#------
# Based on
#------

#Address_Global.py

#import sys
#file1 = sys.argv[1]

def SYMBOLIZE_GLOBAL(f_in, f_out, count):
    #f_in = file(file1, "r")
    #f_out = file(file2, "a")

    for line in f_in:
        line = line.strip()
        pos = line.find("//")
        if (pos != -1):
            line = line[:pos]

        if line.find(";") == -1:
            continue
        if line.find("=") == -1:
            keys = line.split()
            k_index = len(keys)
            if keys[k_index-1].find("__attribute__") != -1:
                target = keys[k_index-2]
            else:
                target = keys[k_index-1][:-1]
        else:
            keys = line.split()
            k_index = 0;
            for key in keys:
                if key == "=":
                    break;
                k_index = k_index+1
            if k_index == len(keys):
                print "Error: " + line
            if keys[k_index-1].find("__attribute__") != -1:
                target = keys[k_index-2]
            else:
                target = keys[k_index-1]

        if target[0] == "&" or target[0] == "*":
            target = target[1:]
        if target.find("Model") == -1:
            continue
        if target.find("[") != -1 or target.find(".") != -1:
            count = count+1
            #target = target[:pos0]+"["+str(i)+"]"
            line0 = "\ttypeof("+target+") symbol_a"+str(count)+";\n"
            line1 = "\tklee_make_symbolic(&symbol_a"+str(count)+", sizeof(symbol_a"+str(count)+"), \""+target+"\");\n"
            line2 = "\t"+target+"=symbol_a"+str(count)+";\n"
            f_out.write(line0)
            f_out.write(line1)
            f_out.write(line2)
        else:
            line0 = "\tklee_make_symbolic(&"+str(target)+", sizeof("+str(target)+"), \""+target+"\");\n"
            f_out.write(line0)

    #f_in.close()
    #f_out.close()
    return count
