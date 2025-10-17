#include <iostream>

int main() {
    // Пункт 1 - массив размером 7 (4 + 3)
    std::cout << "=== Пункт 1 ===" << std::endl;
    const int N = 7;  // Размер массива = 4 + 3
    int arr[N];
    
    // Ввод массива
    std::cout << "Введите " << N << " чисел для массива:" << std::endl;
    for (int i = 0; i < N; ++i) {
        std::cin >> arr[i];
    }
    
    // Проверяем, все ли числа кратны 5
    bool all_multiple_of_5 = true;
    for (int i = 0; i < N; ++i) {
        if (arr[i] % 5 != 0) {
            all_multiple_of_5 = false;
            break;
        }
    }
    
    // Если все числа кратны 5 - сортируем массив
    if (all_multiple_of_5) {
        // Сортировка пузырьком (как в лекции)
        for (int i = 0; i < N - 1; ++i) {
            for (int j = i + 1; j < N; ++j) {
                if (arr[i] > arr[j]) {
                    // Меняем местами
                    int tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
            }
        }
        std::cout << "Массив упорядочен по возрастанию:" << std::endl;
    } else {
        std::cout << "Не все числа кратны 5, массив не изменен:" << std::endl;
    }
    
    // Вывод массива
    for (int i = 0; i < N; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    std::cout << std::endl;
    
    // Пункт 2 - матрица 3x4
    std::cout << "=== Пункт 2 ===" << std::endl;
    const int ROWS = 3;
    const int COLS = 4;
    int matrix[ROWS][COLS];
    
    // Ввод матрицы
    std::cout << "Введите матрицу " << ROWS << "x" << COLS << ":" << std::endl;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            std::cin >> matrix[i][j];
        }
    }
    
    // Ищем столбец с наибольшим количеством отрицательных чисел
    int max_negative_col = 0;
    int max_negative_count = 0;
    
    for (int j = 0; j < COLS; ++j) {
        int negative_count = 0;
        // Считаем отрицательные числа в столбце j
        for (int i = 0; i < ROWS; ++i) {
            if (matrix[i][j] < 0) {
                negative_count++;
            }
        }
        
        // Если нашли столбец с большим количеством отрицательных
        if (negative_count > max_negative_count) {
            max_negative_count = negative_count;
            max_negative_col = j;
        }
    }
    
    std::cout << "Столбец с наибольшим количеством отрицательных: " << max_negative_col << std::endl;
    std::cout << "Количество отрицательных в нем: " << max_negative_count << std::endl;
    
    // Заменяем все значения в найденном столбце на -1
    for (int i = 0; i < ROWS; ++i) {
        matrix[i][max_negative_col] = -1;
    }
    
    // Вывод измененной матрицы
    std::cout << "Измененная матрица:" << std::endl;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}