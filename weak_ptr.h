#pragma once

#include "my_swap.h"
#include "my_move.h"
#include "shared_ptr.h"

template <typename T>
class weak_ptr{
private:
    struct ControlBlock{
        size_t ref_count;
        size_t weak_count;
    }
    T* ptr;
    ControlBlock* counter;

    //зафрендить с shared_ptr
public:
    weak_ptr():ptr(nullptr),counter(nullptr){}
    weak_ptr(const shared_ptr& sh_ptr):ptr(sh_ptr.ptr),counter(sh_ptr.counter){
        if(!counter) ++counter->weak_count;
    }
    weak_ptr(const weak_ptr& w_ptr):ptr(w_ptr.ptr),counter(w_ptr.counter){
        if(!counter) ++counter->weak_count;
    }
    weak_ptr(weak_ptr&& w_ptr):ptr(w_ptr.ptr),counter(w_ptr.counter){
        w_ptr.ptr = nullptr;
        w_ptr.counter = nullptr;
    }

    bool is_expired(){
        return counter->ref_count == 0;
    }
    int use_count(){
        if(!counter) return 0 ;
        return counter->weak_count;
    }
    shared_ptr<T> lock(){
        return shared_ptr;
    }


}