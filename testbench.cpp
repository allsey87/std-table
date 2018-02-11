#include "table.h"

#include <vector>
#include <list>
#include <algorithm>
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
   std::table<double>::row_iterator cRow = my_table.rows().begin();
   ++cRow; ++cRow;
   //my_table.insert(cRow, {13,14,15});

	// TODO need to move to having a row and a row_iterator implementation again
	// assign one row based on another in the same table
	*my_table.rows().begin() = *cRow;
   
   for(std::table<double>::row myRow : my_table.rows()) {
      for(double f : myRow) {
         std::cout << f << ", ";
      }
      std::cout << std::endl;
   }
	
	/*
	auto itRemove = std::remove_if(my_table.rows().begin(),
										    my_table.rows().end(),
											 [] (std::table<double>::row& c_row) {
		int total = 0;
		for(double f : c_row) {
         total += f;
      }
		return (total > 10);
	});
	*/
	//my_table.erase(itRemove, my_table.rows().end());

	
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


  
