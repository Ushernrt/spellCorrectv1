 ///
 /// @file    MyTask.cc
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-26 22:35:06
 ///

#ifndef __WD_MYTASK_H__
#define __WD_MYTASK_H__

#include "MyResult.h"
#include "TcpConnection.h"

#include <string.h>

#include <string>
#include <queue>
#include <vector>
#include <set>

using std::priority_queue;
using std::vector;
using std::string;
using std::set;

namespace wd{

struct MyCompare{
	
bool operator()(MyResult a, MyResult b){
	if(a._iDist != b._iDist) return a._iDist < b._iDist;
	else if(a._iFreq != b._iFreq) return a._iFreq > b._iFreq;
	else
		return strcmp(a._word.c_str(), b._word.c_str());
}

};


class MyTask{

public:
	MyTask(const string & queryWord, const TcpConnectionPtr & conn)
	: _queryWord(queryWord)
	, _conn(conn)
	{

	}

	void process(){
		_conn->sendInLoop("not found");
	}

private:
	void queryIndexTable(){
	}

	//计算
	void statistic(set<int> & iset){

	}

	int distance(const string & rhs){
		return 0;
	}

	void response(){
	}

private:
	std::string _queryWord;
	TcpConnectionPtr _conn;
	priority_queue<MyResult, vector<MyResult>, MyCompare> _resultQue;
};

}//end of namespace wd

#endif

