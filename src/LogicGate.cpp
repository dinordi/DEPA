#include "LogicGate.h"

LogicGate::LogicGate(const std::string& id, int inputCount, int propagationDelay)
    : Component(id, propagationDelay) {
    inputs.reserve(inputCount);
}

void LogicGate::addInput(Component* input) {
    inputs.push_back(input);
}

Component* LogicGate::getInput(int index) const {
    if (index < 0 || static_cast<size_t>(index) >= inputs.size()) {
        return nullptr;
    }
    return inputs[index];
}

int LogicGate::getInputCount() const {
    return static_cast<int>(inputs.size());
}
