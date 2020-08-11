#pragma once

#include <array>
#include <vector>
#include <string>

#define s_auto static constexpr auto
#define s_const static constexpr

template <typename U, typename ...T>
constexpr auto make_array(U first, T... args){
  constexpr size_t size = sizeof...(args);
  return std::array<U, size+1>{first, args...};
}

template <typename U, typename ...T>
constexpr auto make_2d_array(U first, T... args){
  return make_array(make_array(first, args...));
}

typedef std::vector<std::pair<std::string,std::string>> token;
typedef std::vector<std::pair<std::string,token>> operation;