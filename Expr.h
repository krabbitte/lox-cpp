#ifndef LOX_EXPR_H
#define LOX_EXPR_H

class Expr {
public:
    virtual void accept(class Visitor *) = 0;
};

class Assign : public Expr {
public:
    void accept(Visitor *)
    Token name;
    Expr value;
    Assign(Token name, Expr value) {
        this.name = name;
        this.value = value;
    }
};

class Visitor {
public:
    virtual void visit(Assign *) = 0;
};



void Assign::accept(Visitor *e) {
    e->accept(this);
}

#endif //LOX_EXPR_H
