#pragma once

#include "my_swap.h"
#include <cstddef>

template <typename T,class Deleter =  My_Default_Deleter<T>>
class unique_ptr{
private:
    T* ptr;
    Deleter my_delete = Deleter() ;
public:
    //inline
    void swap(unique_ptr<T,Deleter>& un_ptr){
        my_swap(ptr,un_ptr.ptr); 
    }
    unique_ptr():ptr(nullptr){};
    explicit unique_ptr(std::nullptr_t):unique_ptr(){};
    explicit unique_ptr(T* in_ptr):ptr(my_move(in_ptr)){};
    
    unique_ptr(const unique_ptr<T,Deleter>& un_ptr) = delete;

    unique_ptr(unique_ptr<T,Deleter>&& un_ptr ):ptr(un_ptr.ptr){
        un_ptr.ptr = nullptr;
    }
    bool is_free() const {
        return ptr == nullptr;
    }
    void reset(T* new_ptr){ //убрать
        if(ptr==new_ptr) return ;
        auto buf = unique_ptr<T,Deleter>(new_ptr);
        swap(buf);
    }
    void reset(){
        auto buf =  unique_ptr<T,Deleter>();
        swap(buf);
    }
    T* release(){
        T* buf = ptr;
        ptr = nullptr;
        return buf;
    }
    T* get() const {
        return ptr;
    }
    T& operator*() const {
        return *ptr;
    }
    T* operator->() const {
        return ptr;
    }
    T& operator[](int index) const {
        return ptr[index];
    }
    unique_ptr& operator=(const unique_ptr<T,Deleter>& un_ptr)=delete;
    unique_ptr& operator=(std::nullptr_t){
        unique_ptr<T,Deleter> temp_ptr();
        swap(temp_ptr); 
        return *this;
    }
    unique_ptr& operator=(unique_ptr<T,Deleter>&& un_ptr){
        unique_ptr<T,Deleter> temp_ptr(un_ptr);
        swap(temp_ptr); 
        return *this;
    }
    virtual ~unique_ptr(){
        my_delete(ptr);
    }
};



template<typename T,class Deleter =  My_Default_Deleter<T>,typename... Args>
unique_ptr<T,Deleter> make_unique(Args&& ... args){
    return unique_ptr<T,Deleter>(new T(args...));
}




template<typename T,class Deleter =  My_Default_Deleter<T>>
bool operator==(const unique_ptr<T,Deleter> &un_ptr_a, const unique_ptr<T,Deleter> &un_ptr_b) 
{
    return un_ptr_a.get() == un_ptr_b.get();
}

template<typename T,class Deleter =  My_Default_Deleter<T>>
bool operator!=(const unique_ptr<T,Deleter> &un_ptr_a, const unique_ptr<T,Deleter> &un_ptr_b) 
{
    return !(un_ptr_a == un_ptr_b);
}
template<typename T,class Deleter =  My_Default_Deleter<T>>
bool operator==(const unique_ptr<T,Deleter> &un_ptr , std::nullptr_t )
{
    return un_ptr.get()==nullptr;
}
template<typename T,class Deleter =  My_Default_Deleter<T>>
bool operator==( std::nullptr_t , const unique_ptr<T,Deleter> &un_ptr  )
{
    return un_ptr.get()==nullptr;
}
template<typename T,class Deleter =  My_Default_Deleter<T>>
bool operator!=(const unique_ptr<T,Deleter> &un_ptr , std::nullptr_t )
{
    return !(un_ptr == nullptr);
}
template<typename T,class Deleter =  My_Default_Deleter<T>>
bool operator!=( std::nullptr_t ,  const unique_ptr<T,Deleter> &un_ptr)
{
    return !(un_ptr == nullptr);
}

