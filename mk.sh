#!/bin/bash


echo "USING CC: [${CC:=gcc}]"

# static library...
$CC -c -g  -I . citeme_lib.c || exit
ar rcs citeme_lib.a citeme_lib.o || exit 

# shared library...
$CC -c -g  -I . -fPIC citeme_lib.c -o citeme_lib.so.o || exit
$CC -shared -o citeme_lib.so citeme_lib.so.o || exit
# -Wl,-soname,citeme_lib.so 




# main app:
$CC -c -g  -I . citeme_app.c || exit


# shared version:
$CC -g  citeme_app.o -o citeme_app.dynamically_linked -L. citeme_lib.so || exit

## run shared version...
# echo $LD_LIBRARY_PATH
LD_LIBRARY_PATH=. ./citeme_app.dynamically_linked

# static version
$CC -g  -L. citeme_app.o -o citeme_app  citeme_lib.a || exit


$CC -g  -L. -static citeme_app.o -o citeme_app.statically_linked citeme_lib.a  || exit
