#include "pointll.h"
#include <string>
#include "strlib.h"

using namespace std;

PointLL::PointLL()
{
  x = 0;
  y = 0;
}

PointLL::PointLL(long long x, long long y) {
  this->x = x;
  this->y = y;
}

std::string PointLL::toString() const {
  return "(" + longLongToString(x) + "," + longLongToString(y) + ")";
}

long long PointLL::getX() const{
  return x;
}

long long PointLL::getY() const{
  return y;
}

bool PointLL::operator==(const PointLL & p2) const {
  return (x==p2.x && y==p2.y);
}

bool PointLL::operator!=(const PointLL & p2) const {
  return (x!=p2.x || y!=p2.y);
}

bool PointLL::operator<(const PointLL & p2) const {
  //cout << "comparing " << (*this) << " and " << p2 << endl;
  if (x != p2.x)
    {
      return (x < p2.x);
    }
  else
    {
      return (y < p2.y);
    }
  //return (*this != p2);
}

bool PointLL::operator>(const PointLL & p2) const {
  cout << "hmmm they actually called > " << endl;
  if (x > p2.x)
    {
      return (x > p2.x);
    }
  else
    {
      return (y > p2.y);
    }
}

std::ostream & operator<<(std::ostream & os, const PointLL & pt) {
  return os << pt.toString();
}

