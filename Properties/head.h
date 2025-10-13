#pragma once
#include <functional>
#include "restrictions.h"
#include <exception>
#include <string>

#define get_p [this]() -> auto
#define set_p [this](auto value)
#define ref_p [this]() -> auto*

#define readonly [](auto v){ throw ReadonlyError("Cannot change a readonly property."); }
#define nullref [](){ return nullptr; }

class ReadonlyError : std::exception {
    std::string msg;
protected:
    ReadonlyError(std::string msg): msg(msg) {}
    const char* what() const noexcept {
        return msg.c_str();
    }
};

/// @brief A property wrapper designed for meta programming, and insertion of assignment.
/// @brief Supports get, set and ref. set defaults to raising a ReadonlyError, and ref defaults to raising
/// @brief a RefrenceError.
/// @brief Requirements: c++20 standard. concepts.h file, head.h file.
/// @tparam T The type the class.
/// @tparam I The index type for the [] overload.
/// @tparam R The return type for the [] overload.
/// @note The refrence accessor uses a pointer to interact with access. Although it defaults to an error, 
/// @note it can be defaulted to the underlying type, by using new T(args) in the ref by not exposing internal state.
template<typename T, typename I = int, typename R = int>
class property {
private:
    std::function<T()> get;
    std::function<void(T)> set;
    std::function<T*()> ref;
public:
    property(
        std::function<T()> get,
        std::function<void(T)> set,
        std::function<T*()> ref
    ): get(get), set(set), ref(ref) {}

    property(const property&) = delete;
    T operator=(const property&) {return get(); }
    T* operator->(){ return ref(); }
    T* operator*(){ return *ref(); }
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

            property& operator=(const T& value) requires AssignProp::Std::Assign<T> { 
                set(value); 
                return *this;
            }
            property& operator+=(const T& value) requires AssignProp::Std::Add<T> { 
                set(value + get()); 
                return *this;
            }
            property& operator-=(const T& value) requires AssignProp::Std::Sub<T> { 
                set(value - get()); 
                return *this;
            }
            property& operator*=(const T& value) requires AssignProp::Std::Mult<T> { 
                set(value * get()); 
                return *this;
            }
            property& operator/=(const T& value) requires AssignProp::Std::Div<T> {
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

            property& operator<<=(const T& value) requires AssignProp::Bitwise::LeftShift<T> { 
                set(value << get()); 
                return *this;
            }
            property& operator>>=(const T& value) requires AssignProp::Bitwise::RightShift<T> { 
                set(value >> get()); 
                return *this;
            }
            property& operator^=(const T& value) requires AssignProp::Bitwise::Xor<T> { 
                set(value ^ get()); 
                return *this;
            }
            property& operator&=(const T& value) requires AssignProp::Bitwise::And<T> {
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

    static void bind_properties(property<T,I,R> orig_prop, property<T,I,R> prop_to_bind){
        prop_to_bind.get = [&]{ return orig_prop.get(); };
        prop_to_bind.set = [&](auto value){ return orig_prop.set(value); };
        prop_to_bind.ref = [&](){ return prop_to_bind.ref(); };
    }
};