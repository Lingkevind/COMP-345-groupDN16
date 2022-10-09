#include <iostream>
#include <string>
#include <vector>
#include"Orders.h"

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

// /****
//  Order List functions
// ****/


// // OrderList::OrderList(){
// //     /*
// //     Default constructor
// //     Nothing to code for now.
// //     */
// // }
// // OrderList::~OrderList(){
// //     for(Order* order: orderList){
// //         order=nullptr;
// //         delete order;
// //     }
// //     orderList.clear();
// // }

// // OrderList::OrderList(const OrderList& OriginalList){

// //     std::vector<Order*> newList= OriginalList.getOrderList();
// //     for(int i=0;i<newList.size();i++){
// //         switch((*newList.at(i)).getOrderName()){
// //             case "Deploy": 
// //             case "Advance":
// //             case "
// //         }
// //     }
// // }


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