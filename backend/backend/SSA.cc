// Copyright(c) 2018, Team Chant

#include "backend/SSA.h"

using std::cout;
using std::endl;


namespace cs160 {
  namespace backend {
    void ControlFlowGraph::CreateCFG() {
      int numStatements = virgin_IR_.size();
      for (int i = 0; i < numStatements; i++) { cfg_.push_back(std::move(std::make_shared<BasicBlock>())); }
      int trueGoto; // we use this for the conditionals, there is only 
      int falseGoto; // a true and a false branch statement
      int targetGoto; //we use this for the gotos
      for (int i = 0; i < virgin_IR_.size(); i++) {
        switch (virgin_IR_[i]->GetInstruction().GetOpcode()) {
        case Instruction::kLessThan:
        case Instruction::kLessThanEqualTo:
        case Instruction::kGreaterThan:
        case Instruction::kGreaterThanEqualTo:
        case Instruction::kEqualTo:
          trueGoto = virgin_IR_[i]->GetTarget().GetValue(); //true target is always in the same line
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
          targetGoto = virgin_IR_[i]->GetTarget().GetValue(); // the goto statement has a single unconditional branch instruction
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
        default:
          break;
        }
      }
      for (int i = 0; i < cfg_.size(); i++) { //second pass for detecting end of blocks that have no where to go
        if (cfg_[i]->IsBlockEnd() && cfg_[i]->OutgoingEdges().size() == 0 &&
          virgin_IR_[i]->GetInstruction().GetOpcode() != Instruction::kProgramEnd &&
          virgin_IR_[i]->GetInstruction().GetOpcode() != Instruction::kFuncEnd) {
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
          }
        }
        if (virgin_IR_[i]->GetInstruction().GetOpcode() == Instruction::kFuncBegin || virgin_IR_[i]->GetInstruction().GetOpcode() == Instruction::kProgramStart) {
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
    void ControlFlowGraph::PrintGraph() {
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
        virgin_IR_[i]->Print();
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
    void SSA::GenerateDomination() {
      for (int i = 0; i < cfg_.size(); i++) {
        if (cfg_[i]->IsBlockLeader() && cfg_[i]->IncomingEdges().size() == 0) {
          Dominance dom(cfg_, i, original_IR_);
          dom.BuildDomInfo();
          dom.FindDominatorFrontiers();
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
        dominators_[i].FindGlobalVariables();
      }
    }

    void SSA::InsertSSAFunctions() {
      for (int i = 0; i < dominators_.size(); i++) {
        dominators_[i].InsertSSA(original_IR_);
      }
    }
    void Dominance::BuildDomInfo() {
      blockNums_.push_back(startGraphBlockIndex_);
      idoms_.push_back(-1);
      for (auto it : cfg_[startGraphBlockIndex_]->OutgoingEdges()) {
        BuildDomInfo(it);
      }
      std::vector<int> children;
      for (int i = 0; i < blockNums_.size(); i++) {
        children.push_back(blockNums_[i]);
        FindChildrens(blockNums_[i], children);
        dominated_.push_back(children);
        children.clear();
      }
    }
    void Dominance::BuildDomInfo(int index) {
      acyclicPathsFromRoot(index);
      for (auto it : cfg_[index]->OutgoingEdges()) {
        if (std::find(blockNums_.begin(), blockNums_.end(), it) == blockNums_.end()) {
          BuildDomInfo(it);
        }
      }
    }

    void Dominance::FindChildrens(int parent, std::vector<int> &children) {
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

    void Dominance::FindDominatorFrontiers() {
      for (int i = 0; i < blockNums_.size(); i++) {
        std::vector<int> initialVector; //empty
        domFrontier_.push_back(initialVector);
        int root = blockNums_[i];
        std::vector<int> dominated = dominated_[i];
        for (auto dominatedNode : dominated) {
          std::vector<int> graphSuccessors = GetImmediateSucessors(dominatedNode);
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

    void Dominance::FindPhiFunctionPlacements(int Blockid, std::set<int> &locations){
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

    std::vector<int> Dominance::GetImmediateSucessors(int blockNum) {
      std::vector<int> sucessors;
      if (cfg_[blockNum]->OutgoingEdges().size() > 0) {
        for (auto outgoing : cfg_[blockNum]->OutgoingEdges()) {
          sucessors.push_back(outgoing);
        }
      }
      return sucessors;
    }

    void Dominance::PrintDominatorInfo() {
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

    void Dominance::FindGlobalVariables() {
      //get list of blocks
      //find varkill and UEVAR sets
      // for eacha ssignment in blocks add to variable list of where to put a potential phi function
      std::vector<int> blockIds;
      for (auto id : blockNums_) {
        blockIds.push_back(id);
      }
      //cout << "#BLOCK IDS for " << GetGraphId() << ": ";
      //for (auto ids : blockIds) {
       // cout << ids << ",";
      //}
      std::set<string> varKill;
      for (auto block : blockIds) {
        varKill.clear();
        string nameToBeAddedtoGlobal;
        string tobeKilled;
        AssignmentLocation killvar;
        int i = block;
        //cout << "\n#NEW BLOCK: " << block << endl;
        while (!cfg_[i]->IsBlockEnd()) {
          //original_IR_[i]->Print();
          //cout << endl;
          switch (original_IR_[i]->GetInstruction().GetOpcode()) {
          case Instruction::kValueOfVariable:
            nameToBeAddedtoGlobal = original_IR_[i]->GetOp2().GetName();
            //cout << "#Add Global =" << nameToBeAddedtoGlobal << endl;
            if (!(varKill.find(nameToBeAddedtoGlobal) != varKill.end())) {
              globalVariables_.insert(nameToBeAddedtoGlobal);
            }
            break;
          case Instruction::kAssignmentToVariable:
            tobeKilled = original_IR_[i]->GetTarget().GetName();
            //cout << "#VarAssignment =" << tobeKilled << endl;
            varKill.insert(tobeKilled);
            AddToAssignmentLocations(tobeKilled, block);
            break;
          case Instruction::kCall:
            tobeKilled = original_IR_[i]->GetOp1().GetName();
            //cout << "#VarAssignment =" << tobeKilled << endl;
            varKill.insert(tobeKilled);
            AddToAssignmentLocations(tobeKilled, block);
            break;
          default:
            break;
          }
          i++;
        }
        //original_IR_[i]->Print();
        //cout << endl;
        switch (original_IR_[i]->GetInstruction().GetOpcode()) {
        case Instruction::kValueOfVariable:
          nameToBeAddedtoGlobal = original_IR_[i]->GetOp2().GetName();
          //cout << "#Add Global =" << nameToBeAddedtoGlobal << endl;
          if (!(varKill.find(nameToBeAddedtoGlobal) != varKill.end())) {
            globalVariables_.insert(nameToBeAddedtoGlobal);
          }
          break;
        case Instruction::kAssignmentToVariable:
          tobeKilled = original_IR_[i]->GetTarget().GetName();
          //cout << "#VarAssignment =" << tobeKilled << endl;
          varKill.insert(tobeKilled);
          AddToAssignmentLocations(tobeKilled, block);
          break;
        case Instruction::kCall:
          tobeKilled = original_IR_[i]->GetOp1().GetName();
          //cout << "#VarAssignment =" << tobeKilled << endl;
          varKill.insert(tobeKilled);
          AddToAssignmentLocations(tobeKilled, block);
          break;
        default:
          break;
        }
      }
    }

    void Dominance::InsertSSA(std::vector<std::shared_ptr<StatementNode>> &IR) {
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
          FindPhiFunctionPlacements(location,phiFuncPlacements);
        }
        
        
        cout << endl;
        cout << "# Variable assignment for variable " << globalVar << " at:";
        for (auto location : locations) {
          cout << location << ",";
        }
       
        for (auto phiplacement : phiFuncPlacements) {
          InsertPhiFunctAt(globalVar, phiplacement,IR);
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
    }

    void cs160::backend::Dominance::InsertPhiFunctAt(string variable, int blockId, std::vector<std::shared_ptr<StatementNode>> &IR) {
      std::shared_ptr<StatementNode> newhead = std::make_shared< StatementNode>(
        make_unique<Label>(-1),
        make_unique<Variable>(variable),
        make_unique<Instruction>(Instruction::kPhiFunction),
        make_unique<Variable>(variable),
        make_unique<Variable>(variable));
      std::vector<std::shared_ptr<StatementNode>>::iterator iterator;
      iterator = IR.begin();
      IR.insert(iterator + blockId, std::move(newhead));
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
          if (gotoTarget >= insertIndex) {
            //cout << "goto " << IR[i]->GetTarget().GetValue();
            IR[i]->GetTarget().SetValue(gotoTarget+1);
          }
          break;
        default:
          break;
        }
      }

    }

    void Dominance::AddToAssignmentLocations(string nameToBeInserted, int location)
    {
      AssignmentLocation newLocation;
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

    void Dominance::acyclicPathsFromRoot(int desiredIndex) {
      int index = startGraphBlockIndex_;
      std::vector<std::vector<int>> allPaths;
      std::vector<int> path;
      path.push_back(index);
      allPaths.push_back(path);

      for (int i = 0; i < cfg_[index]->OutgoingEdges().size(); i++) {
        acyclicPathsFromRoot(desiredIndex, cfg_[index]->OutgoingEdges()[i], allPaths);
      }
      findIdom(desiredIndex);
    }

    void Dominance::acyclicPathsFromRoot(int desiredIndex, int index, std::vector<std::vector<int>> allPaths_param) {
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

      for (int i = 0; i < cfg_[index]->OutgoingEdges().size(); i++) {
        bool found = false;
        for (auto it : allPaths) {
          if (std::find(it.begin(), it.end(), cfg_[index]->OutgoingEdges()[i]) != it.end()) {
            found = true;
          }
        }
        if (!found) {
          acyclicPathsFromRoot(desiredIndex, cfg_[index]->OutgoingEdges()[i], allPaths);
        }
      }
    }

    void Dominance::findIdom(int index) {
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
    std::vector<int> Dominance::DomFrontiers(int block)
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
