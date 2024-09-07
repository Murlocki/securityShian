#include <iostream>
#include<vector>
#include <fstream>
using namespace std;

//Генерим следующие две позиции
vector<int> nextTwoPositions(vector<int> currentPosition) {
    if (currentPosition[1] == 7) {
        currentPosition[0] = currentPosition[0] + 1;
        currentPosition[1] = currentPosition[0] + 1;
    }
    else {
        currentPosition[1] = currentPosition[1] + 1;
    }
    return currentPosition;
}

//Проверяем существование следующей комбинации
bool checkNextPositionExist(vector<int> currentPosition) {
    if (currentPosition[0] == 7) return false;
    return true;
}

//Генерим новую строку
string generateNewBlock(vector<int> twoPos, vector<int> fivePos) {
    string resultBlock = "77777777";
    resultBlock = resultBlock.replace(twoPos[0], 1, "2");
    resultBlock = resultBlock.replace(twoPos[1], 1, "2");

    resultBlock = resultBlock.replace(fivePos[0], 1, "5");
    resultBlock = resultBlock.replace(fivePos[1], 1, "5");

    return resultBlock;
}

//Генерим вывод
void generateTask1() {
    ofstream outputFile;
    outputFile.open("output.txt");
    vector<int> twoPos = { 0, 1 };
    do {
        vector<int> fivePos = { 0, 1 };
        do {
            auto it1 = find(twoPos.begin(), twoPos.end(), fivePos[0]);
            auto it2 = find(twoPos.begin(), twoPos.end(), fivePos[1]);
            if (it1 != twoPos.end() || it2 != twoPos.end()) {
                fivePos = nextTwoPositions(fivePos);
                continue;
            }
            string resultBlock = generateNewBlock(twoPos, fivePos);
            outputFile << resultBlock << endl;
            fivePos = nextTwoPositions(fivePos);
        } while (checkNextPositionExist(fivePos));
        twoPos = nextTwoPositions(twoPos);
    } while (checkNextPositionExist(twoPos));
    outputFile.close();
}




int main()
{
    generateTask1();
}

