/*
* Copyright(c) 2018 WindSoul Network Technology, Inc. All rights reserved.
*/

/**
* Desc: 字符串工具类
* Author:
* Date: 2018-10-09
* Time: 19:38
*/

#ifndef	__StringUtil_H__
#define	__StringUtil_H__

#if PLATFORM_WINDOWS
#pragma warning(disable:4996)
#endif

#include <string>
#include <vector>

class StringUtil
{
public:

	static void SplitString(std::string str, std::vector<std::string>& params, const char* delim)
	{
		if (str.length() == 0)
		{
			return;
		}

		std::string trimstr = Trim(str);
		if (0 == strcmp("", trimstr.c_str()))
		{
			return;
		}

		char *token = strtok((char*)trimstr.c_str(), delim);		//@TODO 安全检测
		while (token != NULL)
		{
			params.push_back(token);
			token = strtok(NULL, delim);
		}
	}

	static std::string Trim(std::string& str)
	{
		size_t first = str.find_first_not_of(' ');
		size_t last = str.find_last_not_of(' ');
		return str.substr(first, (last - first + 1));
	}
};

#endif
