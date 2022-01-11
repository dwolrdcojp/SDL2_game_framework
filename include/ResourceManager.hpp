#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <string>
#include <unordered_map>

// Third party library
#include <SDL.h>

class ResourceManager{
	private:
		// Constructor
		ResourceManager();
		// Copy Constructor
		ResourceManager(ResourceManager const&);
		// When defining a copy constructor you should also define a copy assignment operator
		ResourceManager operator=(ResourceManager const&);

		std::unordered_map<std::string, SDL_Surface*> m_surfaces;

	public:
		static ResourceManager& GetInstance();

		SDL_Surface* GetSurface(std::string filepath);
};

#endif

