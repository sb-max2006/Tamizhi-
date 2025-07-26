# tamizhi_main.py

import sys

from tamizhi_tokenizer import Tokenizer
from tamizhi_parser import Parser
from tamizhi_interpreter import Interpreter
from tamizhi_errors import TamizhiSyntaxError, TamizhiRuntimeError

def main():
    if len(sys.argv) != 2:
        print("பயன்பாடு: python tamizhi_main.py <பாதை/கோப்பு.tam>")
        sys.exit(1)

    filename = sys.argv[1]

    try:
        with open(filename, 'r', encoding='utf-8') as f:
            source_code = f.read()
    except FileNotFoundError:
        print(f"பிழை: கோப்பு '{filename}' காணவில்லை.")
        sys.exit(1)

    try:
        # 1️⃣ Tokenize
        tokenizer = Tokenizer(source_code)
        tokens = tokenizer.tokenize()

        # 2️⃣ Parse
        parser = Parser(tokens)
        statements = parser.parse()

        # 3️⃣ Interpret
        interpreter = Interpreter()
        interpreter.interpret(statements)

    except TamizhiSyntaxError as e:
        print(e)
    except TamizhiRuntimeError as e:
        print(e)
    except Exception as e:
        print(f"[திடீர் பிழை]: {e}")

if __name__ == "__main__":
    main()
