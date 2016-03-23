#include "stdafx.h"
#include "userInfo.h"

void UserInfo::loadFromJson(const web::json::object& jsonObject)
{
	for (auto iter = jsonObject.cbegin(); iter != jsonObject.cend(); ++iter)
	{
		utility::string_t key = iter->first;
		const web::json::value& value = iter->second;

		//hard coded keys, should be moved into separate data file
		if (key == L"id")
		{
			_id = value.as_integer();
		}
		else if (key == L"name")
		{
			_name = utils::StringUtils::wStringToString(value.as_string());
		}
		else if (key == L"profileIconId")
		{
			_profileIcon = value.as_integer();
		}
		else if (key == L"summonerLevel")
		{
			_summonerLevel = value.as_integer();
		}
	}
}