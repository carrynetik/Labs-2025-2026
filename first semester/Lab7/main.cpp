#include <iostream>
#include <vector>
#include <array>
#include <cstdlib>
#include <ctime>

// Пункт 1 - Используем vector
void showArray(const std::vector<int>& arr) {
    std::cout << "[";
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i];
        if (i + 1 < arr.size()) {
            std::cout << " ";
        }
    }
    std::cout << "]" << std::endl;
}

void addToStart(std::vector<int>& arr, int num) {
    arr.insert(arr.begin(), num);
}

void addToEnd(std::vector<int>& arr, int num) {
    arr.push_back(num);
}

void clearArray(std::vector<int>& arr) {
    arr.clear();
}

std::vector<int> findInArray(const std::vector<int>& arr, int num) {
    std::vector<int> indexes;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == num) {
            indexes.push_back(i);
        }
    }
    return indexes;
}

// Вариант 4 - исправленная версия
void doVariant4(std::vector<int>& arr) {
    if (arr.empty()) {
        std::cout << "Массив пуст" << std::endl;
        return;
    }
    
    // Ищем минимальное по модулю ненулевое число
    bool found = false;
    int min_val = 0;
    
    for (int i = 0; i < arr.size(); i++) {
        int val = arr[i];
        if (val != 0) {
            if (!found || std::abs(val) < std::abs(min_val)) {
                min_val = val;
                found = true;
            }
        }
    }
    
    if (!found) {
        std::cout << "Нет ненулевых чисел" << std::endl;
        return;
    }
    
    // Добавляем нули
    int zero_count = std::abs(min_val);
    std::cout << "Добавляем " << zero_count << " нулей" << std::endl;
    
    for (int i = 0; i < zero_count; i++) {
        arr.push_back(0);
    }
}

// Пункт 2 - Используем array
// Передача по значению - создается копия
void sortByValue(std::array<int, 10> arr) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

// Передача по ссылке - работаем с оригиналом
void sortByReference(std::array<int, 10>& arr) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

// Передача по указателю - работаем через адрес
void sortByPointer(std::array<int, 10>* arr) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9 - i; j++) {
            if ((*arr)[j] > (*arr)[j + 1]) {
                int tmp = (*arr)[j];
                (*arr)[j] = (*arr)[j + 1];
                (*arr)[j + 1] = tmp;
            }
        }
    }
}

void showArrayInfo(const std::array<int, 10>& arr, const std::string& name) {
    std::cout << name << ": [";
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i];
        if (i + 1 < arr.size()) {
            std::cout << " ";
        }
    }
    std::cout << "]" << std::endl;
}

int main() {
    // Инициализация для случайных чисел
    std::srand(std::time(0));
    
    // Начальный массив для пункта 1
    std::vector<int> my_arr = {5, -3, 2, 0, -1, 4};
    
    bool running = true;
    
    while (running) {
        std::cout << std::endl;
        std::cout << "Меню:" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "1. Просмотр массива" << std::endl;
        std::cout << "2. Добавить в начало" << std::endl;
        std::cout << "3. Добавить в конец" << std::endl;
        std::cout << "4. Очистить массив" << std::endl;
        std::cout << "5. Поиск элемента" << std::endl;
        std::cout << "6. Вариант 4" << std::endl;
        std::cout << "7. Сортировки (array)" << std::endl;
        std::cout << "8. Пункт 3 - объяснение" << std::endl;
        std::cout << "Выбор: ";
        
        int choice;
        std::cin >> choice;
        std::cout << std::endl;
        
        switch(choice) {
            case 0:
                running = false;
                break;
                
            case 1:
                std::cout << "Массив: ";
                showArray(my_arr);
                break;
                
            case 2: {
                std::cout << "Число для добавления: ";
                int num;
                std::cin >> num;
                std::cout << "До: ";
                showArray(my_arr);
                addToStart(my_arr, num);
                std::cout << "После: ";
                showArray(my_arr);
                break;
            }
                
            case 3: {
                std::cout << "Число для добавления: ";
                int num;
                std::cin >> num;
                std::cout << "До: ";
                showArray(my_arr);
                addToEnd(my_arr, num);
                std::cout << "После: ";
                showArray(my_arr);
                break;
            }
                
            case 4:
                std::cout << "До: ";
                showArray(my_arr);
                clearArray(my_arr);
                std::cout << "После: ";
                showArray(my_arr);
                break;
                
            case 5: {
                std::cout << "Искать число: ";
                int num;
                std::cin >> num;
                std::vector<int> result = findInArray(my_arr, num);
                if (result.empty()) {
                    std::cout << "Не найдено" << std::endl;
                } else {
                    std::cout << "Индексы: [";
                    for (int i = 0; i < result.size(); i++) {
                        std::cout << result[i];
                        if (i + 1 < result.size()) {
                            std::cout << ",";
                        }
                    }
                    std::cout << "]" << std::endl;
                }
                break;
            }
                
            case 6:
                std::cout << "До: ";
                showArray(my_arr);
                doVariant4(my_arr);
                std::cout << "После: ";
                showArray(my_arr);
                break;
                
            case 7: {
                // Создаем array с случайными числами
                std::array<int, 10> arr;
                std::cout << "Исходный массив (random [-10;10]):" << std::endl;
                for (int i = 0; i < 10; i++) {
                    arr[i] = (std::rand() % 21) - 10; // от -10 до 10
                }
                showArrayInfo(arr, "Исходный ");
                
                // Копии для разных способов передачи
                std::array<int, 10> arr1 = arr;
                std::array<int, 10> arr2 = arr;
                std::array<int, 10> arr3 = arr;
                
                // Сортировка разными способами
                sortByValue(arr1);
                showArrayInfo(arr1, "По значению  ");
                
                sortByReference(arr2);
                showArrayInfo(arr2, "По ссылке    ");
                
                sortByPointer(&arr3);
                showArrayInfo(arr3, "По указателю ");
                
                std::cout << std::endl;
                std::cout << "Разница:" << std::endl;
                std::cout << "- По значению: сортируется копия, оригинал не меняется" << std::endl;
                std::cout << "- По ссылке: сортируется оригинал" << std::endl;
                std::cout << "- По указателю: тоже оригинал, но через адрес" << std::endl;
                break;
            }
                
            case 8:
                std::cout << "Пункт 3 - Объяснение выбора:" << std::endl;
                std::cout << std::endl;
                std::cout << "В пункте 1 использовал vector потому что:" << std::endl;
                std::cout << "- Нужно добавлять/удалять элементы" << std::endl;
                std::cout << "- Размер меняется динамически" << std::endl;
                std::cout << "- Есть функции push_back, insert, clear" << std::endl;
                std::cout << std::endl;
                std::cout << "В пункте 2 использовал array потому что:" << std::endl;
                std::cout << "- Размер фиксированный (10 элементов)" << std::endl;
                std::cout << "- Нужно сравнивать способы передачи" << std::endl;
                std::cout << "- Безопаснее для демонстрации копирования" << std::endl;
                std::cout << std::endl;
                std::cout << "vector и array одинаковы когда:" << std::endl;
                std::cout << "- Размер массива известен заранее" << std::endl;
                std::cout << "- Не нужно изменять размер во время работы" << std::endl;
                std::cout << "- Нужна простая работа с данными" << std::endl;
                break;
                
            default:
                std::cout << "Неверный выбор" << std::endl;
        }
    }
    
    return 0;
}