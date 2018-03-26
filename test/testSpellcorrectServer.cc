 ///
 /// @file    testSpellcorrectServer.cc
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-26 23:26:35
 ///

#include "../include/SpellcorrectServer.cc"
#include "../include/Configuration.h"

#include <iostream>
using std::cout;
using std::endl;


int main(){
	wd::Configuration config("../conf/config");

	wd::SpellcorrectServer server(config);

	server.start();


}
