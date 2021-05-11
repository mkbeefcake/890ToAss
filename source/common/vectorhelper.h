#pragma once

//----------------------------------------------------------------------------------------
//	Copyright © 2004 - 2020 Tangible Software Solutions, Inc.
//	This class can be used by anyone provided that the copyright notice remains intact.
//
//	This class is used to assist conversion of lists to vectors.
//----------------------------------------------------------------------------------------
#include <vector>
#include <algorithm>
#include <stdexcept>

class VectorHelper
{
public:
	template<typename T>
	static int indexOf(std::vector<T> &list, T item)
	{
		typename std::vector<T>::iterator it = std::find(list.begin(), list.end(), item);
		if (it != list.end())
			return std::distance(list.begin(), it);
		else
			return -1;
	}

	template<typename T>
	static int indexOf(std::vector<T>& list, T item, int index)
	{
		if (index <= (int)list.size())
		{
			typename std::vector<T>::iterator it = std::find(list.begin() + index, list.end(), item);
			if (it != list.end())
				return std::distance(list.begin(), it);
			else
				return -1;
		}
		else
			throw std::runtime_error("The 'index' parameter is greater than the vector size.");
	}

	template<typename T>
	static int lastIndexOf(std::vector<T> &list, T item)
	{
		typename std::vector<T>::reverse_iterator it = std::find(list.rbegin(), list.rend(), item);
		if (it != list.rend())
			return std::distance(it, list.rend()) - 1;
		else
			return -1;
	}

	template<typename T>
	static int lastIndexOf(std::vector<T>& list, T item, int index)
	{
		if (index < (int)list.size())
		{
			typename std::vector<T>::reverse_iterator it = std::find(list.rbegin() + (list.size() - index - 1), list.rend(), item);
			if (it != list.rend())
				return std::distance(it, list.rend()) - 1;
			else
				return -1;
		}
		else
			throw std::runtime_error("The 'index' parameter should be less than the vector size.");
	}
};
