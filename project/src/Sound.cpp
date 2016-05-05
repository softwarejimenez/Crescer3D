#include "Sound.h"

namespace Crescer3D
{
#ifndef __CENTOS__
	irrklang::ISoundEngine* Sound::engine;
#endif

	Sound::Sound()
	: System(SystemType::Sys_Sound)
	{
	}

	Sound::~Sound()
	{
#ifndef __CENTOS__
		if(engine)
			engine->drop(); // delete sound engine
#endif
	}

	bool Sound::Initialize()
	{
#ifndef __CENTOS__
		engine = irrklang::createIrrKlangDevice();
		if(!engine) {
			Logger::Log("Could not startup engine\n");
			return false;
		}
		else
			this->playBackgroundMusic();
#endif
			return true;
	}

	void Sound::playBackgroundMusic()
	{
#ifndef __CENTOS__
		if(engine)
		{
			engine->play2D("sounds/backgroundMusic.mp3", true);
		}
#endif
	}

	void Sound::playSound(int index, bool looped)
	{
#ifndef __CENTOS__
		if(engine)
		{
			// play sounds according to index 
			if (index == 1)
			{
				engine->play2D("sounds/slurp.wav");
			}
			if (index == 2)
			{
				engine->play2D("sounds/male-thijs-loud-scream.wav");
			}
		}
#endif
	}
} 