#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include "Component.h"
#include "Input.h"
#include "Probe.h"
#include "ANDGate.h"
#include "ORGate.h"
#include "NOTGate.h"
#include "NANDGate.h"
#include "NORGate.h"
#include "XORGate.h"
#include <string>
#include <memory>
#include <stdexcept>
#include <unordered_map>

/**
 * @brief Factory klasse voor het maken van verschillende soorten componenten
 * Implementeert het Prototype Pattern
 */
class ComponentFactory {
public:
    ComponentFactory() = default;

    /**
     * @brief Registreer een prototype component
     * @param key De sleutel om het prototype te identificeren
     * @param prototype Een pointer naar het prototype component
     */
    void registerPrototype(const std::string& key, Component* prototype);

    /**
     * @brief Maak een component door een prototype te klonen
     * @param key De sleutel van het prototype
     * @param id De unieke ID voor het nieuwe component
     * @return Een pointer naar het nieuw gemaakte component
     */
    Component* createComponent(const std::string& key, const std::string& id);

private:
    std::unordered_map<std::string, Component*> prototypes; // Prototype opslag
};

#endif // COMPONENTFACTORY_H