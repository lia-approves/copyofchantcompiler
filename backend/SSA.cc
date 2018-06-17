// Copyright(c) 2018, Team Chant

#include "backend/SSA.h"

using std::cout;
using std::endl;


namespace cs160 {
  namespace backend {
    void SSA::GenerateDomination() {
      dominators_.clear();
      for (int i = 0; i < cfg_.size(); i++) {
        if (cfg_[i]->IsBlockLeader() && cfg_[i]->IncomingEdges().size() == 0) {
          Graph dom(cfg_, i, original_IR_);
          dom.SetGraphId(i);
          dom.BuildDomInfo(cfg_);
          dom.FindDominatorFrontiers(cfg_);
          dominators_.push_back(std::move(dom));
        }
      }
    }
    void SSA::PrintSSA() {
      for (int i = 0; i < original_IR_.size(); i++) {
        original_IR_[i]->Print();
        cout << endl;
      }
    }

    void SSA::PrintDominators() {
      for (auto dominator : dominators_) {
        cout << endl << "# ______________________";
        cout << endl << "# Domination Info for Graph id: " << dominator.GetGraphId();
        dominator.PrintDominatorInfo();
      }
    }

    void SSA::DetermineVariableLiveness() {
      for (int i = 0; i < dominators_.size(); i++) {
        dominators_[i].FindGlobalVariables(cfg_);
      }
    }

    void SSA::InsertSSAFunctions() {
      int inserted;
      for (int i = 0; i < dominators_.size(); i++) {
        inserted = dominators_[i].InsertSSA(original_IR_, cfg_);
        for (int j = i + 1; j < dominators_.size(); j++) {
          int graphid = dominators_[j].GetGraphId();
          dominators_[j].SetGraphId(graphid + inserted);
          dominators_[j].UpdateCFG(inserted);
        }
      }
    }
    void SSA::RenameAllVariables()
    {
      for (int i = 0; i < dominators_.size(); i++) {
        dominators_[i].RenameAllVariables(original_IR_, cfg_,dominators_[i].GetGraphId());
      }
    }

