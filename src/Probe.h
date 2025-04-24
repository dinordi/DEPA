#ifndef PROBE_H
#define PROBE_H

#include "Component.h"

/**
 * @brief Luistert signaal value op een bepaald punt
 */
class Probe : public Component {
public:
    Probe(const std::string& id);
    
    bool getRecordedValue() const;
    void recordValue(bool value);
    
    // Implementeert de abstracte methode van Component
    bool calculateOutput() override;
    
private:
    bool recordedValue; // De opgenomen waarde
};

// Inline implementaties
inline Probe::Probe(const std::string& id)
    : Component(id, 0), recordedValue(false) {}

inline bool Probe::getRecordedValue() const {
    return recordedValue;
}

inline void Probe::recordValue(bool value) {
    recordedValue = value;
}

inline bool Probe::calculateOutput() {
    // Probe heeft geen echte output functionaliteit
    return recordedValue;
}

#endif // PROBE_H