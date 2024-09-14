#include "my_swap.h"

template <typename T>
class unique_ptr{
private:
    T* ptr;
    size_t* counter;
public:
    unique_ptr():ptr(nullptr),counter(nullptr){};
    explicit unique_ptr(T* ptr):ptr(ptr), counter(new int(1)){};

    unique_ptr(const unique_ptr<T>& un_ptr){
        if(!un_ptr.ptr){
            ptr = nullptr;
            counter = nullptr;
            return;
        }
        ptr = new T(un_ptr->ptr);
        counter  = new int(1); 
    }
    unique_ptr(unique_ptr<T>&& un_ptr ):ptr(un_ptr.ptr),counter(un_ptr.counter){
        un_ptr.ptr = nullptr;
        un_ptr.counter = nullptr;
    }


    T* get(){
        return ptr;
    }
    size_t use_count(){
        if(!counter) return 0;
        return *counter;
    }
    bool is_free(){
        return ptr == nullptr;
    }


    T& operator*(){
        return *get();
    }
    T* operator->(){
        return get();
    }
    T& operator[](int index){
        //index checking
        return ptr[index];
    }
    

    unique_ptr& operator=(const unique_ptr<T>& un_ptr){
        delete ptr;
        if(!counter) counter = new int(0);
        if(!un_ptr.ptr){
            if(!counter) counter = new int(0);
            *counter = 1;
            ptr = new T(un_ptr->ptr);
            return *this;
        }
        ptr = un_ptr.ptr;

        return *this;
    }
};