@echo off
for /f "usebackq tokens=*" %%x in (`cmd /c dir /b tej2o1-01_m-elliot_*`) do rmdir %%x\src & mklink /d %%x\src %~dp0util