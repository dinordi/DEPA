#ifndef INPUT_H
#define INPUT_H

#include "Component.h"

/**
 * @brief Externe input bron voor het circuit
 */
class Input : public Component {
public:
    Input(const std::string& id);
    
    // Stelt de waarde van de input in
    void setValue(bool value);
    
    // Implementeert de Component interface
    Type getType() const override { return Type::INPUT; }
    bool isInput() const override { return true; }
    Input* asInput() override { return this; }
    Component* clone() const override {
        return new Input(*this);
    }
    
    // Implementeert de abstracte methode van Component
    bool calculateOutput() override;
};

#endif // INPUT_H