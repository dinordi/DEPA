#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "Component.h"
#include "Edge.h"
#include <vector>
#include <map>
#include <memory>
#include <string>

/**
 * @brief Representeerd het gehele digitale circuit
 */
class Circuit {
public:
    Circuit() = default;
    ~Circuit();
    
    // Componenten beheer
    void addComponent(Component* component);
    Component* getComponent(const std::string& id);
    std::vector<Component*>& getComponents();
    
    // Verbindingen beheer
    void addEdge(Edge* edge);
    std::vector<Edge*>& getEdges();

private:
    std::vector<Component*> components;  // Lijst van alle componenten
    std::map<std::string, Component*> componentMap; // Map voor snelle lookup op id
    std::vector<Edge*> edges;            // Lijst van alle verbindingen
};

#endif // CIRCUIT_H