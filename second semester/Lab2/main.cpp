#include "car.h"

int main() {
    srand(time(0));

    Car a("Audi", "A6", "A111AA", genReg(), 50000);
    a.addItem("spare_wheel");
    a.addItem("tools");
    a.addItem("jacket");

    Car b("BMW", "M5", "B222BB", genReg(), 30000);
    b.addItem("jacket");
    b.addItem("first_aid_kit");
    b.addItem("tools");

    cout << "Car A: "; a.printInfo();
    cout << "Car B: "; b.printInfo();

    Car c = a + b;
    cout << "A + B: "; c.printInfo();

    Car d = a - b;
    cout << "A - B: "; d.printInfo();

    Car e = a / b;
    cout << "A / B: "; e.printInfo();

    return 0;
}