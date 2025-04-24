#ifndef LOGICGATE_H
#define LOGICGATE_H

#include "Component.h"
#include <vector>
#include <memory>

/**
 * @brief Abstract basis voor logic gates
 */
class LogicGate : public Component {
public:
    LogicGate(const std::string& id, int inputCount, int propagationDelay = 1);
    virtual ~LogicGate() = default;
    
    void addInput(Component* input);
    Component* getInput(int index) const;
    int getInputCount() const;
    
    // calculateOutput wordt geïmplementeerd door specifieke poorten
    virtual bool calculateOutput() override = 0;

protected:
    std::vector<Component*> inputs;  // Pointer naar de input componenten
};

// Inline implementaties
inline LogicGate::LogicGate(const std::string& id, int inputCount, int propagationDelay)
    : Component(id, propagationDelay) {
    inputs.reserve(inputCount);
}

inline void LogicGate::addInput(Component* input) {
    inputs.push_back(input);
}

inline Component* LogicGate::getInput(int index) const {
    if (index < 0 || index >= inputs.size()) {
        return nullptr;
    }
    return inputs[index];
}

inline int LogicGate::getInputCount() const {
    return static_cast<int>(inputs.size());
}

#endif // LOGICGATE_H