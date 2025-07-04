#include <iostream>
#include <fstream>
#include <cmath>

// Структура для хранения координат
struct Point {
    double x, y;
};

// Функция определения положения точки
int checking_the_position(const Point& center, double radius2, const Point& p) {
    double dx = p.x - center.x, dy = p.y - center.y;
    double dist2 = dx * dx + dy * dy;
    constexpr double eps = 1e-8;
    if (std::abs(dist2 - radius2) < eps) return 0;
    if (dist2 < radius2 - eps) return 1;
    return 2;
}

// Открываем и читаем файлы; Для каждой точки вызываем ф-ц проверки положения
int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <./task2 circle.txt points.txt>\n";
        return 1;
    }
    std::ifstream circle_file(argv[1]), points_file(argv[2]);
    Point center;
    double radius;
    if (!(circle_file >> center.x >> center.y >> radius)) {
        std::cerr << "Ошибка: не удалось прочитать файл circle.txt\n";
        return 1;
    }
    double radius2 = radius * radius;
    for (double x, y; points_file >> x >> y; ) {
        Point p{x, y};
        std::cout << checking_the_position(center, radius2, p) << '\n';
    }
}