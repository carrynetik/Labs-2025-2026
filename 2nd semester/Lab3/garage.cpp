#include "garage.h"
#include <iostream>
using namespace std;

Garage::Garage() {
    maxCapacity = 10;
}

Garage::Garage(int capacity) {
    maxCapacity = capacity;
}

Garage::Garage(Garage &other) {
    maxCapacity = other.maxCapacity;
    cars = other.cars;
}

Garage::~Garage() {
    cout << "Гараж очищен" << endl;
    cars.clear();
}

void Garage::addCar(Car* car) {
    if (cars.size() < maxCapacity) {
        cars.push_back(car);
        cout << "Добавлено авто: " << car->getBrand() << endl;
    } else {
        cout << "Нет мест в гараже." << endl;
    }
}

void Garage::sortByBrand() {
    for (int i = 0; i < cars.size(); i++) {
        for (int j = 0; j < cars.size() - 1; j++) {
            if (cars[j]->getBrand() > cars[j + 1]->getBrand()) {
                Car* temp = cars[j];
                cars[j] = cars[j + 1];
                cars[j + 1] = temp;
            }
        }
    }
    cout << "Сортировка по марке завершена." << endl;
}

void Garage::show() {
    cout << "\nГараж (мест: " << maxCapacity << ")" << endl;
    cout << "Занято: " << cars.size() << endl;
    for (int i = 0; i < cars.size(); i++) {
        cout << i + 1 << ". ";
        cars[i]->printInfo();
    }
}s