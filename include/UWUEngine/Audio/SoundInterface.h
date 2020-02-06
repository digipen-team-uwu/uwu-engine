/******************************************************************************/
  /*!
  \par        Project Umbra
  \file       SoundInterface.h
  \author     Zach Rammell
  \date       2019/09/16
  \brief      Declaration of a class to manage, play, and modify sounds.

  Copyright � 2019 DigiPen, All rights reserved.
  */
  /******************************************************************************/

#pragma once

#include <fmod_studio.hpp>	/* FMOD pointers */
#include <fmod.hpp>
#include <string>	/* std::string	 */
#include <map>		/* std::map		 */
#include <UWUEngine/BaseSystem.h>

/******************************************************************************/
  /*!
\class	SoundInterface
\brief	Object for loading, playing, and modifying sounds.

    Currently implements loading and playing sounds.

    TODO: implement multiple sound channels and special effects
  */
  /******************************************************************************/
class SoundInterface : public BaseSystem<SoundInterface>
{
public:
  /**************************************************************************/
    /*!
    Initializes the sound library and system.
    */
    /**************************************************************************/
  SoundInterface();

  /**************************************************************************/
    /*!
    Updates state of the sound library. Must be called every game loop.
    */
    /**************************************************************************/
  void Update() override;

  /**************************************************************************/
    /*!
    Shuts down the sound library and system.
    */
    /**************************************************************************/
  ~SoundInterface();

  /**************************************************************************/
    /*!
    Plays an already loaded sound.
  \param	id Sound's unique ID, previously returned from loading it.
    */
    /**************************************************************************/
  static void playSound(std::string const& name, bool loop = false);

  /**************************************************************************/
    /*!
    Plays an already loaded sound.
  \param	id Sound's unique ID, previously returned from loading it.
    */
    /**************************************************************************/
  static void playSound(char const* name, bool loop = false);

  static void loadSound(char const* name, char const* filepath);
  static void loadSound(std::string const& name, std::string const& filepath);

  static void stopAllSounds();
  static void loadBank(const std::string &filepath);
  static void loadEvent(const std::string& filepath);
private:
  //! FMOD's sound system
  static FMOD::Studio::System* system_;
  static FMOD::System* core_;
  //! Map containing pointers to the internal FMOD sounds
  static std::map<std::string, FMOD::Sound*> sounds_;
  static std::map<int, FMOD::Channel*> channels_;
  static std::map<std::string, FMOD::Studio::EventInstance*> events_;
  static std::map<std::string, FMOD::Studio::Bank*> banks_;
  static void FmodError(FMOD_RESULT result);
  static int channelID;
};
