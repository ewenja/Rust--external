#ifndef decryption_h
#define decryption_h

#include <include.h>

namespace decryptions {
    inline uint64_t Il2cppGetHandle(int32_t ObjectHandleID) {
        uint64_t index = ObjectHandleID >> 3;
        uint64_t offset = (ObjectHandleID & 7) - 1;
        uint64_t baseAddr = globals::game_assembly + offsets::il2cpp_handle_base + offset * 0x28;
        uint32_t limit = m.read<uint32_t>(baseAddr + 0x10);

        if (index >= limit) return 0;

        uintptr_t objAddr = m.read<uintptr_t>(baseAddr);
        if (!objAddr) return 0;

        uint32_t bitMask = m.read<uint32_t>(objAddr + ((index >> 5) << 2));
        if (!(bitMask & (1 << (index & 0x1f)))) return 0;

        uintptr_t ObjectArray = m.read<uintptr_t>(baseAddr + 0x8) + (index << 3);
        return m.read<uint8_t>(baseAddr + 0x14) > 1 ? m.read<uintptr_t>(ObjectArray) : ~m.read<uint32_t>(ObjectArray);
    }

    inline uint64_t decrypt_base_networkable(uint64_t base_networkable) {
        signed __int64* v4; // rdx
        int v5; // r8d
        int v6; // eax
        unsigned int v7; // eax
        signed __int64 v23; // [rsp+20h] [rbp-28h] BYREF

        v4 = &v23;
        v23 = m.read<uint64_t>(base_networkable + 24);
        v5 = 2;
        do
        {
            v6 = *(uint32_t*)v4;
            v4 = (signed __int64*)((char*)v4 + 4);
            v7 = (((v6 - 1018039150) << 25) | ((unsigned int)(v6 - 1018039150) >> 7)) + 796537487;
            *((uint32_t*)v4 - 1) = (v7 << 19) | (v7 >> 13);
            --v5;
        } while (v5);

        return Il2cppGetHandle(v23);
    }

    inline uint64_t decrypt_base_networkable_list(uint64_t base_networkable_list) {
        signed __int64* v4; // rdx
        int v5; // r8d
        int v6; // eax
        signed __int64 v22; // [rsp+20h] [rbp-28h] BYREF

        v4 = &v22;
        v22 = m.read<uint64_t>(base_networkable_list + 24);
        v5 = 2;
        do
        {
            v6 = *(uint32_t*)v4;
            v4 = (signed __int64*)((char*)v4 + 4);
            *((uint32_t*)v4 - 1) = ((4 * (v6 - 2071726037)) | ((unsigned __int64)(unsigned int)(v6 - 2071726037) >> 30))
                + 302687980;
            --v5;
        } while (v5);

        return Il2cppGetHandle(v22);
    }

    inline uint64_t decrypt_player_eyes(uint64_t player_eyes) {
        __int64* v4; // rdx
        int v5; // r8d
        int v6; // eax
        int v7; // ecx
        __int64 v21; // [rsp+20h] [rbp-18h] BYREF

        v4 = &v21;
        v21 = m.read<uint64_t>(player_eyes + 24);
        v5 = 2;
        do
        {
            v6 = *(uint32_t*)v4;
            v7 = *((unsigned __int8*)v4 + 3);
            v4 = (__int64*)((char*)v4 + 4);
            *((uint32_t*)v4 - 1) = ((((v6 << 8) | v7) + 20555843) ^ 0xF09AA6DE) - 1374065269;
            --v5;
        } while (v5);

		return Il2cppGetHandle(v21);
    }

    inline uint64_t decrypt_player_inventory(uint64_t player_inventory) {
        signed __int64* v4; // rdx
        int v5; // r8d
        int v6; // eax
        unsigned int v7; // ecx
        signed __int64 v24; // [rsp+20h] [rbp-28h] BYREF

        v4 = &v24;
		v24 = m.read<uint64_t>(player_inventory + 24);
        v5 = 2;
        do
        {
            v6 = *(uint32_t*)v4;
            v7 = *((unsigned __int16*)v4 + 1);
            v4 = (signed __int64*)((char*)v4 + 4);
            *((uint32_t*)v4 - 1) = (((((v6 << 16) | v7) - 1254262744) << 10) | ((((v6 << 16) | v7) - 1254262744) >> 22))
                + 459864355;
            --v5;
        } while (v5);

        return Il2cppGetHandle(v24);
    }

    inline __int64 decrypt_cl_active_item(uint64_t cl_active_item_address) {
        int* v1; // rax
        int v2; // r8d
        unsigned int v3; // edx
        int v4; // ecx
        __int64 v5; // [rsp+0h] [rbp-18h] BYREF

        v1 = (int*)&v5;
        v2 = 2;
        v5 = cl_active_item_address;
        do
        {
            v3 = *v1;
            v4 = *v1++;
            *(v1 - 1) = (((((v4 << 9) | (v3 >> 23)) + 2047545125) << 10) | ((((v4 << 9) | (v3 >> 23)) + 2047545125) >> 22)) ^ 0x7AD509E9;
            --v2;
        } while (v2);

        return v5;
    }
}


#endif