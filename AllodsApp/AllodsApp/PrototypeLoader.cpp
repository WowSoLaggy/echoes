#include "stdafx.h"
#include "PrototypeLoader.h"

#include <LaggyDx/TextureUtils.h>

#include <LaggySdk/json.h>


namespace
{
  bool hasPrototype(const auto& i_prototypes, const std::string& i_name)
  {
    return std::any_of(i_prototypes.cbegin(), i_prototypes.cend(), [&](const auto& i_prototype) {
      return SAFE_DEREF(i_prototype).name == i_name; });
  }

  void loadCommon(Prototype& io_proto, const Json::Value& i_json)
  {
    CONTRACT_EXPECT(i_json.isMember("TextureName"));
    const auto textureName = i_json["TextureName"].asString();
    io_proto.texture = &Dx::TextureUtils::getTexture(textureName);

    if (i_json.isMember("Behavior"))
      io_proto.bahaviorModel = BehaviorModelStr::fromString(i_json["Behavior"].asString());

    if (i_json.isMember("Volume"))
      io_proto.volume = i_json["Volume"].asDouble();

    CONTRACT_EXPECT(i_json.isMember("Mass"));
    io_proto.mass = i_json["Mass"].asDouble();

    CONTRACT_EXPECT(i_json.isMember("Material"));
    io_proto.material = MaterialStr::fromString(i_json["Material"].asString());
  }

} // anonym NS


std::vector<PrototypePtr> PrototypeLoader::loadAvatars(const fs::path& i_filepath)
{
  CONTRACT_EXPECT(fs::exists(i_filepath));

  Json::Value root;
  {
    Json::Reader reader;
    std::ifstream file(i_filepath.string(), std::ifstream::binary);
    const bool parseOk = reader.parse(file, root, false);
    CONTRACT_ASSERT(parseOk);
  }

  std::vector<PrototypePtr> prototypes;
  for (const auto& protoName : root.getMemberNames())
  {
    CONTRACT_EXPECT(!hasPrototype(prototypes, protoName));

    const auto& protoNode = root[protoName];
    auto proto = std::make_shared<AvatarPrototype>();

    proto->name = protoName;
    loadCommon(*proto, protoNode);

    prototypes.push_back(std::move(proto));
  }

  return prototypes;
}

std::vector<PrototypePtr> PrototypeLoader::loadMounts(const fs::path& i_filepath)
{
  CONTRACT_EXPECT(fs::exists(i_filepath));

  Json::Value root;
  {
    Json::Reader reader;
    std::ifstream file(i_filepath.string(), std::ifstream::binary);
    const bool parseOk = reader.parse(file, root, false);
    CONTRACT_ASSERT(parseOk);
  }

  std::vector<PrototypePtr> prototypes;
  for (const auto& protoName : root.getMemberNames())
  {
    CONTRACT_EXPECT(!hasPrototype(prototypes, protoName));

    const auto& protoNode = root[protoName];
    auto proto = std::make_shared<MountPrototype>();

    proto->name = protoName;
    loadCommon(*proto, protoNode);

    prototypes.push_back(std::move(proto));
  }

  return prototypes;
}

std::vector<PrototypePtr> PrototypeLoader::loadStructures(const fs::path& i_filepath)
{
  CONTRACT_EXPECT(fs::exists(i_filepath));

  Json::Value root;
  {
    Json::Reader reader;
    std::ifstream file(i_filepath.string(), std::ifstream::binary);
    const bool parseOk = reader.parse(file, root, false);
    CONTRACT_ASSERT(parseOk);
  }

  std::vector<PrototypePtr> prototypes;
  for (const auto& protoName : root.getMemberNames())
  {
    CONTRACT_EXPECT(!hasPrototype(prototypes, protoName));

    const auto& protoNode = root[protoName];
    auto proto = std::make_shared<StructurePrototype>();

    proto->name = protoName;
    loadCommon(*proto, protoNode);
    
    proto->layer = LayerStr::fromString(protoNode["Layer"].asString());

    if (protoNode.isMember("Support"))
      proto->support = protoNode["Support"].asBool();

    if (protoNode.isMember("Fixture"))
      proto->fixture = protoNode["Fixture"].asBool();

    if (protoNode.isMember("SpaceExposure"))
      proto->spaceExposure = protoNode["SpaceExposure"].asBool();

    prototypes.push_back(std::move(proto));
  }

  return prototypes;
}

std::vector<PrototypePtr> PrototypeLoader::loadObjects(const fs::path& i_filepath)
{
  CONTRACT_EXPECT(fs::exists(i_filepath));

  Json::Value root;
  {
    Json::Reader reader;
    std::ifstream file(i_filepath.string(), std::ifstream::binary);
    const bool parseOk = reader.parse(file, root, false);
    CONTRACT_ASSERT(parseOk);
  }

  std::vector<PrototypePtr> prototypes;
  for (const auto& protoName : root.getMemberNames())
  {
    CONTRACT_EXPECT(!hasPrototype(prototypes, protoName));

    const auto& protoNode = root[protoName];
    auto proto = std::make_shared<ObjectPrototype>();

    proto->name = protoName;
    loadCommon(*proto, protoNode);

    prototypes.push_back(std::move(proto));
  }

  return prototypes;
}
