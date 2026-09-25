#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <ctime>
#include <cstdlib>

using namespace std;

class Car {
private:
    string brand;
    string model;
    string bodyNumber;
    string regNumber;
    int mileage;
    vector<string> items;

    static const int BODY_LEN = 6;
    bool checkBody(string body);
    bool checkReg(string reg);

public:
    Car();
    Car(string b, string m, string body, string reg, int mil);
    Car(const Car& other);
    Car& operator=(const Car& other);
    ~Car();

    Car operator+(const Car& other);
    Car operator-(const Car& other);
    Car operator/(const Car& other);

    void setBrand(string b);
    void setModel(string m);
    void setBody(string body);
    void setReg(string reg);
    void setMileage(int m);

    void rollbackMileage(int km);
    void addItem(string item);
    void removeItem(int id);
    void printInfo();

    string getReg() const { return regNumber; }
};

string genReg();