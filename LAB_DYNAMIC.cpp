/***----------------------------------------****
****----------Курс программирование---------****
****----------------------------------------****
* Project Type  : Win32 Console Application    *
* Project Name  : LAB_DYNAMIC.CPP              *
* Language      : CPP, MSVS ver 2015 and above *
* Programmers   : Zhbanov I.A.                 *
* Modified By   : Zhbanov I.A.                 *
* Created       : 04/05/2021                   *
* Last Revision : 05/05/2021                   *
* ---------------------------------------------*
* Comment       : Вторая лабораторная работа   *
****-------------------------------------------*/
#include <iostream>
#include <fstream>
using namespace std;
const char* FNAME_A = "A.txt"; 
const char* FNAME_B = "B.txt"; 
/*-----------------------------------*/


//функция записи матрицы
int** InpMatr(const char* FNAME,  //файл с матрицей
    int& N,     //количество строк
    int& M,     //количество столбцов
    int& errorCode) //код ошибки
{
    ifstream fin(FNAME); //подключаем файл
    int** Matr;
    errorCode = 0;
    //если файла не существует
    if (!fin)
    {
        //выводим ошибку и выходим из функции
        errorCode = 1;
        return new int* [0];
    }//if
    //считываем число строк
    fin >> N;
    //если файл пустой
    if (fin.eof())
    {
        //выводим ошибку и выходим из функции
        errorCode = 2;
        return new int* [0];
    }
    //считываем число столбцов
    fin >> M;
    //проверка на нечисло
    if (fin.fail())
    {
        //выводим ошибку и выходим из функции
        errorCode = 3;
        return new int* [0];
    }
    //если размеры массива не положительные
    if (N <= 0)
    {
        errorCode = 4;
        return new int* [0];
    }//if
    if (M <= 0)
    {
        errorCode = 5;
        return new int* [0];
    }//if

    Matr = new int* [N];
    for (int i = 0; i < N; i++) //инициализация элементов матрицы
    {
        Matr[i] = new int[M];
    }

    for (int i = 0; i < N; i++) //инициализация элементов матрицы
    {
        for (int j = 0; j < M; j++)
        {
            if (fin.eof())
            {
                errorCode = 6;       //не хватает чисел
                return Matr;
            }
            fin >> *(*(Matr + i) + j);  //присваивание значений элементам матрицы
        }
    }
    if (!fin.eof())
    {
        errorCode = 6;  //больше чисел, чем требуется
        return 0;
    }
    fin.close();
    return Matr;
}//InpMatr

//функция печати матрицы
void printMatrix(int** Matr, //указатель на матрицу
    int N,  //количество строк
    int M)  //количество столбцов
{
    cout << "Матрица " << N << "x" << M << ":" << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cout << *(*(Matr + i) + j) << '\t'; //выводим матрицу
        }//for
        cout << endl;
    }//for
}//printMatrix

 //функция находит произведение всех положительных элементов над побочной диагональю
void Task1(int** Matr,  //указатель на матрицу
    int& N,  //количество строк
    int& M)  //количество столбцов
{
    int Pr = 1; //произведение
    int k = 0;  //количество положительных элементов
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - i - 1; j++)
        {
            if (*(*(Matr + i) + j) > 0)  //проверка элемента на знак
            {
                Pr *= *(*(Matr + i) + j); //считаем произведение
                k++; //увеличиваем счетчик
            }//if
        }//for
    }//for
    if (k == 0) 
    {
        cout << "В матрице нет положительных элементов над побочной диагональю!" << endl;
    }
    else
    {
        cout << "Произведение положительных элементов матрицы, которые расположены над побочной диагональю = " << Pr << endl;
    }
}//Task1

//функция находит максимум среди сумм по строкам нечетных элементов матрицы
void Task2(int** Matr, //указатель на матрицу
    int& N,   //количесвто строк
    int& M)   //количесвто столбцов
{
    int max = 0;  //максимум
    int* SUM = new int[N]; //вектор сумм
    int sum = 0;  //сумма
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (*(*(Matr + i) + j) % 2 == 1)
            {
                sum += *(*(Matr + i) + j);   //считаем сумму
            }
        }//for
        SUM[i] = sum; //запоминаем сумму
        sum = 0;  //обнуляем сумму при переходе на новую строку
    }//for
    max = SUM[0];
    for (int i = 0; i < N; i++)
    {
        if (SUM[i] > max)
        {
            max = SUM[i];  //запоминаем максимум
        }
    }
    cout << "Максимум среди сумм по строкам нечетных элементов матрицы = " << max << endl;
}//Task2

void PrintError(int errorCode,     //код ошибки
    const char* FNAME) //имя файла
{
    //выбор ошибки в соответствии с ее кодом
    switch (errorCode)
    {
    case 1:
        cout << "\nОшибка! Файл " << FNAME << " не существует!\n\n\n" << endl;
        break;
    case 2:
        cout << "\nОшибка! Файл " << FNAME << " пустой!\n\n\n" << endl;
        break;
    case 3:
        cout << "\nОшибка! В файле " << FNAME << " не число!\n\n\n" << endl;
        break;
    case 4:
        cout << "\nОшибка! В файле " << FNAME << " число строк меньше 0!\n\n\n" << endl;
        break;
    case 5:
        cout << "\nОшибка! В файле " << FNAME << " число столбцов меньше 0!\n\n\n" << endl;
        break;
    case 6:
        cout << "\nОшибка! В файле " << FNAME << " не совпадает количество элементов\n\n\n" << endl;
        break;

    }//switch
}//PrintError

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    int errorCode = 0; //код ошибки
    int N_A, //количество строк в матрице А
        M_A, //количество столбцов в матрице А
        N_B, //количество строк в матрице В
        M_B; //количество столбцов в матрице В
    int** A; //матрица А
    int** B; //матрица B
    A = InpMatr(FNAME_A, N_A, M_A, errorCode);  //вводим матрицу А
    if (errorCode != 0)  //если произошла ошибка
    {
        PrintError(errorCode, FNAME_A);  //выводим сообщение об ошибке
    }
    else
    {
        printMatrix(A, N_A, M_A);  //эхо-печать матрицы А
        Task1(A, N_A, M_A);   //задание 1 для матрицы А
        Task2(A, N_A, M_A);   //задание 2 для матрицы А
    }//if
    cout << endl << endl;
    B = InpMatr(FNAME_B, N_B, M_B, errorCode); //вводим матрицу В
    if (errorCode != 0)  //если произошла ошибка
    {
        PrintError(errorCode, FNAME_B);   //выводим сообщение об ошибке
    }
    else
    {
        printMatrix(B, N_B, M_B);  //эхо-печать матрицы В
        Task1(B, N_B, M_B);  //задание 1 для матрицы В
        Task2(B, N_B, M_B);  //задание 2 для матрицы В
    }//if
    return 0;
}//main
