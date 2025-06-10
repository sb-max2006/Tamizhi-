#include "tamizhi_pkg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PKG 16

static TamizhiPackage installed_pkgs[MAX_PKG];
static int installed_count = 0;

bool tamizhi_pkg_install(const char* pkg_name) {
    // Dummy implementation: Mark as installed if not already
    for (int i = 0; i < installed_count; ++i) {
        if (strcmp(installed_pkgs[i].name, pkg_name) == 0) {
            printf("Package '%s' already installed.\n", pkg_name);
            return false;
        }
    }
    if (installed_count >= MAX_PKG) {
        printf("Package limit reached.\n");
        return false;
    }
    TamizhiPackage pkg = { strdup(pkg_name), strdup("1.0.0"), strdup("Sample package"), true };
    installed_pkgs[installed_count++] = pkg;
    printf("Package '%s' installed.\n", pkg_name);
    return true;
}

bool tamizhi_pkg_remove(const char* pkg_name) {
    for (int i = 0; i < installed_count; ++i) {
        if (strcmp(installed_pkgs[i].name, pkg_name) == 0) {
            free(installed_pkgs[i].name);
            free(installed_pkgs[i].version);
            free(installed_pkgs[i].description);
            for (int j = i; j < installed_count-1; ++j) {
                installed_pkgs[j] = installed_pkgs[j+1];
            }
            installed_count--;
            printf("Package '%s' removed.\n", pkg_name);
            return true;
        }
    }
    printf("Package '%s' not found.\n", pkg_name);
    return false;
}

bool tamizhi_pkg_is_installed(const char* pkg_name) {
    for (int i = 0; i < installed_count; ++i) {
        if (strcmp(installed_pkgs[i].name, pkg_name) == 0)
            return true;
    }
    return false;
}

void tamizhi_pkg_list_installed(void) {
    printf("Installed Packages:\n");
    for (int i = 0; i < installed_count; ++i) {
        printf("  - %s (%s): %s\n", installed_pkgs[i].name, installed_pkgs[i].version, installed_pkgs[i].description);
    }
    if (installed_count == 0) {
        printf("  <none>\n");
    }
}

void tamizhi_pkg_list_available(void) {
    printf("Available Packages:\n");
    printf("  - core (1.0.0)\n");
    printf("  - math (1.0.0)\n");
    printf("  - string (1.0.0)\n");
    printf("  - stdio (1.0.0)\n");
}