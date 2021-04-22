#include "Resources/DialogueScript.hpp"

DialogueScript::DialogueScript(DialogueWindow *dwindow) : dwindow(dwindow) {
    lua_state.open_libraries(sol::lib::base, sol::lib::coroutine);
    lua_state.set_function("add_text", &DialogueWindow::addTexti, dwindow);
    lua_state.set_function("add_option", &DialogueWindow::addOption, dwindow);
    lua_state.set_function("clear_options", &DialogueWindow::clearOptions, dwindow);
    lua_state.set_function("jump_end", &DialogueWindow::jumpToEnd, dwindow);
}

DialogueScript::~DialogueScript() {
}

void DialogueScript::addOption(const char *option) {
    dwindow->addOption(option);
}

#include<iostream>
void DialogueScript::update(float dt) {
    int selected = dwindow->getSelected();
    if(selected != 0) {
        if(coroutine.status() != sol::call_status::yielded) {
            // we're not waiting for text! back out
            dwindow->setVisible(false);
            return;
        }
        lua_state["result"] = selected;
        coroutine();
    }
}

void DialogueScript::load(const char *path) {
    lua_state.script_file(path);
    coroutine = lua_state["start"];
    auto result = coroutine();
}

void DialogueScript::error() {
}
