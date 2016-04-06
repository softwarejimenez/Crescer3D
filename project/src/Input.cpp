#include "Input.h"

namespace Crescer3D
{
	// forward declaration of static members
	float Input::m_CameraAngle;
	float Input::m_DeltaAngle;
	float Input::m_CameraDirX;
	float Input::m_CameraDirZ;
	float Input::m_CameraPosX;
	float Input::m_CameraPosY;
	float Input::m_CameraPosZ;
	int   Input::m_xOrigin;
	mat4  Input::m_LookAtMatrix;

	Input::Input()
		: System(SystemType::Sys_Input)
	{
		m_CameraAngle = 0.0f;
		m_DeltaAngle = 0.0f;
		m_CameraDirX = 0.0f;
		m_CameraDirZ = -1.0f;
		m_CameraPosX = 0.0f;
		m_CameraPosY = 3.0f;
		m_CameraPosZ = 8.0f;
		m_xOrigin = -1;
		m_LookAtMatrix = IdentityMatrix();
		glutMouseFunc(MouseButton);
		glutMotionFunc(MouseMove);
		glutKeyboardFunc(Keyboard);
	}

	Input::~Input()
	{
	}

	void Input::MouseButton(int button, int state, int x, int y)
	{
		// only start motion if the left button is pressed
		if (button == GLUT_LEFT_BUTTON)
		{
			// when the button is released
			if (state == GLUT_UP)
			{
				m_CameraAngle += m_DeltaAngle;
				m_xOrigin = -1;
			}
			else // state = GLUT_DOWN
				m_xOrigin = x;
		}
	}

	void Input::MouseMove(int x, int y)
	{
		// this will only be true when the left button is down
		if (m_xOrigin >= 0)
		{
			// update m_DeltaAngle
			m_DeltaAngle = (x - m_xOrigin) * 0.001f;
			// update camera's direction
			m_CameraDirX = sin(m_CameraAngle + m_DeltaAngle);
			m_CameraDirZ = -cos(m_CameraAngle + m_DeltaAngle);
		}
	}

	void Input::Keyboard(unsigned char key, int xx, int yy)
	{
		float fraction = 0.1f;
		float velocity = 0.5f;

		switch (key)
		{
			case 'i' :
				Game::GetPlayer()->moveForward();
			break;
			case 'j' :
				Game::GetPlayer()->moveLeft();
			break;
			case 'l' :
				Game::GetPlayer()->moveRight();
			break;
			case 'k' :
				Game::GetPlayer()->moveBack();
			break;
			case 'a' :
				m_CameraAngle -= 0.01f;
				m_CameraDirX = sin(m_CameraAngle);
				m_CameraDirZ = -cos(m_CameraAngle);
			break;
			case 'd' :
				m_CameraAngle += 0.01f;
				m_CameraDirX = sin(m_CameraAngle);
				m_CameraDirZ = -cos(m_CameraAngle);
				break;
			case 'w' :
				m_CameraPosX += m_CameraDirX * fraction;
				m_CameraPosZ += m_CameraDirZ * fraction;
				break;
			case 's' :
				m_CameraPosX -= m_CameraDirX * fraction;
				m_CameraPosZ -= m_CameraDirZ * fraction;
				break;
			case 'z' :
				m_CameraPosY += 0.01;
				break;
			case 'x' :
				m_CameraPosY -= 0.01;
				break;
			case 'q' :
				exit(1);
			break;
		}
	}

	bool Input::Update()
	{
		m_LookAtMatrix = lookAt(m_CameraPosX, m_CameraPosY, m_CameraPosZ, m_CameraPosX + m_CameraDirX, m_CameraPosY, m_CameraPosZ + m_CameraDirZ, 0.0f, 1.0f, 0.0f);
		return true;
	}
}