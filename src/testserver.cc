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



int main(int argc, char *argv[]){
	
	if(argc!=2){
		puts("./server.ext ../conf/config\n");
		return -1;
	}

	wd::Configuration config(argv[1]);

	wd::SpellcorrectServer server(config);

	server.start();
	
	return 0;
}
