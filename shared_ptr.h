#pragma once

#include "my_swap.h"
#include <cstddef>


template<typename T>
class shared_ptr{
private:
    T* ptr;
    size_t* counter;
public:
    void swap(shared_ptr<T>& sh_ptr){
        my_swap(ptr,sh_ptr.ptr);  //заменить на свои с std::move()
        my_swap(counter,sh_ptr.counter);
    }

    shared_ptr():ptr(nullptr),counter(nullptr){};
    explicit shared_ptr(T* in_ptr) : ptr(my_move(in_ptr)) {
        if( ptr!= nullptr ){
            counter = new size_t(1);
        }else{
            counter = nullptr;
        }
    };
    
    shared_ptr(const shared_ptr<T>& sh_ptr ){
        ptr = sh_ptr.ptr;
        counter = sh_ptr.counter;
        if( !is_free() ) ++*counter;
    }
    shared_ptr(shared_ptr<T>&& sh_ptr ):ptr(sh_ptr.ptr),counter(sh_ptr.counter){
        sh_ptr.ptr = nullptr;
        sh_ptr.counter = nullptr;
    }

    T* get(){
        return ptr;
    }
    const T* get() const {
        return ptr;
    }
    size_t use_count() const {
        if(!counter) return 0;
        return *counter;
    }
    bool is_unique() const {
        return use_count() == 1;
    }
    bool is_free() const {
        return ptr == nullptr;
    }
    void reset(T* new_ptr){
        if(ptr==new_ptr) return ;
        auto buf = shared_ptr<T>(new_ptr);
        swap(buf);
    }
    void reset(){
        auto buf = shared_ptr<T>();
        swap(buf);
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

    shared_ptr& operator=(const shared_ptr<T>& sh_ptr){
        if(ptr==sh_ptr.ptr) return *this;
        shared_ptr<T> temp_ptr (sh_ptr);
        swap(temp_ptr); 
        return *this;
    }
    shared_ptr& operator=(shared_ptr<T>&& sh_ptr){
        if(ptr==sh_ptr.ptr) return *this;
        swap(sh_ptr); 
        return *this;
    }

    bool operator==(const shared_ptr<T>& sh_ptr) const{
        return ptr == sh_ptr.ptr;
    }
    bool operator==(const T* in_ptr) const{
        return ptr == in_ptr;
    }
    bool operator!=(const T* in_ptr) const {
        return !( *this==in_ptr);
    }
    bool operator!=(const shared_ptr<T>& sh_ptr) const {
        return !( *this==sh_ptr);
    }

    ~shared_ptr(){
        if(!counter) return;
        if( is_unique() ){
            delete ptr;
            delete counter;
        }
        --*counter;
    }
};

template<typename T,typename... Args>
shared_ptr<T> make_shared(Args&& ... args){
    return shared_ptr<T>(new T(args...));
}

/*
template<typename T>
shared_ptr<T[]> make_shared(int n){
    return shared_ptr<T[]>(new T[n]);
}
*/








template<typename T>
bool operator==(const shared_ptr<T> &sh_ptr_a, const shared_ptr<T> &sh_ptr_b) 
{
    return sh_ptr_a.get() == sh_ptr_b.get();
}

template<typename T>
bool operator!=(const shared_ptr<T> &sh_ptr_a, const shared_ptr<T> &sh_ptr_b) 
{
    return !(sh_ptr_a == sh_ptr_b);
}
template<typename T>
bool operator==(const shared_ptr<T> &sh_ptr , std::nullptr_t )
{
    return sh_ptr.get()==nullptr;
}
template<typename T>
bool operator!=(const shared_ptr<T> &sh_ptr , std::nullptr_t )
{
    return !(sh_ptr == nullptr);
}
template<typename T>
bool operator==( std::nullptr_t , const shared_ptr<T> &sh_ptr )
{
    return sh_ptr.get()==nullptr;
}
template<typename T>
bool operator!=( std::nullptr_t ,const shared_ptr<T> &sh_ptr )
{
    return !(sh_ptr == nullptr);
}

template<typename T>
bool operator<(const shared_ptr<T> &sh_ptr_a, const shared_ptr<T> &sh_ptr_b) 
{
    return sh_ptr_a.get() < sh_ptr_b.get();
}
template<typename T>
bool operator>=(const shared_ptr<T> &sh_ptr_a, const shared_ptr<T> &sh_ptr_b) 
{
    return  !( sh_ptr_a < sh_ptr_b );
}
template<typename T>
bool operator>(const shared_ptr<T> &sh_ptr_a, const shared_ptr<T> &sh_ptr_b) 
{
    return sh_ptr_a.get() > sh_ptr_b.get();
}
template<typename T>
bool operator<=(const shared_ptr<T> &sh_ptr_a, const shared_ptr<T> &sh_ptr_b) 
{
    return  !( sh_ptr_a > sh_ptr_b );
}