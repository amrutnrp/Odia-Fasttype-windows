

fr = open ('lut4.txt','r')
fw = open ('keymap.cpp','w')

a= """

//key_press prev_char prev_length
//--shift?_input bksp?_output
//--new_length result
const int max_width = 14;
const int len_pos = max_width - 6 -1;


"""
fw.write(a)
for line in fr:
    fw.write(line)

    

fr.close()
fw.close()


import os


os.replace('keymap.cpp', '../key1/keymap.cpp')
