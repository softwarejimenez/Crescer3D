#ifndef _PLAYER_H
#define _PLAYER_H

#include "Logger.h"
#include "Sphere.h"
#include "Food.h"
#

namespace Crescer3D
{
	class Player : public Sphere
	{
		public:
			Player();
			virtual ~Player();
			virtual bool Initialize();
		private:

		
	};
}

#endif // _PLAYER_H
