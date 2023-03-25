char2key = {}
'''
Read all the Virtual Key codes from 2.lut1.txt and store them in a dictionary
'''
fr = open ('2.lut1.txt','r')
for line in fr:
    char2key [line[0]] = int(line[4:-1])
fr.close()

max_char_length = 0

#======================
FR =  open('3.translation_config.txt','r', encoding="utf8")


for line in FR:

    l2 = line.split('//')
    l3 = l2[0]                              # check if any comments presnt, then throw the commetns away
    
    if len (l3.strip() ) == 0 :
        continue
    if l3.count ("'") + l3.count ("\"") != 4:
        print ('count of quotes not 4! ',line)
        continue
    l4 = l3.split("'")[1::2]                # Find the items under single quotes 
    entry  = l4[0]                          # take bakup of input expression
    out = l4[1]
    # print (out, end ='')
    max_char_length = max( max_char_length, len(out))

FR.close()

print ('max_char_length: ', max_char_length)

FW =  open('5.translation_config.lua','w', encoding="utf8")
FR =  open('3.translation_config.txt','r', encoding="utf8")
FW2 =  open('6.1.view_translation_config.txt','w', encoding="utf8")

FW.writelines ('max_char_length = '+ str(max_char_length) )
FW.write('\nkeymap_table = { \n')

def get_unicode_arr(s, size ):
    arr= ['0']*size
    for index,char in enumerate(s):
        if char == '?':
            arr [index] = '0'
        else:
            arr [index] = hex(ord( char))
    return ','.join(arr)

consonant_list = 'କଖଗଘଙଚଛଜଝଞଟଠଡଢଣଡ଼ଢ଼ତଥଦଧନପଫବଭମଯରଳଵସଶଷୱହୟଲ'
for line in FR:

    l2 = line.split('//')
    l3 = l2[0]                              # check if any comments presnt, then throw the commetns away

    if len (l3.strip() ) == 0 :
        continue
    
    if l3.count ("'") != 4:
        print ('count of quotes not 4! ',line)
        continue
    l4 = l3.split("'")[1::2]                # Find the items under single quotes 
    entry  = l4[0]                          # take bakup of input expression
    out = l4[1]

    consonant_needed_flag = 'false'
    if len(l4[0]) == 1 :
        bksp_flag = 0
        prev_ch = ''
        prev_length = 0

    else:
        bksp_flag = 1
        prev_ch = l4[0][:-1]
        prev_length = len(prev_ch)
        if prev_ch == '?':
            consonant_needed_flag = 'true'
            prev_ch = ''
            # prev_length = 0  can't do because it'll make it a sure shot !!
        
    kp = l4[0][-1]
    result = l4[1]
    shift_flag = 'true' if kp.isupper() else 'false'
    if len (prev_ch) == 0 :
        how_manny_bksp = 0
    else:
        how_manny_bksp = len(result) - len ( prev_ch )  + 1
    #print ( l4[0], result , len(result), len(prev_ch),how_manny_bksp )
    if prev_ch == '':
        prev_ch = '0'
    x=get_unicode_arr  (result,max_char_length) #test
    
    #is_prev_consonant = 1 if  prev_ch[-1] in consonant_list else 0
    is_new_consonant = 'true' if result[-1] in consonant_list else 'false'
    a= '{},{},{},{},{},{},{},{},{},{}\n' .format( 
                                     kp,
                                     prev_ch,
                                     prev_length ,
                                     consonant_needed_flag,
                                     shift_flag,
                                     how_manny_bksp,
                                     len (result),
                                     is_new_consonant,
                                     result,
                                     0
                                     )
    b= '{{{},\t{},{},{},\t\t{},{},{},{},\t\t{}, {}}},\n' .format( 
                                     hex(char2key[kp.upper()]),
                                     get_unicode_arr(prev_ch[-1], 1),
                                     prev_length ,
                                     consonant_needed_flag,
                                     shift_flag,
                                     how_manny_bksp,
                                     len (result),
                                     is_new_consonant,
                                     get_unicode_arr(result, max_char_length),
                                     0
                                     )

    FW.write(b)
    FW2.write(a)


FW.write('} \n')

FR.close()
FW.close()
FW2.close()
'''
1 current key press

2 previous character
3 previous character length
4 Is consonant needed for this?

5 Current character Capital needed
6 how many back spaces needed
7 currnet character length
8 current character is it consonant

9 current character of max length allocated max_char_length

10  0 

'''
    
input ('config generated successfully')