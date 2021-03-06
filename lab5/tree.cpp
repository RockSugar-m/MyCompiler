#include "tree.h"

TreeNode::TreeNode(NodeType nodeType, int lineno)
{
    this->nodeType = nodeType;
    line = lineno;
    childNum = 0;
    for (int i = 0; i < MAXChildNum; i++)
    {
        child[i] = nullptr;
    }
}

void TreeNode::addChild(TreeNode *t)
{
    if (childNum < MAXChildNum)
    {
        child[childNum] = t;
        childNum++;
    }
}

void TreeNode::addSibling(TreeNode *t){
    if(!sibling){
        sibling=t;
    }else{
        TreeNode *temp = sibling;
        while (temp->sibling)
        {
            temp=temp->sibling;
        }
        temp->sibling=t;
    }
}

int NodeNum=0;
void TreeNode::genNodeId(){
    nodeID=NodeNum++;
    int i=0;
    while(child[i]){
        child[i]->genNodeId();
        i++;
    }
    if(sibling) sibling->genNodeId();
}

void TreeNode::printNodeInfo(){
    printf("@%-3d lineno:%-3d ", nodeID, line);
    switch (nodeType)
    {
    case NODE_PROG:
        printf("Program ");
        break;
    case NODE_STMT:
        printf("StmtType:%-17s ", StmtTypeTostring(stmtType).c_str());
        break;
    case NODE_TYPE:
        printf("TYPE:%-11s ", VarTypeTostring(varType).c_str());
        break;
    case NODE_CONST:
        printf("CONST:%-10s value:%-5s ", var_name.c_str(), str_val.c_str());
        break;
    case NODE_VAR:
        printf("VarType:%-5s VarName:%-10s ", VarTypeTostring(varType).c_str(), var_name.c_str());
        break;
    case NODE_BOOL:
        printf("BOOL   value:%-5s", str_val.c_str());
        break;
    case NODE_EXPR:
        printf("Expression ");
        break;
    case NODE_OP:
        printf("Operator:%-3s ", opTypeTostring(opType).c_str());
        break;
    case NODE_NULL:
        printf("null_node");
        break;
    default:
        break;
    }
}

void TreeNode::printAST(){
    printNodeInfo();
    printNodeConnection();
    printf("\n");
    int i=0;
    while(child[i]){
        child[i]->printAST();
        i++;
    }
    if(sibling) sibling->printAST();
}

void TreeNode::printNodeConnection(){
    if(childNum==0) return;
    printf("children: ");
    for(int i=0; i<childNum; i++){
        printf("@%d ", child[i]->nodeID);
        int j=0;
        TreeNode *tnode = child[i]->sibling;
        while (tnode)
        {
            printf("@%d ", tnode->nodeID);
            tnode=tnode->sibling;
        }
    }
}

string TreeNode::NodeTypeTostring(NodeType type){
        switch (type)
        {
        case NODE_CONST:
            return "NODE_CONST";
            break;
        case NODE_BOOL:
            return "NODE_BOOL";
            break;
        case NODE_VAR:
            return "NODE_VAR";
            break;
        case NODE_EXPR:
            return "NODE_EXPR";
            break;
        case NODE_TYPE:
            return "NODE_TYPE";
            break;
        case NODE_STMT:
            return "NODE_STMT";
            break;
        case NODE_PROG:
            return "NODE_PROG";
            break;
        case NODE_OP:
            return "NODE_OP";
            break;
        case NODE_NULL:
            return "NODE_NULL";
            break;
        default:
            return "";
            break;
        }
    }
string TreeNode::StmtTypeTostring(StmtType type){
        switch (type)
        {
        case STMT_IF:
            return "if";
            break;
        case STMT_WHILE:
            return "while";
            break;
        case STMT_DECL:
            return "declare";
            break;
        case STMT_ASSIGN:
            return "assign";
            break;
        case STMT_PRINTF:
            return "print";
            break;
        case STMT_SCANF:
            return "scanf";
            break;
        case STMT_FOR:
            return "for";
            break;
        case STMT_FORCONDITION:
            return "for_condition";
            break;
        case STMT_RETURN:
            return "return";
            break;
        case STMT_BREAK:
            return "break";
            break; 
        case STMT_COMPOUND:
            return "compound_stmt";
            break;
        default:
            return "";
            break;
        }
    }
string TreeNode::opTypeTostring(OpType type){
        switch (type)
        {
        case OP_EQUAL:
            return "==";
            break;
        case OP_GT:
            return ">";
            break;
        case OP_GTE:
            return ">=";
            break;
        case OP_LT:
            return "<";
            break;
        case OP_LTE:
            return "<=";
            break;
        case OP_NOTEQUAL:
            return "!=";
            break;
        case OP_LAND:
            return "&&";
            break;
        case OP_LOR:
            return "||";
            break;
        case OP_NOT:
            return "!";
            break;
        case OP_ADD:
            return "+";
            break;
        case OP_SADD:
            return "+";
            break;
        case OP_SUB:
            return "-";
            break;
        case OP_UMINUS:
            return "-";
            break;
        case OP_MUL:
            return "*";
            break;
        case OP_DIV:
            return "/";
            break;
        case OP_MOD:
            return "%";
            break;
        case OP_INC:
            return "++";
            break;
        case OP_DEC:
            return "--";
            break;
        case OP_ASSIGN:
            return "=";
            break;
        case OP_AASSIGN:
            return "+=";
            break;
        case OP_SASSIGN:
            return "-=";
            break;
        case OP_MASSIGN:
            return "*=";
            break;
        case OP_COMMA:
            return ",";
            break;
        case OP_ADDRO:
            return "&";
            break;
        default:
            return "";
            break;
        }
    }
string TreeNode::VarTypeTostring(VarType type){
        switch (type)
        {
        case VAR_INTEGER:
            return "int";
            break;
        case VAR_VOID:
            return "void";
            break;
        case VAR_CHAR:
            return "char";
            break;
        case VAR_STRING:
            return "string";
            break;
        default:
            return "";
            break;
        }
    }