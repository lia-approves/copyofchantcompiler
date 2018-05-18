// Copyright msg for cpplint
#ifndef BACKEND_ASM_GENERATOR_V5_H_
#define BACKEND_ASM_GENERATOR_V5_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "utility/memory.h"
#include "backend/ir_v5.h"
#include "backend/lowerer_v5.h"

using std::endl;
using std::string;
using cs160::backend::StatementNode;
using cs160::backend::Operator;
using cs160::backend::IrGenVisitor;

namespace cs160 {
  namespace backend {

    class AsmProgram {
    public:
      AsmProgram() {}
      ~AsmProgram() {}
      void IrToAsm(IrGenVisitor* ir);
      string GetASMString() { return asm_sstring_.str(); }
    private:
      void GenerateASM(StatementNode* node);
      stringstream asm_sstring_;
      stringstream asm_sstring_variables_;
      IrGenVisitor *ir_;
    };

    void AsmProgram::IrToAsm(IrGenVisitor* ir) {
      ir_ = ir;
      asm_sstring_ << "#### Start of Assembly ####\n\n";

      //asm_sstring_ << ".global main" << endl;
      //asm_sstring_ << ".text" << endl;
      // asm_sstring_ << "main:" << endl << endl;
      asm_sstring_ << "#### Start of Statements ####\n";
     // asm_sstring_ << "mov %rsp, %rbp\n";


      StatementNode * head = ir_->GetIR();
      while (head != nullptr) {
        asm_sstring_
          << "statementnumber_"
          << head->GetLabel()->GetValue()
          << ":"
          << endl;

        GenerateASM(head);

        head = head->GetNext();
      }

      asm_sstring_ << "#### End of Statements ####\n\n";
      asm_sstring_ << "pop %rax" << endl;
      asm_sstring_ << "mov     $format, %rdi" << endl;
      asm_sstring_ << "mov     %rax, %rsi" << endl;
      asm_sstring_ << "xor     %rax, %rax" << endl;
      asm_sstring_ << "call    printf" << endl;

      asm_sstring_ << "\n##DESTROY LOCAL VARS\n";
      asm_sstring_ << "add $" << 8*ir_->NumberOfMainVars()<<", %rsp\n";
      asm_sstring_ << "##end DESTROY LOCAL VARS\n\n";


      asm_sstring_ << "  ret" << endl;

      asm_sstring_ << "format:" << endl;
      asm_sstring_ << "  .asciz  \"%d\\n\"" << endl;
      asm_sstring_ << endl;
      asm_sstring_ << ".data" << endl;
      //asm_sstring_ << asm_sstring_variables_.str();

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
        asm_sstring_ << "pop " << node->GetTarget()->GetStackOffset() << "(%rbp)" << endl;
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
        break;
      case Operator::kAllocateVars:
        asm_sstring_ << "sub $" << 8*node->GetTarget()->GetValue() << ", %rsp\n";
        break;
      case Operator::kDeallocateVars:
        asm_sstring_ << "add $" << 8 * node->GetTarget()->GetValue() -8<< ", %rsp\n";
        break;
        case Operator::kPrint:
          asm_sstring_ << node->GetTarget()->GetName() << endl;

      default:
        break;
      }
    }


  }  // namespace backend
}  // namespace cs160

#endif  // BACKEND_ASM_GENERATOR_V5_H_
