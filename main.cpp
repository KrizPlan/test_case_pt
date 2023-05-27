#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <mutex>
#include <iomanip>

#include "Event.h"

/// @brief check number is primal
/// @param number nimber to check
/// @return true if number is prime or false if number is not prime
bool numberIsPrime(uint number){
    // set variable to true as default and change value if find divider
    bool is_prime = true;
    for(size_t i = 2; i < number; i++){
        if(number % i == 0){
            is_prime = false;
            break;
        }
    }
    return is_prime;
}


int main(){
    Event evn;

    

    
    std::cout<<evn.get_string_values()<<std::endl;
}