#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <map>

namespace ariel
{

    class NumberWithUnits
    {

    private:
        double num;
        std::string units;
        static double convert(const NumberWithUnits &meunit, const std::string &newunit);

    public:
        //constructor
        NumberWithUnits(double x, const std::string &unitnum);
        static void read_units(std::ifstream &file_name);

        //6 math opertaors
        NumberWithUnits operator+(const NumberWithUnits &f) const;
        NumberWithUnits &operator+=(const NumberWithUnits &f);
        NumberWithUnits operator+() const;
        NumberWithUnits operator-(const NumberWithUnits &f) const;
        NumberWithUnits &operator-=(const NumberWithUnits &f);
        NumberWithUnits operator-() const; //minus of the number
        //6 comparison operators
        bool operator==(const NumberWithUnits &f) const;
        bool operator!=(const NumberWithUnits &f) const;
        bool operator>(const NumberWithUnits &f) const;
        friend bool operator>=(const NumberWithUnits &f, const NumberWithUnits &f2);
        bool operator<(const NumberWithUnits &f) const;
        bool operator<=(const NumberWithUnits &f) const;

        //Magnification by 1
        NumberWithUnits operator++(int); //postfix z++
        NumberWithUnits &operator++();   //prefix ++z
                                         //The smaller in 1
        NumberWithUnits operator--(int); //postfix z--
        NumberWithUnits &operator--();   //prefix --z
                                         //Multiplication
        NumberWithUnits operator*(double y) const;
        friend NumberWithUnits operator*(double y, const NumberWithUnits &f);

        //----------------------------------
        // friend global IO operators
        //----------------------------------
        //operator input
        friend std::istream &operator>>(std::istream &ins, NumberWithUnits &f);

        //operator output
        friend std::ostream &operator<<(std::ostream &outs, const NumberWithUnits &f);
    };
}