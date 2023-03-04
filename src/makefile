CC      = g++
CFLAGS  = -O3 -std=c++11
EXE     = rfea
OBJECTS = electricField.o rfea.o ion.o random.o commandline.o
INSTDIR = /usr/bin


$(EXE):		main.cpp $(OBJECTS)
		$(CC) $(CFLAGS) main.cpp $(OBJECTS) -o $(EXE)

commandline.o:	commandline.h commandline.cpp
		$(CC) $(CFLAGS) -c commandline.cpp

electricField.o:electricField.h electricField.cpp
		$(CC) $(CFLAGS) -c electricField.cpp

rfea.o:	rfea.h rfea.cpp ion.o electricField.o random.o
		$(CC) $(CFLAGS) -c rfea.cpp

ion.o:	ion.h ion.cpp
		$(CC) $(CFLAGS) -c ion.cpp

random.o:	random.h random.cpp
		$(CC) $(CFLAGS) -c random.cpp

clean:
		rm *~ $(EXE) $(OBJECTS)

install:
	cp $(EXE) $(INSTDIR)

uninstall:
	rm $(INSTDIR)/$(EXE)
