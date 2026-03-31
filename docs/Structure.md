# Structure

The *src* folder has:

    - **main.cpp** : this contains the source code of the shell, more components will be added soon.

    - **/lib** : this folder contains all header files the shell will be using.
    
Inside **main.cpp** we used 9 different libraries for our shell:

    - *iostream* : for our shells input and output

    - *sstream* : for tokenizing the input of the user

    - *string* : for string operations

    - *csignals* : for capturing different signal interrupts

    - *cstdlib* : for the **getenv()** function to capture the 'USERPROFILE' environmental variable

    - *fstream* : for future file operations

    - *filesystem* : to navigate the users file system.

Custom Headers:

    - *process.hpp* : for process handling and creation

    - *utility.hpp* : for specialized helpers

    - *operations.hpp* : for all filesystem and file operations

    - *IO.hpp* : **MyShells** I/O handler.

Inside **main.cpp** the shell is using a basic while loop for its exection and a
basic if-else evaluator. This might be changed in the future, but we'll see.
