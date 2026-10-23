#ifndef POET_H
#define POET_H

#include "Base.h"

// Поэт: ФИО, годы жизни, основные произведения
class Poet : public Base {
private:
    std::string years;
public:
    Poet();
    Poet(const std::string& name, const std::string& years, const std::string* works, int count);
    Poet(const Poet& other);
    ~Poet() override;

    Poet& operator=(const Poet& other);

    void setYears(const std::string& y);
    std::string getYears() const;

    Base* clone() const override { return new Poet(*this); }
    int getType() const override { return 1; }
    std::string getTypeName() const override { return "Поэт"; }
    void show(std::ostream& out) const override;
    void edit() override;
    void save(std::ostream& out) const override;
    void load(std::istream& in) override;
};

#endif
