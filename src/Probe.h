#ifndef PROBE_H
#define PROBE_H

#include "Component.h"

/**
 * @brief Luistert signaal value op een bepaald punt
 */
class Probe : public Component, public ComponentObserver {
public:
    Probe(const std::string& id);
    ~Probe() override;
    
    bool getRecordedValue() const;
    
    // Implementeert de Component interface
    Type getType() const override { return Type::PROBE; }
    bool isProbe() const override { return true; }
    Probe* asProbe() override { return this; }
    
    // Implementeert de abstracte methode van Component
    bool calculateOutput() override;
    
    // Observer pattern method
    void update(Component* subject) override;
    
    // Verbind deze probe met een component om te observeren
    void observeComponent(Component* component);
    
private:
    bool recordedValue; // De opgenomen waarde
    Component* observedComponent; // Component die deze probe observeert
};

// Inline implementaties
inline Probe::Probe(const std::string& id)
    : Component(id, 0), recordedValue(false), observedComponent(nullptr) {}

inline Probe::~Probe() {
    if (observedComponent) {
        observedComponent->removeObserver(this);
    }
}

inline bool Probe::getRecordedValue() const {
    return recordedValue;
}

inline void Probe::update(Component* subject) {
    if (subject == observedComponent) {
        recordedValue = subject->getOutputValue();
    }
}

inline void Probe::observeComponent(Component* component) {
    // Verwijder bestaande observatie, indien aanwezig
    if (observedComponent) {
        observedComponent->removeObserver(this);
    }
    
    // Registreer nieuwe observatie
    observedComponent = component;
    if (component) {
        component->addObserver(this);
    }
}

inline bool Probe::calculateOutput() {
    // Probe geeft de geobserveerde waarde terug
    return recordedValue;
}

#endif // PROBE_H