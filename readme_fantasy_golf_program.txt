Some notes about fantasy golf program:

When I installed Windows 11, the old executable (possibly made under Windows 8 or Windows 10) no longer worked.

I downloaded MinGW in order to get a minimal C/C++ compiler/linker.
Had to change various environment variables (in particular the PATH) to point to gcc, Python etc.

Built the C++ application with the following commands:

gcc -c golf_main.c -o golf_main.old
gcc -c golf_utilities.c -o golf_utilities.old
gcc -c prs_line.c -o prs_line.old

To build final executable:

gcc -o fantasy_golf_program golf_main.o golf_utilities.o prs_line.o

Out of the box I tested this using knows files (espn_bmw.txt), but was getting strange results on the money (an extra 0).  It seems to be related to the parse_line function.  I finally got it to work using strtok C library function instead.  Not sure if I will run into other errors in the future.

This is likely due to some C functions behaving differently after several years.