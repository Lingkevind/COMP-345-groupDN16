#include <iostream>
#include <string>
#include <vector>
#include"Orders.h"
//testOrderExecution in the end
/***
Order Class
***/

Order::Order(){
    orderId=0;
}

Order::Order(int orderId){
    count++;
    this->orderId=orderId;
}

Order::Order(Player* orderHolder){
    count++;
	this->orderId = count;
	this->orderHolder = orderHolder;
}

Order::Order(int orderId, Player* orderHolder){
    this->orderId=orderId;
    this->orderHolder=orderHolder;
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


//Method of Order

    Territory* Order::getTargetTerritory(){
            return targetTerritory;
        }
    Territory* Order::getSourceTerritory(){
            return sourceTerritory;
        }
    Player* Order::getOrderHolder(){
            return orderHolder;
        }
    void Order::setTargetTerritory(Territory* target){
        this->targetTerritory=target;
    }
    void Order::setSourceTerritory(Territory* source){
        this->sourceTerritory=source;
    }
    void Order::setOrderHolder(Player* holder){
        this->orderHolder=holder;
    }

/****
 Order List functions
****/


OrderList::OrderList(){		//OrderList default constructor
	
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
}


// /******
//     Deploy functions
// ******/

Deploy::Deploy():Order(){ 
    
}

Deploy::Deploy(int orderId): Order(orderId){

}

Deploy::Deploy(const Deploy& order){
    this->orderId=order.orderId;
    this->army=order.army;
}

Deploy::Deploy(Player* orderHolder, int army, Territory* target){
    this->setOrderHolder(orderHolder);
    this->army=army;
    this->setTargetTerritory(target);
}

Deploy& Deploy::operator=(const Deploy &order){
    this->orderId=order.orderId;
    this->army=order.army;
    return *this;
}

Deploy::~Deploy(){
}
bool Deploy::validate(){
    // logic for validation
    bool isValid=false;

    vector <Territory*> isPresent  = getOrderHolder()->getplayerOccupied();
    for(Territory* t: isPresent){
        if(t==getTargetTerritory()){
            isValid=true;
            cout<<"The Deploy order is valid."<<endl;
             break;
        }
    } 
    return isValid;
}

void Deploy::execute(){
    bool isValid=validate();

    cout<<"Execute function of "<<this->getOrderName()<<endl;

    if(isValid){
        cout<<"Deploying armies"<<endl;
        cout<<"Target territory:"<<getTargetTerritory()->getName();

        getTargetTerritory()->setArmySize(getTargetTerritory()->getArmySize()+ army);

        cout<<"Execution was successful"<<endl;
    }
    else{
        cout<<"Execution cannot be done."<<endl;
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
    
}

Advance::Advance(int orderId):Order(orderId){
    
}

Advance::Advance(const Advance& order){
    this->orderId=order.orderId;
}

Advance::Advance(Player* orderHolder, int army, Territory* source, Territory* target){
    this->setOrderHolder(orderHolder);
    this->army=army;
    this->setSourceTerritory(source);
    this->setTargetTerritory(target);
}

Advance& Advance::operator=(const Advance &order){
    this->orderId=order.orderId;
    return *this;
}

Advance::~Advance(){
}
bool Advance::validate(){
     if(getTargetTerritory()==NULL || getSourceTerritory()==NULL){
        cout<<"Target or source territory is null."<<endl;
        return false;
    }

   

    //source belongs to player
     bool sourceBelongsToPlayer=false;
    vector <Territory*> isPresent  = getOrderHolder()->getplayerOccupied();
    for(Territory* t: isPresent){
        if(t==getSourceTerritory()){
            sourceBelongsToPlayer=true;
             break;
        }
    } 

    //Adjacency test
    bool isAdjacent=false;
     vector <Territory* > adjacency= getTargetTerritory()->getAdjacentTerritories();
    for(Territory* t: adjacency){
        if(t==getSourceTerritory())
            isAdjacent=true;
            break;
    }

    //Are the armies enough to make an advance.
    bool ArmiesEnough=(army<=getSourceTerritory()->getArmySize());
    
    if(!sourceBelongsToPlayer){
        cout<<"Invalid advance order. Source does not belong to player."<<endl;
        return false;
    }

    else if(!isAdjacent){
         cout<<"Invalid advance order. Territories need to be adjacent."<<endl;
        return false;
    }
    else if(!ArmiesEnough){
         cout<<"Invalid advance order. Not enough armies."<<endl;
        return false;
    }
    else {
        cout<<"Valid order."<<endl;
        return true;
    }
  }


    void Advance::execute(){
        bool isValid=validate();

        cout<<"Execute function of "<<this->getOrderName()<<endl;

        if(isValid){
            // If the target territory belongs to the player, you just move armies.
            
            if(getTargetTerritory()->getControllingPlayer()==getOrderHolder()){
                int sourcearmies=getTargetTerritory()->getArmySize();
                int targetarmies=getSourceTerritory()->getArmySize();
                    getTargetTerritory()->setArmySize(targetarmies+ army);
                    getSourceTerritory()->setArmySize(sourcearmies- army);
                
            }
            else{
                    while(army>0){
                        if(getTargetTerritory()->getArmySize()<=0){
                            cout<<" Territory conquered. Remaining armies will remove as it is.";
				
			    this->getTargetTerritory()->getControllingPlayer()->leaveTerritory(getTargetTerritory());
                            this->getOrderHolder()->occupy(getTargetTerritory());

                            int sourcearmies=getTargetTerritory()->getArmySize();
                            int targetarmies=getSourceTerritory()->getArmySize();

                             getTargetTerritory()->setArmySize(targetarmies+ army);
                             getSourceTerritory()->setArmySize(sourcearmies- army);
                             break;
                        }

                        int attackprobability= rand()%10 +1;
                        int defendprobability= rand()%10 +1;

                    if(attackprobability<=6)
                        getTargetTerritory()->setArmySize(getTargetTerritory()->getArmySize()-1);
                    if(defendprobability<=7){
                             army=army-1;
                        getSourceTerritory()->setArmySize(getSourceTerritory()->getArmySize()-1);
                    }
                       
                   } // while loop closes
            } // else closses
            

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
   
}

Bomb::Bomb(int orderId):Order(orderId){

}

Bomb::Bomb(const Bomb& order){
    this->orderId=order.orderId;
}

Bomb::Bomb(Player* orderHolder, Territory* target){
    this->setOrderHolder(orderHolder);
    this->setTargetTerritory(target);
}

Bomb& Bomb::operator=(const Bomb &order){
    this->orderId=order.orderId;
    return *this;
}

Bomb::~Bomb(){
}
bool Bomb::validate(){

     if(getTargetTerritory()==NULL){
        cout<<"Target territory is null."<<endl;
        return false;
    }
    // logic for validation
    bool isAdjacent=false;
    bool belongsToPlayer=false;

    //If the territory belongs to the player himself, then they cannot bomb their own territory.
    vector <Territory*> ownership= getOrderHolder()->getplayerOccupied();
    for(Territory* t: ownership){
        if(t==getTargetTerritory())
            belongsToPlayer=true;
    }

    //If the territory is not adjacent, player cannot bomb the territory.
    vector <Territory* > adjacency= getTargetTerritory()->getAdjacentTerritories();
    for(Territory* t: adjacency){
        if(t->getControllingPlayer()==getOrderHolder())
            isAdjacent=true;
    }
    
    if(belongsToPlayer){
        cout<<"You cannot bomb your own territory buddy."<<endl;
        return false;
    }
    else if(!isAdjacent){
        cout<<"You can only bomb adjacent territory."<<endl;
    }
    else{
        cout<<"Valid order. Bombing the territory."<<endl;
    }
}

void Bomb::execute(){
    bool isValid=validate();

    cout<<"Execute function of "<<this->getOrderName()<<endl;

    if(isValid){
        getTargetTerritory()->setArmySize(getTargetTerritory()->getArmySize()/2);
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
   
}

Blockade::Blockade(int orderId):Order(orderId){
}

Blockade::Blockade(const Blockade& order){
    this->orderId=order.orderId;
}

Blockade::Blockade(Player* orderHolder, Territory* target){
    this->setOrderHolder(orderHolder);
    this->setTargetTerritory(target);
}

Blockade& Blockade::operator=(const Blockade &order){
    this->orderId=order.orderId;
    return *this;
}

Blockade::~Blockade(){
}
bool Blockade::validate(){
    // logic for validation

     if(getTargetTerritory()==NULL){
        cout<<"Target territory is null."<<endl;
        return false;
    }

    if(getTargetTerritory()->getControllingPlayer()!=getOrderHolder()){
        cout<<"Order invalid. You can only blockade your own territory."<<endl;
        return false;
    }
    else{
        cout<<"Valid order. Blockading territory"<<endl;
        return true;
    }
}

void Blockade::execute(){
    bool isValid=validate();

    cout<<"Execute function of "<<this->getOrderName()<<endl;

    if(isValid){

        neutralPlayer= new Player();
        neutralPlayer->setPlayerName("Neutral");

        getTargetTerritory()->setArmySize(2*getTargetTerritory()->getArmySize());
        neutralPlayer->occupy(getTargetTerritory());
        //getOrderHolder()->leaveterritory(getTargetTerritory()); this function is yet to be implemented
        getTargetTerritory()->setControllingPlayer(neutralPlayer);
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
  
}

Airlift::Airlift(int orderId):Order(orderId){
  
}

Airlift::Airlift(const Airlift& order){
    this->orderId=order.orderId;
}

Airlift::Airlift(Player* orderHolder, int army, Territory* source, Territory* target){
    this->setOrderHolder(orderHolder);
    this->army=army;
    this->setSourceTerritory(source);
    this->setTargetTerritory(target);
}

Airlift& Airlift::operator=(const Airlift &order){
    this->orderId=order.orderId;
    return *this;
}

Airlift::~Airlift(){
}
bool Airlift::validate(){
    // logic for validation
    
     if(getTargetTerritory()==NULL||getSourceTerritory()==NULL){
        cout<<"Target or Source territory is null."<<endl;
        return false;
    }

    //Checking if target territory belongs to OrderHolder
    if(getTargetTerritory()->getControllingPlayer()!=getOrderHolder() ){
        cout<<"Order invalid.Target territory should belong to OrderHolder."<<endl;
        return false;
    }
    
    //Checking if source territory belongs to OrderHolder.
    else if(getSourceTerritory()->getControllingPlayer()!=getOrderHolder() ){
        cout<<"Order invalid.Source territory should belong to OrderHolder."<<endl;
        return false;
    }

    //Checking if source territory has enough armies to Airlift.
    else if(army> getSourceTerritory()->getArmySize()){
        cout<<"Order Invalid. You cannot Airlift more armies than you have."<<endl;
        return false;
    }
    else{
        cout<<"Valid order. Airlift armies from source to target territory."<<endl;
        return true;
    }

}

void Airlift::execute(){
    bool isValid=validate();

    cout<<"Execute function of "<<this->getOrderName()<<endl;

    if(isValid){
        getSourceTerritory()->setArmySize(getSourceTerritory()->getArmySize()-army);
        getTargetTerritory()->setArmySize(getTargetTerritory()->getArmySize()+army);
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
   
}

Negotiate::Negotiate(int orderId):Order(orderId){

}

Negotiate::Negotiate(const Negotiate& order){
    this->orderId=order.orderId;
}

Negotiate::Negotiate(Player* orderHolder, Player* negotiateWith){
    this->setOrderHolder(orderHolder);
}

Negotiate& Negotiate::operator=(const Negotiate &order){
    this->orderId=order.orderId;
    return *this;
}

 Negotiate::~Negotiate(){
 }
bool Negotiate::validate(){
    // logic for validation
    Player* negotiateWith= this->getTargetTerritory()->getControllingPlayer();

    if(this->getOrderHolder()==negotiateWith){
        cout<<"You cannot negotiate with yourself buddy."<<endl;
        return false;
    }
    else{
        cout<<"The order is valid. We will negotiate."<<endl;
        return true;
    }

}

void Negotiate::execute(){

    bool isValid=validate();

    cout<<"Execute function of "<<this->getOrderName()<<endl;

    if(isValid){
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

