#ifndef XORGATE_H
#define XORGATE_H

#include "LogicGate.h"

/**
 * @brief Implementeerd XOR logic
 */
class XORGate : public LogicGate {
public:
    XORGate(const std::string& id, int propagationDelay = 1);
    
    // Implementeert de XOR logica: output = input1 XOR input2 XOR ...
    bool calculateOutput() override;

    // Clone method
    Component* clone() const override;
};

// Inline implementaties
inline XORGate::XORGate(const std::string& id, int propagationDelay)
    : LogicGate(id, 2, propagationDelay) {}

inline bool XORGate::calculateOutput() {
    // XOR geeft true als er een oneven aantal inputs true is
    bool result = false;
    for (Component* input : inputs) {
        if (input->getOutputValue()) {
            result = !result; // Toggle het resultaat bij elke true input
        }
    }
    return result;
}

inline Component* XORGate::clone() const {
    return new XORGate(*this);
}

#endif // XORGATE_H