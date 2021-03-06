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

#include "../include/SDLApp.hpp"
#include "../include/TexturedRectangle.hpp"
#include "../include/AnimatedSprite.hpp"
#include "../include/GameEntity.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/Vector2D.hpp"
#include "../include/Sound.hpp"
#include "../include/DynamicText.hpp"

// One possibility of creating a global for our application
SDLApp* app;
// Create two obejcts to render 
// Eventually, we will want some sort of factory
// to manage object creation in our App...
GameEntity* object1;
GameEntity* object2;

Sound* CollisionSound;

void HandleEvents(){
	SDL_Event event;
	// (1) Handle Input
	// Start our event loop
	while(SDL_PollEvent(&event)){
		// Handle each specific event 
		if(event.type == SDL_QUIT){
			app->StopAppLoop();
		}
		// Detect collision from our two shapes if mouse button is pressed 
		if(event.button.button == SDL_BUTTON_LEFT){
			if(object2->GetBoxCollider2D(0).IsColliding(object1->GetBoxCollider2D(0))){
				std::cout << "Is colliding with hit box 1" << std::endl;
				CollisionSound->PlaySound();
			}else{
				std::cout << "Not colliding wiht hit box 1" << std::endl;
			}

			if(object2->GetBoxCollider2D(0).IsColliding(object1->GetBoxCollider2D(1))){
				std::cout << "Is colliding with hit box 2" << std::endl;
				CollisionSound->PlaySound();
			}else{
				std::cout << "Not colliding with hit box 2" << std::endl;
			}
		}
	}
}

void HandleUpdate(){
	// Update each of the objects
	object1->Update();
	object2->Update();

	static int posX = 0;
	static int posY = 0;
	static bool up = true;
	static bool right = true;

	if(up){
		posY--;
	}else{
		posY++;
	}

	if(right){
		posX++;
	}else{
		posX--;
	}

	if(posX > app->GetWindowWidth()){
		right = false;
	}else if(posX < 0){
		right = true;
	}
	
	if(posY < 0){
		up = false;
	}else if(posY > app->GetWindowHeight()){
		up = true;
	}

	object2->SetPosition(posX, posY);
	object2->SetDimensions(100, 100);

	object1->SetPosition(app->GetMouseX(), app->GetMouseY());
	object1->SetDimensions(300, 300);

	object1->GetBoxCollider2D(1).SetDimensions(object1->GetTexturedRectangle().GetWidth(), object1->GetTexturedRectangle().GetHeight()/2);

	Vector2D dims = object1->GetBoxCollider2D(0).SetBoundingBoxAutomatically(
			ResourceManager::GetInstance().GetSurface("../images/donkeykong1.bmp"), 0xFF, 0x00, 0xFF);

	int newXPos = dims.x + app->GetMouseX();
	int newYPos = dims.y + app->GetMouseY();
	
	object1->GetBoxCollider2D(0).SetAbsolutePosition(newXPos, newYPos);
}

void HandleRendering(){
	// Render our objects 
	object1->Render();
	object2->Render();
	
	// Render the text after drawing the objects 
	DynamicText text1("../assets/fonts/Bullpen3D.ttf", 32);
	DynamicText text2("../assets/fonts/Bullpen3D.ttf", 16);
	DynamicText text3("../assets/fonts/Bullpen3D.ttf", 16);
	text1.DrawText(app->GetRenderer(), "Mike SDL2 Series", 0, 0, 100, 50);
	text2.DrawText(app->GetRenderer(), "Text!", 300, 300, 200, 50);
	
	static int counter = 0;
	counter++;
	text3.DrawText(app->GetRenderer(), std::to_string(counter), 50, 300, 50, 50);
}



int main(int argc, char* argv[]) {
	// Setup the SDLApp
	const char* title = "New SDL2 Abstraction";
	app = new SDLApp(SDL_INIT_VIDEO | SDL_INIT_AUDIO, title, 20, 20, 640, 480);
	app->SetMaxFrameRate(16);

	
	// Create any objects in our scene
	object1 = new GameEntity(app->GetRenderer());
	object1->AddTexturedRectangleComponent("../images/donkeykong1.bmp", 0xFF, 0x00, 0xFF);
	object1->AddBoxCollider2D();
	object1->AddBoxCollider2D();

	object2 = new GameEntity(app->GetRenderer());
	object2->AddTexturedRectangleComponent("../images/donkeykong1.bmp");
	object2->AddBoxCollider2D();

	// Set up our sounds 
	CollisionSound = new Sound("../assets/sounds/collide.wav");
	// TODO: For now, we setup the device 'per sound' 
	// 'may' make sense if we have several devices, or 
	// 'capture' devices, likely we'll want to refactor this however
	CollisionSound->SetupDevice();

	// Set callback functions
	app->SetEventCallback(HandleEvents);
	app->SetUpdateCallback(HandleUpdate);
	app->SetRenderCallback(HandleRendering);
	// Run our application until terminated
	app->RunLoop();
	// Clean up our application 
	delete app;
	delete object1;
	delete object2;
	delete CollisionSound;

	return 0;
}
