/******************************************************************************/
/*!
\par        Project Umbra
\file       Editor.cpp
\author     Michael Rollosson Halbhuber
\date       2019/10/16
\brief      A class that allows for the editing of Game Objects and
            levels from within the engine.

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/Editor.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glm\vec4.hpp>
#include <glm\vec3.hpp>
#include <UWUEngine/constants.h>
#include <UWUEngine/WindowManager.h>
#include <magic_enum.hpp>
#include <UWUEngine/FrameRateController.h>
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <UWUEngine/Component/AnimationComponentManager.h>
#include <UWUEngine/Component/TextureComponentManager.h>
#include <sstream>
#include <UWUEngine/Serialization.h>
#include "glm/glm.hpp"

template<>
int RegisterSystemHelper<Editor>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<Editor>(SystemInitOrder::Editor, SystemUpdateOrder::Editor);

//! Sets whether or not the editor is active
bool Editor::active;

//! Sets whether or not the editor is pausing the level
bool Editor::paused;

//! Tracks whether or not the ImGui window is open
bool Editor::open;

std::unordered_map<EntityID, std::string> Editor::name;

// DEPRECATED BLOCK BEGINS (MichaelDeprecatedCode.cpp contains copies of all deprecated code for easy counting)

////! Local Scales
//std::vector<glm::vec3> Editor::scales;
//
////! Local Translations
//std::vector<glm::vec4> Editor::translations;
//
////! Local Rotations
//std::vector<float> Editor::rotations;
//
//// Physics Vectors
//
////! Local old translations
//std::vector<glm::vec4> Editor::oldTranslations;
//// (I don't know if I'm actually doing anything with these right now
//
////! Local accelerations
//std::vector<glm::vec4> Editor::accelerations;
//
////! Local velocities
//std::vector<glm::vec4> Editor::velocities;
//
////! Local rotational velocities
//std::vector<float> Editor::rotationalVelocities;
//
////! Local drags
//std::vector<glm::vec4> Editor::drags;
//
////! Local inverse masses
//std::vector<float> Editor::inverseMasses;
//
//
//
////! Tracks all the existing IDs (so that the GameObjectManager doesn't have to be referenced constantly)
//std::vector<EntityID> Editor::IDs;
// DEPRECATED BLOCK ENDS


// PUBLIC FUNCTIONS

// Creates the editor and sets context required for the Imgui Window
Editor::Editor()
{
    // Upon construction, the editor is not active,
    // it is not open, and it is not pausing the level
    active = false;
    open = false;
    paused = false;
    
    
    // Establishes ImGui context for the editor window
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(WindowManager::getWindowHandle(), true);
    ImGui_ImplOpenGL3_Init("#version 450");
}

void Editor::SetName(EntityID ID, std::string name_)
{
  name[ID] = name_;
}

std::string Editor::GetName(EntityID ID)
{
  return name[ID];
}

bool Editor::HasName(EntityID ID)
{
  auto name_ = name.find(ID);
  return name_ != name.end();
}


Editor::~Editor()
{
    // Destroys ImGui Window Context
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

// Loads the current level data into the editor
void Editor::Start()
{
    // DEPRECATED BLOCK BEGINS (MichaelDeprecatedCode.cpp contains copies of all deprecated code for easy counting)
    // Obtain all the currently in-use IDs from the object manager
    // IDs = EntityManager::GetIDs();

    // Initialize Vector sizes 
    // (See Editor.h for what each of these are, though the names are self-explanatory)


    // scales.resize(GameObjectConstants::INITIAL_OBJECT_COUNT);
    // translations.resize(GameObjectConstants::INITIAL_OBJECT_COUNT);
    // rotations.resize(GameObjectConstants::INITIAL_OBJECT_COUNT);
    // oldTranslations.resize(GameObjectConstants::INITIAL_OBJECT_COUNT);
    // accelerations.resize(GameObjectConstants::INITIAL_OBJECT_COUNT);
    // velocities.resize(GameObjectConstants::INITIAL_OBJECT_COUNT);
    // rotationalVelocities.resize(GameObjectConstants::INITIAL_OBJECT_COUNT);
    // drags.resize(GameObjectConstants::INITIAL_OBJECT_COUNT);
    // inverseMasses.resize(GameObjectConstants::INITIAL_OBJECT_COUNT);

    // Update Local Object Components based on the EntityManager's current state
    // UpdateLocalObjectComponents();
    // DEPRECATED BLOCK ENDS

    // The editor is now open, active, but still not pausing the level
    open = true;
    active = true;
    paused = false;
    FrameRateController::SetPaused(paused);
    
}

// Updates the editor state
void Editor::Update()
{
    // Only do the stuff if the editor is actually active
    if (active)
    {
        // Update Local Object Components based on the EntityManager's current state
        // UpdateLocalObjectComponents();

        // Start the dear imgui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // If it's open, display it
        if (open)
        {
            // Set the window initial size (yes this must be done every loop)
            ImGui::SetNextWindowPos(ImVec2(550, 20), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

            // Create the editor window
            CreateEditorWindow();

            // Show the demo window as well (Useful to reference during construction of editor window)
            //ImGui::ShowDemoWindow(&open);
        }


        // Temporary hack-y implementation of the editing and pausing. This WILL be changed later
        //if (paused)
        //{
            // Update the edits made in the editor and stored locally to the other component managers
            // If the editor is ever made a friend to all components, this may become unnecessary
            // UpdateEditsToObjects();
        //}
        //else
        //{
            //UpdateLocalObjectComponents();
        //}
    }
}

// Exits out of the editor, clearing all the current data
void Editor::Stop()
{
    // DEPRECTATED BLOCK BEGINS (MichaelDeprecatedCode.cpp contains copies of all deprecated code for easy counting)
    // Clear the vectors
    // IDs.clear();
    // scales.clear();
    // translations.clear();
    // oldTranslations.clear();
    // accelerations.clear();
    // velocities.clear();
    // rotationalVelocities.clear();
    // drags.clear();
    // inverseMasses.clear();
    // DEPRECATED BLOCK ENDS

    // Reset all bools to false
    open = false;
    active = false;
    paused = false;
}

// Returns whether or not the editor is active
bool Editor::IsActive()
{
  return active;
}

// PRIVATE FUNCTIONS
void Editor::CreateEditorWindow()
{ 
    // Need this for some stuff I think
    bool menuItem = true;
    // Begin the window 
    // If this doesn't work for any reason, crash the program
    if (ImGui::Begin("Editor", &open, 0))
    {

        // Set width settings (negative value sets a fixed width)
        ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

        // The menu bar
        // TODO: CreateMenuBar function
        // Placeholder for now

        // Creates the menu bar
        if (ImGui::BeginMenuBar())
        {
            // If it was created, begins the menu
            if (ImGui::BeginMenu("Menu"))
            {
                // If the menu was created, create an item
                ImGui::MenuItem("More to come!", NULL, &menuItem, true);

                // End the menu
                ImGui::EndMenu();
            }
            // End the menu bar
            ImGui::EndMenuBar();
        }

        // Pause button!
        ImGui::Checkbox("Pause", &paused);
        // Set the pause function
        FrameRateController::SetPaused(paused);

        
        static char levelName[20] = "BrayanSBOX";

        ImGui::InputText("Level Name", levelName, 20);

        if (ImGui::Button("Save Level"))
        {
            SerializeLevel(levelName);
        }

        // Bounds setters
        static float rightBounds = 20000.0f;
        static float leftBounds = -20000.0f;
        static float topBounds = 20000.0f;
        static float bottomBounds = -20000.0f;

        ImGui::InputFloat("Right Bounds", &rightBounds);
        ImGui::InputFloat("Left Bounds", &leftBounds);
        ImGui::InputFloat("Top Bounds", &topBounds);
        ImGui::InputFloat("Bottom Bounds", &bottomBounds);

        // Create the objects collapsing header
        if (ImGui::CollapsingHeader("Existing Objects"))
        {
            // Loop through all game object ids
            for (EntityID id : EntityManager::ids)
            {
                if (EntityManager::types[id] != EntityManager::Type::Particle)
                {

                    // Create either tree node or collapsing header for every game object
                    // Trying Collapsable Headers first

                    // Create the header name for the header in format "ID - Type"
                    std::stringstream headerName;
                    std::string item_name;
                    if (HasName(id))
                    {
                      item_name = GetName(id);
                    }
                    else
                    {
                      item_name = magic_enum::enum_name(EntityManager::GetType(id));
                      SetName(id, item_name);
                    }
                    headerName << std::to_string(id) << " - " << item_name;

                    // Begin the collapsable header
                    if (ImGui::TreeNode(headerName.str().c_str()))
                    {
                        std::stringstream buttonName;
                        buttonName << std::to_string(id) << " - Change Name";

                        // Button to change the object's name
                        if (ImGui::Button(buttonName.str().c_str()))
                        {
                            ImGui::OpenPopup(buttonName.str().c_str());
                        }

                        if (ImGui::BeginPopupModal(buttonName.str().c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
                        {
                            static char objectName[50] = "Player";

                            ImGui::Text("Type your desired name for the object below");

                            ImGui::InputText("Name", objectName, 50);

                            if (ImGui::Button("Save Name"))
                            {
                                SetName(id, objectName);
                                ImGui::CloseCurrentPopup();
                            }

                            if (ImGui::Button("Cancel"))
                            {
                                ImGui::CloseCurrentPopup();
                            }

                            ImGui::EndPopup();
                        }

                        // Set up the transform node display
                        if (TransformComponentManager::IsActive(id))
                        {
                            // Create a Transform tree node for the object
                            if (ImGui::TreeNode("Transform"))
                            {
                                if (ImGui::Button("Detach Transform"))
                                {
                                    TransformComponentManager::Deactivate(id);
                                }
                                else
                                {

                                    // Decides whether the slider or input is displayed
                                    static int sliderOrInput = 0;

                                    // Radio buttons (only one can be selected at a time)
                                    // Determine whether the slider or input display is to be used
                                    ImGui::RadioButton("Slider", &sliderOrInput, 0); // Display the Sliders
                                    ImGui::SameLine(); // Keep the buttons on the same line
                                    ImGui::RadioButton("Input", &sliderOrInput, 1); // Display the Inputs

                                    // Display the components for editing
                                    if (ImGui::TreeNode("Position"))
                                    {
                                        std::vector<glm::vec4>& translations = TransformComponentManager::translation_;

                                        // Creates either a slider (fast and general) or an input (slow or specific) for each axis

                                        if (sliderOrInput == 0)
                                        {
                                            // Create a slider for the X, Y, and Z positions of the object
                                            ImGui::SliderFloat("X Position", &translations[id].x, leftBounds, rightBounds);
                                            ImGui::SliderFloat("Y Position", &translations[id].y, bottomBounds, topBounds);
                                            ImGui::SliderFloat("Z Position", &translations[id].z, -4000.0f, 4000.0f);
                                        }
                                        else
                                        {
                                            // Create an Input for the X, Y, and Z positions of the object
                                            ImGui::InputFloat("X Position", &translations[id].x, 0.01f, 0.01f);
                                            ImGui::InputFloat("Y Position", &translations[id].y, 0.01f, 0.01f);
                                            ImGui::InputFloat("Z Position", &translations[id].z, 0.01f, 0.01f);
                                        }

                                        // Pop the Position tree node (Go back up a level in the tree)
                                        ImGui::TreePop();
                                    }

                                    if (ImGui::TreeNode("Scale"))
                                    {
                                        std::vector<glm::vec3>& scales = TransformComponentManager::scale_;

                                        // Creates a slider or an input option for both Width and Height

                                        if (sliderOrInput == 0)
                                        {
                                            // Create Width and Height Sliders
                                            ImGui::SliderFloat("Width", &scales[id].x, 0.01f, 4096.0f);
                                            ImGui::SliderFloat("Height", &scales[id].y, 0.01f, 4096.0f);
                                        }
                                        else
                                        {
                                            // Create Width and Height inputs
                                            ImGui::InputFloat("Width", &scales[id].x, 0.01f, 0.01f);
                                            ImGui::InputFloat("Height", &scales[id].y, 0.01f, 0.01f);
                                        }

                                        // Pop the Scale tree node
                                        ImGui::TreePop();
                                    }

                                    if (ImGui::TreeNode("Rotation"))
                                    {
                                        std::vector<float>& rotations = TransformComponentManager::rotation_;

                                        // Creates either a slider or an input for rotation
                                        if (sliderOrInput == 0)
                                        {
                                            // Create a rotation slider
                                            ImGui::SliderFloat("Rotation", &rotations[id], 0.0f, glm::radians(360.0f));
                                        }
                                        else
                                        {
                                            // Create a rotation input
                                            ImGui::InputFloat("Rotation", &rotations[id], 0.01f, 0.01f);
                                        }

                                        // Pop the Rotation tree node
                                        ImGui::TreePop();
                                    }
                                }
                                // Pop the Transform tree node
                                ImGui::TreePop();
                            }
                        }
                        else
                        {
                            if (ImGui::Button("Attach Transform"))
                            {
                                TransformComponentManager::Activate(id);
                            }
                        }

                        // Set up the physics editor
                        if (PhysicsComponentManager::IsActive(id))
                        {
                            // Create a Physics tree node for the object
                            if (ImGui::TreeNode("Physics"))
                            {
                                if (ImGui::Button("Detach Physics"))
                                {
                                    PhysicsComponentManager::Deactivate(id);
                                }
                                else
                                {
                                    // Create a Velocity and Acceleration tree node for the object
                                    if (ImGui::TreeNode("Velocity and Acceleration"))
                                    {
                                        std::vector<glm::vec4>& velocities = PhysicsComponentManager::velocity_;
                                        std::vector<glm::vec4>& accelerations = PhysicsComponentManager::acceleration_;
                                        std::vector<float>& rotationalVelocities = PhysicsComponentManager::rotationalVelocity_;

                                        // Create an input for velocity and acceleration on each axis

                                        // X Velocity and Acceleration Inputs
                                        ImGui::InputFloat("X Velocity", &velocities[id].x, 0.01f, 0.01f);
                                        ImGui::Spacing();  // Formatting
                                        ImGui::SameLine(); // (Broken) Formatting
                                        ImGui::InputFloat("X Acceleration", &accelerations[id].x, 0.01f, 0.01f);

                                        // Y Velocity and Acceleration Inputs
                                        ImGui::InputFloat("Y Velocity", &velocities[id].y, 0.01f, 0.01f);
                                        ImGui::Spacing();  // Formatting
                                        ImGui::SameLine(); // (Broken) Formatting
                                        ImGui::InputFloat("Y Acceleration", &accelerations[id].y, 0.01f, 0.01f);

                                        // Z Velocity and Acceleration Inputs
                                        ImGui::InputFloat("Z Velocity", &velocities[id].z, 0.01f, 0.01f);
                                        ImGui::Spacing();  // Formatting
                                        ImGui::SameLine(); // (Broken) Formatting
                                        ImGui::InputFloat("Z Acceleration", &accelerations[id].y, 0.01f, 0.01f);

                                        // Create an input for Rotational Velocity
                                        ImGui::InputFloat("Rotational Velocity", &rotationalVelocities[id], 0.01f, 0.01f);

                                        // Pop the Velocity and Acceleration Node
                                        ImGui::TreePop();
                                    }

                                    // Create an Inverse Mass and Drag tree node
                                    if (ImGui::TreeNode("Inverse Mass and Drag"))
                                    {
                                        std::vector<float>& inverseMasses = PhysicsComponentManager::inverseMass_;
                                        std::vector<glm::vec4>& drags = PhysicsComponentManager::drag_;

                                        // Create an input for the inverse mass
                                        ImGui::InputFloat("Inverse Mass", &inverseMasses[id], 0.01f, 0.01f);

                                        // Create X Drag, Y Drag, and Z Drag inputs
                                        ImGui::InputFloat("X Drag", &drags[id].x, 0.01f, 0.01f);
                                        ImGui::InputFloat("Y Drag", &drags[id].y, 0.01f, 0.01f);
                                        ImGui::InputFloat("Z Drag", &drags[id].z, 0.01f, 0.01f);

                                        // Pop the Inverse Mass and Drag tree node
                                        ImGui::TreePop();
                                    }
                                }
                                // Pop the Physics tree node
                                ImGui::TreePop();
                            }
                        }
                        else
                        {
                            if (ImGui::Button("Attach Physics"))
                            {
                                PhysicsComponentManager::Activate(id);
                            }
                        }

                        // Set up the animation manager
                        if (AnimationComponentManager::IsActive(id))
                        {
                            // Bool that determines whether or not the popup window will appear
                            static bool stopAsking = false;

                            // Create an Animation tree node
                            if (ImGui::TreeNode("Animation"))
                            {
                                if (ImGui::Button("Detach Animation"))
                                {
                                    AnimationComponentManager::Deactivate(id);
                                }
                                else
                                {

                                    // Get a reference to the current set of animations
                                    AnimationComponentManager::Animations& currAnimations = AnimationComponentManager::animations.at(id);

                                    // Get a reference to the Animation IDs for the object
                                    std::vector<int>& animationIDs = currAnimations.ids;

                                    // Sorry that everything is a tree node right now, They're simple.
                                    // I'll try and make this work with combos or something once all the functionality is in
                                    for (int animationID : animationIDs)
                                    {
                                        // Used to create the name of the node for this animation data
                                        std::stringstream animationHeader;

                                        // Create a string of the format "Animation (AccessID)"
                                        animationHeader << "Animation " << animationID;

                                        // Create a TreeNode for the animation data
                                        if (ImGui::TreeNode(animationHeader.str().c_str()))
                                        {

                                            // Get a reference to the AnimationData at the current id
                                            AnimationComponentManager::AnimationData& currData = currAnimations.data.at(animationID);

                                            // For now, just get these displaying

                                            // Create a checkbox for whether or not the animation loops
                                            ImGui::Checkbox("Looping", &currData.looping_);

                                            // Display the frame count for the animation
                                            ImGui::Text("Frame Count: %i", currData.frameCount_);

                                            // Display the current frame of the animation
                                            ImGui::Text("Current Frame: %i", currData.currentFrame_);

                                            // Display the time remaining in the frame for the animation
                                            ImGui::Text("Frame Delay Remaining: %f", currData.frameDelay_);

                                            // Create a Play button for the animation
                                            if (ImGui::Button("Play"))
                                            {
                                                // Play the animation
                                                AnimationComponentManager::Play(id, animationID);
                                            }

                                            // Display the frames in the animation
                                            if (ImGui::TreeNode("Frames"))
                                            {
                                                // Determines whether a single frame's data or all frame data is displayed
                                                static int singleOrList = 0;

                                                // Create a set of Radio Buttons that display either a single frame or a list of frames
                                                ImGui::RadioButton("Single Frames", &singleOrList, 0); // Display a single frame
                                                ImGui::SameLine(); // Keep the buttons on the same line
                                                ImGui::RadioButton("List of Frames", &singleOrList, 1); // Display a list of frames

                                                // Display only one frame of data
                                                if (singleOrList == 0)
                                                {

                                                    // The current frame being displayed
                                                    static int frame = 0;

                                                    // Allow the frame to be changed
                                                    ImGui::InputInt("Frame", &frame, 1, 1, 0);

                                                    // Check to make sure the frame hasn't gone past the number of frames
                                                    // (For some reason InputInt doesn't appear to have clamping
                                                    // so I'm clamping it myself)
                                                    if (frame >= currData.frameCount_)
                                                    {
                                                        // Clamp to the upper bound
                                                        frame = currData.frameCount_ - 1;
                                                    }
                                                    else if (frame < 0)
                                                    {
                                                        // Clamp to 0
                                                        frame = 0;
                                                    }

                                                    // Allow for editing of the index
                                                    ImGui::InputInt("Frame Index", &currData.frames_[frame].index, 1, 1, 0);

                                                    // Get the dimensions of the texture
                                                    glm::uvec2 textureDim = TextureComponentManager::GetDimensions(id);

                                                    // Calculate the max index for the frame
                                                    int maxIndex = textureDim.x * textureDim.y;

                                                    // Clamp the index
                                                    if (currData.frames_[frame].index >= maxIndex)
                                                    {
                                                        // Clamp to the last frame in the texture
                                                        currData.frames_[frame].index = maxIndex - 1;
                                                    }
                                                    else if (currData.frames_[frame].index < 0)
                                                    {
                                                        // Clamp to the first frame in the texture
                                                        currData.frames_[frame].index = 0;
                                                    }

                                                    // Allow for editing of the frame duration
                                                    ImGui::InputFloat("Frame Duration", &currData.frames_[frame].frameDuration, 0.001f, 1.0f);

                                                    // Clamp the frame duration
                                                    if (currData.frames_[frame].frameDuration < 0.0f)
                                                    {
                                                        // Just make sure it doesn't drop below 0, though a zero frame is mostly pointless too
                                                        // it does at least allow for testing of frame removal without deleting the frame
                                                        currData.frames_[frame].frameDuration = 0.0f;
                                                    }
                                                }
                                                // Display all frame data
                                                else
                                                {
                                                    for (int i = 0; i < currData.frames_.size(); i++)
                                                    {
                                                        // Like other headers, used to create the TreeNode
                                                        std::stringstream frameHeader;

                                                        // Create the string in the format "Frame #"
                                                        frameHeader << "Frame " << i;

                                                        // Create a node for every frame in the AnimationData
                                                        if (ImGui::TreeNode(frameHeader.str().c_str()))
                                                        {
                                                            // Allow for editing of the index
                                                            ImGui::InputInt("Frame Index", &currData.frames_[i].index, 1, 1, 0);

                                                            // Get the dimensions of the texture
                                                            glm::uvec2 textureDim = TextureComponentManager::GetDimensions(id);

                                                            // Calculate the max index for the frame
                                                            int maxIndex = textureDim.x * textureDim.y;

                                                            // Clamp the index
                                                            if (currData.frames_[i].index >= maxIndex)
                                                            {
                                                                // Clamp to the last frame in the texture
                                                                currData.frames_[i].index = maxIndex - 1;
                                                            }
                                                            else if (currData.frames_[i].index < 0)
                                                            {
                                                                // Clamp to the first frame in the texture
                                                                currData.frames_[i].index = 0;
                                                            }

                                                            // Allow for editing of the frame duration
                                                            ImGui::InputFloat("Frame Duration", &currData.frames_[i].frameDuration, 0.001f, 1.0f);

                                                            // Clamp the frame duration
                                                            if (currData.frames_[i].frameDuration < 0.0f)
                                                            {
                                                                // Just make sure it doesn't drop below 0, though a zero frame is mostly pointless too
                                                                // it does at least allow for testing of frame removal without deleting the frame
                                                                currData.frames_[i].frameDuration = 0.0f;
                                                            }

                                                            // Pop the "Frame #" node
                                                            ImGui::TreePop();
                                                        }
                                                    }
                                                }

                                                // Allow frames to be added
                                                if (ImGui::Button("Add Frame"))
                                                {
                                                    // Add a frame
                                                    AnimationComponentManager::AddFrame(0, 0.1f, id, animationID);
                                                }

                                                // Pop the "Frames" node
                                                ImGui::TreePop();
                                            }

                                            // Create a button to delete an animation
                                            if (ImGui::Button("Delete Animation"))
                                            {
                                                // If the button is clicked, create a popup making sure they want to delete the animation struct
                                                if (!stopAsking)
                                                {
                                                    // Open up the popup
                                                    ImGui::OpenPopup("Delete Animation?");
                                                }
                                                else
                                                {
                                                    // Just delete the thing
                                                    // Engine::animationManager.DeleteAnimation(id, animationID);
                                                }
                                            }

                                            // The actual error popup (Has to be outside of the button code to display)
                                            if (ImGui::BeginPopupModal("Delete Animation?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
                                            {
                                                // Display informative text
                                                ImGui::Text("Are you sure you want to delete this animation data?");
                                                ImGui::Text("(This doesn't do anything yet, sorry)");
                                                // Put some space in
                                                ImGui::Separator();

                                                // Checkbox for if they want the popup to stop appearing
                                                ImGui::Checkbox("Don't ask again this session", &stopAsking);

                                                // Button that deletes the animation
                                                if (ImGui::Button("Do it"))
                                                {
                                                    // Delete the thing
                                                    // Engine::animationManager.DeleteAnimation(id, animationID);

                                                    // Close the popup
                                                    ImGui::CloseCurrentPopup();
                                                }

                                                // Keep the buttons on the same line
                                                ImGui::SameLine();

                                                // Exits the popup  without deleting the animation
                                                if (ImGui::Button("Nevermind"))
                                                {
                                                    // Don't delete the thing

                                                    // Close the popup
                                                    ImGui::CloseCurrentPopup();
                                                }

                                                // Ends the popup ImGui section
                                                ImGui::EndPopup();
                                            }

                                            // Pop the "Animation #" node
                                            ImGui::TreePop();
                                        }
                                    }

                                    // The accessID to be used when creating an animation
                                    static int accessID = 0;

                                    // Informative text
                                    ImGui::Text("Add an animation:");

                                    // Input to edit the accessID
                                    ImGui::InputInt("Access ID", &accessID, 1, 1, 0);

                                    // Keep the Add button on the same line
                                    ImGui::SameLine();

                                    // Add an animation with the given access ID
                                    if (ImGui::Button("Add"))
                                    {
                                        // Check if the accessID is already in use
                                        if (currAnimations.data[accessID].frames_.size())
                                        {
                                            // Begin an error popup
                                            ImGui::OpenPopup("Access ID Error");
                                        }
                                        else
                                        {
                                            // Add a new animation
                                            AnimationComponentManager::AddNewAnimation(id, accessID);

                                            // Immediately give it a frame to avoid crashing
                                            AnimationComponentManager::AddFrame(0, 0.1, id, accessID);
                                        }
                                    }

                                    // The actual error popup (Has to be outside of the button to display)
                                    if (ImGui::BeginPopupModal("Access ID Error", NULL, ImGuiWindowFlags_AlwaysAutoResize))
                                    {
                                        // Informative text
                                        ImGui::Text("Error! Access ID %i already in use with this object.", accessID);
                                        ImGui::Text("Access IDs are unique per object. Please use a different one.");

                                        // Formatting
                                        ImGui::Separator();

                                        // Closes the popup
                                        if (ImGui::Button("Okay"))
                                        {
                                            ImGui::CloseCurrentPopup();
                                        }

                                        // Ends the popup ImGui code
                                        ImGui::EndPopup();
                                    }
                                }
                                // Pop the Animation node
                                ImGui::TreePop();
                            }
                        }
                        else
                        {
                            if (ImGui::Button("Attach Animation"))
                            {
                                AnimationComponentManager::Activate(id);

                                // Add a new animation
                                AnimationComponentManager::AddNewAnimation(id, 0);

                                // Immediately give it a frame to avoid crashing
                                AnimationComponentManager::AddFrame(0, 0.1, id, 0);
                            }
                        }

                        // Pop the object node
                        ImGui::TreePop();
                    }
                }
            }
        }
    }

    // Ends the editor window
    ImGui::End();
}

// DEPRECATED BLOCK BEGINS (MichaelDeprecatedCode.cpp contains copies of all deprecated code for easy counting)

// Updates the objects based on current local edited versions
// (Temporary, probably will get deprecated once better implementations of edits are done)
//void Editor::UpdateEditsToObjects()
//{
//    for (EntityID id : IDs)
//    {
//        // Set the transform components
//        if (TransformComponentManager::IsActive(id))
//        {
//            TransformComponentManager::SetTranslation(translations[id], id);
//            TransformComponentManager::SetScale(scales[id], id);
//            TransformComponentManager::SetRotation(rotations[id], id);
//        }
//
//        // Set the physics components
//        if (PhysicsComponentManager::IsActive(id))
//        {
//            PhysicsComponentManager::SetVelocity(velocities[id], id);
//            PhysicsComponentManager::SetAcceleration(accelerations[id], id);
//            PhysicsComponentManager::SetRotationalVelocity(rotationalVelocities[id], id);
//            PhysicsComponentManager::SetDrag(drags[id], id);
//            PhysicsComponentManager::SetInverseMass(inverseMasses[id], id);
//        }
//    }
//}
//
//// Updates the local object component storage based on current object locations
//void Editor::UpdateLocalObjectComponents()
//{
//    for (EntityID id : IDs)
//    {
//        // Update to the current transform state
//        if (TransformComponentManager::IsActive(id))
//        {
//            scales[id] = TransformComponentManager::GetScale(id);
//            translations[id] = TransformComponentManager::GetTranslation(id);
//            rotations[id] = TransformComponentManager::GetRotation(id);
//        }
//        //  Update to the current physics state
//        if (PhysicsComponentManager::IsActive(id))
//        {
//            velocities[id] = PhysicsComponentManager::GetVelocity(id);
//            accelerations[id] = PhysicsComponentManager::GetAcceleration(id);
//            rotationalVelocities[id] = PhysicsComponentManager::GetRotationalVelocity(id);
//            drags[id] = PhysicsComponentManager::GetDrag(id);
//            inverseMasses[id] = PhysicsComponentManager::GetInverseMass(id);
//        }
//    }
//}

// DEPRECATED BLOCK ENDS