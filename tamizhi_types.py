# tamizhi_types.py

from typing import Any

# 🔹 Tamizhi Value வகுப்பு: எல்லா runtime மதிப்புகளையும் நிர்வகிக்கிறது
class TamizhiValue:
    def __init__(self, value: Any):
        self.value = value

    def type_name(self) -> str:
        if self.value is None:
            return "இல்லை"
        elif isinstance(self.value, bool):
            return "தருமம்"
        elif isinstance(self.value, float):
            return "எண்"
        elif isinstance(self.value, str):
            return "உரை"
        elif isinstance(self.value, TamizhiFunction):
            return "நிரல்பாகம்"
        else:
            return "தெரியாத_வகை"

    def __str__(self):
        if self.value is None:
            return "இல்லை"
        elif isinstance(self.value, bool):
            return "சரி" if self.value else "தவறு"
        return str(self.value)

    def __repr__(self):
        return f"<{self.type_name()}: {self.value}>"

# 🔹 Tamizhi தரவுகள்: நேரடி வகைகள்
def make_number(val: float) -> TamizhiValue:
    return TamizhiValue(float(val))

def make_string(val: str) -> TamizhiValue:
    return TamizhiValue(val)

def make_boolean(val: bool) -> TamizhiValue:
    return TamizhiValue(val)

def make_null() -> TamizhiValue:
    return TamizhiValue(None)

# 🔹 Tamizhi Function வகை: later execution
class TamizhiFunction:
    def __init__(self, name: str, parameters: list, body: list, closure: dict):
        self.name = name
        self.parameters = parameters
        self.body = body
        self.closure = closure  # lexical scope

    def arity(self) -> int:
        return len(self.parameters)

    def __repr__(self):
        return f"<TamizhiFunction {self.name}>"