    void SSA::ComputeCFG()
    {
      int numStatements = original_IR_.size();
      for (int i = 0; i < numStatements; i++) { cfg_.push_back(std::move(std::make_shared<BasicBlock>())); }
      int trueGoto; // we use this for the conditionals, there is only 
      int falseGoto; // a true and a false branch statement
      int targetGoto; //we use this for the gotos
      for (int i = 0; i < original_IR_.size(); i++) {
        switch (original_IR_[i]->GetInstruction().GetOpcode()) {
        case Instruction::kLessThan:
        case Instruction::kLessThanEqualTo:
        case Instruction::kGreaterThan:
        case Instruction::kGreaterThanEqualTo:
        case Instruction::kEqualTo:
          trueGoto = original_IR_[i]->GetTarget().GetValue(); //true target is always in the same line
          falseGoto = i + 1; //false target is always the next statement since  it wont jump and it will simply to go the next line
          cfg_[trueGoto]->SetAsBlockLeader(); // the node numbers it will jump to will be set as a block leader
          cfg_[trueGoto]->AddIncomingEdge(i); // and then we will add an incoming edge to it
          cfg_[falseGoto]->SetAsBlockLeader(); // same thing happens to the false statement target 
          cfg_[falseGoto]->AddIncomingEdge(i);
          if (trueGoto - 1 >= 0) cfg_[trueGoto - 1]->SetAsBlockEnd(); // an end of block is always right before a block leader
          if (falseGoto - 1 >= 0) cfg_[falseGoto - 1]->SetAsBlockEnd(); //same for the false branch target leader
          cfg_[i]->AddOutgoingEdge(trueGoto); //add outgoing true edge to current node
          cfg_[i]->AddOutgoingEdge(falseGoto); //add false edge branch too
          break;
        case Instruction::kGoto:
          targetGoto = original_IR_[i]->GetTarget().GetValue(); // the goto statement has a single unconditional branch instruction
          cfg_[targetGoto]->SetAsBlockLeader();
          cfg_[targetGoto]->AddIncomingEdge(i);
          cfg_[i]->AddOutgoingEdge(targetGoto);
          if (targetGoto - 1 >= 0) cfg_[targetGoto - 1]->SetAsBlockEnd();
          break;
        case Instruction::kProgramStart:
        case Instruction::kFuncBegin:
          cfg_[i]->SetAsBlockLeader();
          break;
        case Instruction::kFuncEnd:
        case Instruction::kProgramEnd:
          cfg_[i]->SetAsBlockEnd();
          break;
        case Instruction::kPhiFunction:
          if (i != 1 && original_IR_[i - 1]->GetInstruction().GetOpcode() != Instruction::kPhiFunction) {
            cfg_[i]->SetAsBlockLeader();
          }
          break;
        default:
          break;
        }
      }
      for (int i = 0; i < cfg_.size(); i++) { //second pass for detecting end of blocks that have no where to go
        if (cfg_[i]->IsBlockEnd() && cfg_[i]->OutgoingEdges().size() == 0 &&
          original_IR_[i]->GetInstruction().GetOpcode() != Instruction::kProgramEnd &&
          original_IR_[i]->GetInstruction().GetOpcode() != Instruction::kFuncEnd) {
          targetGoto = i + 1;
          cfg_[i]->AddOutgoingEdge(targetGoto);
          cfg_[targetGoto]->AddIncomingEdge(i);
        }
      }
      for (int i = 0; i < cfg_.size(); i++) {
        int currentLeaderNum;
        int currentgraphidnum;
        if (cfg_[i]->IncomingEdges().size() > 0) {
          for (int j = 0; j < cfg_[i]->IncomingEdges().size(); j++) {
            int currentIncoming = cfg_[i]->IncomingEdges()[j];
            while (cfg_[currentIncoming]->IsBlockLeader() == false) { currentIncoming--; }
            cfg_[i]->IncomingEdges().at(j) = currentIncoming;
            if (original_IR_[j]->GetInstruction().GetOpcode() == Instruction::kPhiFunction && cfg_[j]->IsBlockEnd()) {
              cfg_[j]->RemoveLeaderEndStatus();
              cfg_[j + 1]->RemoveLeaderEndStatus();
            }
          }
        }
        if (original_IR_[i]->GetInstruction().GetOpcode() == Instruction::kFuncBegin || original_IR_[i]->GetInstruction().GetOpcode() == Instruction::kProgramStart) {
          currentgraphidnum = i;
        }
        cfg_[i]->SetgraphIdNum(currentgraphidnum);
        if (cfg_[i]->IsBlockLeader()) {
          currentLeaderNum = i;
        }
        cfg_[i]->SetBlockLeaderNum(currentLeaderNum);
        if (cfg_[i]->IsBlockEnd()) {
          cfg_[currentLeaderNum]->OutgoingEdges() = cfg_[i]->OutgoingEdges();
        }

      }
    }
    void SSA::PrintCFG()
    {
      cout << "## CONTROL FLOW GRAPH BEGIN ##" << endl;
      cout << "## Program Flow starts at \"main program end \"##" << endl;
      for (int i = 0; i < cfg_.size(); i++) {
        if (cfg_[i]->IsBlockLeader()) {
          std::cout << "# __________________" << endl;
          cout << "# Block Id: " << i << endl;
          if (cfg_[i]->IncomingEdges().size() > 0) {
            cout << "# Incoming Edges ->{";
            for (int j = 0; j < cfg_[i]->IncomingEdges().size() - 1; j++) { cout << cfg_[i]->IncomingEdges()[j] << ","; }
            cout << cfg_[i]->IncomingEdges().back();
            cout << "} " << endl;
          }
          cout << "# Block Start Statements:" << endl;
        }
        original_IR_[i]->Print();
        if (cfg_[i]->IsBlockEnd()) {
          cout << endl << "# Block End ";
          if (cfg_[i]->OutgoingEdges().size() == 2) {
            cout << endl << "# Outgoing Edges -> {";
            cout << "True: " << cfg_[i]->OutgoingEdges()[0];
            cout << ",";
            cout << "False: " << cfg_[i]->OutgoingEdges()[1];
            cout << "}";
          }
          if (cfg_[i]->OutgoingEdges().size() == 1) { cout << endl << "# Outgoing Edges -> {" << cfg_[i]->OutgoingEdges()[0] << "}"; }
          cout << endl;
          std::cout << "# __________________" << endl;
        }
        cout << endl;
      }
      cout << "## CONTROL FLOW GRAPH ENDOF ##" << endl;
    }
    void Graph::BuildDomInfo(std::vector<std::shared_ptr<BasicBlock>> &CFG) {
      blockNums_.push_back(startGraphBlockIndex_);
      idoms_.push_back(-1);
      for (auto it : CFG[startGraphBlockIndex_]->OutgoingEdges()) {
        BuildDomInfo(it,CFG);
      }
      std::vector<int> children;
      for (int i = 0; i < blockNums_.size(); i++) {
        children.push_back(blockNums_[i]);
        FindChildrens(blockNums_[i], children);
        dominated_.push_back(children);
        children.clear();
      }
    }
    void Graph::BuildDomInfo(int index, std::vector<std::shared_ptr<BasicBlock>> &CFG) {
      acyclicPathsFromRoot(index,CFG);
      for (auto it : CFG[index]->OutgoingEdges()) {
        if (std::find(blockNums_.begin(), blockNums_.end(), it) == blockNums_.end()) {
          BuildDomInfo(it,CFG);
        }
      }
    }

