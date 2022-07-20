

char2key = {}


fr = open ('lut1.txt','r')
for line in fr:
##    a= line.split()
##    while (',' in a) : a.remove(',')
##    char2key [a[0]] = int(a[1])

    char2key [line[0]] = int(line[4:-1])

    

fr.close()



fr = open('or-fasttype.js','r', encoding="utf8")
#fr = open('lut2.txt','r')
fw =  open('lut3.txt','w', encoding="utf8")
fw2 =  open('lut4.txt','w', encoding="utf8")


def get_uni_arr(s,size):
    l= ['0']*size
    for index,char in enumerate(s):
        if char == '?':
            l [index] = '0'
        else:
            l [index] = hex(ord( char))

    print (l)

    return ','.join(l)
        
fw2.write('const int LUT[][14]= {\n')
fw.write('key_press prev_char prev_length\n--shift?_input bksp?_output\n--new_length result\n')

fw.write('{0,0,0,0,0,0,0,0,0},\n')
fw2.write('{0,0,0,0,0,0,0,0,0,0,0,0,0,0},\n')


valid_rows= 0 
for line in fr:
    if not ('[' in line and ']' in line) :
        continue
    l2 = line.split('//')
##    if len(l2) >1:
##        print (l2[1]) # skip this comments part

    l3 = l2[0]

    if l3.rstrip() == '':
        continue
    l4 = l3.split("'")[1::2]  # extract the two items
    entry  = l4[0]

    bksp_flag = 0
    

    loopflag = False
    
    if '('  in  entry or '\\' in entry:
        if '(' not in entry and entry .count ('\\') < 3:
            l4[0] = entry.replace('\\','')
        elif '(' in entry and '\\' not in entry:
            entry2 = entry.split("'")[1::2]
            continue
            
            
 
        else:
            continue

    
    
    if len(l4[0]) == 1 : #or l4[0][0] == l4[1][0]:  removed 2nd bcz the condition has to be present
        bksp_flag = 0
        prev_ch = '?'
        kp = l4[0][-1]
    else:
        bksp_flag = 1
        prev_ch = l4[0][:-1]  
        kp = l4[0][-1]
            
    result = l4[1] 
    shift_flag = 1 if kp.isupper() or kp in "\"}|{~?>_<" else 0
    new_length = len(result)

    if prev_ch == '?':
        prev_length = 0
    else:
        prev_length = len(prev_ch)

    in_flag = 0; out_flag = 0;
    if '#+' in line:
        out_flag = 1
    elif "#-" in line:
        in_flag = 1;

    s=('{:s}{:s},{:s},{:d},{:d},{:d},{:d},{:d},{:d},{:s}{:s},\n'.format('{',kp,prev_ch,prev_length,shift_flag,bksp_flag,in_flag, out_flag, new_length,result,'}'))
    s2=('{:s}{:s},{:s},{:d},{:d},{:d},{:d},{:d},{:d},{:s}{:s},\n'.format('{',hex(char2key[kp.upper()]),get_uni_arr(prev_ch[-1],1),prev_length,shift_flag,bksp_flag,in_flag, out_flag,new_length,get_uni_arr(result,6),'}'))

    fw.write(s)
    fw2.write(s2)
    valid_rows = valid_rows +1
##    print (line)
##    print (s)

    

fw.write('{0,0,0,0,0,0,0,0,0}\n')
fw2.write('{0,0,0,0,0,0,0,0,0,0,0,0,0,0}\n};')


fw2.write('\n\nconst int max_length = {:d};'.format(valid_rows+2))

        
        

##fw.write('\n\n\n\n{:d}\n\n'.format(valid_rows))
    

fw.close()
fw2.close()
fr.close()
