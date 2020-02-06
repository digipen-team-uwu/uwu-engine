#include <UWUEngine/Entity/EntityCacher.h>
#include <UWUEngine/Entity/EntityFactory.h>
#include <UWUEngine/Component/PhysicsComponentManager.h>
#include <UWUEngine/Component/TextureComponentManager.h>
#include <UWUEngine/Component/AnimationComponentManager.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <rapidjson/document.h>
#include <cstdio>
#include <filesystem>
#include <rapidjson/filereadstream.h>
#include <UWUEngine/Deserialization.h>
#include <UWUEngine/Helper.h>
#include <UWUEngine/Graphics/SpineAnimation/SpineDataManager.h>
#include <UWUEngine/Component/SpineAnimationComponentManager.h>
#include <UWUEngine/Component/SpineSkeletonComponentManager.h>
#include <magic_enum.hpp>
#include <UWUEngine/Component/BehaviorComponentManager.h>
#include <UWUEngine/Debugs/TraceLogger.h>
#include <UWUEngine/Component/ColliderComponentManager.h>

//Colliders
#include <UWUEngine/Physics/Colliders/ColliderPolygon.h>
#include <UWUEngine/Physics/Colliders/ColliderCircle.h>
#include <UWUEngine/Physics/Colliders/ColliderPoint.h>
#include <UWUEngine/Physics/Colliders/ColliderLine.h>

template<>
int RegisterSystemHelper<EntityCacher>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<EntityCacher>(SystemInitOrder::Cacher, SystemUpdateOrder::LAST);

namespace sc = SerializationConstants;

std::unordered_map<EntityManager::Type, CachedEntity> EntityCacher::entities;
std::vector<std::string> EntityCacher::cachedFilepaths;
std::unordered_map<std::string, BaseCachedBehavior*> EntityCacher::behaviors;

void EntityCacher::UpdateCachedBehavior(std::string filename)
{
  auto& cache = behaviors[filename];
  rapidjson::Document obj;
  MakeJsonObject(cache->filepath.c_str(), obj);
  cache->Deserialize(obj);
}

void EntityCacher::InstantiateCachedBehavior(EntityID id, std::string fileName)
{
  if (!BehaviorComponentManager::IsActive(id))
  {
    BehaviorComponentManager::Activate(id);
  }
  behaviors[fileName]->Instantiate(id);
}

void EntityCacher::MakeJsonObject(const char* filepath, rapidjson::Document& obj)
{
  FILE* file = std::fopen(filepath, "rb");
  assert(file);
  rapidjson::FileReadStream stream(file, EntityFactory::readBuffer, sizeof(EntityFactory::readBuffer));
  obj.ParseStream(stream);
  fclose(file);
}

