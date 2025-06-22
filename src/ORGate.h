#ifndef ORGATE_H
#define ORGATE_H

#include "LogicGate.h"

/**
 * @brief Implementeerd OR logic
 */
class ORGate : public LogicGate {
public:
    ORGate(const std::string& id, int propagationDelay = 10);
    
    // Implementeert de OR logica: output = input1 OR input2 OR ...
    bool calculateOutput() override;

    // Clone method
    Component* clone() const override;
};

// Inline implementaties
inline ORGate::ORGate(const std::string& id, int propagationDelay)
    : LogicGate(id, 2, propagationDelay) {}

inline bool ORGate::calculateOutput() {
    // OR geeft true als TEN MINSTE ÉÉN input true is
    for (Component* input : inputs) {
        if (input->getOutputValue()) {
            return true;
        }
    }
    return false;
}

inline Component* ORGate::clone() const {
    return new ORGate(*this);
}

#endif // ORGATE_H