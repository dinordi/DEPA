#include "Circuit.h"
#include "Simulator.h"
#include "InputFileHandler.h"
#include "OutputHandler.h"
#include "ANDGate.h"
#include "ORGate.h"
#include "NOTGate.h"
#include "XORGate.h"  // Toegevoegd voor XORGate gebruik
#include "Input.h"
#include "Probe.h"
#include <iostream>
#include <memory>
#include <string>

// Voorbeeld functie om een handmatig circuit te maken (een half adder)
Circuit* createHalfAdderCircuit() {
    Circuit* circuit = new Circuit();
    
    // Maak de componenten
    Input* inputA = new Input("A");
    Input* inputB = new Input("B");
    ANDGate* andGate = new ANDGate("AND1");
    XORGate* xorGate = new XORGate("XOR1");
    Probe* carryProbe = new Probe("Carry");
    Probe* sumProbe = new Probe("Sum");
    
    // Voeg componenten toe aan het circuit
    circuit->addComponent(inputA);
    circuit->addComponent(inputB);
    circuit->addComponent(andGate);
    circuit->addComponent(xorGate);
    circuit->addComponent(carryProbe);
    circuit->addComponent(sumProbe);
    
    // Configureer inputs voor de gates explicit
    andGate->addInput(inputA);
    andGate->addInput(inputB);
    
    xorGate->addInput(inputA);
    xorGate->addInput(inputB);
    
    // Verbind de componenten (maak edges)
    // AND gate connections
    circuit->addEdge(new Edge(inputA, andGate));
    circuit->addEdge(new Edge(inputB, andGate));
    circuit->addEdge(new Edge(andGate, carryProbe));
    
    // XOR gate connections
    circuit->addEdge(new Edge(inputA, xorGate));
    circuit->addEdge(new Edge(inputB, xorGate));
    circuit->addEdge(new Edge(xorGate, sumProbe));
    
    return circuit;
}

// Voorbeeld van hoe een circuit te simuleren
void simulateHalfAdder(Circuit* circuit) {
    // Zet input waarden
    Input* inputA = dynamic_cast<Input*>(circuit->getComponent("A"));
    Input* inputB = dynamic_cast<Input*>(circuit->getComponent("B"));
    
    if (inputA && inputB) {
        std::cout << "Simulating Half Adder with various inputs..." << std::endl;
        OutputHandler outputHandler;
        Simulator simulator(circuit);
        simulator.setOutputHandler(&outputHandler);
        
        // Simuleer alle mogelijke input combinaties
        for (int i = 0; i < 4; i++) {
            bool a = (i & 0x01) != 0;
            bool b = (i & 0x02) != 0;
            
            inputA->setValue(a);
            inputB->setValue(b);
            
            std::cout << "\nInputs: A = " << (a ? "1" : "0") 
                      << ", B = " << (b ? "1" : "0") << std::endl;
            
            // Simuleer voor enkele tijdstappen
            simulator.simulate(5);
        }
    }
}

int main(int argc, char* argv[]) {
    std::cout << "Circuit Simulator Demo" << std::endl;
    std::cout << "======================" << std::endl;
    
    // Maak een circuit (half adder)
    Circuit* circuit = createHalfAdderCircuit();
    
    // Simuleer het circuit
    simulateHalfAdder(circuit);
    
    // Opruimen
    delete circuit;
    
    return 0;
}