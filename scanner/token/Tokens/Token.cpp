//
//  Token.cpp
//  
//
//  Created by Maggie Schmit on 4/11/18.
//
//

#include "Token.h"
#include <string>


    
Token::Token(std::string str){token_str = str;}
    
std::string Token::get_token(){ return token_str;}