    void Graph::FindChildrens(int parent, std::vector<int> &children) {
      std::vector<int> immediateChildren;
      for (int i = 0; i < idoms_.size(); i++) {
        if (idoms_[i] == parent) {
          immediateChildren.push_back(blockNums_[i]);
          children.push_back(blockNums_[i]);
        }
      }
      if (immediateChildren.size() > 0) {
        for (int i = 0; i < immediateChildren.size(); i++) {
          FindChildrens(immediateChildren[i], children);
        }
      }
    }

    void Graph::FindDominatorFrontiers(std::vector<std::shared_ptr<BasicBlock>> &CFG) {
      for (int i = 0; i < blockNums_.size(); i++) {
        std::vector<int> initialVector; //empty
        domFrontier_.push_back(initialVector);
        int root = blockNums_[i];
        std::vector<int> dominated = dominated_[i];
        for (auto dominatedNode : dominated) {
          std::vector<int> graphSuccessors = GetImmediateGraphSucessors(dominatedNode,CFG);
          if (graphSuccessors.size() > 0) {
            for (auto sucessor : graphSuccessors) {
              if (std::find(dominated.begin(), dominated.end(), sucessor) != dominated.end()) {
                if (sucessor == root) {
                  domFrontier_[i].push_back(sucessor);
                }
                else {
                  // do not push
                }
              }
              else {
                domFrontier_[i].push_back(sucessor);
              }
            }
          }
        }
      }
    }

    void Graph::FindPhiFunctionPlacements(int Blockid, std::set<int> &locations) {
      std::vector<int> frontiers = DomFrontiers(Blockid);
      for (auto frontier : frontiers) {
        locations.insert(frontier);
      }
      for (auto frontier : frontiers) {
        if (!(std::find(locations.begin(), locations.end(), Blockid) != locations.end())) {
          FindPhiFunctionPlacements(frontier, locations);
        }
      }
    }

    std::vector<int> Graph::GetImmediateGraphSucessors(int blockNum, std::vector<std::shared_ptr<BasicBlock>> &CFG) {
      std::vector<int> sucessors;
      if (CFG[blockNum]->OutgoingEdges().size() > 0) {
        for (auto outgoing : CFG[blockNum]->OutgoingEdges()) {
          sucessors.push_back(outgoing);
        }
      }
      return sucessors;
    }

