# Odia-Fasttype-windows
Keyboard Transliteration tool for Windows - for typing Odia exceptionally fast


This code is a  background process implementation for smooth typing interface.
One doesn't need to type only on a window to get odia character.
Any window supporting unicode encoding will display Odia characters upon typing.

The basic building block is complete.
But it's not perfect yet.


# Referece :- 


tries to implement core in c++ and mapping/other scripting in lua
lua helps change the behaviour of code on the fly
while making sure the core interaction is in c++ and doesn't need recompilation every time code is modified

also, errors can be fixed faster with lua rather than waiting for compile->build->run cycle in c++



before running, Add lua binaries and include files to /lua535 


it was developed in windows + codeblocks + mingw + lua5.3