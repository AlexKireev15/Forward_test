#pragma once
#include <string>
#include <fstream>
#include <vector>
namespace Engine {
	struct Properties {
		double MInertia;
		std::vector<std::pair<int, int>> MV;
		double overheatTemperature;
		double HM;
		double HV;
		double C;
	};
	struct Data {
		unsigned int workTime = 0;
		double temperature;
		double M = 0.0;
		double a = 0.0;
		double V = 0.0;
		double Vh = 0.0;
		double Vc = 0.0;
	};

	class IPropertiesReader {
	public:
		virtual Properties readProperties(const std::string&) = 0;
		virtual Properties readProperties(std::ifstream&) = 0;
		virtual Properties getProperties() = 0;
		virtual ~IPropertiesReader() {}
	};

	class IEngine {
	public:
		virtual Data iterate() = 0;
		virtual Data getData() = 0;
		virtual Properties getProperties() = 0;
		virtual void reset() = 0;
		virtual ~IEngine() {}
	};
}