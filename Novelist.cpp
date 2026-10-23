#include "Novelist.h"
#include "Input.h"
#include "AppException.h"

Novelist::Novelist() : Base(), years("0000-"), biography("нет данных") {
    std::cout << "[Novelist] Вызван конструктор без параметров" << std::endl;
}

Novelist::Novelist(const std::string& n, const std::string& y, const std::string* w,
                   int count, const std::string& b)
    : Base(n, w, count), years(y), biography(b) {
    std::cout << "[Novelist] Вызван конструктор с параметрами (" << n << ")" << std::endl;
}

Novelist::Novelist(const Novelist& other)
    : Base(other), years(other.years), biography(other.biography) {
    std::cout << "[Novelist] Вызван конструктор копирования (" << other.name << ")" << std::endl;
}

Novelist::~Novelist() {
    std::cout << "[Novelist] Вызван деструктор (" << name << ")" << std::endl;
}

Novelist& Novelist::operator=(const Novelist& other) {
    if (this != &other) {
        Base::operator=(other);
        years = other.years;
        biography = other.biography;
    }
    return *this;
}

void Novelist::setYears(const std::string& y) {
    if (y.empty()) throw AppException("Ошибка: годы жизни не могут быть пустыми");
    years = y;
}

std::string Novelist::getYears() const { return years; }

void Novelist::setBiography(const std::string& b) {
    if (b.empty()) throw AppException("Ошибка: биография не может быть пустой");
    biography = b;
}

std::string Novelist::getBiography() const { return biography; }

void Novelist::show(std::ostream& out) const {
    out << "  Тип: " << getTypeName() << std::endl;
    out << "  ФИО: " << name << std::endl;
    out << "  Годы жизни: " << years << std::endl;
    showWorks(out);
    out << "  Биография: " << biography << std::endl;
}

void Novelist::edit() {
    std::cout << "  1. ФИО\n  2. Годы жизни\n  3. Произведения\n  4. Биография\n  0. Назад\n";
    int c = readInt("  Что изменить: ", 0, 4);
    if (c == 1) setName(readLine("  Новое ФИО: "));
    else if (c == 2) setYears(readYears("  Годы жизни (ГГГГ-ГГГГ): "));
    else if (c == 3) editWorks();
    else if (c == 4) setBiography(readLine("  Краткая биография: "));
}

void Novelist::save(std::ostream& out) const {
    out << getType() << '\n';
    Base::save(out);
    out << years << '\n' << biography << '\n';
}

void Novelist::load(std::istream& in) {
    Base::load(in);
    years = readFileLine(in);
    biography = readFileLine(in);
}
