@echo off
chcp 1251 > NUL

echo --строка параметров: %*
echo --параметр 1: %1
echo --параметр 2: %2
echo --параметр 3: %3
set /a res = %1 %3 %2
echo %res%

pause