// The main shell of MyShell by Cortez
#include <iostream> //for input and output
#include <fstream> //for file operations
#include <string> //for string operations
#include <sstream> //to tokenize our input
#include <filesystem> //for file system operations
#include <csignal> //to handle signals
#include <algorithm> //for algorithms
#include <cstdlib>  //for getenv()
#include <direct.h> //for _chdir()
#include <windows.h> //for windows api

/*
*   This Project is under GNU General Public License V3, Check LICENSE for more details.
*   Feel free to modify and distribute. =P
*/

//My Libraries
#include "lib/process.hpp" 
#include "lib/utility.hpp"
#include "lib/operations.hpp"
#include "lib/IO.hpp"

using namespace std::filesystem; //so i dont have to type std::filesystem:: -_-

volatile int interrupted = 0;

void sighandler(int sig){ // we handle sigint by making a newline
    interrupted  = 1;
}

path getHomeDir(){ // get the home dir of user, using cstdlib's getenv
    return getenv("USERPROFILE");
}

void clearscreen(cortez::IO& curio){ // ANSI clearscreen
    curio.out("\033[2J\033[H");
}

void printHelp(cortez::IO& curio){ //for user convenience
    curio.out("MyShell Commands: \n");
    curio.out("=====================\n");
    curio.out("  help    : Displays the lists of commands available.\n");
    curio.out("  say     : Output to terminal\n");
    curio.out("  reloc   : Change directories\n");
    curio.out("  wipe    : Clearscreen\n");
    curio.out("  exit    : Exit MyShell\n");
}

void printSay(std::string& msg,cortez::IO& curio){ // command for outputing to terminal
    curio.out(msg);
}

void printError(const std::string& msg,cortez::IO& curio){
    curio.out("\033[91m" + msg + "\n");
}

void execute_exe(std::string name,path& tmp,cortez::IO& curio){ //function responsible for executing external executables

    //we put 3 guard clauses one to check if it exists, if its an executable and the other one if its a directory

    //before executing we check if the exe file does indeed exist, if not
    if(!exists(tmp / name)){ //we throw an error
         printError("\033[91m\nMyShell: " + name + " file not found!\n",curio);
        return;
    }
    
    if(is_directory(tmp / name)){ //if it is a directory we also throw an error
         printError("\033[91m\n MyShell: " + name + " is a directory!\n",curio);
        return;
    }

    path newpath = tmp / name; //we declare our temporary path variable for the 3rd guard clause

    if (newpath.extension() != ".exe"){
        printError("MyShell: " + newpath.string() + " is not an executable\n",curio);
        return;
    }
    //execute after the exe passes the guard clause
    if (!cortez::Execute_External(cortez::Trim("./",name))){ //if it failed to run then we throw an error
        printError("\033[91m\nMyShell: " + name + " failed to start!\n",curio);
        return;
    }
}

// main function of the shell, we will put our final execution here.
int main(int argc,char *argv[]){

    //We first initiate our screen buffer

    HANDLE original = GetStdHandle(STD_OUTPUT_HANDLE); //we save the original consoles screen buffer

    HANDLE nbuf = CreateConsoleScreenBuffer( // we create our own screen buffer.
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        CONSOLE_TEXTMODE_BUFFER,
        NULL
    );

    if(nbuf == INVALID_HANDLE_VALUE){ // if our screen buffer cant be made we throw in a warning and return
        std::cerr << "MyShell: Unable to Create Screenbuffer!\n";
        return 1;
    }

    SetConsoleActiveScreenBuffer(nbuf); 

        //also we grab the screen info
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(nbuf,&csbi);

    //lock the console so it doesnt overwrite
    csbi.dwSize.X = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    csbi.dwSize.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    SetConsoleScreenBufferSize(nbuf,csbi.dwSize); //set the new console size to lock it =D

    //we enable virtual term proc to parse advanced ansi commandsss
    DWORD cmode; //declare our consolemode buffer
    GetConsoleMode(nbuf,&cmode);
    cmode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING; //we turn it on
    SetConsoleMode(nbuf,cmode); //and set it

    

    COORD spos = {0,0};
    SetConsoleCursorPosition(nbuf,spos);

    // end of screen buffer initialization

    cortez::IO iohandle(&nbuf); //we initialize our io handler

    std::signal(SIGINT,sighandler); // ignore sigint

    std::string input; // we declare our input variable to tokenize later
    bool done = false; // to signify, if we want to end the execution loop or not
    path curr = getHomeDir(); // init our current path, 
    cortez::Fops fhandler(&curr); //initialize our FileSystem handler
    current_path(curr); //always set starting dir at users home dir

    while(done == false){ //execution loop

        std::string cleancurr = curr.string();

        char c_str[1] = {'"'};
        cortez::Ult_Trim(c_str,cleancurr); //we trim the quotes
        cortez::replace_all(cleancurr,"\\\\","\\"); //then replace the \\ with '\'

        iohandle.out("\n\e[0;33mMyShell:\e[0;36m" + cleancurr + "$ "); //print our prompt
        input = iohandle.in(); // get input from user

        std::stringstream ss(input); // tokenize the users input to pass in the evaluator later

        std::string cmd; // declare our command variable.

        ss >> cmd; //grab the first input of the user

        if(interrupted >= 1){
            iohandle.out("\n\n");
            interrupted = 0;
        }

        //input evaluator
        if(cmd == "help"){ // to print help for the user
            printHelp(iohandle);
        }else if(cmd == "say"){ // basic command for tesing
            std::string msg; //we declare a msg variable to capture the users input when using say
            std::getline(ss,msg); //capture the entire message
            msg.erase(msg.begin()); //we erase the first character since its always ' '

            // print the users message
            printSay(msg,iohandle);

        }else if(cmd == "exit"){ //exit shell only told so
            exit(0);
        }else if(cortez::contains("./",cmd)){ //to execute external executables found in the filesystem
            execute_exe(cmd,curr,iohandle);
        }else if(cmd == "reloc"){ //change directory
            std::string args; //declare the args variable we'll store the users intended directory to navigate to
            std::getline(ss,args); //capture the entire input and trim the quotes

             iohandle.out("args: " + args + "\n"); //debug args variable,
           
            if(!fhandler.navigateDir(cortez::Trim(" ",args))){  //call the method to navigate directory but we make sure that the directory actually exists
                
                //if the nav fails, then we throw in an error, BUT what?

                if(!exists(curr / args)){ // A! It doesnt exist =0
                    printError("MyShell" + args + " Directory doesnt exist!",iohandle);
                }

                if(!is_directory(curr / args) &&  exists(curr / args)){ // OR B! IT DOES! but its not a directory.... You silly goose =D
                    printError("MyShell" + args + " is not a directory!",iohandle);
                }
            }

        }else if(cmd == "wipe"){ //clearscreen for convinience
            clearscreen(iohandle);
        }else if(cmd == "pwd"){ //output the present working directory to terminal
            std::string ncur = cortez::Trim(c_str,current_path().string()); // we trim qoutes from the ncur string variable
            cortez::replace_all(ncur,"\\\\","\\"); //then trim the double qoutes into one qoute by replacing them using our helper
            iohandle.out( ncur + "\n");
        }else if(cmd.empty()){ //we finally ignore sigint
            continue;
        }else{ // command does not exist we return an error, duhh... but we will put our command watcher here soon
            printError("MyShell: " + cmd + " command does not Exist",iohandle); //TODO, Make the cmds folder watcher, which should be relatively easy
        }

    }

    //after execution loop we set tback the original screen buffer and close our screen buffer
    SetConsoleActiveScreenBuffer(original);
    CloseHandle(nbuf);

}