#pragma once

typedef int UserId;

struct UserInfo
{
	void loadFromJson(const web::json::object& jsonObject);
	std::string _name = "";
	UserId _id = 0;
	int _profileIcon = 0;
	int _summonerLevel = 0;
};


