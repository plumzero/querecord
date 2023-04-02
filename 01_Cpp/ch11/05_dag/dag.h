
#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

class Module {
public:
  Module(const std::string& name, const std::vector<std::string>& deps): _name(name), _deps(deps) {}
  virtual void execute() = 0;
  const std::string& name() const { return _name; };
  const std::vector<std::string>& deps() const { return _deps; };
private:
  std::string _name;
  std::vector<std::string> _deps;
};

class ModuleA: public Module {
public:
  ModuleA(const std::string& name, const std::vector<std::string>& deps): Module(name, deps) {}
  void execute() override {
    std::cout << "executing ModuleA: " << name() << std::endl;
  }
};

class ModuleB: public Module {
public:
  ModuleB(const std::string& name, const std::vector<std::string>& deps): Module(name, deps) {}
  void execute() override {
    std::cout << "executing moduleB: " << name() << std::endl;
  }
};

class Executor {
public:
  void add(Module* m) {
    _modules[m->name()] = m;
  }
  void execute() {
    std::unordered_map<std::string, bool> visited;
    for (auto& pair: _modules) {
      if (! visited[pair.first]) {
          exec(pair.second, visited);
      }
    }
  }

private:
  void exec(Module* m, std::unordered_map<std::string, bool>& visited) {
    visited[m->name()] = true;
    for (auto& dep : m->deps()) {
      if (! visited[dep]) {
        exec(_modules[dep], visited);
      }
    }
    m->execute();
  }
  // members variables
  std::unordered_map<std::string, Module*> _modules;
};
