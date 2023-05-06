@echo off

.\processor\encoder\output\main.exe inputData.txt encodedData.txt
pause
.\processor\channeler\output\main.exe encodedData.txt transmittedData.txt
pause
.\processor\decoder\output\main.exe transmittedData.txt outputData.txt
pause