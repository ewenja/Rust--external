#ifndef memory_h
#define memory_h

#define WIN32_LEAN_AND_MEAN
#include <memory>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include <string>

class c_memory
{
private:
    HANDLE process_handle;
    uint32_t process_pid;
public:
    bool attach(const wchar_t* process_name) {
        PROCESSENTRY32 entry{ sizeof(PROCESSENTRY32) };

        HANDLE snap_shot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (snap_shot == INVALID_HANDLE_VALUE)
            return false;

        while (::Process32Next(snap_shot, &entry)) {
            if (!_wcsicmp(process_name, entry.szExeFile)) {
                process_pid = entry.th32ProcessID;
                process_handle = OpenProcess(PROCESS_ALL_ACCESS, false, process_pid);
                break;
            }
        }

        if (snap_shot)
            CloseHandle(snap_shot);

        return process_handle != 0;
    }

    bool running(const wchar_t* process_name) {
        PROCESSENTRY32 entry{ sizeof(PROCESSENTRY32) };

        HANDLE snap_shot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (snap_shot == INVALID_HANDLE_VALUE)
            return false;

        __int32 target_process_pid = 0;

        while (::Process32Next(snap_shot, &entry)) {
            if (!_wcsicmp(process_name, entry.szExeFile)) {
                target_process_pid = entry.th32ProcessID;
                break;
            }
        }

        if (snap_shot)
            CloseHandle(snap_shot);

        return target_process_pid != 0;
    }

    void detach() {
        if (process_handle)
        {
            CloseHandle(process_handle);
            process_handle = nullptr;
            process_pid = 0;
        }
    }

    uint64_t get_module_base(const wchar_t* module_name) {
        MODULEENTRY32 entry{ sizeof(MODULEENTRY32) };
        HANDLE snap_shot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, process_pid);

        if (snap_shot == INVALID_HANDLE_VALUE)
            return 0;

        while (::Module32Next(snap_shot, &entry)) {
            if (!_wcsicmp(module_name, entry.szModule)) {
                CloseHandle(snap_shot);
                return (uint64_t)entry.modBaseAddr;
                break;
            }
        }

        return 0;
    }

    bool read(uint64_t address, void* buffer, size_t size) {
        return ReadProcessMemory(process_handle, (LPCVOID)address, buffer, size, NULL);
    }

    template <typename T> T read(uint64_t address) {
        T buffer = { };
        ReadProcessMemory(process_handle, (LPCVOID)address, &buffer, sizeof(T), NULL);
        return buffer;
    }

    bool write(uint64_t address, void* buffer, size_t size) {
        return WriteProcessMemory(process_handle, (LPVOID)address, buffer, size, NULL);
    }

    template <typename T> bool write(uint64_t address, T buffer) {
        return write(address, &buffer, sizeof(T));
    }

    std::string read_string(uint64_t address) {
        char buffer[256] = { 0 };
        if (!read(address, buffer, sizeof(buffer)))
            return "";

        return std::string(buffer);
    }

    std::string read_string(uint64_t address, uint32_t size) {
        if (size == 0 || size > 4096)
            return "";

        std::vector<char> buffer(size, 0);
        if (!read(address, buffer.data(), size))
            return "";

        return std::string(buffer.data());
    }

    std::wstring read_wstring(uint64_t address) {
        wchar_t buffer[256] = { 0 };
        if (!read(address, buffer, sizeof(buffer)))
            return L"";

        return std::wstring(buffer);
    }

    std::wstring read_wstring(uint64_t address, uint32_t size) {
        if (size == 0 || size > 4096)
            return L"";

        std::vector<wchar_t> buffer(size, 0);
        if (!read(address, buffer.data(), size * sizeof(wchar_t)))
            return L"";

        return std::wstring(buffer.data());
    }
};

inline c_memory m;

#endif