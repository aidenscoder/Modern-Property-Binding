#pragma once

namespace Prop {
    
    namespace Std {
        template <typename T>
        concept Add = requires(T a, T b) {
            { a + b } -> std::convertible_to<T>;
        };

        template <typename T>
        concept Sub = requires(T a, T b) {
            { a - b } -> std::convertible_to<T>;
        };

        template <typename T>
        concept Neg = requires(T a) {
            { -a } -> std::convertible_to<T>;
        };

        template <typename T>
        concept Mult = requires(T a, T b) {
            { a * b } -> std::convertible_to<T>;
        };

        template <typename T>
        concept Div = requires(T a, T b) {
            { a / b } -> std::convertible_to<T>;
        };

        template <typename T>
        concept Incr = requires(T a) {
            { a++ } -> std::convertible_to<void>;
        };

        template <typename T>
        concept Decr = requires(T a) {
            { a-- } -> std::convertible_to<void>;
        };

        template <typename T, typename I, typename R>
        concept Index = requires(T a, I b) {
            { a[b] } -> std::convertible_to<R>;
        };

        template <typename T>
        concept Iterable = requires(T a){
            std::begin(a);
            std::end(a);
        };
    };
    
    namespace Bitwise {
        template <typename T>
        concept LeftShift = requires(T a, T b) {
            { a << b } -> std::convertible_to<T>;
        };

        template <typename T>
        concept RightShift = requires(T a, T b) {
            { a >> b } -> std::convertible_to<T>;
        };
        
        template <typename T>
        concept Xor = requires(T a, T b) {
            { a ^ b } -> std::convertible_to<T>;
        };

        template <typename T>
        concept And = requires(T a, T b) {
            { a & b } -> std::convertible_to<T>;
        };

        template <typename T>
        concept Not = requires(T a) {
            { ~a } -> std::convertible_to<T>;
        };

    };

    namespace Comparisons {
        template<typename T>
        concept EqualTo = requires(T a, T b){
            { a == b} -> std::convertible_to<bool>;
        };

        template<typename T>
        concept NotEqualTo = requires(T a, T b){
            { a != b} -> std::convertible_to<bool>;
        };

        template<typename T>
        concept GreaterThan = requires(T a, T b){
            { a > b} -> std::convertible_to<bool>;
        };

        template<typename T>
        concept LessThan = requires(T a, T b){
            { a < b} -> std::convertible_to<bool>;
        };

        template<typename T>
        concept GreaterOrEqual = requires(T a, T b){
            { a >= b} -> std::convertible_to<bool>;
        };

        template<typename T>
        concept LessThanOrEqual = requires(T a, T b){
            { a <= b} -> std::convertible_to<bool>;
        };

        template<typename T>
        concept And = requires(T a, T b){
            { a && b} -> std::convertible_to<bool>;
        };

        template<typename T>
        concept Or = requires(T a, T b){
            { a || b} -> std::convertible_to<bool>;
        };

    };

};

namespace AssignProp {
    
    namespace Std {
        template <typename T>
        concept Assign = requires(T a, T b){
            { a = b };
        };
        template <typename T>
        concept Add = requires(T a, T b) {
            { a += b };
        };

        template <typename T>
        concept Sub = requires(T a, T b) {
            { a -= b };
        };

        template <typename T>
        concept Mult = requires(T a, T b) {
            { a *= b };
        };

        template <typename T>
        concept Div = requires(T a, T b) {
            { a /= b };
        };
    };
    
    namespace Bitwise {
        template <typename T>
        concept LeftShift = requires(T a, T b) {
            { a <<= b };
        };

        template <typename T>
        concept RightShift = requires(T a, T b) {
            { a >>= b };
        };
        
        template <typename T>
        concept Xor = requires(T a, T b) {
            { a ^= b };
        };

        template <typename T>
        concept And = requires(T a, T b) {
            { a &= b };
        };
    };

};