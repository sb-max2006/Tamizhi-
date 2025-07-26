# tamizhi_parser.py

from typing import List, Optional
from tamizhi_tokenizer import Token, TokenType

# 🔸 AST நொடிகள் (nodes) import செய்யப்படுவதாக later பாகத்தில் இருப்பது (tamizhi_ast.py)
from tamizhi_ast import *

class ParseError(Exception):
    pass

class Parser:
    def __init__(self, tokens: List[Token]):
        self.tokens = tokens
        self.current = 0

    def parse(self) -> List[Stmt]:
        statements = []
        while not self._is_at_end():
            stmt = self._declaration()
            if stmt:
                statements.append(stmt)
        return statements

    # 🔹 Statements parsing
    def _declaration(self) -> Optional[Stmt]:
        try:
            if self._match("KEYWORD") and self._previous().value == "ஆக":
                return self._var_declaration()
            elif self._check_keyword("நிரல்பாகம்"):
                return self._function_declaration()
            else:
                return self._statement()
        except ParseError as e:
            self._synchronize()
            return None

    def _var_declaration(self) -> Stmt:
        name = self._consume("IDENTIFIER", "பெயருள்ள மாறி எதிர்பார்க்கப்படுகிறது.")
        self._consume("SYMBOL", "=", "=")
        expr = self._expression()
        return VarDeclaration(name.value, expr)

    def _function_declaration(self) -> Stmt:
        self._advance()  # skip "நிரல்பாகம்"
        name = self._consume("IDENTIFIER", "நிரல்பாகத்திற்கு பெயர் தேவை.")
        self._consume("SYMBOL", "(", "(")
        parameters = []
        if not self._check("SYMBOL", ")"):
            while True:
                param = self._consume("IDENTIFIER", "அளவுரு பெயர் தேவை.")
                parameters.append(param.value)
                if not self._match_symbol(","):
                    break
        self._consume("SYMBOL", ")", ")")
        body = self._block()
        return FunctionDeclaration(name.value, parameters, body)

    def _statement(self) -> Stmt:
        if self._check_keyword("பதிப்பி"):
            return self._print_statement()
        elif self._check_keyword("பின்கொடு"):
            return self._return_statement()
        elif self._check_keyword("ஆகில்"):
            return self._if_statement()
        elif self._check_keyword("வரை"):
            return self._while_statement()
        elif self._check("SYMBOL", "{"):
            return Block(self._block())
        else:
            return self._expression_statement()

    def _print_statement(self) -> Stmt:
        self._advance()  # skip "பதிப்பி"
        value = self._expression()
        return PrintStatement(value)

    def _return_statement(self) -> Stmt:
        self._advance()
        expr = self._expression()
        return ReturnStatement(expr)

    def _if_statement(self) -> Stmt:
        self._advance()
        condition = self._expression()
        self._consume("SYMBOL", ":", ":")
        then_branch = self._statement()
        return IfStatement(condition, then_branch)

    def _while_statement(self) -> Stmt:
        self._advance()
        condition = self._expression()
        self._consume("SYMBOL", ":", ":")
        body = self._statement()
        return WhileStatement(condition, body)

    def _expression_statement(self) -> Stmt:
        expr = self._expression()
        return ExpressionStatement(expr)

    def _block(self) -> List[Stmt]:
        statements = []
        self._consume("SYMBOL", "{", "{")
        while not self._check("SYMBOL", "}") and not self._is_at_end():
            stmt = self._declaration()
            if stmt:
                statements.append(stmt)
        self._consume("SYMBOL", "}", "}")
        return statements

    # 🔹 Expression parsing (placeholder)
    def _expression(self) -> Expr:
        return self._primary()

    def _primary(self) -> Expr:
        if self._match("NUMBER"):
            return Literal(float(self._previous().value))
        elif self._match("STRING"):
            return Literal(self._previous().value)
        elif self._match("KEYWORD") and self._previous().value in ("சரி", "தவறு", "இல்லை"):
            value = self._previous().value
            val = True if value == "சரி" else False if value == "தவறு" else None
            return Literal(val)
        elif self._match("IDENTIFIER"):
            return Variable(self._previous().value)
        else:
            raise self._error(self._peek(), "மதிப்பொன்றை எதிர்பார்க்கிறது.")

    # 🔹 Token helper methods
    def _match(self, type_: str) -> bool:
        if self._check(type_):
            self._advance()
            return True
        return False

    def _match_symbol(self, symbol: str) -> bool:
        return self._match("SYMBOL") and self._previous().value == symbol

    def _check(self, type_: str, value: Optional[str] = None) -> bool:
        if self._is_at_end():
            return False
        token = self._peek()
        if token.type != type_:
            return False
        if value is not None and token.value != value:
            return False
        return True

    def _check_keyword(self, word: str) -> bool:
        return self._check("KEYWORD", word)

    def _consume(self, type_: str, message: str, value: Optional[str] = None) -> Token:
        if self._check(type_, value):
            return self._advance()
        raise self._error(self._peek(), message)

    def _advance(self) -> Token:
        if not self._is_at_end():
            self.current += 1
        return self._previous()

    def _previous(self) -> Token:
        return self.tokens[self.current - 1]

    def _peek(self) -> Token:
        return self.tokens[self.current]

    def _is_at_end(self) -> bool:
        return self._peek().type == TokenType.EOF

    def _error(self, token: Token, message: str) -> ParseError:
        print(f"[பிழை] வரி {token.line}, நெடுவரி {token.column}: {message}")
        return ParseError(message)

    def _synchronize(self):
        self._advance()
        while not self._is_at_end():
            if self._previous().type == "SYMBOL" and self._previous().value == ";":
                return
            if self._peek().type == "KEYWORD":
                return
            self._advance()
