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
    Component* clone() const override { return new Probe(*this); }
    
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

#endif // PROBE_H