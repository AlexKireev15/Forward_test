#include <iostream>
#include <fstream>
#include <string>
#include "EngineTester/EngineTester.h"
#include "Engine/DefaultEngine.h"
#include "Test/TemperatureTest.h"

using namespace std;
using namespace Engine;
using namespace Test;

typedef DefaultEngine::PropertiesReader DEPropertiesReader;

int main(int argv, char **argc) {
	double ambientTemperature = 10.0;
	setlocale(LC_ALL, "Russian");
	std::cout << "Температура окружающей среды (С°): ";
	std::cin >> ambientTemperature;

	DEPropertiesReader propReader;
	Properties prop = propReader.readProperties("resources/DefaultEngineProperties.txt");

	IEngine *engine = new DefaultEngine(prop, ambientTemperature);
	ITest *tempTest = new TemperatureTest();

	EngineTester engineTester(ambientTemperature);
	engineTester.setEngine("Default Engine", engine);
	engineTester.addTest("Temperature test", tempTest);

	Data tTestData = engineTester.runTest("Temperature test", true);
	cout << tTestData.workTime << " сек." << endl;

	delete engine;
	delete tempTest;
	system("pause");
	return 0;
}