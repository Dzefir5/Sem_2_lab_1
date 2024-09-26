#pragma once

#include "my_swap.h"
#include "my_move.h"
#include <cstddef>



template<typename T>
class weak_ptr;

//реализовать Deleter или специализаицию для T[]
template<typename T>
class shared_ptr{
private:
    struct ControlBlock{
        size_t ref_count;
        size_t weak_count;
        ControlBlock(size_t ref =0 , size_t weak = 0):ref_count(ref),weak_count(weak){}
    };
    T* ptr; 
    ControlBlock* counter;
    friend class weak_ptr<T>;
public:
    void swap(shared_ptr<T>& sh_ptr){
        my_swap(ptr,sh_ptr.ptr);  
        my_swap(counter,sh_ptr.counter);
    }

    shared_ptr():ptr(nullptr),counter(nullptr){};
    explicit shared_ptr( const weak_ptr<T>& w_ptr ):ptr(w_ptr.ptr),counter(w_ptr.counter){
        if(counter) counter->ref_count++;
    }
    explicit shared_ptr(T* in_ptr) : ptr(my_move(in_ptr)) {
        if( !ptr ){
            counter = new ControlBlock(1,0);
        }else{
            counter = nullptr;
        }
    };
    
    shared_ptr(const shared_ptr<T>& sh_ptr ){
        ptr = sh_ptr.ptr;
        counter = sh_ptr.counter;
        if( !is_free() ) ++counter->ref_count;
    }
    shared_ptr(shared_ptr<T>&& sh_ptr ):ptr(sh_ptr.ptr),counter(sh_ptr.counter){
        sh_ptr.ptr = nullptr;
        sh_ptr.counter = nullptr;
    }

    T* get() const {
        return ptr;
    }
    size_t use_count() const {
        if(!counter) return 0;
        return counter->ref_count;
    }
    size_t weak_count() const {
        if(!counter) return 0;
        return counter->weak_count;
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


    T& operator*() const {
        return *get();
    }
    T* operator->() const {
        return get();
    }

    T& operator[](int index) const {
        return ptr[index];
    }
    shared_ptr& operator=(std::nullptr_t){
        if(!ptr) return *this;
        shared_ptr<T> temp_ptr ();
        swap(temp_ptr); 
        return *this;
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
    ~shared_ptr(){
        if(!counter) return;
        --counter->ref_count;
        if( !counter->ref_count ){
            if()
            delete ptr;
            if( !counter->weak_count ) delete counter ;
        }
        

    }
};

template<typename T,typename... Args>
shared_ptr<T> make_shared(Args&& ... args){
    return shared_ptr<T>(new T(args...));
}

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
bool operator==( std::nullptr_t,const shared_ptr<T> &sh_ptr )
{
    return sh_ptr.get()==nullptr;
}
template<typename T>
bool operator!=(const shared_ptr<T> &sh_ptr , std::nullptr_t )
{
    return !(sh_ptr == nullptr);
}
template<typename T>
bool operator!=( std::nullptr_t , const shared_ptr<T> &sh_ptr)
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

