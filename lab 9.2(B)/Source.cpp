#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> 
using namespace std;
enum Specialnist { KOMPUTERNI_NAUKY, INFORMATYKA, MATEMATYKA_TA_EKONOMIKA, PHISYKA_TA_INFORMATYKA, KIBERBEZPEKA };
string specialnistStr[] = { "КН", "інф", "мат&екон", "фіз&інф", "кібербезпека" };
struct Student
{
    string prizv;
    unsigned kurs;
    Specialnist specialnist;
    unsigned physics;
    unsigned math;
    union
    {
        unsigned programuvannia;
        unsigned chiselni_metody;
        unsigned pedagogika;
    };

};
void Create(Student* p, const int N)
{
    int specialnist;

    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;
        cin.get();
        cin.sync();
        cout << " прізвище: "; getline(cin, p[i].prizv);
        cout << " курс: "; cin >> p[i].kurs;
        cout << " спеціальність (0 - комп'ютерні науки, 1 - інформатика, 2 - математика та економіка, 3 - фізика та інформатика, 4 - кібербезпека):";
        cin >> specialnist;
        cout << " оцінка з фізики: "; cin >> p[i].physics;
        cout << "оцінка з математики: "; cin >> p[i].math;
        p[i].specialnist = Specialnist(specialnist);
        switch (p[i].specialnist)
        {
        case KOMPUTERNI_NAUKY:
            cout << " оцінка з програмування : "; cin >> p[i].programuvannia;
            break;
        case INFORMATYKA:
            cout << "оцінка з чисельних методів: "; cin >> p[i].chiselni_metody;
            break;
        case MATEMATYKA_TA_EKONOMIKA:
        case PHISYKA_TA_INFORMATYKA:
        case KIBERBEZPEKA:
            cout << " оцінка з педагогігики : "; cin >> p[i].pedagogika;
            break;
            cout << endl;
        }
    }
}
void Print(Student* p, const int N)
{
    cout << "========================================================================================================"
        << endl;
    cout << "| № | Прізвище | Курс | Спеціальність | Фізика | Математика | Програмування | Чис. методи | Педагогіка |"
        << endl;
    cout << "--------------------------------------------------------------------------------------------------------"
        << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(1) << right << i + 1 << " ";
        cout << "| " << setw(9) << left << p[i].prizv
            << "| " << setw(4) << right << p[i].kurs << " "
            << "| " << setw(14) << left << specialnistStr[p[i].specialnist]
            << "| " << setw(6) << right << p[i].physics << " "
            << "| " << setw(10) << left << p[i].math << " ";
        switch (p[i].specialnist)
        {
        case KOMPUTERNI_NAUKY:
            cout << "| " << setw(13) << right << p[i].programuvannia << " " << "|" << setw(14) << "|" << setw(13) << "|";
            break;
        case INFORMATYKA:
            cout << "|" << setw(16) << right << fixed << "|" << setw(13) << left << p[i].chiselni_metody << "|" << setw(11) << right << " " << " |";
            break;
        case MATEMATYKA_TA_EKONOMIKA:
        case PHISYKA_TA_INFORMATYKA:
        case KIBERBEZPEKA:
            cout << "|" << setw(17) << right << fixed << "| " << setw(12) << left << " " << "| " << setw(11) << right << p[i].pedagogika << "|";
            break;
            cout << endl;
        }
    }
    cout << "========================================================================================================"
        << endl;
    cout << endl;
}
void Sort(Student* p, const int N)
{
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if ((p[i1].physics > p[i1 + 1].physics)
                ||
                (p[i1].physics == p[i1 + 1].physics &&
                    p[i1].specialnist > p[i1 + 1].specialnist &&
                    p[i1].prizv > p[i1 + 1].prizv))
            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
}
int BinSearch(Student* p, const int N, const string prizv, Specialnist specialnist)
{ // повертає індекс знайденого елемента або -1, якщо шуканий елемент відсутній
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        if (p[m].specialnist == p[m].specialnist && p[m].prizv == prizv)
            return m;
        if ((p[m].prizv < prizv)
            ||
            (p[m].prizv == prizv &&
                p[m].specialnist < p[m].specialnist))
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);
    return -1;
}
int* IndexSort(Student* p, const int N)
{ // використовуємо метод вставки для формування індексного масиву
 //
 // int i, j, value;
 // for (i = 1; i < length; i++) {
 // value = a[i];
 // for (j = i - 1; j >= 0 && a[j] > value; j--) {
 // a[j + 1] = a[j];
 // }
 // a[j + 1] = value;
 // }
    int* I = new int[N]; // створили індексний масив
    for (int i = 0; i < N; i++)
        I[i] = i; // заповнили його початковими даними
    int i, j, value; // починаємо сортувати масив індексів
    for (i = 1; i < N; i++)
    {
        value = I[i];
        for (j = i - 1;
            j >= 0 && ((p[I[j]].physics > p[value].physics) ||
                (p[I[j]].physics == p[value].physics &&
                    p[I[j]].specialnist > p[value].specialnist) ||
                (p[I[j]].specialnist == p[value].specialnist &&
                    p[I[j]].prizv > p[value].prizv));
            j--)
        {
            I[j + 1] = I[j];
        }
        I[j + 1] = value;
    }
    return I;
}
void PrintIndexSorted(Student* p, int* I, const int N)
{ // аналогічно функції Print(), але замість звертання p[i]...
 // використовуємо доступ за допомогою індексного масиву І: p[I[i]]...
    cout << "=========================================================================="
        << endl;
    cout << "| № | Прізвище | Курс | Спеціальність | Фізика | Математика | Інформатика |"
        << endl;
    cout << "--------------------------------------------------------------------------"
        << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(1) << right << i + 1 << " ";
        cout << "| " << setw(10) << left << p[i].prizv
            << "| " << setw(2) << right << p[i].kurs << " "
            << "| " << setw(15) << left << specialnistStr[p[i].specialnist]
            << "| " << setw(6) << right << p[i].physics << " "
            << "| " << setw(10) << left << p[i].math << " ";
        cout << endl;
    }
    cout << "=========================================================================="
        << endl;
    cout << endl;
}
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int N = 0;
    int* I = new int[N];
    string prizv;
    unsigned kurs;
    int ispecialnist;
    Specialnist specialnist;
    int found;
    cout << "Введіть N: "; cin >> N;
    Student* p = new Student[N];
    int menuItem;
    do {
        cout << endl << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - фізичне впорядкування даних" << endl << endl;
        cout << " [4] - бінарний пошук працівника за посадою та прізвищем" << endl;
        cout << " [5] - індексне впорядкування та вивід даних"
            << endl << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl << endl;
        cout << "Введіть значення: "; cin >> menuItem;
        cout << endl << endl << endl;
        switch (menuItem)
        {
        case 1:
            Create(p, N);
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            Sort(p, N);
            break;
        case 4:
            cout << "Введіть ключі пошуку:" << endl;
            cout << " спеціальність (0 - комп'ютерні науки, 1 - інформатика, 2 - математика та економіка, 3 - фізика та інформатика, 4 - кібербезпека): ";
            cin >> ispecialnist;
            specialnist = (Specialnist)ispecialnist;
            cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
            cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

            cout << " прізвище: "; getline(cin, prizv);
            cout << endl;
            if ((found = BinSearch(p, N, prizv, specialnist)) != -1)
                cout << "Знайдено студента в позиції " << found + 1 << endl;
            else
                cout << "Шуканого студента не знайдено" << endl;
            break;
        case 5:
            PrintIndexSorted(p, IndexSort(p, N), N);
            break;

        case 0:
            break;
        default:
            cout << "Ви ввели помилкове значення! "
                "Слід ввести число - номер вибраного пункту меню" << endl;
        }
    } while (menuItem != 0);
    return 0;
}