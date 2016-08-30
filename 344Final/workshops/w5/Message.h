#pragma once
#include <iostream>
#include <fstream>

namespace w5{
class Message{
    std::string user;
    std::string reply;
    std::string tweet;
    
    
public:
Message();
Message(std::ifstream& in, char c);
bool empty() const;
void display(std::ostream& os) const;
};
}//w5