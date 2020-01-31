#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Entity/EntityFactory.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include "UWUEngine/Deserialization.h"
#include <vector>
#include <UWUEngine/Component/TextureComponentManager.h>
#include <UWUEngine/Helper.h>
#include <magic_enum.hpp>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <UWUEngine/Component/AnimationComponentManager.h>
#include <UWUEngine/Graphics/SpineAnimation/SpineDataManager.h>
#include <UWUEngine/Component/SpineAnimationComponentManager.h>
#include <UWUEngine/Component/SpineSkeletonComponentManager.h>
#include <UWUEngine/Graphics/Texture/TextureAtlaser.h>
#include <UWUEngine/Debugs/TraceLogger.h>
#include <sstream>
#include <filesystem>
#include <locale>
#include <UWUEngine/Component/ColliderComponentManager.h>
#ifdef _MSVC
#include <Shlobj_core.h>
#endif

// Allows the RapidJSON Parser to function when members at the end of objects and arrays have trailing commas
#undef RAPIDJSON_PARSE_DEFAULT_FLAGS
#define RAPIDJSON_PARSE_DEFAULT_FLAGS kParseTrailingCommasFlag

// Print the data stored in a vec3 to the stream using JSON array format
static char readBuffer[65536];

std::vector<EntityID> DeserializeLevel(const char* level)
{
  // Create a c-style string that represents the file path
#ifdef _MSVC
  std::wstringstream filepath;
  wchar_t* path = 0;
  SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &path);
  filepath << path << L"\\DigiPen\\Umbra\\levels\\" << level << ".json";
  CoTaskMemFree(static_cast<void*>(path));
  if (!std::filesystem::exists(filepath.str()))
  {
    filepath.str(L"");
    filepath << "./data/levels/" << level << ".json";
  }
#else
  std::stringstream filepath;
  filepath << "./data/levels/" << level << ".json";
#endif

  // Attempt to open the file for reading
  //printf("Attempting to open file %s for reading", filePath); // Debug print
#ifdef _MSVC
  FILE* file;
  _wfopen_s(&file, filepath.str().c_str(), L"rb");
#else
  FILE* file = std::fopen(filepath.str().c_str(), "rb");
#endif

  TraceLogger::Assert(file, "file %s was opened for reading", filepath.str().c_str());

  // Buffer to read file into
  // (I'm basing this off the example from the RapidJSON website)


  memset(readBuffer, 0, sizeof(readBuffer));
  // Read the file into a RapidJSON filestream
  rapidjson::FileReadStream stream(file, readBuffer, sizeof(readBuffer));

  rapidjson::Document doc;

  doc.ParseStream(stream);

  // Close the file to avoid errors from asserts
  fclose(file);

  // Check for the "objects" member array
  //printf("Checking file %s for objects member\n", filePath); // Debug print
  TraceLogger::Assert(doc.HasMember("objects"), "file %s has objects member", filepath.str().c_str());
  //printf("Checking that objects member is array\n"); // Debug print
  TraceLogger::Assert(doc["objects"].IsArray(), "objects member is array");

  // Store a reference for quick access
  rapidjson::Value& objects = doc["objects"];

  // The result vector data structure
  // This is probably not efficient. Consider replacing with a straight array?
  std::vector<EntityID> resVec;

  resVec.reserve(objects.Size());

  // Loop through the entire array of objects
  for (rapidjson::SizeType i = 0; i < objects.Size(); i++)
  {
#ifdef _MSVC
    rapidjson::Value& object = objects[i];
    int size = WideCharToMultiByte(CP_UTF8, 0, &(filepath.str()[0]), (int)filepath.str().size(), NULL, 0, NULL, NULL);
    std::string newPath(size, 0);
    WideCharToMultiByte(CP_UTF8, 0, &(filepath.str()[0]), (int)filepath.str().size(), &(newPath[0]), size, NULL, NULL);
    EntityID id = EntityFactory::CreateObject(object, newPath.c_str());
    resVec.push_back(id);
#else
    rapidjson::Value& object = objects[i];
    EntityID id = EntityFactory::CreateObject(object, filepath.str().c_str());
    resVec.push_back(id);
#endif
  }

  return resVec;
}

