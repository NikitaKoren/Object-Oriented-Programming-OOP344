#include "Message.h"

namespace w5 {

    Message::Message() { }

    Message::Message(std::ifstream &in, char c)
    {

        char x;
        getline(in, user, ' ');


        if(in.peek() == '@') {
            x = in.get();
            getline(in, reply, ' ');
        }

        getline(in, tweet, c);

    }

    bool Message::empty() const
    {
        if (reply == "" && tweet == "") {
            return true;
        } else {
            return false;
        }
    }

    void Message::display(std::ostream &os) const
    {
        os << "Message" << std::endl;


        if(!user.empty()) {
            os << "  User: ";
            os << user << std::endl;


            if(reply != "") {
                os << "  Reply: ";
                os << reply << std::endl;
            }
            os << "  Tweet: ";
            os << tweet << std::endl;
        }
    }
//w5
}