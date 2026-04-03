#include "car.h"
#include "garage.h"
#include <iostream>
#include <vector>
using namespace std;

void myLabRating() {
    cout << "\nОценка работы 3:" << endl;
    cout << "Интерес: 8/10" << endl;
    cout << "Наполненность: 8/10" << endl;
    cout << "Сложность: 7/10" << endl;
}

int main() {
    srand(time(0));
    setlocale(LC_ALL, "russian");

    Car a("Audi", "A6", "A111AA", genReg(), 50000);
    a.addItem("spare_wheel");
    a.addItem("tools");

    Car b("BMW", "M5", "B222BB", genReg(), 30000);
    b.addItem("jacket");
    b.addItem("first_aid_kit");

    Car c("Lada", "Vesta", "L333LL", genReg(), 10000);
    c.addItem("tools");

    cout << "Машина 1:" << endl;
    a.printInfo();

    cout << "Машина 2:" << endl;
    b.printInfo();

    cout << "Бренд первой: " << a.getBrand() << endl;
    cout << "Пробег второй: " << b.getMileage() << endl;

    a.rollbackMileage(500);
    cout << "Скрутили пробег первой: " << a.getMileage() << endl << endl;

    a.setRadio("Sony", 15);
    cout << "Первая после установки радио:" << endl;
    a.printInfo();

    ++a.radio;
    cout << "Громкость вверх: " << a.radio.volume << endl;
    --a.radio;
    cout << "Громкость вниз: " << a.radio.volume << endl << endl;

    cout << "Тест сложения (A + B):" << endl;
    Car d = a + b;
    d.printInfo();

    cout << "Тест пересечения (A / B):" << endl;
    Car e = a / b;
    e.printInfo();

    Garage garage(5);

    garage.addCar(&b);
    garage.addCar(&c);
    garage.addCar(&d);
    garage.addCar(&a);

    garage.show();

    garage.sortByBrand();
    garage.show();

    myLabRating();

    return 0;
}