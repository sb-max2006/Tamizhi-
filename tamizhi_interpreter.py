# tamizhi_interpreter.py

from typing import List
from tamizhi_ast import *
from tamizhi_runtime.py import Environment, create_global_environment
from tamizhi_types import TamizhiValue, make_null, make_boolean, make_number, make_string

class Interpreter:
    def __init__(self):
        self.environment = create_global_environment()

    # 🔸 Statements
    def interpret(self, statements: List[Stmt]):
        for stmt in statements:
            self._execute(stmt)

    def _execute(self, stmt: Stmt):
        if isinstance(stmt, VarDeclaration):
            value = self._evaluate(stmt.initializer)
            self.environment.define(stmt.name, value)
        elif isinstance(stmt, PrintStatement):
            value = self._evaluate(stmt.expression)
            print(str(value))
        elif isinstance(stmt, ExpressionStatement):
            self._evaluate(stmt.expression)
        elif isinstance(stmt, ReturnStatement):
            raise Exception(f"பின்கொடு இன்னும் செயல்படுத்தப்படவில்லை: {stmt.value}")
        elif isinstance(stmt, IfStatement):
            condition = self._evaluate(stmt.condition)
            if condition.value:
                self._execute(stmt.then_branch)
            elif stmt.else_branch:
                self._execute(stmt.else_branch)
        elif isinstance(stmt, WhileStatement):
            while self._evaluate(stmt.condition).value:
                self._execute(stmt.body)
        elif isinstance(stmt, Block):
            self._execute_block(stmt.statements, self.environment.create_child())
        elif isinstance(stmt, FunctionDeclaration):
            print(f"நிரல்பாகம் '{stmt.name}' செயல்படுத்தப்படவில்லை (TODO)")
        else:
            raise RuntimeError(f"அறியப்படாத கூற்று வகை: {stmt}")

    def _execute_block(self, statements: List[Stmt], env: Environment):
        previous = self.environment
        try:
            self.environment = env
            for stmt in statements:
                self._execute(stmt)
        finally:
            self.environment = previous

    # 🔸 Expressions
    def _evaluate(self, expr: Expr) -> TamizhiValue:
        if isinstance(expr, Literal):
            return TamizhiValue(expr.value)
        elif isinstance(expr, Variable):
            return self.environment.get(expr.name)
        elif isinstance(expr, Binary):
            left = self._evaluate(expr.left)
            right = self._evaluate(expr.right)
            return self._eval_binary(left, expr.operator, right)
        else:
            raise RuntimeError(f"அறியப்படாத வெளிப்பாடு வகை: {expr}")

    def _eval_binary(self, left: TamizhiValue, operator: str, right: TamizhiValue) -> TamizhiValue:
        if operator == "+":
            if isinstance(left.value, str) or isinstance(right.value, str):
                return make_string(str(left.value) + str(right.value))
            return make_number(left.value + right.value)
        elif operator == "-":
            return make_number(left.value - right.value)
        elif operator == "*":
            return make_number(left.value * right.value)
        elif operator == "/":
            return make_number(left.value / right.value)
        elif operator == "==":
            return make_boolean(left.value == right.value)
        elif operator == "!=":
            return make_boolean(left.value != right.value)
        elif operator == ">":
            return make_boolean(left.value > right.value)
        elif operator == "<":
            return make_boolean(left.value < right.value)
        else:
            raise RuntimeError(f"அறியப்படாத இயக்கி: {operator}")