    void Graph::PrintDominatorInfo() {
      cout << endl;
      for (int i = 0; i < blockNums_.size(); i++) {
        cout << "# BlockId: " << blockNums_[i] << ", iDom: " << idoms_[i] << ", Dominates: ";
        for (auto dominated : dominated_[i]) {
          cout << dominated << ",";
        }
        cout << " Dominance Frontier: ";
        for (auto domFrontier : domFrontier_[i]) {
          cout << domFrontier << ",";
        }
        cout << endl;
      }
    }

    void Graph::FindGlobalVariables(std::vector<std::shared_ptr<BasicBlock>> &CFG) {
      std::vector<int> blockIds;
      for (auto id : blockNums_) {
        blockIds.push_back(id);
      }
      std::set<string> varKill;
      for (auto block : blockIds) {
        varKill.clear();
        string nameToBeAddedtoGlobal;
        string tobeKilled;
        AssignPoints killvar;
        int i = block;
        while (!CFG[i]->IsBlockEnd()) {
          switch (original_IR_[i]->GetInstruction().GetOpcode()) {
          case Instruction::kValueOfVariable:
            nameToBeAddedtoGlobal = original_IR_[i]->GetOp2().GetName();
            if (!(varKill.find(nameToBeAddedtoGlobal) != varKill.end())) {
              globalVariables_.insert(nameToBeAddedtoGlobal);
            }
            break;
          case Instruction::kAssignmentToVariable:
            tobeKilled = original_IR_[i]->GetTarget().GetName();
            varKill.insert(tobeKilled);
            AddToAssignmentLocations(tobeKilled, block);
            break;
          case Instruction::kCall:
            tobeKilled = original_IR_[i]->GetOp1().GetName();
            varKill.insert(tobeKilled);
            AddToAssignmentLocations(tobeKilled, block);
            break;
          default:
            break;
          }
          i++;
        }
        switch (original_IR_[i]->GetInstruction().GetOpcode()) {
        case Instruction::kValueOfVariable:
          nameToBeAddedtoGlobal = original_IR_[i]->GetOp2().GetName();
          if (!(varKill.find(nameToBeAddedtoGlobal) != varKill.end())) {
            globalVariables_.insert(nameToBeAddedtoGlobal);
          }
          break;
        case Instruction::kAssignmentToVariable:
          tobeKilled = original_IR_[i]->GetTarget().GetName();
          varKill.insert(tobeKilled);
          AddToAssignmentLocations(tobeKilled, block);
          break;
        case Instruction::kCall:
          tobeKilled = original_IR_[i]->GetOp1().GetName();
          varKill.insert(tobeKilled);
          AddToAssignmentLocations(tobeKilled, block);
          break;
        default:
          break;
        }
      }
    }

    std::vector<int> Graph::GetImmediateTreeSucessors(int blockId)
    {
      std::vector<int> sucessors;
      if (idoms_.size() > 0) {
        for (int i = 0; i < idoms_.size(); i++) {
          if (idoms_[i] == blockId) {
            sucessors.push_back(blockNums_[i]);
          }
        }
      }
      return sucessors;
    }
      
