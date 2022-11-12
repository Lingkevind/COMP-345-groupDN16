#include<iostream>
#include<vector>
#include<string>
#include "LoggingObserver.h"

using namespace std;

#ifndef ORDERS_H
#define ORDERS_H

class Order {
public:
    int orderId;
    Order();
    Order(int OrderId);
    Order(const Order& order);
    ~Order();
    Order& operator=(const Order& order);

    friend ostream& operator<<(ostream& os, const Order& order);
    virtual string getOrderName() {
        return orderName;
    }
private:
    string orderName = "unknown order";
};

//Below arxe the six orders mentioned in the assignemnt. Each subclass publicly inherits Order.

/***
 Deploy
 * **/
class Deploy :public Order {
public:
    Deploy();
    Deploy(int orderId);
    Deploy(const Deploy& order);
    ~Deploy();
    Deploy& operator=(const Deploy& order);

    void execute();
    bool validate();
    string getOrderName() { return orderName; }
    friend ostream& operator<<(ostream& os, const Deploy& order);
private:
    string orderName = "Deploy";
};

/***
Advance
 * **/

class Advance : public Order {
public:
    Advance();
    Advance(int orderId);
    Advance(const Advance& order);
    ~Advance();
    Advance& operator=(const Advance& order);

    void execute();
    bool validate();
    string getOrderName() { return orderName; }
    friend ostream& operator<<(ostream& os, const Advance& order);
private:
    string orderName = "Advance";
};

/***
 Bomb
 * **/

class Bomb : public Order {
public:
    Bomb();
    Bomb(int orderId);
    Bomb(const Bomb& order);
    ~Bomb();
    Bomb& operator=(const Bomb& order);

    void execute();
    bool validate();
    string getOrderName() { return orderName; }
    friend ostream& operator<<(ostream& os, const Bomb& order);
private:
    string orderName = "Bomb";
};

/***
 Blockade
 * **/

class Blockade : public Order {
public:
    Blockade();
    Blockade(int orderId);
    Blockade(const Blockade& order);
    ~Blockade();
    Blockade& operator=(const Blockade& order);

    void execute();
    bool validate();
    string getOrderName() { return orderName; }
    friend ostream& operator<<(ostream& os, const Blockade& order);
private:
    string orderName = "Blockade";
};

/***
 Airlift
 * **/

class Airlift : public Order {
public:
    Airlift();
    Airlift(int orderId);
    Airlift(const Airlift& order);
    ~Airlift();
    Airlift& operator=(const Airlift& order);

    void execute();
    bool validate();
    string getOrderName() { return orderName; }
    friend ostream& operator<<(ostream& os, const Airlift& order);
private:
    string orderName = "Airlift";
};

/***
 Negotiate
 * **/

class Negotiate :public Order {
public:
    Negotiate();
    Negotiate(int orderId);
    Negotiate(const Negotiate& order);
    ~Negotiate();
    Negotiate& operator=(const Negotiate& order);

    void execute();
    bool validate();
    string getOrderName() {
        return orderName;
    }
    friend ostream& operator<<(ostream& os, const Negotiate& order);
private:
    string orderName = "Negotiate";
};

/***
 OrderList
 * **/

class OrderList : ILoggable, Subject {
public:
    OrderList();
    ~OrderList();
    OrderList(const OrderList& list);
    OrderList& operator=(const OrderList& list);

    void add(Order* order);
    void remove(int position);
    void move(int intialPosition, int finalPosition);
    int listSize();
    const std::vector<Order*> getOrderList() {
        return orderList;
    }
    friend ostream& operator<<(ostream& os, OrderList& list);

    string StringToLog();

private:
    std::vector<Order*> orderList;
};

#endif