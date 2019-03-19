 ///
 /// @file    Mydict.h
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-26 20:33:54
 ///

#ifndef __WD_MYDICT_H__
#define __WD_MYDICT_H__

#include <stdlib.h>

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <fstream>
#include <memory>
#include <sstream>

using std::istringstream;
using std::ifstream;
using std::unique_ptr;
using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::set;
using std::pair;
using std::string;

namespace wd{

class MyDict{
public:
	static MyDict * createInstance(){
		if(!_pInstance){
			_pInstance = new MyDict;
			::atexit(destroy);
		}
		return _pInstance;
	}

	static void destroy(){
		if(_pInstance)
			delete _pInstance;
	}

	

	void init(const char * dictPath,const char * indexPath){
	
		unique_ptr<ifstream> ifsDict(new ifstream(dictPath));
		if(!ifsDict->good()){
			cout << "ifstream error dictpath" << endl;
			cout << dictPath << endl;
			return;
		}
		unique_ptr<ifstream> ifsIndex(new ifstream(indexPath));
		if(!ifsIndex->good()){
			cout << "ifstream error indexpath" << endl;
			cout << indexPath << endl;
			return ;
		}
		string line;
		string key;
		string value;
		while(getline(*ifsDict, line)){
			istringstream iss(line);
			iss >> key >> value;

			_dict.push_back(make_pair(key,atoi(value.c_str())));
		}

		while(getline(*ifsIndex, line)){
			istringstream iss(line);
			iss >> key;
			while(iss >> value){
				_index_table[key].insert(atoi(value.c_str()));
			}
		}

		cout << "init completed " << endl;
	}

	vector<pair<string,int>> & getDict(){
		return _dict;
	}

	map<string, set<int>> & getIndexTable(){
		return _index_table;
	}


private:
	MyDict(){}
	~MyDict(){}
private:
	vector<pair<string,int>> _dict;
	map<string, set<int>> _index_table;
	
	static MyDict * _pInstance;
};

MyDict * MyDict::_pInstance = createInstance();

}//end of namespace wd
#endif
