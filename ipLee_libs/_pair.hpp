#ifndef _PAIR_HPP
#define _PAIR_HPP


template<typename T1,typename T2>class _pair{
protected:
	
public:
	T1 first;T2 second;

	_pair(){}
	_pair(const T1 & t1,const T2 & t2):first(t1),second(t2){}
	_pair<T1,T2> & operator = (const _pair<T1,T2> & p){
		first=p.first;second=p.second;
		return *this;
	}
	~_pair()=default;
	bool operator == (const _pair<T1,T2> & p) const {
		return p.first==first && p.second==second;
	}
	bool operator != (const _pair<T1,T2> & p) const {
		return !operator==(p);
	}
	bool operator < (const _pair<T1,T2> & p) const {
		// 这个其实不是标准写法
		return (first==p.first)?(second<p.second):(first<p.first);
	}
};


#endif
