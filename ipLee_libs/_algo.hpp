#ifndef _ALGO_HPP
#define _ALGO_HPP
// 这个头文件应当足够独立，因为会有很多模版需要用到它
// 如果这里再include其他文件的话可能会导致互相引用的问题
#include "_vector.hpp"
using std::cerr;
using ll=long long int;
template<typename T>void _swap(T & t1,T & t2){
	T tt=t1;
	t1=t2;
	t2=tt;
};
template<typename T>class _less{
public:
	bool operator () (const T & t1,const T & t2) const {
		return t1<t2;
	}	
};
template<typename T>const T _max(const T & t1,const T & t2){
	return _less<T>()(t1,t2)?t2:t1;
}
template<typename T>const T _min(const T & t1,const T & t2){
	return _less<T>()(t1,t2)?t1:t2;
}

namespace _sort{

template<typename T,bool (*cmp)(const T &,const T &)>
	void _select_sort(typename::_vector<T>::iterator bg,typename::_vector<T>::iterator ed){
		using itr=typename::_vector<T>::iterator;
		itr tosort=bg;
		while(tosort!=ed){
			itr mx=tosort;
			for(auto it=tosort;it!=ed;++it){
				if(cmp(*mx,*it)){
					mx=it;
				}
			}
			_swap<T>(*mx,*tosort);
			++tosort;
		}
	}
template<typename T,bool (*cmp)(const T &,const T &)>
	void  _merge_sort(typename::_vector<T>::iterator bg,typename::_vector<T>::iterator ed,
		typename::_vector<T>::iterator resbg,typename::_vector<T>::iterator resed){
		using itr=typename::_vector<T>::iterator;
		if(bg==ed || bg+1==ed){
			// cerr<<"==="<<endl;
			return;
		}else if(ed-bg==2){
			if(cmp(*bg,*(bg+1))){
				// cerr<<*bg<<" "<<*ed<<endl;
				_swap<T>(*bg,*(bg+1));
			}
			return;
		}
		_merge_sort<T,cmp>(bg,bg+(ed-bg)/2,resbg,resbg+(resed-resbg)/2);
		_merge_sort<T,cmp>(bg+(ed-bg)/2,ed,resbg+(resed-resbg)/2,resed);
		itr mid=bg+(ed-bg)/2;
		itr il=bg;itr ir=mid;
		itr it=resbg;
		while(it!=resed){
			// cerr<<"it : "<<*it<<"  ";
			if(il==mid){
				*it=*ir;++ir;
			}else if(ir==ed){
				*it=*il;++il;
			}else{
				if(cmp(*il,*ir)){
					*it=*ir;++ir;
				}else{
					*it=*il;++il;
				}
			}
			++it;
		}
		// cerr<<endl;
		for(auto it=bg;it!=ed;++it){
			*it=*resbg;++resbg;
		}
	}
template<typename T,bool (*cmp)(const T &,const T &)>
	void _bubble_sort(typename::_vector<T>::iterator bg,typename::_vector<T>::iterator ed){
		using itr=typename::_vector<T>::iterator;
		itr mni=ed;
		while(ed!=bg){
			mni=bg;
			for(itr it=bg;it!=ed;it++){
				if(cmp(*it,*mni)){
					mni=it;
				}	
			}
			_swap<T>(*(ed-1),*mni);--ed;
		}
	}
template<typename T,bool (*cmp)(const T &,const T &)>
	void _binary_insertion_sort(typename::_vector<T>::iterator base,int n){
		using itr=typename::_vector<T>::iterator;
		auto find=[base](int bg,int ed,int idx)->int{ // 返回第一个
			int mid,il=bg,ir=ed,ans=ed+1;
			while(il<=ir){
				mid=(il+ir)>>1;
				if(cmp(*(base+mid),*(base+idx))){
					ans=mid;ir=mid-1;
				}else{
					il=mid+1;
				}
			}
			return ans;
		};
		int il=0,ir=n;
		for(int i=1;i<n;i++){
			int idx=find(0,i-1,i);
			for(int j=i-1;j>=idx;--j){
				_swap<T>(*(base+j),*(base+j+1));
			}
		}
	}
template<typename T,bool (*cmp)(const T &,const T &)>
	void _quick_sort(typename::_vector<T>::iterator bg,typename::_vector<T>::iterator ed){
// 没有任何优化的qsort
		if( ed-bg==1 || ed==bg ){
			return;
		}else if(ed-bg==2){
			if(cmp(*bg,*(ed-1))){
				_swap<T>(*bg,*(ed-1));
			}
			return;
		}
		// cerr<<"sz : "<<ed-bg<<endl;
		// for(auto it=bg;it!=ed;it++){
		// 	cerr<<*it<<" ";
		// }
		// cerr<<endl;
		using itr=typename::_vector<T>::iterator;
		itr bg_cpy=bg,ed_cpy=ed,it=bg;
		while(it+1!=ed){
			if(cmp(*it,*(it+1))){
				_swap<T>(*(it),*(it+1));
				++it;
			}else{
				_swap<T>(*(it+1),*(--ed));
			}
		}
		ed=ed_cpy;bg=bg_cpy;
		_quick_sort<T,cmp>(bg,it);_quick_sort<T,cmp>(it+1,ed);
	}
}


#endif
