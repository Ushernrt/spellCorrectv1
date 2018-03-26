 ///
 /// @file    SplitTool.h
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-26 14:37:48
 ///

#ifndef __WD_SPLITOOL_H__
#define __WD_SPLITOOL_H__

#include <vector>
#include <string>

using std::vector;
using std::string;

namespace wd{

class SplitTool{

public:
	SplitTool(){}
	virtual ~SplitTool(){}

	virtual vector<string> cut(const string & sentence) = 0;

};

}//end of namespace
#endif
