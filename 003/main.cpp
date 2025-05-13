#include "ui.h"
#include <chrono>
#include <thread>

int main() {
    GameState state;
    ui_init(); //게임을 위한 기본 설정
    init_game(state); // GameState 초기화
    
    const auto frame_duration = std::chrono::milliseconds(50); //20FPS
    auto last_frame_time = std::chrono::steady_clock::now();
    
    while (state.running) {
        auto current_time = std::chrono::steady_clock::now();
        auto elapsed = current_time - last_frame_time;
        
        if (elapsed >= frame_duration) { // 시간 제한
            ui_draw(state); //보드 윈도우에 그리기
            int action = ui_get_input(); // 방향키, 스페이스 바, q(uit)
            handle_game_action(state, action); //입력 값에 따라 수행
            update_game(state); // 시간에 따른 중력(입력 값과 관계 없이 지속적 으로 유지 되는 게임 특성)
            last_frame_time = current_time; // 시간 초기화
        } else {
            std::this_thread::sleep_for(frame_duration - elapsed); // 게임 상태 유지
        }
    }
    
    ui_cleanup(state); // 종료(윈도우 닫기)
    return 0;
}