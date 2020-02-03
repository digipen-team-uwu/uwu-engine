#pragma once
#include <list>
#include <UWUEngine/System.h>

namespace UWUEngine
{

class TimerSys final : public System
{
public:
  TimerSys(ISpace*);
  void Update() override;

  class Timer
  {
    friend class TimerSys;
  public:
    Timer(TimerSys& parent, float duration = 0);
    ~Timer();

    bool Finished();
    bool Running() const;

    void SetDuration(float newDuration);

    void Start();
    void Stop();

  private:
    void Update();
    float duration;
    float time;
    bool running;
    TimerSys& parent;
  };

  void AddTimer(Timer*);
  void RemoveTimer(Timer*);

private:
  std::list<Timer*> timers;
};

} // namespace UWUEngine
