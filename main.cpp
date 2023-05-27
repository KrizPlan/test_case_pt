#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <mutex>
#include <iomanip>
#include <signal.h>

#include "Event.h"

static volatile bool running = true;


/// @brief Handler for SIGINT to stop program
/// @param signal received signal
void SIGINTHandler(int signal){
    running = false;
}


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
    srand((unsigned)time(NULL));
    signal(SIGINT, SIGINTHandler);
    Event evn;
    
    std::cout<<evn.get_string_values()<<std::endl;
}