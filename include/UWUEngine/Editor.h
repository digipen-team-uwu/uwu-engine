/******************************************************************************/
/*!
\par        Project Umbra
\file       Editor.h
\author     Michael Rollosson Halbhuber
\date       2019/10/16
\brief      A class that allows for the editing of Game Objects and
            levels from within the engine.

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once

#include <UWUEngine/Entity/EntityFactory.h>
#include <unordered_map>
#include <UWUEngine/BaseSystem.h>

//! Editor Class
class Editor : public BaseSystem<Editor>
{
public:

    /******************************************************************************/
    /*!
      \brief
        Constructs the editor object and initializes the ImGui context
    */
    /******************************************************************************/
    Editor();

    /******************************************************************************/
    /*!
      \brief
        Destructs the editor object and destroys the ImGui context
    */
    /******************************************************************************/
    ~Editor();
    
    /******************************************************************************/
    /*!
      \brief
        Starts the editor and loads the current level data into it
    */
    /******************************************************************************/
    static void Start();
    
    /******************************************************************************/
    /*!
      \brief
        Updates editor variables and members, creates the ImGui window
    */
    /******************************************************************************/
    void Update() override;
    
    /******************************************************************************/
    /*!
      \brief
        Clears all data members and deactivates the editor
    */
    /******************************************************************************/
    static void Stop();
    
    /******************************************************************************/
    /*!
      \brief
        Checks whether or not the editor is currently active

      \return True if the editor is active, false if it isn't
    */
    /******************************************************************************/
    static bool IsActive();

    static void SetName(EntityID ID, std::string name);

    static bool HasName(EntityID ID);

   static std::string GetName(EntityID ID);
    
private:
    // Variables to store pre-edit data?
    // For now, variables to store actively edited data (might set Editor to be friend of component managers later, then repurpose these as pre-edit storage)
    
    // Transform Vectors

    //! Local Scales
    //static std::vector<glm::vec3> scales;

    //! Local Translations
    //static std::vector<glm::vec4> translations;

    //! Local Rotations
    //static std::vector<float> rotations;
    
    // Physics Vectors

    //! Local old translations
    //static std::vector<glm::vec4> oldTranslations;
    // (I don't know if I'm actually doing anything with these right now

    //! Local accelerations
    //static std::vector<glm::vec4> accelerations;

    //! Local velocities
    //static std::vector<glm::vec4> velocities;
    
    //! Local rotational velocities
    //static std::vector<float> rotationalVelocities;

    //! Local drags
    //static std::vector<glm::vec4> drags;

    //! Local inverse masses
    //static std::vector<float> inverseMasses;
    
    //! Sets whether or not the editor is active
    static bool active;

    //! Sets whether or not the editor is pausing the level
    static bool paused;

    static std::unordered_map<EntityID, std::string> name;
    
    //! Tracks all the existing IDs (so that the GameObjectManager doesn't have to be referenced constantly)
    //static std::vector<EntityID> IDs;
    
    //! Tracks whether or not the ImGui window is open
    static bool open;
    
    // Method of separating template IDs (Vector that holds IDs for templates?)
    // Note: Will need to refactor Serialization of level files
    
    // Private functions
    
    /******************************************************************************/
    /*!
      \brief
        Creates the Editor Window via ImGui functions
    */
    /******************************************************************************/
    static void CreateEditorWindow();
    
    // (Temporary, probably will get deprecated once better implementations of edits are done)
    /******************************************************************************/
    /*!
      \brief
        Updates the objects based on current local edited versions
    */
    /******************************************************************************/
    //static void UpdateEditsToObjects();
    
    /******************************************************************************/
    /*!
      \brief
        Updates the local object component storage based on current object locations
    */
    /******************************************************************************/
    //static void UpdateLocalObjectComponents();
    
    // EntityID AddNewObject(GameObjectManager::Type type);
};
