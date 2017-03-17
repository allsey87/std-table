#ifndef TABLE_H
#define TABLE_H

#include <list>
#include <vector>

template <class T, class Container = std::list<T> >
class table {
public:
   // Constructors
   table(unsigned int rows, unsigned int cols) {
      c.resize(rows * cols);
   }

private:
   Container c;
};

#endif


