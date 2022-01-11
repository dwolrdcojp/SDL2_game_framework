#ifndef ANIMATED_SPRITE_HPP
#define ANIMATED_SPRITE_HPP

#include <string>

#include <SDL.h>

class AnimatedSprite{
	public:
		// Constructor
		AnimatedSprite(SDL_Renderer*& renderer, std::string filepath);
		// Destructor
		~AnimatedSprite();

		//
		void Draw(int x, int y, int w, int h);

		// Select and play a specific frame
		void PlayFrame(int x, int y, int w, int h, int frame);

		// Update every frame 
		void Update();

		void Render(SDL_Renderer*& renderer);

	private:
		SDL_Rect m_src;
		SDL_Rect m_dst;
		SDL_Texture* m_texture;
};

#endif

