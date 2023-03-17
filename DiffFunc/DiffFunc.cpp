// DiffFunc.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <vector>


int getXcoord()
{
    CONSOLE_SCREEN_BUFFER_INFO info_x;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info_x);
    return info_x.dwCursorPosition.X;
}

int getYcoord()
{
    CONSOLE_SCREEN_BUFFER_INFO info_y;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info_y);
    return info_y.dwCursorPosition.Y;
}

int** lcs(string line, string line1) {
     const int rows = line.length() ;
     const int cols = line1.length() ;
     int** matr;
     matr = new int*[rows + 1];
     for (int i = 0; i < rows + 1; i++) {
         matr[i] = new int[cols + 1];
     }
     for (int i = 0; i < rows + 1; i++) {
         for (int j = 0; j < cols + 1; j++) {
             matr[i][j] = 0;
         }
     }
     for (int i = 1; i <= rows; i++) {
         for (int j = 1; j <= cols; j++) {
             if (line[i - 1] == line1[j - 1]) {
                 matr[i][j] = 1 + matr[i - 1][j - 1];
             }
             else {
                 matr[i][j] = max(matr[i - 1][j], matr[i][j - 1]);
             }
         }
     }
     return matr;
}

string example(string line, string line1, int** matr) {
    int rows = line.length();
    int cols = line1.length();
    string result = "";
    while (rows > 0 && cols > 0) {
        if (line[rows - 1] == line1[cols - 1]) {
            result += line[rows - 1];
            rows -= 1;
            cols -= 1;

        }
        else {
            if (matr[rows - 1][cols] > matr[rows][cols - 1]) {
                rows -= 1;
            }
            else {
                cols -= 1;
            }
        }
    }
    reverse(result.begin(), result.end());
    return result;
}
void printHighText(string line, string result, int m) {
    int i = 0;
    int j = 0;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
   // COORD position = { 40,0 };
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_BLUE);
    if (m == 1) {
        std::cout << "First file\n" ;
    }
    else {
        std::cout << "Second file\n";
        int k = getYcoord();
        COORD position = { 70, k };
        //std::cout << k;
        SetConsoleCursorPosition(hConsole, position);
    }
    while (i < result.length() && j < line.length()) {
        
        if (result[i] == line[j]) {
            SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
            if (line[j] == ' ') {
                std::cout << '_';
            }
            else {
                std::cout << line[j];
            }
          
            i += 1;
            j += 1;
        }
        else {
            SetConsoleTextAttribute(handle, FOREGROUND_RED);
            if (line[j] == ' ') {
                std::cout << '_';
            } 
            else if (j > 0 && line[j] == '\n' && line[j - 1] == '\n') {
                std::cout << "|\n";
            }
            else if (j == 0 && line[j] == '\n') {
                std::cout << "|\n";
            }
            else {
                std::cout << line[j];
            }
            j += 1;
        }
        if (m == 2 && line[j - 1] == '\n') {
            int k = getYcoord();
            COORD position = { 70, k };
            //std::cout << k;
            SetConsoleCursorPosition(hConsole, position);
        }
    }
   // if (m == )
   // COORD position = { 40, 10 };
   // SetConsoleCursorPosition(hConsole, position);
    while (j < line.length()) {
        SetConsoleTextAttribute(handle, FOREGROUND_RED);
        if (j > 0 && m == 2 && line[j - 1] == '\n') {
            int k = getYcoord();
            COORD position = { 70, k };
            //std::cout << k;
            SetConsoleCursorPosition(hConsole, position);
        }
        if (line[j] == ' ') {
            std::cout << '_';
        }
        else if (j > 0 && line[j] == '\n' && line[j - 1] == '\n') {
            std::cout << "|\n";
        }
        else if (j == 0 && line[j] == '\n') {
            std::cout << "|\n";
        }
        else {
            std::cout << line[j];
        }
        j += 1;
    }
}

int main(int argc, char* argv[])
{   
    //C:\\Users\\KK\\Desktop\\hello1.txt
    //argv[1]
    string line;
    string line1;
    string substr;
    COORD position = { 70,0 };
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ifstream in(argv[1]);
    ifstream in1(argv[2]);
    getline(in, line, '\0');
    getline(in1, line1, '\0');
    in.close();     
    in1.close(); 
    int ln1 = line.length();
    int ln2 = line1.length();
    if (ln1 == 1) {
        line += '\n';
    }
    if (ln2 == 1) {
        line1 += '\n';
    }
    if (ln1 > 50) {
        line.insert(line.length()/2, "\n");
    }
    if (ln2 > 50) {
        line1.insert(line1.length()/2, "\n");
    }
    int y = 0;
    substr = example(line, line1, lcs(line, line1));
    system("cls");
    printHighText(line, substr,1);

    if (ln1 > ln2) {
        y = getYcoord();
    }
    SetConsoleCursorPosition(hConsole, position);
    printHighText(line1, substr,2);
    if (ln1 <= ln2) {
        y = getYcoord();
    }
    COORD position1 = { 0, y + 3};
    SetConsoleCursorPosition(hConsole, position1);
    std::cout << "End of program" << std::endl;
    system("pause");
    return 0;
}


