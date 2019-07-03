#include "DefaultEngine.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace Engine;
DefaultEngine::DefaultEngine(const Properties &properties, double ambientTemperature) noexcept{
	this->properties = Engine::Properties(properties);
	this->data.temperature = ambientTemperature;
	this->ambientTemperature = ambientTemperature;
	this->data.workTime = 0;
}
DefaultEngine::~DefaultEngine() noexcept {}

double calculateY(double x1, double x2, double y1, double y2, double x) {
	return (double)((y2 - y1)*x + (x2*y1 - x1 * y2)) / (x2 - x1);
}

Data Engine::DefaultEngine::iterate() noexcept {
	data.V += (double) * data.a;
	unsigned int i;
	for (i = 1; i < properties.MV.size() - 1; ++i) {
		if (properties.MV[i - 1].second <= data.V && data.V <= properties.MV[i].second) {
			break;
		}
	}
	
	data.M = calculateY(properties.MV[i - 1].second, properties.MV[i].second,
		properties.MV[i - 1].first, properties.MV[i].first, data.V);
	data.a = (double)data.M / properties.MInertia;
	data.Vh = data.M * properties.HM + data.V * data.V * properties.HV;
	data.Vc = properties.C * (this->ambientTemperature - data.temperature);

	data.temperature += data.Vh;
	data.temperature += data.Vc;

	data.workTime += 1;
	return data;
}

Data Engine::DefaultEngine::getData() noexcept {
	return this->data;
}

Properties Engine::DefaultEngine::getProperties() noexcept {
	return this->properties;
}

void Engine::DefaultEngine::reset() noexcept{
	this->data.temperature = ambientTemperature;
	this->data.workTime = 0;
}

Properties DefaultEngine::PropertiesReader::parseFile(std::ifstream& in) {
	in >> properties.MInertia;
	in.get();
	std::string strM, strV;
	std::getline(in, strM);
	std::getline(in, strV);
	std::stringstream sstrM(strM);
	std::stringstream sstrV(strV);
	std::string M, V;
	while (std::getline(sstrM, M, delimeter) && std::getline(sstrV, V, delimeter)) {
		properties.MV.push_back(std::pair<int, int>(stoi(M), stoi(V)));
	}
	if (!sstrM.eof() || !sstrV.eof()) std::cout << "MV dependence is not full!" << std::endl;
	in >> properties.overheatTemperature
		>> properties.HM
		>> properties.HV
		>> properties.C;
	return properties;
}
Properties DefaultEngine::PropertiesReader::readProperties(const std::string &fileName) {
	std::ifstream in(fileName, std::ifstream::in);
	return parseFile(in);
}
Properties Engine::DefaultEngine::PropertiesReader::readProperties(std::ifstream &in){
	return parseFile(in);
}
Properties Engine::DefaultEngine::PropertiesReader::getProperties()
{
	return properties;
}
