CC      = g++
CFLAGS  = -O3 -std=c++11
EXE     = RFEA.x
OBJECTS = electricField.o 
INSTDIR = /usr/bin


$(EXE):		main.cpp $(OBJECTS)
		$(CC) $(CFLAGS) main.cpp $(OBJECTS) -o $(EXE)

electricField.o:electricField.h electricField.cpp
		$(CC) $(CFLAGS) -c electricField.cpp

clean:
		rm *~ $(EXE) $(OBJECTS)

install:
	cp $(EXE) $(INSTDIR)

uninstall:
	rm $(INSTDIR)/$(EXE)
