#include "tamizhi_test.h"
#include <stdio.h>

static int test_passed = 0;
static int test_failed = 0;

void tamizhi_test_assert(int condition, const char* msg, int line) {
    if (!condition) {
        printf("❌ Assertion failed at line %d: %s\n", line, msg);
        test_failed++;
    } else {
        test_passed++;
    }
}

// Example test cases
void test_example_addition() {
    int a = 10, b = 20;
    tamizhi_test_assert((a + b) == 30, "a + b == 30", __LINE__);
}

void test_example_strcmp() {
    tamizhi_test_assert(strcmp("abc", "abc") == 0, "strcmp equality", __LINE__);
}

void tamizhi_test_run_all() {
    printf("[tamizhi_test] யுனிட் சோதனைகள் இயக்கப்படுகின்றன...\n");
    TamizhiTestCase tests[] = {
        {"Addition", test_example_addition},
        {"String Compare", test_example_strcmp},
    };
    int total = sizeof(tests)/sizeof(tests[0]);
    for (int i = 0; i < total; ++i) {
        printf("🔍 %s... ", tests[i].name);
        tests[i].test_fn();
        printf("✅\n");
    }
    printf("\n[tamizhi_test] முடிவுகள்: %d வெற்றி, %d தோல்வி\n", test_passed, test_failed);
}
