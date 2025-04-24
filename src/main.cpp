#include "Circuit.h"
#include "Simulator.h"
#include "InputFileHandler.h"
#include "OutputHandler.h"
#include "ComponentFactory.h"
#include <iostream>
#include <memory>
#include <string>

// Voorbeeld functie om een handmatig circuit te maken (een half adder)
Circuit* createHalfAdderCircuit() {
    Circuit* circuit = new Circuit();
    
    // Maak de componenten met de ComponentFactory (Factory pattern)
    Component* inputA = ComponentFactory::createComponent(ComponentFactory::ComponentType::INPUT, "A");
    Component* inputB = ComponentFactory::createComponent(ComponentFactory::ComponentType::INPUT, "B");
    Component* andGate = ComponentFactory::createComponent(ComponentFactory::ComponentType::AND, "AND1");
    Component* xorGate = ComponentFactory::createComponent(ComponentFactory::ComponentType::XOR, "XOR1");
    Component* carryProbe = ComponentFactory::createComponent(ComponentFactory::ComponentType::PROBE, "Carry");
    Component* sumProbe = ComponentFactory::createComponent(ComponentFactory::ComponentType::PROBE, "Sum");
    
    // Voeg componenten toe aan het circuit
    circuit->addComponent(inputA);
    circuit->addComponent(inputB);
    circuit->addComponent(andGate);
    circuit->addComponent(xorGate);
    circuit->addComponent(carryProbe);
    circuit->addComponent(sumProbe);
    
    // Configureer inputs voor de gates met de polymorfische interface
    andGate->asLogicGate()->addInput(inputA);
    andGate->asLogicGate()->addInput(inputB);
    
    xorGate->asLogicGate()->addInput(inputA);
    xorGate->asLogicGate()->addInput(inputB);
    
    // Verbind de componenten met edges
    circuit->addEdge(new Edge(inputA, andGate));
    circuit->addEdge(new Edge(inputB, andGate));
    circuit->addEdge(new Edge(andGate, carryProbe));
    
    circuit->addEdge(new Edge(inputA, xorGate));
    circuit->addEdge(new Edge(inputB, xorGate));
    circuit->addEdge(new Edge(xorGate, sumProbe));
    
    // Set up observers (Observer pattern)
    carryProbe->asProbe()->observeComponent(andGate);
    sumProbe->asProbe()->observeComponent(xorGate);
    
    return circuit;
}

// Voorbeeld van hoe een circuit te simuleren
void simulateHalfAdder(Circuit* circuit) {
    // Zet input waarden, zonder casts te gebruiken
    Component* componentA = circuit->getComponent("A");
    Component* componentB = circuit->getComponent("B");
    
    if (componentA && componentB && componentA->isInput() && componentB->isInput()) {
        Input* inputA = componentA->asInput();
        Input* inputB = componentB->asInput();
        
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