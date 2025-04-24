#ifndef ORGATE_H
#define ORGATE_H

#include "LogicGate.h"

/**
 * @brief Implementeerd OR logic
 */
class ORGate : public LogicGate {
public:
    ORGate(const std::string& id, int propagationDelay = 1);
    
    // Implementeert de OR logica: output = input1 OR input2 OR ...
    bool calculateOutput() override;
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

#endif // ORGATE_H