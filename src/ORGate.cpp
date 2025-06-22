#include "ORGate.h"

ORGate::ORGate(const std::string& id, int propagationDelay)
    : LogicGate(id, 2, propagationDelay) {}

bool ORGate::calculateOutput() {
    for (Component* input : inputs) {
        if (input->getOutputValue()) {
            return true;
        }
    }
    return false;
}

Component* ORGate::clone() const {
    return new ORGate(*this);
}
