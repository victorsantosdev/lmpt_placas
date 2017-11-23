REM CommandInterpreter: $(COMSPEC)
@echo OFF
del .\bin\*.dll
del .\bin\*.tds
copy ..\bibliotecas\lib\*.dll .\bin\
copy ..\bibliotecas\lib\*.tds .\bin\
@echo ON
