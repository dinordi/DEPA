#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Circuit.h"
#include "InputFileHandler.h"
#include "OutputHandler.h"
#include "Probe.h"
#include "Input.h"
#include <vector>
#include <queue>
#include <functional>
#include <utility>

/**
 * @brief Simuleert het circuit met tijdsynchronisatie
 */
class Simulator {
public:
    Simulator(Circuit* circuit = nullptr);
    
    void setCircuit(Circuit* circuit);
    Circuit* getCircuit() const;
    
    void setInputFileHandler(InputFileHandler* handler);
    void setOutputHandler(OutputHandler* handler);
    
    // Laadt een circuit uit een bestand
    bool loadCircuit(const std::string& filename);
    
    // Start de simulatie
    void simulate(int timeSteps);
    void processEventsAtTimeStep(int currentStep);

    // Display probe outputs for all clock cycles
    void displaySimulationResults(int timeSteps);
    
private:
    // Event voor de simulatie: component + tijdstip
    struct Event {
        Component* component;
        int time;
        
        // Vergelijking voor priority queue (kleinere tijd eerst)
        bool operator>(const Event& other) const {
            return time > other.time;
        }
    };

    // Verzamel alle probes in het circuit
    std::vector<Probe*> collectProbes();
    
    Circuit* circuit;                        // Het circuit dat we simuleren
    InputFileHandler* inputFileHandler;      // Voor het laden van het circuit
    OutputHandler* outputHandler;            // Voor het uitvoeren van de resultaten
    
    // Priority queue voor gebeurtenissen, gesorteerd op tijd
    std::priority_queue<Event, std::vector<Event>, std::greater<Event>> eventQueue;
};

// Implementaties
inline Simulator::Simulator(Circuit* circuit)
    : circuit(circuit), inputFileHandler(nullptr), outputHandler(nullptr) {}

inline void Simulator::setCircuit(Circuit* circuit) {
    this->circuit = circuit;
}

inline Circuit* Simulator::getCircuit() const {
    return circuit;
}

inline void Simulator::setInputFileHandler(InputFileHandler* handler) {
    inputFileHandler = handler;
}

inline void Simulator::setOutputHandler(OutputHandler* handler) {
    outputHandler = handler;
}

inline bool Simulator::loadCircuit(const std::string& filename) {
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

inline std::vector<Probe*> Simulator::collectProbes() {
    std::vector<Probe*> probes;
    
    if (!circuit) {
        return probes;
    }
    
    // Gebruik polymorfisme in plaats van dynamic_cast
    for (Component* component : circuit->getComponents()) {
        if (component->isProbe()) {
            probes.push_back(component->asProbe());
        }
    }
    
    return probes;
}

inline void Simulator::simulate(int timeSteps) {
    if (!circuit) {
        return;
    }
    
    // Zet alle events in de queue voor t=0
    for (Component* component : circuit->getComponents()) {
        if (component->isInput()) {
            eventQueue.push({component, 0});
        }
        else
        {
            component->setOutputValue(false); // Initialiseer niet-ingestelde componenten
        }
    }
    
    // Verwerk events tot aan timeSteps
    int currentTime = 0;
    int steps = 0;
    while (!eventQueue.empty() && currentTime <= timeSteps) {
        steps++;
        // Haal het volgende event op
        Event event = eventQueue.top();
        eventQueue.pop();
        
        // Update de huidige tijd
        currentTime = event.time;
        if (currentTime > timeSteps) {
            break;
        }
        
        // Bereken de nieuwe output
        bool oldValue = event.component->getOutputValue();
        bool newValue = event.component->calculateOutput();
        
        // Als de waarde is veranderd, update en plan nieuwe events voor verbonden componenten
        if (newValue != oldValue || event.component->isInput()) {
            event.component->setOutputValue(newValue);
            
            // Vind alle edges die deze component als source hebben
            for (Edge* edge : circuit->getEdges()) {
                if (edge->getSource() == event.component) {
                    // Plan een nieuw event voor de target component
                    Component* target = edge->getTarget();
                    int delay = target->getPropagationDelay();
                    eventQueue.push({target, currentTime + delay});
                }
            }
        }
    // Schrijf resultaten als er een OutputHandler is
    if (outputHandler) {
        std::vector<Probe*> probes = collectProbes();
        // outputHandler->writeResults(probes);
        displaySimulationResults(steps);
    }
    }
    
}

inline void Simulator::displaySimulationResults(int timeSteps) {
    std::vector<Probe*> probes = collectProbes();
    std::vector<Input*> inputs;

    // Collect all inputs in the circuit
    for (Component* component : circuit->getComponents()) {
        if (component->isInput()) {
            inputs.push_back(component->asInput());
        }
    }

    std::cout << "Time step " << timeSteps << ":\n";

    // Display input values
    for (Input* input : inputs) {
        std::cout << "Input " << input->getId() << ": "
                    << (input->getOutputValue() ? "HIGH" : "LOW") << "\n";
    }

    // Display probe values
    for (Probe* probe : probes) {
        std::cout << "Probe " << probe->getId() << ": "
                    << (probe->getRecordedValue() ? "HIGH" : "LOW") << "\n";
    }

    std::cout << "===================\n";

}

#endif // SIMULATOR_H