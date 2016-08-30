// Created by Nikita Koren on 22/11/15.
#include "Utilities.h"


// declaring a static member variable
char Utilities::delimiter = '\0';

void Utilities::setDelimiter(const char c) {
    delimiter = c;
}

const char Utilities::getDelimiter() {
    return delimiter;
}


Utilities::Utilities(size_t minimum_field_width) {
    field_width = minimum_field_width;
}


void Utilities::setFieldWidth(size_t fw) {
    field_width = fw;
}


size_t Utilities::getFieldWidth() const {
    return field_width;
}

const std::string Utilities::nextToken(const std::string& str, size_t& next_pos, bool& more) {


    /* str string  has one record that has multiple tokens
     * token       is a data block until delimiter(|)
     * next_pos    is a position from where to start to read a token
     * more        stores indicator if we have more tokens
     * */

    std::string token = "";
    size_t size = str.size();

    //read one token (note: some records does not have delimiter)
    while(str[next_pos] != delimiter && next_pos != size ) {

        token+=str[next_pos];
        next_pos++;
    }

    /* trim token  */
    std::string whitespaces (" \t\r");

    // trim left part
    size_t c = token.find_first_not_of(whitespaces);
    token.erase(0, c);

    //trim right part
    c = token.find_last_not_of(whitespaces);
    token.erase(c+1);


    //check if there are more tokens
    if(next_pos != size) {
        more = true;
        next_pos+= 1; // skip delimiter
    }
    else
        more = false;

    if (field_width < token.size())
        field_width = token.size();

    return token;
}
