#ifndef offset_h
#define offset_h

#include <include.h>

using offset = const uint32_t;

namespace offsets {
    offset il2cpp_handle_base = 0xD24D990;
    offset base_networkable = 0xCEE2CE0;
    offset base_camera = 0xCEE5388;
    offset tod_sky = 0xCF85138;

    namespace base_networkable_class {
        offset static_fields = 0xB8;
        offset wrapper_fields = 0x38LL;
        offset parent_static_fields = 0x10;
        offset entity = 0x18;
    }

    namespace entity_list {
        offset array = 0x10;
        offset size = 0x18;
    }

    namespace base_camera_class {
        offset static_fields = 0xB8;
        offset wrapper_class = 0x90LL;
        offset parent_static_fields = 0x10;
        offset matrix = 0x30c;
        offset position = 0x454;
    }

    namespace tod_ambient_parameters {
        offset mode = 0x10; // public TOD_AmbientType
        offset Saturation = 0x14; // public float
        offset UpdateInterval = 0x18; // public float
    }

    namespace tod_sky_class {
        offset static_fields = 0xB8;
        offset wrapper_class = 0x78LL; // instances
        offset parent_static_fields = 0x10;
        offset TOD_AmbientParameters = 0x68;

        namespace ambient_params {
            offset update_int = 0x18; // public float UpdateInterval;
        }

        offset TOD_CycleParameters = 0x10; // public TOD_CycleParameters Cycle;
        namespace cycle_params {
            offset time = 0x10;
        }
    }

    namespace base_entity {
        offset bounds = 0xA0; // public Bounds bounds
        offset model = 0xC8; // Public Model model
    }

    namespace base_combat_entity {
        offset lifestate = 0x234; // public BaseCombatEntity.LifeState lifestate
        offset _health = 0x23C; // float
        offset _maxHealth = 0x240; // float
    }

    namespace base_player {
        offset currentTeam = 0x450; // unsigned long
        offset playerFlags = 0x578; // public BasePlayer.PlayerFlags playerFlags
        offset playerModel = 0x5A0; // public PlayerModel < obfuscated name >
        offset inventoryValue = 0x2A8; // private encrypted_value<PlayerInventory> < obfuscated name >
        offset clActiveItem = 0x480; // private encrypted_value< < random class name ( unsigned long ) > > < obfuscated name >
        offset _displayName = 0x2B0; // protected string < obfuscated name >
        offset eyesValue = 0x330; // private encrypted_value<PlayerEyes> < obfuscated name >
        offset input = 0x5B8; // public PlayerInput < obfuscated name >
        offset movement = 0x490; // public BaseMovement < obfuscated name >
    }

    namespace player_model {
        offset position = 0x1D8; // internal Vector3 < obfuscated name >
        offset _multiMesh = 0x278; // private SkinnedMultiMesh < obfuscated name >
    }

    namespace player_eyes {
        offset eye_offset = 0x50;
        offset eye_rotation = 0x6C;
        offset body_rotation = 0x50;
        offset view_offset = 0x40;
    }
}

#endif // !offset_h
