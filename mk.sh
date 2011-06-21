#!/bin/bash


echo "USING CC: [${CC:=gcc}]"

# static library...
echo ":::::::::::::::::::::: Data Provider :::::::::::::::::::::::"
$CC -c -g  -I . citeme_provide.c -o citeme_lib.o || exit
strip -x citeme_lib.o || exit
objdump -t citeme_lib.o || exit 
nm citeme_lib.o  || exit 

echo ":::::::::::::::::::::: Static library:::::::::::::::::::::::"
ar rcs citeme_lib.a citeme_lib.o || exit 

objdump -t citeme_lib.a || exit 
nm citeme_lib.a  || exit 


echo ":::::::::::::::::::::: Shared library:::::::::::::::::::::::"
# shared library...
$CC -c -g  -I . -fPIC citeme_provide.c -o citeme_lib.so.o || exit
$CC  -Wl,-x -shared -o citeme_lib.so citeme_lib.so.o || exit
# -Wl,-soname,citeme_lib.so 

strip -x citeme_lib.so || exit
objdump -t citeme_lib.so || exit
nm citeme_lib.so || exit


echo ":::::::::::::::::::::: Data Collector :::::::::::::::::::::::"

# main app:
$CC -c -g  -I . citeme_collect.c -o citeme_app.o || exit
strip -x citeme_app.o || exit

objdump -t citeme_app.o || exit 
nm citeme_app.o  || exit 


echo ":::::::::::::::::::::: Shared version :::::::::::::::::::::::"

# shared version:
$CC -g  citeme_app.o -o citeme_app.dynamically_linked -L. citeme_lib.so || exit

strip -x citeme_app.dynamically_linked || exit

objdump -t citeme_app.dynamically_linked || exit 
nm citeme_app.dynamically_linked || exit 

echo "Running......................................................"
## run shared version...
# echo $LD_LIBRARY_PATH
LD_LIBRARY_PATH=. ./citeme_app.dynamically_linked
echo "......................................................ret: $?"


echo ":::::::::::::::::::::: Static version :::::::::::::::::::::::"

# static version
$CC -g -L. citeme_app.o -o citeme_app  citeme_lib.a || exit
strip -x citeme_app || exit

objdump -t citeme_app || exit 
nm citeme_app || exit 

echo "Running......................................................"
./citeme_app
echo "......................................................ret: $?"

echo ":::::::::::::::::::::: Totally Static version (gcc only?) :::::::::::::::::::::::"

$CC -g  -L. -static citeme_app.o -o citeme_app.statically_linked citeme_lib.a  || exit

strip -x citeme_app.statically_linked || exit

######### TOOOOOOOOOOO MUCH SYMBOLS.....
objdump -t citeme_app.statically_linked | grep RegisterCitation || exit 
nm citeme_app.statically_linked | grep RegisterCitation || exit 

echo "Running......................................................"
./citeme_app.statically_linked
echo "......................................................ret: $?"
