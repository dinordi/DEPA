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

#endif // SIMULATOR_H