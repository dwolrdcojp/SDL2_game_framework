#ifndef SOUND_HPP
#define SOUND_HPP

#include <string>

// Third party
#include <SDL2/SDL.h>

// Interace for Audio
class ISound{
	public:
		// Destructor is virtual for our interface 
		virtual ~ISound() {};
		// Member functions that should be implemented
		virtual void PlaySound() = 0;
		virtual void StopSound() = 0;
};

class Sound : public ISound{
	public:
		// Constructor
		Sound(std::string filepath);
		// Destructor
		~Sound();
		// Play sound
		void PlaySound();
		// Stop the sound 
		void StopSound();
		// Specific to SDL_Audio API 
		void SetupDevice();

	private: // (private member variables)
		// Device the sound will play on
		// Note: This could be moved to some configuration,
		// i.e., a higher level 'AudioManager' class
		SDL_AudioDeviceID m_device;

		// Properties of the wave file that is loaded 
		SDL_AudioSpec m_audioSpec;
		Uint8* 	      m_waveStart;
		Uint32        m_waveLength; 
};

#endif
