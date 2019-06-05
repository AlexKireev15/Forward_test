#pragma once
#include "../Engine/Engine.h"
#include "../Test/Test.h"
#include <map>
typedef Engine::Data Data;
class EngineTester {
private:
	double ambientTemperature;
	std::string name;
	Engine::IEngine *engine;
	std::map<std::string, Test::ITest*> tests;
public:
	EngineTester(double ambientTemperature) : ambientTemperature(ambientTemperature) {}
	virtual void setEngine(const std::string &name, Engine::IEngine *engine);
	virtual void addTest(const std::string &name, Test::ITest *test);
	virtual Data runTest(const std::string &name);
	virtual Data runTest(const std::string &name, bool logFlag);
	virtual void runAllTests(Data**);
	virtual ~EngineTester();
};
