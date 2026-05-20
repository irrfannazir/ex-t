echo This is command to compile or install the compiler.
@REM xargs npm install < packages.txt
gcc main.c src/* lex/lex.c lex/src/* alt-parse/parse.c alt-parse/src/* alt-compile/compile.c alt-compile/src/* ^
    -I lex -I alt-parse -I alt-compile -I lex/include -I alt-parse/include -I alt-compile/include -I include   ^
    -o ex-c
@REM gcc -g -Wunused-function -Wall -Wextra main.c src/* lex/lex.c lex/src/* alt-parse/parse.c alt-parse/src/* alt-compile/compile.c alt-compile/src/* ^
@REM     -I lex -I alt-parse -I alt-compile -I lex/include -I alt-parse/include -I alt-compile/include -I include ^
@REM     -o ex-c
@REM .\ex-c main.ex