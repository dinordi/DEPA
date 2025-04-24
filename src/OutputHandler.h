#ifndef OUTPUTHANDLER_H
#define OUTPUTHANDLER_H

#include "Probe.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

/**
 * @brief Schrijft simulatieresultaten
 */
class OutputHandler {
public:
    OutputHandler(std::ostream& output = std::cout);
    OutputHandler(const std::string& filename);
    ~OutputHandler();
    
    // Schrijft de resultaten van de simulatie (probe waarden)
    void writeResults(const std::vector<Probe*>& probes);
    
private:
    std::ostream* output;       // Output stream (console of bestand)
    std::ofstream fileStream;   // Bestandsstream indien nodig
    bool usingFileStream;       // Flag om aan te geven of we een bestand gebruiken
};

// Implementaties
inline OutputHandler::OutputHandler(std::ostream& output) 
    : output(&output), usingFileStream(false) {}

inline OutputHandler::OutputHandler(const std::string& filename) 
    : usingFileStream(true) {
    fileStream.open(filename);
    output = &fileStream;
}

inline OutputHandler::~OutputHandler() {
    if (usingFileStream && fileStream.is_open()) {
        fileStream.close();
    }
}

inline void OutputHandler::writeResults(const std::vector<Probe*>& probes) {
    if (!output) return;
    
    *output << "Simulation Results:" << std::endl;
    *output << "===================" << std::endl;
    
    for (auto probe : probes) {
        *output << "Probe " << probe->getId() << ": " 
                << (probe->getRecordedValue() ? "HIGH" : "LOW") << std::endl;
    }
    
    *output << "===================" << std::endl;
}

#endif // OUTPUTHANDLER_H