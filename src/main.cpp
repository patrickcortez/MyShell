// The main shell of MyShell by Cortez
#include <iostream> //for input and output
#include <fstream> //for file operations
#include <string> //for string operations
#include <sstream> //to tokenize our input
#include <filesystem> //for file system operations
#include <csignal> //to handle signals
#include <cstdlib> 

using namespace std::filesystem;

void sighandler(int sig){ // we handle sigint by making a newline
    std::cout << "\n"; //TODO fix this so it enters returns to a new line, instead of an infinity loop of new lines.
}

path getHomeDir(){ // get the home dir of user, using cstdlib's getenv
    return getenv("USERPROFILE"); // TODO clean the extra '\' from the path, and the qoutes
}

void printHelp(){
    std::cout << "MyShell Commands: \n";
    std::cout << "=====================\n";
    std::cout << "  help : Displays the lists of commands available.\n";
    std::cout << "  say  : Output to terminal\n";
    std::cout << "  exit : Exit MyShell\n";
}

void printSay(std::string& msg){ // command for outputing to terminal
    std::cout << msg << std::endl;
}

void printError(const std::string& msg){
    std::cout << "\033[91m" << msg << std::endl;
}

// main function of the shell, we will put our final execution here.
int main(int argc,char *argv[]){
    std::signal(SIGINT,sighandler); //ignore sigint

    std::string input; // we declare our input variable to tokenize later
    bool done = false; // to signify, if we want to end the execution loop or not
    path curr = getHomeDir(); // init our current path, 

    while(done == false){ //execution loop

        std::cout << "MyShell:" << curr << "$ "; //print our prompt
        std::getline(std::cin,input); // get input from user
        std::cout << std::endl; // for proper output formatting

        std::stringstream ss(input); // tokenize the users input to pass in the evaluator later

        std::string cmd; // declare our command variable.

        ss >> cmd; //grab the first input of the user

        //input evaluator
        if(cmd == "help"){ // to print help for the user
            printHelp();
        }else if(cmd == "say"){ // basic command for tesing
            std::string msg; //we declare a msg variable to capture the users input when using say
            std::getline(ss,msg); //capture the entire message

            // print the users message
            printSay(msg);

        }else if(cmd == "exit"){ //exit shell only told so
            exit(0);
        }else{ // command does not exist we return an error, duhh... but we will put our command watcher here soon
            printError("MyShell: " + cmd + " command does not Exist");
        }

        std::cout << std::endl; // for proper formatting

    }


}