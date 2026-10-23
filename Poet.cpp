#include "Poet.h"
#include "Input.h"
#include "AppException.h"

Poet::Poet() : Base(), years("0000-") {
    std::cout << "[Poet] Вызван конструктор без параметров" << std::endl;
}

Poet::Poet(const std::string& n, const std::string& y, const std::string* w, int count)
    : Base(n, w, count), years(y) {
    std::cout << "[Poet] Вызван конструктор с параметрами (" << n << ")" << std::endl;
}

Poet::Poet(const Poet& other) : Base(other), years(other.years) {
    std::cout << "[Poet] Вызван конструктор копирования (" << other.name << ")" << std::endl;
}

Poet::~Poet() {
    std::cout << "[Poet] Вызван деструктор (" << name << ")" << std::endl;
}

Poet& Poet::operator=(const Poet& other) {
    if (this != &other) {
        Base::operator=(other);
        years = other.years;
    }
    return *this;
}

void Poet::setYears(const std::string& y) {
    if (y.empty()) throw AppException("Ошибка: годы жизни не могут быть пустыми");
    years = y;
}

std::string Poet::getYears() const { return years; }

void Poet::show(std::ostream& out) const {
    out << "  Тип: " << getTypeName() << std::endl;
    out << "  ФИО: " << name << std::endl;
    out << "  Годы жизни: " << years << std::endl;
    showWorks(out);
}

void Poet::edit() {
    std::cout << "  1. ФИО\n  2. Годы жизни\n  3. Произведения\n  0. Назад\n";
    int c = readInt("  Что изменить: ", 0, 3);
    if (c == 1) setName(readLine("  Новое ФИО: "));
    else if (c == 2) setYears(readYears("  Годы жизни (ГГГГ-ГГГГ): "));
    else if (c == 3) editWorks();
}

void Poet::save(std::ostream& out) const {
    out << getType() << '\n';
    Base::save(out);
    out << years << '\n';
}

void Poet::load(std::istream& in) {
    Base::load(in);
    years = readFileLine(in);
}
