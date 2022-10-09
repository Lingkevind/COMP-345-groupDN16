#include<iostream>
#include<vector>
#include<string>
using namespace std;

#ifndef ORDERS_H
#define ORDERS_H

class Order{
    public:
        int orderId;
        Order();
        Order(int OrderId);
        Order(const Order& order);
        ~Order();
        Order& operator=(const Order& order);

        friend ostream& operator<<(ostream& os, const Order& order);
        string getOrderName(){
            return orderName;
        }
    private:
        string orderName="unknown order";
};

// class OrderList{
//     public:
//         OrderList();
//         ~OrderList();
//         OrderList (const OrderList& list);
//         void add();
//         void remove();
//         void move();
//         int listSize();
//         const std::vector<Order*> getOrderList(){
//             return orderList;
//         }
    
//     private:
//         std::vector<Order*> orderList;
// };

// //Below arxe the six orders mentioned in the assignemnt. Each subclass publicly inherits Order.
// //All the functions are the same except A parameterised is added in the subclasses which takes an Order.

class Deploy:public Order{
    public:
        Deploy();
        Deploy(int orderId);
        Deploy(const Deploy &order);
        ~Deploy();
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
        Blockade &operator=(const Blockade& order);

        void execute();
        bool validate();
        string orderName = "Blockade";

        string getOrderName(){ return orderName;}
        friend ostream& operator<<(ostream& os, const Blockade& order);
    private:
};

class Airlift: public Order{
    public:
        Airlift();
        Airlift(int orderId);
        Airlift(const Airlift &order);
        ~Airlift();
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