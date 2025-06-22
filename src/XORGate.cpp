#include "XORGate.h"

XORGate::XORGate(const std::string& id, int propagationDelay)
    : LogicGate(id, 2, propagationDelay) {}

bool XORGate::calculateOutput() {
    bool result = false;
    for (Component* input : inputs) {
        if (input->getOutputValue()) {
            result = !result;
        }
    }
    return result;
}

Component* XORGate::clone() const {
    return new XORGate(*this);
}
