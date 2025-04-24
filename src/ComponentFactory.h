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

/**
 * @brief Factory klasse voor het maken van verschillende soorten componenten
 * Implementeert het Factory Method Pattern
 */
class ComponentFactory {
public:
    /**
     * @brief Componenttype enumeratie om het type component aan te geven
     */
    enum class ComponentType {
        AND,
        OR,
        NOT,
        NAND,
        NOR,
        XOR,
        INPUT,
        PROBE
    };
    
    /**
     * @brief Maakt een component van het opgegeven type
     * @param type Het type component dat moet worden gemaakt
     * @param id De ID van de nieuwe component
     * @param propagationDelay De optionele voortplantingsvertraging
     * @return Een pointer naar het nieuw gemaakte component
     * @throw std::invalid_argument Als het type niet wordt ondersteund
     */
    static Component* createComponent(ComponentType type, const std::string& id, int propagationDelay = 1) {
        switch (type) {
            case ComponentType::AND:
                return new ANDGate(id, propagationDelay);
            case ComponentType::OR:
                return new ORGate(id, propagationDelay);
            case ComponentType::NOT:
                return new NOTGate(id, propagationDelay);
            case ComponentType::NAND:
                return new NANDGate(id, propagationDelay);
            case ComponentType::NOR:
                return new NORGate(id, propagationDelay);
            case ComponentType::XOR:
                return new XORGate(id, propagationDelay);
            case ComponentType::INPUT:
                return new Input(id); // Input heeft geen vertraging
            case ComponentType::PROBE:
                return new Probe(id); // Probe heeft geen vertraging
            default:
                throw std::invalid_argument("Onbekend componenttype");
        }
    }
    
    /**
     * @brief Maakt een component op basis van een typestring
     * @param typeStr Het type als een string (bijv. "AND", "OR")
     * @param id De ID van de nieuwe component
     * @param propagationDelay De optionele voortplantingsvertraging
     * @return Een pointer naar het nieuw gemaakte component
     * @throw std::invalid_argument Als het type niet wordt ondersteund
     */
    static Component* createComponent(const std::string& typeStr, const std::string& id, int propagationDelay = 1) {
        if (typeStr == "AND") return createComponent(ComponentType::AND, id, propagationDelay);
        if (typeStr == "OR") return createComponent(ComponentType::OR, id, propagationDelay);
        if (typeStr == "NOT") return createComponent(ComponentType::NOT, id, propagationDelay);
        if (typeStr == "NAND") return createComponent(ComponentType::NAND, id, propagationDelay);
        if (typeStr == "NOR") return createComponent(ComponentType::NOR, id, propagationDelay);
        if (typeStr == "XOR") return createComponent(ComponentType::XOR, id, propagationDelay);
        if (typeStr == "INPUT") return createComponent(ComponentType::INPUT, id);
        if (typeStr == "PROBE") return createComponent(ComponentType::PROBE, id);
        throw std::invalid_argument("Onbekend componenttype: " + typeStr);
    }
};

#endif // COMPONENTFACTORY_H