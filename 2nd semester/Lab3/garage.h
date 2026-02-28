#ifndef GARAGE_H
#define GARAGE_H

#include "car.h"
#include <vector>
#include <iostream>
using namespace std;

class Garage {
public:
    vector<Car*> cars;
    int maxCapacity;

    Garage();
    Garage(int capacity);
    Garage(Garage &other);
    ~Garage();

    void addCar(Car* car);
    void sortByBrand();
    void show();
};

#endif