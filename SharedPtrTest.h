
#include <iostream>
#include "shared_ptr.h"
#include "my_swap.h"
#include "my_move.h"



void test_swap(){
    int a = 5;
    int b = 6;
    my_swap(a,b);
    std::cout<<a<<"_"<<b<<std::endl;

    std::string str1 = "abc";
    std::string str2 = "def";
    my_swap(str1,str2);
    std::cout<<"("<<str1<<")"<<std::endl;
    std::cout<<"("<<str2<<")"<<std::endl;

}
void test_move(){
    int a = 5;
    int b = 6;
    a = my_move(b);
    std::cout<<a<<std::endl;
    std::string str1 = "abc";
    std::string str2 = "def";
    str1 = my_move(str2);
    std::cout<<"("<<str1<<")"<<std::endl;
    std::cout<<"("<<str2<<")"<<std::endl;
}


