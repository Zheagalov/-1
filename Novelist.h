#ifndef NOVELIST_H
#define NOVELIST_H

#include "Base.h"

// Романист: ФИО, годы жизни, произведения, краткая биография
class Novelist : public Base {
private:
    std::string years;
    std::string biography;
public:
    Novelist();
    Novelist(const std::string& name, const std::string& years, const std::string* works,
             int count, const std::string& biography);
    Novelist(const Novelist& other);
    ~Novelist() override;

    Novelist& operator=(const Novelist& other);

    void setYears(const std::string& y);
    std::string getYears() const;
    void setBiography(const std::string& b);
    std::string getBiography() const;

    Base* clone() const override { return new Novelist(*this); }
    int getType() const override { return 2; }
    std::string getTypeName() const override { return "Романист"; }
    void show(std::ostream& out) const override;
    void edit() override;
    void save(std::ostream& out) const override;
    void load(std::istream& in) override;
};

#endif
