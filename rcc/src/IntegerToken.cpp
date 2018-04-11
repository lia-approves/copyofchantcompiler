//
//  IntegerToken.cpp
//  
//
//  Created by Maggie Schmit on 4/11/18.
//
//

#include "IntegerToken.h"
#include <sstream>

void IntegerToken::set_token(string str){
    
    token_str = str;
    
    stringstream cast_to_int(str);
    
    cast_to_int >> token_int;
    
    
}

string IntegerToken::get_token_string(){
    return token_str;
}

int IntegerToken::get_token_int(){
    return token_int;
}
