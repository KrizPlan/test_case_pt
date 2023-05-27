#include "Event.h"

Event::Event(){
    generation_date = std::chrono::system_clock::now();
    number = rand() % 1000000 + 1;
}

std::string Event::get_string_values() const{
    std::time_t time_t_generation_date = std::chrono::system_clock::to_time_t(generation_date);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t_generation_date), "%Y-%m-%d %X");
    return std::string("Number: " + std::to_string(number) + " date: " + ss.str());
}

uint Event::get_number() const{
    return number;
}