    int Graph::InsertSSA(std::vector<std::shared_ptr<StatementNode>> &IR, std::vector<std::shared_ptr<BasicBlock>> &CFG) {
      int inserted = 0;
      std::vector<int> locations;// list of places where var will be found
      std::set<int> phiFuncPlacements;
      cout << "\n### Live variable info for graphID: " << GetGraphId() << " ###\n";
      for (auto globalVar : globalVariables_) { // lets go trough all the variables in the global list
        for (auto assignmentlocation : assignmentPoints_) {
          if (globalVar == assignmentlocation.name_) { // here we search for it in 
            for (auto location : assignmentlocation.blockLocations_) {
              locations.push_back(location);
            }
          }
        }
        for (auto location : locations) {
          FindPhiFunctionPlacements(location, phiFuncPlacements);
        }
        cout << endl;
        cout << "# Variable assignment for variable " << globalVar << " at:";
        for (auto location : locations) {
          cout << location << ",";
        }
        std::set<int>::iterator it;
        std::set<int>::iterator inc;
        int current;

        std::vector<int> placements;
        for (auto phiplacement : phiFuncPlacements) {
          placements.push_back(phiplacement);
        }
        for (int i = 0; i < placements.size(); i++) {
          InsertPhiFunctAt(globalVar, placements[i], IR, CFG);
          for (int j= i+1; j < placements.size(); j++) {
            placements[j] = placements[j]++;
            inserted++;
          }
          inserted++;
        }
        locations.clear();
      }
      cout << endl << "# Global Variables: ";
      for (auto each : globalVariables_) {
        cout << each << ",";
      }
      cout << "\n# Phi functions to be placed at:";
      for (auto phiplacement : phiFuncPlacements) {
        cout << phiplacement << ",";
      }
      cout << endl;
      cout << "\n### End of  variable info for graphID: " << GetGraphId() << " ###" << endl;
      cout << endl;
      return inserted;
    }

    void cs160::backend::Graph::InsertPhiFunctAt(string variable, int blockId, std::vector<std::shared_ptr<StatementNode>> &IR, std::vector<std::shared_ptr<BasicBlock>> &CFG) {
      cout << endl;
      int itor = blockId;
      bool alreadyInserted = false;
      while (IR[itor]->GetInstruction().GetOpcode() == Instruction::kPhiFunction) {
        if (IR[itor]->GetTarget().GetName() == variable) {
          alreadyInserted = true;
        }
        itor++;
      }
      if (alreadyInserted) {
        return;
      }
      std::shared_ptr<StatementNode> newhead = std::make_shared< StatementNode>(
        make_unique<Label>(-1),
        make_unique<Variable>(variable),
        make_unique<Instruction>(Instruction::kPhiFunction),
        make_unique<Variable>(variable),
        make_unique<Variable>(""));
      std::vector<std::shared_ptr<StatementNode>>::iterator irIterator;
      std::vector<std::shared_ptr<BasicBlock>>::iterator cfgIterator;
      cfgIterator = CFG.begin();
      irIterator = IR.begin();
      IR.insert(irIterator + blockId, std::move(newhead));
      CFG.insert(cfgIterator + blockId, std::move(std::make_shared<BasicBlock>()));
      CFG[blockId]->SetAsBlockLeader();
      CFG[blockId]->SetBlockLeaderNum(CFG[blockId + 1]->GetgraphIdNum());
      CFG[blockId]->IncomingEdges() = CFG[blockId + 1]->IncomingEdges();
      CFG[blockId]->OutgoingEdges() = CFG[blockId + 1]->OutgoingEdges();
      CFG[blockId]->SetgraphIdNum(CFG[blockId + 1]->GetgraphIdNum());
      CFG[blockId]->SetBlockLeaderNum(CFG[blockId + 1]->GetBlockLeaderNum());
      CFG[blockId + 1]->IncomingEdges().clear();
      CFG[blockId + 1]->OutgoingEdges().clear();
      CFG[blockId + 1]->RemoveLeaderEndStatus();
      for (int i = 0; i < CFG.size(); i++) {
        if (CFG[i]->IncomingEdges().size() > 0) {

          for (int j = 0; j < CFG[i]->IncomingEdges().size(); j++) {
            if (CFG[i]->IncomingEdges()[j] > blockId) {
              CFG[i]->IncomingEdges()[j] = CFG[i]->IncomingEdges()[j] + 1;
            }
          }
        }
        if (CFG[i]->OutgoingEdges().size() > 0) {
          for (int j = 0; j < CFG[i]->OutgoingEdges().size(); j++) {
            if (CFG[i]->OutgoingEdges()[j] > blockId) {
              CFG[i]->OutgoingEdges()[j] = CFG[i]->OutgoingEdges()[j] + 1;
            }
          }
        }
      }
      int insertIndex = blockId;
      int gotoTarget;
      for (int i = 0; i < IR.size(); i++) {
        IR[i]->GetLabel().SetValue(i);
        switch (IR[i]->GetInstruction().GetOpcode())
        {
        case Instruction::kLessThan:
        case Instruction::kLessThanEqualTo:
        case Instruction::kGreaterThan:
        case Instruction::kGreaterThanEqualTo:
        case Instruction::kEqualTo:
        case Instruction::kGoto:
          gotoTarget = IR[i]->GetTarget().GetValue();
          if (gotoTarget > insertIndex) {
            IR[i]->GetTarget().SetValue(gotoTarget + 1);
          }
          break;
        default:
          break;
        }
      }
      for (int i = 0; i < blockNums_.size(); i++) {
        if (blockNums_[i] > blockId) {
          blockNums_[i] = blockNums_[i] + 1;
        }
      }
      for (int i = 0; i < idoms_.size(); i++) {
        if (idoms_[i] > blockId) {
          idoms_[i] = idoms_[i] + 1;
        }
      }
      for (int i = 0; i < blockNums_.size(); i++) {
        if (dominated_[i].size() > 0) {
          for (int j = 0; j < dominated_[i].size(); j++) {
            if (dominated_[i][j] > blockId) {
              dominated_[i][j] = dominated_[i][j] + 1;
            }
          }
        }
      }
      for (int i = 0; i < blockNums_.size(); i++) {
        if (domFrontier_[i].size() > 0) {
          for (int j = 0; j < domFrontier_[i].size(); j++) {
            if (domFrontier_[i][j] > blockId) {
              domFrontier_[i][j] = domFrontier_[i][j] + 1;
            }
          }
        }
      }
    }

