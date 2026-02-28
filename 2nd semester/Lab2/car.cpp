#include "car.h"
#include <algorithm>
#include <map>

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
    cout << "vector cleared. Destructor called." << endl;
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

Car Car::operator+(const Car& other) {
    Car res = *this;
    res.brand = (rand() % 2 == 0) ? this->brand : other.brand;
    do {
        res.regNumber = genReg();
    } while (res.regNumber == this->regNumber || res.regNumber == other.regNumber);

    vector<string> combined = this->items;
    combined.insert(combined.end(), other.items.begin(), other.items.end());
    sort(combined.begin(), combined.end());
    res.items = combined;
    return res;
}

Car Car::operator-(const Car& other) {
    Car res = *this;
    res.brand = (rand() % 2 == 0) ? this->brand : other.brand;
    do {
        res.regNumber = genReg();
    } while (res.regNumber == this->regNumber || res.regNumber == other.regNumber);

    vector<string> unique_items;
    map<string, int> counts;
    for (const auto& i : this->items) counts[i]++;
    for (const auto& i : other.items) counts[i]++;
    for (const auto& pair : counts) {
        if (pair.second == 1) unique_items.push_back(pair.first);
    }
    res.items = unique_items;
    return res;
}

Car Car::operator/(const Car& other) {
    Car res = *this;
    res.brand = (rand() % 2 == 0) ? this->brand : other.brand;
    do {
        res.regNumber = genReg();
    } while (res.regNumber == this->regNumber || res.regNumber == other.regNumber);

    vector<string> common;
    for (const auto& i : this->items) {
        if (find(other.items.begin(), other.items.end(), i) != other.items.end()) {
            if (find(common.begin(), common.end(), i) == common.end()) {
                common.push_back(i);
            }
        }
    }
    res.items = common;
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
    cout << "Brand: " << brand << " | Model: " << model << " | Reg: " << regNumber << " | Items: ";
    if (items.empty()) cout << "none";
    else for (const auto& i : items) cout << i << " ";
    cout << endl;
}

string genReg() {
    string a = "ABEKMHOPCTYX";
    string n = "0123456789";
    string r;
    r += a[rand() % a.size()];
    for (int i = 0; i < 3; i++) r += n[rand() % 10];
    r += a[rand() % a.size()];
    r += a[rand() % a.size()];
    return r;
}