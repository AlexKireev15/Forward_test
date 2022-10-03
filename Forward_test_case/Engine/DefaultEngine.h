#pragma once
#include "Engine.h"
namespace Engine {
	class DefaultEngine : public IEngine {
	private:
		double ambientTemperature;
		Properties properties;
		Data data;
	public:
		class PropertiesReader : IPropertiesReader {
		private:
			Properties properties;
			std::ifstream input;
			char delimeter = ',';
			Properties parseFile(std::ifstream&);
		public:
			PropertiesReader() {}
			PropertiesReader(char delimeter) : delimeter(delimeter) {}
			Properties readProperties(const std::string&) final;
			Properties readProperties(std::ifstream&) final;
			Properties getProperties() final;
			~PropertiesReader(){ }
		};

		DefaultEngine(const Properties &properties, double ambientTemperature) noexcept;
		~DefaultEngine() noexcept final;
		virtual Data iterate() noexcept final;
		virtual Data getData() noexcept final;
		virtual Properties getProperties() noexcept final;
		virtual bool isRelevantCalculation() noexcept final;
		virtual void reset() noexcept final;
	};
}