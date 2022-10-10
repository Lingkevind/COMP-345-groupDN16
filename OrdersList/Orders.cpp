#include <iostream>
#include <string>
#include <vector>
#include"Orders.h"


using namespace std;

/***
Order Class
***/
Order::Order(){
    orderId=0;		//Order default constructor
}

Order::Order(int orderId){
    this->orderId=orderId;	//Order Parameterised constructor
}

Order::Order(const Order& order){
    this->orderId=order.orderId;	//Order copy constructor
}

Order& Order::operator=(const Order& order){
    this->orderId=order.orderId;	//Order assignment operator
    return *this;
}
Order::~Order(){	//Order destructor
}

ostream& operator<<(ostream& os, const Order& order){
    os<<"Order ID:"<<order.orderId<<"\t"<< "Order Name:"<<order.orderName<<endl;
    return os;				//Order output stream function
}



// /******
//     Deploy functions
// ******/

Deploy::Deploy():Order(){ 
    orderId=0;		//Deploy default constructor
}

Deploy::Deploy(int orderId){
    this->orderId=orderId;	//Deploy parameterised constructor
}

Deploy::Deploy(const Deploy& order){
    this->orderId=order.orderId;  //Deploy copy constructor
}

Deploy& Deploy::operator=(const Deploy &order){
    this->orderId=order.orderId;
    return *this;		//Deploy assignment operator
}

Deploy::~Deploy(){	//Deploy destructor
}
bool Deploy::validate(){
    // logic for validation	//Deploy validate function
	cout<<"Validate function running."<<endl;
    return true;
}

void Deploy::execute(){
    bool canExecute=validate();	 //Deploy execute function

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
    return os;			//Deploy output stream function
}

/******
    Advance functions
******/

Advance::Advance():Order(){ 
    orderId=0;		//Advance default constructor
}

Advance::Advance(int orderId){
    this->orderId=orderId;	//Advance parameterised constructor
}

Advance::Advance(const Advance& order){
    this->orderId=order.orderId; // Advance copy constructor
}

Advance& Advance::operator=(const Advance &order){
    this->orderId=order.orderId;
    return *this;		//Advance assignment operator
}

Advance::~Advance(){		//Advance destructor
}
bool Advance::validate(){
    // logic for validation	//Advance validation function

    return true;
}

void Advance::execute(){
    bool canExecute=validate();	//Advance execute function

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
    return os;			//Advance output stream operator
}


/******
    Bomb functions
******/

Bomb::Bomb():Order(){ 		//Bomb default constructor
    orderId=0;    
}

Bomb::Bomb(int orderId){	//Bomb parameterised constructor
    this->orderId=orderId;
}

Bomb::Bomb(const Bomb& order){	//Bomb copy constructor
    this->orderId=order.orderId;
}

Bomb& Bomb::operator=(const Bomb &order){
    this->orderId=order.orderId;  //Bomb assignment operator
    return *this;
}

Bomb::~Bomb(){
}				//Bomb destructor
bool Bomb::validate(){
    // logic for validation	//Bomb validate function
	cout<<"Validate function running."<<endl;
    return true;
}

void Bomb::execute(){		// Bomb execute function
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
    return os;			//Bomb output stream function
}


/******
    Blockade functions
******/

Blockade::Blockade():Order(){ 
   orderId=0;   		//Blockade default constructor
}

Blockade::Blockade(int orderId){
    this->orderId=orderId;	//Blockade parameterised constructor
}

Blockade::Blockade(const Blockade& order){
    this->orderId=order.orderId;  //Blockade copy constructor
}

Blockade& Blockade::operator=(const Blockade &order){
    this->orderId=order.orderId;  //Blockade assignment operator
    return *this;
}

Blockade::~Blockade(){		//Blockade destructor 
}
bool Blockade::validate(){
    // logic for validation	//Blockade validate function
	cout<<"Validate function running."<<endl;
    return true;
}

void Blockade::execute(){	//Blockade execute function
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
    return os;			//Blockade output stream function
}


/******
    Airlift functions
******/

Airlift::Airlift():Order(){ 
    orderId=0;  		//Airlift default constructor
}

Airlift::Airlift(int orderId){
    this->orderId=orderId;	//Airlift parameterised constructor
}

Airlift::Airlift(const Airlift& order){
    this->orderId=order.orderId;  //Airlift copy constructor
}

Airlift& Airlift::operator=(const Airlift &order){
    this->orderId=order.orderId;  //Airlift assignment operator
    return *this;
}

Airlift::~Airlift(){		//Blockade destructor
}
bool Airlift::validate(){
    // logic for validation	//Blockade validate function
	cout<<"Validate function running."<<endl;
    return true;
}

void Airlift::execute(){	//Blockade execute function
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
    return os;			//Blockade output stream operator function
}


/******
    Negotiate functions
******/

Negotiate::Negotiate():Order() {
   orderId=0;    		//Negotiate default constructore
}

Negotiate::Negotiate(int orderId){
    this->orderId=orderId;	//Negotiate parameterised constructor
}

Negotiate::Negotiate(const Negotiate& order){
    this->orderId=order.orderId;  //Negotiate copy contructor
}

Negotiate& Negotiate::operator=(const Negotiate &order){
    this->orderId=order.orderId;
    return *this;		// Negotiate assignment operator
}

 Negotiate::~Negotiate(){	//Negotiate destructor 
 }				
bool Negotiate::validate(){
    // logic for validation	//Negotiate validate function
	cout<<"Validate function running."<<endl;
    return true;
}

void Negotiate::execute(){	//Negotiate execute function
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
    return os;			//Negotiate output stream function
}

/****
 Order List functions
****/


OrderList::OrderList(){		//OrderList default constructor
    /*
    Default constructor	
    Nothing to code for now.
    */
}
OrderList::~OrderList(){	//OrderList destructor
    for(Order* order: orderList){
        delete order;
        order=nullptr;      
    }
    orderList.clear();
}

OrderList::OrderList(const OrderList& OriginalList){
    this->orderList=OriginalList.orderList; //OrderList copy constructor	
}				

OrderList& OrderList::operator=(const OrderList& OriginalList){
    this->orderList=OriginalList.orderList;	//OrderList assignment operator
    return *this;
}

void OrderList::add(Order *order){
    this->orderList.push_back(order);	//OrderList add function
    cout<<order->getOrderName()<<"Order added"<<endl;
}

void OrderList::remove(int position){
    if(position<0 || position>=getOrderList().size()){
        cout<<"Invalid remove order"<<endl;	//OrderList remove function
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
         }			//OrderList execute function
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
	return os;		//OrderList output stream function
};
