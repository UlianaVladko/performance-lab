#include <iostream>
#include <vector>

int main() {
    int n, m;
    std::cout << "Введите n и m: ";
    std::cin >> n >> m;

    // Формируем круговой массив
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i)
        arr[i] = i + 1;

    std::cout << "Круговой массив: ";
    for (int x : arr) std::cout << x;
    std::cout << std::endl;

    // Путь, интервалы, стартовый индекс
    std::vector<int> path;
    std::vector<std::vector<int>> intervals;
    int start_idx = 0;

    // Строим интервалы по кругу и формируем путь, пока не встретим повтор первого элемента
    while (true) {
        path.push_back(arr[start_idx]);
        std::vector<int> interval;
        for (int j = 0; j < m; ++j)
            interval.push_back(arr[(start_idx + j) % n]);
        intervals.push_back(interval);
        
        int next_idx = (start_idx + m - 1) %n;
        if (arr[next_idx] == 1) break;
        start_idx = next_idx;
    }

    // Вывод результатов
    std::cout << "При длине обхода " << m << " получаем интервалы: ";
    for (size_t i = 0; i < intervals.size(); ++i) {
        for (size_t j = 0; j < intervals[i].size(); ++j) {
            std::cout << intervals[i][j];
            if (j + 1 < intervals[i].size());
        }
        if (i + 1 < intervals.size()) std::cout << ", ";
    }
    std::cout << std::endl;

    std::cout << "Полученный путь: ";
    for (int x : path) std::cout << x;
    std::cout << std::endl;

}
