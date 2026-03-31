# MyShell

**MyShell** is a shell made in C++ by *Cortez*, for educational purposes and is one of the first projects
with out the aid of **AI**. Using only documentations and other third party sources to create the entire shell.
The compiler being used is MingW64, downloaded using [MSYS2 UCRT64](https://www.msys2.org/) and written in Visual Studio code.

## Structure

**MyShell** will have a dedicated folder of its own named ***cmds*** which it will constantly monitor because
it will contain most of its commands and also having the ability to use other services that are in the
users *PATH*.

 - **/src** : This folder will contain all of the source code for **MyShell**.

 - **/bin** : This folder will contain all of the binary executables

 - **/docs** : This folder will contain all documentations regarding the shell.

## Set-up

To set up **MyShell** you would need:

 - MingW64 (to compile **MyShell**)
 - MSYS2 UCRT64 (to download MingW64)

After acquiring *MingW64* just run:

`./compile.bat`

then once it is done compiling:

`./bin/MyShell.exe`

## License

**MyShell** is under the GNU General Public License v3. Check the LICENSE file for more information.
