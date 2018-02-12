REM запуск программы без параметров
pr.exe
IF NOT ERRORLEVEL 1 GOTO err

REM запуск программы с одним параметром
pr.exe OneParameters
IF NOT ERRORLEVEL 1 GOTO err

pr.exe in2.txt out.txt 
IF ERRORLEVEL 1 GOTO err
FC /B out.txt out2.txt
IF ERRORLEVEL 1 GOTO err

pr.exe in3.txt out.txt 
IF ERRORLEVEL 1 GOTO err
FC /B out.txt out3.txt
IF ERRORLEVEL 1 GOTO err

pr.exe in4.txt out.txt 
IF ERRORLEVEL 1 GOTO err
FC /B out.txt out4.txt
IF ERRORLEVEL 1 GOTO err

pr.exe in5.txt out.txt 
IF ERRORLEVEL 1 GOTO err
FC /B out.txt out5.txt
IF ERRORLEVEL 1 GOTO err

pr.exe in6.txt out.txt 
IF ERRORLEVEL 1 GOTO err
FC /B out.txt out6.txt
IF ERRORLEVEL 1 GOTO err

pr.exe in7.txt out.txt 
IF ERRORLEVEL 1 GOTO err
FC /B out.txt out7.txt
IF ERRORLEVEL 1 GOTO err

pr.exe in8.txt out.txt 
IF ERRORLEVEL 1 GOTO err
FC /B out.txt out8.txt
IF ERRORLEVEL 1 GOTO err

pr.exe in9.txt out.txt 
IF ERRORLEVEL 1 GOTO err
FC /B out.txt out9.txt
IF ERRORLEVEL 1 GOTO err

pr.exe in10.txt out.txt 
IF ERRORLEVEL 1 GOTO err
FC /B out.txt out10.txt
IF ERRORLEVEL 1 GOTO err

pr.exe in11.txt out.txt 
IF ERRORLEVEL 1 GOTO err
FC /B out.txt out11.txt
IF ERRORLEVEL 1 GOTO err

pr.exe in12.txt out.txt 
IF ERRORLEVEL 1 GOTO err
FC /B out.txt out12.txt
IF ERRORLEVEL 1 GOTO err

pr.exe in13.txt out.txt 
IF ERRORLEVEL 1 GOTO err
FC /B out.txt out13.txt
IF ERRORLEVEL 1 GOTO err

pr.exe in14.txt out.txt 
IF ERRORLEVEL 1 GOTO err
FC /B out.txt out14.txt
IF ERRORLEVEL 1 GOTO err

pr.exe in15.txt out.txt 
IF ERRORLEVEL 1 GOTO err
FC /B out.txt out15.txt
IF ERRORLEVEL 1 GOTO err

pr.exe in16.txt out.txt 
IF ERRORLEVEL 1 GOTO err
FC /B out.txt out16.txt
IF ERRORLEVEL 1 GOTO err



ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT
