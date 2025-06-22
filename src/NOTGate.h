#ifndef NOTGATE_H
#define NOTGATE_H

#include "LogicGate.h"
#include <iostream>

/**
 * @brief Implementeerd NOT logic
 */
class NOTGate : public LogicGate {
public:
    NOTGate(const std::string& id, int propagationDelay = 10);
    
    // Implementeert de NOT logica: output = NOT input
    bool calculateOutput() override;

    // Clone method
    Component* clone() const override;
};

#endif // NOTGATE_H