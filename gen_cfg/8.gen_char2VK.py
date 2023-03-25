import shutil, os
final_path = os.path.join ('9.char2vkKey.lua')

'''
Read all the Virtual Key codes from 2.lut1.txt and store them in a dictionary
'''
fr = open ('2.lut1.txt','r')
try:
    fw = open (final_path, 'w')
except:
    h=  input ('Could not find the path for out put file ../app/char2vkKey.lua')
    SystemExit
fw.write (' str2vk = {}')   
for line in fr:
    fw.write ( 'str2vk[ \'{}\' ] = {} \n' .format (line[0],line[4:-1]))


fr.close()
fw.close()

h= input ('completed , file written at ../app/char2vkKey.lua ')
