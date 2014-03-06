#ifndef		STRINGNEW_H
#define		STRINGNEW_H

#include <string>
#include <algorithm>
#include <functional>
#include <cctype>

using namespace std;

class Cstringnew
{
public:
	// 主要用于消除首尾空格
	inline string trim ( string& ss, string _tStr )
	{
		// trim right
		ss.erase ( ss.find_last_not_of (_tStr) + 1 );
		// trim left
		ss.erase ( 0, ss.find_first_not_of (_tStr) );
		return ss;
	}
	inline string& lTrim ( string& ss, string _tStr )
	{
		ss.erase ( 0, ss.find_first_not_of (_tStr) );
		return ss;
	}
	inline string& rTrim ( string& ss, string _tStr )
	{
		ss.erase ( ss.find_last_not_of (_tStr) + 1 );
		return ss;
	}

};

#endif