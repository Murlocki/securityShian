#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// Типы для удобства
using Rights = unordered_set<string>; // Множество прав доступа
using Graph = unordered_map<string, unordered_map<string, Rights>>; // Граф доступа

// Парсинг прав из строки формата "r1,r2,r3"
Rights parseRights(const string& rights_str) {
    Rights rights;
    istringstream iss(rights_str);
    string right;
    while (getline(iss, right, ',')) {
        rights.insert(right);
    }
    return rights;
}

// Загрузка графа из файла
void loadGraph(const string& filename, Graph& graph) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка: Не удалось открыть файл.\n";
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string x, y, rights_str;
        if (!(iss >> x >> y >> rights_str)) {
            cerr << "Ошибка: Неверный формат строки: " << line << "\n";
            continue;
        }

        Rights rights = parseRights(rights_str);
        graph[x][y] = rights;
        graph[y][x] = rights; // Делаем граф неориентированным
    }
    cout << "Граф доступа:\n";
    for (const auto& entry : graph) {
        const string& subject = entry.first;
        const auto& neighbors = entry.second;

        cout << subject << " -> ";
        for (const auto& neighbor : neighbors) {
            const string& neighbor_name = neighbor.first;
            const Rights& rights = neighbor.second;

            cout << neighbor_name << " (";
            bool first = true;
            for (const auto& right : rights) {
                if (!first) cout << ", ";
                cout << right;
                first = false;
            }
            cout << ") ";
        }
        cout << "\n";
    }

}

// Проверка, что одно множество является подмножеством другого
bool isSubset(const Rights& subset, const Rights& set) {
    for (const auto& elem : subset) {
        if (set.count(elem) == 0) return false;
    }
    return true;
}

// Поиск tg-пути (путь с дугами, содержащими 't' или 'g') между двумя вершинами
bool hasTGPath(const Graph& graph, const string& start, const string& end) {
    unordered_set<string> visited;
    queue<string> q;
    q.push(start);

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        if (current == end) return true;
        visited.insert(current);

        if (graph.find(current) != graph.end()) {
            for (const auto& neighbor : graph.at(current)) {
                const string& neighbor_name = neighbor.first;
                const Rights& rights = neighbor.second;

                if (visited.count(neighbor_name) == 0 &&
                    (rights.count("t") || rights.count("g"))) {
                    q.push(neighbor_name);
                }
            }
        }
    }
    return false;
}

// Проверка условия Possible_Access(A, x, y)
bool possibleAccess(const Graph& graph, const Rights& A, const string& x, const string& y) {
    vector<string> potentialSubjects;

    // Найти всех субъектов, обладающих правами из A на y
    for (const auto& entry : graph) {
        const string& subject = entry.first;
        const auto& neighbors = entry.second;

        if (neighbors.find(y) != neighbors.end() &&
            isSubset(neighbors.at(y), A)) {
            potentialSubjects.push_back(subject);
        }
    }

    // Проверить наличие tg-пути от x до каждого найденного субъекта
    for (const string& subject : potentialSubjects) {
        if (!hasTGPath(graph, x, subject)) return false;
    }
    if(potentialSubjects.size()>0)return true;
    return false;
}

int main() {
    Graph graph;
    setlocale(LC_ALL, "ru");
    // Загрузка графа из файла
    loadGraph("input.txt", graph);

    // Интерактивный режим для проверки Possible_Access
    while (true) {
        cout << "Введите тройку A, x, y (или 'exit' для выхода): ";
        string input;
        getline(cin, input);

        if (input == "exit") break;

        istringstream iss(input);
        string A_str, x, y;
        if (!(iss >> A_str >> x >> y)) {
            cerr << "Ошибка: Неверный ввод. Попробуйте снова.\n";
            continue;
        }

        Rights A = parseRights(A_str);

        if (possibleAccess(graph, A, x, y)) {
            cout << "Possible_Access: Доступ возможен\n";
        }
        else {
            cout << "Possible_Access: Доступ невозможен\n";
        }
    }

    return 0;
}