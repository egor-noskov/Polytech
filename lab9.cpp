#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

bool createF1(const string& filename) {
    ofstream f1(filename);

    if (f1.is_open()) {
        cout << "Введите содержимое файла " << filename << " (не менее 10 строк). Для завершения введите 'END' на отдельной строке:" << endl;

        string line;
        int line_count = 0;
        while (getline(cin, line)) {
            if (line == "END") {
                break;
            }
            f1 << line << endl;
            line_count++;
            if (line_count >= 10 && line != "END")
            {
              break;
            }
        }

        if(line_count < 10){
          cout << "Предупреждение: введено менее 10 строк.  Может некорректно работать" << endl;
        }
        f1.close();
        cout << "Файл " << filename << " успешно создан и заполнен." << endl;
        return true;
    } else {
        cerr << "Ошибка: Не удалось открыть файл " << filename << " для записи." << endl;
        return false;
    }
}

bool copyEvenLines(const string& f1_filename, const string& f2_filename) {
    ifstream f1(f1_filename);
    ofstream f2(f2_filename);

    if (!f1.is_open()) {
        cerr << "Ошибка: Не удалось открыть файл " << f1_filename << " для чтения." << endl;
        return false;
    }

    if (!f2.is_open()) {
        cerr << "Ошибка: Не удалось открыть файл " << f2_filename << " для записи." << endl;
        f1.close();
        return false;
    }

    string line;
    int line_number = 1;

    cout << "nСодержимое файла " << f1_filename << ":" << endl;
    while (getline(f1, line)) {
        cout << line << endl;

        if (line_number % 2 == 0) {
            f2 << line << endl;
        }
        line_number++;
    }
    f1.close();

    f2.close();

    ifstream f2_display(f2_filename);

    if(!f2_display.is_open()) {
      cerr << "Ошибка: Не удалось открыть файл " << f2_filename << " для чтения после записи." << endl;
      return true;
    }

    cout << "nСодержимое файла " << f2_filename << " (четные строки из " << f1_filename << "):" << endl;
    while(getline(f2_display, line)){
      cout << line << endl;
    }

    f2_display.close();

    cout << "Четные строки успешно скопированы из " << f1_filename << " в " << f2_filename << "." << endl;
    return true;
}

long long calculateFileSize(const string& filename) {
    try {
        if (fs::exists(filename)) {
            return fs::file_size(filename);
        } else {
            cerr << "Ошибка: Файл " << filename << " не найден." << endl;
            return -1;
        }
    } catch (const fs::filesystem_error& e) {
        cerr << "Ошибка при определении размера файла " << filename << ": " << e.what() << endl;
        return -1;
    }
}

int main() {
    const string F1_FILENAME = "F1.txt";
    const string F2_FILENAME = "F2.txt";

    if (createF1(F1_FILENAME)) {
        if (copyEvenLines(F1_FILENAME, F2_FILENAME)) {
            long long size_f1 = calculateFileSize(F1_FILENAME);
            long long size_f2 = calculateFileSize(F2_FILENAME);

            if (size_f1 != -1 && size_f2 != -1) {
                cout << "Размер файла " << F1_FILENAME << ": " << size_f1 << " байт" << endl;
                cout << "Размер файла " << F2_FILENAME << ": " << size_f2 << " байт" << endl;
            }
        }
    }

    return 0;
}