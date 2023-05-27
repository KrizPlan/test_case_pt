#pragma once

#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

class Event{
private:
    std::chrono::_V2::system_clock::time_point generation_date;
    uint number;
public:
    Event();
    std::string get_string_values() const;
};