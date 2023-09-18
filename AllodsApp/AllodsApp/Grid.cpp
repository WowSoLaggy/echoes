#include "stdafx.h"
#include "Grid.h"

#include <LaggyDx/App.h>
#include <LaggyDx/ImageDescription.h>
#include <LaggyDx/IRenderer2d.h>
#include <LaggyDx/ITexture.h>


namespace
{
  const std::string TextureName_T = "Grid_T.png";
  const std::string TextureName_TL = "Grid_TL.png";
  const std::string TextureName_TR = "Grid_TR.png";
  const std::string TextureName_L = "Grid_L.png";
  const std::string TextureName_R = "Grid_R.png";
  const std::string TextureName_B = "Grid_B.png";
  const std::string TextureName_BL = "Grid_BL.png";
  const std::string TextureName_BR = "Grid_BR.png";
  const std::string TextureName_Item = "Grid_Item.png";
  const std::string TextureName_Frame = "Grid_Frame.png";

  const Dx::ITexture& getTexture(const fs::path& i_name)
  {
    const auto& rc = Dx::App::get().getResourceController();
    return rc.getTexture(i_name);
  }

} // anonym NS


Grid::Grid(const int i_slotsX, const int i_slotsY)
{
  resize(i_slotsX, i_slotsY);
  createGridSprites();
}


void Grid::render(Dx::IRenderer2d& i_renderer) const
{
  i_renderer.setTranslation(getPositionAbsolute());
  for (const auto& sprite : d_gridSprites)
    i_renderer.renderSprite(sprite);
}


void Grid::resize(const int i_slotsX, const int i_slotsY)
{
  d_slotsX = i_slotsX;
  d_slotsY = i_slotsY;
}


void Grid::createGridSprites()
{
  const auto& texture_T(getTexture(TextureName_T));
  const auto& texture_TL(getTexture(TextureName_TL));
  const auto& texture_TR(getTexture(TextureName_TR));
  const auto& texture_L(getTexture(TextureName_L));
  const auto& texture_R(getTexture(TextureName_R));
  const auto& texture_B(getTexture(TextureName_B));
  const auto& texture_BL(getTexture(TextureName_BL));
  const auto& texture_BR(getTexture(TextureName_BR));
  const auto& texture_Item(getTexture(TextureName_Item));
  const auto& texture_Frame(getTexture(TextureName_Frame));

  d_gridSprites.push_back(
    Dx::Sprite{ &texture_T, { 0, 0 }, texture_T.getDescription().size(), Sdk::Vector4F::identity() });
  /*d_gridSprites.emplace_back(Dx::Sprite{
    &textureTr, { CornerSize + d_slotsHor * SlotSize, 0 },
      textureTr.getDescription().size(), Sdk::Vector4F::identity() });
  d_gridSprites.emplace_back(Dx::Sprite{
    &textureBl, { 0, CornerSize + d_slotsVert * SlotSize },
      textureBl.getDescription().size(), Sdk::Vector4F::identity() });
  d_gridSprites.emplace_back(Dx::Sprite{
    &textureBr, { CornerSize + d_slotsHor * SlotSize, CornerSize + d_slotsVert * SlotSize },
      textureBr.getDescription().size(), Sdk::Vector4F::identity() });

  /*for (int i = 0; i < d_slotsHor; ++i)
  {
    d_gridSprites.emplace_back(Dx::Sprite{
      &textureT, { CornerSize + SlotSize * i, 0 },
        textureT.getDescription().size(), Sdk::Vector4F::identity() });
    d_gridSprites.emplace_back(Dx::Sprite{
      &textureB, { CornerSize + SlotSize * i, CornerSize + d_slotsVert * SlotSize },
        textureB.getDescription().size(), Sdk::Vector4F::identity() });
  }

  for (int i = 0; i < d_slotsVert; ++i)
  {
    d_gridSprites.emplace_back(Dx::Sprite{
      &textureL, { 0, CornerSize + SlotSize * i },
        textureL.getDescription().size(), Sdk::Vector4F::identity() });
    d_gridSprites.emplace_back(Dx::Sprite{
      &textureR, { CornerSize + SlotSize * d_slotsHor, CornerSize + SlotSize * i },
        textureR.getDescription().size(), Sdk::Vector4F::identity() });
  }

  for (int y = 0; y < d_slotsVert; ++y)
  {
    for (int x = 0; x < d_slotsHor; ++x)
    {
      d_framesSprites.emplace_back(Dx::Sprite{
        &textureItem, { CornerSize + SlotSize * x, CornerSize + SlotSize * y },
          textureItem.getDescription().size(), Sdk::Vector4F::identity() });

      d_itemSprites.emplace_back(Dx::Sprite{
        nullptr, { CornerSize + SlotSize * x + 4, CornerSize + SlotSize * y + 4 },
          textureItem.getDescription().size(), Sdk::Vector4F::identity() });

      d_itemOffsets.emplace_back(Sdk::Vector2I{ 0, 0 });

      updateItemSprite(x + y * d_slotsHor);
    }
  }*/
}
