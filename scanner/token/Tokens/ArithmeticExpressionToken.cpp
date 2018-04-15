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
    
    sstream ss;
    ss << tok;
    ss >> token_str;
}

ArithmeticExpressionToken::ArithmeticExpressionToken(std::string tok){
    token_str = tok;
    
    token_char = tok[0];
}

void ArithmeticExpressionToken::set_token(std::string tok){
    token_str = tok;
    
    token_char = tok[0];
}


void ArithmeticExpressionToken::set_token_char(char tok){
    token_char = tok;
    
    sstream ss;
    ss << tok;
    ss >> token_str;
}


char ArithmeticExpressionToken::get_token_char(){
    return token_char;
}
