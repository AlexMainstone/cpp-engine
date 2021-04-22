#pragma once

#include <sol/sol.hpp>

#include "UI/DialogueWindow.hpp"

class DialogueScript {
    public:
        DialogueScript(DialogueWindow *dwindow);
        ~DialogueScript();
        
        void load(const char *path);
        
        void update(float dt);
        
        void addOption(const char *option);
        
        void error();
    private:
        DialogueWindow *dwindow;
        sol::state lua_state;
        sol::coroutine coroutine;
};