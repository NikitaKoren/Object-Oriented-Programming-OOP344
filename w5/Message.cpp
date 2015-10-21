//Message.cpp
#include "Message.h"

namespace w5 {

    Message::Message() {
    }

    Message::Message(std::ifstream &in, char c) /*constructor retrieves a record from
the in file object, parses the record (as described above) and stores 
its components in the Message object. c is the character that delimits 
each record*/
    {
        if (!in.eof()) {
            user = "Message\n User : ";
            char x;
            x = in.get();
            while (x != ' ' && x != c && x != EOF) {
                user += x;
                x = in.get();
            }
            if (x == c)
                reply = "";
            else {
                x = in.get();
                if (x == '@') {
                    reply += "Reply : ";
                    while (x != ' ' && x != c && x != EOF) {
                        x = in.get();
                        reply += x;
                    }
                }
                tweet += "Tweet : ";
                while (x != c && x != EOF) {
                    tweet += x;
                    x = in.get();
                }

            }
        }
    }

    bool Message::empty() const// returns true if the object is in a safe empty state
    {
        if (reply == "" && tweet == "") {
            return true;
        } else {
            return false;
        }
    }

    void Message::display(std::ostream &os) const// displays the Message objects within the container
    {
        os << user << std::endl;
        os << reply << std::endl;
        os << tweet << std::endl;
    }
//w5
}