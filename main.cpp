//#include <iostream>
#include "shared_ptr.h"
#include "DynamicArray.h"
#include "DynamicArrayTest.h"
#include "SharedPtrTest.h"
#include "UniquePtrTest.h"

#include <iostream>
//clang++ main.cpp  -Wall -Wextra -o main.exe
int main(){
    
    test_move();
    test_swap();
    //Test_DynamicArray_Constructors();
    //Test_DynamicArray_Set();
    //Test_DynamicArray_CompareOperator();
    test_shared_ptr_main();
    test_unique_ptr_main();
}