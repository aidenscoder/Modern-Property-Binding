#pragma once
#include <functional>
#include "concepts.h"
#include <exception>
#include <string>

class ReadonlyError : std::exception {
    std::string msg;
public:
    ReadonlyError(std::string msg): msg(msg) {}
    const char* what() const noexcept {
        return msg.c_str();
    }
};

class RefrenceError : std::exception {
    std::string msg;
public:
    RefrenceError(std::string msg): msg(msg) {}
    const char* what() const noexcept {
        return msg.c_str();
    }
};


template<typename T, typename I = int, typename R = int>
class Property {
    std::function<T()> get;
    std::function<void(T)> set;
    std::function<T*()> ref;
public:
    Property(
        std::function<T()> get,
        std::function<void(T)> set = [](auto value){
            throw ReadonlyError("Cannot change a readonly property.");
        },
        std::function<T*()> ref = [](){
            throw RefrenceError("Cannot refrence a non refrence property.");
        }
    ): get(get), set(set), ref(ref) {}

    Property(const Property&) = delete;
    Property& operator=(const Property&) = delete;
    T& MutableRef(){ return ref(); }
    operator T() const { return get(); }

    //Standard
    #pragma region

    T operator+(const T& value) const requires Prop::Std::Add<T> { return value + get(); }
    T operator-(const T& value) const requires Prop::Std::Sub<T> { return value - get(); }
    T operator*(const T& value) const requires Prop::Std::Mult<T> { return value * get(); }
    T operator/(const T& value) const requires Prop::Std::Div<T> { return value / get(); }
    T operator-() const requires Prop::Std::Neg<T> { return -get(); }
    R operator[](const I& value) requires Prop::Std::Index<T,I,R> { return get()[value]; }
        // Assigment
        #pragma region

            void operator=(const T& value) requires AssignProp::Std::Assign<T> { set(value); }
            Property& operator+=(const T& value) requires AssignProp::Std::Add<T> { 
                set(value + get()); 
                return *this;
            }
            Property& operator-=(const T& value) requires AssignProp::Std::Sub<T> { 
                set(value - get()); 
                return *this;
            }
            Property& operator*=(const T& value) requires AssignProp::Std::Mult<T> { 
                set(value * get()); 
                return *this;
            }
            Property& operator/=(const T& value) requires AssignProp::Std::Div<T> {
                set(value / get());
                return *this;
            }
            void operator++() requires Prop::Std::Incr<T> {
                set(get()+1);
            }
            void operator--() requires Prop::Std::Decr<T> {
                set(get()-1);
            }
            void operator++(int) requires Prop::Std::Incr<T> {
                set(get()+1);
            }
            void operator--(int) requires Prop::Std::Decr<T> {
                set(get()-1);
            }

        #pragma endregion
        // Assignment

    #pragma endregion
    //Standard

    //Bitwise
    #pragma region

    T operator<<(const T& value) const requires Prop::Bitwise::LeftShift<T> { return value << get(); }
    T operator>>(const T& value) const requires Prop::Bitwise::RightShift<T> { return value >> get(); }
    T operator^(const T& value) const requires Prop::Bitwise::Xor<T> { return value ^ get(); }
    T operator&(const T& value) const requires Prop::Bitwise::And<T> { return value & get(); }
    T operator~() requires Prop::Bitwise::Not<T> { return ~get(); }
        // Assigment
        #pragma region

            Property& operator<<=(const T& value) requires AssignProp::Bitwise::LeftShift<T> { 
                set(value << get()); 
                return *this;
            }
            Property& operator>>=(const T& value) requires AssignProp::Bitwise::RightShift<T> { 
                set(value >> get()); 
                return *this;
            }
            Property& operator^=(const T& value) requires AssignProp::Bitwise::Xor<T> { 
                set(value ^ get()); 
                return *this;
            }
            Property& operator&=(const T& value) requires AssignProp::Bitwise::And<T> {
                set(value & get());
                return *this;
            }

        #pragma endregion
        // Assignment

    #pragma endregion
    //Bitwise

    //Comparisons
    #pragma region

    bool operator==(const T& value) const requires Prop::Comparisons::EqualTo<T> { return value == get(); }
    bool operator!=(const T& value) const requires Prop::Comparisons::NotEqualTo<T> { return value != get(); }
    bool operator<=(const T& value) const requires Prop::Comparisons::GreaterOrEqual<T> { return get() >= value; }
    bool operator>=(const T& value) const requires Prop::Comparisons::LessThanOrEqual<T> { return get() <= value; }
    bool operator>(const T& value) const requires Prop::Comparisons::LessThan<T> { return get() < value; }
    bool operator<(const T& value) const requires Prop::Comparisons::GreaterThan<T> { return get() > value; }

    #pragma endregion
    //Comparisons

};