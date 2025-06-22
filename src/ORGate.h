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

#endif // ORGATE_H