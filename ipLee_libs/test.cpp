#include <bits/stdc++.h>
typedef long long int ll;
using namespace std;
#define _DEBUG_
#ifdef _DEBUG_
#define debug(x) cout << #x << ": " << x << "  "
#define cout_n cout<<endl
#else
#define debug(x)
#define cout_n
#endif

#include "_vector.hpp"
#include "_algo.hpp"
#include "_queue.hpp"
#include "_deque.hpp"
#include "_list.hpp"
#include "_set.hpp"


// using namespace std;
#define pb push_back

namespace test_sort{
_vector<int>vi;
bool cmp_int(const int & i1,const int & i2){
	return i1>i2;
}
void test(void){
	int cnt=25;
	for(int i=1;i<=cnt;i++){
		vi.pb(rand()%30);
	}
	_vector<int>res(vi);
	// cerr<<vi.end()-vi.begin()<<endl;
	// for(auto x:vi){
	// 	cout<<x<<' ';
	// }
	// cout<<endl;
	auto f=[](const int & x){cout<<x<<" ";};
	vi.traverse(f);cout<<endl;
	_sort::_select_sort<int,cmp_int>(vi.begin(),vi.end());
	// _sort::_merge_sort<int,cmp_int>(vi.begin(),vi.end(),res.begin(),res.end());
	// _sort::_bubble_sort<int,cmp_int>(vi.begin(),vi.end());
	// _sort::_binary_insertion_sort<int,cmp_int>(vi.begin(),vi.size());
	// _sort::_quik_sort<int,cmp_int>(vi.begin(),vi.end());
	
	for(auto x:vi){
		cout<<x<<' ';
	}
	cout<<endl;
}
};


namespace test_queue{
void test(void){
	_queue<int>q;
	for(int i=1;i<=20;i++){
		q.push(rand()%100);
	}
	q.print_all([](const int & x){cout<<x<<" ";});cout<<endl;
	while(!q.empty()){
		cout<<q.front()<<' ';q.pop();
	}
}
};

namespace test_set{
const int MAXKEY=50;
struct true_set{
	set<int>data;
	vector<int>tmp;
	FILE * fp;
	true_set(const char * filename){
		fp=fopen(filename,"w");
	}
	~true_set(){
		fclose(fp);
	}
	static int randval(void){
		return rand()%MAXKEY+1;
	}
	int del(void){
		int val=randval();
		fprintf(fp,"2 %d\n",val);
		data.erase(val);
		return val;
	}
	int add(void){
		int val=randval();
		fprintf(fp,"1 %d\n",val);
		data.insert(val);
		return val;
	}
	const vector<int> & get_vals(void){
		tmp.clear();
		for(auto x:data){
			tmp.push_back(x);
		}
		return tmp;
	}
};
typedef double db;
void randtest(const char * filename){
	_AVLTree<int>S;
	true_set ts(filename);
	vector<int>Svals;
	int cnt=1e5; // 测试次数
	db p_insert=0.5,p_erase=0.4,p_check=0.1;
	while(cnt--){
		db p=db(rand())/RAND_MAX;
		debug(p);cout_n;
		if(p<p_insert){
			S.insert(ts.add());
		}else if(p<p_erase+p_erase){
			S.erase(ts.del());
		}else{
			debug("xxx");cout_n;
			Svals.clear();
			for(auto x:S){
				Svals.push_back(x);
			}
			if(Svals!=ts.get_vals()){
				cerr<<"ERROR"<<endl;
				cout<<"ERROR"<<endl;
				return;
			}
		}
	}
}
void filetest(const char * filename){
	FILE * fp=fopen(filename,"r");
	int cmd,val;
	_AVLTree<int>S;
	while(~fscanf(fp,"%d %d",&cmd,&val)){
		cout<<endl;cout<<endl;
		debug(cmd);debug(val);cout_n;
		if(cmd==1){
			S.insert(val);
		}else{
			auto it=S.find(val);
			cout_n;
			if(it!=S.end()){
				cout<<"fnd:"<<*it<<endl;	
			}
			cout<<"del:"<<int(S.erase(val))<<endl;
		}
		for(auto x:S){
			cout<<x<<' ';
		}
		cout<<endl;
	}
	fclose(fp);
}
}
namespace test_hashset{
// DS上要求的HashSet和C++实际使用的unordered_set完全不一样，所以就不管了
};

int main() {
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifdef _DEBUG_
	// freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	clock_t _BEGIN_T=clock();
#endif
	srand(time(0));
	// test_queue::test();

	// test_set::randtest("test.in");
	// test_set::filetest("test.in");

	test_sort::test();

	// int * p1=new int;*p1=3;
	// void * p2=nullptr;
	// void * tmp=(void*)p1;
	// p1=(int*)p2;
	// p2=(void*)tmp;
	// cout<<*(int*)p2<<endl;
	// swap<int*>((int*)p1,(int*)p2);
	
#ifdef _DEBUG_
	clock_t _END_T=clock();
	cerr<<"TIME: "<<(double)(_END_T-_BEGIN_T)/CLOCKS_PER_SEC*1000.0<<"mS"<<endl;
#endif
	return 0;
}
