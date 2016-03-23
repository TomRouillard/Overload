#include "stdafx.h"
#include "daemon.h"
#include "loadingScreen.h"
#include "overload.h"

Daemon::Daemon(Overload& overload): _running(true),
									_gameRunning(false),
									_overload(overload)
{
}

void Daemon::stop()
{
	_running = false;
}

void Daemon::startLoadingScreen()
{
	LoadingScreen loadingScreen;
	loadingScreen.displayLoop(_overload.retrieveCurrentGameInfo(), _overload.getDefaultLeagueImageDirectory());
}

void Daemon::lookForProcess()
{
	sf::Clock clock;
	while (_running)
	{
		float elapsedTime = (float)clock.getElapsedTime().asMilliseconds();
		if (elapsedTime >= 1000)
		{
			clock.restart();
			bool processStarted = utils::ProcessUtils::isProcessStarted(LOL_PROCESS_NAME);
			if (processStarted && !_gameRunning)
			{
				// game started
				startLoadingScreen();
				_gameRunning = true;
			}
			if (!processStarted && _gameRunning)
			{
				_gameRunning = false;
				// game ended
			}
		}
		else
		{
			sf::sleep(sf::milliseconds(sf::Int32(1000 - elapsedTime)));
		}
	}
}