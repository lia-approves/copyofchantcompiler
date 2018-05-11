// Copyright msg for cpplint
#ifndef BACKEND_ASM_GENERATOR_V3_H_
#define BACKEND_ASM_GENERATOR_V3_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "utility/memory.h"
#include "backend/ir_v3.h"

using std::endl;
using std::string;
using cs160::backend::StatementNode;
using cs160::backend::Operator;

namespace cs160 {
<<<<<<< HEAD
  namespace backend {

    class AsmProgram {
    public:
      AsmProgram() {}
      ~AsmProgram() {}
      void IrToAsm(StatementNode* head);
      string GetASMString() { return asm_sstring_.str(); }
    private:
      void GenerateASM(StatementNode* node);
      stringstream asm_sstring_;
      stringstream asm_sstring_variables_;
    };
=======
namespace backend {

class AsmProgram {
 public:
  AsmProgram() {}
  ~AsmProgram() {}
  void IrToAsm(StatementNode* head);
  string GetASMString() { return asm_sstring_.str(); }
 private:
  void GenerateASM(StatementNode* node);
  stringstream asm_sstring_;
  stringstream asm_sstring_variables_;
};

  void AsmProgram::IrToAsm(StatementNode* head) {
    asm_sstring_ << "#### Start of Assembly ####\n\n";

    asm_sstring_ << ".global main" << endl;
    asm_sstring_ << ".text" << endl;
    asm_sstring_ << "main:" << endl << endl;
    asm_sstring_ << "#### Start of Statements ####\n";

    while (head != nullptr) {
      asm_sstring_
      << endl
      << "statementnumber_"
      << head->GetLabel()->GetValue()
      << ":"
      << endl
      << endl;

      GenerateASM(head);

      head = head->GetNext();
    }
>>>>>>> 160c71cb371d2b02a6df186bc1ee1c5891334f42

    asm_sstring_ << "#### End of Statements ####\n\n";
    asm_sstring_ << "pop %rax" << endl;
    asm_sstring_ << "mov     $format, %rdi" << endl;
    asm_sstring_ << "mov     %rax, %rsi" << endl;
    asm_sstring_ << "xor     %rax, %rax" << endl;
    asm_sstring_ << "call    printf" << endl;

    asm_sstring_ << "  ret" << endl;

<<<<<<< HEAD
      while (head != nullptr) {
        asm_sstring_
          << endl
          << "statementnumber_"
          << head->GetLabel()->GetValue()
          << ":"
          << endl
          << endl;
=======
    asm_sstring_ << "format:" << endl;
    asm_sstring_ << "  .asciz  \"%d\\n\"" << endl;
    asm_sstring_ << endl;
    asm_sstring_ << ".data" << endl;
    asm_sstring_ << asm_sstring_variables_.str();

    asm_sstring_ << "\n#### End of Assembly ####\n";
  }
>>>>>>> 160c71cb371d2b02a6df186bc1ee1c5891334f42

  void AsmProgram::GenerateASM(StatementNode* node) {
    if (node->GetOp1() != nullptr) node->GetOp1()->PushToAsmSS(asm_sstring_);
    if (node->GetOp2() != nullptr) node->GetOp2()->PushToAsmSS(asm_sstring_);

    switch (node->GetInstruction()->GetOpcode()) {
    case Operator::kAdd:
      asm_sstring_ << "pop %rax" << endl;
<<<<<<< HEAD
      asm_sstring_ << "mov     $format, %rdi" << endl;
      asm_sstring_ << "mov     %rax, %rsi" << endl;
      asm_sstring_ << "xor     %rax, %rax" << endl;
      asm_sstring_ << "call    printf" << endl;

      asm_sstring_ << "  ret" << endl;

      asm_sstring_ << "format:" << endl;
      asm_sstring_ << "  .asciz  \"%d\\n\"" << endl;
      asm_sstring_ << endl;
      asm_sstring_ << ".data" << endl;
      asm_sstring_ << asm_sstring_variables_.str();

      asm_sstring_ << "\n#### End of Assembly ####\n";
    }

    void AsmProgram::GenerateASM(StatementNode* node) {
      if (node->GetOp1() != nullptr) node->GetOp1()->PushToAsmSS(asm_sstring_);
      if (node->GetOp2() != nullptr) node->GetOp2()->PushToAsmSS(asm_sstring_);

      switch (node->GetInstruction()->GetOpcode()) {
      case Operator::kAdd:
        asm_sstring_ << "pop %rax" << endl;
        asm_sstring_ << "pop %rbx" << endl;
        asm_sstring_ << "add %rax, %rbx" << endl;
        asm_sstring_ << "push %rbx" << endl << endl;
        break;
      case Operator::kSubtract:
        asm_sstring_ << "pop %rax" << endl;
        asm_sstring_ << "pop %rbx" << endl;
        asm_sstring_ << "sub %rax, %rbx" << endl;
        asm_sstring_ << "push %rbx" << endl << endl;
        break;
      case Operator::kMultiply:
        asm_sstring_ << "pop %rax" << endl;
        asm_sstring_ << "pop %rbx" << endl;
        asm_sstring_ << "imul %rax, %rbx" << endl;
        asm_sstring_ << "push %rbx" << endl << endl;
        break;
      case Operator::kDivide:
        asm_sstring_ << "pop %rbx" << endl;
        asm_sstring_ << "pop %rax" << endl;
        asm_sstring_ << "mov $0, %rdx" << endl;
        asm_sstring_ << "idiv %rbx" << endl;
        asm_sstring_ << "push %rax" << endl << endl;
        break;
      case Operator::kAssign:
        if (asm_sstring_variables_
          .str()
          .find(node->GetTarget()->GetName()) == std::string::npos) {
          asm_sstring_variables_ << node->GetTarget()->GetName() << ":" << endl;
          asm_sstring_variables_ << "  .quad  0" << endl;
        }
        else {
          // do not add same definition of variable if its already there
        }
        asm_sstring_ << "pop (" << node->GetTarget()->GetName() << ")" << endl;
        break;
      case Operator::kLessThan:
        asm_sstring_ << "pop %rax" << endl;
        asm_sstring_ << "pop %rbx" << endl;
        asm_sstring_ << "cmp %rax, %rbx" << endl;
        asm_sstring_ << "jl " << node->GetTarget()->GetName() << endl;
        break;
      case Operator::kLessThanEqualTo:
        asm_sstring_ << "pop %rax" << endl;
        asm_sstring_ << "pop %rbx" << endl;
        asm_sstring_ << "cmp %rax, %rbx" << endl;
        asm_sstring_ << "jle " << node->GetTarget()->GetName() << endl;
        break;
      case Operator::kGreaterThan:
        asm_sstring_ << "pop %rax" << endl;
        asm_sstring_ << "pop %rbx" << endl;
        asm_sstring_ << "cmp %rax, %rbx" << endl;
        asm_sstring_ << "jg " << node->GetTarget()->GetName() << endl;
        break;
      case Operator::kGreaterThanEqualTo:
        asm_sstring_ << "pop %rax" << endl;
        asm_sstring_ << "pop %rbx" << endl;
        asm_sstring_ << "cmp %rax, %rbx" << endl;
        asm_sstring_ << "jge " << node->GetTarget()->GetName() << endl;
        break;
      case Operator::kEqualTo:
        asm_sstring_ << "pop %rax" << endl;
        asm_sstring_ << "pop %rbx" << endl;
        asm_sstring_ << "cmp %rax, %rbx" << endl;
        asm_sstring_ << "je " << node->GetTarget()->GetName() << endl;
        break;
      case Operator::kGoto:
        asm_sstring_ << "jmp " << node->GetTarget()->GetName() << endl;
      default:
        break;
      }
=======
      asm_sstring_ << "pop %rbx" << endl;
      asm_sstring_ << "add %rax, %rbx" << endl;
      asm_sstring_ << "push %rbx" << endl << endl;
      break;
    case Operator::kSubtract:
      asm_sstring_ << "pop %rax" << endl;
      asm_sstring_ << "pop %rbx" << endl;
      asm_sstring_ << "sub %rax, %rbx" << endl;
      asm_sstring_ << "push %rbx" << endl << endl;
      break;
    case Operator::kMultiply:
      asm_sstring_ << "pop %rax" << endl;
      asm_sstring_ << "pop %rbx" << endl;
      asm_sstring_ << "imul %rax, %rbx" << endl;
      asm_sstring_ << "push %rbx" << endl << endl;
      break;
    case Operator::kDivide:
      asm_sstring_ << "pop %rbx" << endl;
      asm_sstring_ << "pop %rax" << endl;
      asm_sstring_ << "mov $0, %rdx" << endl;
      asm_sstring_ << "idiv %rbx" << endl;
      asm_sstring_ << "push %rax" << endl << endl;
      break;
    case Operator::kAssign:
      if (asm_sstring_variables_
        .str()
        .find(node->GetTarget()->GetName()) == std::string::npos) {
        asm_sstring_variables_ << node->GetTarget()->GetName() << ":" << endl;
        asm_sstring_variables_ << "  .quad  0" << endl;
      } else {
        // do not add same definition of variable if its already there
      }
      asm_sstring_ << "pop (" << node->GetTarget()->GetName() << ")" << endl;
      break;
    case Operator::kLessThan:
      asm_sstring_ << "pop %rax" << endl;
      asm_sstring_ << "pop %rbx" << endl;
      asm_sstring_ << "cmp %rax, %rbx" << endl;
      asm_sstring_ << "jl " << node->GetTarget()->GetName() << endl;
      break;
    case Operator::kLessThanEqualTo:
      asm_sstring_ << "pop %rax" << endl;
      asm_sstring_ << "pop %rbx" << endl;
      asm_sstring_ << "cmp %rax, %rbx" << endl;
      asm_sstring_ << "jle " << node->GetTarget()->GetName() << endl;
      break;
    case Operator::kGreaterThan:
      asm_sstring_ << "pop %rax" << endl;
      asm_sstring_ << "pop %rbx" << endl;
      asm_sstring_ << "cmp %rax, %rbx" << endl;
      asm_sstring_ << "jg " << node->GetTarget()->GetName() << endl;
      break;
    case Operator::kGreaterThanEqualTo:
      asm_sstring_ << "pop %rax" << endl;
      asm_sstring_ << "pop %rbx" << endl;
      asm_sstring_ << "cmp %rax, %rbx" << endl;
      asm_sstring_ << "jge " << node->GetTarget()->GetName() << endl;
      break;
    case Operator::kEqualTo:
      asm_sstring_ << "pop %rax" << endl;
      asm_sstring_ << "pop %rbx" << endl;
      asm_sstring_ << "cmp %rax, %rbx" << endl;
      asm_sstring_ << "je " << node->GetTarget()->GetName() << endl;
      break;
    case Operator::kGoto:
      asm_sstring_ << "jmp " << node->GetTarget()->GetName() << endl;
    default:
      break;
>>>>>>> 160c71cb371d2b02a6df186bc1ee1c5891334f42
    }
  }


}  // namespace backend
}  // namespace cs160

#endif  // BACKEND_ASM_GENERATOR_V3_H_
