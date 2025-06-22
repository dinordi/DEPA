#include "OutputHandler.h"

OutputHandler::OutputHandler(std::ostream& output)
    : output(&output), usingFileStream(false) {}

OutputHandler::OutputHandler(const std::string& filename)
    : usingFileStream(true) {
    fileStream.open(filename);
    output = &fileStream;
}

OutputHandler::~OutputHandler() {
    if (usingFileStream && fileStream.is_open()) {
        fileStream.close();
    }
}

void OutputHandler::writeResults(const std::vector<Probe*>& probes) {
    if (!output) return;
    *output << "Simulation Results:" << std::endl;
    *output << "===================" << std::endl;
    for (auto probe : probes) {
        *output << "Probe " << probe->getId() << ": "
                << (probe->getRecordedValue() ? "HIGH" : "LOW") << std::endl;
    }
    *output << "===================" << std::endl;
}
