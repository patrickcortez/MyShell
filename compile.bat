@ECHO OFF

gcc --version >nul 2>&1

if %ERRORLEVEL% EQU 0 (

    echo "Compiling MyShell..."

    g++ src/main.cpp -o bin/MyShell.exe >nul 2>&1

    echo "MyShell Successfully compiled!"
) else (
    echo "GCC not installed!"
)