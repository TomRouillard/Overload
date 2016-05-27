#include "stdafx.h"
#include "serverManager.h"

void ServerManager::initializeServerInfo(std::string serverAddress, int serverPort)
{
	web::uri_builder builder;
	builder.set_host(utils::StringUtils::stringToWString(serverAddress));
	builder.set_port(serverPort);
	_uri = builder.to_uri();
	LOG(INFO) << "Server info initialized with URI: " << utils::StringUtils::wStringToString(_uri.to_string());
}

void ServerManager::loadFiles(const std::vector<std::string>& files)
{
	//sf::Http http(_serverAddress, m_serverPort);
	//for (std::size_t i = 0; i < files.size(); i++)
	//{
	//	sf::Http::Request request;
	//	request.setMethod(sf::Http::Request::Post);
	//	request.setUri(files[i]);
	//	auto response = http.sendRequest(request, sf::seconds(3));
	//	if (response.getStatus() == response.Ok)
	//	{
	//		auto data = response.getBody();
	//		Utils::saveFileAt(data, files[i]);
	//	}
	//}
}

UserInfo ServerManager::retrieveUserInfo(std::string userName, std::string serverName)
{
	UserInfo userInfo;
	web::uri_builder builder(L"api/summoner");
	builder.append_path(utils::StringUtils::stringToWString(userName));
	builder.append_path(utils::StringUtils::stringToWString(serverName));
	retrieveJson(builder.to_uri()).then([&userInfo](pplx::task<web::json::value> previousTask)
	{
		try
		{
			const web::json::value &jsonValue = previousTask.get();
			const web::json::object& jsonObject = jsonValue.as_object();
			userInfo.loadFromJson(jsonObject.cbegin()->second.as_object());
		}
		catch (const web::http::http_exception &e)
		{
			LOG(ERROR) << "Error while sending an http request... " << e.what();
		}
	}).wait();
	return userInfo;
}

std::string ServerManager::retrieveGameInfo(const UserId& userId, std::string serverName)
{
	std::string gameInfo;
	web::uri_builder builder(L"api/game");
	builder.append_path(utils::StringUtils::stringToWString(serverName));
	builder.append_path(std::to_wstring(userId));
	retrieveJson(builder.to_uri()).then([&gameInfo](pplx::task<web::json::value> previousTask)
	{
		try
		{
			const web::json::value &jsonValue = previousTask.get();
			gameInfo = utils::StringUtils::wStringToString(jsonValue.serialize());
		}
		catch (const web::http::http_exception &e)
		{
			LOG(ERROR) << L"Error while sending an http request... " << e.what();
		}
	}).wait();
	return gameInfo;
}

void ServerManager::retrieveUpdates(std::string currentVersion)
{
	// Check for available updates and download files
}

const pplx::task<web::json::value> ServerManager::retrieveJson(const web::uri& uri, web::http::method method) const
{
	web::http::client::http_client httpClient(_uri);
	
	return httpClient.request(method, uri.path()).then([&](web::http::http_response response) -> pplx::task<web::json::value>
	{
		if (response.status_code() == web::http::status_codes::OK)
		{
			return response.extract_json();
		}
		return pplx::task_from_result(web::json::value());
	});
}

const pplx::task<utility::string_t> ServerManager::retrieveString(const web::uri& uri, web::http::method method) const
{
	web::http::client::http_client httpClient(_uri);

	return httpClient.request(method, uri.path()).then([](web::http::http_response response) -> pplx::task<utility::string_t>
	{
		if (response.status_code() == web::http::status_codes::OK)
		{
			return response.extract_string();
		}
		return pplx::task_from_result(utility::string_t());
	});
}