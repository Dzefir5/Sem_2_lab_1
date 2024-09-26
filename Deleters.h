#pragma once

template<typename T>
struct My_Default_Deleter{
    void operator()(T* ptr){
        delete ptr;
    }
};

template<typename T>
struct My_Default_ArrayDeleter{
    void operator()(T* ptr){
        delete[] ptr;
    }
};
template<typename T>
struct My_Default_ArrayDeleter<T[]>{
    void operator()(T* ptr){
        delete[] ptr;
    }
};

