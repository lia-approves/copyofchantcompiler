//
//  ClosedParenthesisToken.hpp
//
//
//  Created by Maggie Schmit on 4/11/18.
//
//

#ifndef ClosedParenthesisToken_h
#define ClosedParenthesisToken_h

#include <stdio.h>
#include "Token.h"

namespace cs160 {
namespace scanner {
namespace token {

class ClosedParenthesisToken : public Token{

public:
    //Constructor
    //cannot use the Token(string) constructor, or it will be bad
    ClosedParenthesisToken();

    //Getter and Setters
    void set_token(std::string str);
    char get_token_char();

private:
    const char token_char_ = ')';
    const std::string token_str_ = ")";


};
} // namespace token
} // namespace scanner
} // namespace cs160

#endif /* ClosedParenthesisToken_hpp */