    void Graph::RenameAllVariables(std::vector<std::shared_ptr<StatementNode>>& IR, std::vector<std::shared_ptr<BasicBlock>> &CFG,int graphid) {
      int howManyVars = globalVariables_.size();
      std::vector<AssignPoints> VarStackCounters;
      NamesCounterStack namestack;
      for (auto varname : globalVariables_) {
        namestack.name_ = varname;
        namestack.counter_ = 1;
        namestack.nameStack_.push_back(0);
        renameStack_.push_back(namestack);
      }
      RenameBlock(GetRootNode(), IR, CFG);
    }

    int Graph::NewNameWithSubscript(string varName)
    {
      if (renameStack_.size() > 0) {
        for (int i = 0; i < renameStack_.size(); i++) {
          if (renameStack_[i].name_ == varName) {
            int j = renameStack_[i].counter_;
            renameStack_[i].counter_++;
            renameStack_[i].nameStack_.push_back(j);
            return j;
          }
        }
      }
    }

    int Graph::CurrentNameWithSubscript(string varName)
    {
      if (renameStack_.size() > 0) {
        for (int i = 0; i < renameStack_.size(); i++) {
          if (renameStack_[i].name_ == varName) {
            return renameStack_[i].nameStack_.back();
          }
        }
      }
    }

