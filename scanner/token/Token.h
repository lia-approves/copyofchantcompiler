//
//  Token.h
//  
//
//  Created by Maggie Schmit on 4/11/18.
//
//

#ifndef Token_h
#define Token_h

#include <string>

class Token{
public:
    
    Token ();
    Token(std::string str);
    
    std::string get_token();
    
    virtual void set_token(std::string str) = 0;
    
    void set_token_str(std::string str);
    
private:
    std::string token_str; //string representation of the token being represented
    
    

};
#endif /* Token_h  */
