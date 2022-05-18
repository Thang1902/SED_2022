#include <iostream>
using namespace std;

class node{
    int data;
    node* next1;
    node* next2;
    public:
        void setnext1(node* ptr){next1 = ptr;}
        void setnext2(node* ptr){next2 = ptr;}
        node* getnext1(){return next1;}
        node* getnext2(){return next2;}
        void setdata(int d){data = d;}
        int getdata(){return data;}
};

void main(){
    node *head = new node;
    node * ptr = new node;
    head->setdata(15);
    head->setnext1(NULL);
    head->setnext2(ptr);
    ptr->setdata(10);
    ptr->setnext1(head);
    ptr->setnext2(NULL);
    cout << ptr->getnext1()->getdata();
}