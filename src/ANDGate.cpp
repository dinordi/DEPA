#include "ANDGate.h"
#include "ComponentFactory.h"

namespace {
    struct ANDGateProtoType {
        ANDGateProtoType() {
            ComponentFactory::getInstance().registerPrototype("AND", new ANDGate("prototype"));
        }
    };
    static ANDGateProtoType reg;
}

ANDGate::ANDGate(const std::string& id, int propagationDelay)
    : LogicGate(id, 2, propagationDelay) {}

bool ANDGate::calculateOutput() {
    for (Component* input : inputs) {
        if (!input->getOutputValue()) {
            return false;
        }
    }
    return true;
}

Component* ANDGate::clone() const {
    return new ANDGate(*this);
}
