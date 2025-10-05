#ifndef sdk_h
#define sdk_h

#include <include.h>

class Bounds {
public:
    unsigned long long get() const {
        return (unsigned long long)(this);
    }

    // these values should never change

    engine::vec3_t m_Center() const {
        return m.read<engine::vec3_t>(get());
    }

    engine::vec3_t m_Extents() const {
        return m.read<engine::vec3_t>(get() + 0xC);
    }
};

class Model {
public:

};

class PlayerModel {
public:
    unsigned long long get() const {
        return (unsigned long long)(this);
    }

    engine::vec3_t position() const {
        return m.read<engine::vec3_t>(get() + offsets::player_model::position);
    }

    unsigned long long _multiMesh() const {
        return m.read<unsigned long long>(get() + offsets::player_model::_multiMesh);
    }
};

class PlayerInput {
public:

};

class BaseMovement {
public:
    // don't forgot this is inherited from a class with actual values ts useless other than that
};

class PlayerEyes {
public:

};

class PlayerInventory {
public:

};

class BaseEntity {
public:
    unsigned long long get() const {
        return (unsigned long long)(this);
    }

    std::string get_class_name() const {
        unsigned long long pointer = m.read<unsigned long long>(get() + 0x0);
        if (!pointer)
            return "";

        pointer = m.read<unsigned long long>(pointer + 0x10);
        if(!pointer)
            return "";

        return m.read_string(pointer);
    }

    Bounds* bounds() const {
        return m.read<Bounds*>(get() + offsets::base_entity::bounds);
    }

    Model* model() const {
        return m.read<Model*>(get() + offsets::base_entity::model);
    }
};

class BaseCombatEntity : public BaseEntity {
public:
    enum LifeState : int {
        Alive = 0,
        Dead = 1
    };

    LifeState lifestate() {
        return m.read<LifeState>(get() + offsets::base_combat_entity::lifestate);
    }

    float _health() {
        return m.read<float>(get() + offsets::base_combat_entity::_health);
    }

    float _maxHealth() {
        return m.read<float>(get() + offsets::base_combat_entity::_maxHealth);
    }
};

class BasePlayer : public BaseCombatEntity {
public:
    enum class PlayerFlags : int {
        Unused1 = 1,
        Unused2 = 2,
        IsAdmin = 4,
        ReceivingSnapshot = 8,
        Sleeping = 16,
        Spectating = 32,
        Wounded = 64,
        IsDeveloper = 128,
        Connected = 256,
        ThirdPersonViewmode = 1024,
        EyesViewmode = 2048,
        ChatMute = 4096,
        NoSprint = 8192,
        Aiming = 16384,
        DisplaySash = 32768,
        Relaxed = 65536,
        SafeZone = 131072,
        ServerFall = 262144,
        Incapacitated = 524288,
        Workbench1 = 1048576,
        Workbench2 = 2097152,
        Workbench3 = 4194304,
        VoiceRangeBoost = 8388608,
        ModifyClan = 16777216,
        LoadingAfterTransfer = 33554432,
        NoRespawnZone = 67108864,
        IsInTutorial = 134217728,
        IsRestrained = 268435456,
        CreativeMode = 536870912,
        WaitingForGestureInteraction = 1073741824,
        Ragdolling = -2147483648
    };

    unsigned long currentTeam() {
        return m.read<unsigned long>(get() + offsets::base_player::currentTeam);
    }

    PlayerFlags playerFlags() {
        return m.read<PlayerFlags>(get() + offsets::base_player::playerFlags);
    }

    PlayerModel* playerModel() {
        return m.read<PlayerModel*>(get() + offsets::base_player::playerModel);
    }

    PlayerInventory* inventoryValue() {
        PlayerInventory* encrypted_value = m.read<PlayerInventory*>(get() + offsets::base_player::inventoryValue);
        if (!encrypted_value)
            return nullptr;

        return (PlayerInventory*)decryptions::decrypt_player_inventory((unsigned long long)encrypted_value);
    }

    unsigned long clActiveItem() {
        return m.read<unsigned long>(get() + offsets::base_player::clActiveItem);
    }

    std::string _displayName() {
        unsigned long long pointer = m.read<unsigned long long>(get() + offsets::base_player::_displayName);
        if (!pointer)
            return "";

        int string_len = m.read<int>(pointer + 0x10);
        if (!string_len)
            return "";

        std::wstring read_string = m.read_wstring(pointer + 0x14, string_len);
        if (read_string.empty())
            return "";

        read_string.erase(string_len);

        return std::string(read_string.begin(), read_string.end());;
    }

    BaseMovement* movement() {
        return m.read<BaseMovement*>(get() + offsets::base_player::movement);
    }

    PlayerInput* input() {
        return m.read<PlayerInput*>(get() + offsets::base_player::input);
    }

    PlayerEyes* eyesValue() {
        PlayerEyes* encrypted_value = m.read<PlayerEyes*>(get() + offsets::base_player::eyesValue);
        if (!encrypted_value)
            return nullptr;

        return (PlayerEyes*)decryptions::decrypt_player_inventory((unsigned long long)encrypted_value);
    }
};

