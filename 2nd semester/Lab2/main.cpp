#include "car.h"

int main() {
    srand(time(0));

    Car a;
    a.addItem("wheel");
    a.addItem("engine");
    a.addItem("door");

    Car b("BMW", "X5", "B123CD", genReg(), 120000);
    b.addItem("door");
    b.addItem("mirror");

    Car c = a + b;
    Car d = a - b;
    Car e = a / b;

    a.printInfo();
    b.printInfo();
    c.printInfo();
    d.printInfo();
    e.printInfo();

    return 0;
}
