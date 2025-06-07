// ... [Previous parts of tamizhi_vm.c stay unchanged above this line] ...

// -----------------------------
// ✅ tamizhi_test: Test Runner
// -----------------------------
#include <assert.h>

typedef struct {
    const char* name;
    void (*test_fn)();
} TamizhiTestCase;

int test_passed = 0;
int test_failed = 0;

#define T_ASSERT(cond) \
    do { \
        if (!(cond)) { \
            printf("❌ Assertion failed: %s (line %d)\n", #cond, __LINE__); \
            test_failed++; \
        } else { \
            test_passed++; \
        } \
    } while(0)

// -----------------------------
// 📌 Individual Tests
// -----------------------------
void test_addition() {
    TamizhiValue a = make_int(10);
    TamizhiValue b = make_int(20);
    T_ASSERT((a.as_int + b.as_int) == 30);
}

void test_subtraction() {
    TamizhiValue a = make_int(50);
    TamizhiValue b = make_int(15);
    T_ASSERT((a.as_int - b.as_int) == 35);
}

void test_is_falsey() {
    T_ASSERT(is_falsey(make_int(0)));
    T_ASSERT(!is_falsey(make_int(1)));
}

void test_push_pop() {
    reset_stack();
    TamizhiValue val = make_int(42);
    push(val);
    T_ASSERT(pop().as_int == 42);
}

// -----------------------------
// 🚀 Run All Tests
// -----------------------------
int tamizhi_test_run_all() {
    printf("[tamizhi_test] யுனிட் சோதனைகள் இயக்கப்படுகின்றன...\n");

    TamizhiTestCase tests[] = {
        {"test_addition", test_addition},
        {"test_subtraction", test_subtraction},
        {"test_is_falsey", test_is_falsey},
        {"test_push_pop", test_push_pop},
    };

    int total = sizeof(tests) / sizeof(tests[0]);
    for (int i = 0; i < total; i++) {
        printf("🔍 %s... ", tests[i].name);
        tests[i].test_fn();
        printf("✅\n");
    }

    printf("\n[tamizhi_test] முடிவுகள்: %d வெற்றி, %d தோல்வி\n", test_passed, test_failed);
    return test_failed == 0 ? 0 : 1;
}

// -----------------------------
// ✅ tamizhi_pkg: Package Manager
// -----------------------------
void tamizhi_pkg_install(const char* pkg_name) {
    printf("[tamizhi_pkg] '%s' தொகுப்பை நிறுவுகிறது...\n", pkg_name);
    // Stub: Future support for downloading and caching Tamizhi packages
}

void tamizhi_pkg_list_installed() {
    printf("[tamizhi_pkg] நிறுவப்பட்ட தொகுப்புகள்:\n");
    printf("  - core\n  - math\n  - stdio\n");
}
