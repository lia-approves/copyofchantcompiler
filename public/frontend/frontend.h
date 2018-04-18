#ifndef FRONTEND_H_
#define FRONTEND_H_

#include "abstract_syntax/abstract_syntax.h"

namespace cs160 {
namespace frontend {

class Frontend {
  public:
    ~Frontend(void);

    void stringToAst(std::string input);

};

}
}

#endif // FRONTEND_H_