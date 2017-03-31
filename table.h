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
   
   /*
   struct row_view_range {
      row_view_iterator m_begin;
      row_view_iterator m_end;     
      auto begin() {
         return m_begin;
      };
      auto end() {
         return m_end;  
      };
   };
   */
   
   class row {
   public:
      class iterator {
      public:
         iterator(row& _row, unsigned int _index = 0) :
            m_row(_row),
            m_index(_index) {}
         
         iterator(const iterator& iter) :
            m_row(iter.m_row),
            m_index(iter.m_index) {}
         
         ~iterator() {}

         iterator& operator=(const iterator& iter) {
            m_index = iter.m_index;
         }
        
         bool operator==(const iterator& iter) const {
            return (m_index == iter.m_index);
         }
        
         bool operator!=(const iterator& iter) const {
            return (m_index != iter.m_index);
         }
         
         iterator& operator++() {
            ++m_index;
            return *this;
         }
         
         value_type& operator*() {
            typename Container::iterator it = std::begin(m_row.m_table.c);
            std::advance(it, m_row.m_table.m_cols * m_row.m_index + m_index);
            return *it;
         }
        
      private:
         row& m_row;
         unsigned int m_index;
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
      
      /* contents! */
      //bool operator==(const row&) const {}  
      
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
