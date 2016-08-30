#pragma once
#include <iostream>
#include "Message.h"
namespace w5{
class Notifications
{
    int saved;
    Message* msg[10];
public:
    Notifications();
    Notifications(const Notifications& src);
    Notifications& operator=(const Notifications& src);
    Notifications(Notifications&& src);
    Notifications& operator=(Notifications&& src);
    ~Notifications();
    void operator+=(const Message& msg);
    void display(std::ostream& os) const;
};
}//w5