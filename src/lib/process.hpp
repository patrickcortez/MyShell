/*
*   This is MyShell's Process Handler, basically where child processes
*   will be handled and created. This is a header file only implementation to be simple.
*/
#ifndef PROCESS_HPP
#define PROCESS_HPP

// essential libraries needed for process creation and handling
#include <windows.h> // for CreateProcessA
#include <iostream> // for cerr
#include <string> // for string and other string operations

namespace cortez{

    bool Execute_External(std::string exe_name){

        STARTUPINFOA sinf = {0}; //we init the start up info and process info for the process
        PROCESS_INFORMATION prinf = {0};

       bool success =  CreateProcessA( //we create start a process with windows CreateProcessA by passing the exe name after the './' delimiter
            NULL,
            exe_name.data(),
            NULL,
            NULL,
            false,
            0,
            NULL,
            NULL,
            &sinf,
            &prinf
        );
        
        //if the process fails to start we throw an error, else we wait.
        if(!success){
            return false; // we return false to signify it failed to create the process
        }

        WaitForSingleObject(prinf.hProcess,INFINITE);

        //Close our handles after the process is done
        CloseHandle(&prinf);
        CloseHandle(&sinf);

        return true; // we then return true after successful execution
    }
};

#endif