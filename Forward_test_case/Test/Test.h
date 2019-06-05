#pragma once
#include "../Engine/Engine.h"
namespace Test {
	class ITest {
	public:
		virtual Engine::Data run(Engine::IEngine *engine) = 0;
		virtual Engine::Data run(const std::string &name, Engine::IEngine *engine, bool logFlag) = 0;
		virtual ~ITest() { };
	};
}