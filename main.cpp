#include <iostream>
#include <string>
#include "Keeper.h"
#include "Poet.h"
#include "Novelist.h"
#include "Fantast.h"
#include "Input.h"
#include "AppException.h"

#ifdef _WIN32
#include <windows.h>
#endif

// Ввод списка произведений с клавиатуры, массив создаётся динамически
static std::string* inputWorks(int& count) {
    count = readInt("Количество произведений (0-50): ", 0, 50);
    std::string* works = count > 0 ? new std::string[count] : nullptr;
    try {
        for (int i = 0; i < count; i++)
            works[i] = readLine("  Произведение " + std::to_string(i + 1) + ": ");
    } catch (...) {
        delete[] works;
        throw;
    }
    return works;
}

static Base* createObject() {
    std::cout << "1. Поэт\n2. Романист\n3. Фантаст\n0. Отмена\n";
    int type = readInt("Тип объекта: ", 0, 3);
    if (type == 0) return nullptr;

    std::string name = readLine("ФИО: ");
    std::string years;
    if (type != 3) years = readYears("Годы жизни (ГГГГ-ГГГГ или ГГГГ-): ");
    int count = 0;
    std::string* works = inputWorks(count);

    Base* obj = nullptr;
    try {
        if (type == 1) {
            obj = new Poet(name, years, works, count);
        } else if (type == 2) {
            std::string bio = readLine("Краткая биография: ");
            obj = new Novelist(name, years, works, count, bio);
        } else {
            bool films = readYesNo("Сняты ли фильмы по книгам");
            obj = new Fantast(name, works, count, films);
        }
    } catch (...) {
        delete[] works;
        throw;
    }
    delete[] works;
    return obj;
}

static int chooseIndex(Keeper& k) {
    if (k.getSize() == 0) throw AppException("Ошибка: контейнер пуст");
    return readInt("Номер объекта (1-" + std::to_string(k.getSize()) + "): ", 1, k.getSize()) - 1;
}

int main() {
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif
    Keeper keeper;
    bool running = true;

    while (running) {
        std::cout << "\n===== ПЕЧАТНОЕ ИЗДАНИЕ =====\n"
                  << "Объектов в контейнере: " << keeper.getSize() << "\n"
                  << "1. Добавить объект\n"
                  << "2. Удалить объект\n"
                  << "3. Показать все объекты\n"
                  << "4. Показать один объект\n"
                  << "5. Изменить объект\n"
                  << "6. Скопировать объект\n"
                  << "7. Сохранить контейнер в файл\n"
                  << "8. Загрузить контейнер из файла\n"
                  << "0. Выход\n";
        try {
            int choice = readInt("Выбор: ", 0, 8);
            switch (choice) {
            case 1: {
                Base* obj = createObject();
                if (obj != nullptr) {
                    keeper += obj;
                    std::cout << "Объект добавлен" << std::endl;
                }
                break;
            }
            case 2:
                keeper -= chooseIndex(keeper);
                std::cout << "Объект удалён" << std::endl;
                break;
            case 3:
                keeper.showAll(std::cout);
                break;
            case 4:
                std::cout << keeper[chooseIndex(keeper)];
                break;
            case 5: {
                int i = chooseIndex(keeper);
                std::cout << keeper[i];
                keeper[i].edit();
                std::cout << "Текущие данные:" << std::endl << keeper[i];
                break;
            }
            case 6:
                keeper += keeper[chooseIndex(keeper)].clone();
                std::cout << "Копия добавлена в конец контейнера" << std::endl;
                break;
            case 7: {
                std::string file = readLine("Имя файла: ");
                keeper.saveToFile(file);
                std::cout << "Контейнер сохранён в файл " << file << std::endl;
                break;
            }
            case 8: {
                std::string file = readLine("Имя файла: ");
                keeper.loadFromFile(file);
                std::cout << "Загружено объектов: " << keeper.getSize() << std::endl;
                break;
            }
            case 0:
                running = false;
                break;
            }
        } catch (const AppException& e) {
            std::cout << e.what() << std::endl;
            if (!std::cin) running = false;
        } catch (const std::bad_alloc&) {
            std::cout << "Ошибка: не хватает памяти" << std::endl;
        }
    }
    std::cout << "Завершение работы программы" << std::endl;
    return 0;
}
