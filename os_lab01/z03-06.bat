@echo off
echo -- List of arameters: %1 %2
echo -- Mode: %1
echo -- File name: %2

if "%1" EQU "" goto help
if /I "%1" EQU "create" goto create
if /I "%1" EQU "delete" goto delete
if "%1" NEQ "delete" goto error
if "%1" NEQ "create" goto error

:help
	echo -- * SYNTAX: %0 mode file
	echo -- * mode = {create, delete}
	echo -- * file = [filename]
	goto exit

:error
	echo -- * ERROR: invalid mode
	goto exit

:create
	if "%2" NEQ "" goto checkFileToCreate
	echo -- * ERROR: empty filename
	goto exit

:delete
	if "%2" NEQ "" goto checkFileToDelete
	echo -- * ERROR: empty filename
	goto exit

:checkFileToCreate
	if exist %2 (goto fileAlredyExists)
	copy NUL %2
	echo -- * File %2 was created
	goto exit

:checkFileToDelete
	if not exist %2 (goto fileNotFound)
	del %2
	echo -- File %2 was deleted
	goto exit

:fileAlredyExists
	echo -- * ERROR: File %2 already exists
	goto exit

:fileNotFound
	echo -- * ERROR: File %2 is not found
	goto exit

:exit