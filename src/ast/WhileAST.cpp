#include "AST.h"
#include "WhileAST.h"
#include "CompoundAST.h"
#include "../visitors/CodegenVisitor.h"
#include "../visitors/ASTStringifier.h"

WhileAST::WhileAST(std::unique_ptr<AST> expr, std::unique_ptr<CompoundAST> body)
    : expr(std::move(expr)), body(std::move(body)) {}

WhileAST::WhileAST(const WhileAST& other)
    : expr(std::unique_ptr<AST>(other.expr->clone())),
      body(std::unique_ptr<CompoundAST>(dynamic_cast<CompoundAST*>(other.expr->clone()))) {}

llvm::Value* WhileAST::accept(CodegenVisitor& cg) 
{
    return cg.codegen(this);
}

std::string WhileAST::accept(ASTStringifier& sf, int tabs) 
{
    return sf.toString(this, tabs);
}

WhileAST* WhileAST::cloneImpl()
{
    return new WhileAST(*this);
}