//
//  Token.cpp
//
//
//  Created by Maggie Schmit on 4/11/18.
//
//

#include "Token.h"
#include <string>


Token::Token(){ /*doesn't do anything, is necessary to have a default constructor in InvalidToken*/};
Token::Token(std::string str){token_str_ = str;}

std::string Token::get_token(){ return token_str_;}

void Token::set_token_str(std::string str){ token_str_ = str;}

void Token::set_token(std::string str) {token_str_ = str;}
