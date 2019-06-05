#include "EngineTester.h"
#include <exception>
#include <string>
void EngineTester::setEngine(const std::string &name, Engine::IEngine *engine) throw(std::exception) {
	if (engine == nullptr) throw std::exception("Bad engine ptr");
	this->name = name;
	this->engine = engine;
}
void EngineTester::addTest(const std::string &name, Test::ITest *test) {
	this->tests.emplace(name, test);
}
Data EngineTester::runTest(const std::string &name){
	auto it = tests.find(name);
	if (it == tests.end()) {
		throw std::exception(("No such test: " + name).data());
	}
	Data data = it->second->run(this->engine);
	return data;
}
Data EngineTester::runTest(const std::string &name, bool logFlag) {
	auto it = tests.find(name);
	if (it == tests.end()) {
		throw std::exception(("No such test: " + name).data());
	}
	Data data = it->second->run(it->first, this->engine, logFlag);
	return data;
}
void EngineTester::runAllTests(Data **data){
	
}
EngineTester::~EngineTester() { }