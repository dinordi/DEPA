#include "Component.h"

Component::Component(const std::string& id, int propagationDelay)
    : id(id), propagationDelay(propagationDelay), outputValue(false) {}

std::string Component::getId() const {
    return id;
}

int Component::getPropagationDelay() const {
    return propagationDelay;
}

bool Component::getOutputValue() const {
    return outputValue;
}

void Component::setOutputValue(bool value) {
    outputValue = value;
}

void Component::setId(const std::string& newId) {
    id = newId;
}

// Add other method implementations as needed from the header.
