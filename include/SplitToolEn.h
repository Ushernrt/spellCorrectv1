 ///
 /// @file    SplitToolEn.h
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-26 14:41:20
 ///
 
#ifndef _WD_SPLITTOOLEN_H__
#define _WD_SPLITTOOLEN_H__

#include "SplitTool.h"

#include <iostream>
#include <sstream>
using std::cout;
using std::endl;
using std::istringstream;

namespace wd{

class SplitToolEn
: public SplitTool
{
public:	
	SplitToolEn(){}

	~SplitToolEn(){}

	vector<string> cut(const string & sentence){
		vector<string> res ;
		res.reserve(10);

		string word;
		istringstream iss(sentence);
		while(iss >> word){
			res.push_back(word);
		}

		return res;
	}
};

}//end of namespace wd
#endif
