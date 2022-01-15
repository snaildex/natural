#pragma once
#include <type_traits>
#define Entity(Type)\
Type ( const Type & ) = delete;\
const Type & operator=( const Type & ) = delete;
#define EnumFlags(Type)\
 constexpr Type operator| ( Type l, Type r) noexcept { return static_cast< Type >(static_cast<std::underlying_type_t< Type >>(l)|static_cast<std::underlying_type_t< Type >>(r));}\
 constexpr Type operator& ( Type l, Type r) noexcept { return static_cast< Type >(static_cast<std::underlying_type_t< Type >>(l)&static_cast<std::underlying_type_t< Type >>(r));}