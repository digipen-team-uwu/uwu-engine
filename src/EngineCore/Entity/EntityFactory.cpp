/******************************************************************************/
/*!
\par        Project Umbra
\file       GameObjectfactory.cpp
\author     Michael Rollosson Halbhuber
\date       2019/09/19
\brief      Constructs game objects from serialized files

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Entity/EntityFactory.h>
#include <UWUEngine/Entity/EntityCacher.h>
#include <UWUEngine/Editor/Windows/EditorEntityViewer.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <document.h>
#include <filereadstream.h>
#include <UWUEngine/constants.h>
#include <UWUEngine/Serialization.h>
#include <magic_enum.hpp>
#include <UWUEngine/Helper.h>
#include <UWUEngine/Component/BehaviorComponentManager.h>
#include <UWUEngine/Debugs/TraceLogger.h>
#include <UWUEngine/Debugs/ColoredOutput.h>

template<>
int RegisterSystemHelper<EntityFactory>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<EntityFactory>(SystemInitOrder::LAST, SystemUpdateOrder::LAST);

using namespace ColoredOutput;


char EntityFactory::readBuffer[65536];


EntityID EntityFactory::CreateObject(std::string filepath, EntityManager::Type type)
{
	// Returns the ID of the object
	EntityID resultID = -1;
	FILE* file;
	if(filepath.length())
	{
		// Open the file
		file = fopen(filepath.c_str(), "rb");
	}
	else
		{
			// A destination buffer for filePath
			std::stringstream path;

			// construct the path
			path << "./data/entities/" << magic_enum::enum_name(type) << ".json";
            file = fopen(path.str().c_str(), "rb");
		}
	// Check to make sure the file opened properly
	//printf("Attempting to open file %s\n", filePath.str().c_str()); // Debug print
	assert(file);
	
	// Read the file into a RapidJSON filestream
	rapidjson::FileReadStream stream(file, readBuffer, sizeof(readBuffer));
	
	// The RapidJSON document object
	rapidjson::Document doc;
	
	// Parse the file stream using RapidJSON
	doc.ParseStream(stream);
	
	// Close the file to avoid memory errors from asserts
	fclose(file);
	
	// Make sure the document was properly formatted
	// (More important once this is generalized)
	//printf("Checking %s for type member", filePath); // Debug print
	//assert(doc.HasMember("type"));
	//printf("Checking that %s type member is string"); // Debug print
	//assert(doc["type"].IsString());
	
	
	if(type != EntityManager::Empty) //if type was given
		resultID = EntityManager::New(type);// Get the EntityID from the manager
	else
	{
	  //figure it out from file name
		for (auto i : EntityManagerTypeIterator())
		{
            if (filepath.find(magic_enum::enum_name(i).data()) != std::string::npos)
            {
		  	    type = i;
                resultID = EntityManager::New(type);// Get the EntityID from the manager
                break;
            }
		}
	}
	
	// Construct all relevant components
	if (doc.HasMember("name"))
		Editors::EntityViewer::SetName(resultID, doc["name"].GetString()); //entity has a name
    else
        Editors::EntityViewer::SetName(resultID, doc["type"].GetString()); //use type as name
	
	// Check for a texture component
	CheckTexture(doc, resultID, filepath.c_str());
	
	// Check for a transform component
	CheckTransform(doc, resultID, filepath.c_str());
	
	// Check for a physics component
	CheckPhysics(doc, resultID, filepath.c_str());
	
	// Check for an animation component
	CheckAnimation(doc, resultID, filepath.c_str());
	
	CheckCollider(doc, resultID, filepath.c_str());
	
	
	
	CheckShader(doc, resultID, filepath.c_str());
	
	CheckSpineSkeleton(doc, resultID, filepath.c_str());
	
	// TODO: activate behavior if listed in json (CheckBehavior)
	if (doc.HasMember("behavior"))
	{
		BehaviorComponentManager::Activate(resultID);
		BehaviorComponentManager::GetBaseBehavior(resultID)->Deserialize(doc, resultID, filepath.c_str());
	}
	
	// Give the object a mesh (for now only square)
	//MeshComponentManager::Activate(resultID);
	//MeshComponentManager::SetMesh(resultID, MeshComponentManager::getSquareMesh());
	
	return resultID;
}


/******************************************************************************/
/*!
  \brief
    Creates a game object of the given type, currently through serialization only

  \param type
    The type of object to deserialize

  \return
    The ID of the created game object
*/
/******************************************************************************/
EntityID EntityFactory::CreateObject(EntityManager::Type type)
{
#if 0
    // Returns the ID of the object
    EntityID resultID = -1;

    // A destination buffer for filePath
    std::stringstream filePath;
    // char filePath[50];

    // Set the filePath based on the type.
    filePath << "./data/entities/" << magic_enum::enum_name(type) << ".json";
    // sprintf_s(filePath, "./data/%s.json", magic_enum::enum_name(type).data());


    // Open the file
    FILE* file = fopen(filePath.str().c_str(), "rb");

    // Check to make sure the file opened properly
    //printf("Attempting to open file %s\n", filePath.str().c_str()); // Debug print
    assert(file);

    // Read the file into a RapidJSON filestream
    rapidjson::FileReadStream stream(file, readBuffer, sizeof(readBuffer));

    // The RapidJSON document object
    rapidjson::Document doc;

    // Parse the file stream using RapidJSON
    doc.ParseStream(stream);

    // Close the file to avoid memory errors from asserts
    fclose(file);

    // Make sure the document was properly formatted
    // (More important once this is generalized)
    //printf("Checking %s for type member", filePath); // Debug print
    //assert(doc.HasMember("type"));
    //printf("Checking that %s type member is string"); // Debug print
    //assert(doc["type"].IsString());

    // Get the EntityID from the manager
    resultID = EntityManager::New(type);

    // Construct all relevant components
    if (doc.HasMember("name"))
      Editors::EntityViewer::SetName(resultID, doc["name"].GetString());

    // Check for a texture component
    CheckTexture(doc, resultID, filePath.str().c_str());

    // Check for a transform component
    CheckTransform(doc, resultID, filePath.str().c_str());

    // Check for a physics component
    CheckPhysics(doc, resultID, filePath.str().c_str());

    // Check for an animation component
    CheckAnimation(doc, resultID, filePath.str().c_str());

    CheckCollider(doc, resultID, filePath.str().c_str());

    

    CheckShader(doc, resultID, filePath.str().c_str());

	CheckSpineSkeleton(doc, resultID, filePath.str().c_str());

	// TODO: activate behavior if listed in json (CheckBehavior)
    if (doc.HasMember("behavior"))
    {
      BehaviorComponentManager::Activate(resultID);
      BehaviorComponentManager::GetBaseBehavior(resultID)->Deserialize(doc, resultID, filePath.str().c_str());
    }

    // Give the object a mesh (for now only square)
    //MeshComponentManager::Activate(resultID);
    //MeshComponentManager::SetMesh(resultID, MeshComponentManager::getSquareMesh());

    return resultID;
#endif
    return CreateObject(std::string(""), type);
}

