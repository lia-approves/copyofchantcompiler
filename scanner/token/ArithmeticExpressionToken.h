//
//  ArithmeticExpressionToken.hpp
//  
//
//  Created by Maggie Schmit on 4/11/18.
//
//

#ifndef ArithmeticExpressionToken_h
#define ArithmeticExpressionToken_h

#include <stdio.h>
#include "Token.h"

class ArithmeticExpressionToken: public Token{
    
public:
    explicit ArithmeticExpressionToken(char tok);
    explicit ArithmeticExpressionToken(std::string tok);
    void set_token(std::string str);
    void set_token_char(char tok);
    char get_token_char();
    
    
private:
    char token_char_;
};

#endif /* ArithmeticExpressionToken_hpp */
