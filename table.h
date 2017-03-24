#ifndef TABLE_H
#define TABLE_H

#include <list>

template <class T, class Container = std::list<T> >
class table {
public:
   // Constructors
   table(unsigned int rows, unsigned int cols) :
      m_rows(rows),
      m_cols(cols) {
      c.resize(rows * cols);
   }
   
   // Element-wise access
   typename Container::iterator begin() {
      return std::begin(c);      
   }
   
   typename Container::iterator end() {
      return std::end(c);
   }
   
   /*
   auto rows() {
      return struct {
         row_view_iterator begin = the_begin; 
         row_view_iterator end = the_end;
      };
   }
   
   void some_other_function(row_iterator it_row) {
      row = *it_row;
      
   }
   
   class row_view {
      row_view(table<T>& table, unsigned int index) :
         m_table(table),
         m_index(index) {}
      table<T>& m_table;
      unsigned int m_index;
   };
   */
private:
   unsigned int m_rows;
   unsigned int m_cols;
   
   Container c;
};
#endif
