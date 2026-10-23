#include "Fantast.h"
#include "Input.h"
#include "AppException.h"

Fantast::Fantast() : Base(), hasFilms(false) {
    std::cout << "[Fantast] Вызван конструктор без параметров" << std::endl;
}

Fantast::Fantast(const std::string& n, const std::string* w, int count, bool f)
    : Base(n, w, count), hasFilms(f) {
    std::cout << "[Fantast] Вызван конструктор с параметрами (" << n << ")" << std::endl;
}

Fantast::Fantast(const Fantast& other) : Base(other), hasFilms(other.hasFilms) {
    std::cout << "[Fantast] Вызван конструктор копирования (" << other.name << ")" << std::endl;
}

Fantast::~Fantast() {
    std::cout << "[Fantast] Вызван деструктор (" << name << ")" << std::endl;
}

Fantast& Fantast::operator=(const Fantast& other) {
    if (this != &other) {
        Base::operator=(other);
        hasFilms = other.hasFilms;
    }
    return *this;
}

void Fantast::setHasFilms(bool f) { hasFilms = f; }

bool Fantast::getHasFilms() const { return hasFilms; }

void Fantast::show(std::ostream& out) const {
    out << "  Тип: " << getTypeName() << std::endl;
    out << "  ФИО: " << name << std::endl;
    showWorks(out);
    out << "  Фильмы по книгам: " << (hasFilms ? "сняты" : "не сняты") << std::endl;
}

void Fantast::edit() {
    std::cout << "  1. ФИО\n  2. Произведения\n  3. Наличие фильмов\n  0. Назад\n";
    int c = readInt("  Что изменить: ", 0, 3);
    if (c == 1) setName(readLine("  Новое ФИО: "));
    else if (c == 2) editWorks();
    else if (c == 3) setHasFilms(readYesNo("  Сняты ли фильмы по книгам"));
}

void Fantast::save(std::ostream& out) const {
    out << getType() << '\n';
    Base::save(out);
    out << (hasFilms ? 1 : 0) << '\n';
}

void Fantast::load(std::istream& in) {
    Base::load(in);
    std::string f = readFileLine(in);
    if (f != "0" && f != "1")
        throw AppException("Ошибка: в файле неверно указано наличие фильмов");
    hasFilms = (f == "1");
}
