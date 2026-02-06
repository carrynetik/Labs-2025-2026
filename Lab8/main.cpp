#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>

using namespace std;

class Car {
public:
    string brand;

    Car() : brand("Mercedes"), model("GL500"),
        bodyNumber("AB1234"), regNumber("M500MM"), mileage(160000) {
    }

    Car(string brand, string model, string bodyNumber,
        string regNumber, int mileage)
        : brand(brand), model(model), mileage(mileage) {
        setBodyNumber(bodyNumber);
        setRegNumber(regNumber);
    }

    Car(const Car& other) {
        brand = other.brand;
        model = other.model;
        bodyNumber = other.bodyNumber;
        regNumber = other.regNumber;
        mileage = other.mileage;
    }

    ~Car() {
        cout << "Объект Car удалён из памяти" << endl;
    }

    string getBrand() const { return brand; }
    string getModel() const { return model; }
    string getBodyNumber() const { return bodyNumber; }
    string getRegNumber() const { return regNumber; }
    int getMileage() const { return mileage; }

    void setBodyNumber(const string& number) {
        if (number.size() != 6)
            throw invalid_argument("Некорректная длина номера кузова");

        for (char c : number) {
            if (!isalnum(c))
                throw invalid_argument("Номер кузова содержит недопустимые символы");
        }

        bodyNumber = number;
    }

    void setRegNumber(const string& number) {
        if (number.size() != 6)
            throw invalid_argument("Неверная длина госномера");

        if (!(isalpha(number[0]) &&
              isdigit(number[1]) &&
              isdigit(number[2]) &&
              isdigit(number[3]) &&
              isalpha(number[4]) &&
              isalpha(number[5]))) {
            throw invalid_argument("Госномер не соответствует формату А555АА");
        }

        regNumber = number;
    }

    void rollbackMileage(int value) {
        if (value <= 0)
            throw invalid_argument("Значение скрутки некорректно");

        if (mileage - value < 0)
            throw invalid_argument("Пробег не может быть меньше нуля");

        mileage -= value;
    }

    void printInfo() const {
        cout << "Марка: " << brand << endl;
        cout << "Модель: " << model << endl;
        cout << "Кузов: " << bodyNumber << endl;
        cout << "Госномер: " << regNumber << endl;
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
        cout << "Ошибка выполнения: " << e.what() << endl;
    }

    return 0;
}
