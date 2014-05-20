@echo off

FOR /F "tokens=3 delims= " %%G in ('reg query "hklm\system\controlset001\control\nls\language" /v Installlanguage') DO (
IF [%%G] EQU [0413] (
	echo B|xcopy "..\Debug\Engine.dll" "..\2DFrontend\bin\Debug\Engine.dll" /y



	echo B|xcopy "..\Debug\Engine.dll" "..\XNAFrontend\XNAFrontend\bin\x86\Debug\Engine.dll" /y

) ELSE (
	echo F|xcopy "..\Debug\Engine.dll" "..\2DFrontend\bin\Debug\Engine.dll" /y



	echo F|xcopy "..\Debug\Engine.dll" "..\XNAFrontend\XNAFrontend\bin\x86\Debug\Engine.dll" /y

))