EntityCacher::EntityCacher()
{
  for (const auto& dir : std::filesystem::directory_iterator(sc::JSON_PATH))
  {
    for (auto i : EntityManagerTypeIterator())
    {
      //add 1 to path because dir path adds a backslash
      std::string key = dir.path().string().substr(strlen(sc::JSON_PATH) + 1);

      if (key == magic_enum::enum_name(i).data())
      {
        for (const auto& file : std::filesystem::directory_iterator(dir.path().string()))
        {
          BaseCachedBehavior* cache = BehaviorComponentManager::CreateCachedBehavior(i);
          cache->filepath = file.path().string();
          rapidjson::Document obj;
          MakeJsonObject(cache->filepath.c_str(), obj);
          cache->Deserialize(obj);
          //get rid of json path and key, plus two backslashes
          std::string partKey = file.path().string().substr(strlen(sc::JSON_PATH) + 1 + key.length() + 1);
          //get rid of ".json"
          partKey = partKey.substr(0, partKey.length() - 5);
          CacheBehavior(partKey, cache);
        }
        break;
      }
    }
  }
  for (const auto& file : std::filesystem::directory_iterator("./data/entities"))
  {
    rapidjson::Document obj;
    MakeJsonObject(file.path().string().c_str(), obj);
    CachedEntity entity;

    if (obj.HasMember("type"))
    {
      entity.type = magic_enum::enum_cast<EntityManager::Type>(obj["type"].GetString()).value();
    }

    if (obj.HasMember("transform"))
    {
      entity.transform.active = true;
      if (obj["transform"].HasMember("translation"))
      {
        entity.transform.translation = DeserializeVec4(obj["transform"]["translation"]);
      }
      if (obj["transform"].HasMember("rotation"))
      {
        entity.transform.rotation = obj["transform"]["rotation"].GetFloat();
      }
      if (obj["transform"].HasMember("scale"))
      {
        entity.transform.scale = DeserializeVec3(obj["transform"]["scale"]);
      }
    }

    if (obj.HasMember("physics"))
    {
      entity.physics.active = true;
      if (obj["physics"].HasMember("type"))
      {
        std::string typeString(obj["physics"]["type"].GetString());
        typeString = str_toupper(typeString);
        entity.physics.type = magic_enum::enum_cast<PhysicsComponentManager::BodyType>(typeString.c_str()).value();
      }
      if (obj["physics"].HasMember("velocity"))
      {
        entity.physics.velocity = DeserializeVec4(obj["physics"]["velocity"]);
      }
      if (obj["physics"].HasMember("drag"))
      {
        entity.physics.drag = DeserializeVec4(obj["physics"]["drag"]);
      }
      if (obj["physics"].HasMember("acceleration"))
      {
        entity.physics.acceleration = DeserializeVec4(obj["physics"]["acceleration"]);
      }
      if (obj["physics"].HasMember("rotational velocity"))
      {
        entity.physics.rotationalVelocity = obj["physics"]["rotational velocity"].GetFloat();
      }
      if (obj["physics"].HasMember("inverse mass"))
      {
        entity.physics.inverseMass = obj["physics"]["inverse mass"].GetFloat();
      }
    }

    if (obj.HasMember("texture"))
    {
      entity.texture.active = true;
      if (obj["texture"].IsString())
      {
        entity.texture.filepaths[0] = obj["texture"].GetString();
        cachedFilepaths.push_back(entity.texture.filepaths[0]);
      }
      else if (obj["texture"].IsArray())
      {
        for (int i = 0; i < obj["texture"].Size(); ++i)
        {
          entity.texture.filepaths[i] = obj["texture"][i].GetString();
          cachedFilepaths.push_back(entity.texture.filepaths[i]);
        }
      }
    }

    if (obj.HasMember("animation"))
    {
      for (int i = 0; i < obj["animation"]["animations"].Size(); ++i)
      {
        entity.animation.active = true;
        entity.animation.animations[i] = DeserializeAnimation(obj["animation"]["animations"][i]);
      }
    }

    if (obj.HasMember("collider"))
    {
      entity.collider.active = true;
      std::string typeString(obj["collider"]["type"].GetString());
      typeString = str_toupper(typeString);
      entity.collider.type = magic_enum::enum_cast<Collider::ShapeType>(typeString.c_str()).value();

      switch (entity.collider.type)
      {
      case Collider::ShapeType::INACTIVE:
        break;
      case Collider::ShapeType::INVALID:
        break;
      case Collider::ShapeType::POINT:
        TraceLogger::Assert(obj["collider"]["position"].IsArray(), "Point Collider (position) is in correct format");

        entity.collider.collider = static_cast<Collider*>(new ColliderPoint(
          0,
          DeserializeVec2(obj["collider"]["position"])
        ));
        break;
      case Collider::ShapeType::LINE:
        TraceLogger::Assert(obj["collider"]["start"].IsArray(), "Line Collider (start) is in correct format");
        TraceLogger::Assert(obj["collider"]["end"].IsArray(), "Line Collider (end) is in correct format");

        entity.collider.collider = static_cast<Collider*>(new ColliderLine(
          0,
          DeserializeVec2(obj["collider"]["start"]),
          DeserializeVec2(obj["collider"]["end"])
        ));
        break;
      case Collider::ShapeType::CIRCLE:
        TraceLogger::Assert(obj["collider"]["center"].IsArray(), "Circle Collider (center) is in correct format");
        TraceLogger::Assert(obj["collider"]["radius"].IsFloat(), "Circle Collider (start) is in correct format");

        entity.collider.collider = static_cast<Collider*>(new ColliderCircle(
          0,
          DeserializeVec2(obj["collider"]["center"]),
          obj["collider"]["radius"].GetFloat()
        ));
        break;
      case Collider::ShapeType::POLYGON:
      {
        TraceLogger::Assert(obj["collider"]["center"].IsArray(), "Polygon Collider (center) is in correct format");
        TraceLogger::Assert(obj["collider"]["vertices"].IsArray(), "Polygon Collider (vertices) is in correct format");

        ColliderPolygon* collider = new ColliderPolygon(
          0,
          DeserializeVec2(obj["collider"]["center"])
        );
        for (rapidjson::SizeType i = 0; i < obj["collider"]["vertices"].Size(); ++i)
        {
          glm::vec2 vertex = DeserializeVec2(obj["collider"]["vertices"][i]);
          collider->InsertVertex(vertex);
        }
        entity.collider.collider = static_cast<Collider*>(collider);
      }
      break;
      case Collider::ShapeType::RECTANGLE:
        entity.collider.collider = static_cast<Collider*>(new ColliderPolygon(0));
        // Default
        break;
      default:;
      }
    }

    if (obj.HasMember("spineSkeleton"))
    {
      entity.spineSkeleton.active = true;
      if (obj["spineSkeleton"].HasMember("name"))
      {
        entity.spineSkeleton.name = obj["spineSkeleton"]["name"].GetString();
      }
      if (obj["spineSkeleton"].HasMember("json"))
      {
        entity.spineSkeleton.json = obj["spineSkeleton"]["json"].GetString();
      }
      if (obj["spineSkeleton"].HasMember("atlas"))
      {
        entity.spineSkeleton.atlas = obj["spineSkeleton"]["atlas"].GetString();
      }
      if (obj["spineSkeleton"].HasMember("skin"))
      {
        entity.spineSkeleton.skin = obj["spineSkeleton"]["skin"].GetString();
      }
      if (obj["spineSkeleton"].HasMember("defaultAnim"))
      {
        entity.spineSkeleton.defualtAnim = obj["spineSkeleton"]["defaultAnim"].GetString();
      }
      if (obj["spineSkeleton"].HasMember("scaleOffset"))
      {
        entity.spineSkeleton.scaleOffset = obj["spineSkeleton"]["scaleOffset"].GetFloat();
      }
    }

    EntityCacher::CacheEntity(entity);
  }
}