class BaseNetworkable {
private:
    static unsigned long long get_static_class() {
        return m.read<unsigned long long>(globals::game_assembly + offsets::base_networkable);
    }

    static unsigned long long get_static_field() {
        return m.read<unsigned long long>(get_static_class() + offsets::base_networkable_class::static_fields);
    }

    static unsigned long long get_wrapper_class_pointer() {
        return m.read<unsigned long long>(get_static_field() + offsets::base_networkable_class::wrapper_fields);
    }

    static unsigned long long get_wrapper_class() {
        return decryptions::decrypt_base_networkable(get_wrapper_class_pointer());
    }

    static unsigned long long get_parent_class() {
        return m.read<unsigned long long>(get_wrapper_class() + offsets::base_networkable_class::parent_static_fields);
    }

    static unsigned long long get_parent_class_fields() {
        return decryptions::decrypt_base_networkable_list(get_parent_class());
    }

public:
    struct object_list {
        unsigned long long array;
        unsigned long long count;
    };

    object_list get_object_list() {
        object_list list = { 0 };

        unsigned long long object_directory = 
            m.read<unsigned long long>(
                (unsigned long long)(this) + offsets::base_networkable_class::entity
            );

        if (!object_directory)
            return list;

        list.array = m.read<unsigned long long>(object_directory + offsets::entity_list::array);
        list.count = m.read<unsigned long long>(object_directory + offsets::entity_list::size);

        return list;
    }

    static BaseNetworkable* get_base_networkable() {
        unsigned long long parent_fields = get_parent_class_fields();
        if (!parent_fields)
            return nullptr;

        return (BaseNetworkable*)parent_fields;
    }
};

class MainCamera {
private:
    static unsigned long long get_static_class() {
        return m.read<unsigned long long>(globals::game_assembly + offsets::base_camera);
    }

    static unsigned long long get_static_field() {
        return m.read<unsigned long long>(get_static_class() + offsets::base_camera_class::static_fields);
    }

    static unsigned long long get_wrapper_class() {
        return m.read<unsigned long long>(get_static_field() + offsets::base_camera_class::wrapper_class);
    }

    static unsigned long long get_parent_class_fields() {
        return m.read<unsigned long long>(get_wrapper_class() + offsets::base_camera_class::parent_static_fields);
    }

public:
    static MainCamera* get_main_camera() {
        unsigned long long parent_fields = get_parent_class_fields();
        if (!parent_fields)
            return nullptr;

        return (MainCamera*)parent_fields;
    }

    engine::matrix_4x4_t get_view_matrix() const {
        return m.read<engine::matrix_4x4_t>((unsigned long long)(this) + offsets::base_camera_class::matrix);
    }

    engine::vec2_t world_to_screen(const engine::vec3_t world_position) const {
        if (world_position.empty())
            return engine::vec2_t(0, 0);

        engine::matrix_4x4_t view_matrix = get_view_matrix();

        engine::vec3_t transpose_vector{ view_matrix._14, view_matrix._24, view_matrix._34 };
        engine::vec3_t right_vector{ view_matrix._11, view_matrix._21, view_matrix._31 };
        engine::vec3_t up_vector{ view_matrix._12, view_matrix._22, view_matrix._32 };

        float w = transpose_vector.Dot(world_position) + view_matrix._44;
        if (w < 0.01f)
            return engine::vec2_t(0, 0);

        float x = right_vector.Dot(world_position) + view_matrix._41;
        float y = up_vector.Dot(world_position) + view_matrix._42;
        float ndc_x = x / w;
        float ndc_y = y / w;

        // hard coded for now!!!

        return engine::vec2_t(
            (2560 / 2.0f) * (1.0f + ndc_x),
            (1440 / 2.0f) * (1.0f - ndc_y)
        );
    }

    engine::vec2_t world_to_screen_refrenece(const engine::vec3_t& world_position) const {
        if (world_position.empty())
            return engine::vec2_t(0, 0);

        engine::matrix_4x4_t view_matrix = get_view_matrix();

        engine::vec3_t transpose_vector{ view_matrix._14, view_matrix._24, view_matrix._34 };
        engine::vec3_t right_vector{ view_matrix._11, view_matrix._21, view_matrix._31 };
        engine::vec3_t up_vector{ view_matrix._12, view_matrix._22, view_matrix._32 };

        float w = transpose_vector.Dot(world_position) + view_matrix._44;
        if (w < 0.01f)
            return engine::vec2_t(0, 0);

        float x = right_vector.Dot(world_position) + view_matrix._41;
        float y = up_vector.Dot(world_position) + view_matrix._42;
        float ndc_x = x / w;
        float ndc_y = y / w;

        // hard coded for now!!!

        return engine::vec2_t(
            (2560 / 2.0f) * (1.0f + ndc_x),
            (1440 / 2.0f) * (1.0f - ndc_y)
        );
    }
};

#endif // !sdk_H
