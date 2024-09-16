#pragma once

#include "my_swap.h"
#include <cstddef>

template <typename T>
class unique_ptr{
private:
    T* ptr;
public:
    void swap(unique_ptr<T>& un_ptr){
        my_swap(ptr,un_ptr.ptr); 
    }

    unique_ptr():ptr(nullptr){};
    explicit unique_ptr(T* in_ptr):ptr(my_move(in_ptr)){};

    unique_ptr(const unique_ptr<T>& un_ptr):unique_ptr(){
        if(!un_ptr.ptr) return;
        ptr = new T(*(un_ptr.ptr));
    }
    unique_ptr(unique_ptr<T>&& un_ptr ):ptr(un_ptr.ptr){
        un_ptr.ptr = nullptr;
    }


    T* get(){
        return ptr;
    }
    const T* get() const {
        return ptr;
    }
    bool is_free() const {
        return ptr == nullptr;
    }
    void reset(T* new_ptr){
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

    T& operator*(){
        return *get();
    }
    T* operator->(){
        return get();
    }
    const T& operator*() const {
        return *get();
    }
    const T* operator->() const {
        return get();
    }

    T& operator[](int index){
        return ptr[index];
    }
    const T& operator[](int index) const {
        return ptr[index];
    }

    unique_ptr& operator=(const unique_ptr<T>& un_ptr){
        //std::cout<<"Assignment operator called"<<std::endl;
        unique_ptr<T> temp_ptr (un_ptr);
        swap(temp_ptr); 
        return *this;
    }
    unique_ptr& operator=(unique_ptr<T>&& un_ptr){
        //std::cout<<"Move Assignment operator called"<<std::endl;
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
bool operator!=(const unique_ptr<T> &un_ptr , std::nullptr_t )
{
    return !(un_ptr == nullptr);
}
template<typename T>
bool operator==( std::nullptr_t , const unique_ptr<T> &un_ptr )
{
    return un_ptr.get()==nullptr;
}
template<typename T>
bool operator!=( std::nullptr_t ,const unique_ptr<T> &un_ptr )
{
    return !(un_ptr == nullptr);
}

template<typename T>
bool operator<(const unique_ptr<T> &un_ptr_a, const unique_ptr<T> &un_ptr_b) 
{
    return un_ptr_a.get() < un_ptr_b.get();
}
template<typename T>
bool operator>=(const unique_ptr<T> &un_ptr_a, const unique_ptr<T> &un_ptr_b) 
{
    return  !( un_ptr_a < un_ptr_b );
}
template<typename T>
bool operator>(const unique_ptr<T> &un_ptr_a, const unique_ptr<T> &un_ptr_b) 
{
    return un_ptr_a.get() > un_ptr_b.get();
}
template<typename T>
bool operator<=(const unique_ptr<T> &un_ptr_a, const unique_ptr<T> &un_ptr_b) 
{
    return  !( un_ptr_a > un_ptr_b );
}


// реализовать space-ship operator
// перегрузить вывод в поток

