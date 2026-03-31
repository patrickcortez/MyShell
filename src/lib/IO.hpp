/*
*   This is MyShells IO handler, this replaces the standard
*   iostream, as MyShell will have its own dedicated screen buffer
*   this component is responsible for the input and output of MyShell
*/

#ifndef IO_HPP
#define IO_HPP

// essential libraries 
#include <windows.h>  //for windows API
#include <conio.h> //for _getch()
#include <cctype> //for isprint()
#include <string> //for string and string operations

namespace cortez{
  
    class IO{
        private:
            HANDLE* currbuff = nullptr;

            bool check(){ // a guard function to check if we have passed our screen buffer
                if(currbuff == nullptr){
                    return false;
                }

                return true;
            }

        public:

            IO(HANDLE* scrbuff) : currbuff(scrbuff){} //our constructor to initialize our screen buffer by passing its pointer

            void out(const std::string& msg){ // simple output handler
                DWORD cbuff; // we declare our buffer to use to write to console

                if(!check){ // a guard clause to make sure there is an actual screen buffer
                    return;
                }
 
                WriteConsoleA( //finally we write to terminal
                    *currbuff,
                    msg.c_str(),
                    msg.size(),
                    &cbuff,
                    NULL
                );
                
            }

            std::string in(){ //simple input handler, limitations: All input are strings -_-, templates will be used in the future
                std::string data = ""; //declare our character buffer for user input

                while(true){
                    char c = _getch(); //we use _getch() to get key events and store each key in a character var

                    //we evaluate the users input
                    if(c == '\r'){  //enter key
                        out("\n");
                        break;
                    }else if(c == '\b'){ //backspace key
                        if(!data.empty()){
                            data.pop_back();
                            out("\b \b");
                        }
                    }else if(c == 3){ // to prevent a forever loop, break when its sigint
                        break;
                    }else if(isprint(c)){ //letters,special characters and numbers
                        data += c;
                        std::string s(1,c);

                        out(s);
                    }
                }

                return data;
            }
    };

};

#endif //