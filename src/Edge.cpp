#include "Edge.h"

Edge::Edge(Component* source, Component* target)
    : source(source), target(target) {}

Component* Edge::getSource() const {
    return source;
}

Component* Edge::getTarget() const {
    return target;
}
