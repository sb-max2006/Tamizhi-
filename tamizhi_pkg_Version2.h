#ifndef TAMIZHI_PKG_H
#define TAMIZHI_PKG_H

#include <stdbool.h>

typedef struct TamizhiPackage {
    char* name;
    char* version;
    char* description;
    bool installed;
} TamizhiPackage;

// தொகுப்பு மேலாண்மை செயல்பாடுகள்
bool tamizhi_pkg_install(const char* pkg_name);
bool tamizhi_pkg_remove(const char* pkg_name);
bool tamizhi_pkg_is_installed(const char* pkg_name);
void tamizhi_pkg_list_installed(void);
void tamizhi_pkg_list_available(void);

#endif // TAMIZHI_PKG_H