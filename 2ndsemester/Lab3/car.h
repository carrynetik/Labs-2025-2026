#ifndef CAR_H
#define CAR_H

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
    struct Radio {
        string brand;
        int volume;

        Radio() {
            brand = "Pioneer";
            volume = 10;
        }

        Radio(string b, int v) {
            brand = b;
            volume = v;
        }

        Radio operator++() {
            volume = volume + 1;
            return *this;
        }

        Radio operator--() {
            volume = volume - 1;
            return *this;
        }

        void show() {
            cout << "Радио: " << brand << ", громкость " << volume << endl;
        }
    };

    bool hasRadio;
    Radio radio;

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
    void setRadio(string b, int v);
    void printInfo();

    string getReg() const { return regNumber; }
    string getBrand() const { return brand; }
    int getMileage() const { return mileage; }
};

string genReg();

#endif