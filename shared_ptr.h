#pragma once

#include "my_swap.h"


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
    explicit shared_ptr(T* in_ptr) : ptr(in_ptr) , counter(new size_t(1)){
        //std::cout<<"Constructor called for value ( "<<*in_ptr<<" ) current count :"<<use_count()<<std::endl;
    };
    
    shared_ptr(const shared_ptr<T>& sh_ptr ){
        //std::cout<<"Copy Constructor called for value ( "<<*sh_ptr<<" ) current count :"<<sh_ptr.use_count()<<std::endl;
        ptr = sh_ptr.ptr;
        counter = sh_ptr.counter;
        if( !is_free() ) ++*counter; 
    }
    shared_ptr(shared_ptr<T>&& sh_ptr ):ptr(sh_ptr.ptr),counter(sh_ptr.counter){
        //std::cout<<"Move Constructor called for value ( "<<*sh_ptr<<" ) current count :"<<sh_ptr.use_count()<<std::endl;
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
    bool is_unique(){
        return use_count() == 1;
    }
    bool is_free(){
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
        //index checking
        return ptr[index];
    }
    const T& operator[](int index) const {
        return ptr[index];
    }

    shared_ptr& operator=(const shared_ptr<T>& sh_ptr){\
        //std::cout<<"Assignment operator called"<<std::endl;
        if(ptr==sh_ptr.ptr) return *this;
        shared_ptr<T> temp_ptr (sh_ptr);
        swap(temp_ptr); 
        return *this;
    }
    shared_ptr& operator=(shared_ptr<T>&& sh_ptr){
        //std::cout<<"Move Assignment operator called"<<std::endl;
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
        //std::cout<<"Destructor called for value ( "<<*ptr<<" ) current count :"<<*counter<<std::endl;
        if( is_unique() ){
            //std::cout<<"Final destructor called for value ( "<<*ptr<<" )"<<std::endl;
            delete ptr;
            delete counter;
        }
        --*counter;
    }
};

template<typename T,typename... Args>
shared_ptr<T> make_shared(Args&& ... args){
    //void* p = new char[aligof(T)+sizeof(size_t)]; 
    return shared_ptr<T>(new T(args...));
}
