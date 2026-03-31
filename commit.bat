@ECHO OFF

:: Git helper script 

git --version >nul 2>&1

if %ERRORLEVEL% EQU 0 (

    git add -A

    if %1 == "" (
        echo "Commit Message cannot be empty"
    ) else (
        git commit -m %1 
    )
) else (
    echo "Git not installed!"
)