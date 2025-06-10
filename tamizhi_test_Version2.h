#ifndef TAMIZHI_TEST_H
#define TAMIZHI_TEST_H

// Tamizhi Unit Test Framework (Minimal)
typedef struct {
    const char* name;
    void (*test_fn)();
} TamizhiTestCase;

void tamizhi_test_assert(int condition, const char* msg, int line);
void tamizhi_test_run_all();

#endif // TAMIZHI_TEST_H