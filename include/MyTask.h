 ///
 /// @file    MyTask.cc
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-26 22:35:06
 ///

#ifndef __WD_MYTASK_H__
#define __WD_MYTASK_H__

#include "MyResult.h"
#include "TcpConnection.h"
#include "Mydict.h"

#include <string.h>

#include <string>
#include <queue>
#include <vector>
#include <set>
#include <sstream>

using std::priority_queue;
using std::vector;
using std::string;
using std::set;
using std::ostringstream;

namespace wd{

struct MyCompare{
	
bool operator()(MyResult a, MyResult b){
	if(a._iDist != b._iDist) return a._iDist > b._iDist;
	else if(a._iFreq != b._iFreq) return a._iFreq < b._iFreq;
	else
		return (-1)*strcmp(a._word.c_str(), b._word.c_str());
}

};


class MyTask{

public:
	MyTask(MyDict * dict, const string & queryWord, const TcpConnectionPtr & conn)
	: _dict(dict)
	, _queryWord(queryWord)
	, _conn(conn)
	{

	}

	void process(){
		queryIndexTable();
		
		response();
		// _conn->sendInLoop("not found");
	}

private:
	
	string chartostring(char x){
		
		ostringstream oss;
		oss << x;
		return oss.str();

	}

	void queryIndexTable(){
		size_t len = _queryWord.size();
		if(len <= 0) return ;
		for(size_t i = 0; i != len;++ i){
			set<int> iset = _dict->getIndexTable()[chartostring(_queryWord[i])];
			statistic(iset);
		}
		cout << "query index table completed" << endl;
	}

	//计算
	void statistic(set<int> & iset){
		MyResult res;
		
		vector<pair<string, int>> dict = _dict->getDict();
		for(auto & item : iset){
			res._word = dict[item].first;
			res._iFreq = dict[item].second;
			res._iDist = miniDist(res._word, _queryWord);

			_resultQue.push(res);
		}
	}

	int miniDist(const string & v1, const string & v2){


		return 0;		
	}

	int distance(const string & rhs){
		




		return 0;
	}

	void response(){
		string res ;
		for(int i = 0;i != 5;++ i){
			res += _resultQue.top()._word;
			res += "\n";
			_resultQue.pop();
		}

		_conn->sendInLoop(res);
	}

private:
	MyDict * _dict;
	std::string _queryWord;
	TcpConnectionPtr _conn;
	priority_queue<MyResult, vector<MyResult>, MyCompare> _resultQue;
};

}//end of namespace wd

#endif

