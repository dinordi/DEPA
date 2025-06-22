#include "NANDGate.h"

NANDGate::NANDGate(const std::string& id, int propagationDelay)
    : LogicGate(id, 2, propagationDelay) {}

bool NANDGate::calculateOutput() {
    for (Component* input : inputs) {
        if (!input->getOutputValue()) {
            return true;
        }
    }
    return false;
}

Component* NANDGate::clone() const {
    return new NANDGate(*this);
}
