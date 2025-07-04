#include <iostream>
#include <fstream>
#include <unordered_map>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

// Загрузка json-файла
json load_json(const string& filename) {
    ifstream in(filename);
    if (!in) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        exit(1);
    }
    json j;
    in >> j;
    return j;
}

// Рекурсивно заполняем value по id
void fill_values(json& node, const unordered_map<int, string>& values_map) {
    if (node.contains("id") && node.contains("value")) {
        int id = node["id"];
        auto it = values_map.find(id);
        if (it != values_map.end()) {
            node["value"] = it->second;
        }
    }
    // Если есть вложенные values, обрабатываем
    if (node.contains("values")) {
        for (auto& child : node["values"]) {
            fill_values(child, values_map);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " <./task3 values.json tests.json report.json>" << endl;
        return 1;
    }

    // Загружаем values
    json values_json = load_json(argv[1]);
    unordered_map<int, string> values_map;
    for (const auto& item : values_json["values"]) {
        values_map[item["id"]] = item["value"];
    }

    // Загружаем tests
    json tests_json = load_json(argv[2]);

    // Заполняем значения
    if (tests_json.contains("tests")) {
        for (auto& test : tests_json["tests"]) {
            fill_values(test, values_map);
        }
    }

    // Сохраняем результат
    ofstream out(argv[3]);
    out << tests_json.dump(4);

    return 0;
}