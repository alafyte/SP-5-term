@echo off
chcp 1251 > NUL

for %%A in ("%~dpnx0") do (
  set "FilePath=%%~fA"
  set "FileName=%%~nA"
)

for /f "tokens=1-2" %%B in ('dir /tc "%FilePath%" ^| find "%FileName%"') do (
  set "FileCreateDateDate=%%B"
  set "FileCreateTime=%%C"
)

echo --имя этого bat-файла:     %FileName%
echo --этот bat-файл создан:  %FileCreateDateDate%, %FileCreateTime%
echo --путь bat-файла:     %FilePath%

pause