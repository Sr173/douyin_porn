#pragma once
#include <sstream>
#include <vector>
#include <algorithm>

namespace std
{
	template <class T>
	std::vector<T> split(const T& data,typename T::value_type a)
	{
		std::vector<T> result;
		basic_stringstream<T::value_type , char_traits<T::value_type>, allocator<T::value_type>> stream(data);
		T buffer;
		
		while (std::getline(stream, buffer, a)) {
			result.push_back(buffer);
		}
		
		return std::move(result);
	}

	template <class T>
	vector<T> split(const T& s, const T& delimiter)
	{
		size_t pos_start = 0, pos_end, delim_len = delimiter.length();
		T token;
		vector<T> res;

		while ((pos_end = s.find(delimiter, pos_start)) != T::npos) {
			token = s.substr(pos_start, pos_end - pos_start);
			pos_start = pos_end + delim_len;
			res.push_back(token);
		}

		res.push_back(s.substr(pos_start));
		return res;
	}
	
	template <class T>
	void string_tolower(T& string)
	{
		std::transform(string.begin(), string.end(), string.begin(), [](typename T::value_type val)->typename T::value_type
		{
			return val >= 'A' && val <= 'Z' ? val -= ('A' - 'a') : val;
		});
	}

	template <class T>
	T string_toupper(T& string)
	{
		std::transform(string.begin(), string.end(), string.begin(), [](typename T::value_type val)->typename T::value_type
			{
				return val >= 'a' && val <= 'z' ? val += ('A' - 'a') : val;
			});
		return string;
	}

	template <class T>
	int compare_no_case(T a, T b)
	{
		string_tolower(a);
		string_tolower(b);
		return a.compare(b);
	}
}