#include "car.h"

bool Car::checkBody(string body) {
    return body.size() == BODY_LEN;
}

bool Car::checkReg(string reg) {
    if (reg.size() != 6) return false;
    if (!isalpha(reg[0])) return false;
    for (int i = 1; i <= 3; i++)
        if (!isdigit(reg[i])) return false;
    if (!isalpha(reg[4]) || !isalpha(reg[5])) return false;
    return true;
}

Car::Car() {
    brand = "Mercedes";
    model = "GL500";
    bodyNumber = "X500XH";
    regNumber = "A555AA";
    mileage = 160000;
}

Car::Car(string b, string m, string body, string reg, int mil) {
    setBrand(b);
    setModel(m);
    setBody(body);
    setReg(reg);
    setMileage(mil);
}

Car::Car(const Car& other) {
    brand = other.brand;
    model = other.model;
    bodyNumber = other.bodyNumber;
    regNumber = other.regNumber;
    mileage = other.mileage;
    items = other.items;
}

Car::~Car() {
    items.clear();
    items.shrink_to_fit();
    cout << "vector cleared\n";
}

Car& Car::operator=(const Car& other) {
    if (this == &other) return *this;

    brand = other.brand;
    model = other.model;
    bodyNumber = other.bodyNumber;
    regNumber = other.regNumber;
    mileage = other.mileage;
    items = other.items;

    return *this;
}

Car Car::operator+(Car& other) {
    Car res = *this;
    for (auto& i : other.items)
        res.items.push_back(i);
    return res;
}

Car Car::operator-(Car& other) {
    Car res = *this;
    for (auto& i : other.items) {
        for (int j = 0; j < res.items.size(); j++) {
            if (res.items[j] == i) {
                res.items.erase(res.items.begin() + j);
                break;
            }
        }
    }
    return res;
}

Car Car::operator/(Car& other) {
    Car res = *this;
    vector<string> tmp;

    for (auto& i : items)
        for (auto& j : other.items)
            if (i == j) tmp.push_back(i);

    res.items = tmp;
    return res;
}

void Car::setBrand(string b) { brand = b; }
void Car::setModel(string m) { model = m; }

void Car::setBody(string body) {
    if (!checkBody(body)) throw invalid_argument("bad body");
    bodyNumber = body;
}

void Car::setReg(string reg) {
    if (!checkReg(reg)) throw invalid_argument("bad reg");
    regNumber = reg;
}

void Car::setMileage(int m) {
    if (m < 0) throw invalid_argument("bad mileage");
    mileage = m;
}

void Car::rollbackMileage(int km) {
    if (km > mileage) mileage = 0;
    else mileage -= km;
}

void Car::addItem(string item) {
    items.push_back(item);
}

void Car::removeItem(int id) {
    if (id >= items.size()) return;
    items.erase(items.begin() + id);
}

void Car::printInfo() {
    cout << "\nBrand: " << brand
         << "\nModel: " << model
         << "\nBody: " << bodyNumber
         << "\nReg: " << regNumber
         << "\nMileage: " << mileage
         << "\nItems: ";

    for (auto& i : items) cout << i << " ";
    cout << endl;
}

string genReg() {
    string a = "ABEKMHOPCTYX";
    string n = "0123456789";

    string r;
    r += a[rand() % a.size()];
    for (int i = 0; i < 3; i++)
        r += n[rand() % 10];
    r += a[rand() % a.size()];
    r += a[rand() % a.size()];

    return r;
}
