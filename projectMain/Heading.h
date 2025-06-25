#pragma once
class Heading {
public:
    virtual double calcHeadingBonus(size_t numSubordinates) = 0;
    virtual ~Heading() {};
};