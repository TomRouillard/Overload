#pragma once

#define TIMEOUT

#include "UserInfo.h"

class ServerManager
{
public:
	void initializeServerInfo(std::string serverAddress, int serverPort);

	void loadFiles(const std::vector<std::string>& files);

	UserInfo retrieveUserInfo(std::string userName, std::string serverName = "euw");

	std::string retrieveGameInfo(const UserId& userId, std::string serverName = "EUW1");

	void retrieveUpdates(std::string currentVersion);

private:
	const web::http::client::http_client getClient() const;

	//Useful function to retrieve a json from a url
	const pplx::task<web::json::value> retrieveJson(const web::uri& uri, web::http::method method = web::http::methods::GET) const;

	//Useful function to retrieve a string from a url
	const pplx::task<utility::string_t> retrieveString(const web::uri& uri, web::http::method method = web::http::methods::GET) const;

private:
	web::uri _uri;
};
