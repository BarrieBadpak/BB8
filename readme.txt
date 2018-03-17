src = c files
lib = libraries
bin = binary executables
include = header files

//create object files from c scripts
gcc -o functions.o functions.c -c

//create libraries
ar rcs lib[library name].a [object file].o

//compile the binary executable with a library
gcc -static ./src/[main c script] -L./lib -I./include -l[library name] -lm -o ./bin/[program name]

//clone specific branch from github
git clone -b {branch} https://github.com/barriebadpak/bb8.git
