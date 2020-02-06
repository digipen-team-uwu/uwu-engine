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
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <fstream>
#include <UWUEngine/Debugs/ColoredOutput.h>


using namespace ColoredOutput;

FMOD::Studio::System* SoundInterface::system_;
FMOD::System* SoundInterface::core_;
std::map<std::string, FMOD::Sound*> SoundInterface::sounds_;
std::map<int, FMOD::Channel*> SoundInterface::channels_;
std::map<std::string, FMOD::Studio::EventInstance*> SoundInterface::events_;
std::map<std::string, FMOD::Studio::Bank*> SoundInterface::banks_;
int SoundInterface::channelID;

void SoundInterface::FmodError(FMOD_RESULT result)
{
  if (result != FMOD_OK)
  {
    TraceLogger::Log(TraceLogger::FAILURE) << "FMOD error! (" << result << ")" << FMOD_ErrorString(result);
  }
}

SoundInterface::SoundInterface()
{
  // Create the main system object.
  FmodError(FMOD::Studio::System::create(&system_));

  // Initialize FMOD.
  FmodError(system_->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_PROFILE_ENABLE, NULL));

  FmodError(system_->getCoreSystem(&core_));

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
  for (auto it = channels_.begin(); it != channels_.end(); ++it)
  {
    bool isPlaying;
    FmodError(it->second->isPlaying(&isPlaying));
    if (!isPlaying)
    {
      channels_.erase(it);
    }
  }
  FmodError(system_->update());
}

SoundInterface::~SoundInterface()
{

}

void SoundInterface::playSound(std::string const& name, const glm::vec3& pos, float volume)
{
  //TODO: play sounds on different channels
  TraceLogger::Log(TraceLogger::DEBUG) << "Playing sound " << Set(Cyan) << name << Set() << "\n";
  FMOD::Channel* channel;
  auto sound = sounds_.at(name);
  FmodError(core_->playSound(sound, nullptr, true, &channel));
  FMOD_MODE mode;
  FmodError(sound->getMode(&mode));
  if (mode & FMOD_3D)
  {
    FMOD_VECTOR fpos{ pos.x, pos.y, pos.z };
    channel->set3DAttributes(&fpos, nullptr);
  }
  FmodError(channel->setVolume(volume));
  FmodError(channel->setPaused(false));
  channels_.emplace(std::make_pair(channelID++, channel));
}

void SoundInterface::playSound(char const* name, bool loop)
{
  playSound(std::string(name), loop);
}

void SoundInterface::loadSound(char const* name, char const* filepath)
{
  loadSound(std::string(name), std::string(filepath));
}

void SoundInterface::loadSound(std::string const& name, std::string const& filepath, bool looping, bool spacial)
{
  FMOD::Sound* sound;
  core_->createSound(filepath.c_str(), FMOD_DEFAULT | looping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF | spacial ? FMOD_3D : FMOD_2D, nullptr, &sound);
  sounds_.emplace(std::make_pair(name, sound));
}

void SoundInterface::stopAllSounds()
{

}

void SoundInterface::loadBank(const std::string& filepath)
{
  FMOD::Studio::Bank* bank;
  FmodError(system_->loadBankFile(filepath.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &bank));
  banks_.emplace(std::make_pair(filepath, bank));
}

void SoundInterface::loadEvent(const std::string& filepath)
{
  FMOD::Studio::EventDescription* eventDes;
  FMOD::Studio::EventInstance* event;
  FmodError(system_->getEvent(filepath.c_str(), &eventDes));
  FmodError(eventDes->createInstance(&event));
  events_.emplace(std::make_pair(filepath, event));
}