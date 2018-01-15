#include "table.h"

#include <vector>
#include <iostream>

int main(int argc, char* args[]) {
   //table<double, std::vector<double> > my_table(3,4);
   std::table<double> my_table(4,3, {
      1,2,3,
      4,5,6,
      7,8,9,
      10,11,12,
   });

   /*
   table<double>::column myColumn(my_table, 2);
   for(double f : myColumn) {
      std::cout << f << ", ";
   }
   std::cout << std::endl;
   */
   
   //my_table.insert_column(column_iterator, {4,7,10,13});
   std::table<double>::row_iterator itRow = my_table.rows().begin();
   ++itRow; ++itRow; ++itRow;
   my_table.insert(itRow, {13,14,15});
   
   for(std::table<double>::row myRow : my_table.rows()) {
      for(double f : myRow) {
         std::cout << f << ", ";
      }
      std::cout << std::endl;
   }
   /*
   for(table<double>::row_iterator itRow = my_table.rows().begin();
       itRow != my_table.rows().end();
       ++itRow) {
      for(double f : *itRow) {
         std::cout << f << ", ";
      }
      std::cout << std::endl;
   }  
   */
   return 0;
}


  
