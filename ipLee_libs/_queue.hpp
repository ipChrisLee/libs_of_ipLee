#ifndef _QUEUE_HPP
#define _QUEUE_HPP
#include "_deque.hpp"
template<typename T> class _queue{ // 这玩意实际上如果是const的话就一定是空的
protected:
	_deque<T> deq;
public:
	_queue()=default;
	_queue(const _queue & q):deq(q.deq){}
	_queue & operator = (const _queue & q){
		deq=q.deq;
	}
	~_queue()=default;
	const T & front(void) const {
		return deq.front();
	}
	T & front(void){
		return deq.front();
	}
	void push(const T & t){
		deq.push_back(t);
	}
	bool empty(void) const {
		return deq.empty();
	}
	void clear(void){
		deq.clear();
	}
	size_t size(void) const {
		return deq.size();
	}
	void pop(void){
		deq.pop_front();
	}
	void print_all(void prt(const T & )) const { // 从_front向_back
		deq.print_all(prt);
	}
};

#endif