    void Graph::RenameBlock(int blockid, std::vector<std::shared_ptr<StatementNode>>& IR, std::vector<std::shared_ptr<BasicBlock>> &CFG) {
      // 1st case
      int i = blockid;
      string varName;
      string ssaName;
      string phiParams;
      int newsubscript;
      int currentsubscript;
      Variable* variableptr;
      while (IR[i]->GetInstruction().GetOpcode() == Instruction::kPhiFunction) {
        variableptr = dynamic_cast<Variable*>(&IR[i]->GetTarget());
        string currentName = variableptr->GetNameWithoutSubscript();
        newsubscript = NewNameWithSubscript(currentName);
        variableptr->SetSubscript(std::to_string(newsubscript));
        i++;
      }
      // 2nd case
      i = blockid;
      while (!CFG[i]->IsBlockEnd()) {
        switch (IR[i]->GetInstruction().GetOpcode()) {
        case Instruction::kValueOfVariable:
          variableptr = dynamic_cast<Variable*>(&IR[i]->GetOp2());
          varName = variableptr->GetNameWithoutSubscript();
          currentsubscript = CurrentNameWithSubscript(varName);
          variableptr->SetSubscript(std::to_string(currentsubscript));
          break;
        case Instruction::kAssignmentToVariable:
          variableptr = dynamic_cast<Variable*>(&IR[i]->GetTarget());

          varName = variableptr->GetNameWithoutSubscript();
          if (globalVariables_.find(varName) != globalVariables_.end()) {
            variableptr->SetSubscript(std::to_string(NewNameWithSubscript(varName)));
          } else{
            variableptr->SetSubscript("1");
          }
          break;
        case Instruction::kCall:
          variableptr = dynamic_cast<Variable*>(&IR[i]->GetOp1());

          varName = variableptr->GetNameWithoutSubscript();
          if (globalVariables_.find(varName) != globalVariables_.end()) {
            variableptr->SetSubscript(std::to_string(NewNameWithSubscript(varName)));
          }
          else {
            variableptr->SetSubscript("1");
          }
          break;
        default:
          break;
        }
        i++;
      }
      switch (IR[i]->GetInstruction().GetOpcode()) {
      case Instruction::kValueOfVariable:
        variableptr = dynamic_cast<Variable*>(&IR[i]->GetOp2());

        varName = variableptr->GetNameWithoutSubscript();
        variableptr->SetSubscript(std::to_string(CurrentNameWithSubscript(varName)));
        break;
      case Instruction::kAssignmentToVariable:
        variableptr = dynamic_cast<Variable*>(&IR[i]->GetTarget());

        varName = variableptr->GetNameWithoutSubscript();
        if (globalVariables_.find(varName) != globalVariables_.end()) {
          variableptr->SetSubscript(std::to_string(NewNameWithSubscript(varName)));
        }
        else {
          variableptr->SetSubscript("1");
        }
        break;
      case Instruction::kCall:
        variableptr = dynamic_cast<Variable*>(&IR[i]->GetOp1());

        varName = variableptr->GetNameWithoutSubscript();
        if (globalVariables_.find(varName) != globalVariables_.end()) {
          variableptr->SetSubscript(std::to_string(NewNameWithSubscript(varName)));
        }
        else {
          variableptr->SetSubscript("1");
        }
        break;
      default:
        break;
      }

      // 3rd case
      i = blockid;
      std::vector<int> cfgSuccessors = GetImmediateGraphSucessors(i,CFG);
      string currentValue;
      string realVar;
      string newVar;
      for (auto successor : cfgSuccessors) {
        i = successor;

        while (IR[i]->GetInstruction().GetOpcode() == Instruction::kPhiFunction) {
          variableptr = dynamic_cast<Variable*>(&IR[i]->GetOp1());

          currentValue = IR[i]->GetOp2().GetName();
          realVar = variableptr->GetNameWithoutSubscript();

          ssaName = realVar + std::to_string(CurrentNameWithSubscript(realVar));
          newVar = currentValue + " " + ssaName;

          if (!(currentValue.find(ssaName) != std::string::npos)) {
            IR[i]->GetOp2().SetName(newVar);
          }
          i++;
        }
      }
      cfgSuccessors.clear();

      // 4th case
      i = blockid;
      std::vector<int> treeSuccessors = GetImmediateTreeSucessors(i);
      for (auto successor : treeSuccessors) {
        RenameBlock(successor, IR, CFG);
      }
    }

    void Graph::AddToAssignmentLocations(string nameToBeInserted, int location)
    {
      AssignPoints newLocation;
      if (assignmentPoints_.size() == 0) {
        newLocation.name_ = nameToBeInserted;
        newLocation.blockLocations_.insert(location);
        assignmentPoints_.push_back(newLocation);
        return;
      }
      for (int i = 0; i < assignmentPoints_.size(); i++) {
        if (assignmentPoints_[i].name_ == nameToBeInserted) {
          assignmentPoints_[i].blockLocations_.insert(location);
          return;
        }
      }
      newLocation.name_ = nameToBeInserted; //not found
      newLocation.blockLocations_.insert(location);
      assignmentPoints_.push_back(newLocation);
    }

