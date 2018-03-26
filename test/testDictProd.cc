 ///
 /// @file    testDictProd.cc
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-26 16:03:00
 ///

#include "../include/DictProducer.h"
#include "../include/Configuration.h"
#include <iostream>
using std::cout;
using std::endl;

int main(int argc , char **argv){

	if(argc != 2){
		cout << "error args" << endl;
		return -1;
	}
	string s(argv[1]);	
	map<string,string> res;
	wd::Configuration conf(s);
	res = conf.getConfigMap();

	wd::DictProducer dict(res["yuliaoku"]);
	dict.build_dict();
	dict.store_dict("/home/xiu/spellCorrect/dict/dict.txt");
	dict.build_index();
	dict.store_index("/home/xiu/spellCorrect/dict/index.txt");
	return 0;

}

