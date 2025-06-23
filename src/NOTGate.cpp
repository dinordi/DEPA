#include "NOTGate.h"
#include "ComponentFactory.h"

namespace {
    struct NOTGateProtoType {
        NOTGateProtoType() {
            ComponentFactory::getInstance().registerPrototype("NOT", new NOTGate("prototype"));
        }
    };
    static NOTGateProtoType reg;
}

NOTGate::NOTGate(const std::string& id, int propagationDelay)
    : LogicGate(id, 1, propagationDelay) {}

bool NOTGate::calculateOutput() {
    if (inputs.empty()) {
        return false;
    }
    return !inputs[0]->getOutputValue();
}

Component* NOTGate::clone() const {
    return new NOTGate(*this);
}
