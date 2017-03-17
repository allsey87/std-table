#include "table.h"

#include <vector>

int main(int argc, char* args[]) {
   // test constructors, template parameters
   table<double> my_table(4,3);
   table<double, std::vector<double> > my_vec_table(3,4);

   // row and column iterators
   /*
   // for ranged-for to work my_table.rows() must return a struct or class with members begin() and end()
   for(const table<double>::row& tr : my_table.rows()) {
      for(auto el : tr) {
         std::cout << el << ", ";      
      }
      std::cout << std::endl;
   }
   
   for(const table<double>::column& tc : my_table.columns()) {
      for(auto el : tc) {
         std::cout << el << ", ";      
      }
      std::cout << std::endl;
   }
   */
   
   return 0;
}


