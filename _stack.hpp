#ifndef _STACK_HPP
#define _STACK_HPP
using namespace std;
template<typename T>class _stack{
protected:
	class node{
	public:
		T * pt;
		node * nxt;
		node(){
			// cout<<"node()"<<endl;
			pt=nullptr;nxt=nullptr;
		}
		node(const T * _pt){
			// cout<<"node(T * _pt)"<<endl;
			pt=_pt;nxt=nullptr;
		}
		node(T * _pt){
			// cout<<"node(T * _pt)"<<endl;
			pt=_pt;nxt=nullptr;
		}
		node(const node & nn){
			// cout<<"node(const node & nn)"<<endl;
			pt=new T(*(nn.pt));nxt=nullptr;
		}
		void operator = (const node & n)=delete;
		~node(){
			// cout<<"~node()"<<endl;
			if(pt!=nullptr){
				delete pt;
			}
		}
	}* _base,* _top;
	size_t _sz;
public:
	_stack(){
		_base=new node;_top=_base;_sz=0;
	}
	~_stack(){
		node * p=_top;
		while(p!=nullptr){
			node * pre=p;p=p->nxt;
			delete pre;
		}
	}
	_stack<T> & push(const T & t){
		node * _topo=_top;_top=new node(new T(t));_top->nxt=_topo;++_sz;
		return *this;
	}
	T & top(void){
		return *(_top->pt);
	}
	const T & top(void) const {
		return *(_top->pt);
	}
	void pop(void){
		node * pre=_top;_top=_top->nxt;delete pre;--_sz;
	}
	bool empty(void) const {
		return _sz==0;
	}
	size_t size(void) const {
		return _sz;
	}
};

#endif