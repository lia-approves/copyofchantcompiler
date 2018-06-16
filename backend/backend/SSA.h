// Copyright(c) 2018, Team Chant

#ifndef BACKEND_SSA_H_
#define BACKEND_SSA_H_

#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "utility/memory.h"
#include "backend/ir_v5.h"
#include "backend/lowerer_v5.h"

using cs160::backend::StatementNode;
using std::vector;


namespace cs160 {
  namespace backend {

    class BasicBlock {
    public:
      BasicBlock(){}
      ~BasicBlock(){}
      void SetAsBlockLeader() { isBlockLeader_ = true; }
      void SetAsBlockEnd() { isBlockEnd_ = true; }
      bool IsBlockLeader() { return isBlockLeader_; }
      bool IsBlockEnd() { return isBlockEnd_; }
      void AddIncomingEdge(int incoming) { incomingEdges_.push_back(incoming); }
      void AddOutgoingEdge(int outgoing) { outgoingEdges_.push_back(outgoing); }
      std::vector<int> &IncomingEdges() { return incomingEdges_; }
      std::vector<int> &OutgoingEdges() { return outgoingEdges_; }
      void SetBlockLeaderNum(int leader) { blockLeaderNum_ = leader; }
      int GetBlockLeaderNum() { return blockLeaderNum_; }
      void SetgraphIdNum(int graphid) { graphIdNum_ = graphid; }
      int GetgraphIdNum() { return graphIdNum_; }
    private:
      bool isBlockLeader_ = false;
      bool isBlockEnd_ = false;
      std::vector<int> incomingEdges_;
      std::vector<int> outgoingEdges_;
      int blockLeaderNum_ = 0;
      int graphIdNum_ = 0;
    };

    class ControlFlowGraph {
    public:
      ControlFlowGraph(std::vector<std::shared_ptr<StatementNode>> virgin_IR) { virgin_IR_ = virgin_IR; }
      std::vector<std::shared_ptr<BasicBlock>> CFG() { return cfg_; }
      void CreateCFG();
      void PrintGraph();
    private:
      std::vector<std::shared_ptr<StatementNode>> virgin_IR_;
      std::vector<std::shared_ptr<BasicBlock>> cfg_;
    };
   
    class Dominance{
    public:
      Dominance(std::vector<std::shared_ptr<BasicBlock>> &cfg, int startBlockIndex, std::vector<std::shared_ptr<StatementNode>> &original_IR) : cfg_(cfg), startGraphBlockIndex_(startBlockIndex), graphId_(startBlockIndex), original_IR_(original_IR){}
      void BuildDomInfo();
      void FindChildrens(int parent,std::vector<int> &children);
      void FindDominatorFrontiers();
      void FindPhiFunctionPlacements(int Blockid,std::set<int> &locations);
      void InsertPhiFunctAt(string variable, int blockId, std::vector<std::shared_ptr<StatementNode>> &IR);
      std::vector<int> GetImmediateSucessors(int blockNum);
      int GetGraphId() { return graphId_; }
      void PrintDominatorInfo();
      void FindGlobalVariables();
      void InsertSSA(std::vector<std::shared_ptr<StatementNode>> &IR);
      void AddToAssignmentLocations(string name, int location);
      struct AssignmentLocation{
        string name_;
        std::set<int> blockLocations_;
      };
      // preconditions for the following getter methods is that the vectors
      // they return aren't empty
      std::vector<int> GetBlockNums() { return blockNums_; }
      std::vector<std::vector<int>> GetDominated() { return dominated_; }
      std::vector<int> GetIdoms() { return idoms_; }
      std::vector<std::vector<int>> GetDomFrontiers() { return domFrontier_; }
    private:
      std::vector<std::shared_ptr<BasicBlock>> cfg_;
      int startGraphBlockIndex_;
      std::vector<int> blockNums_;
      std::vector<int> idoms_;
      std::vector<std::vector<int>> dominated_;
      std::vector<std::vector<int>> domFrontier_;
      std::vector<std::vector<int>> allPaths_;
      void BuildDomInfo(int index);
      void acyclicPathsFromRoot(int desiredIndex);
      void acyclicPathsFromRoot(int desiredIndex, int index, std::vector<std::vector<int>> allPaths);
      void findIdom(int index);
      std::vector<int> DomFrontiers(int block);
      int graphId_ = 0;
      std::vector<std::shared_ptr<StatementNode>> original_IR_;
      std::set<string> globalVariables_;
      std::vector<AssignmentLocation> assignmentPoints_;
    };
    class SSA {
    public:
      SSA(std::vector<std::shared_ptr<StatementNode>> original_IR, std::vector<std::shared_ptr<BasicBlock>> cfg) { original_IR_ = original_IR; cfg_ = cfg; }
      void GenerateDomination();
      void PrintSSA();
      void PrintDominators();
      void DetermineVariableLiveness();
      void InsertSSAFunctions();
      std::vector<std::shared_ptr<StatementNode>> GetSSAIR() { return original_IR_; }
      std::vector<Dominance> GetDominators() { return dominators_; }

    private:
      std::vector<std::shared_ptr<StatementNode>> original_IR_;
      std::vector<std::shared_ptr<BasicBlock>> cfg_;
      std::vector<Dominance> dominators_;
    };
  }  // namespace backend
}  // namespace cs160


#endif  // BACKEND_SSA_H_
