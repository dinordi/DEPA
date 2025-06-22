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

#endif // ANDGATE_H