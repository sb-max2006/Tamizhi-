# tamizhi_runtime.py

from typing import Optional, Dict
from tamizhi_types import TamizhiValue, TamizhiFunction

# 🔹 சூழ்நிலை வகுப்பு (Environment)
class Environment:
    def __init__(self, parent: Optional['Environment'] = None):
        self.values: Dict[str, TamizhiValue] = {}
        self.parent = parent

    def define(self, name: str, value: TamizhiValue):
        self.values[name] = value
        # print(f"[DEF] {name} = {value}")

    def assign(self, name: str, value: TamizhiValue):
        if name in self.values:
            self.values[name] = value
        elif self.parent:
            self.parent.assign(name, value)
        else:
            raise RuntimeError(f"மாறி '{name}' வரையறுக்கப்படவில்லை.")

    def get(self, name: str) -> TamizhiValue:
        if name in self.values:
            return self.values[name]
        elif self.parent:
            return self.parent.get(name)
        else:
            raise RuntimeError(f"மாறி '{name}' காணப்படவில்லை.")

    def has(self, name: str) -> bool:
        if name in self.values:
            return True
        elif self.parent:
            return self.parent.has(name)
        return False

    def create_child(self) -> 'Environment':
        return Environment(parent=self)

# 🔹 உள்ளமைக்கப்பட்ட நுண்ணறிவு உதவிகள்
def create_global_environment() -> Environment:
    env = Environment()
    # Built-in constants or functions can be added here later
    return env
