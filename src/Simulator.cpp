#include "Simulator.h"
#include <iostream>

Simulator::Simulator(Circuit* circuit)
    : circuit(circuit), inputFileHandler(nullptr), outputHandler(nullptr) {}

void Simulator::setCircuit(Circuit* circuit) {
    this->circuit = circuit;
}

Circuit* Simulator::getCircuit() const {
    return circuit;
}

void Simulator::setInputFileHandler(InputFileHandler* handler) {
    inputFileHandler = handler;
}

void Simulator::setOutputHandler(OutputHandler* handler) {
    outputHandler = handler;
}

bool Simulator::loadCircuit(const std::string& filename) {
    if (!inputFileHandler) {
        return false;
    }
    Circuit* loadedCircuit = inputFileHandler->readCircuit(filename);
    if (loadedCircuit) {
        if (circuit) {
            delete circuit;
        }
        circuit = loadedCircuit;
        return true;
    }
    return false;
}

std::vector<Probe*> Simulator::collectProbes() {
    std::vector<Probe*> probes;
    if (!circuit) {
        return probes;
    }
    for (Component* component : circuit->getComponents()) {
        if (component->isProbe()) {
            probes.push_back(component->asProbe());
        }
    }
    return probes;
}

void Simulator::simulate(int timeSteps) {
    if (!circuit) {
        return;
    }
    for (Component* component : circuit->getComponents()) {
        if (component->isInput()) {
            eventQueue.push({component, 0});
        } else {
            component->setOutputValue(false);
        }
    }
    int currentTime = 0;
    while (currentTime <= timeSteps) {
        std::vector<Event> eventsThisStep;
        while (!eventQueue.empty() && eventQueue.top().time == currentTime) {
            eventsThisStep.push_back(eventQueue.top());
            eventQueue.pop();
        }
        for (const Event& event : eventsThisStep) {
            bool oldValue = event.component->getOutputValue();
            bool newValue = event.component->calculateOutput();
            event.component->setOutputValue(newValue);
            for (Edge* edge : circuit->getEdges()) {
                if (edge->getSource() == event.component) {
                    Component* target = edge->getTarget();
                    int delay = target->getPropagationDelay();
                    eventQueue.push({target, currentTime + delay});
                }
            }
        }
        if (outputHandler) {
            displaySimulationResults(currentTime);
        }
        currentTime++;
    }
}

void Simulator::displaySimulationResults(int timeSteps) {
    std::vector<Probe*> probes = collectProbes();
    std::vector<Input*> inputs;
    for (Component* component : circuit->getComponents()) {
        if (component->isInput()) {
            inputs.push_back(component->asInput());
        }
    }
    std::cout << "Time step " << timeSteps << ":\n";
    for (Input* input : inputs) {
        std::cout << "Input " << input->getId() << ": "
                  << (input->getOutputValue() ? "HIGH" : "LOW") << "\n";
    }
    for (Probe* probe : probes) {
        std::cout << "Probe " << probe->getId() << ": "
                  << (probe->getRecordedValue() ? "HIGH" : "LOW") << "\n";
    }
    std::cout << "===================\n";
}
