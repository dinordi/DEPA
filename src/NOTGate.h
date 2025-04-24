#ifndef NOTGATE_H
#define NOTGATE_H

#include "LogicGate.h"

/**
 * @brief Implementeerd NOT logic
 */
class NOTGate : public LogicGate {
public:
    NOTGate(const std::string& id, int propagationDelay = 1);
    
    // Implementeert de NOT logica: output = NOT input
    bool calculateOutput() override;
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

#endif // NOTGATE_H