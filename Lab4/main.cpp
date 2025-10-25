#include <iostream>

int main() {
    // пункт 1
    std::cout << "Пункт 1" << std::endl;
    const int N = 7;
    int arr[N];
    std::cout << "Введите " << N << " чисел для массива:" << std::endl;
    for (int i = 0; i < N; ++i) {
        std::cin >> arr[i];
    }

    bool kratno_5 = true;
    for (int i = 0; i < N; ++i) {
        if (arr[i] % 5 != 0) {  
            kratno_5 = false;
            break; 
        }
    }

    if (kratno_5) {
        for (int i = 0; i < N - 1; ++i) { 
            for (int j = i + 1; j < N; ++j) {  
                if (arr[i] > arr[j]) { 
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
    for (int i = 0; i < N; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    std::cout << std::endl;
    


    // Пункт 2
    std::cout << "Пункт 2" << std::endl;
    const int stroki = 3;  
    const int stolb = 4;   
    int matrix[stroki][stolb];
    
    std::cout << "Введите матрицу " << stroki << "x" << stolb << ":" << std::endl;
    for (int i = 0; i < stroki; ++i) {     
        for (int j = 0; j < stolb; ++j) {  
            std::cin >> matrix[i][j];
        }
    }
    int max_stolb_otr = 0;      // номер столбца с макс количеством отрицательных
    int max_kolvo_otr = 0;      // максимальное количество отрицательных в столбце
    for (int j = 0; j < stolb; ++j) {  
        int kolvo_otr = 0;  // счетчик отрицательных чисел в текущем столбце
        for (int i = 0; i < stroki; ++i) {  // перебираем все строки в столбце j
            if (matrix[i][j] < 0) {
                kolvo_otr++;
            }
        }
        if (kolvo_otr > max_kolvo_otr) {
            max_kolvo_otr = kolvo_otr; 
            max_stolb_otr = j;         
        }
    }
    std::cout << "Столбец с наибольшим количеством отрицательных: " << max_stolb_otr << std::endl;
    std::cout << "Количество отрицательных в нем: " << max_kolvo_otr << std::endl;
    for (int i = 0; i < stroki; ++i) {
        matrix[i][max_stolb_otr] = -1;  // заменяем каждое число в столбце на -1
    }
    std::cout << "Измененная матрица:" << std::endl;
    for (int i = 0; i < stroki; ++i) {
        for (int j = 0; j < stolb; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}