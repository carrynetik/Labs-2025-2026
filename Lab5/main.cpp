#include <iostream>
#include <cmath>

// Функция для одного числа - сколько раз повторяется максимальная цифра
int func_odin_chislo(int x) {
    std::cout << "исп. функция для одного числа" << std::endl;
    
    if (x == 0) {
        return 1; // для числа 0 максимальная цифра 0 повторяется 1 раз
    }
    
    // Находим максимальную цифру
    int max_cifra = 0;
    int temp = std::abs(x); // берем модуль чтобы работать с положительным числом
    while (temp > 0) {
        int cifra = temp % 10; // получаем последнюю цифру
        if (cifra > max_cifra) {
            max_cifra = cifra; // обновляем максимальную цифру
        }
        temp = temp / 10; // убираем последнюю цифру
    }
    
    // Считаем сколько раз повторяется максимальная цифра
    int count = 0;
    temp = std::abs(x);
    while (temp > 0) {
        int cifra = temp % 10;
        if (cifra == max_cifra) {
            count++; // увеличиваем счетчик если цифра равна максимальной
        }
        temp = temp / 10;
    }
    
    return count;
}

// Функция для трех чисел
int func_tri_chisla(int a, int b, int c) {
    std::cout << "исп. функция для трех чисел" << std::endl;
    
    // Проверяем, все ли числа разные
    if (a != b && a != c && b != c) {
        // Средняя по модулю величина
        int sum = std::abs(a) + std::abs(b) + std::abs(c);
        return sum / 3; // среднее арифметическое модулей
    } else {
        // Иначе находим минимальное число
        int min_chislo = a;
        if (b < min_chislo) min_chislo = b;
        if (c < min_chislo) min_chislo = c;
        return min_chislo;
    }
}

// Функция для пункта 2 (void функция)
void func_punkt2() {
    std::cout << "исп. void функция для пункта 2" << std::endl;
    std::cout << "Эта функция ничего не возвращает, просто выводит текст" << std::endl;
    std::cout << "Выполняется дополнительное задание" << std::endl;
}

int main() {
    int punkt;
    std::cout << "Введите номер пункта (1 или 2): ";
    std::cin >> punkt;
    
    if (punkt == 1) {
        int a, b, c;
        std::cout << "Введите три числа: ";
        std::cin >> a >> b >> c;
        
        // Правило: если число = 0, считаем что его нет
        int count_chisel = 0;
        if (a != 0) count_chisel++;
        if (b != 0) count_chisel++;
        if (c != 0) count_chisel++;
        
        int result;
        if (count_chisel == 1) {
            // Находим какое число не равно 0
            int chislo = (a != 0) ? a : ((b != 0) ? b : c);
            result = func_odin_chislo(chislo);
            std::cout << "Результат для одного числа: " << result << std::endl;
        } else if (count_chisel == 3) {
            result = func_tri_chisla(a, b, c);
            std::cout << "Результат для трех чисел: " << result << std::endl;
        } else {
            // Для двух чисел - используем функцию для трех, но одно число будет 0
            // По правилу 0 считается "отсутствующим", но для функции передаем как есть
            result = func_tri_chisla(a, b, c);
            std::cout << "Результат: " << result << std::endl;
        }
        
    } else if (punkt == 2) {
        func_punkt2();
    } else {
        std::cout << "Неверный номер пункта" << std::endl;
    }
    
    return 0;
}