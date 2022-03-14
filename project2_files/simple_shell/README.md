Name: Amy Phan
ID: CM82779
Class: CMSC421 OS - SPRING 2022 Section 4
Date: 3/14/2022

GITHUB: mphan1@umbc.edu

------------------------------

Project:
I created a simple shell in c. When executed, the shell will ask the user for a command and execute that command with execvp().
When finished with the command, it will ask the user for a command again until they enter exit. The user is able to enter in
any length for the command as it parses through.This shell has a built in function for both exit and proc as it is also supports
proc commands.

------------------------------


citations:
Writing/read proc
	https://stackoverflow.com/questions/63214325/proper-way-of-writing-to-sys-or-proc-filesystem-in-c
	https://linux.die.net/lkmpg/x769.html

Part 1 - Template:
	https://github.com/brenns10/lsh/blob/407938170e8b40d231781576e05282a41634848c/src/main.c
	https://github.com/rehassachdeva/C-Shell/blob/master/basic_setup.c
	https://github.com/AlphaArslan/C-Simple-Linux-Shell-Wrapper/blob/master/code/shell.c
	https://github.com/rehassachdeva/C-Shell
	https://www.youtube.com/watch?v=hMU3IL48Z_w

Parsing:
	https://www.youtube.com/watch?v=O5s-jYoR6c4
	https://stackoverflow.com/questions/9659697/parse-string-into-array-based-on-spaces-or-double-quotes-strings

exevp()
	https://www.journaldev.com/40793/execvp-function-c-plus-plus

Reading string of unknown length:
	https://stackoverflow.com/questions/5375604/reading-in-a-string-of-unknown-length-from-the-console
	https://codereview.stackexchange.com/questions/31095/reading-unlimited-input-strings-in-c

Info about EOF:
	https://stackoverflow.com/questions/1782080/what-is-eof-in-the-c-programming-language


Print to stderr:
	https://stackoverflow.com/questions/39002052/how-i-can-print-to-stderr-in-c

