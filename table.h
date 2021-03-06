#ifndef TABLE_H
#define TABLE_H

#include <list>
#include <exception>
#include <iterator>

namespace std {

   template <class T, class Container = list<T> >
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
      
      table(unsigned int _rows, unsigned int _cols, initializer_list<value_type> _values) :
         m_rows(_rows),
         m_cols(_cols) {
         c.assign(_values);
      }
      
      // Element-wise access
      typename Container::iterator begin() {
         return c.begin();      
      }
      
      typename Container::iterator end() {
         return c.end();
      }
      
      class row { 
      public:
         class iterator {
         public:
            iterator(row& _row, unsigned int _index = 0) :
               m_row(_row) {
               m_iter = m_row.m_table.c.begin();
               advance(m_iter, m_row.m_index * m_row.m_table.m_cols + _index);
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

			//row& operator=(row&& _row)	

			row& operator=(row& _row) {
				for(iterator it_src = _row.begin(), iterator it_dst = this->begin();
					 it_src != _row.end() && it_dst = this->end();
					 ++it_src, ++it_dst) {
					*it_dst = *it_src;
				}	 
				return *this;
         }

         bool operator==(const row& _row) const {
            return (m_index == _row.m_index);
         }
         
         bool operator!=(const row& _row) const {
            return (m_index != _row.m_index);
         }

         row& operator++() {
            m_index++;
            return *this;
         }
	
			/* dereferencing a row has no effect */
			row& operator*() {
            return *this;
         }
         
         row(table<T, Container>& _table, unsigned int _index) :
            m_table(_table),
            m_index(_index) {}

         // hack
      public:
         table<T, Container>& m_table;
         unsigned int m_index;
      };

      void insert(row _position, initializer_list<value_type> _values) {
         if(_values.size() > m_cols) {
            throw bad_array_new_length();
         }
         m_rows++;
         typename Container::iterator iter = c.begin(); 
         advance(iter, _position.m_index * m_cols);
         c.insert(iter, _values);
         // todo return row_iterator
      }
      
      struct row_iterators {
         row_iterators(table<T, Container>& _table) :
            m_begin(_table, 0),
            m_end(_table, _table.m_rows) {}
            
         row begin() {
            return m_begin;
         }   
         row end() {
            return m_end;
         }
         row m_begin;
         row m_end;
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
               m_iter = m_col.m_table.c.begin();
               advance(m_iter, m_col.m_index + m_col.m_table.m_cols * _index);
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
               advance(m_iter, m_col.m_table.m_cols);
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
}
#endif
