#include "InputFileHandler.h"
#include "ComponentFactory.h"
#include "LogicGate.h"
#include "Probe.h"
#include <fstream>
#include <sstream>
#include <string>
#include <map>

// Leest een circuit beschrijving uit een bestand
Circuit* InputFileHandler::readCircuit(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return nullptr;
    }

    // Lees de hele bestandsinhoud in een string
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    
    // Maak een nieuw circuit
    Circuit* circuit = new Circuit();
    
    // Parse het bestand
    try {
        parseComponents(circuit, content);
        parseConnections(circuit, content);
    }
    catch (const std::exception& e) {
        // Bij een fout, ruim het circuit op en return nullptr
        delete circuit;
        return nullptr;
    }
    
    return circuit;
}

// Helper methode om de componenten te parsen uit de bestandsinhoud
void InputFileHandler::parseComponents(Circuit* circuit, const std::string& content) {
    // Eenvoudige parselogica voor demonstratie
    
    std::istringstream stream(content);
    std::string line;
    
    // Lees het bestand regel voor regel
    while (std::getline(stream, line)) {
        if (line.empty() || line[0] == '#') {
            continue; // Sla lege regels en commentaar over
        }
        
        std::istringstream lineStream(line);
        std::string type, id;
        int delay = 1; // standaard vertraging
        
        lineStream >> type >> id;
        
        // Gebruik de ComponentFactory om component te maken
        try {
            if (type == "AND" || type == "OR" || type == "NOT" || 
                type == "NAND" || type == "NOR" || type == "XOR") {
                lineStream >> delay; // probeer een vertraging te lezen
            }
            
            Component* component = ComponentFactory::createComponent(type, id, delay);
            circuit->addComponent(component);
        }
        catch (const std::exception& e) {
            // Ongeldig componenttype, sla over
        }
    }
}

// Helper methode om de verbindingen tussen componenten te parsen
void InputFileHandler::parseConnections(Circuit* circuit, const std::string& content) {
    std::istringstream stream(content);
    std::string line;
    
    // Lees het bestand regel voor regel
    while (std::getline(stream, line)) {
        if (line.empty() || line[0] == '#' || line.find("CONNECT") == std::string::npos) {
            continue; // Sla lege regels, commentaar en niet-verbindingsregels over
        }
        
        std::istringstream lineStream(line);
        std::string connect, sourceId, targetId;
        
        lineStream >> connect >> sourceId >> targetId;
        
        if (connect == "CONNECT") {
            Component* source = circuit->getComponent(sourceId);
            Component* target = circuit->getComponent(targetId);
            
            if (source && target) {
                circuit->addEdge(new Edge(source, target));
                
                // Als het een LogicGate is, voeg de input toe aan de gate
                if (target->isLogicGate()) {
                    LogicGate* gate = target->asLogicGate();
                    gate->addInput(source);
                }
                
                // Als het target een Probe is, laat het de source observeren
                if (target->isProbe()) {
                    Probe* probe = target->asProbe();
                    probe->observeComponent(source);
                }
            }
        }
    }
}