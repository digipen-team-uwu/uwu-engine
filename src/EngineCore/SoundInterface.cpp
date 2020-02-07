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


using namespace ColoredOutput;

FMOD::System* SoundInterface::system_;
std::map<std::string, FMOD::Sound*> SoundInterface::sounds_;
std::map<std::string, FMOD::ChannelGroup*> SoundInterface::channels_;

void SoundInterface::playSound(char const* name, bool loop)
{
  playSound(std::string(name), loop);
}


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
  auto& chan = channels_.find(name);
  if (chan != channels_.end() && chan->second)
  {
    stopSound(name);
  }
  TraceLogger::Log(TraceLogger::DEBUG) << "Playing sound " << Set(Cyan) << name << Set() << "\n";
  if (loop) [[unlikely]]
  {
    unsigned int length;
    sounds_.at(name)->getLength(&length, FMOD_TIMEUNIT_MS);
    sounds_.at(name)->setLoopPoints(0, FMOD_TIMEUNIT_MS, length, FMOD_TIMEUNIT_MS);
    sounds_.at(name)->setLoopCount(loop ? -1 : 1);
  }
  system_->playSound(sounds_.at(name), channels_[name], false, nullptr);
}

void SoundInterface::loadSound(char const* name, char const* filepath)
{
  loadSound(std::string(name), std::string(filepath));
  FMOD::ChannelGroup* group;
  system_->createChannelGroup("default", &group);
  channels_[name] = group;
}

void SoundInterface::stopSound(const std::string &str)
{
  channels_[str]->stop();
}

void SoundInterface::stopSound(char const* name)
{
  channels_[name]->stop();
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
  for (auto& it : channels_)
  {
    it.second->stop();
  }
}
