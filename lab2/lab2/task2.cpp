#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// ���� ��� ��������
using Rights = unordered_set<string>; // ��������� ���� �������
using Graph = unordered_map<string, unordered_map<string, Rights>>; // ���� �������

// ������� ���� �� ������ ������� "r1,r2,r3"
Rights parseRights(const string& rights_str) {
    Rights rights;
    istringstream iss(rights_str);
    string right;
    while (getline(iss, right, ',')) {
        rights.insert(right);
    }
    return rights;
}

// �������� ����� �� �����
void loadGraph(const string& filename, Graph& graph) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "������: �� ������� ������� ����.\n";
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string x, y, rights_str;
        if (!(iss >> x >> y >> rights_str)) {
            cerr << "������: �������� ������ ������: " << line << "\n";
            continue;
        }

        Rights rights = parseRights(rights_str);
        graph[x][y] = rights;
        graph[y][x] = rights; // ������ ���� �����������������
    }
    cout << "���� �������:\n";
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

// ��������, ��� ���� ��������� �������� ������������� �������
bool isSubset(const Rights& subset, const Rights& set) {
    for (const auto& elem : subset) {
        if (set.count(elem) == 0) return false;
    }
    return true;
}

// ����� tg-���� (���� � ������, ����������� 't' ��� 'g') ����� ����� ���������
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

// �������� ������� Possible_Access(A, x, y)
bool possibleAccess(const Graph& graph, const Rights& A, const string& x, const string& y) {
    vector<string> potentialSubjects;

    // ����� ���� ���������, ���������� ������� �� A �� y
    for (const auto& entry : graph) {
        const string& subject = entry.first;
        const auto& neighbors = entry.second;

        if (neighbors.find(y) != neighbors.end() &&
            isSubset(neighbors.at(y), A)) {
            potentialSubjects.push_back(subject);
        }
    }

    // ��������� ������� tg-���� �� x �� ������� ���������� ��������
    for (const string& subject : potentialSubjects) {
        if (!hasTGPath(graph, x, subject)) return false;
    }
    if(potentialSubjects.size()>0)return true;
    return false;
}

int main() {
    Graph graph;
    setlocale(LC_ALL, "ru");
    // �������� ����� �� �����
    loadGraph("input.txt", graph);

    // ������������� ����� ��� �������� Possible_Access
    while (true) {
        cout << "������� ������ A, x, y (��� 'exit' ��� ������): ";
        string input;
        getline(cin, input);

        if (input == "exit") break;

        istringstream iss(input);
        string A_str, x, y;
        if (!(iss >> A_str >> x >> y)) {
            cerr << "������: �������� ����. ���������� �����.\n";
            continue;
        }

        Rights A = parseRights(A_str);

        if (possibleAccess(graph, A, x, y)) {
            cout << "Possible_Access: ������ ��������\n";
        }
        else {
            cout << "Possible_Access: ������ ����������\n";
        }
    }

    return 0;
}