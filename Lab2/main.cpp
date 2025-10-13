#include <iostream>
#include <bitset>

int main() {
    // Пункт 1
    short A;
    std::cout << "Введите A: ";
    std::cin >> A;
    short i;
    std::cout << "Введите номер бита: ";
    std::cin >> i;
    if (i >= 0 && i <= 7) {   // проверяем что бы ввелось правильное кол-во битов, тк мы работаем с 0 до 7 битами
        short bit = ((A >> i) & 1); // сдвигаем бит в самую правую сторону, что бы потом извлечь и узнать какое значение
        std::cout << A << " = " << std::bitset<8>(A) << std::endl; // сначала выводим в десятичном - потом в двоичном
        std::cout << "Бит " << i << " = " << bit << std::endl; 
        if (bit != 0) {
            short B;
            short C;
            std::cout << "Введите B: ";
            std::cin >> B;
            std::cout << "Введите C: ";
            std::cin >> C;
            if ((A < B) && (B < C)) {  // если A меньше B и B меньше C
                short result = C - B - A;
                std::cout << result << " = " << std::bitset<8>(result) << std::endl;
            } else if (C != 0 && A % C == 0) {  // кратно ли А на С и обязательно проверяем С не равно 0
                short result = A / C + B;
                std::cout << result << " = " << std::bitset<8>(result) << std::endl;
            } else {
                short result = A + B + C;
                std::cout << result << " = " << std::bitset<8>(result) << std::endl; // "A + B + C = " , я бы вставил это вперед, что бы понимать какое действие происходит, но я так понял по условию выводить строго нужно в формате дестяич=двоич
            }
        } else {
            short result = A | A;  // побитово складываем число A с самим собой, тк | знак ИЛИ он если 1 накладывается на 0 то все равно выведет 1, это и есть побитовое сложение
            std::cout << result << " = " << std::bitset<8>(result) << std::endl;
        }
    } else {
        std::cout << "Номер бита должен быть от 0 до 7" << std::endl;
    }
    
    std::cout << std::endl; // Разделитель между заданиями
    
    // Пункт 2
    int N;
    std::cout << "Введите номер месяца: ";
    std::cin >> N;
    
    switch(N) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: 
            std::cout << "Дней в месяце - 31" << std::endl;
            break;
        case 4: case 6: case 9: case 11: 
            std::cout << "Дней в месяце - 30" << std::endl;
            break;
        case 2: 
            std::cout << "Дней в месяце - 28" << std::endl;
            break;
        default: 
            std::cout << "Неизвестный месяц" << std::endl;
            break;
    }
    
    return 0;
}
