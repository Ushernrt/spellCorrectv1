 ///
 /// @file    testConfiguration.cc
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-26 14:18:19
 ///

#include "../include/Configuration.h"


int main(int argc, char **argv){
	if(2 != argc){
		cout << "error args" << endl;
		return -1;
	}
	string file(argv[1]);
	wd::Configuration conf(file);
	map<string, string> res = conf.getConfigMap();

	map<string, string>::iterator it = res.begin();

	while(it != res.end()){
		cout << it->first << "->>" << it->second << endl;
		++ it;
	}
	
	return 0;
}

