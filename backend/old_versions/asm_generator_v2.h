// Copyright msg for cpplint
#ifndef BACKEND_ASM_GENERATOR_V2_H_
#define BACKEND_ASM_GENERATOR_V2_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "utility/memory.h"
#include "backend/ir_v2.h"

using std::endl;
using std::string;
using cs160::backend::ir::StatementNode;
using cs160::backend::ir::Operator;
namespace cs160 {
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
      asm_sstring_ << ".global main" << endl;
      asm_sstring_ << ".text" << endl;
      asm_sstring_ << "main:" << endl << endl;
      while (head != nullptr) {
        GenerateASM(head);
        head = head->GetNext();
      }
      asm_sstring_ << "pop %rax" << endl;
      asm_sstring_ << "mov     $format, %rdi" << endl;
      asm_sstring_ << "mov     %rax, %rsi" << endl;
      asm_sstring_ << "xor     %rax, %rax" << endl;
      asm_sstring_ << "call    printf" << endl;

      asm_sstring_ << "  ret" << endl;

      asm_sstring_ << "format:" << endl;
      asm_sstring_ << "  .asciz  \"%0ld\\n\"" << endl;
      asm_sstring_ << endl;
      asm_sstring_ << ".data" << endl;
      asm_sstring_ << asm_sstring_variables_.str();
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
        if (asm_sstring_variables_.str().find(node->GetTarget()->GetName()) == std::string::npos) {
          asm_sstring_variables_ << node->GetTarget()->GetName() << ":" << endl;
          asm_sstring_variables_ << "  .quad  0" << endl;
        }
        else {
          // do not add same definition of variable if its already there
        }
        asm_sstring_ << "pop (" << node->GetTarget()->GetName() << ")" << endl;
        break;
      default:
        break;

      }

    }


  }  // namespace backend
}  // namespace cs160

#endif  // BACKEND_ASM_GENERATOR_V2_H_