void CheckTransform(rapidjson::Value& object, EntityID ID, const char* filePath, bool mandate)
{
  if (object.HasMember("transform"))
  {
    //printf("Checking that %s transform component is nested object\n", filePath); // Debug print
    assert(object["transform"].IsObject());

    // If this is mandated, we're treating it as a completely new object
    if (mandate)
    {
      //printf("Activating ID Transform: %d\n", ID);

      TransformComponentManager::Activate(ID);
    }

    // Check for translation
    if (mandate || object["transform"].HasMember("translation"))
    {
      // Create and assign translation
      // (Doing it this way has one extra line, but it's fine)
      glm::vec4 translation = CreateMemberVec4(object, filePath, "transform", "translation");
      // Assign the translation
      TransformComponentManager::SetTranslation(translation, ID);

      //printf("Setting ID: %d to < %f, %f >\n", ID, TransformComponentManager::GetTranslation(ID).x,
        //TransformComponentManager::GetTranslation(ID).y);
      TraceLogger::Log(TraceLogger::TRACE, "Setting ID: %d to <%.2f, %.2f>\n", ID, TransformComponentManager::GetTranslation(ID).x,
        TransformComponentManager::GetTranslation(ID).y);

    }

    // Check for rotation
    if (mandate || object["transform"].HasMember("rotation"))
    {
      float rotation = CheckFloat(object, filePath, "transform", "rotation");

      // Assign the rotation
      TransformComponentManager::SetRotation(rotation, ID);
    }


    // Check for scale
    if (mandate || object["transform"].HasMember("scale"))
    {
      if (object["transform"]["scale"].IsArray())
      {
        glm::vec3 scale = CreateMemberVec3(object, filePath, "transform", "scale");
        TransformComponentManager::SetScale(scale, ID);
      }
      else if (object["transform"]["scale"].IsFloat())
      {
        TransformComponentManager::SetScale(glm::vec3(TextureAtlaser::GetBrayanTexture(TextureComponentManager::getFilePath(ID)), 0), ID);
      }

      // Assign the scale


      //printf("Scaling ID: %d to < %f, %f >\n", ID, TransformComponentManager::GetScale(ID).x,
        //TransformComponentManager::GetScale(ID).y);

    }


  }
}


void CheckPhysics(rapidjson::Value& object, EntityID ID, const char* filePath, bool mandate)
{
  // Check that the physics component exists
  if (object.HasMember("physics"))
  {
    //printf("Checking that %s physics component is nested object\n", filePath); // Debug print
    assert(object["physics"].IsObject());

    if (mandate)
    {
      // Activate the physics
      PhysicsComponentManager::Activate(ID);
    }

    //Check for body type
    if (object["physics"].HasMember("type"))
    {
      std::string typeString(object["physics"]["type"].GetString());
      typeString = str_toupper(typeString);
      PhysicsComponentManager::SetBodyType(magic_enum::enum_cast<PhysicsComponentManager::BodyType>(typeString.c_str()).value(), ID);
    }
    else { PhysicsComponentManager::SetBodyType(PhysicsComponentManager::BodyType::STATIC, ID); }

    // Check for and create the velocity
    if (mandate || object["physics"].HasMember("velocity"))
    {
      glm::vec4 velocity = CreateMemberVec4(object, filePath, "physics", "velocity");

      // Assign the velocity
      PhysicsComponentManager::SetVelocity(velocity, ID);
    }

    // Check for and create the acceleration
    if (mandate || object["physics"].HasMember("acceleration"))
    {
      glm::vec4 acceleration = CreateMemberVec4(object, filePath, "physics", "acceleration");

      // Assign the acceleration
      PhysicsComponentManager::SetAcceleration(acceleration, ID);
    }

    // Check for and obtain the rotational velocity
    //TODO: rotational velocity?
    if (mandate || object["physics"].HasMember("acceleration"))
    {
      float rotVel = CheckFloat(object, filePath, "physics", "rotational velocity");

      PhysicsComponentManager::SetRotationalVelocity(rotVel, ID);
    }

    // Check for and obtain the drag
    if (mandate || object["physics"].HasMember("drag"))
    {
      glm::vec4 drag = CreateMemberVec4(object, filePath, "physics", "drag");

      PhysicsComponentManager::SetDrag(drag, ID);
    }

    // Check for and obatin the inverse mass
    if (mandate || object["physics"].HasMember("inverse mass"))
    {
      float invMass = CheckFloat(object, filePath, "physics", "inverse mass");

      PhysicsComponentManager::SetInverseMass(invMass, ID);
    }
  }
}


