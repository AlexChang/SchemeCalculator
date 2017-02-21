#pragma once
#include <string>
#include <cstring>
#include <sstream>

template<typename T> std::string toString(const T& b){
	std::stringstream ss("");
	ss<<b;
	return ss.str();
}

template<typename T> T fromString(const std::string& s){
	std::stringstream ss(s);
	T x;
	ss>>x;
	return x;
}

