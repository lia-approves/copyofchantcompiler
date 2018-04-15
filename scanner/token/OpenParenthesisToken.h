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

class OpenParenthesisToken : public Token{
    
public:
    //cannot use the Token(string) constructor, or it will be bad
    OpenParenthesisToken();
    set_token(std::string str);
    get_token_char();
    
private:
    const char token_char = '(';
    const std::string token_str = "(";
    
    
};

#endif /* OpenParenthesisToken_hpp */
