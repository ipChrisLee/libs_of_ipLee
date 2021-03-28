#ifndef _DEQUE_HPP
#define _DEQUE_HPP
#include "_list.hpp"
template<typename T> class _deque{
// 需要注意，STL的deque不是使用双向队列实现的（估计是因为这么分配内存很慢）
// 这里只是模仿实现了一下接口函数
protected:
	_list<T>lis;
public:
	_deque<T>(){}
	~_deque<T>()=default;
	void push_back(const T & t){
		lis.push_back(t);
	}
	void pop_back(void){
		lis.pop_back();
	}
	void push_front(const T & t){
		lis.push_front(t);
	}
	void pop_front(void){
		lis.pop_front();
	}
	_deque(const _deque<T> & deq):lis(deq.lis){}
	void clear(void){
		lis.clear();
	}
	_deque<T> & operator = (const _deque<T> & deq){
		lis.operator=(deq.lis);
	}
	T & front(void){
		return lis.front();
	}
	const T & front(void) const {
		return lis.front();
	}
	T & back(void){
		return lis.back();
	}
	const T & back(void) const {
		return lis.back();
	}
	bool empty(void) const {
		return lis.empty();
	}
	size_t size(void) const {
		return lis.size();
	}
	void print_all(void prt(const T & )) const { // 从_front向_back
		lis.print_all(prt);
	}
};

#endif
