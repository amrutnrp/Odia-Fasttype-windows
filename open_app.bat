echo off 

copy /s "%~dp0\lua535\lua53.dll" "%~dp0\app\bin\Debug"

copy /s "%~dp0\app\*.lua" "%~dp0\app\bin\Debug"


echo on


cd app\bin\Debug
@cmd 





