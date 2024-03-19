@echo off
:loop
data.exe > duipai.in
std.exe < duipai.in > std.out 
fuck.exe < duipai.in > fuck.out
fc /A std.out fuck.out
if %errorlevel%==0 goto loop
echo WA
pause