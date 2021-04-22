#pragma once

struct controlled {
    bool current;
};

struct creature {
    int hp;
    int max_hp;
};

enum ENEMY_STATE {
    IDLE,
    SPOTTED,
    LAST_KNOWN
};

struct enemy {
    ENEMY_STATE state = ENEMY_STATE::IDLE;
    int spotted_x;
    int spotted_y;
};

struct interactable {};
struct solid {};

struct position {
    float x;
    float y;
    
    int target_x;
    int target_y;
};

struct render_tile {
    int tile;
};