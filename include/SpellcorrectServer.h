 ///
 /// @file    SpellcorrectServer.h
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-26 21:55:01
 ///

#ifndef __WD_CPELLCORRECTSERVER_H__
#define __WD_CPELLCORRECTSERVER_H__

#include "Configuration.h"
#include "TcpServer.h"
#include "Threadpool.h"
#include "MyTask.h"

namespace wd{

class SpellcorrectServer{
public:
	SpellcorrectServer(Configuration & conf)
	: _conf(conf)
	, _tcpServer(8888)
	, _threadpool(4, 10)
	{
		_dict = MyDict::createInstance();
		_dict->init(_conf.getConfigMap()["dictPath"].c_str(),_conf.getConfigMap()["indexPath"].c_str());
		_tcpServer.setConnectionCallback(std::bind(&SpellcorrectServer::onConnection,this,std::placeholders::_1));
		_tcpServer.setMessageCallback(std::bind(&SpellcorrectServer::onMessage,this,std::placeholders::_1));
		_tcpServer.setCloseCallback(std::bind(&SpellcorrectServer::onClose,this,std::placeholders::_1));
	}

	void start(){
		_threadpool.start();
		_tcpServer.start();
	}

	void onConnection(const TcpConnectionPtr & conn){
		cout << conn->toString() << endl;		
		conn->send("hello , welcome to SpellcorrectServer.\r\n");
	}

	void onMessage(const TcpConnectionPtr & conn){
		std::string s(conn->receive());
		
		MyTask task(_dict, s, conn);

		_threadpool.addTask(std::bind(&MyTask::process, task));
		cout << "add task to threadpool" << endl;
	}

	void onClose(const TcpConnectionPtr & conn){
		cout << conn->toString().c_str() << endl;
	}
	

private:
	MyDict * _dict;
	Configuration & _conf;
	TcpServer _tcpServer;
	Threadpool _threadpool;
};


}//end of namespace wd
#endif
