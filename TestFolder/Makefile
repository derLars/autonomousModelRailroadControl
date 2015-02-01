##################################################
#Sunday, 31.August.2014 made by Lars C. Schwensen#
##################################################

#################################################################
#This is a standard makefile to compile and flash an ATmega8    #
#on an OLIMEX p-28 development board.                           #
#The programmer is an USBPROG which works as an avrispmkII clone#
#################################################################

#the name of the finally output file
OUTPUTNAME=myTest

#all the project files
#REPLACE THESE FILES WITH YOUR PROJECT FILES!!!!
PRJSRC=dccTest.c

#project files as .o files
OBJECTS= $(PRJSRC:.c=.o)

#additional includes
INCLUDES=
LIBRARIES=
#optimization level between (0 (zero) and 3 (maximum))
OPTIMIZE=0

#compilerflags
CFLAGS= -Wall -g -O$(OPTIMIZE)
#-wall enables all warnings
#-g is a debugging flag

#linkerflags
LDFLAGS= 

#executables
CC=gcc
OBJCOPY=objcopy

all: $(OUTPUTNAME)

#link the object files 
$(OUTPUTNAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(OUTPUTNAME) $(OBJECTS) $(LDFLAGS)

#create object files
.c.o: 
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f *.o
