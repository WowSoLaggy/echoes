#include "stdafx.h"
#include "PrototypeLoader.h"

#include <LaggyDx/TextureUtils.h>

#include <LaggySdk/json.h>


namespace
{
  bool hasPrototype(const auto& i_prototypes, const std::string& i_name)
  {
    return std::any_of(i_prototypes.cbegin(), i_prototypes.cend(), [&](const auto& i_prototype) {
      return i_prototype.name == i_name; });
  }

} // anonym NS


std::vector<AvatarPrototype> PrototypeLoader::loadAvatars(const fs::path& i_filepath)
{
  CONTRACT_EXPECT(fs::exists(i_filepath));

  Json::Value root;
  {
    Json::Reader reader;
    std::ifstream file(i_filepath.string(), std::ifstream::binary);
    const bool parseOk = reader.parse(file, root, false);
    CONTRACT_ASSERT(parseOk);
  }

  std::vector<AvatarPrototype> prototypes;
  for (const auto& protoName : root.getMemberNames())
  {
    CONTRACT_EXPECT(!hasPrototype(prototypes, protoName));

    const auto& protoNode = root[protoName];
    AvatarPrototype proto;

    proto.name = protoName;
    const auto textureName = protoNode["TextureName"].asString();
    proto.texture = &Dx::TextureUtils::getTexture(textureName);

    prototypes.push_back(std::move(proto));
  }

  return prototypes;
}

std::vector<MountPrototype> PrototypeLoader::loadMounts(const fs::path& i_filepath)
{
  CONTRACT_EXPECT(fs::exists(i_filepath));

  Json::Value root;
  {
    Json::Reader reader;
    std::ifstream file(i_filepath.string(), std::ifstream::binary);
    const bool parseOk = reader.parse(file, root, false);
    CONTRACT_ASSERT(parseOk);
  }

  std::vector<MountPrototype> prototypes;
  for (const auto& protoName : root.getMemberNames())
  {
    CONTRACT_EXPECT(!hasPrototype(prototypes, protoName));

    const auto& protoNode = root[protoName];
    MountPrototype proto;

    proto.name = protoName;
    const auto textureName = protoNode["TextureName"].asString();
    proto.texture = &Dx::TextureUtils::getTexture(textureName);

    if (protoNode.isMember("Behavior"))
      proto.bahaviorModel = BehaviorModelStr::fromString(protoNode["Behavior"].asString());

    prototypes.push_back(std::move(proto));
  }

  return prototypes;
}

std::vector<StructurePrototype> PrototypeLoader::loadStructures(const fs::path& i_filepath)
{
  CONTRACT_EXPECT(fs::exists(i_filepath));

  Json::Value root;
  {
    Json::Reader reader;
    std::ifstream file(i_filepath.string(), std::ifstream::binary);
    const bool parseOk = reader.parse(file, root, false);
    CONTRACT_ASSERT(parseOk);
  }

  std::vector<StructurePrototype> prototypes;
  for (const auto& protoName : root.getMemberNames())
  {
    CONTRACT_EXPECT(!hasPrototype(prototypes, protoName));

    const auto& protoNode = root[protoName];
    StructurePrototype proto;

    proto.name = protoName;
    const auto textureName = protoNode["TextureName"].asString();
    proto.texture = &Dx::TextureUtils::getTexture(textureName);
    proto.layer = LayerStr::fromString(protoNode["Layer"].asString());

    if (protoNode.isMember("Support"))
      proto.support = protoNode["Support"].asBool();

    if (protoNode.isMember("Fixture"))
      proto.fixture = protoNode["Fixture"].asBool();

    if (protoNode.isMember("Behavior"))
      proto.bahaviorModel = BehaviorModelStr::fromString(protoNode["Behavior"].asString());

    prototypes.push_back(std::move(proto));
  }

  return prototypes;
}

std::vector<ObjectPrototype> PrototypeLoader::loadObjects(const fs::path& i_filepath)
{
  CONTRACT_EXPECT(fs::exists(i_filepath));

  Json::Value root;
  {
    Json::Reader reader;
    std::ifstream file(i_filepath.string(), std::ifstream::binary);
    const bool parseOk = reader.parse(file, root, false);
    CONTRACT_ASSERT(parseOk);
  }

  std::vector<ObjectPrototype> prototypes;
  for (const auto& protoName : root.getMemberNames())
  {
    CONTRACT_EXPECT(!hasPrototype(prototypes, protoName));

    const auto& protoNode = root[protoName];
    ObjectPrototype proto;

    proto.name = protoName;
    const auto textureName = protoNode["TextureName"].asString();
    proto.texture = &Dx::TextureUtils::getTexture(textureName);

    if (protoNode.isMember("Behavior"))
      proto.bahaviorModel = BehaviorModelStr::fromString(protoNode["Behavior"].asString());

    prototypes.push_back(std::move(proto));
  }

  return prototypes;
}
