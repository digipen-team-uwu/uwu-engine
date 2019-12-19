#pragma once
#include <list>

class Timer
{
public:
  Timer(float duration);
  Timer();
  ~Timer();
  
  bool Finished();
  bool Running();

  void SetDuration(float newDuration);

  void Start();
  void Stop();

  friend class TimerManager;
private:
  void Update();
  float duration;
  float time;
  bool running;
};

class TimerManager
{
public:
  void Update();
  friend class Timer;
private:
  std::list<Timer*> timers;
};