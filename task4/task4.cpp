#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>

// Чтение массива чисел из файла
bool read_numbers(const std::string& filename, std::vector<int>& numbers) {
    std::ifstream input(filename);
    if (!input) {
        std::cerr << "Ошибка: не удалось открыть файл \"" << filename << "\"\n";
        return false;
    }
    int value;
    while (input >> value) {
        numbers.push_back(value);
    }
    if (numbers.empty()) {
        std::cerr << "Ошибка: файл \"" << filename << "\" не содержит чисел\n";
        return false;
    }
    return true;
}

// Возвращает медиану отсортированного массива
int find_median(const std::vector<int>& nums) {
    size_t n = nums.size();
    return nums[n / 2];
}

// Вычисляет минимальное количество ходов
long long min_moves_to_equal_elements(std::vector<int>& nums) {
    std::sort(nums.begin(), nums.end());
    int median = find_median(nums);
    // Используем std::accumulate и лямбда-функцию для подсчета суммы модулей разностей
    return std::accumulate(nums.begin(), nums.end(), 0LL,
        [median](long long sum, int x) { return sum + std::abs(x - median); });
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <./task4 nums.txt>" << std::endl;
        return 1;
    }

    std::vector<int> numbers;
    if (!read_numbers(argv[1], numbers)) {
        return 1;
    }

    long long moves = min_moves_to_equal_elements(numbers);

    std::cout << moves << std::endl;
    return 0;
}