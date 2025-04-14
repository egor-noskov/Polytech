#include <iostream>
#include <string>
#include <clocale>
#include <limits>
using namespace std;

class Student {
    string fio;
    string gruppa;
    float srball;

public:
    Student() {
        fio = "-";
        gruppa = "-";
        srball = 0;
        cout << "Конструктор без параметров для объекта " << this << endl;
    }

    Student(string F, string G, float S) {
        fio = F;
        gruppa = G;
        srball = S;
        cout << "Конструктор с параметрами для объекта " << this << endl;
    }

    Student(const Student& student) {
        fio = student.fio;
        gruppa = student.gruppa;
        srball = student.srball;
        cout << "Конструктор копирования для объекта " << this << endl;
    }

    ~Student() {
        cout << "Деструктор для объекта " << this << endl;
    }

    string get_fio() {
        return fio;
    }

    void set_fio(string F) {
        fio = F;
    }

    string get_gruppa() {
        return gruppa;
    }

    void set_gruppa(string G) {
        gruppa = G;
    }

    float get_srball() {
        return srball;
    }

    void set_srball(float S) {
        srball = S;
    }

    void show() {
        cout << "ФИО: " << fio << endl;
        cout << "Группа: " << gruppa << endl;
        cout << "Средний балл: " << srball << endl;
    }
};

Student Make_Student() {
    string fio, gruppa;
    float srball;
    cout << "Введите ФИО" << endl;
    getline(cin, fio);
    cout << "Введите группу" << endl;
    getline(cin, gruppa); // Исправлено: использована правильная переменная
    cout << "Введите средний балл" << endl;
    cin >> srball;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Student student(fio, gruppa, srball);
    return student;
}

void Print_Student(Student student) {
    student.show();
}

int main() {
    setlocale(LC_ALL, "RU");
    system("chcp 1251");
    system("cls");

    Student student1;
    student1.show();

    Student student2("Носков Егор Михайлович", "РИС-24-3Б", 2.33);
    student2.show();

    Student student3 = student1;
    student3.set_fio("Александров Александр Александрович");
    student3.set_gruppa("ИВТ-24-1");
    student3.set_srball(3.44);
    Print_Student(student3);

    student1 = Make_Student();
    student1.show();

    return 0;
}