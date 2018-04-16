//
//  IntegerToken.cpp
//
//
//  Created by Maggie Schmit on 4/11/18.
//
//

#include "IntegerToken.h"
#include <sstream>

IntegerToken::IntegerToken(std::string str) : Token(str) {}
IntegerToken::IntegerToken(int tok_integer) {
    std::string str_arg = std::to_string(tok_integer);
    set_token_str(str_arg);
    
    token_int_ = tok_integer;
    
}

void IntegerToken::set_token(std::string str){

    set_token_str(str);

    std::stringstream cast_to_int(str);

    cast_to_int >> token_int_;


}

int IntegerToken::get_token_int(){
    return token_int_;
}
