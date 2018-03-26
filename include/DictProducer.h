 ///
 /// @file    DictProducer.h
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-26 15:25:58
 ///

#ifndef __WD_DICTPRODUCER_H__
#define __WD_DICTPRODUCER_H__
#include "SplitTool.h"
#include "SplitToolEn.h"
#include "Configuration.h"

#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <set>

using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::string;
using std::unique_ptr;
using std::ofstream;
using std::set;

namespace wd{

class DictProducer{
public:
	DictProducer(const string & dir)
	:_dir(dir)
	,_splitTool(new SplitToolEn())
	{
		get_files();
	}

	DictProducer(const string & dir, SplitTool * splitTool)
	: _dir(dir)
	, _splitTool(splitTool){
		get_files();
	}

	void show_files() const{
		for(size_t i = 0;i < _files.size(); ++i){
			cout << _files[i] << endl;
		}
	}

	void build_dict(){
		vector<string>::iterator it = _files.begin();

		while(it != _files.end()){
			unique_ptr<ifstream> ifs(new ifstream(*it));
			if(!ifs->good()){
				cout << "ifstream error" << endl;
				exit(EXIT_FAILURE);
			}
			string line;
			size_t i;
			vector<string> ret;
			while(getline(*ifs, line)){
				for(i = 0;i != line.size();++ i){
					if(!isalpha(line[i])){
						line[i] = ' ';
					}
				}

				ret = _splitTool->cut(line);
				for(i = 0;i != ret.size(); ++ i){
					++_dict[ret[i]];
				}
			}
			cout << *it << " build completed " << endl;
			++ it;
		}
	}

	void build_cn_dict(){
	}
	
	void build_index(){
		size_t idx ;
		string word;
		char alpha;
		size_t idxI = 0;
		for(auto & item : _dict ){
			word = item.first;
			for(idx = 0;idx != word.size(); ++ idx){
				alpha = tolower(word[idx]);
				_index[alpha].insert(idxI);
			}
			++ idxI;
		}
		cout << "create index file completed" << endl;
	}
	
	void store_index(const char * filepath){
		unique_ptr<ofstream> ofs(new ofstream(filepath));
		if(!ofs->good()){
			cout << "ofstream error" << endl;
			return;
		}

		for(auto & item : _index){
			*ofs << item.first << " ";
			for(auto & item2 : item.second){
				*ofs << item2 << " " ;
			}
			*ofs << endl;
		}
		cout << "write index completed" << endl;
	}

	void store_dict(const char * filepath){
		unique_ptr<ofstream> ofs(new ofstream(filepath));
		if(!ofs->good()){
			cout << "ofstream error" << endl;
			return;
		}
		for(auto & item : _dict){
			*ofs << item.first << " " << item.second << endl;
		}

		cout << filepath << " write completed" << endl;
	}

	void show_dict() const{
		for(auto & item : _dict){
			cout << item.first << ":" << item.second << endl;
		}
	}


private:
	void push_dict(const string & word){
	}

	void get_files(){
		DIR * dir;	
	
		struct dirent * ptr;

		if((dir = opendir(_dir.c_str())) == NULL){
			perror("oper dir error");
			exit(1);
		}
		
		while((ptr = readdir(dir)) != NULL){
			if(strcmp(ptr->d_name,".") == 0 || strcmp(ptr->d_name, "..") == 0){
				continue;
			}else if(ptr->d_type == 8){//文件
				string filename = string(_dir)+ string(ptr->d_name);
				_files.push_back(filename);
			}else if(ptr->d_type == 10){//链接文件
				continue;
			}else if(ptr->d_type == 4){//文件夹
				continue;
			}

		}
		closedir(dir);
	}

private:
	string _dir;
	vector<string> _files;
	map<string, int> _dict;
	SplitTool * _splitTool;
	map<char, set<int> > _index;
};

}//end of namespace wd
#endif
