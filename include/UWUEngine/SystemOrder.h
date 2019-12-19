#pragma once

enum class SystemUpdateOrder
{
  FIRST        = 0,
  FrameRate    = 9250,
  StateMachine = 9300,
  Editor       = 9350,
  Entity       = 9600,
  TexLoad      = 9603,
  Atlas        = 9606,
  EntityVec    = 9609,
  UI           = 9612,
  HUD          = 9625,
  Light        = 9650,
  Debug        = 9700,
  Timer        = 9750,
  Camera       = 9800,
  Render       = 9850,
  Action       = 9860,
  Input        = 9870,
  Window       = 9900,
  LAST         = 10000,
  INVALID      = -1,
};

enum class SystemInitOrder
{
  Trace         = 0, // Don't put anything before this one
  FIRST         = 1,
  Window        = 9450,
  Editor        = 9500,
  Input         = 9550,
  Action        = 9570,
  Cacher        = 9650,
  Entity        = 9750,
  TexLoad       = 9755,
  Atlas         = 9758,
  EntityVec     = 9760,
  UI            = 9762,
  HUD           = 9775,
  Light         = 9800,
  Debug         = 9850,
  Render        = 9900,
  LAST          = 10000,
  StateMachine  = -2, // IT IS NOT AN ERROR THAT STATE MACHINE COMES AFTER THE LAST SYSTEM
  INVALID = -1,
};

enum class ComponentUpdateOrder
{
  Animation,
  SpineAnimation,
  SpineSkeleton,
  Behavior,
  Physics,
  Collider,
  LAST,
  INVALID = -1,
};