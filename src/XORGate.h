#ifndef XORGATE_H
#define XORGATE_H

#include "LogicGate.h"

/**
 * @brief Implementeerd XOR logic
 */
class XORGate : public LogicGate {
public:
    XORGate(const std::string& id, int propagationDelay = 10);
    
    // Implementeert de XOR logica: output = input1 XOR input2 XOR ...
    bool calculateOutput() override;

    // Clone method
    Component* clone() const override;
};

#endif // XORGATE_H