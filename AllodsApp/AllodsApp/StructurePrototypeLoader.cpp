#include "stdafx.h"
#include "StructurePrototypeLoader.h"

#include <LaggySdk/json.h>


namespace
{
  Layer getLayerByName(const std::string& i_name)
  {
    const std::unordered_map<std::string, Layer> LayersMap {
      { "Panneling", Layer::Panneling },
      { "Floor", Layer::Floor },
    };

    CONTRACT_ENSURE(LayersMap.size() == static_cast<int>(Layer::Count));
    return LayersMap.at(i_name);
  }

  bool hasPrototype(const std::vector<StructurePrototype>& i_prototypes, const std::string& i_name)
  {
    return std::any_of(i_prototypes.cbegin(), i_prototypes.cend(), [&](const auto& i_prototype) {
      return i_prototype.name == i_name; });
  }

} // anonym NS


std::vector<StructurePrototype> StructurePrototypeLoader::load(const fs::path& i_filepath)
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
    proto.textureName = protoNode["TextureName"].asString();
    proto.layer = getLayerByName(protoNode["Layer"].asString());
    proto.support = protoNode["Support"].asBool();

    prototypes.push_back(std::move(proto));
  }

  return prototypes;
}
