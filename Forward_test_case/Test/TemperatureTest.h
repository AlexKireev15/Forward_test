#pragma once
#include "Test.h"
namespace Test {
	class TemperatureTest : public ITest {
	private:
		bool logFlag = false;
	public:
		TemperatureTest() { }
		virtual Engine::Data run(Engine::IEngine* engine);
		virtual Engine::Data run(const std::string &name, Engine::IEngine* engine, bool logFlag);
		virtual ~TemperatureTest() {}
	};
}