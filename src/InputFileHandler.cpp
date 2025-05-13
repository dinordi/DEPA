#include "InputFileHandler.h"
#include "ComponentFactory.h"
#include "LogicGate.h"
#include "Probe.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <cctype>

// Functie om whitespace te verwijderen aan begin en einde van een string
std::string trimWhitespace(const std::string& str) {
    auto start = std::find_if_not(str.begin(), str.end(), [](unsigned char c) { return std::isspace(c); });
    auto end = std::find_if_not(str.rbegin(), str.rend(), [](unsigned char c) { return std::isspace(c); }).base();
    
    return (start < end ? std::string(start, end) : std::string());
}

// ComponentFactory instance
ComponentFactory componentFactory;


InputFileHandler::InputFileHandler() {
    // Initialiseer de prototypes
    initializePrototypes();
}

// Methode om prototypes te initialiseren
void InputFileHandler::initializePrototypes() {
    componentFactory.registerPrototype("AND", new ANDGate("prototype"));
    componentFactory.registerPrototype("OR", new ORGate("prototype"));
    componentFactory.registerPrototype("NOT", new NOTGate("prototype"));
    componentFactory.registerPrototype("NAND", new NANDGate("prototype"));
    componentFactory.registerPrototype("NOR", new NORGate("prototype"));
    componentFactory.registerPrototype("XOR", new XORGate("prototype"));
    componentFactory.registerPrototype("INPUT", new Input("prototype"));
    componentFactory.registerPrototype("PROBE", new Probe("prototype"));
    componentFactory.registerPrototype("INPUT_HIGH", new Input("prototype"));
    componentFactory.registerPrototype("INPUT_LOW", new Input("prototype"));
}

// Leest een circuit beschrijving uit een bestand
Circuit* InputFileHandler::readCircuit(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Kan bestand niet openen: " << filename << std::endl;
        return nullptr;
    }

    // Lees de hele bestandsinhoud in een string
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    
    // Maak een nieuw circuit
    Circuit* circuit = new Circuit();
    
    // Split de content in regels
    std::istringstream contentStream(content);
    std::vector<std::string> lines;
    std::string line;
    
    while (std::getline(contentStream, line)) {
        // Verwijder commentaar en whitespace
        size_t commentPos = line.find('#');
        if (commentPos != std::string::npos) {
            line = line.substr(0, commentPos);
        }
        line = trimWhitespace(line);
        
        // Voeg alleen niet-lege regels toe
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
    
    // Parse het bestand
    try {
        // Ensure all components are added to the circuit before parsing connections
        for (auto it = lines.begin(); it != lines.end();) {
            const std::string& line = *it;
            if (line.find("INPUT_HIGH") != std::string::npos || 
                line.find("INPUT_LOW") != std::string::npos ||
                line.find("PROBE") != std::string::npos ||
                (line.find("OR;") != std::string::npos && line.find("XOR;") == std::string::npos) ||
                line.find("AND;") != std::string::npos ||
                line.find("NOT;") != std::string::npos ||
                line.find("NAND;") != std::string::npos ||
                line.find("NOR;") != std::string::npos ||
                line.find("XOR;") != std::string::npos) 
            {
                parseComponent(circuit, line);
                // Remove the component from the lines vector to avoid re-parsing
                // std::cout << "Component geparsed: " << line << std::endl;
                it = lines.erase(it);
            } else {
                ++it;
            }
        }
        std::cout << "Componenten geparsed, nu verbindingen. Grootte lines: " << lines.size() << std::endl;
        // Parseer vervolgens alle verbindingen
        for (auto it = lines.begin(); it != lines.end();) {
            const std::string& line = *it;
            size_t colonPos = line.find(':');
            size_t semicolonPos = line.find(';');
            if (colonPos != std::string::npos && semicolonPos != std::string::npos) {
                // Extraheer de source node ID (voor de dubbele punt)
                std::string sourceId = trimWhitespace(line.substr(0, colonPos));
                
                // Haal de source component op
                Component* source = circuit->getComponent(sourceId);
                if (source) {
                    // Dit is waarschijnlijk een verbindingsdefinitie
                    parseConnection(circuit, line);
                    // Verwijder de verbinding uit de regels vector
                    it = lines.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }
    catch (const std::exception& e) {
        std::cout << "Fout bij het parseren van het circuit: " << e.what() << std::endl;
        // Bij een fout, ruim het circuit op en return nullptr
        delete circuit;
        return nullptr;
    }
    
    return circuit;
}

// Helper methode om een componentdefinitie te parsen
void InputFileHandler::parseComponent(Circuit* circuit, const std::string& line) {
    size_t colonPos = line.find(':');
    size_t semicolonPos = line.find(';');
    
    if (colonPos != std::string::npos && semicolonPos != std::string::npos) {
        // Extraheer de node ID (voor de dubbele punt)
        std::string nodeId = trimWhitespace(line.substr(0, colonPos));
        
        // Extraheer het node type (tussen de dubbele punt en de puntkomma)
        std::string nodeType = trimWhitespace(line.substr(colonPos + 1, semicolonPos - colonPos - 1));
        
        // Converteer naar component type
        try {
            Component* component = componentFactory.createComponent(nodeType, nodeId);

            if (nodeType == "INPUT_HIGH") {
                component->setOutputValue(true);
            } else if (nodeType == "INPUT_LOW") {
                component->setOutputValue(false);
            }

            circuit->addComponent(component);
            std::cout << "Component toegevoegd: " << nodeId << " van type " << nodeType << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << "Fout bij het maken van component: " << e.what() << std::endl;
        }
    }
}

// Helper methode om een verbindingsdefinitie te parsen
void InputFileHandler::parseConnection(Circuit* circuit, const std::string& line) {
    size_t colonPos = line.find(':');
    size_t semicolonPos = line.find(';');
    
    if (colonPos != std::string::npos && semicolonPos != std::string::npos) {
        // Extraheer de source node ID (voor de dubbele punt)
        std::string sourceId = trimWhitespace(line.substr(0, colonPos));
        
        // Extraheer de target node IDs (tussen de dubbele punt en de puntkomma)
        std::string targetsStr = trimWhitespace(line.substr(colonPos + 1, semicolonPos - colonPos - 1));
        
        // Verkrijg de source component
        Component* source = circuit->getComponent(sourceId);
        if (!source) {
            std::cout << "Source component niet gevonden: " << sourceId << std::endl;
            return;
        }
        
        // Split de target string op komma's
        std::istringstream targetsStream(targetsStr);
        std::string targetId;
        
        while (std::getline(targetsStream, targetId, ',')) {
            targetId = trimWhitespace(targetId);
            
            // Verkrijg de target component
            Component* target = circuit->getComponent(targetId);
            if (!target) {
                std::cout << "Target component niet gevonden: " << targetId << std::endl;
                continue;
            }
            
            // Maak een nieuwe edge
            circuit->addEdge(new Edge(source, target));
            std::cout << "Edge toegevoegd: " << sourceId << " -> " << targetId << std::endl;
            
            // Als het target een LogicGate is, voeg de source toe aan zijn inputs
            if (target->isLogicGate()) {
                target->asLogicGate()->addInput(source);
            }
            
            // Als het target een Probe is, laat het de source observeren
            if (target->isProbe()) {
                target->asProbe()->observeComponent(source);
            }
        }
    }
}