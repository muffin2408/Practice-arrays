//Задача 1
//#include <iostream>
//#include <ctime>
//#include <cstdlib>
//using namespace std;
//
//void bubbleSort(int arr[], int start, int end)
//{
//    for (int a = start + 1; a < end; a++)
//    {
//        for (int b = end - 1; b >= a; b--)
//        {
//            if (arr[b - 1] > arr[b])
//            {
//                int temp = arr[b - 1];
//                arr[b - 1] = arr[b];
//                arr[b] = temp;
//            }
//        }
//    }
//}
//
//void printArray(int arr[], int n, const char* msg)
//{
//    cout << msg;
//    for (int i = 0; i < n; i++)
//    {
//        cout << arr[i] << " ";
//    }
//    cout << endl;
//}
//
//void fillRandom(int arr[], int n, int min, int max)
//{
//    for (int i = 0; i < n; i++)
//    {
//        arr[i] = min + rand() % (max - min + 1);
//    }
//}
//
//int main()
//{
//    setlocale(LC_ALL, "");
//    srand(time(0));
//
//    try {
//        int N, K;
//        cout << "Введите размер массива N: ";
//        cin >> N;
//
//        int* arr = new int[N];
//
//        fillRandom(arr, N, 10, 99);
//        printArray(arr, N, "Исходный массив: ");
//
//        cout << "Введите количество блоков K (K <= N): ";
//        cin >> K;
//
//        int blockSize = N / K;
//        int remainder = N % K;
//
//        cout << "\nРазмер блока: " << blockSize;
//        if (remainder > 0) {
//            cout << " (первые " << remainder << " блоков больше на 1 элемент)";
//        }
//        cout << endl;
//
//        int start = 0;
//        for (int i = 0; i < K; i++) {
//            int end = start + blockSize;
//            if (i < remainder) {
//                end++;
//            }
//
//            cout << "Блок " << i + 1 << ": ";
//            for (int j = start; j < end; j++) {
//                cout << arr[j] << " ";
//            }
//            cout << " -> ";
//
//            bubbleSort(arr, start, end);
//
//            for (int j = start; j < end; j++) {
//                cout << arr[j] << " ";
//            }
//            cout << endl;
//
//            start = end;
//        }
//
//        cout << "\nРезультат:\n";
//        printArray(arr, N, "Отсортированный массив: ");
//
//        delete[] arr;
//    }
//    catch (const string& e) {
//        cerr << e << endl;
//        return 1;
//    }
//    catch (const bad_alloc& e) {
//        cerr << "Ошибка выделения памяти" << endl;
//        return 1;
//    }
//    return 0;
//}

//Задача_2
#include <iostream>
#include <cstring> 
#include <clocale>  
#include <cstdlib>
using namespace std;

void toLower(char dest[], const char src[]) {
    int len = strlen(src);
    for (int i = 0; i <= len; i++) {
        dest[i] = tolower(src[i]);
    }
}

bool isDelim(char ch) {
    return ch == ' ' || ch == ',' || ch == '.' || ch == '!' || ch == '?' ||
        ch == ';' || ch == ':' || ch == '-' || ch == '"' || ch == '\'' ||
        ch == '(' || ch == ')' || ch == '\n' || ch == '\t' || ch == '\0';
}

int findWord(const char txt[], int pos, const char wrd[], int& wLen) {
    int txtLen = strlen(txt);
    int wrdLen = strlen(wrd);

    for (int i = pos; i <= txtLen - wrdLen; i++) {
        bool found = true;

        if (i > 0 && !isDelim(txt[i - 1])) {
            continue;
        }

        for (int j = 0; j < wrdLen; j++) {
            char c1 = tolower(txt[i + j]);
            char c2 = tolower(wrd[j]);

            if (c1 != c2) {
                found = false;
                break;
            }
        }

        if (found) {
            char next = txt[i + wrdLen];
            if (isDelim(next) || next == '\0') {
                wLen = wrdLen;
                return i;
            }
        }
    }
    return -1;
}

void replaceWord(char txt[], int pos, int len) {
    for (int i = 0; i < len; i++) {
        txt[pos + i] = '*';
    }
}

void filterText(char txt[], char bad[][20], int badCnt) {
    int txtLen = strlen(txt);
    char badLow[10][20];

    for (int i = 0; i < badCnt; i++) {
        toLower(badLow[i], bad[i]);
    }

    int curPos = 0;
    while (curPos < txtLen) {
        int minPos = txtLen;
        int curLen = 0;
        int curIdx = -1;

        for (int i = 0; i < badCnt; i++) {
            int wLen = 0;
            int fndPos = findWord(txt, curPos, badLow[i], wLen);

            if (fndPos != -1 && fndPos < minPos) {
                minPos = fndPos;
                curLen = wLen;
                curIdx = i;
            }
        }

        if (curIdx != -1) {
            replaceWord(txt, minPos, curLen);
            curPos = minPos + curLen;
        }
        else {
            break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    system("chcp 1251 > nul");

    try {
        const int MAX_TXT = 1000;
        const int MAX_BAD = 10;
        const int MAX_WLEN = 20;

        char txt[MAX_TXT];
        char bad[MAX_BAD][MAX_WLEN];
        int badCnt;

        cout << "Введите текст (максимум " << MAX_TXT - 1 << " символов):" << endl;
        cin.getline(txt, MAX_TXT);

        if (strlen(txt) == 0) {
            throw "Текст не может быть пустым";
        }

        cout << "Введите количество запрещенных слов: ";
        cin >> badCnt;
        cin.ignore();

        if (cin.fail() || badCnt <= 0 || badCnt > MAX_BAD) {
            throw "Некорректное количество запрещенных слов";
        }

        cout << "Введите " << badCnt << " запрещенных слов:" << endl;
        for (int i = 0; i < badCnt; i++) {
            cout << i + 1 << ": ";
            cin.getline(bad[i], MAX_WLEN);

            if (strlen(bad[i]) == 0) {
                throw "Запрещенное слово не может быть пустым";
            }
        }

        cout << "\nИсходный текст: " << txt << endl;
        cout << "Запрещенные слова: ";
        for (int i = 0; i < badCnt; i++) {
            cout << bad[i];
            if (i < badCnt - 1) cout << ", ";
        }
        cout << endl;

        filterText(txt, bad, badCnt);
        cout << "Отфильтрованный текст: " << txt << endl;
    }
    catch (const char* err) {
        cerr << "Ошибка: " << err << endl;
        return 1;
    }
    catch (...) {
        cerr << "Неизвестная ошибка!" << endl;
        return 1;
    }
    return 0;
}