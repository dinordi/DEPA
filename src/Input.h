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
    
    // Implementeert de abstracte methode van Component
    bool calculateOutput() override;
};

// Inline implementaties
inline Input::Input(const std::string& id)
    : Component(id, 0) {} // Input heeft geen vertraging

inline void Input::setValue(bool value) {
    setOutputValue(value);
}

inline bool Input::calculateOutput() {
    // Input berekent niet, geeft gewoon de ingestelde waarde terug
    return getOutputValue();
}

#endif // INPUT_H