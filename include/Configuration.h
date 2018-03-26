 ///
 /// @file    Configuration.cc
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-26 13:49:26
 ///

#ifndef __WD_CONFIGURATION_H__
#define __WD_CONFIGURATION_H__

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <memory>

using std::string;
using std::map;
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;
using std::unique_ptr;

namespace wd{

class Configuration{
public:
	Configuration(const string & filepath)
	: _filepath(filepath)
	{
		
	}

	map<string, string> & getConfigMap(){
		unique_ptr<ifstream> ifs(new ifstream(_filepath.c_str()));
//		ifstream ifs(_filepath.c_str());
		if(!ifs->good()){
			cout << "ifstream open error!" << endl;
			return	_configMap; 
		}

		string line;
		string key;
		string value;
		while(getline(*ifs, line)){
			istringstream iss(line);
			iss >> key;
			iss >> value;

			_configMap[key] = value;
		}
		
		return _configMap;
	}

private:
	string _filepath;
	map<string, string> _configMap;	
};




}//end of namespace wd
#endif
