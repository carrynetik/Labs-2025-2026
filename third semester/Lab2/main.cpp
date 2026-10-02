#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

class JaggedArray {
private:
    std::vector<std::vector<std::string>> array;

public:
    bool read_file(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            return false;
        }

        array.clear();
        std::string line;

        while (std::getline(file, line)) {
            std::istringstream stream(line);
            std::vector<std::string> row;
            std::string item;

            while (stream >> item) {
                row.push_back(item);
            }

            array.push_back(row);
        }

        return true;
    }

    std::vector<std::string>& operator[](std::size_t i) {
        return array.at(i);
    }

    const std::vector<std::string>& operator[](std::size_t i) const {
        return array.at(i);
    }

    void delete_element(std::size_t i, std::size_t j) {
        if (i < array.size() && j < array[i].size()) {
            array[i].erase(array[i].begin() + j);
        }
    }

    void delete_element(const std::string& item) {
        for (std::size_t i = 0; i < array.size(); i++) {
            for (std::size_t j = 0; j < array[i].size();) {
                if (array[i][j] == item) {
                    array[i].erase(array[i].begin() + j);
                } else {
                    j++;
                }
            }
        }
    }

    void add_endline(std::size_t k, const std::string& item) {
        if (k < array.size()) {
            array[k].push_back(item);
        }
    }

    JaggedArray operator-(const JaggedArray& other) const {
        JaggedArray result = *this;

        for (std::size_t i = 0; i < result.array.size(); i++) {
            if (i >= other.array.size()) {
                continue;
            }

            for (std::size_t j = 0; j < result.array[i].size(); j++) {
                if (j >= other.array[i].size()) {
                    continue;
                }

                std::string& item = result.array[i][j];
                const std::string& part = other.array[i][j];

                if (!part.empty() && item.size() >= part.size()) {
                    std::size_t position = item.size() - part.size();

                    if (item.compare(position, part.size(), part) == 0) {
                        item.erase(position);
                    }
                }
            }
        }

        return result;
    }

    JaggedArray& operator--() {
        for (std::size_t i = 0; i < array.size(); i++) {
            for (std::size_t j = 0; j < array[i].size(); j++) {
                for (std::size_t k = 0; k < array[i][j].size(); k++) {
                    char& symbol = array[i][j][k];

                    if (symbol == '0') {
                        symbol = '9';
                    } else if (symbol >= '1' && symbol <= '9') {
                        symbol--;
                    }
                }
            }
        }

        return *this;
    }

    JaggedArray operator--(int) {
        JaggedArray previous = *this;
        --(*this);
        return previous;
    }

    void sort_rows() {
        for (std::size_t i = 0; i < array.size(); i++) {
            std::sort(array[i].begin(), array[i].end());
        }
    }

    void print() const {
        for (std::size_t i = 0; i < array.size(); i++) {
            std::cout << "\033[" << 31 + i % 6 << "m";

            for (std::size_t j = 0; j < array[i].size(); j++) {
                std::cout << '[' << array[i][j] << "] ";
            }

            std::cout << "\033[0m\n";
        }
    }
};

int main() {
    std::string filename = __FILE__;
    std::size_t position = filename.find_last_of("/\\");
    std::string folder;

    if (position != std::string::npos) {
        folder = filename.substr(0, position + 1);
    }

    JaggedArray first;
    JaggedArray second;

    if (!first.read_file(folder + "first.txt") ||
        !second.read_file(folder + "second.txt")) {
        std::cout << "Не удалось открыть first.txt или second.txt\n";
        return 1;
    }

    std::cout << "Первый массив:\n";
    first.print();

    std::cout << "\nВторой массив:\n";
    second.print();

    JaggedArray result = first - second;

    std::cout << "\nРезультат первого массива минус второй:\n";
    result.print();

    first--;

    std::cout << "\nПервый массив после --:\n";
    first.print();

    first.add_endline(0, "новый");

    std::cout << "\nДобавление элемента в строку 0:\n";
    first.print();

    first.delete_element(0, 1);

    std::cout << "\nУдаление элемента с индексами 0, 1:\n";
    first.print();

    first.delete_element("новый");

    std::cout << "\nУдаление по значению:\n";
    first.print();

    first.sort_rows();

    std::cout << "\nСортировка внутри строк:\n";
    first.print();

    std::cout << "\nЭлемент first[0][0]: " << first[0][0] << '\n';

    return 0;
}