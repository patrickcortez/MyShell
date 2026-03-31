/*
*   This is where all file-system and file operations are handled.
*   which will cover the basic file system operations.
*/
#ifndef OPERATIONS_HPP
#define OPERATIONS_HPP

// essential libraries
#include <string>
#include <filesystem>
#include <fstream>

using namespace std::filesystem;

namespace cortez{
    
    class Fops{
        private:
        path* currpath;

        public:

        Fops(path* current) : currpath(current){}


        bool navigateDir(const std::string Npath){ //handler to navigate directories

            if(!is_directory(*currpath / Npath)){ // guard clause incase it is exists but isnt a directory
                return false;
            }
            
            if(Npath == ".."){ //if the Npath entered is ".." we go back to the parent path
                *this->currpath = currpath->parent_path();
            }else{ //otherwise we traverse the Npath but we make sure that the path actually exists
                if(exists(*currpath / Npath)){
                   *this->currpath = *this->currpath / Npath;
                   current_path(*currpath);
                }else{
                    return false;
                }
            }

            return true;
        }

        

            
    };

};

#endif // !OPERATIONS_HPP
