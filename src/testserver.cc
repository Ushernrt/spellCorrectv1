 ///
 /// @file    testserver.cc
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-25 20:34:18
 ///

#include "../include/SpellcorrectServer.h"
#include "../include/Configuration.h"

#include <iostream>
using std::cout;
using std::endl;



int main(){
	wd::Configuration config("/home/xiu/spellCorrectv2/conf/config")	;

	wd::SpellcorrectServer server(config);

	server.start();
	
	return 0;
}
