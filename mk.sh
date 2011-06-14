#!/bin/sh


# static library...
gcc -c -g -Wall -I . citeme_lib.c || exit
ar rcs citeme_lib.a citeme_lib.o || exit 

# shared library...
gcc -c -g -Wall -I . -fPIC citeme_lib.c -o citeme_lib.so.o || exit
gcc -shared -o citeme_lib.so citeme_lib.so.o || exit
# -Wl,-soname,citeme_lib.so 




# main app:
gcc -c -g -Wall -I . citeme_app.c || exit

# static version
gcc -g -Wall -static citeme_app.o -L. citeme_lib.a -o citeme_app.statically_linked || exit
gcc -g -Wall -L. citeme_app.o -o citeme_app  citeme_lib.a



# shared version:
gcc -g -Wall citeme_app.o -o citeme_app.dynamically_linked -L. citeme_lib.so


echo $LD_LIBRARY_PATH
LD_LIBRARY_PATH=. ./citeme_app.dynamically_linked