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

#endif // EDGE_H