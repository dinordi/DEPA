#include "Input.h"

Input::Input(const std::string& id)
    : Component(id, 0) {}

void Input::setValue(bool value) {
    setOutputValue(value);
}

bool Input::calculateOutput() {
    return getOutputValue();
}
