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


//Задание 2
//Проверка произведения цифр
bool checkDigitsMult(int number) {
    int mult = 1;
    do {
        mult = mult * (number % 10);
        number = number / 10;
    } while (number > 0);
    if (mult == 243) return true;
    return false;
}
//Проверка на простоту
bool checkSimplinest(int number) {
    if (number == 0 || number == 1) return false;

    for (int i = 2; i <= number / 2; i++) {
        if (number % i == 0) return false;
    }
    return true;
}

void generateTask2() {
    ofstream outputFile;
    outputFile.open("output2.txt");
    
    int counter = 0;
    vector<int>numbers;
    for (int i = 1000; i < 10000; i++) {
        if (checkDigitsMult(i) && checkSimplinest(i)) {
            counter += 1;
            numbers.push_back(i);
        }
    }
    outputFile << counter << endl;
    for (int i = 0; i < numbers.size(); i++) {
        outputFile << numbers[i]<<" ";
    }
    outputFile.close();
}

void generateTask2Smart() {

    int counter = 0;
    vector<string>numbers;
    //Есть только 1 вариант с возможными простыми числами и произведением в 243 - число с цифрами 1 3 9 9
   
        int onePos = 0;
        do {
            int threePos = 0;
            do {
                if (onePos == threePos) {
                    threePos += 1;
                    continue;
                }
                string result = "9999";
                result = result.replace(onePos, 1, "1");
                result = result.replace(threePos, 1, "3");
                if (checkSimplinest(atof(result.c_str()))) {
                    counter += 1;
                    numbers.push_back(result);
                }
                threePos += 1;
            } while (threePos < 4);
            onePos += 1;
        } while (onePos < 4);

    //Вывод в файл
    ofstream outputFile;
    outputFile.open("output3.txt");
    outputFile << counter << endl;
    for (int i = 0; i < numbers.size(); i++) {
        outputFile << numbers[i] << " ";
    }
    outputFile.close();
}
int main()
{
    generateTask1();
    generateTask2();
    generateTask2Smart();
}

//243=3^5
//1399
//1993
//3919
//9139
//9391
//9931

