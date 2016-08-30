#pragma once
// Milestone 1 - Utilities Interface
// Utilities.h
// Chris Szalwinski
// v1.0 - 24/10/2015
#include <string>
 
const unsigned int CODE_WIDTH = 5; // item code field width (later)
 
class Utilities 
{
    size_t field_width;
    static char delimiter;
 
public:
 
	/**
	 *	Upon instantiation, a Utilities object receives the minimum value of the field 
	 *	width to be used in displaying any token in a list of tokens.  The object’s 
	 *	constructor initializes the field_width instance variable to this minimum value.
	 */
    Utilities(size_t minimum_field_width = 1u);
 
    /**
     *	resets the field width to fw
     */
    void setFieldWidth(size_t fw);
 
    /**
     *	returns the field width
     */
    size_t getFieldWidth() const;
 
    /**
     *	receives a reference to string str, a reference to the position (next_pos) in 
     *	this string at which to start extracting the next token, and a reference to a 
     *	boolean flag (more).  This function returns the next token found and sets more 
     *	to true if the function has found more tokens after the extracted token; false otherwise.
     */
    const std::string nextToken(const std::string& str, size_t& next_pos, bool& more);
 
    /**	
     *	resets the delimiter for this class to the character received
     */
    static void setDelimiter(const char c);
 
    /**
     *	returns the delimiter for this class
     */
    static const char getDelimiter();
};
