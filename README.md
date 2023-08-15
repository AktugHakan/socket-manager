# Socket Manager
C++ abstraction over linux socket system calls.

## Getting Started
### Clone the repo
Clone the repo into your code base as a gitmodule or git repo.  
To clone as a git repo:
```bash
git clone https://github.com/AktugHakan/socket-manager.git

```
### Build
Socket Manager library has its built-in makefile  
In the library directory run
```bash
make
```
to compile the library. When compilation is successful, ```libSockets.a``` file is generated in the libraries main folder.  
You have to give the ```libSockets.a``` file to your linker. Add the following arguments to your compiler flags
```bash
-L<library_path> -lSockets
```

### Cross-Compilation
Built-in Makefile also supports cross-compiling. To cross-compile the library:
```bash
make CROSS_COMPILE=<compiler_prefix>
```
for example, if your cross-compiler is ```arm-linux-gnueabihf-gcc``` you should give ```arm-linux-gnueabihf-``` as compiler prefix argument.