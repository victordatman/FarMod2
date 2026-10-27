#include <windows.h>
#include <stdio.h>
#include <string.h>

typedef BOOL(WINAPI* GetFileVersionInfoA_t)(LPCSTR, DWORD, DWORD, LPVOID);
typedef BOOL(WINAPI* GetFileVersionInfoW_t)(LPCWSTR, DWORD, DWORD, LPVOID);
typedef BOOL(WINAPI* GetFileVersionInfoE_t)(LPCSTR, DWORD, DWORD, LPVOID);
typedef BOOL(WINAPI* GetFileVersionInfoByHandle_t)(int, LPVOID, LPVOID, int);
typedef BOOL(WINAPI* GetFileVersionInfoExA_t)(DWORD, LPCSTR, DWORD, DWORD, LPVOID);
typedef BOOL(WINAPI* GetFileVersionInfoExW_t)(DWORD, LPCWSTR, DWORD, DWORD, LPVOID);
typedef DWORD(WINAPI* GetFileVersionInfoSizeA_t)(LPCSTR, LPDWORD);
typedef DWORD(WINAPI* GetFileVersionInfoSizeW_t)(LPCWSTR, LPDWORD);
typedef DWORD(WINAPI* GetFileVersionInfoSizeE_t)(LPCSTR, LPDWORD);
typedef DWORD(WINAPI* GetFileVersionInfoSizeExA_t)(DWORD, LPCSTR, LPDWORD);
typedef DWORD(WINAPI* GetFileVersionInfoSizeExW_t)(DWORD, LPCWSTR, LPDWORD);
typedef DWORD(WINAPI* VerFindFileA_t)(DWORD, LPSTR, LPSTR, LPSTR, LPSTR, PUINT, LPSTR, PUINT);
typedef DWORD(WINAPI* VerFindFileW_t)(DWORD, LPWSTR, LPWSTR, LPWSTR, LPWSTR, PUINT, LPWSTR, PUINT);
typedef DWORD(WINAPI* VerInstallFileA_t)(DWORD, LPSTR, LPSTR, LPSTR, LPSTR, LPSTR, LPSTR, PUINT);
typedef DWORD(WINAPI* VerInstallFileW_t)(DWORD, LPWSTR, LPWSTR, LPWSTR, LPWSTR, LPWSTR, LPWSTR, PUINT);
typedef DWORD(WINAPI* VerLanguageNameA_t)(DWORD, LPSTR, DWORD);
typedef DWORD(WINAPI* VerLanguageNameW_t)(DWORD, LPWSTR, DWORD);
typedef BOOL(WINAPI* VerQueryValueA_t)(LPCVOID, LPCSTR, LPVOID*, PUINT);
typedef BOOL(WINAPI* VerQueryValueW_t)(LPCVOID, LPCWSTR, LPVOID*, PUINT);

GetFileVersionInfoA_t pGetFileVersionInfoA = NULL;
GetFileVersionInfoW_t pGetFileVersionInfoW = NULL;
GetFileVersionInfoE_t pGetFileVersionInfoE = NULL;
GetFileVersionInfoByHandle_t pGetFileVersionInfoByHandle = NULL;
GetFileVersionInfoExA_t pGetFileVersionInfoExA = NULL;
GetFileVersionInfoExW_t pGetFileVersionInfoExW = NULL;
GetFileVersionInfoSizeA_t pGetFileVersionInfoSizeA = NULL;
GetFileVersionInfoSizeW_t pGetFileVersionInfoSizeW = NULL;
GetFileVersionInfoSizeE_t pGetFileVersionInfoSizeE = NULL;
GetFileVersionInfoSizeExA_t pGetFileVersionInfoSizeExA = NULL;
GetFileVersionInfoSizeExW_t pGetFileVersionInfoSizeExW = NULL;
VerFindFileA_t pVerFindFileA = NULL;
VerFindFileW_t pVerFindFileW = NULL;
VerInstallFileA_t pVerInstallFileA = NULL;
VerInstallFileW_t pVerInstallFileW = NULL;
VerLanguageNameA_t pVerLanguageNameA = NULL;
VerLanguageNameW_t pVerLanguageNameW = NULL;
VerQueryValueA_t pVerQueryValueA = NULL;
VerQueryValueW_t pVerQueryValueW = NULL;

HMODULE hRealVersion = NULL;
BOOL mods_loaded = FALSE;

