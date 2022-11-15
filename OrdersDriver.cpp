#include<iostream>
#include "Orders.h"


using namespace std;

int main(){
    Order x(20);
      
    cout<<x.getOrderName()<<endl;

     Advance a1(15);
     a1.execute();

    Advance a2;
    a2=a1;
    cout<<a2.orderId<<endl;

    cout<<endl<<a1<<x;

    OrderList l;
    l.add(new Deploy(1));
    l.add(new Advance(2));
    l.add(new Bomb(3));
    l.add(new Blockade(4));
    l.add(new Airlift(5));
    l.add(&a1);

    cout<<"size of list"<<l.getOrderList().size()<<endl;

    OrderList l2(l);
    OrderList l3;
    l3=l2;
    cout<<l2;

    

    l.move(0,5);
    l.move(0,1);

    cout<<"\nAfter moving list is:\n"<<l;


    l.remove(0);
    l.remove(5);//invalid 
    cout<<"\n\nafter removing list is:\n"<<l;

}
