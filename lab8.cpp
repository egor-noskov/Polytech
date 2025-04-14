
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;


struct Abiturient {
    char fio[64];
    int god_rozhdeniya;
    int ocenki[3];
    float sredniy_ball_attestata;
};

const char* FILENAME = "abiturients.dat";

void create_file(const char* filename) {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Ошибка при создании файла: " << filename << endl;
        return;
    }

    vector<Abiturient> abiturients = {
        {"Иванов Иван Иванович", 2003, {4, 5, 4}, 4.5f},
        {"Петров Петр Петрович", 2002, {5, 5, 5}, 4.8f},
        {"Сидоров Сидор Сидорович", 2004, {3, 4, 3}, 3.9f}
    };

    for (const auto& abiturient : abiturients) {
        file.write(reinterpret_cast<const char*>(&abiturient), sizeof(Abiturient));
    }

    file.close();
    cout << "Файл '" << filename << "' успешно создан и заполнен." << endl;
}

void print_file(const char* filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Ошибка при открытии файла: " << filename << endl;
        return;
    }

    Abiturient abiturient;
    while (file.read(reinterpret_cast<char*>(&abiturient), sizeof(Abiturient))) {
        cout << "ФИО: " << abiturient.fio
             << ", Год рождения: " << abiturient.god_rozhdeniya
             << ", Оценки: " << abiturient.ocenki[0] << " " << abiturient.ocenki[1] << " " << abiturient.ocenki[2]
             << ", Ср. балл: " << abiturient.sredniy_ball_attestata << endl;
    }

    file.close();
}

void delete_abiturient_by_index(const char* filename) {
    int index_to_delete;

    cout << "Введите индекс абитуриента для удаления: ";
    cin >> index_to_delete;

    vector<Abiturient> abiturients;
    ifstream file_read(filename, ios::binary);
    if (!file_read.is_open()) {
        cerr << "Ошибка при открытии файла для чтения." << endl;
        return;
    }

    Abiturient abiturient;
    while (file_read.read(reinterpret_cast<char*>(&abiturient), sizeof(Abiturient))) {
        abiturients.push_back(abiturient);
    }
    file_read.close();

    if (index_to_delete < 0 || index_to_delete >= abiturients.size()) {
        cerr << "Недопустимый индекс для удаления: " << index_to_delete << endl;
        return;
    }

    ofstream file_write(filename, ios::binary);
    if (!file_write.is_open()) {
        cerr << "Ошибка при открытии файла для записи." << endl;
        return;
    }

    for (size_t i = 0; i < abiturients.size(); ++i) {
        if (i != static_cast<size_t>(index_to_delete)) {
            file_write.write(reinterpret_cast<const char*>(&abiturients[i]), sizeof(Abiturient));
        }
    }
    file_write.close();

    cout << "Абитуриент с индексом " << index_to_delete << " успешно удален." << endl;
}
int find_abiturient(const char* filename, const char* fio_to_find) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Ошибка при открытии файла: " << filename << endl;
        return -1; 
    }

    Abiturient abiturient;
    int index = 0;
    while (file.read(reinterpret_cast<char*>(&abiturient), sizeof(Abiturient))) {
        if (strcmp(abiturient.fio, fio_to_find) == 0) {
            file.close();
            return index; 
        }
        index++;
    }

    file.close();
    return -2; 
}

void add_abiturient_after(const char* filename, const char* fio_after, const Abiturient& new_abiturient) {
    int index_after = find_abiturient(filename, fio_after);

    if (index_after == -1) {
        cerr << "Ошибка при открытии файла для поиска." << endl;
        return;
    }
    if (index_after == -2) {
        cout << "Абитуриент с ФИО '" << fio_after << "' не найден." << endl;
        return;
    }

    vector<Abiturient> abiturients;
    ifstream file_read(filename, ios::binary);
    if (!file_read.is_open()) {
        cerr << "Ошибка при открытии файла для чтения." << endl;
        return;
    }

    Abiturient abiturient;
    while (file_read.read(reinterpret_cast<char*>(&abiturient), sizeof(Abiturient))) {
        abiturients.push_back(abiturient);
    }
    file_read.close();

    abiturients.insert(abiturients.begin() + index_after + 1, new_abiturient);

    ofstream file_write(filename, ios::binary);
    if (!file_write.is_open()) {
        cerr << "Ошибка при открытии файла для записи." << endl;
        return;
    }

    for (const auto& ab : abiturients) {
        file_write.write(reinterpret_cast<const char*>(&ab), sizeof(Abiturient));
    }
    file_write.close();

    cout << "Абитуриент с ФИО '" << new_abiturient.fio << "' успешно добавлен после '" << fio_after << "'." << endl;
}


int main() {
    create_file(FILENAME);
    cout << "Содержимое файла:" << endl;
    print_file(FILENAME);
    delete_abiturient_by_index(FILENAME);

    cout << "\nСодержимое файла после удаления:" << endl;
    print_file(FILENAME);
    Abiturient new_abiturient;
    strcpy(new_abiturient.fio, "Смирнов Алексей Иванович");
    new_abiturient.god_rozhdeniya = 2001;
    new_abiturient.ocenki[0] = 5;
    new_abiturient.ocenki[1] = 4;
    new_abiturient.ocenki[2] = 5;
    new_abiturient.sredniy_ball_attestata = 4.9f;
    add_abiturient_after(FILENAME, "Иванов Иван Иванович", new_abiturient);

    cout << "\nСодержимое файла после добавления:" << endl;
    print_file(FILENAME);

    return 0;
}
