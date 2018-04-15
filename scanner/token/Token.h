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

public class Token{
public:
    
    Token(string str);
    
    string get_token_string();
    
    virtual void set_token(string str) = 0;
    
private:
    string token_str; //string representation of the token being represented
    
    

};
#endif /* Token_h  */
