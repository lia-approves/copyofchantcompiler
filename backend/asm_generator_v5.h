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
using cs160::backend::Instruction;
using cs160::backend::IrGenVisitor;

namespace cs160 {
  namespace backend {
    class AsmProgram {
    public:
      AsmProgram() {}
      ~AsmProgram() {}
      void IrToAsm(IrGenVisitor* ir);
      void SSAIRToAsm(std::vector<std::shared_ptr<StatementNode>> SSAIR);
      string GetASMString() { return asm_sstring_.str(); }
      int GetOffSet(string variable);
    private:
      void GenerateASM(std::shared_ptr<StatementNode> node);
      stringstream asm_sstring_;
      stringstream asm_sstring_variables_;
      IrGenVisitor *ir_;
      void NewSymbolTable() { paramVariables_.clear(); localVariables_.clear(); }
      std::vector<string> paramVariables_;
      std::vector<string> paramVariablesSubscripts_;
      std::vector<string> localVariables_;
      std::vector<string> localVariablesSubscripts_;
      int offSet_ = 0; //used by switch so we dont redeclare and dont have to create new scope
    };
    void AsmProgram::IrToAsm(IrGenVisitor* ir) {
      ir_ = ir;
      std::vector<std::shared_ptr<StatementNode>> nodes = ir_->GetIR();
      for (int i = 0; i < nodes.size(); i++) {
        asm_sstring_ << endl << "S" << i << ":" << endl;
        GenerateASM(nodes[i]);
      }
    }
    void AsmProgram::GenerateASM(std::shared_ptr<StatementNode> node) {
      Variable* variableptr;

      switch (node->GetInstruction().GetOpcode()) {
      case Instruction::kAdd:
        asm_sstring_
          << "pop %rax" << endl
          << "pop %rbx" << endl
          << "add %rax, %rbx" << endl
          << "push %rbx" << endl;
        break;
      case Instruction::kSubtract:
        asm_sstring_
          << "pop %rax" << endl
          << "pop %rbx" << endl
          << "sub %rax, %rbx" << endl
          << "push %rbx" << endl;
        break;
      case Instruction::kMultiply:
        asm_sstring_
          << "pop %rax" << endl
          << "pop %rbx" << endl
          << "imul %rax, %rbx" << endl
          << "push %rbx" << endl;
        break;
      case Instruction::kDivide:
        asm_sstring_
          << "pop %rbx" << endl
          << "pop %rax" << endl
          << "mov $0, %rdx" << endl
          << "idiv %rbx" << endl
          << "push %rax" << endl;
        break;
      case Instruction::kLessThan:
        asm_sstring_
          << "pop %rax" << endl
          << "pop %rbx" << endl
          << "cmp %rax, %rbx" << endl
          << "jl S" << node->GetTarget().GetValue() << endl;
        break;
      case Instruction::kLessThanEqualTo:
        asm_sstring_
          << "pop %rax" << endl
          << "pop %rbx" << endl
          << "cmp %rax, %rbx" << endl
          << "jle S" << node->GetTarget().GetValue() << endl;
        break;
      case Instruction::kGreaterThan:
        asm_sstring_
          << "pop %rax" << endl
          << "pop %rbx" << endl
          << "cmp %rax, %rbx" << endl
          << "jg S" << node->GetTarget().GetValue() << endl;
        break;
      case Instruction::kGreaterThanEqualTo:
        asm_sstring_
          << "pop %rax" << endl
          << "pop %rbx" << endl
          << "cmp %rax, %rbx" << endl
          << "jge S" << node->GetTarget().GetValue() << endl;
        break;
      case Instruction::kEqualTo:
        asm_sstring_
          << "pop %rax" << endl
          << "pop %rbx" << endl
          << "cmp %rax, %rbx" << endl
          << "je S" << node->GetTarget().GetValue() << endl;
        break;
      case Instruction::kGoto:
        asm_sstring_
          << "jmp S" << node->GetTarget().GetValue() << endl;
        break;
      case Instruction::kValueOfInteger:
        asm_sstring_
          << "push $" << node->GetOp2().GetValue() << endl; //only integer visitor uses this
        break;
      case Instruction::kValueOfVariable:
        variableptr = dynamic_cast<Variable*>(&node->GetOp2());

        offSet_ = GetOffSet(variableptr->GetNameWithoutSubscript());
        asm_sstring_
          << "mov %rbp,%rcx" << endl;
        if (offSet_ < 0) {
          asm_sstring_
            << "sub $" << -1 * offSet_ << ", %rcx" << endl;
        }
        else {
          asm_sstring_
            << "add $" << offSet_ << " ,%rcx" << endl;
        }
        asm_sstring_
          << "push (%rcx)" << endl; //if we want the value at address we put parenthesis around
        break;
      case Instruction::kAddressOfVariable:
         variableptr = dynamic_cast<Variable*>(&node->GetOp2());

        offSet_ = GetOffSet(variableptr->GetNameWithoutSubscript());
        asm_sstring_
          << "mov %rbp,%rcx" << endl;  //get rbp(start of stack) put in rcx
        if (offSet_ < 0) {
          asm_sstring_
            << "sub $" << -1 * offSet_ << ", %rcx" << endl;
        }
        else { //get exact adress by adding or subtracting the offset
          asm_sstring_ << "add $" << offSet_ << " ,%rcx" << endl;
        }
        asm_sstring_ << "push %rcx" << endl; // address is in rcx we push it
        break;
      case Instruction::kAddressOfDereference: // index is at the top of stack, address is at second to last, which has location of pointer as value
        asm_sstring_
          << "pop %rax" << endl //place index at rax
          << "mov $8, %rbx" << endl //multiplier at rbx
          << "imul %rax, %rbx" << endl //multiply, result in rbx
          << "pop %rcx" << endl // pushing adress of pointer in rcx
          << "mov (%rcx), %rax" << endl // mov pointer address into rax, if we wrote %rcx without parent, we would be moving the address which contains the value of the pointer, not the pointer
          << "add %rbx,%rax" << endl //add 8*index to address of rax(base array pointer)
          << "push %rax" << endl; //push address what is at %rax(location of array + index)
        break;
      case Instruction::kValueOfDereference:
        asm_sstring_
          << "pop %rax" << endl //place index at rax
          << "mov $8, %rbx" << endl //multiplier at rbx
          << "imul %rax, %rbx" << endl //multiply, result in rbx
          << "pop %rcx" << endl // pushing adress of pointer in rcx
          << "mov (%rcx), %rax" << endl // mov pointer address into rax, if we wrote %rcx without parent, we would be moving the address which contains the value of the pointer, not the pointer
          << "add %rbx,%rax" << endl //add 8*index to address of rax(base array pointer)
          << "push (%rax)" << endl; //push value of what is at %rax(location of array + index)
        break;
      case Instruction::kAssignmentFromNewTuple: // we store adress of heap at variable directly
        asm_sstring_
          << "#new tuple" << endl //friendly message
          << "mov $12, %rax" << endl // brk syscall number
          << "mov $0, %rdi" << endl // arg 0 in rax to get currrent pos of heap
          << "syscall" << endl // puts adress of heap in rax
          << "mov %rax, %rsi" << endl //start of heap saved in rsi, this is our pointer
          << "mov %rax, %rdi" << endl // prepare to move heap start by moving breakpoint we need to put desired address in rdi
          << "pop %rax" << endl // size of desired tuple in rax
          << "inc %rax" << endl // allocate one more byte just in case some crazy mofo wants to start arrays at 1
          << "mov $8, %rbx" << endl //size times 8
          << "imul %rax, %rbx" << endl //multiply, result in rbx
          << "add %rbx, %rdi" << endl //move heap breakpoint by 8 * size of tuple, size was in rbx
          << "mov $12, %rax" << endl // prepare brk syscall number again
          << "syscall" << endl // new heap breakpoint has been moved
          << "pop %rcx" << endl // place adress of reference variable into %rcx (lhs), it was on the stack 
          << "mov %rsi, (%rcx)" << endl;// move heap pointer(the start) into the location of %rcx(address of variable)
                                        // at the end, the program break is moved so we dont need to have a new base, every time we request the address of the program break(start of heap), we get a fresh address
        break;
      case Instruction::kAssignmentFromArithExp:
        asm_sstring_
          << "pop %rax" << endl // address is top of stack place it at rax
          << "pop %rbx" << endl  //we visit lhs second so value is at bottomit in rbx
          << "mov %rbx, (%rax)" << endl; //move value rbx to location at address rax
        break;
      case Instruction::kAssignmentToVariable:
        variableptr = dynamic_cast<Variable*>(&node->GetTarget());

        offSet_ = GetOffSet(variableptr->GetNameWithoutSubscript());       
        asm_sstring_
          << "mov %rbp,%rcx" << endl;
        if (offSet_ < 0) {
          asm_sstring_
            << "sub $" << -1 * offSet_ << ", %rcx" << endl;
        }
        else {
          asm_sstring_
            << "add $" << offSet_ << " ,%rcx" << endl;
        }
        asm_sstring_
          << "push %rcx" << endl; //if we want the value at address we put parenthesis around
        asm_sstring_
          << "pop %rax" << endl // address is top of stack place it at rax
          << "pop %rbx" << endl  //we visit lhs second so value is at bottomit in rbx
          << "mov %rbx, (%rax)" << endl; //move value rbx to location at address rax
        break;
      case Instruction::kFuncBegin:
        NewSymbolTable();
        asm_sstring_
          << ".type " << node->GetTarget().GetName() << ",@function" << endl
          << node->GetTarget().GetName() << ":" << endl
          << "push %rbp" << endl
          << "mov %rsp, %rbp" << endl
          << "sub $" << 8 * node->GetOp2().GetValue() << ", %rsp";
        break;
      case Instruction::kFuncEnd:
        asm_sstring_
          << "pop %rax" << endl //return value in rax by convention
          << "mov %rbp, %rsp" << endl
          << "pop %rbp" << endl
          << "ret" << endl;
        NewSymbolTable();
        break;
      case Instruction::kArgument:
        asm_sstring_
          << "#argument" << endl;
        break;
      case Instruction::kParam:
        paramVariables_.push_back(node->GetTarget().GetName());
        asm_sstring_
          << "#parameter " << node->GetTarget().GetName() << endl;
        break;
      case Instruction::kCall:
        variableptr = dynamic_cast<Variable*>(&node->GetOp1());

        offSet_ = GetOffSet(variableptr->GetNameWithoutSubscript());
        asm_sstring_
          << "call " << node->GetTarget().GetName() << endl //call
          << "push %rax" << endl //after func returns, return value in rax
          << "pop " << offSet_ << "(%rbp)" << endl // move value to variable( call.lhs.name)
          << "add $" << 8 * node->GetOp2().GetValue() << ", %rsp" << endl;  //should change this whole routine soon it works for now
        break;
      case Instruction::kProgramStart:
        NewSymbolTable();
        asm_sstring_
          << ".global main" << endl
          << ".text" << endl
          << " main:" << endl
          << "mov %rsp, %rbp" << endl
          << "sub $" << 8 * node->GetOp2().GetValue() << ", %rsp" << endl; //allocate local vars
        break;
      case Instruction::kProgramEnd:
        asm_sstring_
          << "pop %rax" << endl //ae will be in rax
          << "mov $format, %rdi" << endl
          << "mov %rax, %rsi" << endl
          << "mov $0, %rax" << endl
          << "call printf" << endl << endl
          << "add $" << 8 * node->GetOp1().GetValue() << ", %rsp" << endl // add to stack to delete local variables
          << "mov $0, %rax" << endl //return code 0 for exit
          << "ret" << endl
          << "format:" << endl
          << ".asciz  \"%d\\n\"" << endl;
        break;
      case Instruction::kReturn:
        asm_sstring_
          << "# Function or Program Returns Value" << endl;
        break;
      default:
        asm_sstring_
          << "error: no suitable enum found" << endl;
        break;
      case Instruction::kPhiFunction:
        // todo
        break;
      }
    }
    void AsmProgram::SSAIRToAsm(std::vector<std::shared_ptr<StatementNode>> SSAIR) {
      for (int i = 0; i < SSAIR.size(); i++) {
        asm_sstring_ << endl << "S" << i << ":" << endl;
        GenerateASM(SSAIR[i]);
      }
    }
    int AsmProgram::GetOffSet(string variable) {
            int pos;
      int stackOffset;
      bool foundinParams = std::find(paramVariables_.begin(), paramVariables_.end(), (variable)) != paramVariables_.end();
      if (foundinParams) {
        pos = std::distance(paramVariables_.begin(), std::find(paramVariables_.begin(), paramVariables_.end(), variable));
        stackOffset = 1 * ((pos + 2) * 8);
      }
      else {
        bool foundinLocal = std::find(localVariables_.begin(), localVariables_.end(), (variable)) != localVariables_.end();
        if (!foundinLocal) { localVariables_.push_back(variable); }
        else {}
        pos = std::distance(localVariables_.begin(), std::find(localVariables_.begin(), localVariables_.end(), variable));
        stackOffset = -1 * ((pos + 1) * 8);
      }
      return stackOffset;
    }
  }  // namespace backend
}  // namespace cs160

#endif  // BACKEND_ASM_GENERATOR_V5_H_
