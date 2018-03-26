 ///
 /// @file    testSplitToolEn.cc
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-26 15:13:09
 ///

#include "../include/SplitToolEn.h"
#include <iostream>
using std::cout;
using std::endl;

int main(){
	vector<string> res;

	wd::SplitToolEn ste;

	res = ste.cut(string("1 2 3 45 6"));
	
	vector<string>::const_iterator it = res.begin();
	
	while(it!=res.end()){
		cout << *it << endl;
		++it;
	}



}
