#include "Circuit.h"
#include "Simulator.h"
#include "InputFileHandler.h"
#include "OutputHandler.h"
#include "ComponentFactory.h"
#include <iostream>
#include <memory>
#include <string>

int main(int argc, char* argv[]) {
    std::cout << "Circuit Simulator" << std::endl;
    std::cout << "=================" << std::endl;
    
    // Controleer of het bestandspad als argument is meegegeven
    if (argc < 2) {
        std::cout << "Gebruik: " << argv[0] << " <pad_naar_circuit_bestand>" << std::endl;
        std::cout << "Bijvoorbeeld: " << argv[0] << " test_circuits/full_adder.txt" << std::endl;
        return 1;
    }
    
    std::string circuitFilePath = argv[1];
    std::cout << "Circuit bestand: " << circuitFilePath << std::endl;
    
    // Maak de input handler en simulator
    InputFileHandler inputFileHandler;
    OutputHandler outputHandler;
    Simulator simulator;
    
    // Stel de handlers in
    simulator.setInputFileHandler(&inputFileHandler);
    simulator.setOutputHandler(&outputHandler);
    
    // Laad het circuit uit het bestand
    if (!simulator.loadCircuit(circuitFilePath)) {
        std::cout << "Fout bij het laden van het circuit uit bestand: " << circuitFilePath << std::endl;
        return 1;
    }
    
    std::cout << "Circuit succesvol geladen." << std::endl;
    
    // Simuleer het circuit voor een aantal tijdstappen
    std::cout << "\nStart simulatie..." << std::endl;
    simulator.simulate(10); // Simuleer voor 10 tijdstappen
    
    // Het circuit wordt automatisch opgeruimd door de simulator destructor
    std::cout << "\nSimulatie voltooid." << std::endl;
    
    return 0;
}