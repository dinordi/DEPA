#ifndef NORGATE_H
#define NORGATE_H

#include "LogicGate.h"

/**
 * @brief Implementeerd NOR logic
 */
class NORGate : public LogicGate {
public:
    NORGate(const std::string& id, int propagationDelay = 10);
    
    // Implementeert de NOR logica: output = NOT (input1 OR input2 OR ...)
    bool calculateOutput() override;

    // Clone method
    Component* clone() const override;
};

// Inline implementaties
inline NORGate::NORGate(const std::string& id, int propagationDelay)
    : LogicGate(id, 2, propagationDelay) {}

inline bool NORGate::calculateOutput() {
    // NOR is de inverse van OR: returneer true alleen als ALLE inputs false zijn
    for (Component* input : inputs) {
        if (input->getOutputValue()) {
            return false;
        }
    }
    return true;
}

inline Component* NORGate::clone() const {
    return new NORGate(*this);
}

#endif // NORGATE_H