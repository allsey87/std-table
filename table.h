#ifndef TABLE_H
#define TABLE_H


#include <list>

template <class T, class Container = std::list<T> >
class table {
public:
   typedef typename Container::value_type       value_type;
   typedef typename Container::reference        reference;
   typedef typename Container::const_reference  const_reference;
   typedef typename Container::size_type        size_type;
   typedef          Container                   container_type;
   
public:
   // Constructors
   table(unsigned int rows, unsigned int cols) :
      m_rows(rows),
      m_cols(cols) {
      c.resize(rows * cols);
   }
   
   table(unsigned int rows, unsigned int cols, std::initializer_list<value_type> values) :
      m_rows(rows),
      m_cols(cols) {
      c.assign(values);
   }
   
   // Element-wise access
   typename Container::iterator begin() {
      return std::begin(c);      
   }
   
   typename Container::iterator end() {
      return std::end(c);
   }
   
   class row {
   public:
      class iterator {
      public:
         iterator(row& _row, unsigned int _index = 0) :
            m_row(_row) {
            m_iter = std::begin(m_row.m_table.c);
            std::advance(m_iter, m_row.m_index * m_row.m_table.m_cols + _index);
         }
         
         iterator(const iterator& iter) :
            m_row(iter.m_row),
            m_iter(iter.m_iter) {}
         
         ~iterator() {}

         iterator& operator=(const iterator& iter) {
            m_iter = iter.m_iter;
            return *this;
         }
        
         bool operator==(const iterator& iter) const {
            return (m_iter == iter.m_iter);
         }
        
         bool operator!=(const iterator& iter) const {
            return (m_iter != iter.m_iter);
         }
         
         iterator& operator++() {
            m_iter++;
            return *this;
         }
         
         value_type& operator*() {
            return *m_iter;
         }
        
      private:
         row& m_row;
         typename Container::iterator m_iter;
      };
      
      iterator begin() {
         return iterator(*this);
      }
      
      iterator end() {
         return iterator(*this,m_table.m_cols);
      }
      
      row(table<T>& table, unsigned int index) :
         m_table(table),
         m_index(index) {}
  
   private:
      table<T>& m_table;
      unsigned int m_index;
   };

   class column {
   public:
      class iterator {
      public:
         iterator(column& _col, unsigned int _index = 0) :
            m_col(_col) {
            m_iter = std::begin(m_col.m_table.c);
            std::advance(m_iter, m_col.m_index + m_col.m_table.m_cols * _index);
         }
         
         iterator(const iterator& _iter) :
            m_col(_iter.m_col),
            m_iter(_iter.m_iter) {}
         
         ~iterator() {}

         iterator& operator=(const iterator& _iter) {
            m_iter = _iter.m_iter;
            return *this;
         }
        
         bool operator==(const iterator& _iter) const {
            return (m_iter == _iter.m_iter);
         }
        
         bool operator!=(const iterator& _iter) const {
            return (m_iter != _iter.m_iter);
         }
         
         iterator& operator++() {
            std::advance(m_iter, m_col.m_table.m_cols);
            return *this;
         }
         
         value_type& operator*() {
            return *m_iter;
         }
        
      private:
         column& m_col;
         typename Container::iterator m_iter;
      };
      
      iterator begin() {
         return iterator(*this);
      }
      
      iterator end() {
         return iterator(*this,m_table.m_rows);
      }
      
      column(table<T>& table, unsigned int index) :
         m_table(table),
         m_index(index) {} 
      
   private:
      table<T>& m_table;
      unsigned int m_index;
   };
  
private:
   unsigned int m_rows;
   unsigned int m_cols;
   
   Container c;
};
#endif
