#ifndef FANTAST_H
#define FANTAST_H

#include "Base.h"

// Фантаст: ФИО, произведения, сняты ли фильмы по книгам
class Fantast : public Base {
private:
    bool hasFilms;
public:
    Fantast();
    Fantast(const std::string& name, const std::string* works, int count, bool hasFilms);
    Fantast(const Fantast& other);
    ~Fantast() override;

    Fantast& operator=(const Fantast& other);

    void setHasFilms(bool f);
    bool getHasFilms() const;

    Base* clone() const override { return new Fantast(*this); }
    int getType() const override { return 3; }
    std::string getTypeName() const override { return "Фантаст"; }
    void show(std::ostream& out) const override;
    void edit() override;
    void save(std::ostream& out) const override;
    void load(std::istream& in) override;
};

#endif
