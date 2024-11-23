#include <iostream>
#include <conio.h>
#include <string>
#include <cstdlib>
#include<vector>

using namespace std;

struct Student {
    string name;
    string group;
    string id;
    int grades[4];
};
struct Listitem {
    Student student;
    Listitem* pnext, * plast;
};
struct List {
    Listitem* pFirst;
};

void addinlist(List& list, Listitem* p, bool flag = true) {
    if (list.pFirst == nullptr) {
        list.pFirst = p->pnext = p->plast = p;
    }
    else {
        p->pnext = list.pFirst;
        p->plast = list.pFirst->plast;
        list.pFirst->plast->pnext = p;
        list.pFirst->plast = p;
        if (flag) list.pFirst = p;
    }
}
void addAfterZad(Listitem* pZad, Listitem* p)
{
    p->pnext = pZad->pnext;
    p->plast = pZad;
    pZad->pnext->plast = p;
    pZad->pnext = p;
}
Listitem* myremove(List& list, Listitem* p) {
    if (list.pFirst == 0 || p == 0) return 0;
    if (list.pFirst->pnext == list.pFirst) // Список состоит из 1 элемента
    {
        if (p == list.pFirst)
        {
            list.pFirst = 0;
            return p;
        }
        else return 0; // Ошибка
    }
    if (p == list.pFirst) // Извлекаемый элемент первый
        list.pFirst = list.pFirst->pnext; // Второй будет первым
    p->plast->pnext = p->pnext;
    p->pnext->plast = p->plast;
    return p;

}

void print(List list) {
    if (list.pFirst == nullptr) {
        cout << "The list is empty." << endl;
        return;
    }
    Listitem* p = list.pFirst;
    do {
        cout << "\nName - " << p->student.name << endl << "ID - " << p->student.id << endl << "Group - " << p->student.group << endl;
        cout << "Grades: ";
        cout << p->student.grades[0] << " " << p->student.grades[1] << " " << p->student.grades[2] << " " << p->student.grades[3] << endl;
        cout << endl;
        p = p->pnext;
    } while (p != list.pFirst);
}


int main() {
    setlocale(LC_ALL, "rus");
    List l = { nullptr }; // Инициализация списка
    Listitem* p;
    char ch;

    do {
        p = new Listitem;
        cout << "name - ";
        getline(cin, p->student.name);
        cout << "ID - ";
        getline(cin, p->student.id);
        cout << "Group - ";
        getline(cin, p->student.group);
        cout << "Enter grades: " << endl;
        cin >> p->student.grades[0];
        cin >> p->student.grades[1];
        cin >> p->student.grades[2];
        cin >> p->student.grades[3];
        cin.ignore();
        addinlist(l, p, false);

        cout << "Press 'Y' to continue, or any other key to exit: ";
        ch = _getche();
        cout << endl;
    } while (ch == 'Y' || ch == 'y');

    cout << "Your list before sorting: " << endl;
    print(l);
    cout << "Your list after sortnig: " << endl;
    p = l.pFirst->pnext;
    do {
        Listitem* p1 = p->pnext;
        Listitem* p2 = l.pFirst;
        do {
            if (p2->student.name > p->student.name) {
                p = myremove(l, p);
                if (p == 0) {
                    cout << "List error";
                    system("pause");
                    return 0;
                }
                if (p2 == l.pFirst) addinlist(l, p, true);
                else addAfterZad(p2->plast, p);
                break;
            }
            p2 = p2->pnext;
        } while (p2 != p);
    } while (p != l.pFirst);
    print(l);

    return 0;
}
