# tamizhi_errors.py

class TamizhiError(Exception):
    """மூல Tamizhi பிழை வகை"""
    pass

class TamizhiSyntaxError(TamizhiError):
    def __init__(self, message: str, line: int = -1, column: int = -1):
        self.message = message
        self.line = line
        self.column = column

    def __str__(self):
        location = f" (வரி {self.line}, நெடுவரி {self.column})" if self.line >= 0 else ""
        return f"[தொகுப்புப் பிழை]{location}: {self.message}"

class TamizhiRuntimeError(TamizhiError):
    def __init__(self, message: str):
        self.message = message

    def __str__(self):
        return f"[இயக்கப் பிழை]: {self.message}"

class ReturnException(Exception):
    """நிரல்பாகங்களில் 'பின்கொடு' கட்டளையை செயல்படுத்த பயன்படுத்தப்படும்"""
    def __init__(self, value):
        self.value = value
