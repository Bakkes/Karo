@echo off

FOR /F "tokens=3 delims= " %%G in ('reg query "hklm\system\controlset001\control\nls\language" /v Installlanguage') DO (
IF [%%G] EQU [0413] (
	echo B|xcopy "..\Release\Engine.dll" "..\2DFrontend\bin\Release\Engine.dll" /y



	echo B|xcopy "..\Release\Engine.dll" "..\XNAFrontend\XNAFrontend\bin\x86\Release\Engine.dll" /y

) ELSE (
	echo F|xcopy "..\Release\Engine.dll" "..\2DFrontend\bin\Release\Engine.dll" /y



	echo F|xcopy "..\Release\Engine.dll" "..\XNAFrontend\XNAFrontend\bin\x86\Release\Engine.dll" /y

))