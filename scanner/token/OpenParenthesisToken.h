//
//  OpenParenthesisToken.hpp
//
//
//  Created by Maggie Schmit on 4/11/18.
//
//

#ifndef OpenParenthesisToken_h
#define OpenParenthesisToken_h

#include <stdio.h>
#include "Token.h"

namespace cs160 {
namespace scanner {
namespace token {

class OpenParenthesisToken : public Token{

public:
    //cannot use the Token(string) constructor, or it will be bad
    OpenParenthesisToken();
    void set_token(std::string str);
    char get_token_char();

private:
    const char token_char_ = '(';
    const std::string token_str_ = "(";


};
} // namespace token
} // namespace scanner
} // namespace cs160

#endif /* OpenParenthesisToken_hpp */
