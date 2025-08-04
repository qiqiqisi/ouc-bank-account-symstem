//
// Created by Administrator on 2025/6/7.
//
#include "utils.h"
#include <iostream>
#include <sstream>
using namespace std;

template<typename T>
T Utils<T>::stringToOther(const string& s){
    istringstream ss(s);
    T d;
    ss >> d;
    return d;
}

// 显式实例化模板
template class Utils<int>;
template class Utils<double>;