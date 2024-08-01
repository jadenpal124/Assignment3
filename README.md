Steps to run seed file.

1. "make clean" - this will remove all object files and .dat files

2. "g++ seed.cpp User.cpp Product.cpp Release.cpp changeRequest.cpp changeItem.cpp -o seed -std=c++11 && ./seed" - this will run the .seed files and make .dat files

3. "make" - this will compile and link all the modules

4. ./program - run the program

5. program should loadup with existing items in .dat files.

NOTE: There are still debug outputs in code that still need to be deleted. 
