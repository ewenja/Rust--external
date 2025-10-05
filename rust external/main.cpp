#include <include.h>

int main() {
    printf("starting project\n");

    if (!m.attach(L"RustClient.exe")) {
        printf("failed to attach to rust\n");
        return -1;
    }

    globals::game_assembly = m.get_module_base(L"GameAssembly.dll");

    if (!overlay::initialize(L"UnityWndClass", L"Rust")) {
        printf("failed to setup overlay\n");
        return -1;
    }

    printf("setup everything\n");
    printf("game assembly -> 0x%llx\n", globals::game_assembly);

    MSG msg = { 0 };
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }

        if (!overlay::scale())
            break;

        if (GetKeyState(VK_END))
            break;

        auto shown = GetKeyState(VK_INSERT);
        overlay::click_through(!shown);

        window::new_frame();

        ImGui::GetForegroundDrawList()->AddText(
            ImVec2(50, 50),
            ImColor(255, 255, 255),
            std::string(std::to_string(ImGui::GetIO().Framerate)).c_str()
        );

        if (shown) {
            ImGui::Begin("project");

            ImGui::End();
        }

        window::draw();
    }

    window::cleanup();
    m.detach();

    printf("peace\n");

    return 0;
}