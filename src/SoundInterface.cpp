/******************************************************************************/
  /*!
  \par        Project Umbra
  \file       SoundInterface.h
  \author     Zach Rammell
  \date       2019/09/16
  \brief      Implementation of a class to manage, play, and modify sounds.

  Copyright � 2019 DigiPen, All rights reserved.
  */
/******************************************************************************/

#include <UWUEngine/Audio/SoundInterface.h>
#include <UWUEngine/Debugs/TraceLogger.h>
#include "fmod_errors.h"
#include <document.h>
#include <istreamwrapper.h>
#include <fstream>
#include <UWUEngine/Debugs/ColoredOutput.h>

template<>
int RegisterSystemHelper<SoundInterface>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<SoundInterface>(SystemInitOrder::FIRST, SystemUpdateOrder::FIRST);

using namespace ColoredOutput;

FMOD::System* SoundInterface::system_;
std::map<std::string, FMOD::Sound*> SoundInterface::sounds_;
FMOD::ChannelGroup* SoundInterface::default_channel_;

SoundInterface::SoundInterface()
{
  // Create the main system object.
  FMOD_RESULT result = FMOD::System_Create(&system_);
  if (result != FMOD_OK)
  {
    TraceLogger::Log(TraceLogger::FAILURE) << "FMOD error! (" << result << ")" << FMOD_ErrorString(result);
  }

  // Initialize FMOD.
  result = system_->init(512, FMOD_INIT_NORMAL, 0);
  if (result != FMOD_OK)
  {
    TraceLogger::Log(TraceLogger::FAILURE) << "FMOD error! (" << result << ")" << FMOD_ErrorString(result);
  }

  result = system_->createChannelGroup("default", &default_channel_);
  if (result != FMOD_OK)
  {
    TraceLogger::Log(TraceLogger::FAILURE) << "FMOD error! (" << result << ")" << FMOD_ErrorString(result);
  }

  std::ifstream sounds_file("./data/sounds.json");
  rapidjson::IStreamWrapper wrapper(sounds_file);
  rapidjson::Document doc;

  doc.ParseStream(wrapper);

  if (doc.HasParseError())
  {
    TraceLogger::Log(TraceLogger::FAILURE, "sounds.json is invalid.\n");
    return;
  }

  for (auto sound = doc.MemberBegin(); sound != doc.MemberEnd(); ++sound)
  {
    auto& log_stream = TraceLogger::Log(TraceLogger::SERIALIZATION);
    log_stream << "Loaded sound " << Set(Green) << sound->value.GetString() << Set();
    log_stream << " as " << Set(Cyan) << sound->name.GetString() << Set() << "\n";
    loadSound(sound->name.GetString(), sound->value.GetString());
  }
}

void SoundInterface::Update()
{
  system_->update();
}

SoundInterface::~SoundInterface()
{
  system_->release();
  system_ = nullptr;
}

void SoundInterface::playSound(std::string const& name, bool loop)
{
  //TODO: play sounds on different channels
  TraceLogger::Log(TraceLogger::DEBUG) << "Playing sound " << Set(Cyan) << name << Set() << "\n";
  if (loop) [[unlikely]]
  {
    unsigned int length;
    sounds_.at(name)->getLength(&length, FMOD_TIMEUNIT_MS);
    sounds_.at(name)->setLoopPoints(0, FMOD_TIMEUNIT_MS, length, FMOD_TIMEUNIT_MS);
    sounds_.at(name)->setLoopCount(loop ? -1 : 1);
  }
  system_->playSound(sounds_.at(name), default_channel_, false, nullptr);
}

void SoundInterface::playSound(char const* name, bool loop)
{
  playSound(std::string(name), loop);
}

void SoundInterface::loadSound(char const* name, char const* filepath)
{
  loadSound(std::string(name), std::string(filepath));
}

void SoundInterface::loadSound(std::string const& name, std::string const& filepath)
{
  FMOD::Sound* sound;
  if (name.find("music") != std::string::npos)
  {
    system_->createSound(filepath.c_str(), FMOD_LOOP_NORMAL, nullptr, &sound);
  }
  else
  {
    system_->createSound(filepath.c_str(), FMOD_DEFAULT, nullptr, &sound);
  }
  
  sounds_.emplace(std::make_pair(name, sound));
}

void SoundInterface::stopAllSounds()
{
  default_channel_->stop();
}
