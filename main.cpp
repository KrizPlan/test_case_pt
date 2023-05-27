#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <mutex>
#include <iomanip>
#include <signal.h>
#include <queue>
#include <list>
#include <vector>

#include "Event.h"

static volatile bool running = true;

std::mutex mutex_for_event_queue;

std::mutex mutex_for_finded_prime_numbers_list;


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
    
    std::queue<Event> event_queue;
    std::list<uint> finded_prime_numbers_list;

    uint number_of_generation_threads;
    uint number_of_generations_in_each_thread;
    uint number_of_handler_threads;

    std::cout<<"Enter number of generation threads"<<std::endl;
    std::cin>>number_of_generation_threads;

    std::cout<<"Enter number of generations in each thread"<<std::endl;
    std::cin>>number_of_generations_in_each_thread;

    std::cout<<"Enter number of handler threads"<<std::endl;
    std::cin>>number_of_handler_threads;


    std::vector<std::thread> generation_threads_vector;
    std::vector<std::thread> handler_threads_vector;

    // create vector of generation threads
    for(size_t i = 0; i < number_of_generation_threads; i++){
        // push lambda function
        generation_threads_vector.push_back(std::thread([&event_queue](const uint number_of_generations){
                for(size_t i = 0; i < number_of_generations && running; i++){
                // if push in full vector then throw exception
                try
                {
                    mutex_for_event_queue.lock();
                    event_queue.push(Event());
                    mutex_for_event_queue.unlock();
                }
                catch(const std::exception& e)
                {
                    mutex_for_event_queue.unlock();
                    std::cerr << e.what() << '\n';
                }
            } // for in labda function
            }, // lambda
            number_of_generations_in_each_thread) // param in lambda function
        ); // push_back
    } // main for

    // create vector of handler threads
    for(size_t i = 0; i < number_of_handler_threads; i++){
        // push lambda function
        handler_threads_vector.push_back(
            std::thread([&event_queue, &finded_prime_numbers_list](){
            Event event_to_handle;
            while(running){
                // check queue is empty and if yes wait 100 ms and check again
                mutex_for_event_queue.lock();
                if(event_queue.size() == 0){
                    mutex_for_event_queue.unlock();
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));

                    mutex_for_event_queue.lock();
                    if(event_queue.size() == 0){
                        mutex_for_event_queue.unlock();
                        break;
                    }
                    else{
                        event_to_handle = event_queue.front();
                        event_queue.pop();
                        mutex_for_event_queue.unlock();
                    }
                }
                else{
                    event_to_handle = event_queue.front();
                    event_queue.pop();
                    mutex_for_event_queue.unlock();
                }

                // check received event number is prime and if yes then add number in list
                if(numberIsPrime(event_to_handle.get_number())){
                    // if list is full then throw exception
                    try
                    {
                        mutex_for_finded_prime_numbers_list.lock();
                        finded_prime_numbers_list.push_back(event_to_handle.get_number());
                        mutex_for_finded_prime_numbers_list.unlock();
                    }
                    catch(const std::exception& e)
                    {
                        mutex_for_finded_prime_numbers_list.unlock();
                        std::cerr << e.what() << '\n';
                    }
                }
            }; // while
        }) // thread
        ); // push_back
    } // main for


    // join all generation threads
    for(size_t i = 0; i < generation_threads_vector.size(); i++){
        generation_threads_vector[i].join();
    }

    // join all handler threads
    for(size_t i = 0; i < handler_threads_vector.size(); i++){
        handler_threads_vector[i].join();
    }

    // Print all prime numbers
    std::cout<<"Finded prime numbers: "<<std::endl;
    for(auto prime_number : finded_prime_numbers_list){
        std::cout<<prime_number<<" ";
    }
    std::cout<<std::endl;

}