#include "NORGate.h"

NORGate::NORGate(const std::string& id, int propagationDelay)
    : LogicGate(id, 2, propagationDelay) {}

bool NORGate::calculateOutput() {
    for (Component* input : inputs) {
        if (input->getOutputValue()) {
            return false;
        }
    }
    return true;
}

Component* NORGate::clone() const {
    return new NORGate(*this);
}
