#include <iostream>
#include <vector>
#include "vector.hpp"

using namespace std;

class B {
public:
    char *l;
    int i;
    B():l(nullptr), i(1) {};
    B(const int &ex) {
        this->i = ex;
        this->l = new char('a');
    };
    virtual ~B() {
        delete this->l;
        this->l = nullptr;
    };
};

class A : public B {
public:
    A():B(){};
    A(const B* ex){
        this->l = new char(*(ex->l));
        this->i = ex->i;
        if (ex->i == -1) throw "n";
    }
    ~A() {
        delete this->l;
        this->l = nullptr;
    };
};
int main (){


	std::vector<int> vector1;
    std::vector<int> v;
    std::vector<int> tmp;
    tmp.assign(2600 * 1, 1);
    vector1.assign(4200 * 1, 1);
    vector1.insert(vector1.end() - 1000 * 1, tmp.begin(), tmp.end());
    v.push_back(vector1[3]);
    v.push_back(vector1.size());
    v.push_back(vector1.capacity());

    std::unique_ptr<B> k2(new B(3));
    std::unique_ptr<B> k3(new B(4));
    std::unique_ptr<B> k4(new B(-1));
    std::vector<A> vvv;
    std::vector<B*> v1;

    v1.push_back(&(*k2));
    v1.push_back(&(*k3));
    v1.push_back(&(*k4));
    try { vvv.insert(vvv.begin(), v1.begin(), v1.end()); }
    catch (...) {
        v.push_back(vvv.size());
        v.push_back(vvv.capacity());
    }



	
    ft::vector<int> _vector;
    ft::vector<int> tmp1;
    tmp1.assign(2600 * 1, 1);
    _vector.assign(4200 * 1, 1);
    _vector.insert(_vector.end() - 1000 * 1, tmp1.begin(), tmp1.end());
    v.push_back(_vector[3]);
    v.push_back(_vector.size());
    v.push_back(_vector.capacity());

    std::unique_ptr<B> kk2(new B(3));
    std::unique_ptr<B> kk3(new B(4));
    std::unique_ptr<B> kk4(new B(-1));
    ft::vector<A> vv;
    ft::vector<B*> vv1;

    vv1.push_back(&(*kk2));
    vv1.push_back(&(*kk3));
    vv1.push_back(&(*kk4));
    try { vv.insert(vv.begin(), vv1.begin(), vv1.end()); }
    catch (...) {
        v.push_back(vv.size());
        v.push_back(vv.capacity());
    }
    for (int i = 0 ; i < v.size(); i++)
    {if (i ==5 )
        cout << std::endl;
    cout << v[i] << " " << std::endl;}
        

}



// int main ()
// {
	// ft::vector<int> c2 ;
	// std::vector<int> c4 ;
	// c2.assign(2600, 2);
	// cout << c2.capacity()<<endl;
	// c2.insert(c2.end() ,3,2);
	// cout << c2.capacity()<<endl;
	
	// c4.assign(2600, 4);
	// cout << c4.capacity()<<endl;
	// c4.insert(c4.end() ,3,2);
	// cout << c4.capacity()<<endl;
	
	
	// c2.insert(c2.end() - 50,4200,1);
	// c4.insert(c4.end() - 50,4200,1);
	
	// cout << c2[2121] <<" " << c2.size()<<" " <<c2.capacity()<<" " <<endl; 
	// cout << c4[2121]<<" "  << c4.size()<<" " <<c4.capacity()<<" " <<endl;
	
	// for (int i = 0 ; i < c2.size();i++)
	// 	cout << c2[i] << endl;
	// for (int i = 0 ; i < c4.size();i++)
	// 	cout << c4[i] << endl;
	// cout <<"========================================="<<endl;

	// ft::vector<int> c3 ;
	// std::vector<int> c5 ;
	
	// c3.assign(5, 42);
	// c5.assign(5, 42);
	
	// cout <<"========================================="<<endl;
	
	// c2.insert(c2.begin(), c3.begin(), c3.end());
	// for (int i = 0 ; i < c2.size(); i++)
	// 	cout <<"i "<<i<< ";"<<c2[i]<<endl;
	// 	 cout << c2.size()<<endl;
	// cout << c2.capacity()<<endl;
	
	// cout <<"========================================="<<endl;
	// c4.insert(c4.begin(), c5.begin(), c5.end());
	// for (int i = 0 ; i < c4.size(); i++)
	// 	cout <<"i "<<i<< ";"<<c4[i]<<endl;
	// 	 cout << c4.size()<<endl;
	// cout << c4.capacity()<<endl;
	
	


// }