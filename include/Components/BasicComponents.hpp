#pragma once

struct controlled {
    bool current;
};

struct position {
    float x;
    float y;
    
    int target_x;
    int target_y;
};

struct render_tile {
    int tile;
};