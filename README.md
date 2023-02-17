# my zsh qwasar

### Task Description

Your interpreter will display a prompt: $> (for example)

You will have to wait for a command line to be written (ending by a newline character (enter))

You will have to parse the command line and format it in order to execute it.

The prompt must be displayed again only after the command execution.

For the execution you must use execve.

Only basic command lines are expected to be executed; no pipes, redirections or any other advanced features. The executables should be those found in the path, as indicated in the PATH variable.

If the executable cannot be found, you must display an error message and display the prompt again. Errors must be dealt with and must display the appropriate message on the error output. You must correctly handle the PATH and the environment (by copying and restoring the initial env).

You must implement the following builtins: 
* Echo
* cd
* setenv
* unsetenv
* env
* exit
* pwd
* which

------------------------------------------------------------------------------------------------------------------------------
### Program Usage

#### 1. Type "make" to compile the program.

  ```sh
   make
  ```
#### 2. You can then run the program with "./my_zsh" to run the shell and a prompt ">" will appear then user can use following built-ins: 
   ```sh
    * exit
    
         'exit' will exit ./my_zsh
   ```
   ```sh
    * echo:
    
         'echo $[VARNAME]' will return the value of environment variables if they exist (case sensitive)
         'echo "anything"' will return the strings entered without quotations.
   ```
   ```sh
    * cd
    
         'cd ..' will move back in the path
         'cd /' will move to /
         'cd -' will move back to original file position
         'cd [dirname]' will move to directory if it exists
   ```
   ```sh
    * pwd
    
         'pwd' will print the path of the current working directory
   ```
   ```sh
    * env
    
         'env' will output the environment to terminal
   ```
   ```sh
    * setenv
    
         'setenv $[VARNAME] [VALUE]' will set an environment variable and value. 
         Variable names must be uppercase and Variable and value must be separated by a single space.
   ```
   ```sh
    * unsetenv
    
         'unsetenv $[VARNAME]' will remove environment variable if it is found in environment
   ```
   ```sh
    * which 
    
         'which' will identify the location of binary executables, 
         for built-in functions it will produce a message declaring such
   ```
   ```sh
    or binary executables and their arguments:
         * touch
         * ls
         * etc....
   ```
   ```sh
    compiling '*.c' files with 'make' command followed by the filename without the '.c' extension 
    and subsequently executing the executable with './[FILENAME]
    
    e.g file: main.c
         >'make main'
         >'./main'
         
    **NOTE: Two test '.c' files have been left in main folder for behavior examples of a functioning program 
    and a segfaulting program!!! 
   ```

 #### 3. You can clean up '.o' files by typing the following command after usage
  ```sh
        'make clean'
  ```
