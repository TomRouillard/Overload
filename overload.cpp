#include "stdafx.h"
#include "overload.h"
#include "exception.h"

Overload::Overload() : _daemon(*this)
{
	_serverManager.initializeServerInfo(SERVER_IP, SERVER_PORT);

	_defaultLeagueDirectory = getDefaultLeagueDirectory();

	loadUsersData();
}

void Overload::start()
{
	_daemon.lookForProcess();
}

std::string Overload::getDefaultLeagueDirectory()
{
	std::vector<std::string> files = utils::FileUtils::getFoldersInDirectory(DEFAULT_LOL_VERSION_DIRECTORY);
	if (files.size() > 0)
	{
		return DEFAULT_LOL_VERSION_DIRECTORY + files[0] + DEFAULT_LOL_ACCOUNT_DIRECTORY;
	}
	throw exception::EmptyDirectory(DEFAULT_LOL_VERSION_DIRECTORY);
}

std::string Overload::getDefaultLeagueImageDirectory()
{
	std::vector<std::string> files = utils::FileUtils::getFoldersInDirectory(DEFAULT_LOL_VERSION_DIRECTORY);
	if (files.size() > 0)
	{
		return DEFAULT_LOL_VERSION_DIRECTORY + files[0] + DEFAULT_LOL_IMAGE_FILE_PATH;
	}
	throw exception::EmptyDirectory(DEFAULT_LOL_VERSION_DIRECTORY);
}

std::string Overload::retrieveCurrentGameInfo()
{
	UserInfo currentUser = retrieveCurrentUser();
	return _serverManager.retrieveGameInfo(currentUser._id);
}

//Reach useful values inside LeagueOfLegends files.
void Overload::loadUsersData()
{
	std::vector<std::string> userNames = utils::FileUtils::getFilesInDirectory(_defaultLeagueDirectory);
	std::string fileContent = utils::FileUtils::readFile(_defaultLeagueDirectory + std::string("global/global.properties"));
	for (std::size_t i = 0; i < userNames.size(); i++)
	{
		std::string userName = userNames[i].substr(0, userNames[i].size() - 11);
		if (userName.find("shared") == std::string::npos)
		{
			userName = utils::StringUtils::removeSpaces(userName);
			loadUserName(userName);
		}
	}
	LOG(INFO) << "User data loaded.";
}

void Overload::loadUserName(std::string name)
{
	UserInfo user = _serverManager.retrieveUserInfo(name);
	_users.push_back(user);
}

UserInfo Overload::retrieveCurrentUser() const
{
	std::vector<std::string> userNames = utils::FileUtils::getFilesInDirectory(_defaultLeagueDirectory);
	std::string fileContent = utils::FileUtils::readFile(_defaultLeagueDirectory + std::string("global/global.properties"));
	for (std::size_t i = 0; i < userNames.size(); i++)
	{
		std::string userName = userNames[i].substr(0, userNames[i].size() - 11);
		std::size_t id = fileContent.find(userName);
		if (id != std::string::npos)
		{
			return getLoadedUser(userName);
		}
	}
	return UserInfo();
}

UserInfo Overload::getLoadedUser(std::string userName) const
{
	auto userIt = std::find_if(_users.begin(), _users.end(), [userName](UserInfo user){ return userName == user._name; });
	if (userIt != _users.end())
	{
		return *userIt;
	}
	return UserInfo();
}