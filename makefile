CC      = g++
CFLAGS  = -O3 -std=c++11
EXE     = RFEA.x
OBJECTS = electricField.o rfea.o ion.o
INSTDIR = /usr/bin


$(EXE):		main.cpp $(OBJECTS)
		$(CC) $(CFLAGS) main.cpp $(OBJECTS) -o $(EXE)

electricField.o:electricField.h electricField.cpp
		$(CC) $(CFLAGS) -c electricField.cpp

rfea.o:	rfea.h rfea.cpp
		$(CC) $(CFLAGS) -c rfea.cpp

ion.o:	ion.h ion.cpp
		$(CC) $(CFLAGS) -c ion.cpp

clean:
		rm *~ $(EXE) $(OBJECTS)

install:
	cp $(EXE) $(INSTDIR)

uninstall:
	rm $(INSTDIR)/$(EXE)
