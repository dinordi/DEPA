#include "Circuit.h"
#include <algorithm>

Circuit::~Circuit() {
    for (Component* component : components) {
        delete component;
    }
    for (Edge* edge : edges) {
        delete edge;
    }
}

void Circuit::addComponent(Component* component) {
    components.push_back(component);
    componentMap[component->getId()] = component;
}

Component* Circuit::getComponent(const std::string& id) {
    auto it = componentMap.find(id);
    if (it != componentMap.end()) {
        return it->second;
    }
    return nullptr;
}

std::vector<Component*>& Circuit::getComponents() {
    return components;
}

void Circuit::addEdge(Edge* edge) {
    edges.push_back(edge);
}

std::vector<Edge*>& Circuit::getEdges() {
    return edges;
}