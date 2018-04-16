//
//  ArithmeticExpressionToken.cpp
//  
//
//  Created by Maggie Schmit on 4/11/18.
//
//

#include "ArithmeticExpressionToken.h"
#include <sstream>

ArithmeticExpressionToken::ArithmeticExpressionToken(char tok){
    
    token_char = tok;
    
    std::stringstream ss;
    ss << tok;
    std::string setter = "";
    ss >> setter;
    
    set_token_str(setter);
}

ArithmeticExpressionToken::ArithmeticExpressionToken(std::string tok){
    set_token_str(tok);
    
    token_char = tok[0];
}

void ArithmeticExpressionToken::set_token(std::string tok){
    set_token_str(tok);
    
    token_char = tok[0];
}


void ArithmeticExpressionToken::set_token_char(char tok){
    token_char = tok;
    
    std::stringstream ss;
    ss << tok;
    std::string setter;
    set_token_str(setter);
}


char ArithmeticExpressionToken::get_token_char(){
    return token_char;
}
