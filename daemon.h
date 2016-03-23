#pragma once
#define LOL_PROCESS_NAME "League of Legends.exe"

class Overload;
class Daemon
{
public:
	Daemon(Overload& overload);

	void stop();

	// look for LeagueOfLegend process to start
	void lookForProcess();

private:
	void startLoadingScreen();

private:
	bool _running;
	bool _gameRunning;
	Overload& _overload;
};

