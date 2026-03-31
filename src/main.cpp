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

/*
*   This Project is under GNU General Public License V3, Check LICENSE for more details.
*   Feel free to modify and distribute. =P
*/

//My Libraries
#include "lib/process.hpp"
#include "lib/utility.hpp"
#include "lib/operations.hpp"

using namespace std::filesystem; //so i dont have to type std::filesystem:: -_-

volatile int interrupted = 0;

void sighandler(int sig){ // we handle sigint by making a newline
    interrupted  = 1;
}

path getHomeDir(){ // get the home dir of user, using cstdlib's getenv
    return getenv("USERPROFILE");
}

void clearscreen(){ // ANSI clearscreen
    std::cout << "\033[2J\033[H";
}

void printHelp(){ //for user convenience
    std::cout << "MyShell Commands: \n";
    std::cout << "=====================\n";
    std::cout << "  help    : Displays the lists of commands available.\n";
    std::cout << "  say     : Output to terminal\n";
    std::cout << "  reloc   : Change directories\n";
    std::cout << "  wipe    : Clearscreen\n";
    std::cout << "  exit    : Exit MyShell\n";
}

void printSay(std::string& msg){ // command for outputing to terminal
    std::cout << msg << std::endl;
}

void printError(const std::string& msg){
    std::cout << "\033[91m" << msg << std::endl;
}

void execute_exe(std::string name,path& tmp){ //function responsible for executing external executables

    //we put 3 guard clauses one to check if it exists, if its an executable and the other one if its a directory

    //before executing we check if the exe file does indeed exist, if not
    if(!exists(tmp / name)){ //we throw an error
        std::cerr << "\033[91m\n" << "MyShell: " << name << " file not found!\n";
        return;
    }
    
    if(is_directory(tmp / name)){ //if it is a directory we also throw an error
        std::cerr << "\033[91m\n" << "MyShell: " << name << " is a directory!\n";
        return;
    }

    path newpath = tmp / name; //we declare our temporary path variable for the 3rd guard clause

    if (newpath.extension() != ".exe"){
        printError("MyShell: " + newpath.string() + " is not an executable\n");
        return;
    }
    //execute after the exe passes the guard clause
    if (!cortez::Execute_External(cortez::Trim("./",name))){ //if it failed to run then we throw an error
        std::cerr << "\033[91m\n" << "MyShell: " << name << " failed to start!\n";
        return;
    }
}

// main function of the shell, we will put our final execution here.
int main(int argc,char *argv[]){

    //TODO, probably put the initialization of Screen buffer and screen info here, before the main loop

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

        std::cout << "\n\e[0;33mMyShell:\e[0;36m" << cleancurr << "$ "; //print our prompt
        std::getline(std::cin,input); // get input from user

        std::stringstream ss(input); // tokenize the users input to pass in the evaluator later

        std::string cmd; // declare our command variable.

        ss >> cmd; //grab the first input of the user

        if(interrupted >= 1){
            std::cout << "\n";
            interrupted = 0;
        }

        //input evaluator
        if(cmd == "help"){ // to print help for the user
            printHelp();
        }else if(cmd == "say"){ // basic command for tesing
            std::string msg; //we declare a msg variable to capture the users input when using say
            std::getline(ss,msg); //capture the entire message

            // print the users message
            printSay(msg); //TODO replace cout with my own I/O layer

        }else if(cmd == "exit"){ //exit shell only told so
            exit(0);
        }else if(cortez::contains("./",cmd)){ //to execute external executables found in the filesystem
            execute_exe(cmd,curr);
        }else if(cmd == "reloc"){ //change directory
            std::string args; //declare the args variable we'll store the users intended directory to navigate to
            std::getline(ss,args); //capture the entire input and trim the quotes

            std::cout << "args: " << args << "\n"; //debug args variable,
           
            if(!fhandler.navigateDir(cortez::Trim(" ",args))){  //call the method to navigate directory but we make sure that the directory actually exists
                
                //if the nav fails, then we throw in an error, BUT what?

                if(!exists(curr / args)){ // A! It doesnt exist =0
                    printError("MyShell" + args + " Directory doesnt exist!");
                }

                if(!is_directory(curr / args) &&  exists(curr / args)){ // OR B! IT DOES! but its not a directory.... You silly goose =D
                    printError("MyShell" + args + " is not a directory!");
                }
            }

        }else if(cmd == "wipe"){ //clearscreen for convinience
            clearscreen(); //TODO, make its own screen buffer, and enable VT
        }else if(cmd == "pwd"){ //output the present working directory to terminal
            std::string ncur = cortez::Trim(c_str,current_path().string()); // we trim qoutes from the ncur string variable
            cortez::replace_all(ncur,"\\\\","\\"); //then trim the double qoutes into one qoute by replacing them using our helper
            std::cout << ncur << "\n";
        }else{ // command does not exist we return an error, duhh... but we will put our command watcher here soon
            printError("MyShell: " + cmd + " command does not Exist"); //TODO, Make the cmds folder watcher, which should be relatively easy
        }

    }

}