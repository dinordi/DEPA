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

#endif // OUTPUTHANDLER_H