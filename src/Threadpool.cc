 ///
 /// @file    Threadpool.cc
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-25 15:42:47
 ///

#include "../include/Threadpool.h"
#include "../include/Thread.h"
#include <unistd.h>
#include <iostream>
namespace wd{

Threadpool::Threadpool(size_t threadNum, size_t queSize)
: _threadNum(threadNum)
, _queSize(queSize)
, _taskque(_queSize)
, _isExit(false)
{
	_threads.reserve(_threadNum);
}

Threadpool::~Threadpool(){
	if(!_isExit)
		stop();
}

void Threadpool::start(){
	for(size_t idx = 0; idx != _threadNum; ++idx){
		unique_ptr<Thread> up(new Thread(std::bind(&Threadpool::threadFunc, this)));
		_threads.push_back(std::move(up));
	}

	for(auto & subThread : _threads){
		subThread->start();
	}
}

void Threadpool::stop(){
	if(!_isExit){
		while(!_taskque.empty()){
			::sleep(2);
		}

		_isExit = true;

		_taskque.wakeup();

		for(auto & subThread : _threads){
			subThread->join();
		}
	}
}

void Threadpool::addTask(Task task){
	_taskque.push(task);
}

Threadpool::Task Threadpool::getTask(){
	return _taskque.pop();
}

void Threadpool::threadFunc(){
	while(!_isExit){
		Task task = getTask();
		if(task)
			task();
		std::cout << "task completed" << std::endl;
	}

}



}//end of namespace wd

