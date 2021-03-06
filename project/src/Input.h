#ifndef _INPUT_H
#define _INPUT_H

#if defined (__LINUX__) || (__CENTOS__)
	extern "C"
	{
		#define GL_GLEXT_PROTOTYPES
		#include "../../common/Linux/MicroGlut.h"
	}
#endif
#ifdef __OSX__
	extern "C"
	{
		#include <OpenGL/gl3.h>
		#include "../../common/mac/MicroGlut.h"
	}
#endif
#include "System.h"
#include "Game.h"
#include "Engine.h"
#include "../../common/VectorUtils3.h"
#include "Window.h"
#include "GUI.h"
#include "Sound.h"

namespace Crescer3D
{
	class Input : public System
	{
	public:
		Input();
		virtual bool Initialize();
		virtual ~Input();

		virtual bool Update();
		static vec2 GetMousePosition();
		static void Reset();
	private:
		static void Keyboard(unsigned char key, int xx, int yy);
		static void MouseButton(int button, int state, int x, int y);
		static void MouseMove(int x, int y);
		static int m_MouseXPos;
		static int m_MouseYPos;
	};
}

#endif // _INPUT_H
