#ifndef NANDGATE_H
#define NANDGATE_H

#include "LogicGate.h"

/**
 * @brief Implementeerd NAND logic
 */
class NANDGate : public LogicGate {
public:
    NANDGate(const std::string& id, int propagationDelay = 10);
    
    // Implementeert de NAND logica: output = NOT (input1 AND input2 AND ...)
    bool calculateOutput() override;

    Component* clone() const override;
};

#endif // NANDGATE_H