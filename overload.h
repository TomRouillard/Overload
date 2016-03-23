#pragma once
#include "serverManager.h"
#include "daemon.h"

#define CONFIGURATION_FILE_PATH "configuration/configuration.cfg"
#define USERS_DATA_FILE_PATH "configuration/usersData.cfg"
#define DEFAULT_LOL_VERSION_DIRECTORY "C:/Riot Games/League of Legends/RADS/projects/lol_air_client/releases/"
#define DEFAULT_LOL_ACCOUNT_DIRECTORY "/deploy/preferences/"
#define DEFAULT_LOL_IMAGE_FILE_PATH "/deploy/assets/images/champions/"
#define SERVER_IP "95.85.46.198"
#define SERVER_PORT 80

class Overload
{
public:
	Overload();

	void start();

	std::string retrieveCurrentGameInfo();

	std::string getDefaultLeagueDirectory();

	std::string getDefaultLeagueImageDirectory();

private:
	void loadUsersData();

	void loadUserName(std::string name);

	UserInfo retrieveCurrentUser() const;

	UserInfo getLoadedUser(std::string userName) const;

private:
	std::thread _daemonThread;
	Daemon _daemon;
	std::string _defaultLeagueDirectory;
	ServerManager _serverManager;
	std::vector<UserInfo> _users;
};

