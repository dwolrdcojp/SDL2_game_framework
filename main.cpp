// Compile in the terminal for mac
// g++ -std=c++19 main.cpp ./glad/src/glad.c -I./glad/include -o prog -I/Users/max/Library/Frameworks/SDL2.framework/Versions/A/Headers -F/Users/max/Library/Frameworks -framework SDL2 -ldl
// install_name_tool -change @rpath/SDL2.framework/Versions/A/SDL2 /Users/max/Library/Frameworks/SDL2.framework/Versions/A/SDL2 prog
// ./prog

// Example program
// Using SDL2 to create an application window
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <SDL.h>
#include "TexturedRectangle.hpp"

int main(int argc, char* argv[]) {

	SDL_Window *window=nullptr; // Declare a pointer

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		std::cout << "SDL could not be initialized: " <<
			SDL_GetError();
	}else{
		std::cout << "SDL video system is ready to go\n";
	}

	
	// Create an application window with the following settings:
	window = SDL_CreateWindow(
			"A SDL2 Window", // window title
			0, // initial x position
			0, // initial y position
			640, // width in pixels
			480, // height in pixels,
			SDL_WINDOW_SHOWN
	);

	SDL_Renderer* renderer=nullptr;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	

	// Check that window was successfully created
	if (window == NULL) {
		// In the case that window could not be made...
		std::cout << "Could not create the window" << std::endl;
		return 1;
	}

	std::vector<std::shared_ptr<TexturedRectangle>> rects;
	for(int i=0; i < 6; i++){
		std::shared_ptr<TexturedRectangle> rect = std::make_shared<TexturedRectangle>(renderer,"./images/example.bmp");
		rects.push_back(rect);
	}

	int row = 0;
	int col = 1;
	for(int i=0; i < 3; i++){
		rects[i]->SetRectangleProperties(200*col, 200*row, 200, 200);
		if(i < 1){
			std::cout << rects[i] << "row: " << row << " col: " << col << std::endl;
		}else if(i < 3){
			col++;
			std::cout << rects[i] << "row: " << row << " col: " << col << std::endl;
		}
	}
	row = 1;
	col = 0;
	for(int i=3; i < 6; i++){
		rects[i]->SetRectangleProperties(200*col, 200*row, 200, 200);
		if(i > 2){
			col++;
			std::cout << rects[i] << "row: " << row << " col: " << col << std::endl;
		}
	}


	// Infinite loop for our application 
	bool gameIsRunning = true;
	while(gameIsRunning){
		SDL_Event event;
		// Start our event loop
		while(SDL_PollEvent(&event)){
			// Handle each specific event
			if(event.type == SDL_QUIT){
				gameIsRunning = false;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

		for(auto& rect: rects){
			rect->Render(renderer);
		}

		// Finally show what we have drawn
		SDL_RenderPresent(renderer);
	}
	// Close and destroy the window (becaue this is C and you have to create and delete memory allocations)
	SDL_DestroyWindow(window);

	// Clean up
	SDL_Quit();
	return 0;
}
