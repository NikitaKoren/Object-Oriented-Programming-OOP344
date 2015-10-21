//Message.cpp
#include "Message.h"

namespace w5 {

    Message::Message() { } // returns true if the object is in a safe empty state

    Message::Message(std::ifstream &in, char c) {
        if (!in.eof()) {
            getline(in, user, ' ');

            if (in.peek() == '@') {
                in.get();
                getline(in, reply, ' ');
            }

            getline(in, tweet, c);
        }
    }

    bool Message::empty() const // returns true if the object is in a safe empty state
    {
        return reply == "" && tweet == "" ? true : false;
    }

    void Message::display(std::ostream &os) const // displays the Message objects within the container
    {
        if (!empty()) {
            os << "Message\n User : ";
            os << user << std::endl;

            if (reply != "") {
                os << "Reply : ";
                os << reply << std::endl;
            }
            os << "Tweet : ";
            os << tweet << std::endl;
        }
    }

}//w5