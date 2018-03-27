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
	{
		_tcpServer.setConnectionCallback(&(SpellcorrectServer::onConnection));
		_tcpServer.setMessageCallback(SpellcorrectServer::onMessage);
		_tcpServer.setCloseCallback(&onClose);
	}

	void start(){
		_threadpool.start();
		_tcpServer.start();
	}

	static void onConnection(const TcpConnectionPtr & conn){
		cout << conn->toString() << endl;		
		conn->send("hello , welcome to SpellcorrectServer.\r\n");
	}

	static void onMessage(const TcpConnectionPtr & conn){
		std::string s(conn->receive());
		
		MyTask task(s, conn);

		_threadpool.addTask(std::bind(&MyTask::process, task));
		cout << "add task to threadpool" << endl;
	}

	static void onClose(const TcpConnectionPtr & conn){
		cout << conn->toString().c_str() << endl;
	}
	

private:
	Configuration & _conf;
	TcpServer _tcpServer;
	static Threadpool _threadpool;
};

Threadpool SpellcorrectServer::_threadpool(4,10);

}//end of namespace wd
#endif
