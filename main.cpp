#include <iostream>
#include "shared_ptr.h"
#include "DynamicArray.h"
#include "DynamicArrayTest.h"
#include "SharedPtrTest.h"

int main(){
    
    test_move();
    test_swap();
    auto ptr1 = shared_ptr<int>(new int(10));
    auto ptr3 = ptr1;
    auto ptr4 = ptr1;
    ptr4 = shared_ptr<int>(new int(300));
    ptr4.reset();
    auto ptr2 = shared_ptr<int>(new int(20));
    std::cout<<"_____________________"<<std::endl;
    std::cout<<*ptr1<<"_"<<*ptr2<<std::endl;
    std::cout<<"_____________________"<<std::endl;
    ptr2 = ptr1;
    std::cout<<*ptr1<<"_"<<*ptr2<<std::endl;
    std::cout<<"+_____________________"<<std::endl;
    {
       auto ptr5 = make_shared<int>(50); 
    }
    std::cout<<"+_____________________"<<std::endl;
    Test_DynamicArray_Constructors();
    std::cout<<"1"<<std::endl;
    Test_DynamicArray_Set();
    std::cout<<"1"<<std::endl;
    Test_DynamicArray_CompareOperator();
    std::cout<<"1"<<std::endl;
    test_shared_ptr_main();
}