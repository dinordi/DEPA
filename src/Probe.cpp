#include "Probe.h"

Probe::Probe(const std::string& id)
    : Component(id, 10), recordedValue(false), observedComponent(nullptr) {}

Probe::~Probe() {
    if (observedComponent) {
        observedComponent->removeObserver(this);
    }
}

bool Probe::getRecordedValue() const {
    return recordedValue;
}

void Probe::update(Component* subject) {
    if (subject == observedComponent) {
        recordedValue = subject->getOutputValue();
    }
}

void Probe::observeComponent(Component* component) {
    if (observedComponent) {
        observedComponent->removeObserver(this);
    }
    observedComponent = component;
    if (observedComponent) {
        observedComponent->addObserver(this);
        recordedValue = observedComponent->getOutputValue();
    }
}

bool Probe::calculateOutput() {
    return recordedValue;
}
