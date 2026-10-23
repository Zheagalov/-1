#include "Base.h"
#include "AppException.h"
#include "Input.h"

Base::Base() : name("Неизвестно"), works(nullptr), worksCount(0) {
    std::cout << "[Base] Вызван конструктор без параметров" << std::endl;
}

Base::Base(const std::string& n, const std::string* w, int count)
    : name(n), works(nullptr), worksCount(0) {
    std::cout << "[Base] Вызван конструктор с параметрами (" << n << ")" << std::endl;
    setWorks(w, count);
}

Base::Base(const Base& other) : name(other.name), works(nullptr), worksCount(0) {
    std::cout << "[Base] Вызван конструктор копирования (" << other.name << ")" << std::endl;
    setWorks(other.works, other.worksCount);
}

Base::~Base() {
    std::cout << "[Base] Вызван деструктор (" << name << ")" << std::endl;
    delete[] works;
}

Base& Base::operator=(const Base& other) {
    if (this != &other) {
        name = other.name;
        setWorks(other.works, other.worksCount);
    }
    return *this;
}

void Base::setName(const std::string& n) {
    if (n.empty()) throw AppException("Ошибка: ФИО не может быть пустым");
    name = n;
}

std::string Base::getName() const { return name; }

void Base::setWorks(const std::string* w, int count) {
    if (count < 0) throw AppException("Ошибка: количество произведений не может быть отрицательным");
    std::string* tmp = nullptr;
    if (count > 0) {
        tmp = new std::string[count];
        for (int i = 0; i < count; i++) tmp[i] = w[i];
    }
    delete[] works;
    works = tmp;
    worksCount = count;
}

int Base::getWorksCount() const { return worksCount; }

std::string Base::getWork(int index) const {
    if (index < 0 || index >= worksCount)
        throw AppException("Ошибка: произведения с номером " + std::to_string(index + 1) + " нет");
    return works[index];
}

void Base::addWork(const std::string& w) {
    if (w.empty()) throw AppException("Ошибка: название произведения не может быть пустым");
    std::string* tmp = new std::string[worksCount + 1];
    for (int i = 0; i < worksCount; i++) tmp[i] = works[i];
    tmp[worksCount] = w;
    delete[] works;
    works = tmp;
    worksCount++;
}

void Base::removeWork(int index) {
    if (index < 0 || index >= worksCount)
        throw AppException("Ошибка: произведения с номером " + std::to_string(index + 1) + " нет");
    std::string* tmp = nullptr;
    if (worksCount > 1) {
        tmp = new std::string[worksCount - 1];
        for (int i = 0, j = 0; i < worksCount; i++)
            if (i != index) tmp[j++] = works[i];
    }
    delete[] works;
    works = tmp;
    worksCount--;
}

void Base::showWorks(std::ostream& out) const {
    out << "  Произведения:";
    if (worksCount == 0) out << " нет";
    out << std::endl;
    for (int i = 0; i < worksCount; i++)
        out << "    " << i + 1 << ". " << works[i] << std::endl;
}

void Base::save(std::ostream& out) const {
    out << name << '\n' << worksCount << '\n';
    for (int i = 0; i < worksCount; i++) out << works[i] << '\n';
}

void Base::load(std::istream& in) {
    name = readFileLine(in);
    int count;
    try {
        count = std::stoi(readFileLine(in));
    } catch (const std::invalid_argument&) {
        throw AppException("Ошибка: в файле неверно указано количество произведений");
    }
    if (count < 0) throw AppException("Ошибка: в файле отрицательное количество произведений");
    std::string* tmp = count > 0 ? new std::string[count] : nullptr;
    try {
        for (int i = 0; i < count; i++) tmp[i] = readFileLine(in);
    } catch (...) {
        delete[] tmp;
        throw;
    }
    delete[] works;
    works = tmp;
    worksCount = count;
}

void Base::editWorks() {
    showWorks(std::cout);
    std::cout << "  1. Добавить произведение\n  2. Удалить произведение\n  0. Назад\n";
    int c = readInt("  Выбор: ", 0, 2);
    if (c == 1) {
        addWork(readLine("  Название произведения: "));
        std::cout << "  Произведение добавлено" << std::endl;
    } else if (c == 2) {
        if (worksCount == 0) throw AppException("Ошибка: список произведений пуст");
        removeWork(readInt("  Номер произведения: ", 1, worksCount) - 1);
        std::cout << "  Произведение удалено" << std::endl;
    }
}

std::ostream& operator<<(std::ostream& out, const Base& obj) {
    obj.show(out);
    return out;
}
