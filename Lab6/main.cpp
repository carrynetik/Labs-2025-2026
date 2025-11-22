#include <iostream>
#include <cstdlib>

int* modifyMatrix(int**& mat, int& row_cnt, int& col_cnt, int A_val, int B_val, int C_val, int D_val) {
    int new_row_cnt = 2 + A_val;
    int new_col_cnt = 2 + B_val;

    // сохраняем исходные значения
    int saveA = mat[0][0];
    int saveB = mat[0][1]; 
    int saveC = mat[1][0];
    int saveD = mat[1][1];

    // изменяем размер матрицы
    mat = (int**)realloc(mat, new_row_cnt * sizeof(int*));
    for(int i = 0; i < new_row_cnt; i++) {
        if(i < row_cnt) {
            mat[i] = (int*)realloc(mat[i], new_col_cnt * sizeof(int));
            for(int j = col_cnt; j < new_col_cnt; j++) {
                mat[i][j] = 0;
            }
        } else {
            mat[i] = (int*)calloc(new_col_cnt, sizeof(int));
        }
    }

    row_cnt = new_row_cnt;
    col_cnt = new_col_cnt;

    // заполняем матрицу по условию
    for(int i = 0; i < row_cnt; i++) {
        for(int j = 0; j < col_cnt; j++) {
            if(i >= A_val && j >= B_val) {
                mat[i][j] = mat[i - A_val][j - B_val];
            }
            else {
                mat[i][j] = i * C_val + j * D_val;
            }
        }
    }
    
    // восстанавливаем исходные значения
    mat[A_val][B_val] = saveA; 
    mat[A_val][B_val+1] = saveB;
    mat[A_val+1][B_val] = saveC;
    mat[A_val+1][B_val+1] = saveD;
    
    // ищем строки с нулями
    int zero_count = 0;
    for (int i = 0; i < row_cnt; i++) {
        for (int j = 0; j < col_cnt; j++) {
            if (mat[i][j] == 0) {
                zero_count++;
                break;
            }
        }
    }
    
    int* result_arr = (int*)malloc((zero_count + 1) * sizeof(int));
    result_arr[0] = zero_count;
    
    int result_index = 1;
    for (int i = 0; i < row_cnt; i++) {
        for (int j = 0; j < col_cnt; j++) {
            if (mat[i][j] == 0) {
                result_arr[result_index++] = i;
                break;
            }
        }
    }
    
    return result_arr;
}

void deleteRows(int**& mat, int& row_cnt, int& col_cnt, int* rows_to_delete) {
    int delete_count = rows_to_delete[0];
    if (delete_count == 0) {
        std::cout << "нету строк для удаления" << std::endl;
        return;
    }
    
    // освобождаем удаляемые строки
    for (int k = 1; k <= delete_count; k++) {
        int row_to_delete = rows_to_delete[k];
        if (row_to_delete < row_cnt && mat[row_to_delete] != NULL) {
            free(mat[row_to_delete]);
            mat[row_to_delete] = NULL;
        }
    }
    
    // сдвигаем оставшиеся строки
    int new_index = 0;
    for (int i = 0; i < row_cnt; i++) {
        if (mat[i] != NULL) {
            if (new_index != i) {
                mat[new_index] = mat[i];
                mat[i] = NULL;
            }
            new_index++;
        }
    }
    
    // изменяем размер массива указателей
    if (new_index > 0) {
        int** temp = (int**)realloc(mat, new_index * sizeof(int*));
        if (temp != NULL) {
            mat = temp;
        }
        row_cnt = new_index;
    } else {
        free(mat);
        mat = NULL;
        row_cnt = 0;
    }
}

void showMatrix(int** mat, int row_cnt, int col_cnt) {
    for (int i = 0; i < row_cnt; i++) {
        for (int j = 0; j < col_cnt; j++) {
            std::cout << mat[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void pointerWork() {
    int x, y;

    std::cin >> x;
    std::cin >> y;
    
    int* ptr_x = new int(x);
    int* ptr_y = new int(y);
        
    *ptr_x *= 2;
    
    int tmp = *ptr_x;
    *ptr_x = *ptr_y;
    *ptr_y = tmp;
    
    x = *ptr_x;
    y = *ptr_y;

    std::cout << "X = " << x << ", Y = " << y << std::endl;

    delete ptr_x;
    delete ptr_y;
}

int main() {        
    int A, B, C, D;
    
    do {
        std::cout << "Введите A: ";
        std::cin >> A;
        if (A < 0) {
            std::cout << "A должно быть неотрицательным" << std::endl;
        }
    } while (A < 0);
    
    do {
        std::cout << "Введите B: ";
        std::cin >> B;
        if (B < 0) {
            std::cout << "B должно быть неотрицательным" << std::endl;
        }
    } while (B < 0);
    
    std::cout << "Введите C: ";
    std::cin >> C;
    std::cout << "Введите D: ";  
    std::cin >> D;
    
    int row_cnt = 2;
    int col_cnt = 2;
    int** mat = (int**)malloc(row_cnt * sizeof(int*));
    for (int i = 0; i < row_cnt; i++) {
        mat[i] = (int*)malloc(col_cnt * sizeof(int));
    }
    
    mat[0][0] = A;
    mat[0][1] = B;
    mat[1][0] = C;
    mat[1][1] = D;
    
    std::cout << "исходная матрица:" << std::endl;
    showMatrix(mat, row_cnt, col_cnt);
    
    int* zero_rows = modifyMatrix(mat, row_cnt, col_cnt, A, B, C, D);
    
    std::cout << "матрица после modifyMatrix:" << std::endl;
    showMatrix(mat, row_cnt, col_cnt);
    
    deleteRows(mat, row_cnt, col_cnt, zero_rows);
    
    std::cout << "матрица после удаления строк с нулями:" << std::endl;
    showMatrix(mat, row_cnt, col_cnt);
    
    free(zero_rows);

    if (mat != NULL) {
        for (int i = 0; i < row_cnt; i++) {
            if (mat[i] != NULL) {
                free(mat[i]);
            }
        }
        free(mat);
    }
    
    pointerWork();

    return 0;
}