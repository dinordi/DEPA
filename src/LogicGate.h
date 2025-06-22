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
    LogicGate(const std::string& id, int inputCount, int propagationDelay = 10);
    virtual ~LogicGate() = default;
    
    void addInput(Component* input);
    Component* getInput(int index) const;
    int getInputCount() const;
    
    // Implementeert de Component interface
    Type getType() const override { return Type::LOGIC_GATE; }
    bool isLogicGate() const override { return true; }
    LogicGate* asLogicGate() override { return this; }
    
    // calculateOutput wordt geïmplementeerd door specifieke poorten
    virtual bool calculateOutput() override = 0;

protected:
    std::vector<Component*> inputs;  // Pointer naar de input componenten
};

#endif // LOGICGATE_H