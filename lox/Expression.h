#include<memory>
#include"Token.h"

#pragma once

struct Expr {
    virtual ~Expr() = default;
};

struct BinaryExpr : Expr {
    std::unique_ptr<Expr> left;
    Token op;
    std::unique_ptr<Expr> right;
};

struct Grouping : Expr {
    std::unique_ptr<Expr> expression;
};

struct Literal : Expr {
    LoxValue value;
};

struct Unary : Expr {
    Token op;
    std::unique_ptr<Expr> right;
};

