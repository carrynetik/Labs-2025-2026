#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>

using namespace std;

class Car {
public:
    string brand;

    // конструктор по умолчанию
    Car() : brand("Mercedes"), model("GL500"),
        bodyNumber("AB1234"), regNumber("M500MM"), mileage(160000) {
    }

    // конструктор с параметрами
    Car(string brand, string model, string bodyNumber,
        string regNumber, int mileage)
        : brand(brand), model(model), mileage(mileage) {
        setBodyNumber(bodyNumber);
        setRegNumber(regNumber);
    }

    // конструктор копирования
    Car(const Car& other) {
        brand = other.brand;
        model = other.model;
        bodyNumber = other.bodyNumber;
        regNumber = other.regNumber;
        mileage = other.mileage;
    }

    // деструктор
    ~Car() {
        cout << "деструктор car вызван" << endl;
    }

    // получение данных
    string getBrand() const { return brand; }
    string getModel() const { return model; }
    string getBodyNumber() const { return bodyNumber; }
    string getRegNumber() const { return regNumber; }
    int getMileage() const { return mileage; }

    void setBodyNumber(const string& number) {
        if (number.length() != 6)
            throw invalid_argument("неверная длина номера кузова");

        for (char c : number) {
            if (!isalnum(c))
                throw invalid_argument("неверный формат номера кузова");
        }

        bodyNumber = number;
    }

    void setRegNumber(const string& number) {
        if (number.length() != 6)
            throw invalid_argument("неверная длина гос номера");

        if (!isalpha(number[0]) ||
            !isdigit(number[1]) ||
            !isdigit(number[2]) ||
            !isdigit(number[3]) ||
            !isalpha(number[4]) ||
            !isalpha(number[5])) {
            throw invalid_argument("формат гос номера A555AA");
        }

        regNumber = number;
    }

    // изменение пробега
    void rollbackMileage(int x) {
        if (x <= 0)
            throw invalid_argument("некорректное значение");

        if (mileage - x < 0)
            throw invalid_argument("пробег не может быть отрицательным");

        mileage -= x;
    }

    // вывод информации
    void printInfo() const {
        cout << "Марка: " << brand << endl;
        cout << "Модель: " << model << endl;
        cout << "Номер кузова: " << bodyNumber << endl;
        cout << "Гос. номер: " << regNumber << endl;
        cout << "Пробег: " << mileage << endl;
    }

protected:
    string model;

private:
    string bodyNumber;
    string regNumber;
    int mileage;
};

int main() {
    setlocale(LC_ALL, "russian");

    try {
        Car car;

        car.brand = "Mercedes";
        car.setBodyNumber("ZX9087");
        car.setRegNumber("A777AA");
        car.rollbackMileage(500);
        car.printInfo();
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }

    return 0;
}
