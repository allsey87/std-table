#include "table.h"

#include <vector>
#include <iostream>

int main(int argc, char* args[]) {
   //table<double, std::vector<double> > my_table(3,4);
   table<double> my_table(4,3, {
      1,2,3,
      4,5,6,
      7,8,9,
      10,11,12,
   });
      
   table<double>::row myRow(my_table, 3);
   
   for(double f : myRow) {
      std::cout << f << ", ";
   }
   
   return 0;
}


  