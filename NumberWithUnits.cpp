#include "NumberWithUnits.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <string>
using namespace std;

namespace ariel
{
    static map<string, map<string, double>> unitmap;
    const static double epselon = 0.001;

    NumberWithUnits::NumberWithUnits(double x, const string &unitnum)
    {
        if (unitmap.count(unitnum) > 0)
        {
            this->num = x;
            this->units = unitnum;
        }
        else
        {
            throw("Fail");
        }
    }

    void NumberWithUnits::read_units(ifstream &file_name)
    {
        if (file_name.fail() || file_name.bad())
        {
            throw runtime_error("reading file failed");
        }
        string a, b;
        double sum = 0;
        while (!file_name.fail() && !file_name.bad())
        {
            file_name >> a;
            if (a == "1")
            {
                if ((file_name >> a >> b >> sum >> b))
                {
                    unitmap[a][b] = sum;
                    unitmap[b][a] = 1 / sum;
                    for (auto &unit : unitmap[a])
                    {
                        double x = sum / unit.second;
                        double x2 = unit.second / sum;
                        unitmap[b][unit.first] = x2;
                        unitmap[unit.first][b] = x;
                    }

                    for (auto &unit : unitmap[b])
                    {
                        double x = (1 / sum) / unit.second;
                        unitmap[unit.first][a] = x;
                        double x2 = unit.second / (1 / sum);
                        unitmap[a][unit.first] = x2;
                    }
                }
            }
        }
    }




    //stream overloading
    istream &operator>>(istream &in, NumberWithUnits &f)
    {
        string unit;
        double num = 0;
        char ch = ' ';
        in >> num;
        in >> ch;
        while (ch != ']')
        {
            if (ch != '[')
            {
                unit.push_back(ch);
            }
            in >> ch;
        }
        if (unitmap.count(unit) >= 1)
        {
            f.units = unit;
            f.num = num;

            return in;
        }
        throw("Empty");
    }
    ostream &operator<<(std::ostream &out, const NumberWithUnits &f)
    {
        return out << (f.num) << "[" << f.units << "]";
    }


    double NumberWithUnits::convert(const NumberWithUnits &meunit, const string &newunit)
    {
        if (unitmap.count(newunit) <=0 || unitmap[meunit.units][newunit] <= 0 || unitmap[newunit][meunit.units] <= 0)
        {
            throw invalid_argument("Wrong ");
        }
        if (meunit.units == newunit)
        {
            return meunit.num;
        }
    
        double a=unitmap[meunit.units][newunit];
        double b=meunit.num;
        return a * b;
    }



    bool NumberWithUnits::operator==(const NumberWithUnits &f) const
    {
        return (abs(this->num - convert(f, this->units)) <= epselon);
    }

    bool NumberWithUnits::operator!=(const NumberWithUnits &f) const
    {
        return !(*this == f);
    }
    bool NumberWithUnits::operator>(const NumberWithUnits &f) const
    {
        return this->num - convert(f, this->units) >= epselon;
    }
    bool operator>=(const NumberWithUnits &f, const NumberWithUnits &f2)
    {
        return ((f == f2) || (f > f2));
    }
    bool NumberWithUnits::operator<(const NumberWithUnits &f) const
    {
        return convert(f, this->units) - this->num >= epselon;
    }

    bool NumberWithUnits::operator<=(const NumberWithUnits &f) const
    {
        return !(*this > f);
    }


    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &f) const
    {
        return NumberWithUnits(convert(f, this->units) + this->num, this->units);
    }
    NumberWithUnits NumberWithUnits::operator+() const
    {
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &f) const
    {
        return NumberWithUnits{this->num - convert(f, this->units), this->units};
    }

    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &f)
    {
        *this = *this + f;
        return *this;
    }

    // NumberWithUnits operator-(const NumberWithUnits &f) const;
    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &f)
    {
        *this = *this - f;
        return *this;
    }

    
    NumberWithUnits NumberWithUnits::operator-() const
    {
        return NumberWithUnits{-this->num, this->units};
    }

    NumberWithUnits NumberWithUnits::operator++(int)
    {
        return NumberWithUnits(this->num++, this->units);
    }
    NumberWithUnits &NumberWithUnits::operator++()
    {
        ++(this->num);
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator--(int)
    {
        return NumberWithUnits(this->num--, this->units);
    }
    NumberWithUnits &NumberWithUnits::operator--()
    {
        --(this->num);
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator*(double y) const
    {
        return NumberWithUnits{this->num * y, this->units};
    }
    NumberWithUnits operator*(double y, const NumberWithUnits &f)
    {
        return NumberWithUnits{y * f.num, f.units};
    }


}