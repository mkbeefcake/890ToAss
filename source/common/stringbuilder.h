﻿#pragma once

//----------------------------------------------------------------------------------------
//	Copyright © 2004 - 2020 Tangible Software Solutions, Inc.
//	This class can be used by anyone provided that the copyright notice remains intact.
//
//	This class is used to replace the .NET StringBuilder in C++.
//----------------------------------------------------------------------------------------
#include <string>
#include <cstring>
#include <sstream>

class StringBuilder
{
private:
	std::string privateString;

public:
	StringBuilder()
	{
	}

	StringBuilder(const std::string &initialString)
	{
		privateString = initialString;
	}

	StringBuilder(std::size_t capacity)
	{
		ensureCapacity(capacity);
	}

	StringBuilder(const std::string &initialString, std::size_t capacity)
	{
		privateString = initialString;
		ensureCapacity(capacity);
	}

	char operator [](std::size_t index)
	{
		if (index >= privateString.length())
			return 0;

		return privateString[index];
	}

	StringBuilder *append(const std::string &toAppend)
	{
		privateString += toAppend;
		return this;
	}

	template<typename T>
	StringBuilder *append(const T &toAppend)
	{
		privateString += toString(toAppend);
		return this;
	}

	StringBuilder *appendLine()
	{
		privateString += "\r\n";
		return this;
	}

	StringBuilder *appendLine(const std::string &toAppend)
	{
		privateString += toAppend + "\r\n";
		return this;
	}

	StringBuilder *insert(std::size_t position, const std::string &toInsert)
	{
		if (position >= privateString.length())
			privateString += toInsert;
		else 
			privateString.insert(position, toInsert);

		return this;
	}

	template<typename T>
	StringBuilder *insert(std::size_t position, const T &toInsert)
	{
		if (position >= privateString.length())
			privateString += toString(toInsert);
		else 
			privateString.insert(position, toString(toInsert));

		return this;
	}

	std::string toString()
	{
		return privateString;
	}

	std::string toString(std::size_t start, std::size_t length)
	{
		if (start >= privateString.length())
			return "";
		else
			return privateString.substr(start, length);
	}

	std::size_t length()
	{
		return privateString.length();
	}

	void setLength(std::size_t newLength)
	{
		privateString.resize(newLength);
	}

	std::size_t capacity()
	{
		return privateString.capacity();
	}

	void ensureCapacity(std::size_t minimumCapacity)
	{
		privateString.reserve(minimumCapacity);
	}

	std::size_t maxCapacity()
	{
		return privateString.max_size();
	}

	void clear()
	{
		privateString.clear();
	}

	StringBuilder *remove(std::size_t start, std::size_t length)
	{
		if (start >= privateString.length())
			return this;

		privateString.erase(start, length);
		privateString.resize(std::strlen(privateString.c_str()));
		return this;
	}

	StringBuilder *replace(const std::string &oldString, const std::string &newString)
	{
		if (oldString.empty())
			return this;

		std::size_t pos = 0;
		while ((pos = privateString.find(oldString, pos)) != std::string::npos)
		{
			privateString.replace(pos, oldString.length(), newString);
			pos += newString.length();
		}
		privateString.resize(std::strlen(privateString.c_str()));
		return this;
	}

private:
	template<typename T>
	static std::string toString(const T &subject)
	{
		std::ostringstream ss;
		ss << subject;
		return ss.str();
	}
};
