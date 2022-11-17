#include<iostream>
#include<vector>
#include<string>
#include "Map.h"
#include "Player.h"
#include "LoggingObserver.h"
using namespace std;

#ifndef ORDERS_H
#define ORDERS_H

void testOrderLists();

class Order: public Subject{
    public:
        int army;
        static int count;
        int orderId;
        Order();
        Order(Player* orderHolder);
        Order(int orderId);
        Order(int OrderId, Player* orderHolder);
        Order(const Order& order);
        ~Order();


        Order& operator=(const Order& order);
        friend ostream& operator<<(ostream& os, const Order& order);
        
        virtual bool validate(){return false;}
        virtual void execute();
        
        virtual string getOrderName() {return orderName;}
        Territory* getTargetTerritory();
        Territory* getSourceTerritory();
        Player* getOrderHolder();
        void setTargetTerritory(Territory* target);
        void setSourceTerritory(Territory* source);
        void setOrderHolder(Player* OrderHolder);

    private:
        string orderName="unknown order";
        Player* orderHolder;
        Territory* sourceTerritory;
        Territory* targetTerritory;
};

class OrderList: public Subject{
    public:
        OrderList();
        ~OrderList();
        OrderList (const OrderList& list);
        void add(Order* order);
        void remove(int position);
        void move(int initialPosition, int finalPosition);
        const std::vector<Order*> getOrderList(){
            return orderList;
        }
    
    private:
        std::vector<Order*> orderList;
};

//Below arxe the six orders mentioned in the assignemnt. Each subclass publicly inherits Order.
//All the functions are the same except A parameterised is added in the subclasses which takes an Order.

class Deploy:public Order{
    public:
        Deploy();
        Deploy(int orderId);
        Deploy(const Deploy &order);
        ~Deploy();
        Deploy(Player* orderHolder, int army, Territory* target);
        Deploy &operator=(const Deploy& order);

        void execute();
        bool validate();
        string getOrderName(){ return orderName;}
        friend ostream& operator<<(ostream& os, const Deploy& order);
        string orderName = "Deploy";
    private:
       
};

class Advance: public Order{
    public:
        Advance();
        Advance(int orderId);
        Advance(const Advance &order);
        ~Advance();
        Advance(Player* orderHolder, int army, Territory* source, Territory* target);
        Advance &operator=(const Advance& order);

        void execute();
        bool validate();
        string getOrderName(){ return orderName;}
        friend ostream& operator<<(ostream& os, const Advance& order);
    private:
        string orderName="Advance";
};

class Bomb: public Order{
    public:
        Bomb();
        Bomb(int orderId);
        Bomb(const Bomb &order);
        ~Bomb();
        Bomb(Player* orderHolder, Territory* target);
        Bomb &operator=(const Bomb& order);

        void execute();
        bool validate();
        string getOrderName(){ return orderName;}
        friend ostream& operator<<(ostream& os, const Bomb& order);
    private:
        string orderName="Bomb";
};

class Blockade: public Order{
    public:
        Blockade();
        Blockade(int orderId);
        Blockade(const Blockade &order);
        ~Blockade();
        Blockade(Player* orderHolder, Territory* target);
        Blockade &operator=(const Blockade& order);

        void execute();
        bool validate();
        string orderName = "Blockade";

        string getOrderName(){ return orderName;}
        friend ostream& operator<<(ostream& os, const Blockade& order);

        //Neutral player. Just for blockade class.
        Player* neutralPlayer;
};

class Airlift: public Order{
    public:
        Airlift();
        Airlift(int orderId);
        Airlift(const Airlift &order);
        ~Airlift();
        Airlift(Player* orderHolder, int army, Territory* source, Territory* target);
        Airlift &operator=(const Airlift& order);

        void execute();
        bool validate();
        string getOrderName(){ return orderName;}
        friend ostream& operator<<(ostream& os, const Airlift& order);
    private:
        string orderName="Airlift";
};

class Negotiate:public Order{
    public:
        Negotiate();
        Negotiate(int orderId);
        Negotiate(const Negotiate &order);
        ~Negotiate();
        Negotiate(Player* orderHolder, Player* negotiateWith);
        Negotiate& operator=(const Negotiate& order);

        void execute();
        bool validate();
        string getOrderName(){
            return orderName;
        }
        friend ostream& operator<<(ostream& os, const Negotiate& order);
    private:
        string orderName="Negotiate";
};
#endif
