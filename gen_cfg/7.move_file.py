

import shutil, os

from os.path import dirname as up_f
cwd = os.getcwd()

up1 = up_f (cwd)


final_path = os.path.join (up1, 'app', 'keymap.lua')
shutil.copy('5.translation_config.lua', final_path)

h= input ('File moved to ../app/keymap.lua!\n\nPress enter to continue.. ')
