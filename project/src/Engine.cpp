#include "Engine.h"

namespace Crescer3D
{
	Engine* Engine::m_Engine;
	EngineState Engine::m_EngineState = Invalid;

	Engine::Engine()
	{
		m_EngineState = Constructing;
		Timing::SetStartTime();
	}

	Engine* Engine::GetEngine()
	{
		if(m_Engine != NULL)
		{
			return m_Engine;
		}
		else
		{
			m_Engine = new Engine();
			return m_Engine;
		}
	}

	void Engine::SetEngineState(EngineState newState)
	{
		m_EngineState = newState;
	}

	Engine::~Engine()
	{
		m_EngineState = Destroying;
	}

	bool Engine::runMainLoop()
	{
		if (!this->Initialize())
			return false;

		m_EngineState = Running;

		while (m_EngineState == Running)
		{
			this->Update();
			internalCheckLoop();
		}

		if (!this->Shutdown())
			return false;

		return true;
	}

	int Engine::Initialize()
	{
		Logger::Log("Starting Crescer3D...");
		m_EngineState = Initializing;

		Crescer3D::Game* game = CreateGame();

		// Add subsystems
		if (!AddSystem(new Crescer3D::Logger()))
			return false;

		if (!AddSystem(new Crescer3D::Window("Crescer3D", 800, 600)))
			return false;

		if (!AddSystem(new Crescer3D::Input()))
			return false;

		if (!AddSystem(new Crescer3D::Camera()))
			return false;
		
#ifndef __CENTOS__
		if (!AddSystem(new Crescer3D::Sound()))
			return false;
#endif
		if (!AddSystem(new Crescer3D::HighScore()))
			return false;

		if (!AddSystem(new Crescer3D::GUI()))
			return false;


		// ... add more subsystems

		// Init subsystems

		if (!m_mapSystems[Crescer3D::SystemType::Sys_Game]->Initialize())
			return false;

		if (!m_mapSystems[Crescer3D::SystemType::Sys_Window]->Initialize())
			return false;

		if (!m_mapSystems[Crescer3D::SystemType::Sys_Camera]->Initialize())
			return false;
#ifndef __CENTOS__
		if (!m_mapSystems[Crescer3D::SystemType::Sys_Sound]->Initialize())
			return false;
#endif
		if (!m_mapSystems[Crescer3D::SystemType::Sys_HighScore]->Initialize())
			return false;
		if (!m_mapSystems[Crescer3D::SystemType::Sys_GUI]->Initialize())
			return false;
		if (!m_mapSystems[Crescer3D::SystemType::Sys_Input]->Initialize())
			return false;



		

		glutStartLoop();

		// ... init more subsystems
			return true;

	}

	Crescer3D::Game* Engine::CreateGame()
	{
		if (!AddSystem(new Crescer3D::Game()))
			return NULL;

		Crescer3D::Game* game = GetSystem<Crescer3D::Game>(Crescer3D::Sys_Game);

		if (!game)
			return NULL;

		return game;
	}

	int Engine::Update()
	{
		typedef std::map<Crescer3D::SystemType, Crescer3D::System*>::const_iterator it_type;
		for (it_type iterator = m_mapSystems.begin(); iterator != m_mapSystems.end(); iterator++)
		{
			if (!iterator->second)
				continue;

			iterator->second->Update();
		}

		return true;
	}

	int Engine::Shutdown()
	{
		m_EngineState = ShuttingDown;
		Logger::Log("Shutting down Crescer3D...");
		glutEndLoop();

		// Delete all subsystems
		typedef std::map<Crescer3D::SystemType, Crescer3D::System*>::iterator it_type;
		for (it_type iterator = m_mapSystems.begin(); iterator != m_mapSystems.end(); iterator++)
		{
			if (!iterator->second->ShutDown())
				Logger::Log("Failed to shutdown Subsystem: " + iterator->first);
				continue;

			SafeDelete(iterator->second);
		}
		return true;
	}

	int Engine::AddSystem(Crescer3D::System* pSys)
	{
		auto element = m_mapSystems.insert(std::make_pair(pSys->GetType(), pSys));
		if (element.second)
			return true;

		return false;
	}
}
