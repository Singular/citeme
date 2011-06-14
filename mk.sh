#!/bin/sh

gcc -c -g -Wall -I . citeme_lib.c || exit

ar  rcs citeme_lib.a citeme_lib.o || exit 


gcc -g -Wall -I . citeme_app.c -o citeme_app  citeme_lib.a

