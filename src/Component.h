#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <vector>
#include <algorithm>

// Forward declarations
class ComponentObserver;
class LogicGate;
class Probe;
class Input;

/**
 * @brief Abstracte basis voor alle circuit elementen
 */
class Component {
public:
    // Componenttypes enum
    enum class Type {
        LOGIC_GATE,
        INPUT,
        PROBE
    };
    
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
    
    /**
     * @brief Geeft het type van deze component terug
     * @return Het componenttype
     */
    virtual Type getType() const = 0;
    
    /**
     * @brief Controleert of deze component een LogicGate is
     * @return true als het een LogicGate is, anders false
     */
    virtual bool isLogicGate() const { return false; }
    
    /**
     * @brief Controleert of deze component een Probe is
     * @return true als het een Probe is, anders false
     */
    virtual bool isProbe() const { return false; }
    
    /**
     * @brief Controleert of deze component een Input is
     * @return true als het een Input is, anders false
     */
    virtual bool isInput() const { return false; }
    
    /**
     * @brief Geeft een pointer naar deze component als LogicGate
     * @return Pointer naar LogicGate of nullptr als het geen LogicGate is
     */
    virtual LogicGate* asLogicGate() { return nullptr; }
    
    /**
     * @brief Geeft een pointer naar deze component als Probe
     * @return Pointer naar Probe of nullptr als het geen Probe is
     */
    virtual Probe* asProbe() { return nullptr; }
    
    /**
     * @brief Geeft een pointer naar deze component als Input
     * @return Pointer naar Input of nullptr als het geen Input is
     */
    virtual Input* asInput() { return nullptr; }
    
    // Observer pattern methods
    void addObserver(ComponentObserver* observer);
    void removeObserver(ComponentObserver* observer);
    void notifyObservers();

protected:
    std::string id;              // Unieke identificatie
    int propagationDelay;        // Voortplantingsvertraging
    bool outputValue;            // Huidige uitgangswaarde
    std::vector<ComponentObserver*> observers; // Observer pattern
};

/**
 * @brief Observer interface voor het reageren op veranderingen in componenten
 */
class ComponentObserver {
public:
    virtual ~ComponentObserver() = default;
    virtual void update(Component* subject) = 0;
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
    bool oldValue = outputValue;
    outputValue = value;
    if (oldValue != value) {
        notifyObservers();
    }
}

inline void Component::addObserver(ComponentObserver* observer) {
    observers.push_back(observer);
}

inline void Component::removeObserver(ComponentObserver* observer) {
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end()) {
        observers.erase(it);
    }
}

inline void Component::notifyObservers() {
    for (auto observer : observers) {
        observer->update(this);
    }
}

#endif // COMPONENT_H