void CheckAnimation(rapidjson::Value& object, EntityID ID, const char* filePath)
{
  // Check that the object has an animation component
  if (object.HasMember("animation"))
  {
    // Check that the animation component is properly formatted
    //printf("Checking that %s animation component is nested object\n", filePath); // Debug print
    assert(object["animation"].IsObject());

    // Activate the animation
    AnimationComponentManager::Activate(ID);

    rapidjson::Value& animations = object["animation"]["animations"];
    assert(animations[0].IsObject());
    for (unsigned int i = 0; i < animations.Size(); ++i)
    {
      int animID = animations[i]["id"].GetInt();
      AnimationComponentManager::AddNewAnimation(ID, animID);
      // Check for and obtain the frames member
      //printf("Checking that %s animation component has frames member\n", filePath); // Debug print
      assert(animations[i].HasMember("frames"));
      //printf("Checking that %s frames member is an array\n", filePath); // Debug print
      assert(animations[i]["frames"].IsArray());

      // Store a reference for quick access
      rapidjson::Value& frames = animations[i]["frames"];

      // Loop through the array
      for (unsigned int j = 0; j < frames.Size(); j++)
      {
        // Check that the member at this index is an object
        //printf("Checking that %s frames member array has an object at index %i\n", filePath, i);
        assert(frames[j].IsObject());

        // Check object for index member
        // Since the int is not in a nested object in this object, there is no helper function as of yet
        //printf("Checking that %s frames member array object at index %i has index member\n", filePath, i);
        assert(frames[j].HasMember("index"));
        //printf("Checking that %s frames member array object at index %i index member is int\n", filePath, i);
        assert(frames[j]["index"].IsInt());
        int index = frames[j]["index"].GetInt();

        // Check object for duration member
        // Since this is a unique case as described for index, there is no helper function as of yet
        //printf("Checking that %s frames member array object at index %i has duration member\n", filePath, i);
        assert(frames[j].HasMember("duration"));
        //printf("Checking that %s frames member array object at index %i duration member is float\n", filePath, i);
        assert(frames[j]["duration"].IsFloat());
        float duration = frames[j]["duration"].GetFloat();

        // Add the frame to the animation
        AnimationComponentManager::AddFrame(index, duration, ID, animID);

      }

      // Check that animation component has looping member
      bool looping = animations[i]["looping"].GetBool();

      // Assign the looping bool
      AnimationComponentManager::SetLooping(looping, ID, animID);

      // Check that the animation component has the current frame member
      int currentFrame = animations[i]["current frame"].GetInt();

      // Assign the current frame
      AnimationComponentManager::SetCurrentFrameIndex(currentFrame, ID, animID);

      // Check that the animation component has running member
      bool running = animations[i]["running"].GetBool();

      // If the animation is running, start playing the animation
      if (running)
      {
        AnimationComponentManager::Play(ID, animID);
      }
    }
  }
}

void CheckTexture(rapidjson::Value& object, EntityID ID, const char* filePath)
{
  // Check for the texture member
  if (object.HasMember("texture"))
  {
    // Check that it's a string

    // Create the texture
    TextureComponentManager::Activate(ID);
    if (object["texture"].IsString())
    {
      TextureComponentManager::SetFilePath(ID, object["texture"].GetString());
    }
    else if (object["texture"].IsArray())
    {
      for (int i = 0; i < object["texture"].Size(); ++i)
        TextureComponentManager::SetFilePath(ID, object["texture"][i].GetString(), i);
    }
    else if (object["texture"].IsObject())
    {
      if (object["texture"].HasMember("filepath"))
      {
        if (object["texture"]["filepath"].IsString())
          TextureComponentManager::SetFilePath(ID, object["texture"]["filepath"].GetString());
        else if (object["texture"]["filepath"].IsArray())
          for (int i = 0; i < object["texture"]["filepath"].Size(); ++i)
            TextureComponentManager::SetFilePath(ID, object["texture"]["filepath"][i].GetString(), i);
      }
      if (object["texture"].HasMember("uvs"))
      {
        TextureComponentManager::SetUV(ID, { object["texture"]["uvs"][0].GetFloat(),object["texture"]["uvs"][1].GetFloat() });
      }
      if (object["texture"].HasMember("color"))
      {
        TextureComponentManager::SetColor(ID, { object["texture"]["color"][0].GetFloat(),
                                                object["texture"]["color"][1].GetFloat(),
                                                object["texture"]["color"][2].GetFloat(),
                                                object["texture"]["color"][3].GetFloat() });
      }
    }
    //GLuint texture = TextureComponentManager::LoadTexture(ID);

    // Assign the texture to the object
    //TextureComponentManager::SetTextureID(ID, texture);
  }
}

