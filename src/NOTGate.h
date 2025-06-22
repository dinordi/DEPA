#ifndef NOTGATE_H
#define NOTGATE_H

#include "LogicGate.h"
#include <iostream>

/**
 * @brief Implementeerd NOT logic
 */
class NOTGate : public LogicGate {
public:
    NOTGate(const std::string& id, int propagationDelay = 10);
    
    // Implementeert de NOT logica: output = NOT input
    bool calculateOutput() override;

    // Clone method
    Component* clone() const override;
};

// Inline implementaties
inline NOTGate::NOTGate(const std::string& id, int propagationDelay)
    : LogicGate(id, 1, propagationDelay) {}

inline bool NOTGate::calculateOutput() {
    // NOT inverteert de input waarde - hier gebruiken we alleen de eerste input
    if (inputs.empty()) {
        return false;
    }
    return !inputs[0]->getOutputValue();
}

inline Component* NOTGate::clone() const {
    return new NOTGate(*this);
}

#endif // NOTGATE_H