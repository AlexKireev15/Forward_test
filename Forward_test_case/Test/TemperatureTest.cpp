#include "TemperatureTest.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <sstream>
Engine::Data Test::TemperatureTest::run(const std::string &name, Engine::IEngine *engine, bool logFlag) {
	double overheatTemp = engine->getProperties().overheatTemperature;
	if (logFlag) {
		std::stringstream sstr;
		sstr << "tests/" << name << time(0) << ".txt";
		std::string name = sstr.str();
		std::ofstream logOut(name, std::ofstream::ate);
		logOut << "Engine overheat temperature (C°): " << overheatTemp << std::endl;
		Engine::Data data = engine->getData();
		while (data.temperature < overheatTemp) {
			logOut << "Time step " << data.workTime << std::endl <<
				"\tCrankshaft rotation speed(Rad/sec): " << data.V << std::endl <<
				"\tSpin moment(H*m): " << data.M << std::endl <<
				"\tCrankshaft acceleration(m/sec^2): " << data.a << std::endl <<
				"\tHeat velocity(C°/sec): " << data.Vh << std::endl <<
				"\tCool velocity(C°/sec): " << data.Vc << std::endl <<
				"\tTemperature(C°): " << data.temperature << std::endl;			
			data = engine->iterate();
			if (!engine->isRelevantCalculation())
				break;
		}
		logOut << "Time step " << data.workTime << std::endl <<
			"\tCrankshaft rotation speed(Rad/sec): " << data.V << std::endl <<
			"\tSpin moment(H*m): " << data.M << std::endl <<
			"\tCrankshaft acceleration(m/sec^2): " << data.a << std::endl <<
			"\tHeat velocity(C°/sec): " << data.Vh << std::endl <<
			"\tCool velocity(C°/sec): " << data.Vc << std::endl <<
			"\tTemperature(C°): " << data.temperature << std::endl;
		logOut.close();
	}
	else {
		while (engine->getData().temperature < overheatTemp) {
			engine->iterate();
		}
	}
	return engine->getData();
}
Engine::Data Test::TemperatureTest::run(Engine::IEngine *engine) {
	return this->run("", engine, false);
}