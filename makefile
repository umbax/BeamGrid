all: main.exe
  
clean:
	rm main.o main.exe
  
main.exe: main.o
	g++ -g -o main.exe main.o
  
main.o: main.cpp
	g++ -c -g main.cpp