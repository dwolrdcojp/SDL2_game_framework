prog.o: main.cpp
	g++ main.cpp TexturedRectangle.cpp -o prog -std=c++17 -F/Users/max/Library/Frameworks -framework SDL2 -Wl,-rpath,/Users/max/Library/Frameworks 
