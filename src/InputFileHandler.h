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
    InputFileHandler();
    
    // Leest een circuitbeschrijving uit een bestand en maakt een Circuit object
    Circuit* readCircuit(const std::string& filename);

    /**
     * @brief Initialize prototypes for the ComponentFactory
     */
    void initializePrototypes();

private:
    // Helper methoden voor het parseren van verschillende onderdelen van het bestand
    void parseComponent(Circuit* circuit, const std::string& line);
    void parseConnection(Circuit* circuit, const std::string& line);
};

#endif // INPUTFILEHANDLER_H