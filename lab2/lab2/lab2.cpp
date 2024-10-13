#include <iostream>
#include <vector>
#include <string>

using namespace std;

void createAllLevels(int currentI, int currentJ, vector<vector<string>>A, vector<int>LS, vector<int>LO, bool*exist) {
   if (!*exist) {
        if (currentI != LS.size() && currentJ != LO.size()) {
                for (int iLevel = 0; iLevel < LS.size() + LO.size(); iLevel++) {
                    LS[currentI] = iLevel;
                    LO[currentI] = iLevel;
                     createAllLevels(currentI+1, currentJ+1, A, LS, LO, exist);
                     }
        }
        else if (currentI == LS.size() && currentJ != LO.size()) {
            for (int jLevel = 0; jLevel < LS.size() + LO.size(); jLevel++) {
                LO[currentJ] = jLevel;
                createAllLevels(currentI, currentJ+1, A, LS, LO, exist);
            }
        }
        else {
            bool check = true;
            for (int indexRow = 0; (indexRow < LS.size()); indexRow++) {
                for (int jCol = 0; (jCol < LO.size()); jCol++) {
                    if (A[indexRow][jCol].find('r') != string::npos && A[indexRow][jCol].find('w') != string::npos && !(LS[indexRow] == LO[jCol])) {
                        cout << "Решение не существует: нарушение прав по привалу rw на A[" << indexRow << "][" << jCol << "].\n";
                        check = false;
                    }
                    else if (A[indexRow][jCol].find('r') != string::npos && A[indexRow][jCol].find('w') == string::npos && !(LS[indexRow] > LO[jCol])) {
                        cout << "Решение не существует: нарушение 'no read up' на A[" << indexRow << "][" << jCol << "].\n";
                        check = false;
                    }
                    else if (A[indexRow][jCol].find('w') != string::npos && A[indexRow][jCol].find('r') == string::npos && !(LS[indexRow] < LO[jCol])) {
                        cout << "Решение не существует: нарушение 'no write down' на A[" << indexRow << "][" << jCol << "].\n";
                        check = false;
                    }
                    if (!check) break;
                }
                if (!check) break;
            }
            cout << "Не Уровни допуска субъектов (LS): ";
            for (int i = 0; i < LS.size(); ++i) cout << LS[i] << " ";
            cout << "\nНе Уровни секретности объектов (LO): ";
            for (int j = 0; j < LO.size(); ++j) cout << LO[j] << " ";
            cout << endl;
            if (check) {
                *exist = true;
                cout << "Уровни допуска субъектов (LS): ";
                for (int i = 0; i < LS.size(); ++i) cout << LS[i] << " ";
                cout << "\nУровни секретности объектов (LO): ";
                for (int j = 0; j < LO.size(); ++j) cout << LO[j] << " ";
                cout << endl;
            }
        }
    }
}

// Функция для подбора уровней допуска и секретности
void bellLapadula(int n, int m, const vector<vector<string>>A, vector<int>LS, vector<int>LO) {

    vector<int> levels(n+m, 0);
    for (int i = 0; i < n + m; i++) {
        levels[i] = i;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout<<A[i][j];
        }
    }
    bool exist = false;
    cout <<exist << endl;
    createAllLevels(0, 0, A, LS, LO, &exist);
}


int mai() {
    int n = 3;  // Количество субъектов
    int m = 3;  // Количество объектов
    setlocale(LC_ALL, "ru");
    // Матрица прав доступа A[i][j]: 'r' - чтение, 'w' - запись
    // 2 3 1
    // 2 3 1
    vector<vector<string>> A = {
        {"rw","w", "r"},
        {"r", "rw", "r"},
        {"w", "w", "rw"}
    };

    vector<int> LS(n, 0);  // Уровни допуска субъектов (инициализируем нулями)
    vector<int> LO(m, 0);  // Уровни секретности объектов (инициализируем нулями)

    bellLapadula(n, m, A, LS, LO);

    return 0;
}