#ifndef _LIST_HPP
#define _LIST_HPP
template<typename T>class _list;
template<typename T>class _list_node_p;
template<typename T>class _list_node{
public:
	friend _list<T>;
	friend _list_node_p<T>;
protected:
	_list_node * _pre;
	_list_node * _nxt;
	T * _t; // 一开始写的时候写的是void * ，所有后面的调用都使用了强制类型转换。。。纯属当时脑瘫了
	_list_node<T>(_list_node<T> * pre,T * t,_list_node<T> * nxt):_t(t){
		// debug(*t);cout_n;
		// debug(this);debug(pre);debug(nxt);cout_n;
		pre->_nxt=this;this->_pre=pre;
		this->_nxt=nxt;nxt->_pre=this;
	}
	void change_t(T * new_t){
		if(_t!=nullptr){
			delete _t;
		}
		_t=new_t;
	}
public:
	_list_node<T>():_pre(nullptr),_nxt(nullptr),_t(nullptr){}
	_list_node<T>(const _list_node<T> & nn):_pre(nn._pre),_nxt(nn._nxt),_t(nn._t){}
	_list_node<T> & operator = (const _list_node<T> & )=default;
	~_list_node<T>(){
		if(_t!=nullptr){
			// debug(ll(_t));cout_n;
			delete _t;
		}
	}
};
template<typename T>class _list_node_p{
	friend _list<T>;
public:
	typedef _list_node<T> node;
protected:
	node * pn;
	_list_node_p<T>(const node * _pn):pn(_pn){} // const和非const的都应该有一个
	_list_node_p<T>(node * _pn):pn(_pn){}
public:
	_list_node_p<T>():pn(nullptr){}
	_list_node_p<T>(const _list_node_p<T> & lnp):pn(lnp.pn){}
	_list_node_p<T> & operator = (const _list_node_p & lnp){
		pn=lnp.pn;
	}
	~_list_node_p<T>(){};
	T & operator * (void){
		return *pn->_t;
	}
	const T & operator * (void) const {
		return  *pn->_t;
	}
	_list_node_p<T> & operator ++ (void){
		pn=pn->_nxt;return *this;
	}
	_list_node_p<T> operator ++ (int){
		node * pre=pn;pn=pn->_nxt;
		return _list_node_p<T>(pre);
	}
	_list_node_p<T> & operator -- (void){
		pn=pn->_pre;return *this;
	}
	_list_node_p<T> operator -- (int){
		node * pre=pn;pn=pn->_pre;
		return _list_node_p<T>(pre);
	}
	bool operator == (const _list_node_p<T> & lnp) const {
		return pn==lnp.pn;
	}
	bool operator != (const _list_node_p<T> & lnp) const {
		return pn!=lnp.pn;
	}

};
template<typename T>class _list{
// 照搬_deque
// 注意，_list没有预设内存的构造函数，但是设计了迭代器
public:
	typedef _list_node<T> node;
	typedef _list_node_p<T> iterator;
protected:
	node * _front,* _back;
	size_t sz;
public:
	// typedef _list_node iterator;
	_list<T>(){
		_front=new node;_back=new node;
		_front->_nxt=_back;
		_back->_pre=_front;sz=0;
	}
	~_list<T>(){
		node * p=_front, * pre=_front;
		// debug(ll(_front));debug(ll(_back));cout_n;
		// for(_list_node * xp=_front;xp!=nullptr;xp=xp->_nxt){
		// 	debug(ll(xp));
		// }
		// cout_n;
		while(p!=nullptr){
			// debug(ll(p));cout_n;
			pre=p;p=p->_nxt;delete pre;
		}
	}
	const iterator find(const T & t,bool cmp(const T & ,const T &)) const {
	// 返回第一个cmp(t,x)=true的x的位置，查找失败返回false
		node * p=_front->_nxt;
		while(p!=_back){
			if(cmp(t,*p->_t)){
				return iterator(p);
			}
		}
		return end();
	}
	iterator find(const T & t,bool cmp(const T & ,const T &)){
	// 返回第一个cmp(t,x)=true的x的位置，查找失败返回false
		node * p=_front->_nxt;
		while(p!=_back){
			if(cmp(t,*p->_t)){
				return iterator(p);
			}
		}
		return end();
	}

	iterator insert(const T & t,iterator it){ // insert到it之前
		node * p=_front->_nxt;node * tofind=it.pn;
		while(p!=_back && p!=tofind){
			p=p->_nxt;
		}
		if(p==tofind){ // 找到了
			new node(tofind->_pre,t,tofind);++sz;
		}else{ // 没找到
			return end();
		}
	}
	iterator push_back(const T & t){
		// T * pt=new T(t);
		// debug(pt);cout_n;
		new node(_back->_pre,new T(t),_back);++sz;
		return iterator(_back->_pre);
	}
	void pop_back(void){
		// 必须保证至少有一个元素，否则就会爆炸
		node * nn=_back->_pre;
		nn->_pre->_nxt=_back;
		_back->_pre=nn->_pre;
		delete nn;--sz;
	}
	iterator push_front(const T & t){
		new node(_front,new T(t),_front->_nxt);++sz;
		return iterator(_front->_nxt);
	}
	void pop_front(void){
		// 必须保证至少有一个元素，否则就会爆炸
		node * nn=_front->_nxt;
		nn->_nxt->_pre=_front;
		_front->_nxt=nn->_nxt;
		delete nn;--sz;
	}
	_list<T>(const _list<T> & lis){
		_front=new node;_back=new node;
		_front->_nxt=_back;_back->_pre=_front;
		this->operator=(lis);
	}
	void clear(void){
		node * p=_front->_nxt;
		while(p!=_back){
			node * pre=p;p=p->_nxt;delete pre;
		}
		_front->_nxt=_back;_back->_pre=_front;
	}
	_list<T> & operator = (const _list<T> & lis){
		this->clear();
		for(node * p=lis._front->_nxt;p!=lis._back;p=p->_nxt){
			this->push_back(*p->_t);
		}
		return *this;
	}
	void print_all(void prt(const T & )) const {
		// 将队列内容使用prt函数输出
		// 每次调用prt函数之后不会输出空格或者换行，需要手动控制
		// 这个函数最后会也不会输出endl
		node * p=_front->_nxt;
		while(p!=_back){
			prt(*(p->_t));p=p->_nxt;
		}
	}
	size_t erase(const T & tmp,bool (*equals)(const T & ,const T &)){
	// 删除equals(tmp,t)为true的元素，返回删除了几个
		node * p=_front->_nxt;node * pre=_front;
		size_t cnt=0;
		while(p!=_back){
			if(equals(tmp,*p->_t)){
				pre->_nxt=p->_nxt;
				p->_nxt->_pre=pre;
				node * _p=p;
				p=p->_nxt;
				delete _p;
				cnt++;
			}else{
				p=p->_nxt;pre=pre->_nxt;
			}
		}
		sz-=cnt;
		return cnt;
	}
	void traverse(void (*fun)(const T &) ) const {
		node * p=_front->_nxt;
		while(p!=_back){
			fun(*(p->_t));p=p->_nxt;
		}
	}
	void traverse( void (*fun)(T &) ) {
		node * p=_front->_nxt;
		while(p!=_back){
			fun(*(p->_t));p=p->_nxt;
		}
	}

	const iterator begin(void) const {
		return iterator(_front->_nxt);
	}
	iterator begin(void) {
		return iterator(_front->_nxt);
	}
	const iterator end(void) const {
		return iterator(_back);
	}
	iterator end(void){
		return iterator(_back);
	}
	const T & front(void) const {
		return *_front->_nxt->_t;
	}
	T & front(void){
		return *_front->_nxt->_t;
	}
	const T & back(void) const {
		return *_back->_pre->_t;
	}
	T & back(void) {
		return *_back->_pre->_t;
	}
	bool empty(void) const {
		return sz==0;
	}
	size_t size(void) const {
		return sz;
	}
};

#endif
