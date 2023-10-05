@echo off
chcp 1251 > NUL

echo --строка параметров: %*
echo --параметр 1: %1
echo --параметр 2: %2
echo --параметр 3: %3

set p1=%1
set p2=%2
set p3=%3

set /a sum=p1+p2
set /a mult=p1*p2
set /a div=p3/p1
set /a dif=p3-p1
set /a expression = (p3-p1)*(p1-p2)

echo %p1%+%p2% = %sum%
echo %p1%*%p2% = %mult%
echo %p3%/%p1% = %div%
echo %p3%-%p1% = %dif%
echo (%p3%-%p1%)*(%p1%-%p2%) = %expression% 

pause