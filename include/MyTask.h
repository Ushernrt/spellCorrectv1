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
#include <ctype.h>

#include <string>
#include <queue>
#include <vector>
#include <set>
#include <sstream>
#include <bitset>

using std::priority_queue;
using std::vector;
using std::string;
using std::set;
using std::ostringstream;
using std::bitset;

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
	}

private:
	
	string chartostring(char x){
		
		ostringstream oss;
		oss << x;
		return oss.str();

	}

	void queryIndexTable(){
		size_t len = _queryWord.size() - 1;
		_isUsed.reset(); 
		if(len <= 0) return ;
		for(size_t i = 0; i != len;++ i){
			set<int> iset = _dict->getIndexTable()[chartostring(::tolower(_queryWord[i]))];
						
			statistic(iset);
		}
		cout << "query index table completed" << endl;
	}

	//计算
	void statistic(set<int> & iset){
		MyResult res;
	
		vector<pair<string, int>> dict = _dict->getDict();
		for(auto & item : iset){
						
			if(!_isUsed[item]){

				res._word = dict[item].first;
				res._iFreq = dict[item].second;
				res._iDist = miniDist(res._word, _queryWord);
				//cout << res._word << endl;
				_resultQue.push(res);
				_isUsed[item] = 1;
			}
		}

	}

	int min(int x, int y){
		return x > y ? y : x;
	}

	int miniDist(const string & v1, const string & v2){
		int n = v1.length();
		int m = v2.length();

		vector<vector<int> > dp(n + 1);

		for(int i = 0;i <= n;++ i){
			dp[i].resize(m + 1);
		}

		dp[0][0] = 0;

		for(int i = 1;i <= n;++ i){
			dp[i][0] = i;
		}
		for(int j = 1;j <= m;++ j){
			dp[0][j] = j;
		}
		 
		for(int i = 1;i <= n;++ i){
			for(int j = 1;j <= m;++ j){
				dp[i][j] = min(dp[i-1][j]+1, dp[i][j-1]+1);
				if(v1[i-1] == v2[j - 1])
					dp[i][j] = min(dp[i-1][j-1], dp[i][j]);
				else 
					dp[i][j] = min(dp[i][j], dp[i-1][j-1]+1);
			}
		}

		return dp[n][m];
	}

	int distance(const string & rhs){
		
		return miniDist(_queryWord, rhs);
		
	}

	void response(){
#if 0	
		for(size_t i = 0; i <= 8; ++ i){
			cout << _resultQue.top()._word << endl;
			_resultQue.pop();
		}
#endif
		cout << _resultQue.size() << endl;
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
	bitset<50000> _isUsed;
};

}//end of namespace wd

#endif

