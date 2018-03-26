 ///
 /// @file    testMydict.cc
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-26 21:24:31
 ///

#include "../include/Mydict.h"
#include "../include/Configuration.h"
#include <unistd.h>


#include <iostream>
using std::cout;
using std::endl;

int main()
{
	string conf = "../conf/config";

	wd::Configuration config(conf);
	
	wd::MyDict * myd = wd::MyDict::createInstance();

	map<string,string> con = config.getConfigMap();

	myd->init(con["dictPath"].c_str(),con["indexPath"].c_str());

	vector<pair<string,int>> dict =  myd->getDict();
		
	map<string, set<int>> index = myd->getIndexTable();
	
	set<int> res = index["a"];

	set<int>::iterator it = res.begin();
	
	cout << "a" << endl;

	::sleep(3);

	while(it != res.end()){
		cout << dict[*it].first << ":" << dict[*it].second << endl;


		++it;
	}


	return 0;
}
