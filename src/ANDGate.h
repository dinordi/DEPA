#ifndef ANDGATE_H
#define ANDGATE_H

#include "LogicGate.h"
#include <iostream>

/**
 * @brief Implementeerd AND logic
 */
class ANDGate : public LogicGate {
public:
    ANDGate(const std::string& id, int propagationDelay = 10);
    
    // Implementeert de AND logica: output = input1 AND input2 AND ...
    bool calculateOutput() override;

    // Clone method
    Component* clone() const override;
};

// Inline implementaties
inline ANDGate::ANDGate(const std::string& id, int propagationDelay)
    : LogicGate(id, 2, propagationDelay) {}

inline bool ANDGate::calculateOutput() {
    // AND geeft alleen true als ALLE inputs true zijn
    for (Component* input : inputs) {
        if (!input->getOutputValue()) {
            return false;
        }
    }
    return true;
}

inline Component* ANDGate::clone() const {
    return new ANDGate(*this);
}

#endif // ANDGATE_H