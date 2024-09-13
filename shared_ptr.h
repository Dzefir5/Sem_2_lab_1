#include "my_swap.h"


template<typename T>
class shared_ptr{
private:
    T* ptr;
    size_t* counter;
    void swap(shared_ptr<T>& sh_ptr){
        my_swap(ptr,sh_ptr.ptr);  //заменить на свои с std::move()
        my_swap(counter,sh_ptr.counter)
    }
public:
    shared_ptr():ptr(nullptr),counter(nullptr);
    explicit shared_ptr(T* ptr) : ptr(ptr) , counter(new int(1));
    
    shared_ptr(const shared_ptr<T>& sh_ptr ){
        ptr = sh_ptr.ptr;
        counter = sh_ptr.counter;
        if( is_free() ) ++*counter; 
    }
    shared_ptr(shared_ptr<T>&& sh_ptr ):ptr(sh_ptr.ptr),counter(sh_ptr.counter){
        sh_ptr.ptr = nullptr;
        sh_ptr.counter = nullptr;
    }

    T* get(){
        return ptr;
    }
    size_t use_count(){
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
    const T& operator[](int index) const {

    }

    shared_ptr& operator=(const shared_ptr<T>& sh_ptr){
        if(ptr==sh_ptr.ptr) return *this;
        shared_ptr<T> temp_ptr(sh_ptr);
        swap(temp_ptr); 

        /*
        if(ptr==sh_ptr.ptr) return *this;
        if(is_free()){
            ptr = sh_ptr.ptr;
            counter = sh_ptr.counter;
            ++*counter;
            return *this;
        }
        if( unique() ){
            delete ptr;
            delete counter;
            ptr = sh_ptr.ptr;
            counter = sh_ptr.counter;
            if(!ptr) ++*counter;
            return *this;
        }
        --*counter;
        ptr = sh_ptr.ptr;
        counter = sh_ptr.counter;
        ++*counter;
        */
        return *this;
    }
    shared_ptr& operator=(shared_ptr<T>&& sh_ptr){
        if(ptr==sh_ptr.ptr) return *this;
        if( is_unique() ){
            delete ptr;
            delete counter;
        }else{ --*counter;  }
        ptr = sh_ptr.ptr;
        counter = sh_ptr.counter;
        return *this;
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
    //void* p = new char[aligof(T)+sizeof(size_t)]; 
    return shared_ptr<T>(new T(args...));
}
