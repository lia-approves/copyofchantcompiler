//
//  Token.h
//
//
//  Created by Maggie Schmit on 4/11/18.
//  Default token base class.
//  Represents an INVALID token
//

#ifndef Token_h
#define Token_h

#include <string>

namespace cs160 {
namespace scanner {
namespace token {

class Token{
public:
    //Constructors
    //Note: default does not do anything
    Token();
    explicit Token(std::string str);

    //Getters and setters
    virtual std::string get_token();
    virtual void set_token(std::string str);
    void set_token_str(std::string str);

private:
    std::string token_str_; //string representation of the token being represented



};
} // namespace token
} // namespace scanner
} // namespace cs160
#endif /* Token_h  */
