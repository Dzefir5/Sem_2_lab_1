#pragma once

#include "my_swap.h"
#include <cstddef>

template <typename T>
class unique_ptr{
private:
    T* ptr;
    T* get() const {
        return ptr;
    }
public:
    //inline
    void swap(unique_ptr<T>& un_ptr){
        my_swap(ptr,un_ptr.ptr); 
    }
    unique_ptr():ptr(nullptr){};
    explicit unique_ptr(std::nullptr_t):unique_ptr(){};
    explicit unique_ptr(T* in_ptr):ptr(my_move(in_ptr)){};
    
    unique_ptr(const unique_ptr<T>& un_ptr) = delete;

    unique_ptr(unique_ptr<T>&& un_ptr ):ptr(un_ptr.ptr){
        un_ptr.ptr = nullptr;
    }
    bool is_free() const {
        return ptr == nullptr;
    }
    void reset(T* new_ptr){ //убрать
        if(ptr==new_ptr) return ;
        auto buf = unique_ptr<T>(new_ptr);
        swap(buf);
    }
    void reset(){
        auto buf =  unique_ptr<T>();
        swap(buf);
    }
    T* release(){
        T* buf = ptr;
        ptr = nullptr;
        return buf;
    }
    
    //можно ли менять? подумать и записать
    T& operator*() const {
        return *ptr;
    }
    T* operator->() const {
        return ptr;
    }
    /*
    T& operator[](int index) const {
        return ptr[index];
    }
    */
    unique_ptr& operator=(const unique_ptr<T>& un_ptr)=delete;
    unique_ptr& operator=(std::nullptr_t);
    {
        unique_ptr<T> temp_ptr();
        swap(temp_ptr); 
        return *this;
    }
    unique_ptr& operator=(unique_ptr<T>&& un_ptr){
        swap(un_ptr); 
        return *this;
    }
    virtual ~unique_ptr(){
        delete ptr;
    }
};



template<typename T,typename... Args>
unique_ptr<T> make_unique(Args&& ... args){
    return unique_ptr<T>(new T(args...));
}




template<typename T>
bool operator==(const unique_ptr<T> &un_ptr_a, const unique_ptr<T> &un_ptr_b) 
{
    return un_ptr_a.get() == un_ptr_b.get();
}

template<typename T>
bool operator!=(const unique_ptr<T> &un_ptr_a, const unique_ptr<T> &un_ptr_b) 
{
    return !(un_ptr_a == un_ptr_b);
}
template<typename T>
bool operator==(const unique_ptr<T> &un_ptr , std::nullptr_t )
{
    return un_ptr.get()==nullptr;
}
template<typename T>
bool operator==( std::nullptr_t , const unique_ptr<T> &un_ptr  )
{
    return un_ptr.get()==nullptr;
}
template<typename T>
bool operator!=(const unique_ptr<T> &un_ptr , std::nullptr_t )
{
    return !(un_ptr == nullptr);
}
template<typename T>
bool operator!=( std::nullptr_t ,  const unique_ptr<T> &un_ptr)
{
    return !(un_ptr == nullptr);
}