/******************************************************************************/
/*!
  \brief
    Creates an object from the json file with the given file path
    via serialization

  \param object
    The json object file containing the data for the game object

  \param filePath
    The file path of the source file of the json object
*/
/******************************************************************************/
EntityID EntityFactory::CreateObject(rapidjson::Value& object, const char * filePath)
{
    // Check that the object is actually an object
  TraceLogger::Assert(object.IsObject(), "object from %s%s%s is actually an object.", Set(Green).c_str(), filePath, Set().c_str());

    // Check that object has type
  TraceLogger::Assert(object.HasMember("type"), "object in %s has a type.", filePath);
  TraceLogger::Assert(object["type"].IsString(), "type is string.");

  TraceLogger::Log(TraceLogger::SERIALIZATION) << "Checking that object type is legal\n";

    //TODO::Something is wrong here after I add LevelEnd, that's why I changed this logic into magic enum cast but something needs to be fixed
    EntityManager::Type type = magic_enum::enum_cast<EntityManager::Type>(object["type"].GetString()).value();
    //for (auto i : EntityManagerTypeIterator())
    //{
    //  //printf("Checking Type Against: %s\n", magic_enum::enum_name(i).data());
    //    // Check to see if the strings are the same (evaluates to !0 if they are)
    //    if (!strcmp(object["type"].GetString(), magic_enum::enum_name(i).data()))
    //    {
    //        type = i;
    //        break;
    //    }
    //}
    
    // This assert should only trigger if the if check above never evaluated to true,
    // or if the object's type is set to Empty or TypeCount, which are illegal object types
    TraceLogger::Assert(type != EntityManager::Empty && type != EntityManager::TypeCount, "type is legal.");

    /*if (type == EntityManager::Background)
    {
        printf("Here\n");
    }*/

    EntityID resultID;
    bool partial;
    // Will edit as more types get templates until hopefully this can list the types that DON'T have templates (hopefully eventually just the debug ones)
    if (!EntityCacher::EntityIsCached(type))
    {
        // Type is currently untemplated, going to need to do a full construction
        resultID = EntityManager::New(type);
        partial = false;
    }
    else
    {
        // Construct the base object from a template
      resultID = EntityCacher::CreateCachedEntity(EntityCacher::GetCachedEntity(type));
      partial = true;
    }

    // Edit all relevant components

    if (!partial)
      CheckTexture(object, resultID, filePath);

    // Check transform
    CheckTransform(object, resultID, filePath, !partial);
    //std::cout << "ID: " << resultID << ", Position: < " << TransformComponentManager::GetTranslation(resultID).x <<
      //"," << TransformComponentManager::GetTranslation(resultID).y << " >" << std::endl;
    //std::cout << "Scale: <" << TransformComponentManager::GetScale(resultID).x << " , " <<
      //TransformComponentManager::GetScale(resultID).y << " >" << std::endl;
    // Check physics
    CheckPhysics(object, resultID, filePath, !partial);

    CheckCollider(object, resultID, filePath);

    if (object.HasMember("name"))
      Editors::EntityViewer::SetName(resultID, object["name"].GetString());

    if (object.HasMember("behavior"))
    {
      BehaviorComponentManager::Activate(resultID);
      if (object["behavior"].IsString())
      {
        EntityCacher::InstantiateCachedBehavior(resultID, object["behavior"].GetString());
      }
      else
      {
        BehaviorComponentManager::GetBaseBehavior(resultID)->Deserialize(object, resultID, filePath);
      }
    }

    // Check animation
    if (!partial)
    {
        CheckAnimation(object, resultID, filePath);

        // Check texture
        CheckTexture(object, resultID, filePath);

        CheckShader(object, resultID, filePath);
    }

    // Give the object a mesh (for now only square)
   // if (!MeshComponentManager::IsActive(resultID))
    //{
      //  MeshComponentManager::Activate(resultID);
        //MeshComponentManager::SetMesh(resultID, MeshComponentManager::getSquareMesh());
    //}

    return resultID;
}