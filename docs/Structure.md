# Structure

The *src* folder only has 1 file for now:

 - **main.cpp** : this contains the source code of the shell, more components will be added soon.
    
Inside **main.cpp** we used 7 different libraries for our shell:

 - *iostream* : for our shells input and output

 - *sstream* : for tokenizing the input of the user

 - *string* : for string operations

 - *csignals* : for capturing different signal interrupts

 - *cstdlib* : for the **getenv()** function to capture the 'USERPROFILE' environmental variable

 - *fstream* : for future file operations

 - *filesystem* : to navigate the users file system.

Inside **main.cpp** the shell is using a basic while loop for its exection and a
basic if-else evaluator. This might be changed in the future, but we'll see.