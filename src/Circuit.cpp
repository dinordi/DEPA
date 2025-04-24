#include "Circuit.h"

// Voeg een component toe aan het circuit
void Circuit::addComponent(Component* component) {
    components.push_back(component);
    componentMap[component->getId()] = component;
}

// Zoek een component op basis van ID
Component* Circuit::getComponent(const std::string& id) {
    auto it = componentMap.find(id);
    if (it != componentMap.end()) {
        return it->second;
    }
    return nullptr;
}

// Haal alle componenten op
std::vector<Component*>& Circuit::getComponents() {
    return components;
}

// Voeg een verbinding toe aan het circuit
void Circuit::addEdge(Edge* edge) {
    edges.push_back(edge);
}

// Haal alle verbindingen op
std::vector<Edge*>& Circuit::getEdges() {
    return edges;
}

// Destructor: ruim alle gealloceerde componenten en verbindingen op
Circuit::~Circuit() {
    // Verwijder alle componenten
    for (auto component : components) {
        delete component;
    }
    
    // Verwijder alle edges
    for (auto edge : edges) {
        delete edge;
    }
    
    // Maak de vectoren leeg
    components.clear();
    edges.clear();
    componentMap.clear();
}