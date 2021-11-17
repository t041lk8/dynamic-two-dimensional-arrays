/***----------------------------------------****
****----------���� ����������������---------****
****----------------------------------------****
* Project Type  : Win32 Console Application    *
* Project Name  : LAB_DYNAMIC.CPP              *
* Language      : CPP, MSVS ver 2015 and above *
* Programmers   : Zhbanov I.A.                 *
* Modified By   : Zhbanov I.A.                 *
* Created       : 04/05/2021                   *
* Last Revision : 05/05/2021                   *
* ---------------------------------------------*
* Comment       : ������ ������������ ������   *
****-------------------------------------------*/
#include <iostream>
#include <fstream>
using namespace std;
const char* FNAME_A = "A.txt"; 
const char* FNAME_B = "B.txt"; 
/*-----------------------------------*/


//������� ������ �������
int** InpMatr(const char* FNAME,  //���� � ��������
    int& N,     //���������� �����
    int& M,     //���������� ��������
    int& errorCode) //��� ������
{
    ifstream fin(FNAME); //���������� ����
    int** Matr;
    errorCode = 0;
    //���� ����� �� ����������
    if (!fin)
    {
        //������� ������ � ������� �� �������
        errorCode = 1;
        return new int* [0];
    }//if
    //��������� ����� �����
    fin >> N;
    //���� ���� ������
    if (fin.eof())
    {
        //������� ������ � ������� �� �������
        errorCode = 2;
        return new int* [0];
    }
    //��������� ����� ��������
    fin >> M;
    //�������� �� �������
    if (fin.fail())
    {
        //������� ������ � ������� �� �������
        errorCode = 3;
        return new int* [0];
    }
    //���� ������� ������� �� �������������
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
    for (int i = 0; i < N; i++) //������������� ��������� �������
    {
        Matr[i] = new int[M];
    }

    for (int i = 0; i < N; i++) //������������� ��������� �������
    {
        for (int j = 0; j < M; j++)
        {
            if (fin.eof())
            {
                errorCode = 6;       //�� ������� �����
                return Matr;
            }
            fin >> *(*(Matr + i) + j);  //������������ �������� ��������� �������
        }
    }
    if (!fin.eof())
    {
        errorCode = 6;  //������ �����, ��� ���������
        return 0;
    }
    fin.close();
    return Matr;
}//InpMatr

//������� ������ �������
void printMatrix(int** Matr, //��������� �� �������
    int N,  //���������� �����
    int M)  //���������� ��������
{
    cout << "������� " << N << "x" << M << ":" << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cout << *(*(Matr + i) + j) << '\t'; //������� �������
        }//for
        cout << endl;
    }//for
}//printMatrix

 //������� ������� ������������ ���� ������������� ��������� ��� �������� ����������
void Task1(int** Matr,  //��������� �� �������
    int& N,  //���������� �����
    int& M)  //���������� ��������
{
    int Pr = 1; //������������
    int k = 0;  //���������� ������������� ���������
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - i - 1; j++)
        {
            if (*(*(Matr + i) + j) > 0)  //�������� �������� �� ����
            {
                Pr *= *(*(Matr + i) + j); //������� ������������
                k++; //����������� �������
            }//if
        }//for
    }//for
    if (k == 0) 
    {
        cout << "� ������� ��� ������������� ��������� ��� �������� ����������!" << endl;
    }
    else
    {
        cout << "������������ ������������� ��������� �������, ������� ����������� ��� �������� ���������� = " << Pr << endl;
    }
}//Task1

//������� ������� �������� ����� ���� �� ������� �������� ��������� �������
void Task2(int** Matr, //��������� �� �������
    int& N,   //���������� �����
    int& M)   //���������� ��������
{
    int max = 0;  //��������
    int* SUM = new int[N]; //������ ����
    int sum = 0;  //�����
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (*(*(Matr + i) + j) % 2 == 1)
            {
                sum += *(*(Matr + i) + j);   //������� �����
            }
        }//for
        SUM[i] = sum; //���������� �����
        sum = 0;  //�������� ����� ��� �������� �� ����� ������
    }//for
    max = SUM[0];
    for (int i = 0; i < N; i++)
    {
        if (SUM[i] > max)
        {
            max = SUM[i];  //���������� ��������
        }
    }
    cout << "�������� ����� ���� �� ������� �������� ��������� ������� = " << max << endl;
}//Task2

void PrintError(int errorCode,     //��� ������
    const char* FNAME) //��� �����
{
    //����� ������ � ������������ � �� �����
    switch (errorCode)
    {
    case 1:
        cout << "\n������! ���� " << FNAME << " �� ����������!\n\n\n" << endl;
        break;
    case 2:
        cout << "\n������! ���� " << FNAME << " ������!\n\n\n" << endl;
        break;
    case 3:
        cout << "\n������! � ����� " << FNAME << " �� �����!\n\n\n" << endl;
        break;
    case 4:
        cout << "\n������! � ����� " << FNAME << " ����� ����� ������ 0!\n\n\n" << endl;
        break;
    case 5:
        cout << "\n������! � ����� " << FNAME << " ����� �������� ������ 0!\n\n\n" << endl;
        break;
    case 6:
        cout << "\n������! � ����� " << FNAME << " �� ��������� ���������� ���������\n\n\n" << endl;
        break;

    }//switch
}//PrintError

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    int errorCode = 0; //��� ������
    int N_A, //���������� ����� � ������� �
        M_A, //���������� �������� � ������� �
        N_B, //���������� ����� � ������� �
        M_B; //���������� �������� � ������� �
    int** A; //������� �
    int** B; //������� B
    A = InpMatr(FNAME_A, N_A, M_A, errorCode);  //������ ������� �
    if (errorCode != 0)  //���� ��������� ������
    {
        PrintError(errorCode, FNAME_A);  //������� ��������� �� ������
    }
    else
    {
        printMatrix(A, N_A, M_A);  //���-������ ������� �
        Task1(A, N_A, M_A);   //������� 1 ��� ������� �
        Task2(A, N_A, M_A);   //������� 2 ��� ������� �
    }//if
    cout << endl << endl;
    B = InpMatr(FNAME_B, N_B, M_B, errorCode); //������ ������� �
    if (errorCode != 0)  //���� ��������� ������
    {
        PrintError(errorCode, FNAME_B);   //������� ��������� �� ������
    }
    else
    {
        printMatrix(B, N_B, M_B);  //���-������ ������� �
        Task1(B, N_B, M_B);  //������� 1 ��� ������� �
        Task2(B, N_B, M_B);  //������� 2 ��� ������� �
    }//if
    return 0;
}//main
