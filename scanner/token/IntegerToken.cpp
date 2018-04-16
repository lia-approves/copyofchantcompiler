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

void IntegerToken::set_token(std::string str){

    set_token_str(str);

    std::stringstream cast_to_int(str);

    cast_to_int >> token_int;


}

int IntegerToken::get_token_int(){
    return token_int;
}
