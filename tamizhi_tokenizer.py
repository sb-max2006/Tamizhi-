# tamizhi_tokenizer.py

import re
from typing import List, Optional

# 🔸 ஒவ்வொரு Token இன் வகையை வரையறுக்கின்றோம்
class TokenType:
    IDENTIFIER = "IDENTIFIER"
    NUMBER = "NUMBER"
    STRING = "STRING"
    KEYWORD = "KEYWORD"
    SYMBOL = "SYMBOL"
    EOF = "EOF"

# 🔸 Tamizhi மொழிக்கான முக்கிய குறியீட்டு வார்த்தைகள்
TAMIZHI_KEYWORDS = {
    "ஆக": "let",         # let a = 5
    "நிரல்பாகம்": "function",
    "பின்கொடு": "return",
    "ஆனால்": "else",
    "ஆனால்_இல்லை": "elif",
    "ஆகில்": "if",
    "வரை": "while",
    "பதிப்பி": "print",
    "உள்ளீடு": "input",
    "சரி": "true",
    "தவறு": "false",
    "இல்லை": "null"
}

# 🔸 Token வகுப்புகள்
class Token:
    def __init__(self, type_: str, value: str, line: int, column: int):
        self.type = type_
        self.value = value
        self.line = line
        self.column = column

    def __repr__(self):
        return f"Token({self.type}, {self.value}, Line: {self.line}, Col: {self.column})"

# 🔸 உரையை Tokenகளாக மாற்றும் தொகுப்பான்
class Tokenizer:
    def __init__(self, source: str):
        self.source = source
        self.position = 0
        self.line = 1
        self.column = 1
        self.tokens: List[Token] = []

    def tokenize(self) -> List[Token]:
        while not self._is_at_end():
            self._skip_whitespace()
            start_pos = self.position
            char = self._peek()

            if char.isalpha() or self._is_tamil_letter(char):
                self._identifier_or_keyword()
            elif char.isdigit():
                self._number()
            elif char == '"':
                self._string()
            elif char in "+-*/=(){}<>!,:;":
                self._symbol()
            else:
                self._error(f"அறியப்படாத எழுத்து: '{char}'")
                self._advance()
        
        self.tokens.append(Token(TokenType.EOF, "", self.line, self.column))
        return self.tokens

    def _is_tamil_letter(self, char: str) -> bool:
        return '\u0B80' <= char <= '\u0BFF'

    def _identifier_or_keyword(self):
        start_line, start_col = self.line, self.column
        start = self.position
        while not self._is_at_end() and (self._peek().isalnum() or self._is_tamil_letter(self._peek()) or self._peek() == "_"):
            self._advance()
        value = self.source[start:self.position]
        token_type = TokenType.KEYWORD if value in TAMIZHI_KEYWORDS else TokenType.IDENTIFIER
        self.tokens.append(Token(token_type, value, start_line, start_col))

    def _number(self):
        start_line, start_col = self.line, self.column
        start = self.position
        while not self._is_at_end() and self._peek().isdigit():
            self._advance()
        self.tokens.append(Token(TokenType.NUMBER, self.source[start:self.position], start_line, start_col))

    def _string(self):
        start_line, start_col = self.line, self.column
        self._advance()  # skip opening "
        start = self.position
        while not self._is_at_end() and self._peek() != '"':
            if self._peek() == "\n":
                self.line += 1
                self.column = 1
            self._advance()
        if self._is_at_end():
            self._error("மூடிய தொடக்கம் இல்லாத எழுத்து வரி (Unterminated string)")
            return
        value = self.source[start:self.position]
        self._advance()  # skip closing "
        self.tokens.append(Token(TokenType.STRING, value, start_line, start_col))

    def _symbol(self):
        start_line, start_col = self.line, self.column
        value = self._advance()
        self.tokens.append(Token(TokenType.SYMBOL, value, start_line, start_col))

    def _skip_whitespace(self):
        while not self._is_at_end() and self._peek().isspace():
            if self._peek() == "\n":
                self.line += 1
                self.column = 1
            else:
                self.column += 1
            self.position += 1

    def _peek(self) -> str:
        return self.source[self.position] if not self._is_at_end() else '\0'

    def _advance(self) -> str:
        char = self.source[self.position]
        self.position += 1
        self.column += 1
        return char

    def _is_at_end(self) -> bool:
        return self.position >= len(self.source)

    def _error(self, message: str):
        print(f"[தொகுப்பு பிழை] வரி {self.line}, நெடுவரி {self.column}: {message}")

# 🔸 சோதனைக்கு உதாரணம்
if __name__ == "__main__":
    code = '''
    ஆக x = 10
    பதிப்பி "வணக்கம்"
    ஆகில் x > 5:
        பதிப்பி "x பெரியது"
    '''
    tokenizer = Tokenizer(code)
    tokens = tokenizer.tokenize()
    for tok in tokens:
        print(tok)
