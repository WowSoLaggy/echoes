#pragma once

#include "Fwd.h"
#include "Tile.h"
#include "TileCollection.h"

#include <LaggySdk/EventHandler.h>
#include <LaggySdk/ISerializable.h>
#include <LaggySdk/Rect.h>


class Location : public Sdk::EventHandler, public Sdk::ISerializable
{
public:
  Location();

  virtual void pushFields() override;
  virtual Sdk::FieldHandled onFieldNotFound(const std::string& i_name, const Json::Value& i_json);
  virtual void onDeserialized() override;

  void setName(std::string i_name);
  const std::string& getName() const;

  void update(double i_dt);

  const Sdk::RectI& getRect() const;

  const Tiles& getTiles() const;
  Tile& getOrCreateTile(const TileCoord& i_coord);
  Tile* getTile(const TileCoord& i_coord);
  const Tile* getTile(const TileCoord& i_coord) const;
  
  Objects& getObjects();
  const Objects& getObjects() const;

  Avatars& getAvatars();
  const Avatars& getAvatars() const;

private:
  std::string d_name;

  Sdk::RectI d_minMaxRect;
  void updateMinMax(const TileCoord& i_coord);
  void updateMinMax();

  Tiles d_tiles;
  TileCollection d_tileCollection;
  Avatars d_avatars;
  Objects d_objects;
};
