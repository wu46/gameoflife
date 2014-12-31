#ifndef POINTLL_H
#define POINTLL_H

#include <string>

class PointLL
{
public:
    PointLL();
    PointLL(long long x, long long y);
    std::string toString() const;
    long long getX() const;
    long long getY() const;
    bool operator==(const PointLL & p2) const;
    bool operator!=(const PointLL & p2) const;
    bool operator<(const PointLL & p2) const;
    bool operator>(const PointLL & p2) const;

private:
    long long x;
    long long y;
};

std::ostream & operator<<(std::ostream & os, const PointLL & pt);

#endif // POINTLL_H
