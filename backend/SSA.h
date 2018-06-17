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
      void RemoveLeaderEndStatus() { isBlockEnd_ = false; isBlockLeader_ = false; }
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
   
    class Graph{
    public:
      Graph(std::vector<std::shared_ptr<BasicBlock>> &cfg, int startBlockIndex, std::vector<std::shared_ptr<StatementNode>> &original_IR) :  startGraphBlockIndex_(startBlockIndex), graphId_(startBlockIndex), original_IR_(original_IR){}
      void BuildDomInfo(std::vector<std::shared_ptr<BasicBlock>> &CFG);
      void FindChildrens(int parent,std::vector<int> &children);
      void FindDominatorFrontiers(std::vector<std::shared_ptr<BasicBlock>> &CFG);
      void FindPhiFunctionPlacements(int Blockid,std::set<int> &locations);
      void InsertPhiFunctAt(string variable, int blockId, std::vector<std::shared_ptr<StatementNode>> &IR, std::vector<std::shared_ptr<BasicBlock>> &CFG);
      void RenameAllVariables(std::vector<std::shared_ptr<StatementNode>> &IR, std::vector<std::shared_ptr<BasicBlock>> &CFG,int graphid);
      int GetRootNode() { return graphId_; }
      int NewNameWithSubscript(string varName);
      int CurrentNameWithSubscript(string varName);
      void RenameBlock(int blockid, std::vector<std::shared_ptr<StatementNode>> &IR, std::vector<std::shared_ptr<BasicBlock>> &CFG);
      std::vector<int> GetImmediateGraphSucessors(int blockNum, std::vector<std::shared_ptr<BasicBlock>> &CFG);
      int GetGraphId() { return graphId_; }
      void SetGraphId(int id) { graphId_ = id; }
      void PrintDominatorInfo();
      void FindGlobalVariables(std::vector<std::shared_ptr<BasicBlock>> &CFG);
      std::vector<int> GetImmediateTreeSucessors(int blockId);
      int InsertSSA(std::vector<std::shared_ptr<StatementNode>> &IR, std::vector<std::shared_ptr<BasicBlock>> &CFG);
      void AddToAssignmentLocations(string name, int location);
      void UpdateCFG(int offset);
      struct AssignPoints{
        string name_;
        std::set<int> blockLocations_;
      };
      struct NamesCounterStack {
        string name_;
        int counter_;
        std::vector<int> nameStack_;
      };
      std::vector<int> GetBlockNums() { return blockNums_; }
      std::vector<std::vector<int>> GetDominated() { return dominated_; }
      std::vector<int> GetIdoms() { return idoms_; }
      std::vector<std::vector<int>> GetDomFrontiers() { return domFrontier_; }
    private:
      int startGraphBlockIndex_;
      std::vector<int> blockNums_;
      std::vector<int> idoms_;
      std::vector<std::vector<int>> dominated_;
      std::vector<std::vector<int>> domFrontier_;
      std::vector<std::vector<int>> allPaths_;
      void BuildDomInfo(int index, std::vector<std::shared_ptr<BasicBlock>> &CFG);
      void acyclicPathsFromRoot(int desiredIndex, std::vector<std::shared_ptr<BasicBlock>> &CFG);
      void acyclicPathsFromRoot(int desiredIndex, int index, std::vector<std::vector<int>> allPaths, std::vector<std::shared_ptr<BasicBlock>> &CFG);
      void findIdom(int index);
      std::vector<int> DomFrontiers(int block);
      int graphId_ = 0;
      std::vector<std::shared_ptr<StatementNode>> original_IR_;
      std::set<string> globalVariables_;
      std::vector<AssignPoints> assignmentPoints_;
      std::vector<NamesCounterStack> renameStack_;
    };

    class SSA {
    public:
      SSA(std::vector<std::shared_ptr<StatementNode>> original_IR) { original_IR_ = original_IR; }
      void GenerateDomination();
      void PrintSSA();
      void PrintDominators();
      void DetermineVariableLiveness();
      void InsertSSAFunctions();
      void RenameAllVariables();
      std::vector<std::shared_ptr<StatementNode>> GetSSAIR() { return original_IR_; }
      std::vector<Graph> GetDominators() { return dominators_; }
      void ComputeCFG();
      void PrintCFG();
    private:
      std::vector<std::shared_ptr<StatementNode>> original_IR_;
      std::vector<std::shared_ptr<BasicBlock>> cfg_;
      std::vector<Graph> dominators_;
    };
  }  // namespace backend
}  // namespace cs160


#endif  // BACKEND_SSA_H_