    void Graph::UpdateCFG(int offset){
      for (int i = 0; i < blockNums_.size(); i++) {
        blockNums_[i] = blockNums_[i] + offset;
      }
      for (int i = 1; i < idoms_.size(); i++) {
        idoms_[i] = idoms_[i] + offset;
      }
      for (int i = 0; i < blockNums_.size(); i++) {
        if (dominated_[i].size() > 0) {
          for (int j = 0; j < dominated_[i].size(); j++) {
            dominated_[i][j] = dominated_[i][j] + offset;
          }
        }
      }
      for (int i = 0; i < blockNums_.size(); i++) {
        if (domFrontier_[i].size() > 0) {
          for (int j = 0; j < domFrontier_[i].size(); j++) {
            domFrontier_[i][j] = domFrontier_[i][j] + offset;
          }
        }
      }
      if (assignmentPoints_.size() > 0) {
        for (int i = 0; i < assignmentPoints_.size(); i++) {
          for (auto location : assignmentPoints_[i].blockLocations_) {
            int original = location;
            assignmentPoints_[i].blockLocations_.erase(original);
            assignmentPoints_[i].blockLocations_.insert(original + 1);
          }
        }
      }
    }

    void Graph::acyclicPathsFromRoot(int desiredIndex, std::vector<std::shared_ptr<BasicBlock>> &CFG) {
      int index = startGraphBlockIndex_;
      std::vector<std::vector<int>> allPaths;
      std::vector<int> path;
      path.push_back(index);
      allPaths.push_back(path);

      for (int i = 0; i < CFG[index]->OutgoingEdges().size(); i++) {
        acyclicPathsFromRoot(desiredIndex, CFG[index]->OutgoingEdges()[i], allPaths, CFG);
      }
      findIdom(desiredIndex);
    }

    void Graph::acyclicPathsFromRoot(int desiredIndex, int index, std::vector<std::vector<int>> allPaths_param, std::vector<std::shared_ptr<BasicBlock>> &CFG) {
      std::vector<std::vector<int>> allPaths = allPaths_param;
      for (int i = 0; i < allPaths.size(); i++) {
        allPaths[i].push_back(index);
      }
      if (index == desiredIndex) {
        for (auto it : allPaths) {
          allPaths_.push_back(it);
        }
        return;
      }

      for (int i = 0; i < CFG[index]->OutgoingEdges().size(); i++) {
        bool found = false;
        for (auto it : allPaths) {
          if (std::find(it.begin(), it.end(), CFG[index]->OutgoingEdges()[i]) != it.end()) {
            found = true;
          }
        }
        if (!found) {
          acyclicPathsFromRoot(desiredIndex, CFG[index]->OutgoingEdges()[i], allPaths,CFG);
        }
      }
    }

    void Graph::findIdom(int index) {
      for (int i = allPaths_[0].size() - 2; i >= 0; i--) {
        bool found = true;
        for (auto it : allPaths_) {
          if (std::find(it.begin(), it.end(), allPaths_[0][i]) == it.end()) {
            found = false;
          }
        }
        if (found) {
          blockNums_.push_back(index);
          idoms_.push_back(allPaths_[0][i]);
          allPaths_.clear();
          return;
        }
      }
    }

    std::vector<int> Graph::DomFrontiers(int block)
    {
      std::vector<int> frontiers;
      int index;
      for (int i = 0; i < blockNums_.size(); i++) {
        if (blockNums_[i] == block) {
          index = i;
        }
      }
      for (auto frontier : domFrontier_[index]) {
        frontiers.push_back(frontier);
      }
      return frontiers;
    }

  }  // namespace backend
}  // namespace cs160
