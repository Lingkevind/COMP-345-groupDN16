#include <iostream>
#include <string>
#include <vector>
#include"Orders.h"


using namespace std;

/***
Order Class
***/
Order::Order(){
    orderId=0;
}

Order::Order(int orderId){
    this->orderId=orderId;
}

Order::Order(const Order& order){
    this->orderId=order.orderId;
}

Order& Order::operator=(const Order& order){
    this->orderId=order.orderId;
    return *this;
}
Order::~Order(){
}

ostream& operator<<(ostream& os, const Order& order){
    os<<"Order ID:"<<order.orderId<<"\t"<< "Order Name:"<<order.orderName<<endl;
    return os;
}



// /******
//     Deploy functions
// ******/

Deploy::Deploy():Order(){ 
    orderId=0;
}

Deploy::Deploy(int orderId){
    this->orderId=orderId;
}

Deploy::Deploy(const Deploy& order){
    this->orderId=order.orderId;
}

Deploy& Deploy::operator=(const Deploy &order){
    this->orderId=order.orderId;
    return *this;
}

Deploy::~Deploy(){
}
bool Deploy::validate(){
    // logic for validation
    return true;
}

void Deploy::execute(){
    bool canExecute=validate();

    cout<<"Execute function of "<<this->getOrderName()<<endl;

    if(canExecute){
        cout<<"Execution was successful"<<endl;
    }
    else{
        cout<<"Execution cannot be done"<<endl;
    }
}

ostream& operator<<(ostream& os, const Deploy& order){
    os<<"Order ID:"<<order.orderId<<"\t"<< "Order Name:"<<order.orderName<<endl;
    return os;
}

/******
    Advance functions
******/

Advance::Advance():Order(){ 
    orderId=0;
}

Advance::Advance(int orderId){
    this->orderId=orderId;
}

Advance::Advance(const Advance& order){
    this->orderId=order.orderId;
}

Advance& Advance::operator=(const Advance &order){
    this->orderId=order.orderId;
    return *this;
}

Advance::~Advance(){
}
bool Advance::validate(){
    // logic for validation

    return true;
}

void Advance::execute(){
    bool canExecute=validate();

    cout<<"Execute function of "<<this->getOrderName()<<endl;

    if(canExecute){
        cout<<"Execution was successful"<<endl;
    }
    else{
        cout<<"Execution cannot be done"<<endl;
    }
}

ostream& operator<<(ostream& os, const Advance& order){
    os<<"Order ID:"<<order.orderId<<"\t"<< "Order Name:"<<order.orderName<<endl;
    return os;
}


/******
    Bomb functions
******/

Bomb::Bomb():Order(){ 
    orderId=0;    
}

Bomb::Bomb(int orderId){
    this->orderId=orderId;
}

Bomb::Bomb(const Bomb& order){
    this->orderId=order.orderId;
}

Bomb& Bomb::operator=(const Bomb &order){
    this->orderId=order.orderId;
    return *this;
}

Bomb::~Bomb(){
}
bool Bomb::validate(){
    // logic for validation
    return true;
}

void Bomb::execute(){
    bool canExecute=validate();

    cout<<"Execute function of "<<this->getOrderName()<<endl;

    if(canExecute){
        cout<<"Execution was successful"<<endl;
    }
    else{
        cout<<"Execution cannot be done"<<endl;
    }
}

ostream& operator<<(ostream& os, const Bomb& order){
    os<<"Order ID:"<<order.orderId<<"\t"<< "Order Name:"<<order.orderName<<endl;
    return os;
}


/******
    Blockade functions
******/

Blockade::Blockade():Order(){ 
   orderId=0;   
}

Blockade::Blockade(int orderId){
    this->orderId=orderId;
}

Blockade::Blockade(const Blockade& order){
    this->orderId=order.orderId;
}

Blockade& Blockade::operator=(const Blockade &order){
    this->orderId=order.orderId;
    return *this;
}

Blockade::~Blockade(){
}
bool Blockade::validate(){
    // logic for validation
    return true;
}

void Blockade::execute(){
    bool canExecute=validate();

    cout<<"Execute function of "<<this->getOrderName()<<endl;

    if(canExecute){
        cout<<"Execution was successful"<<endl;
    }
    else{
        cout<<"Execution cannot be done"<<endl;
    }
}

