////Задача 1
//#include <iostream>
//#include <ctime>
//#include <cstdlib>
//using namespace std;
//
//int main()
//{
//    setlocale(LC_ALL, "");
//    srand(time(0));
//
//    int N, K;
//    cout << "Введите размер массива N: ";
//    cin >> N;
//
//    int* arr = new int[N];
//
//    for (int i = 0; i < N; i++)
//    {
//        arr[i] = 10 + rand() % (99 - 10 + 1);
//    }
//
//    cout << "Исходный массив: ";
//    for (int i = 0; i < N; i++)
//    {
//        cout << arr[i] << " ";
//    }
//    cout << endl;
//
//    cout << "Введите количество блоков K (K <= N): ";
//    cin >> K;
//
//    int blockSize = N / K;
//    int remainder = N % K;
//
//    int start = 0;
//    for (int i = 0; i < K; i++) {
//        int end = start + blockSize;
//        if (i < remainder) {
//            end++;
//        }
//
//        cout << "Блок " << i + 1 << ": ";
//        for (int j = start; j < end; j++) {
//            cout << arr[j] << " ";
//        }
//        cout << " -> ";
//
//        for (int a = start + 1; a < end; a++)
//        {
//            for (int b = end - 1; b >= a; b--)
//            {
//                if (arr[b - 1] > arr[b])
//                {
//                    int temp = arr[b - 1];
//                    arr[b - 1] = arr[b];
//                    arr[b] = temp;
//                }
//            }
//        }
//
//        for (int j = start; j < end; j++) {
//            cout << arr[j] << " ";
//        }
//        cout << endl;
//
//        start = end;
//    }
//
//    cout << "\nРезультат:\n";
//    cout << "Отсортированный массив: ";
//    for (int i = 0; i < N; i++)
//    {
//        cout << arr[i] << " ";
//    }
//    cout << endl;
//    return 0;
//}

//Задача_2
#include <iostream>
#include <cstring> 
#include <clocale>  
#include <cctype>
#include <cstdlib>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    system("chcp 1251 > nul");

    const int max_txt = 1000;
    const int max_bad = 10;
    const int max_wlen = 20;

    char txt[max_txt];
    char bad[max_bad][max_wlen];
    int badCnt;

    cout << "Введите текст (максимум " << max_txt - 1 << " символов):" << endl;
    cin.getline(txt, max_txt);

    if (strlen(txt) == 0) {
        cout << "Ошибка: текст не может быть пустым" << endl;
        return 1;
    }

    cout << "Введите количество запрещенных слов: ";
    cin >> badCnt;
    cin.ignore();

    if (cin.fail() || badCnt <= 0 || badCnt > max_bad) {
        cout << "Ошибка: некорректное количество запрещенных слов" << endl;
        return 1;
    }

    cout << "Введите " << badCnt << " запрещенных слов:" << endl;
    for (int i = 0; i < badCnt; i++) {
        cout << i + 1 << ": ";
        cin.getline(bad[i], max_wlen);

        if (strlen(bad[i]) == 0) {
            cout << "Ошибка: запрещенное слово не может быть пустым" << endl;
            return 1;
        }
    }

    cout << "\nИсходный текст: " << txt << endl;
    cout << "Запрещенные слова: ";
    for (int i = 0; i < badCnt; i++) {
        cout << bad[i];
        if (i < badCnt - 1) cout << ", ";
    }
    cout << endl;

    char badLow[max_bad][max_wlen];
    for (int i = 0; i < badCnt; i++) {
        int len = strlen(bad[i]);
        for (int j = 0; j <= len; j++) {
            badLow[i][j] = tolower(bad[i][j]);
        }
    }

    int txtLen = strlen(txt);
    int curPos = 0;

    while (curPos < txtLen) {
        int minPos = txtLen;
        int curLen = 0;
        int curIdx = -1;

        for (int i = 0; i < badCnt; i++) {
            int wrdLen = strlen(badLow[i]);

            for (int j = curPos; j <= txtLen - wrdLen; j++) {
                if (j > 0) {
                    char prev = txt[j - 1];
                    bool isPrevDelim = (prev == ' ' || prev == ',' || prev == '.' || prev == '!' ||
                        prev == '?' || prev == ';' || prev == ':' || prev == '-' ||
                        prev == '"' || prev == '\'' || prev == '(' || prev == ')' ||
                        prev == '\n' || prev == '\t');
                    if (!isPrevDelim) {
                        continue;
                    }
                }
                bool found = true;
                for (int k = 0; k < wrdLen; k++) {
                    char c1 = tolower(txt[j + k]);
                    char c2 = badLow[i][k];

                    if (c1 != c2) {
                        found = false;
                        break;
                    }
                }

                if (found) {
                    char next = txt[j + wrdLen];
                    bool isNextDelim = (next == ' ' || next == ',' || next == '.' || next == '!' ||
                        next == '?' || next == ';' || next == ':' || next == '-' ||
                        next == '"' || next == '\'' || next == '(' || next == ')' ||
                        next == '\n' || next == '\t' || next == '\0');

                    if (isNextDelim && j < minPos) {
                        minPos = j;
                        curLen = wrdLen;
                        curIdx = i;
                    }
                }
            }
        }

        if (curIdx != -1) {
            for (int i = 0; i < curLen; i++) {
                txt[minPos + i] = '*';
            }
            curPos = minPos + curLen;
        }
        else {
            break;
        }
    }

    cout << "Отфильтрованный текст: " << txt << endl;

    return 0;
}
