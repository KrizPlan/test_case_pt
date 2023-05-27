#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <mutex>

/// @brief check number is primal
/// @param number nimber to check
/// @return true if number is prime or false if number is not prime
bool number_is_prime(uint number){
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
    uint number;
    do
    {
        std::cin>>number;
        std::cout<<"Result: "<<number_is_prime(number)<<std::endl;
    } while (number != 0);
    
    std::cout<<"Hello world!"<<std::endl;
}