void CheckCollider(rapidjson::Value& object, EntityID ID, const char* filePath)
{
  //TODO:redo this later

  if (object.HasMember("collider"))
  {
    assert(object["collider"].IsObject());
    ColliderComponentManager::Activate(ID);

    //Extract collider type
    std::string typeString(object["collider"]["type"].GetString());
    typeString = str_toupper(typeString);
    Collider::ShapeType type = magic_enum::enum_cast<Collider::ShapeType>(typeString.c_str()).value();

    //TODO: make deserialize collider function
    switch (type)
    {
    case Collider::ShapeType::INACTIVE: break;
    case Collider::ShapeType::INVALID: break;
    case Collider::ShapeType::POINT:

      break;
    case Collider::ShapeType::LINE:
      break;
    case Collider::ShapeType::CIRCLE:
      break;
    case Collider::ShapeType::POLYGON:
      ColliderComponentManager::SetPolygonCollider(ID);
      break;
    case Collider::ShapeType::RECTANGLE:
      ColliderComponentManager::SetRectangleCollider(ID);
      break;
    case Collider::ShapeType::COUNT: break;
    default:;
    }
  }

  //// Check for the texture member
  //if (object.HasMember("collider"))
  //{
  //  // Check that it's a string
  //  //printf("Checking that %s collider value is object\n", filePath);
  //  assert(object["collider"].IsObject());

  //  // Create the texture
  //  ColliderComponentManager::Activate(ID);

  //  //printf("Checking that %s collider value has type\n", filePath);
  //  assert(object["collider"].HasMember("type"));
  //  
  //  //printf("Checking that %s collider type is string\n", filePath);
  //  assert(object["collider"]["type"].IsString());

  //  std::string typeString(object["collider"]["type"].GetString());
  //  typeString = str_toupper(typeString);
  //  ColliderComponentManager::Type type = magic_enum::enum_cast<ColliderComponentManager::Type>(typeString.c_str()).value();

  //  //TODO: deserialize other types of hitboxes besides rectangle
  //  switch (type)
  //  {
  //  case ColliderComponentManager::Type::RECTANGLE :

  //    //printf("Checking that %s collider value has hitbox\n", filePath);
  //    assert(object["collider"].HasMember("hitbox"));

  //    //printf("Checking that %s collider hitbox is object\n", filePath);
  //    assert(object["collider"]["hitbox"].IsObject());

  //    //printf("Checking that %s collider hitbox has offset\n", filePath);
  //    assert(object["collider"]["hitbox"].HasMember("offset"));

  //    //printf("Checking that %s collider hitbox has size\n", filePath);
  //    assert(object["collider"]["hitbox"].HasMember("size"));

  //    glm::vec2 offset = CreateMemberVec2(object["collider"], filePath, "hitbox", "offset");
  //    glm::vec2 size = CreateMemberVec2(object["collider"], filePath, "hitbox", "size");
  //    
  //    ColliderComponentManager::SetRectangularHitbox(ID, { offset, size });
  //    break;
  //  }

  //}
}

void CheckShader(rapidjson::Value& object, EntityID ID, const char* filePath)
{
  // Check that the object has a shader component
  if (object.HasMember("shader"))
  {
    // Check that the shader component is a nested object
    //printf("Checking that %s shader component is a nested object\n", filePath);
    assert(object["shader"].IsObject());

    // Check the nested shader for its components
    const char* vertex = CheckString(object, filePath, "shader", "vertex");
    const char* fragment = CheckString(object, filePath, "shader", "fragment");

    // Activate the shader
    //ShaderModule::Activate(ID);
    //GLSLShader shader = ShaderModule::CreateShader(ID, vertex, fragment);
    //ShaderModule::SetShader(ID, shader);
  }
}

