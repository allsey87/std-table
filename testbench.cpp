#include "table.h"

#include <vector>
#include <iostream>

int main(int argc, char* args[]) {
   // test constructors, template parameters
   table<double> my_table(4,3);
   table<double, std::vector<double> > my_vec_table(3,4);

     
   for(double x : my_table) {
      std::cout << x;
   }
      
   //auto itRowBegin = my_table.row_begin();
   
   //table<double>::row_view my_row;
   
   // row and column iterators
   // for ranged-for to work my_table.rows() must return a struct or class with members begin() and end()
   
   /*
   for(table<double>::row_view tr : my_table.rows()) {
      tr[2] = 3;
   }
   
   for(const table<double>::column& tc : my_table.columns()) {
      for(double : tc) {
         std::cout << el << ", ";      
      }
      std::cout << std::endl;
   }
   */
   
   return 0;
}


