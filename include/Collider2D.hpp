#ifndef COLLIDER_2D_HPP
#define COLLIDER_2D_HPP

#include <SDL.h>

#include "../include/TexturedRectangle.hpp"
#include "../include/Vector2D.hpp"

class ICollider2D{
	virtual void Update()=0;
	virtual void Render()=0;
};

// A box collider is a 2D collider, so we inherit from that interface
class BoxCollider2D : public ICollider2D{
	public:
		// Default Constructor
		BoxCollider2D();
		// Destructor
		~BoxCollider2D();
		// Retrieve the bounding box rectangle
		SDL_Rect& GetColliderBoundingBox();
		// Detect collision
		// TODO: We may want to think about if we'll
		// handle one 'ICollider2D' object, or 
		// otherwise handle different colliders later
		// on. This means passing in a pointer later 
		// on and detecting the type at run-time, which
		// could be expense.
		SDL_bool IsColliding(BoxCollider2D& collider);
		// Set the collider position (top-left corner of bounding box)
		void SetAbsolutePosition(int x, int y);
		// Set the dimensions of the bounding box
		void SetDimensions(int w, int h);
		// Special function to automatically set the bounding box 
		// This function will look at a surface, and create 
		// a bounding box tightly fit around the surfaces 
		// minimum and maximum x and y values. 
		Vector2D SetBoundingBoxAutomatically(SDL_Surface* surface, Uint8 r, Uint8 g, Uint8 b);

		void Update();
		void Render();
	private:
		SDL_Rect* m_colliderRectangle;
};

#endif
