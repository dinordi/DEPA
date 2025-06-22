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

#endif // NORGATE_H