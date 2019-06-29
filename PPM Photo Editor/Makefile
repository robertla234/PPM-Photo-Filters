######################################################################
# Makefile: Makefile for Assignment #3 EECS22 Fall 2018
#
# 10/30/18 Mihnea Chirila: updated for EECS22 Assignment 3 Fall 2018
#
######################################################################


# design names
DESIGN = PhotoLab PhotoLabTest

#libs
LIBS   = libFilter.a

CC     = gcc
DEBUG  = -DDEBUG
DNDEBUG = -DNDEBUG
CFLAGS = -ansi -std=c99 -g -Wall -c
LFLAGS = -ansi -std=c99 -g -Wall -lm
AR     = ar rc
RANLIB = ranlib

IMAGES = bw.ppm \
         edge.ppm \
         shuffle.ppm \
	 brightness.ppm \
         hmirror.ppm \
         hue.ppm \
         bigresize.ppm \
         smallresize.ppm \
         hflip.ppm \
         rotate.ppm \
         saturate.ppm \

all: PhotoLab PhotoLabTest


########### generate object files ###########

#target to generate FileIO.o
FileIO.o: Image.h FileIO.h FileIO.c Constants.h
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o

#target to generate DIPs.o
DIPs.o: Image.h DIPs.h DIPs.c Constants.h
	$(CC) $(CFLAGS)  DIPs.c -o DIPs.o

#target to generate Advanced.o
Advanced.o: Image.h Advanced.h Advanced.c Constants.h
	$(CC) $(CFLAGS) Advanced.c -o Advanced.o

Test.o: Test.h Constants.h Test.c 
	$(CC) $(CFLAGS) Test.c -o Test.o

Image.o: Image.h Constants.h Image.c
	$(CC) $(CFLAGS) Image.c -o Image.o

#target to generate PhotoLab.o
PhotoLab.o: Image.h PhotoLab_v4.c DIPs.h Advanced.h FileIO.h Constants.h
	$(CC) $(CFLAGS) $(DNDEBUG) PhotoLab_v4.c -o PhotoLab.o

#target to generate FileIO_DEBUG.o
PhotoLab_DEBUG.o: Image.h PhotoLab_v4.c DIPs.h Advanced.h FileIO.h Constants.h
	$(CC) $(CFLAGS) $(DEBUG) -c PhotoLab_v4.c -o PhotoLab_DEBUG.o


########### generate library files ###########

#target to generate libFilter.a
libFilter.a: DIPs.o Advanced.o
	$(AR) libFilter.a Advanced.o DIPs.o
	$(RANLIB) libFilter.a

########### generate executables ###########

#target to generate PhotoLab
PhotoLab: Image.o PhotoLab.o FileIO.o libFilter.a
	$(CC) $(LFLAGS) PhotoLab.o FileIO.o Image.o -L. -lFilter -o PhotoLab

#target to generate test
PhotoLabTest: Image.o PhotoLab_DEBUG.o Test.o FileIO.o libFilter.a
	$(CC) $(LFLAGS) PhotoLab_DEBUG.o Test.o FileIO.o Image.o -L. -lFilter -o PhotoLabTest

#target to clean the directory
clean:
	rm -f *.o *.jpg $(DESIGN) $(IMAGES) $(LIBS)
