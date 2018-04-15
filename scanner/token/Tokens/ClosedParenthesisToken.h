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


class ClosedParenthesisToken : public Token{
    
public:
    //cannot use the Token(string) constructor, or it will be bad
    ClosedParenthesisToken();
    set_token(std::string str);
    get_token_char();
    
private:
    const char token_char = ')';
    const std::string token_str = ")";
    
    
};

#endif /* ClosedParenthesisToken_hpp */
