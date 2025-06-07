# Tamizhi Programming Language

**Tamizhi** என்பது தமிழ் அடிப்படையிலான, முழுமையான செயல்பாடுகளுடன் கூடிய, புதிய நிரல்மொழி ஆகும். இது toy language அல்ல. இது compile, run, link, format, test, மற்றும் package செய்யும் முழு சூழலுடன் வருகிறது.

---

## 💡 இலக்கம் (Vision)

* தமிழில் நிரலாக்கம் நவீனமயமாகவும், நடைமுறைக்கு ஏற்பவும் இருக்க வேண்டும்.
* ஏற்கனவே உள்ள நிரல்மொழிகளின் பலவீனங்களை சரி செய்யும் நோக்கத்துடன் உருவாக்கப்பட்டுள்ளது.

---

## 📁 கோப்பு அமைப்பு (File Structure)

```
tamizhi/
├── compiler/            # Compiler source
├── runtime/             # VM & Standard Library
├── linker/              # Linker component
├── errors/              # Error handling logic
├── pkg/                 # Package manager
├── test/                # Unit tests
├── tools/               # Formatter (tamizhi_fmt)
├── main.c               # Entry point
└── README.md
```

---

## ⚙️ Tamizhi கட்டமைப்பது எப்படி?

### 🔧 Build:

```sh
gcc -o tamizhi main.c tamizhi_vm.c tamizhi_compiler.c tamizhi_linker.c tamizhi_stdlib.c tamizhi_errors.c tamizhi_pkg.c
```

### ▶️ Execute:

```sh
./tamizhi examples/hello.tml
```

---

## 🧪 Unit Test இயக்கம்

```sh
./tamizhi_test
```

---

## 📦 Package Command:

```sh
tamizhi_pkg install <package>
tamizhi_pkg update
```

---

## 🧹 Formatter

```sh
tamizhi_fmt examples/hello.tml
```

---

## 🧑‍💻 உதாரண Tamizhi நிரல்

```tamizhi
எண் a = 10;
எண் b = 20;
அச்சிடு(a + b);
```

---

## 🔖 License

MIT License

Copyright (c) 2025 Sakthibala

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


---

## 🙏 (Contribution)

# Tamizhi Contribution Guidelines

நன்றி! நீங்கள் Tamizhi நிரல்மொழியில் பங்களிக்க விரும்புகிறீர்கள் என்றால், இது உங்கள் வழிகாட்டி:

---

## ✅ என்ன பங்களிக்கலாம்?

* Tamizhi மொழிக்கான புதிய அம்சங்கள்
* பிழை திருத்தங்கள் (bug fixes)
* வகுப்புகள், வரையறைகள், runtime மேம்பாடுகள்
* test case-கள்
* ஆவணப்படுத்தல் (documentation)
* localization & i18n

---

## 📦 Tamizhi அமைப்பை இயக்கு:

```bash
make build       # (அல்லது gcc-வுடன் compile)
./tamizhi         # நீங்கள் உருவாக்கிய நிரலை இயக்க
```

---

## 🔃 Pull Request வழிமுறை:

1. Fork செய்க
2. உங்கள் தனிப்பட்ட பிரிவில் மாற்றங்களைச் செய்க (feature/my-feature)
3. Commit செய்த பிறகு pull request அனுப்பவும்
4. Code review-க்கு பிறகு merge செய்யப்படும்

---

## ✏️ Code Style:

* Use consistent indentation (4 spaces)
* Variable names in Tamil or transliterated Latin (e.g., `nilai`, `azhagu_var`)
* Avoid macros unless absolutely necessary

---

## 📂 கோப்பு அமைப்பை மதிக்கவும்:

தனித்தனி நிரல்கள், header கோப்புகள், compiler/runtime பாகங்களை சீராக வைத்திருக்க வேண்டும்.

---

## 🧪 Test Case-கள்

* உங்கள் commit-க்கு test case சேர்க்கவும்
* `tamizhi_test` வழியாக பரிசோதிக்கவும்

---

## 🙋 உதவி தேவைப்படுகிறதா?

Issue tab-ல் உங்கள் கேள்விகளை பகிரலாம்!

---

**அனைத்து பங்களிப்புக்கும் நன்றி!** ❤️

---

## 🇮🇳 Made with ❤️ in Tamil



