#include "Button.h"

namespace Crescer3D
{
	Button::Button()
	{
		x=0;
		y=0;
		label="";
		cube=NULL;
		Program=NULL;
		width=0;
		height=0;
		click=false;
	}

	Button::Button(int pos_x,int pos_y, std::string l,GLuint Program_shader)
	{
		sfMakeRasterFont(); // init font
		cube=LoadModelPlus("model/cube/cubeplus.obj");
		x=pos_x;
		y=pos_y;
		label=l;
		Program=Program_shader;
		width=0;
		height=0;
		click=false;
	}

	Button::~Button()
	{
		x=0;
		y=0;
		label="";
		cube=NULL;
		Program=NULL;
		width=30;
		height=20;
		click=false;
	}

	void Button::WriteLabel()
	{
		sfDrawString(x-15,y, label.c_str());
	}

	void Button::set(std::string l,GLuint Program_shader)
	{
		sfMakeRasterFont(); // init font
		cube=LoadModelPlus("model/cube/cubeplus.obj");
		label=l;
		Program=Program_shader;
	}
	//postion is %
	void Button::setPositionSize(int pos_x,int pos_y,int w,int h)
	{
		x=Window::GetWidth()/*800*/*pos_x /100;
		y=Window::GetHeight()/*600*/*pos_y /100;
		width=w;
		height=h;
	}



	/*----------------------------------------------------------------------------------------
	 *	\brief	This function draws the specified button.
	 */
	void Button::Draw()
	{
		glDisable(GL_DEPTH_TEST);
		mat4 mdlMatrix;
		mdlMatrix=IdentityMatrix();
		glUseProgram(Program);
		mdlMatrix=Mult(T(x,y,0),S(width,height,1));
		glUniformMatrix4fv(glGetUniformLocation(Program, "mdlViewMatrix"), 1, GL_TRUE, mdlMatrix.m);
		DrawModel(cube, Program, "inPosition", NULL, NULL);

		/*
		 *	Calculate the x and y coords for the text string in order to center it.
		 */
		WriteLabel();
		glEnable(GL_DEPTH_TEST);
	}

	bool Button::isClick()
	{
		if(click)
		{
			ClickFalse();
			return true;
		}else
		{
			return false;
		}

	}

		/*----------------------------------------------------------------------------------------
	 *	\brief	This function is used to see if a mouse click or event is within a button
	 *			client area.
	 *	\param	b	-	a pointer to the button to test
	 *	\param	x	-	the x coord to test
	 *	\param	y	-	the y-coord to test
	 */
	void Button::ClickTest(int x_pos,int y_pos)
	{
	    if( x_pos > x-width   && x_pos < x+width &&
			y_pos > y-height  && y_pos < y+height ) {
				click=true;
		}
	}
	void Button::ClickFalse()
	{
		click=false;
	}
}