void show_error(const char* message) {
    MessageBoxA(NULL, message, "farmod2 - CRITICAL ERROR", MB_OK | MB_ICONERROR);
}

void show_info(const char* title, const char* message) {
    MessageBoxA(NULL, message, title, MB_OK | MB_ICONINFORMATION);
}

void load_system_version() {
    if (hRealVersion) return;
    char sys_path[MAX_PATH];
    GetSystemDirectoryA(sys_path, MAX_PATH);
    strcat(sys_path, "\\version.dll");
    hRealVersion = LoadLibraryExA(sys_path, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
    if (!hRealVersion) {
        show_error("Critical proxy error: Could not target real system version.dll!");
        return;
    }
    pGetFileVersionInfoA = (GetFileVersionInfoA_t)GetProcAddress(hRealVersion, "GetFileVersionInfoA");
    pGetFileVersionInfoW = (GetFileVersionInfoW_t)GetProcAddress(hRealVersion, "GetFileVersionInfoW");
    pGetFileVersionInfoE = (GetFileVersionInfoE_t)GetProcAddress(hRealVersion, "GetFileVersionInfoE");
    pGetFileVersionInfoByHandle = (GetFileVersionInfoByHandle_t)GetProcAddress(hRealVersion, "GetFileVersionInfoByHandle");
    pGetFileVersionInfoExA = (GetFileVersionInfoExA_t)GetProcAddress(hRealVersion, "GetFileVersionInfoExA");
    pGetFileVersionInfoExW = (GetFileVersionInfoExW_t)GetProcAddress(hRealVersion, "GetFileVersionInfoExW");
    pGetFileVersionInfoSizeA = (GetFileVersionInfoSizeA_t)GetProcAddress(hRealVersion, "GetFileVersionInfoSizeA");
    pGetFileVersionInfoSizeW = (GetFileVersionInfoSizeW_t)GetProcAddress(hRealVersion, "GetFileVersionInfoSizeW");
    pGetFileVersionInfoSizeE = (GetFileVersionInfoSizeE_t)GetProcAddress(hRealVersion, "GetFileVersionInfoSizeE");
    pGetFileVersionInfoSizeExA = (GetFileVersionInfoSizeExA_t)GetProcAddress(hRealVersion, "GetFileVersionInfoSizeExA");
    pGetFileVersionInfoSizeExW = (GetFileVersionInfoSizeExW_t)GetProcAddress(hRealVersion, "GetFileVersionInfoSizeExW");
    pVerFindFileA = (VerFindFileA_t)GetProcAddress(hRealVersion, "VerFindFileA");
    pVerFindFileW = (VerFindFileW_t)GetProcAddress(hRealVersion, "VerFindFileW");
    pVerInstallFileA = (VerInstallFileA_t)GetProcAddress(hRealVersion, "VerInstallFileA");
    pVerInstallFileW = (VerInstallFileW_t)GetProcAddress(hRealVersion, "VerInstallFileW");
    pVerLanguageNameA = (VerLanguageNameA_t)GetProcAddress(hRealVersion, "VerLanguageNameA");
    pVerLanguageNameW = (VerLanguageNameW_t)GetProcAddress(hRealVersion, "VerLanguageNameW");
    pVerQueryValueA = (VerQueryValueA_t)GetProcAddress(hRealVersion, "VerQueryValueA");
    pVerQueryValueW = (VerQueryValueW_t)GetProcAddress(hRealVersion, "VerQueryValueW");
}

__declspec(dllexport) BOOL WINAPI GetFileVersionInfoA(LPCSTR l, DWORD d1, DWORD d2, LPVOID lp) { load_system_version(); return pGetFileVersionInfoA(l, d1, d2, lp); }
__declspec(dllexport) BOOL WINAPI GetFileVersionInfoW(LPCWSTR l, DWORD d1, DWORD d2, LPVOID lp) { load_system_version(); return pGetFileVersionInfoW(l, d1, d2, lp); }
__declspec(dllexport) BOOL WINAPI GetFileVersionInfoE(LPCSTR l, DWORD d1, DWORD d2, LPVOID lp) { load_system_version(); return pGetFileVersionInfoE(l, d1, d2, lp); }
__declspec(dllexport) BOOL WINAPI GetFileVersionInfoByHandle(int h, LPVOID lp1, LPVOID lp2, int i) { load_system_version(); return pGetFileVersionInfoByHandle(h, lp1, lp2, i); }
__declspec(dllexport) BOOL WINAPI GetFileVersionInfoExA(DWORD d, LPCSTR l, DWORD d1, DWORD d2, LPVOID lp) { load_system_version(); return pGetFileVersionInfoExA(d, l, d1, d2, lp); }
__declspec(dllexport) BOOL WINAPI GetFileVersionInfoExW(DWORD d, LPCWSTR l, DWORD d1, DWORD d2, LPVOID lp) { load_system_version(); return pGetFileVersionInfoExW(d, l, d1, d2, lp); }
__declspec(dllexport) DWORD WINAPI GetFileVersionInfoSizeA(LPCSTR l, LPDWORD lp) { load_system_version(); return pGetFileVersionInfoSizeA(l, lp); }
__declspec(dllexport) DWORD WINAPI GetFileVersionInfoSizeW(LPCWSTR l, LPDWORD lp) { load_system_version(); return pGetFileVersionInfoSizeW(l, lp); }
__declspec(dllexport) DWORD WINAPI GetFileVersionInfoSizeE(LPCSTR l, LPDWORD lp) { load_system_version(); return pGetFileVersionInfoSizeE(l, lp); }
__declspec(dllexport) DWORD WINAPI GetFileVersionInfoSizeExA(DWORD d, LPCSTR l, LPDWORD lp) { load_system_version(); return pGetFileVersionInfoSizeExA(d, l, lp); }
__declspec(dllexport) DWORD WINAPI GetFileVersionInfoSizeExW(DWORD d, LPCWSTR l, LPDWORD lp) { load_system_version(); return pGetFileVersionInfoSizeExW(d, l, lp); }
__declspec(dllexport) DWORD WINAPI VerFindFileA(DWORD d, LPSTR l1, LPSTR l2, LPSTR l3, LPSTR lp1, PUINT p1, LPSTR lp2, PUINT p2) { load_system_version(); return pVerFindFileA(d, l1, l2, l3, lp1, p1, lp2, p2); }
__declspec(dllexport) DWORD WINAPI VerFindFileW(DWORD d, LPWSTR l1, LPWSTR l2, LPWSTR l3, LPWSTR lp1, PUINT p1, LPWSTR lp2, PUINT p2) { load_system_version(); return pVerFindFileW(d, l1, l2, l3, lp1, p1, lp2, p2); }
__declspec(dllexport) DWORD WINAPI VerInstallFileA(DWORD d, LPSTR l1, LPSTR l2, LPSTR l3, LPSTR l4, LPSTR l5, LPSTR lp, PUINT p) { load_system_version(); return pVerInstallFileA(d, l1, l2, l3, l4, l5, lp, p); }
__declspec(dllexport) DWORD WINAPI VerInstallFileW(DWORD d, LPWSTR l1, LPWSTR l2, LPWSTR l3, LPWSTR l4, LPWSTR l5, LPWSTR lp, PUINT p) { load_system_version(); return pVerInstallFileW(d, l1, l2, l3, l4, l5, lp, p); }
__declspec(dllexport) DWORD WINAPI VerLanguageNameA(DWORD d, LPSTR l, DWORD d2) { load_system_version(); return pVerLanguageNameA(d, l, d2); }
__declspec(dllexport) DWORD WINAPI VerLanguageNameW(DWORD d, LPWSTR l, DWORD d2) { load_system_version(); return pVerLanguageNameW(d, l, d2); }
__declspec(dllexport) BOOL WINAPI VerQueryValueA(LPCVOID p, LPCSTR l, LPVOID* lp, PUINT pu) { load_system_version(); return pVerQueryValueA(p, l, lp, pu); }
__declspec(dllexport) BOOL WINAPI VerQueryValueW(LPCVOID p, LPCWSTR l, LPVOID* lp, PUINT pu) { load_system_version(); return pVerQueryValueW(p, l, lp, pu); }

// Keep the module handles so eject can release exactly what inject loaded.
#define MAX_LOADED_MODS 128
static HMODULE loaded_mods[MAX_LOADED_MODS];
static size_t loaded_mod_count = 0;

typedef void (*ModCallback)(void);

void inject_mods() {
    if (mods_loaded) return;

    CreateDirectoryA(".\\mods", NULL);
    WIN32_FIND_DATAA file_data;
    HANDLE search_handle = FindFirstFileA(".\\mods\\*.dll", &file_data);
    if (search_handle == INVALID_HANDLE_VALUE) return;

    do {
        if (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;
        if (loaded_mod_count == MAX_LOADED_MODS) {
            show_error("Too many mods loaded (limit: 128).");
            break;
        }

        char full_path[MAX_PATH];
        int length = snprintf(full_path, sizeof(full_path),
                              ".\\mods\\%s", file_data.cFileName);
        if (length < 0 || (size_t)length >= sizeof(full_path)) continue;

        HMODULE module = LoadLibraryA(full_path);
        if (!module) continue;

        loaded_mods[loaded_mod_count++] = module;
        ModCallback init = (ModCallback)GetProcAddress(module, "objTM_init");
        if (init) init();
    } while (FindNextFileA(search_handle, &file_data));

    FindClose(search_handle);
    mods_loaded = (loaded_mod_count != 0);
}

void eject_mods() {
    if (loaded_mod_count == 0) {
        show_info("farmod2 - eject", "No loaded mods to eject.");
        mods_loaded = FALSE;
        return;
    }

    for (size_t i = loaded_mod_count; i > 0; --i) {
        HMODULE module = loaded_mods[i - 1];
        ModCallback shutdown = (ModCallback)GetProcAddress(module, "objTM_shutdown");
        if (!shutdown) {
            show_error("A mod has no shutdown export, eject cancelled to avoid unsafe unloading.");
            return;
        }
    }

    for (size_t i = loaded_mod_count; i > 0; --i) {
        HMODULE module = loaded_mods[i - 1];
        ModCallback shutdown = (ModCallback)GetProcAddress(module, "objTM_shutdown");
        shutdown();
        FreeLibrary(module);
        loaded_mods[i - 1] = NULL;
    }

    loaded_mod_count = 0;
    mods_loaded = FALSE;
    show_info("farmod2 - eject", "All tracked mods have been released.");
}

void list_mods() {
    WIN32_FIND_DATAA file_data;
    HANDLE search_handle = FindFirstFileA(".\\mods\\*.dll", &file_data);
    if (search_handle == INVALID_HANDLE_VALUE) {
        show_info("farmod2 - --mods", "mods folder is empty.");
        return;
    }
    char list_buf[2048] = "found mods:\n";
    do {
        strncat(list_buf, "- ", sizeof(list_buf) - strlen(list_buf) - 1);
        strncat(list_buf, file_data.cFileName, sizeof(list_buf) - strlen(list_buf) - 1);
        strncat(list_buf, "\n", sizeof(list_buf) - strlen(list_buf) - 1);
    } while (FindNextFileA(search_handle, &file_data));
    FindClose(search_handle);
    show_info("farmod2 - --mods", list_buf);
}
void parse_command(const char* cmd) {
    if (strstr(cmd, "--version")) {
        show_info("farmod2 --version", "farmod2 engine loader\nversion: 1.0.0\nbuild: 32-bit (dunia compatible)\nauthor: objTM");
    } else if (strstr(cmd, "--mods")) {
        list_mods();
    } else if (strstr(cmd, "inject")) {
        inject_mods();
    } else if (strstr(cmd, "eject")) {
        eject_mods();
    } else if (strlen(cmd) > 1) {
        char unknown_buf[256];
        snprintf(unknown_buf, sizeof(unknown_buf), "unknown command: %s\nvalid args: --version, --mods, inject, eject", cmd);
        show_error(unknown_buf);
    }
}
DWORD WINAPI mod_thread(LPVOID param) {
    MessageBoxA(
        NULL, 
        "Thank you for using Far Mod 2. We hope you have as much fun playing your mods as we had coding it! \n \nBetter than malaria.", 
        "Far Mod 2", 
        MB_OK | MB_ICONINFORMATION
    );
    Sleep(3000);
    inject_mods();
    char cmd_file[] = ".\\farmod2.txt";
    while (TRUE) {
        Sleep(500);
        FILE* f = fopen(cmd_file, "r");
        if (f) {
            char cmd_line[256] = {0};
            if (fgets(cmd_line, sizeof(cmd_line), f)) {
                cmd_line[strcspn(cmd_line, "\r\n")] = 0;
                fclose(f);
                parse_command(cmd_line);
                DeleteFileA(cmd_file);
            } else {
                fclose(f);
            }
        }
    }
    return 0;
}
BOOL APIENTRY DllMain(HMODULE mod, DWORD reason, LPVOID res) {
    if (reason == DLL_PROCESS_ATTACH) {
        load_system_version();
        CreateThread(NULL, 0, mod_thread, NULL, 0, NULL);
    }
    return TRUE;
}
