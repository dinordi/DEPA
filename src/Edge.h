#ifndef EDGE_H
#define EDGE_H

#include "Component.h"
#include <memory>

/**
 * @brief Representeert een verbinding tussen componenten
 */
class Edge {
public:
    Edge(Component* source, Component* target);

    Component* getSource() const;
    Component* getTarget() const;

private:
    Component* source; // Broncomponent (output)
    Component* target; // Doelcomponent (input)
};

// Inline implementaties
inline Edge::Edge(Component* source, Component* target) 
    : source(source), target(target) {}

inline Component* Edge::getSource() const {
    return source;
}

inline Component* Edge::getTarget() const {
    return target;
}

#endif // EDGE_H