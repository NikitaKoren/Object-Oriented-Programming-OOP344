//Notifications.cpp
#include "Notifications.h"
namespace w5 {
Notifications::Notifications() //default constructor - empty
{
    saved = 0;
    for (int i = 0; i < 10; ++i)
        msg[i] = new Message();

}
Notifications::Notifications(const Notifications& src) //- copy constructor
{
    saved=src.saved;
    for (int i = 0; i<saved;i++)
        msg[i] = src.msg[i];
}
Notifications& Notifications::operator=(const Notifications& src)// - copy assignment operator
{
    if (this != &src)
    {
        saved = src.saved;
        for (int i = 0; i<saved;i++)
            msg[i] = src.msg[i];
    }
    return *this;
}
Notifications::Notifications(Notifications&& src)// - move constructor
{
        saved = src.saved;
        for (int i = 0; i < src.saved; i++)
        {
            msg[i] = src.msg[i];
        }
    
    for (int i = 0; i < src.saved; ++i)
    {
        delete src.msg[i];
        src.msg[i] = NULL;
    }
}
    
Notifications& Notifications::operator=(Notifications&& src)// - move assignment operator
{
    if (this != &src)
    {
        saved = src.saved;
        src.saved = 0;
        for (int i = 0; i<saved;i++)
        {
            msg[i] = src.msg[i];
        }
        
        for (int i = 0; i < saved; ++i)
        {
            delete src.msg[i];
            src.msg[i] = NULL;
        }
    }
    return *this;
}
    
Notifications::~Notifications()// - destructor
{
    if (saved > 0)
    {
        for (int i = 0; i < saved; ++i)
        {
            delete msg[i];
            msg[i] = NULL;
        }
    }
}
void Notifications::operator+=(const Message& msg)// - adds msg to the set
{
    if (saved < 10)
    {
        saved++;
        *this->msg[saved] = msg;
    }
}
    
void Notifications::display(std::ostream& os) const/* - inserts the Message objects
to the os output stream*/
{

    for (int i = 0; i<saved;i++)
        msg[i]->display(std::cout);
    
}
}//w5