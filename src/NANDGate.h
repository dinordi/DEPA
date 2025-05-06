#ifndef NANDGATE_H
#define NANDGATE_H

#include "LogicGate.h"

/**
 * @brief Implementeerd NAND logic
 */
class NANDGate : public LogicGate {
public:
    NANDGate(const std::string& id, int propagationDelay = 1);
    
    // Implementeert de NAND logica: output = NOT (input1 AND input2 AND ...)
    bool calculateOutput() override;

    Component* clone() const override;
};

// Inline implementaties
inline NANDGate::NANDGate(const std::string& id, int propagationDelay)
    : LogicGate(id, 2, propagationDelay) {}

inline bool NANDGate::calculateOutput() {
    // NAND is de inverse van AND: returneer false alleen als ALLE inputs true zijn
    for (Component* input : inputs) {
        if (!input->getOutputValue()) {
            return true;
        }
    }
    return false;
}

inline Component* NANDGate::clone() const {
    return new NANDGate(*this);
}

#endif // NANDGATE_H