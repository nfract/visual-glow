//
// Created by Brandon on 5/21/2020.
//

#pragma once

#include <chrono>
#include <iostream>

#define SOFTX86_INF(x) std::cout << "softx86_inf: " << x << std::endl;
#define SOFTX86_ERR(x) std::cout << "softx86_err: " << x << std::endl;

static unsigned long long get_time_milliseconds() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}