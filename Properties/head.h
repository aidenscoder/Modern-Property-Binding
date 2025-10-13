#pragma once
#include <functional>
#include "restrictions.h"
#include <exception>
#include <string>

#define get_p [this]() -> auto
#define set_p [this](auto value)
#define ref_p [this]() -> auto*
#define property _Property

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
class _Property {
private:
    std::function<T()> get;
    std::function<void(T)> set;
    std::function<T*()> ref;
public:
    _Property(
        std::function<T()> get,
        std::function<void(T)> set = [](auto value){
            throw ReadonlyError("Cannot change a readonly property.");
        },
        std::function<T*()> ref = [](){ return nullptr; }
    ): get(get), set(set), ref(ref) {}

    _Property(const _Property&) = delete;
    T operator=(const _Property&) {return get(); }
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

            _Property& operator=(const T& value) requires AssignProp::Std::Assign<T> { 
                set(value); 
                return *this;
            }
            _Property& operator+=(const T& value) requires AssignProp::Std::Add<T> { 
                set(value + get()); 
                return *this;
            }
            _Property& operator-=(const T& value) requires AssignProp::Std::Sub<T> { 
                set(value - get()); 
                return *this;
            }
            _Property& operator*=(const T& value) requires AssignProp::Std::Mult<T> { 
                set(value * get()); 
                return *this;
            }
            _Property& operator/=(const T& value) requires AssignProp::Std::Div<T> {
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

            _Property& operator<<=(const T& value) requires AssignProp::Bitwise::LeftShift<T> { 
                set(value << get()); 
                return *this;
            }
            _Property& operator>>=(const T& value) requires AssignProp::Bitwise::RightShift<T> { 
                set(value >> get()); 
                return *this;
            }
            _Property& operator^=(const T& value) requires AssignProp::Bitwise::Xor<T> { 
                set(value ^ get()); 
                return *this;
            }
            _Property& operator&=(const T& value) requires AssignProp::Bitwise::And<T> {
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

    static void bind_properties(_Property<T,I,R> orig_prop, _Property<T,I,R> prop_to_bind){
        prop_to_bind.get = [&]{ return orig_prop.get(); };
        prop_to_bind.set = [&](auto value){ return orig_prop.set(value); };
        prop_to_bind.ref = [&](){ return prop_to_bind.ref(); };
    }

    static constexpr int size = 96;
    static constexpr int fn = 3;
};