#include <iostream>
#include <cmath>

int main() {
    int r;
    const float konstanta = 13.1415;
    std::cout << "Введите радиус: ";
    std::cin >> r;
    std::cout << "Тип: float" << std::endl; //выбрал float, тк число с плавающей запятой(не целое)
    std::cout << "Размер в байтах: " << sizeof(konstanta) << std::endl;
    // float minsize = pow(2, -126);
    // float maxsize = (2 - pow(2, -23)) * pow(2, 127);   изначально думал так, но потом увидел что есть int_max, почему то на маке надо с двух сторон нижнее подчеркивание
    float maxsize = __FLT_MAX__; // на маке именно такой вариант
    float minsize = __FLT_MIN__;
    std::cout << "Минимальное значениe: " << minsize << std::endl;
    std::cout << "Максимальное значение: " << maxsize << std::endl;
    float V = (4 * konstanta * pow(r, 3)) / 3;
    float S = 4 * konstanta * pow(r, 2);
    std::cout << "V = " << V << std::endl;
    std::cout << "S = " << S << std::endl;
    return 0;
}
