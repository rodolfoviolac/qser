CC=gcc
SRCPATH=./src/
OBJPATH=./obj/
FLAGS=-O2 -Wall -I./include

all: qser

qser: pidController.o decoderInterface.o quanserInterface.o userInterface.o helpers.o mainThread.o main.o
	@echo "Building Qser..."
	$(CC) $(FLAGS) $(OBJPATH)* -o qser -lpthread

main.o: $(SRCPATH)main.c
	$(CC) $(FLAGS) -c $(SRCPATH)main.c -o $(OBJPATH)main.o

helpers.o: $(SRCPATH)helpers/helpers.c
	$(CC) $(FLAGS) -c $(SRCPATH)helpers/helpers.c -o $(OBJPATH)helpers.o

mainThread.o: $(SRCPATH)mainThread/mainThread.c
	$(CC) $(FLAGS) -c $(SRCPATH)mainThread/mainThread.c -o $(OBJPATH)mainThread.o

quanserInterface.o: $(SRCPATH)quanserInterface/quanserInterface.c
	$(CC) $(FLAGS) -c $(SRCPATH)quanserInterface/quanserInterface.c -o $(OBJPATH)quanserInterface.o

userInterface.o: $(SRCPATH)userInterface/userInterface.c
	$(CC) $(FLAGS) -c $(SRCPATH)userInterface/userInterface.c -o $(OBJPATH)userInterface.o

pidController.o: $(SRCPATH)pidController/pidController.c
	$(CC) $(FLAGS) -c $(SRCPATH)pidController/pidController.c -o $(OBJPATH)pidController.o

decoderInterface.o: $(SRCPATH)decoderInterface/decoderInterface.c
	$(CC) $(FLAGS) -c $(SRCPATH)decoderInterface/decoderInterface.c -o $(OBJPATH)decoderInterface.o

docs: Doxyfile DoxygenLayout.xml README.md LICENSE.md
	@echo "Building Doxygen..."
	doxygen

clean:
	rm -f $(OBJPATH)* qser