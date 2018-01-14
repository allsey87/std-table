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
   table(unsigned int _rows, unsigned int _cols) :
      m_rows(_rows),
      m_cols(_cols) {
      c.resize(_rows * _cols);
   }
   
   table(unsigned int _rows, unsigned int _cols, std::initializer_list<value_type> _values) :
      m_rows(_rows),
      m_cols(_cols) {
      c.assign(_values);
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
         
         iterator(const iterator& _iter) :
            m_row(_iter.m_row),
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
         return iterator(*this, m_table.m_cols);
      }

      bool operator==(const row& _row) const {
         return (m_index == _row.m_index);
      }
      
      bool operator!=(const row& _row) const {
         return (m_index != _row.m_index);
      }
      
      row(table<T, Container>& _table, unsigned int _index) :
         m_table(_table),
         m_index(_index) {}

      // hack
   public:
      table<T, Container>& m_table;
      unsigned int m_index;
   };

   class row_iterator {
   public:
      row_iterator(table<T, Container>& _table, unsigned int _index) :
         m_row(_table, _index) {}
      
      row_iterator(const row_iterator& _iter) :
         m_row(_iter.m_row) {}
      
      row_iterator& operator=(const row_iterator& _iter) {
         m_row = _iter.m_row;
         return *this;
      }
        
      bool operator==(const row_iterator& _iter) const {
         return (m_row == _iter.m_row);
      }
      
      bool operator!=(const row_iterator& _iter) const {
         return (m_row != _iter.m_row);
      }
         
      row_iterator& operator++() {
         m_row.m_index++;
         return *this;
      }
         
      row& operator*() {
         return m_row;
      }
      
   private:
      row m_row;
   };

   struct row_iterators {
      row_iterators(table<T, Container>& _table) :
         m_begin(_table, 0),
         m_end(_table, _table.m_rows) {}
         
      row_iterator begin() {
         return m_begin;
      }   
      row_iterator end() {
         return m_end;
      }
      row_iterator m_begin;
      row_iterator m_end;
   };
   
   auto rows() {
      return row_iterators(*this);  
   }

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
      table<T, Container>& m_table;
      unsigned int m_index;
   };
  
private:
   unsigned int m_rows;
   unsigned int m_cols;
   
   Container c;
};
#endif