void CheckSpineSkeleton(rapidjson::Value& object, EntityID ID, const char* filePath)
{
  //Check if the object has a spine instance component
  if (object.HasMember("spineSkeleton"))
  {
    assert(object["spineSkeleton"].IsObject());

    //Load in data
    const char* spineSkeletonName = CheckString(object, filePath, "spineSkeleton", "name");
    const char* spineJsonPath = CheckString(object, filePath, "spineSkeleton", "json");
    const char* spineAtlasPath = CheckString(object, filePath, "spineSkeleton", "atlas");
    const char* defaultSkinName = CheckString(object, filePath, "spineSkeleton", "skin");
    const char* defaultAnimationName = CheckString(object, filePath, "spineSkeleton", "defaultAnim");
    float scaleOffset = CheckFloat(object, filePath, "spineSkeleton", "scaleOffset");

    //Add data
    SpineDataManager::LoadData(spineSkeletonName, spineAtlasPath, spineJsonPath, scaleOffset);

    SpineSkeletonComponentManager::Activate(ID);
    SpineAnimationComponentManager::Activate(ID);
    SpineSkeletonComponentManager::SetSkeleton(ID, spineSkeletonName);
    SpineAnimationComponentManager::SetAnimation(ID, spineSkeletonName);

    SpineSkeleton& skeleton = SpineSkeletonComponentManager::GetSkeleton(ID);
    SpineAnimation& animation = SpineAnimationComponentManager::GetAnimation(ID);

    skeleton.ChangeSkin(defaultSkinName);
    animation.ChangeAnimation(defaultAnimationName, true);
  }
}


glm::vec4 DeserializeVec4(rapidjson::Value& object)
{
  float memberX = object[0].GetFloat();
  float memberY = object[1].GetFloat();
  float memberZ = object[2].GetFloat();
  float memberW = object[3].GetFloat();

  // Create the vec4 for the member
  glm::vec4 memberVec(memberX, memberY, memberZ, memberW);

  return memberVec;
}

glm::vec3 DeserializeVec3(rapidjson::Value& object)
{
  float memberX = object[0].GetFloat();
  float memberY = object[1].GetFloat();
  float memberZ = object[2].GetFloat();

  // Create the vec4 for the member
  glm::vec3 memberVec(memberX, memberY, memberZ);

  return memberVec;
}

glm::vec2 DeserializeVec2(rapidjson::Value& object)
{
  float memberX = object[0].GetFloat();
  float memberY = object[1].GetFloat();

  // Create the vec4 for the member
  glm::vec2 memberVec(memberX, memberY);

  return memberVec;
}

AnimationComponentManager::AnimationData DeserializeAnimation(rapidjson::Value& sprite)
{
  AnimationComponentManager::AnimationData animdata;
  if (sprite.HasMember("frames"))
    for (unsigned k = 0; k < sprite["frames"].Size(); ++k)
      animdata.frames_.push_back({ sprite["frames"][k]["index"].GetInt(),sprite["frames"][k]["duration"].GetFloat() });
  if (sprite.HasMember("looping"))
    animdata.looping_ = sprite["looping"].GetBool();
  if (sprite.HasMember("running"))
    animdata.isRunning_ = sprite["running"].GetBool();
  if (sprite.HasMember("current frame"))
    animdata.currentFrame_ = sprite["current frame"].GetInt();
  return animdata;
}

float CheckFloat(rapidjson::Value& object, const char* filePath,
  const char* component, const char* member)
{
  // Check for float
  //printf("Checking that %s %s component has %s\n", filePath, component, member); // Debug print
  assert(object[component].HasMember(member));
  //printf("Checking that %s %s is a float\n", filePath, member); // Debug print
  assert((object[component])[member].IsFloat());

  return object[component][member].GetFloat();
}

int CheckInt(rapidjson::Value& object, const char* filePath,
  const char* component, const char* member)
{
  // Check for int
  //printf("Checking that %s %s component has %s\n", filePath, component, member); // Debug print
  assert(object[component].HasMember(member));
  //printf("Checking that %s %s is an int\n", filePath, member); // Debug print
  assert((object[component])[member].IsInt());

  return object[component][member].GetInt();
}

bool CheckBool(rapidjson::Value& object, const char* filePath,
  const char* component, const char* member)
{
  // Check for bool
  //printf("Checking that %s %s component has %s\n", filePath, component, member); // Debug print
  assert(object[component].HasMember(member));
  //printf("Checking that %s %s is a bool\n", filePath, member); // Debug print
  assert(object[component][member].IsBool());

  return object[component][member].GetBool();
}

const char* CheckString(rapidjson::Value& object, const char* filePath,
  const char* component, const char* member)
{
  // Check for string
  //printf("Checking that %s %s component has %s\n", filePath, component, member);
  assert(object[component].HasMember(member));
  //printf("Checking that %s %s is a string\n", filePath, member);
  assert(object[component][member].IsString());

  return object[component][member].GetString();
}
