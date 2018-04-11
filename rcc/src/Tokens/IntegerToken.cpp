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

int IntegerToken::get_token_int(){
    return token_int;
}
