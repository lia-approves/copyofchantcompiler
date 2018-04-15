//
//  IntegerToken.hpp
//  
//
//  Created by Maggie Schmit on 4/11/18.
//
//

#ifndef IntegerToken_h
#define IntegerToken_h

#include <stdio.h>
#include <string>

class IntegerToken: public Token{
    
public:
    void set_token_string(std::string str);
    int get_token_int();
    
private:
    int token_int;
    
    
};

#endif /* IntegerToken_hpp */
