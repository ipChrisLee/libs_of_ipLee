#ifndef _BINARY_HEAP_HPP
#define _BINARY_HEAP_HPP
#include "_vector.hpp"
#include "_algo.hpp"
template<typename T,class _less_cmp=_less<T> >class _binary_heap{
// 默认container是_vector
// _less_cmp(t1,t2)为true：t1优先级小于t2
// 最后排序的时候优先级高的靠前
protected:
	_vector<T>_vec; // 从0开始。。。
	int ls(int x){return (x<<1)|1;}
	int rs(int x){return (x<<1)+2;}
	int fa(int x){return x==0?-1:(x-1)>>1;}
	bool legal_pos(int idx){
		return idx>=0 && idx<_vec.size();
	}
#define pb push_back
	void max_heapify(int p){
		using cmp=_less_cmp;
		while(legal_pos(p)){
			int imx;
			if( legal_pos(ls(p)) && legal_pos(rs(p)) ){ // 两个儿子下标都是对的
				int ils=ls(p),irs=rs(p);
				if(cmp()(_vec[ils],_vec[irs])){
					imx=irs;
				}else{
					imx=ils; // 相同没有影响
				}
			}else if(legal_pos(ls(p))){
				imx=ls(p);
			}else if(legal_pos(rs(p))){
				imx=rs(p);
			}else{
				imx=-1;
			}
			if(imx==-1){
				break;
			}
			if(cmp()(_vec[p],_vec[imx])){
				_swap<T>(_vec[p],_vec[imx]);
				p=imx;
			}else{
				break;
			}
		}
	}
public:
	_binary_heap(){}
	_binary_heap(const _binary_heap & bh)=default;
	_binary_heap(const _vector<T> & vec):_vec(vec){
		for(int i=_vec.size()/2;i>=0;i--){ 
		// 这里会有size_t转int的精度丢失问题，不过不管了
		// 另外，实际上_vec.size()/2那个元素是不需要被max的
			max_heapify(i);
		}
	}
	_binary_heap & operator = (const _binary_heap & bh)=default;
	~_binary_heap()=default;

	size_t size(void){return _vec.size();}
	bool empty(void){return _vec.size()==0;}
	void push(const T & t){
		// _vec.pb(t);int p=int(_vec.size()-1); // 不会爆size_t
		// _swap<T>(_vec[0],_vec[p]);
		// max_heapify(0);
		_vec.pb(t);int p=int(_vec.size()-1); // 不会爆size_t
		while(p!=-1){
			max_heapify(p);p=fa(p);
		}
	}
	const T & top(void){
		return _vec[0];
	}
	void pop(void){
		// 如果只剩一个元素_vec.size()==1，没有问题
		// 但是如果没有元素的话这里就会爆炸
		int p=int(_vec.size()-1);
		_swap(_vec[0],_vec[p]);
		_vec.pop_back();
		max_heapify(0);
	}
	_vector<T> heap_sort(void){
		// 外部排序
		_binary_heap<T,_less_cmp> bh(*this);
		_vector<T>res;
		while(!bh.empty()){
			res.pb(bh.top());bh.pop();
		}
		return res;
	}
	void heap_sort(_vector<T> & res){
		res.clear();
		_binary_heap<T> bh(*this);
		while(!bh.empty()){
			res.pb(bh.top());bh.pop();
		}
	}
#undef pb
};

#endif
