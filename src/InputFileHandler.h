#ifndef INPUTFILEHANDLER_H
#define INPUTFILEHANDLER_H

#include "Circuit.h"
#include <string>
#include <memory>

/**
 * @brief Leest circuitbeschrijving uit een bestand
 */
class InputFileHandler {
public:
    InputFileHandler() = default;
    
    // Leest een circuitbeschrijving uit een bestand en maakt een Circuit object
    Circuit* readCircuit(const std::string& filename);

private:
    // Helper methoden voor het parseren van verschillende onderdelen van het bestand
    void parseComponents(Circuit* circuit, const std::string& content);
    void parseConnections(Circuit* circuit, const std::string& content);
};

#endif // INPUTFILEHANDLER_H