ostream& operator<<(ostream& os, const Blockade& order){
    os<<"Order ID:"<<order.orderId<<"\t"<< "Order Name:"<<order.orderName<<endl;
    return os;
}


/******
    Airlift functions
******/

Airlift::Airlift():Order(){ 
    orderId=0;  
}

Airlift::Airlift(int orderId){
    this->orderId=orderId;
}

Airlift::Airlift(const Airlift& order){
    this->orderId=order.orderId;
}

Airlift& Airlift::operator=(const Airlift &order){
    this->orderId=order.orderId;
    return *this;
}

Airlift::~Airlift(){
}
bool Airlift::validate(){
    // logic for validation
    return true;
}

void Airlift::execute(){
    bool canExecute=validate();

    cout<<"Execute function of "<<this->getOrderName()<<endl;

    if(canExecute){
        cout<<"Execution was successful"<<endl;
    }
    else{
        cout<<"Execution cannot be done"<<endl;
    }
}

ostream& operator<<(ostream& os, const Airlift& order){
    os<<"Order ID:"<<order.orderId<<"\t"<< "Order Name:"<<order.orderName<<endl;
    return os;
}


/******
    Negotiate functions
******/

Negotiate::Negotiate():Order() {
   orderId=0;    
}

Negotiate::Negotiate(int orderId){
    this->orderId=orderId;
}

Negotiate::Negotiate(const Negotiate& order){
    this->orderId=order.orderId;
}

Negotiate& Negotiate::operator=(const Negotiate &order){
    this->orderId=order.orderId;
    return *this;
}

 Negotiate::~Negotiate(){
 }
bool Negotiate::validate(){
    // logic for validation
    return true;
}

void Negotiate::execute(){
    bool canExecute=validate();

    cout<<"Execute function of "<<this->getOrderName()<<endl;

    if(canExecute){
        cout<<"Execution was successful"<<endl;
    }
    else{
        cout<<"Execution cannot be done"<<endl;
    }
}

ostream& operator<<(ostream& os, const Negotiate& order){
    os<<"Order ID:"<<order.orderId<<"\t"<< "Order Name:"<<order.orderName<<endl;
    return os;
}

/****
 Order List functions
****/


OrderList::OrderList(){
    /*
    Default constructor
    Nothing to code for now.
    */
}
OrderList::~OrderList(){
    for(Order* order: orderList){
        delete order;
        order=nullptr;      
    }
    orderList.clear();
}

OrderList::OrderList(const OrderList& OriginalList){
    this->orderList=OriginalList.orderList;
}

OrderList& OrderList::operator=(const OrderList& OriginalList){
    this->orderList=OriginalList.orderList;
    return *this;
}

void OrderList::add(Order *order){
    this->orderList.push_back(order);
    cout<<order->getOrderName()<<"Order added"<<endl;
}

void OrderList::remove(int position){
    if(position<0 || position>=getOrderList().size()){
        cout<<"Invalid remove order"<<endl;
    }
    else{
        Order *removeOrder=getOrderList().at(position);
        delete removeOrder;
        removeOrder=nullptr;
        this->orderList.erase(orderList.begin()+position);
        cout<<"Order removed"<<endl;
    }
}

void OrderList::move(int initialPosition, int finalPosition){
    if(initialPosition<0 ||  initialPosition>=getOrderList().size() ||
         finalPosition<0 ||  finalPosition>=getOrderList().size()){
            cout<<"invalid move Order"<<endl;
         }
    else{
        Order *moveOrder=getOrderList().at(initialPosition);
        this->orderList.erase(orderList.begin()+initialPosition);
        this->orderList.insert(orderList.begin()+finalPosition, moveOrder);
        cout<<"Order moved"<<endl;
    }
}

ostream& operator<<(ostream& os, OrderList& OriginalList) {
	 vector<Order*> temp = OriginalList.getOrderList();
	 for (int i = 0; i < temp.size(); i++) {
	 	os << temp.at(i)->orderId << temp.at(i)->getOrderName() << endl;
	 }
	return os;
};
