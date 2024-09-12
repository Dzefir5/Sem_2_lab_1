
template<typename T>
class shared_ptr{
private:
    T* ptr;
    size_t* counter;
public:
    explicit shared_ptr(T* ptr) : ptr(ptr) , counter(new int(1));
    
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


    ~shared_ptr(){
        if(!counter) return;
        --*counter;
        if(!*counter){
            delete ptr;
            delete counter;
        }
    }
};

template<typename T>
shared_ptr<T> shared_ptr<T>::make_shared(T* ptr){

}
template<typename T>
shared_ptr<T> shared_ptr<T>::make_shared(const T& value){

}
