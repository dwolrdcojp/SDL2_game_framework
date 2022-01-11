#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP
#include <string>
#include <vector>

#include <SDL.h>

#include "../include/TexturedRectangle.hpp"
#include "../include/Collider2D.hpp"

class GameEntity{
	public:
		GameEntity();
		GameEntity(SDL_Renderer* renderer);

		~GameEntity();

		void Update();

		void Render();

		// Adding components
		void AddTexturedRectangleComponent(std::string spritepath);
		void AddTexturedRectangleComponent(std::string spritepath, int redcolorkey, int greencolorkey, int bluecolorkey);

		void AddBoxCollider2D();

		TexturedRectangle& GetTexturedRectangle();
		BoxCollider2D& GetBoxCollider2D(size_t index);
		// Sets the position of our game entity 
		// This operates by moving all of the 
		// components position as well so they are 
		// updated.
		void SetPosition(int x, int y);
		// Sets all the components to a specificied dimension 
		void SetDimensions(int w, int h);


	private:
		// compenents
		TexturedRectangle* m_sprite;
		std::vector<BoxCollider2D*> m_colliders;
		// Pointer to the render that object will render compenents to
		SDL_Renderer* m_renderer;
};

#endif
