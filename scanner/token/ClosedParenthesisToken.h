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

class ClosedParenthesisToken : public Token{
    
public:
    //cannot use the Token(string) constructor, or it will be bad
    ClosedParenthesisToken();
    void set_token(std::string str);
    char get_token_char();
    
private:
    const char token_char_ = ')';
    const std::string token_str_ = ")";
    
    
};

#endif /* ClosedParenthesisToken_hpp */
