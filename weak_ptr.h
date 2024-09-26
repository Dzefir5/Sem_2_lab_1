#pragma once

#include "shared_ptr.h"
#include "my_swap.h"
#include "my_move.h"

template <typename T>
class weak_ptr{
private:
    T* ptr;
    typename shared_ptr<T>::ControlBlock* counter;
public:
    void swap(weak_ptr<T>& w_ptr){
        my_swap(ptr,w_ptr.ptr);  
        my_swap(counter,w_ptr.counter);
    }
    weak_ptr():ptr(nullptr),counter(nullptr){}
    weak_ptr(std::nullptr_t):weak_ptr(){}
    weak_ptr(const shared_ptr<T>& sh_ptr):ptr(sh_ptr.ptr),counter(sh_ptr.counter){
        if(counter && ptr) counter->weak_count++;
    }
    weak_ptr(const weak_ptr<T>& w_ptr):ptr(w_ptr.ptr),counter(w_ptr.counter){
        if(counter && ptr) counter->weak_count++;
    }
    weak_ptr(weak_ptr<T>&& w_ptr):ptr(w_ptr.ptr),counter(w_ptr.counter){
        w_ptr.ptr = nullptr;
        w_ptr.counter = nullptr;
    }

    bool is_expired(){
        if(!counter) return true;
        return counter->ref_count == 0;
    }
    int use_count(){
        if(!counter) return 0 ;
        return counter->weak_count;
    }
    shared_ptr<T> lock(){
        return shared_ptr<T>(*this);
    }

    weak_ptr& operator=(const weak_ptr<T>& w_ptr){
        if(ptr==w_ptr.ptr) return *this;
        weak_ptr<T> temp_ptr (w_ptr);
        swap(temp_ptr); 
        return *this;
    }
    weak_ptr& operator=(weak_ptr<T>&& w_ptr){
        if(ptr==w_ptr.ptr) return *this;
        swap(w_ptr); 
        return *this;
    }
    weak_ptr& operator=(std::nullptr_t){
        if(!ptr) return *this;
        weak_ptr<T> temp_ptr ();
        swap(w_ptr); 
        return *this;
    }

    ~weak_ptr(){
        if(!counter) return ;
        counter->weak_count--;
        if(!counter->weak_count && !counter->ref_count){
            delete counter;
        }
    }

};
