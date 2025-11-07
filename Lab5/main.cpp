#include <iostream>
#include <cmath>
#include <algorithm> //для min и max функций

int func_odno_chislo(int x) {
    std::cout << "исп. функция для одного числа" << std::endl;
    if (x == 0) return 1;
    
    x = abs(x); // модуль
    int max_cifra = 0;
    int count_max = 0;
    
    int temp = x;   // рабираем на цифры
    while (temp > 0) {
        int cifra = temp % 10;
        if (cifra > max_cifra) max_cifra = cifra;
        temp /= 10;
    }
    
    temp = x;
    while (temp > 0) {
        int cifra = temp % 10;
        if (cifra == max_cifra) count_max++; // если макс число вновь повторилось то считаем
        temp /= 10;
    }
    
    return count_max; // сколько раз встретилась максимальная цифра
}

int func_tri_chisla(int a, int b, int c) {
    std::cout << "исп. функция для трех чисел" << std::endl;
    
    if (a != b && a != c && b != c) {
        return (abs(a) + abs(b) + abs(c)) / 3;
    } else { // если присутствуют одинаковые, возвращаем минимальное число
        return std::min(a, std::min(b, c));
    }
}

void laba1_volume() {
    std::cout << "исп. void функция для объема сферы" << std::endl;
    
    const float P = 13.1415;
    std::cout << "Тип: float" << std::endl;
    std::cout << "Размер в байтах: " << sizeof(P) << std::endl;
    float maxsize = __FLT_MAX__;
    float minsize = __FLT_MIN__;
    std::cout << "Минимальное значение: " << minsize << std::endl;
    std::cout << "Максимальное значение: " << maxsize << std::endl;
    
    int radius;
    std::cout << "Введите радиус: ";
    std::cin >> radius;
    
    float volume = (4 * P * pow(radius, 3)) / 3;
    float square = 4 * P * pow(radius, 2);
    
    std::cout << "V = " << volume << std::endl;
    std::cout << "S = " << square << std::endl;
}

int main() {
    std::cout << "Введите номер пункта (1 или 2): ";
    
    int point;
    std::cin >> point;

    if (point == 1) {
        std::cout << "Введите три числа: ";
        int a, b, c;
        std::cin >> a >> b >> c;
        
        int count = 0;
        if (a != 0) count++;
        if (b != 0) count++;
        if (c != 0) count++;
        
        if (count == 1) {
            int num;
            if (a != 0) num = a;
            else if (b != 0) num = b;
            else num = c;
            std::cout << "Результат: " << func_odno_chislo(num) << std::endl;
        } 
        else if (count == 3) {
            std::cout << "Результат: " << func_tri_chisla(a, b, c) << std::endl;
        }
        else {
            std::cout << "Нужно 1 или 3 ненулевых числа" << std::endl;
        }
    } 
    else if (point == 2) {
        laba1_volume();
    }
    else {
        std::cout << "Неверный пункт" << std::endl;
    }
    
    return 0;
}