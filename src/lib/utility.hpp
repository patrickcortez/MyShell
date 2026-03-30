/*
*   This is the utility of MyShell, where string operations and other important functions will be made.
*   And will be used all through out the shell.
*/
#ifndef UTILITY_HPP
#define UTILITY_HPP

// essential libraries
#include <string> //for string and string operations
#include <algorithm>

namespace cortez{

    std::string Trim(const std::string& delim,std::string input){ // this function is to get the string after the delimiter

       input.erase( std::remove_if(input.begin(),input.end(),[&](char c){ //we remove the delimiter using the remove_if() function rather than making a complex one using forloops -_-
            return delim.find(c) != std::string::npos; //we use a lambda function to determine the position of the delimiter in the string
        }),input.end());

        return input; // we return input, so i can use them in arguments
              
    }

    void Ult_Trim(const std::string& delim,std::string& input){ // instead of a returning a string literal, 
        //we modify the string variable directly using passby reference

       input.erase( std::remove_if(input.begin(),input.end(),[&](char c){ //we remove the delimiter using the remove_if() function rather than making a complex one using forloops -_-
            return delim.find(c) != std::string::npos; //we use a lambda function to determine the position of the delimiter in the string
        }),input.end());
              
    }

    bool contains(const std::string& delim,std::string& input){ // this functions only purpose is to find a certain delimiter in a string
        return input.find(delim) != std::string::npos; // by using strings find method and comparing it to string no position using with the not equal operator
    }

    std::string replace_all(std::string input, const std::string& target, const std::string& New) { // We pass the users input to a string param, while the target and new string are constant pass by references so we can use string literals as arguments
    size_t pos = 0;
    while ((pos = input.find(target, pos)) != std::string::npos) { // we find how many instances of our target in the input string
        input.replace(pos, target.length(), New); //then replace them with our new string
        pos += New.length();
    }
    // return once the whole operation is done
    return input;
    }

};

#endif