#include "ComponentFactory.h"

// All methods are already implemented inline in the header, but for a clean split, move them here.

void ComponentFactory::registerPrototype(const std::string& key, Component* prototype) {
    prototypes[key] = prototype;
}

Component* ComponentFactory::createComponent(const std::string& key, const std::string& id) {
    auto it = prototypes.find(key);
    if (it != prototypes.end()) {
        Component* cloned = it->second->clone();
        cloned->setId(id);
        cloned->setOutputValue(false);
        return cloned;
    }
    throw std::invalid_argument("Prototype not found for key: " + key);
}
