# tamizhi_ast.py

from typing import List, Optional, Union

# 🔹 Base classes
class Expr:
    pass

class Stmt:
    pass

# 🔹 Expressions (மதிப்புகள்)

class Literal(Expr):
    def __init__(self, value: Union[str, float, bool, None]):
        self.value = value

    def __repr__(self):
        return f"Literal({self.value})"

class Variable(Expr):
    def __init__(self, name: str):
        self.name = name

    def __repr__(self):
        return f"Variable({self.name})"

class Binary(Expr):
    def __init__(self, left: Expr, operator: str, right: Expr):
        self.left = left
        self.operator = operator
        self.right = right

    def __repr__(self):
        return f"Binary({self.left}, '{self.operator}', {self.right})"

# 🔹 Statements (கூற்றுகள்)

class PrintStatement(Stmt):
    def __init__(self, expression: Expr):
        self.expression = expression

    def __repr__(self):
        return f"Print({self.expression})"

class VarDeclaration(Stmt):
    def __init__(self, name: str, initializer: Expr):
        self.name = name
        self.initializer = initializer

    def __repr__(self):
        return f"VarDeclaration({self.name}, {self.initializer})"

class FunctionDeclaration(Stmt):
    def __init__(self, name: str, parameters: List[str], body: List[Stmt]):
        self.name = name
        self.parameters = parameters
        self.body = body

    def __repr__(self):
        return f"Function({self.name}, params={self.parameters}, body={self.body})"

class ReturnStatement(Stmt):
    def __init__(self, value: Expr):
        self.value = value

    def __repr__(self):
        return f"Return({self.value})"

class IfStatement(Stmt):
    def __init__(self, condition: Expr, then_branch: Stmt, else_branch: Optional[Stmt] = None):
        self.condition = condition
        self.then_branch = then_branch
        self.else_branch = else_branch

    def __repr__(self):
        return f"If({self.condition}, then={self.then_branch}, else={self.else_branch})"

class WhileStatement(Stmt):
    def __init__(self, condition: Expr, body: Stmt):
        self.condition = condition
        self.body = body

    def __repr__(self):
        return f"While({self.condition}, do={self.body})"

class Block(Stmt):
    def __init__(self, statements: List[Stmt]):
        self.statements = statements

    def __repr__(self):
        return f"Block({self.statements})"

class ExpressionStatement(Stmt):
    def __init__(self, expression: Expr):
        self.expression = expression

    def __repr__(self):
        return f"ExprStmt({self.expression})"
