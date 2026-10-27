#include "Keeper.h"
#include "Poet.h"
#include "Novelist.h"
#include "Fantast.h"
#include "Input.h"
#include "AppException.h"
#include <fstream>

Keeper::Keeper() : items(nullptr), size(0) {
    std::cout << "[Keeper] Вызван конструктор без параметров" << std::endl;
}

Keeper::Keeper(const std::string& fileName) : items(nullptr), size(0) {
    std::cout << "[Keeper] Вызван конструктор с параметрами (файл " << fileName << ")" << std::endl;
    loadFromFile(fileName);
}

Keeper::Keeper(const Keeper& other) : items(nullptr), size(0) {
    std::cout << "[Keeper] Вызван конструктор копирования" << std::endl;
    if (other.size > 0) {
        items = new Base*[other.size];
        for (int i = 0; i < other.size; i++) items[i] = other.items[i]->clone();
        size = other.size;
    }
}

Keeper::~Keeper() {
    std::cout << "[Keeper] Вызван деструктор" << std::endl;
    clear();
}

void Keeper::clear() {
    for (int i = 0; i < size; i++) delete items[i];
    delete[] items;
    items = nullptr;
    size = 0;
}

Keeper& Keeper::operator=(const Keeper& other) {
    if (this != &other) {
        Keeper tmp(other);
        Base** t = items; items = tmp.items; tmp.items = t;
        int s = size; size = tmp.size; tmp.size = s;
    }
    return *this;
}

Keeper& Keeper::operator+=(Base* obj) {
    add(obj);
    return *this;
}

Keeper& Keeper::operator-=(int index) {
    remove(index);
    return *this;
}

Base& Keeper::operator[](int index) {
    if (index < 0 || index >= size)
        throw AppException("Ошибка: объекта с номером " + std::to_string(index + 1) + " нет в контейнере");
    return *items[index];
}

void Keeper::add(Base* obj) {
    if (obj == nullptr) throw AppException("Ошибка: попытка добавить пустой объект");
    Base** tmp = new Base*[size + 1];
    for (int i = 0; i < size; i++) tmp[i] = items[i];
    tmp[size] = obj;
    delete[] items;
    items = tmp;
    size++;
}

void Keeper::remove(int index) {
    if (size == 0) throw AppException("Ошибка: контейнер пуст, удалять нечего");
    if (index < 0 || index >= size)
        throw AppException("Ошибка: объекта с номером " + std::to_string(index + 1) + " нет в контейнере");
    delete items[index];
    Base** tmp = nullptr;
    if (size > 1) {
        tmp = new Base*[size - 1];
        for (int i = 0, j = 0; i < size; i++)
            if (i != index) tmp[j++] = items[i];
    }
    delete[] items;
    items = tmp;
    size--;
}

int Keeper::getSize() const { return size; }

void Keeper::showAll(std::ostream& out) const {
    if (size == 0) {
        out << "Контейнер пуст" << std::endl;
        return;
    }
    for (int i = 0; i < size; i++) {
        out << "Объект №" << i + 1 << std::endl;
        out << *items[i];
    }
}

void Keeper::saveToFile(const std::string& fileName) const {
    std::ofstream out(fileName);
    if (!out.is_open())
        throw AppException("Ошибка: не удалось открыть файл \"" + fileName + "\" для записи");
    out << size << '\n';
    for (int i = 0; i < size; i++) items[i]->save(out);
    if (!out.good())
        throw AppException("Ошибка: при записи в файл \"" + fileName + "\" произошёл сбой");
}

void Keeper::loadFromFile(const std::string& fileName) {
    std::ifstream in(fileName);
    if (!in.is_open())
        throw AppException("Ошибка: файл \"" + fileName + "\" не найден или не открывается");
    int count;
    try {
        count = std::stoi(readFileLine(in));
    } catch (const std::invalid_argument&) {
        throw AppException("Ошибка: в начале файла должно быть количество объектов");
    }
    if (count < 0) throw AppException("Ошибка: в файле указано отрицательное количество объектов");

    // Объекты собираются во временный массив, чтобы при ошибке не потерять текущие данные
    Base** tmp = count > 0 ? new Base*[count]() : nullptr;
    int loaded = 0;
    try {
        for (; loaded < count; loaded++) {
            std::string type = readFileLine(in);
            Base* obj;
            if (type == "1") obj = new Poet();
            else if (type == "2") obj = new Novelist();
            else if (type == "3") obj = new Fantast();
            else throw AppException("Ошибка: в файле неизвестный тип объекта \"" + type + "\"");
            tmp[loaded] = obj;
            obj->load(in);
        }
    } catch (...) {
        for (int i = 0; i < count; i++) delete tmp[i];
        delete[] tmp;
        throw;
    }
    clear();
    items = tmp;
    size = count;
}
