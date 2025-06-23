#include "Input.h"
#include "ComponentFactory.h"

namespace {
    struct InputProtoType {
        InputProtoType() {
            ComponentFactory::getInstance().registerPrototype("INPUT_HIGH", new Input("prototype"));
            ComponentFactory::getInstance().registerPrototype("INPUT_LOW", new Input("prototype"));
        }
    };
    static InputProtoType reg;
}

Input::Input(const std::string& id)
    : Component(id, 0) {}

void Input::setValue(bool value) {
    setOutputValue(value);
}

bool Input::calculateOutput() {
    return getOutputValue();
}
