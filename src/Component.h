#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

/**
 * @brief Abstracte basis voor alle circuit elementen
 */
class Component {
public:
    Component(const std::string& id, int propagationDelay = 0);
    virtual ~Component() = default;

    std::string getId() const;
    int getPropagationDelay() const;
    bool getOutputValue() const;
    void setOutputValue(bool value);
    
    /**
     * @brief Abstracte methode om de uitgangswaarde te berekenen
     * @return De berekende uitgangswaarde
     */
    virtual bool calculateOutput() = 0;

protected:
    std::string id;              // Unieke identificatie
    int propagationDelay;        // Voortplantingsvertraging
    bool outputValue;            // Huidige uitgangswaarde
};

// Inline implementaties
inline Component::Component(const std::string& id, int propagationDelay)
    : id(id), propagationDelay(propagationDelay), outputValue(false) {}

inline std::string Component::getId() const {
    return id;
}

inline int Component::getPropagationDelay() const {
    return propagationDelay;
}

inline bool Component::getOutputValue() const {
    return outputValue;
}

inline void Component::setOutputValue(bool value) {
    outputValue = value;
}

#endif // COMPONENT_H