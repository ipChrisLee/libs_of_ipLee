#ifndef _VECTOR_HPP
#define _VECTOR_HPP
#include <cstdio>
#include <cstdlib>
#include <memory>

using namespace std;
template<typename T>class _vector;
template<typename T>class _vector_node_p {
// 这个迭代器只能用于顺序存储的，也就是_vector的
// 具体迭代器的设计参照这篇文章：https://www.cnblogs.com/cv-pr/p/7765858.html
// 不过对于使用for-each和vector的范型算法来说是够了
    friend _vector<T>;
protected:
    T * iter;
    _vector_node_p(const T * p):iter(p){}
    _vector_node_p(T * p):iter(p){}
    
public:
    _vector_node_p(const _vector_node_p & _it):iter(_it.iter){}
    _vector_node_p():iter(nullptr){}
    _vector_node_p operator = (const _vector_node_p & _it){
        iter=_it.iter;
        return *this;
    }
    ~_vector_node_p(){}
    _vector_node_p operator ++ (void){
        iter++;
        return *this;
    }
    _vector_node_p operator -- (void){
        iter--;
        return *this;
    }
    _vector_node_p operator ++ (int){
        return _vector_node_p(iter++);
    }
    _vector_node_p operator -- (int){
        return _vector_node_p(iter--);
    }
    bool operator != (const _vector_node_p _it){
        return _it.iter!=iter;
    }
    bool operator == (const _vector_node_p _it){
        return _it.iter==iter;
    }
    const T & operator * (void) const {
        return *iter;
    }
    T & operator * (void){
        return *iter;
    }
    _vector_node_p operator + (int offset) const {
        return _vector_node_p(iter+offset);
    }
    _vector_node_p operator - (int offset) const {
        return _vector_node_p(iter-offset);
    }
    long operator - (const _vector_node_p & it){
        return iter-it.iter;
    }
};
template<typename T>class _vector{ 
// 就是vector，保证开空间的均摊O(1)效率，但是不保证和vector行为一致，也没有异常检查
protected:
    size_t _sz; // 已经分配的空间，即外部看起来的占用内存，也就是数组中[0,_sz)部分
    size_t _len; // 实际上的空间占用，_sz<_len（需要保证迭代器的尾后指针）,_len>0
    using alloc=std::allocator<T>;
    alloc alc;
    T * _head;
    void shrink(void){
        // 收缩内存
        if(_sz<_len/4){ // _len==1的时候不会有任何问题
            T * pre=_head;
            size_t presz=_sz,prelen=_len;
            _len=_sz*2+1;
            _head=alc.allocate(_len);
            uninitialized_copy_n(pre,_sz,_head);
            this->free(pre,presz,prelen);
        }
    }
    void free(T * pbg,const size_t psz,const size_t plen){
        // 析构元素并释放空间
        T * tail=pbg+psz;
        while(tail!=pbg){
            alc.destroy(--tail);
        }
        alc.deallocate(pbg,plen);
    }
public:
    typedef _vector_node_p<T> iterator;
    _vector():_sz(0),_len(17){
        _head=alc.allocate(_len);
    }
    _vector(const size_t size,const T & t=T()):_sz(size),_len(size*2+1){
        _head=alc.allocate(_len);
        uninitialized_fill_n(_head,_sz,t);
    }
    _vector(const size_t size,const T * vec):_sz(size),_len(size*2+1){
        _head=alc.allocate(_len);
        uninitialized_copy_n(vec,_sz,_head);
    }
    _vector(const _vector<T> & vec):_sz(vec._sz),_len(vec._len){
        _head=alc.allocate(_len);
        uninitialized_copy_n(vec._head,_sz,_head);
    }
    ~_vector(){
        this->free(_head,_sz,_len);
    }
    void clear(void){
        free(_head,_sz,_len);
        _sz=0;_len=17;
        _head=alc.allocate(_len);
    }
    _vector & operator = (const _vector<T> & vec){
        this->free(_head,_sz,_len);
        _sz=vec._sz;_len=vec._len;
        _head=alc.allocate(_len);
        uninitialized_copy_n(vec._head,_sz,_head);
        return *this;
    }
    _vector & resize(const size_t new_size,const T & t=move(*(new T))){
        // 将外部看见的内存改成new_size
        if(new_size<_sz){
            T * pbg=_head+new_size;T * ped=_head+_sz;
            while(pbg!=ped){
                alc.destroy(pbg++);
            }
            _sz=new_size;
        }else if(new_size<_len){ // _sz<=new_size<=_len-1 
            T * pbg=_head+_sz;T * ped=_head+new_size;
            while(pbg!=ped){
                alc.construct(pbg++,t);
            }
            _sz=new_size;
        }else{ // new_size>=_len-1
            T * pre=_head;size_t presz=_sz,prelen=_len;
            _sz=new_size;_len=_sz*2+1;
            _head=alc.allocate(_len);
            uninitialized_copy_n(pre,presz,_head);
            T * pbg=_head+presz;T * ped=_head+_sz;
            while(pbg!=ped){
                alc.construct(pbg++,t);
            }
            this->free(pre,presz,prelen);
        }
        return *this;
    }
    void push_back(const T & t){
        // debug(_sz);debug(_len);cout_n;
        if(_sz>=_len-1){
            T * pre=_head;size_t presz=_sz,prelen=_len;
            _len=2*_len+1;
            // debug(_len);cout_n;
            _head=alc.allocate(_len);
            uninitialized_copy_n(pre,presz,_head);
            this->free(pre,presz,prelen);
        }
        alc.construct(_head+(_sz++),t);
    }
    void traverse(void (*fun)(const T &)) const {
        for(auto it:*this){
            fun(it);
        }
    }
    void pop_back(void){
        alc.destroy(_head+(--_sz));
        shrink();
    }
    T & operator [] (const size_t idx){
        return _head[idx];
    }
    const T & operator [] (const size_t idx) const {
        return _head[idx];
    }
    size_t size(void) const {
        return _sz;
    }
    const iterator begin(void) const {
        return iterator(_head);
    }
    const iterator end(void) const {
        return iterator(_head+_sz);
    }
    iterator begin(void){
        return iterator(_head);
    }
    iterator end(void){
        return iterator(_head+_sz);
    }
};
#endif