void EntityCacher::CacheBehavior(std::string filepath, BaseCachedBehavior* behavior)
{
  behaviors[filepath] = behavior;
}

void EntityCacher::CacheFile(std::string file)
{
  cachedFilepaths.push_back(file);
}

const std::vector<std::string>& EntityCacher::GetCachedFilepaths()
{
  return cachedFilepaths;
}

void EntityCacher::CacheEntity(const CachedEntity& entity)
{
  entities[entity.type] = entity;
}

EntityID EntityCacher::CreateCachedEntity(const CachedEntity& entity)
{
  EntityID object = EntityManager::New(entity.type);

  if (entity.physics.active)
  {
    PhysicsComponentManager::Activate(object);
    PhysicsComponentManager::SetBodyType(entity.physics.type, object);
    PhysicsComponentManager::SetAcceleration(entity.physics.acceleration, object);
    PhysicsComponentManager::SetDrag(entity.physics.drag, object);
    PhysicsComponentManager::SetInverseMass(entity.physics.inverseMass, object);
    PhysicsComponentManager::SetRotationalVelocity(entity.physics.rotationalVelocity, object);
    PhysicsComponentManager::SetVelocity(entity.physics.velocity, object);
  }

  if (entity.transform.active)
  {
    TransformComponentManager::Activate(object);
    TransformComponentManager::SetTranslation(entity.transform.translation, object);
    TransformComponentManager::SetRotation(entity.transform.rotation, object);
    TransformComponentManager::SetScale(entity.transform.scale, object);
  }

  if (entity.collider.active)
  {
    ColliderComp::Activate(object);
    ColliderComp::SetCollider(object, entity.collider.collider);
  }

  if (entity.texture.active)
  {
    TextureComponentManager::Activate(object);
    TextureComponentManager::SetFilePaths(object, entity.texture.filepaths);
  }

  if (entity.animation.active)
  {
    AnimationComponentManager::Activate(object);
    AnimationComponentManager::AddAnimationDatas(object, entity.animation.animations);
  }

  if (entity.spineSkeleton.active)
  {
    SpineDataManager::LoadData(entity.spineSkeleton.name.c_str(), entity.spineSkeleton.atlas.c_str(), entity.spineSkeleton.json.c_str(), entity.spineSkeleton.scaleOffset);

    SpineSkeletonComponentManager::Activate(object);
    SpineAnimationComponentManager::Activate(object);
    SpineSkeletonComponentManager::SetSkeleton(object, entity.spineSkeleton.name.c_str());
    SpineAnimationComponentManager::SetAnimation(object, entity.spineSkeleton.name.c_str());

    SpineSkeleton& skeleton = SpineSkeletonComponentManager::GetSkeleton(object);
    SpineAnimation& animation = SpineAnimationComponentManager::GetAnimation(object);

    skeleton.ChangeSkin(entity.spineSkeleton.skin.c_str());
    animation.ChangeAnimation(entity.spineSkeleton.defualtAnim.c_str(), true);
  }

  return object;
}

bool EntityCacher::EntityIsCached(EntityManager::Type type)
{
  return entities.find(type) != entities.end();
}

const CachedEntity& EntityCacher::GetCachedEntity(EntityManager::Type type)
{
  return entities[type];
}