#include "HighScore.h"

namespace Crescer3D
{
	// forward declaration of static members
	int HighScore::m_Score;

	HighScore::HighScore(): System(SystemType::Sys_HighScore)
	{
		m_Score=0;
	}

	HighScore::~HighScore()
	{
		m_Score=0;
	}
	bool HighScore::Initialize()
	{
		sfMakeRasterFont(); // init font
		return true;
	}

	void HighScore::DisplayScore()
	{
		//with C++11
		std::string result = "Score: ";
		result = result + std::to_string(m_Score);
		sfDrawString(20, 20, result.c_str());
	}

	void HighScore::IncrementScore()
	{
		m_Score++;
	}

	void HighScore::DisplayListScores()
	{
		int positionx=-30;
		int positiony= 40;
		int limmitScores=10;//not display more than 10 lines
		std::string line;
		std::ifstream myfile ("dataBase/Score.txt", std::ios::in );
		if (myfile.is_open())
		{
			while ( getline (myfile,line) && limmitScores>0)
			{
				//Logger::Log(line);
				sfDrawString(positionx, positiony, line.c_str());
				limmitScores--;
				positiony+=20;
			}
			myfile.close();
		}
		else
		{
			Logger::Log( "Unable to open file");
		}
	}
	void HighScore::SaveScore(std::string name)
	{
		//TODO save only if score >0
		if(m_Score>0)
		{
			std::ofstream myfile ("dataBase/Score.txt", std::ios::out| std::ios::app );
			if (myfile.is_open() )
			{
				myfile << name+" "+std::to_string(m_Score)+"\n";
				Logger::Log( name+" "+std::to_string(m_Score)+"\n");
				myfile.close();
			}
			else
			{
				Logger::Log( "Unable to open file");
			}
		}

	}

}
