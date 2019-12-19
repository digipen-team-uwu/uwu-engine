#pragma once

class IBaseSystem
{
public:
  IBaseSystem() = default;
  virtual void Update() = 0;
  virtual ~IBaseSystem() = default;
  IBaseSystem(const IBaseSystem&) = delete;
  void operator=(const IBaseSystem&) = delete;
  IBaseSystem(const IBaseSystem&&) = delete;
  void operator=(const IBaseSystem&&) = delete;
};

template<typename T>
class RegisterSystemHelper;

template <typename T>
class BaseSystem : public IBaseSystem, public RegisterSystemHelper<T>
{
public:
  BaseSystem() = default;
  void Update() override {};
  ~BaseSystem() = default;
  BaseSystem(const BaseSystem&) = delete;
  void operator=(const BaseSystem&) = delete;
  BaseSystem(const BaseSystem&&) = delete;
  void operator=(const BaseSystem&&) = delete;
};

#include "BaseSystem.inline.cpp" /* Template implementations. */
