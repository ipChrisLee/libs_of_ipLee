#ifndef _SET_HPP
#define _SET_HPP
#include "_algo.hpp"
#include "_pair.hpp"

template<typename T,class _less_cmp=_less<T> >class _AVLTree;
template<typename T,class _less_cmp=_less<T> >class _AVLTree_node_p;

template<typename T,class _less_cmp=_less<T> >class _AVLTree_node{
	friend _AVLTree<T,_less_cmp>;
	friend _AVLTree_node_p<T,_less_cmp>;
protected:
	T * pkey;
	// 这里如果写T*完全没问题
	// 不过要注意base的pkey=nullptr，写pkey=new T()会强制T有默认构造函数
	_AVLTree_node<T,_less_cmp> * fa, * ls, * rs;
	int hgh; // 高度
public:
	_AVLTree_node(){ // 默认构造函数用来构造根
		pkey=nullptr;fa=ls=rs=nullptr;hgh=1;
	}
	_AVLTree_node(const T & _key,const int _hgh=1,_AVLTree_node<T,_less_cmp> * _fa=nullptr,
		_AVLTree_node<T,_less_cmp> * _ls=nullptr,_AVLTree_node<T,_less_cmp> * _rs=nullptr):
		fa(_fa),ls(_ls),rs(_rs),hgh(_hgh){
			pkey=new T(_key);
	}
	_AVLTree_node(const _AVLTree_node<T,_less_cmp> & )=delete;
	_AVLTree_node & operator = (const _AVLTree_node<T,_less_cmp> & nn)=delete;
	/*
	{
		pkey=nn.pkey;fa=nn.fa;ls=nn.ls;rs=nn.rs;hgh=nn.hgh;
		return *this;
	}
	*/
	~_AVLTree_node(){
		if(pkey!=nullptr){
			delete pkey;
		}
	}
};
template<typename T,class _less_cmp>class _AVLTree_node_p{
public:
	friend _AVLTree<T,_less_cmp>;
protected:
	typedef _AVLTree_node<T,_less_cmp> node;
	node * pn;

	_AVLTree_node_p(const _AVLTree_node<T,_less_cmp> * _pn){
		pn=_pn;
	}
	_AVLTree_node_p(_AVLTree_node<T,_less_cmp> * _pn){
		pn=_pn;
	}
public:
	_AVLTree_node_p():pn(nullptr){}
	_AVLTree_node_p(const _AVLTree_node_p<T,_less_cmp> & _p){
		pn=_p.pn;
	}
	~_AVLTree_node_p(){}
	_AVLTree_node_p<T,_less_cmp> & operator = (const _AVLTree_node_p<T,_less_cmp> & _p){
		pn=_p.pn;return *this;
	}
	bool operator == (const _AVLTree_node_p<T,_less_cmp> & _p) const {
		return pn==_p.pn;
	}
	bool operator != (const _AVLTree_node_p<T,_less_cmp> & _p) const {
		return pn!=_p.pn;
	}
	const T & operator * (void) const {
		return *pn->pkey;
	}
	_AVLTree_node_p<T,_less_cmp> & operator ++(void){
		if(pn->rs!=nullptr){
			pn=pn->rs;
			while(pn->ls!=nullptr){
				pn=pn->ls;
			}
		}else{
			while(pn->pkey!=nullptr && pn->fa->rs==pn ){
			// 没有跳到顶并且pn是父亲的右儿子
				pn=pn->fa;
			}
			pn=(pn->pkey==nullptr)?pn:pn->fa;
		}
		return *this;
	}
	_AVLTree_node_p<T,_less_cmp> operator ++(int){
		node * nown=pn;
		(*this).operaotr++();
		return _AVLTree_node_p<T,_less_cmp>(nown);
	}
	_AVLTree_node_p<T,_less_cmp> & operator --(void){ // --没有经过实验
		if(pn->ls!=nullptr){
			pn=pn->ls;
			while(pn->rs!=nullptr){
				pn=pn->rs;
			}
		}else{
			while(pn->pkey!=nullptr && pn->fa->ls==pn ){
			// 没有跳到顶并且pn是父亲的左儿子
				pn=pn->fa;
			}
			pn=(pn->pkey==nullptr)?pn:pn->fa;
		}
		return *this;
	}
	_AVLTree_node_p<T,_less_cmp> operator --(int){
		node * nown=pn;
		(*this).operaotr--();
		return _AVLTree_node_p<T,_less_cmp>(nown);
	}
};
template<typename T,class _less_cmp>class _AVLTree{
public:
	typedef _AVLTree_node<T,_less_cmp> node;
	typedef _AVLTree_node_p<T,_less_cmp> iterator;
protected:
	node * base;
	int sz;
	_less_cmp cmp;
	bool equals(const T & key1,const T & key2){
		return (!cmp(key1,key2))&&(!cmp(key2,key1));
	}
	int height(const node * nn) const {
		// debug("height");cout_n;
		return nn==nullptr?0:nn->hgh;
	}
	void count_hgh(node * nn) const {
		// nn->hgh=_max<int>(nn->ls==nullptr?0:nn->ls->hgh,nn->rs==nullptr?0:nn->rs->hgh)+1;
		if(nn==nullptr){
			return;
		}
		// debug("count_hgh");cout_n;
		nn->hgh=_max<int>(height(nn->ls),height(nn->rs))+1;
	}
	void rotateL(node * nn) const { // 能保证nn、nn->fa、nn->rs是存在的
		node * nnfa=nn->fa, * nnrs=nn->rs;
		if(nnfa->ls==nn){nnrs->fa=nnfa;nnfa->ls=nnrs;}
		if(nnfa->rs==nn){nnrs->fa=nnfa;nnfa->rs=nnrs;}
		nn->rs=nnrs->ls;if(nnrs->ls!=nullptr){nnrs->ls->fa=nn;}
		nnrs->ls=nn;nn->fa=nnrs;
		count_hgh(nn);count_hgh(nnrs);count_hgh(nnfa);
	}
	void rotateR(node * nn) const { // 能保证nn、nn->fa、nn->ls是存在的
		node * nnfa=nn->fa, * nnls=nn->ls;
		if(nnfa->ls==nn){nnls->fa=nnfa;nnfa->ls=nnls;}
		if(nnfa->rs==nn){nnls->fa=nnfa;nnfa->rs=nnls;}
		nn->ls=nnls->rs;if(nnls->rs!=nullptr){nnls->rs->fa=nn;}
		nnls->rs=nn;nn->fa=nnls;
		count_hgh(nn);count_hgh(nnls);count_hgh(nnfa);
	}
	void balance(node * nn){ // 保证nn存在
		node * nown=nn;
		if(height(nn->ls)>=height(nn->rs)+2){
			nown=nown->ls; // 保证nown存在
			if(height(nown->ls)>=height(nown->rs)){ // LL
				rotateR(nn);
			}else{ // LR
				rotateL(nown);
				rotateR(nn);
			}
		}else if(height(nn->ls)+2<=height(nn->rs)){
			nown=nown->rs; // 保证nown存在
			if(height(nown->rs)>=height(nown->ls)){ // RR
				rotateL(nn);
			}else{ // RL
				rotateR(nown);
				rotateL(nn);
			}
		}
	}
	const T & keyval(const node * nn) const {return *(nn->pkey);}
	T & keyval(node * nn) {return *(nn->pkey);}
	const T & keyval(const T * pk) const {return *(pk);}
	T & keyval(T * pk){return *(pk);}
public:
	_AVLTree():sz(0),cmp(){
		base=new node();
	}
	iterator insert(const T & tval){
		node * pnew;
		node * nown=base->ls;node * pren=base;
		int dir=-1; // 表示方向
		while(nown!=nullptr){
			if(equals(tval,keyval(nown))){
				return iterator(nown);
			}
			pren=nown;
			if(cmp(tval,keyval(nown))){ // tval<nown->key
				nown=nown->ls;dir=0;
			}else{
				nown=nown->rs;dir=1;
			}
		}
		if(dir==0){ // 应该插入到pren的左边
			pren->ls=pnew=new node(tval,1,pren);
		}else if(dir==1){
			pren->rs=pnew=new node(tval,1,pren);
		}else if(dir==-1){
			pren->ls=pren->rs=pnew=new node(tval,1,pren);
		}
		nown=pren;
		while(nown!=base){
			balance(nown);
			nown=nown->fa;
		}
		count_hgh(base);
		++sz;
		return iterator(pnew);
	}

	const iterator find(const T & val) const {
		node * nown=base->ls;
		while( nown!=nullptr && !eqauls(keyval(nown),val) ){
			// 这里已经排除了已经找到的情况
			if(cmp(val,keyval(nown))){
				nown=nown->ls;
			}else{
				nown=nown->rs;
			}
		}
		return nown==nullptr?end():iterator(nown);
	}
	iterator find(const T & val) {
		node * nown=base->ls;
		while( nown!=nullptr && !equals(keyval(nown),val) ){
			// 这里已经排除了已经找到的情况
			// debug(keyval(nown));debug(val);cout_n;
			if(cmp(val,keyval(nown))){
				nown=nown->ls;
			}else{
				nown=nown->rs;
			}
		}
		return nown==nullptr?end():iterator(nown);
	}

	bool erase(iterator nn){
		node * pn=nn.pn;int dir=-1;
		if(pn==nullptr || pn->pkey==nullptr){ // 查到不存在的结点了
			return false;
		}
		node * nown=base->ls;
		while(nown!=nullptr && nown!=pn){
			if(cmp(keyval(pn),keyval(nown))){
				nown=nown->ls;dir=0;
			}else{
				nown=nown->rs;dir=1;
			}
		}
		if(nown==nullptr){
			return false;
		}
		// 找到节点了，此时nown=pn
		// 删除节点，记得让父亲指向空
		// 这个if-elseif执行完之后应该：
		// nown指向第一个需要被平衡的结点，并且这个结点以下的内容已经被处理过
		// pn指向需要被删除的结点
		if(pn->ls==nullptr && pn->rs==nullptr){ // 被删节点为叶子结点
			if(dir==0){
				nown->fa->ls=nullptr;
			}else if(dir==1){
				nown->fa->rs=nullptr;
			}else{
				nown->fa->ls=nown->fa->rs=nullptr;
			}
			pn=nown;nown=nown->fa;
		}else if(pn->ls!=nullptr){ // 有左子树就找左子树最大和它交换
			nown=pn->ls;dir=0;
			while(nown->rs!=nullptr){
				nown=nown->rs;dir=1;
			}
			_swap<T*>(pn->pkey,nown->pkey);
			if(dir==0){
				nown->fa->ls=nown->ls;
			}else if(dir==1){
				nown->fa->rs=nown->ls;
			}else{
				// dir==-1是不可能的
			}
			if(nown->ls!=nullptr){nown->ls->fa=nown->fa;}
			pn=nown;nown=nown->fa;
		}else if(pn->rs!=nullptr){ // 有右子树就找右子树最小和它交换
			nown=pn->rs;dir=1;
			while(nown->ls!=nullptr){
				nown=nown->ls;dir=0;
			}
			_swap<T*>(pn->pkey,nown->pkey);
			if(dir==0){
				nown->fa->ls=nown->rs;
			}else if(dir==1){
				nown->fa->rs=nown->rs;
			}else{
				// dir==-1是不可能的
			}
			if(nown->rs!=nullptr){nown->rs->fa=nown->fa;}
			pn=nown;nown=nown->fa;
		}
		while(nown!=base){ // 这里不能包括base！
			balance(nown);
			nown=nown->fa;
		}
		count_hgh(base);
		delete pn;
		--sz;
		return true;
	}
	bool erase(const T & val){
		return erase(find(val));
	}
	const iterator end(void) const { // *(.end())会产生未定义结果
		return iterator(base);
	}
	iterator end(void) {
		return iterator(base);
	}
	const iterator begin(void) const {
		node * pnow=base;
		if(pnow!=nullptr){
			while(pnow->ls!=nullptr){
				pnow=pnow->ls;
			}
		}
		return iterator(pnow);
	}
	iterator begin(void){
		node * pnow=base;
		if(pnow!=nullptr){
			while(pnow->ls!=nullptr){
				pnow=pnow->ls;
			}
		}
		return iterator(pnow);
	}
protected:
	void dfsdel(node * nn){ // 递归析构
		if(nn->ls!=nullptr){
			dfsdel(nn->ls);
		}
		if(nn->rs!=nullptr){
			dfsdel(nn->rs);
		}
		delete nn;
	}
public:
	~_AVLTree(){
		// debug("~AVLTree");cout_n;
		if(base->ls!=nullptr){dfsdel(base->ls);}
		delete base;
	}
	int height(void) const {
		return base->hgh-1;
	}
	int size(void) const {
		return sz;
	}
};


#endif