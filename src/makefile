CC      = g++
CFLAGS  = -O3 -std=c++11 -Wall -g
EXE     = rfea
OBJECTS = electricField.o rfea.o ion.o random.o commandline.o functions.o XSection.o plasma.o integration.o
INSTDIR = /usr/bin


$(EXE):		main.cpp $(OBJECTS)
		$(CC) $(CFLAGS) main.cpp $(OBJECTS) -o $(EXE)

commandline.o:	commandline.h commandline.cpp
		$(CC) $(CFLAGS) -c commandline.cpp

electricField.o:electricField.h electricField.cpp plasma.o
		$(CC) $(CFLAGS) -c electricField.cpp

rfea.o:		rfea.h rfea.cpp ion.o electricField.o random.o functions.o
		$(CC) $(CFLAGS) -c rfea.cpp

ion.o:		ion.h ion.cpp functions.h functions.cpp
		$(CC) $(CFLAGS) -c ion.cpp

random.o:	random.h random.cpp
		$(CC) $(CFLAGS) -c random.cpp

functions.o:	functions.h functions.cpp
		$(CC) $(CFLAGS) -c functions.cpp

XSection.o:     XSection.h XSection.cpp
		$(CC) $(CFLAGS) -c XSection.cpp

plasma.o:	plasma.h plasma.cpp integration.h integration.cpp
		$(CC) $(CFLAGS) -c plasma.cpp

integration.o:	integration.h integration.cpp
		$(CC) $(CFLAGS) -c integration.cpp

clean:
		rm *~ $(EXE) $(OBJECTS)

install:
		cp $(EXE) $(INSTDIR)

uninstall:
		rm $(INSTDIR)/$(EXE)
