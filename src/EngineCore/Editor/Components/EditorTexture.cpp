#include <UWUEngine/Editor/Components/EditorTexture.h>
#include <UWUEngine/Component/TextureComponentManager.h>
#include <imgui.h>

Editors::Texture::Texture(const std::string& name):
Component(name), texture_("./assets/DigiPen_RED_1024px.png")
{
}

Editors::Texture::~Texture()
= default;

void Editors::Texture::CheckActive(EntityID id)
{
  isActive = TextureComponentManager::IsActive(id);
}

void Editors::Texture::UpdateComponent(EntityID id)
{
  uv = &TextureComponentManager::uvs_[id];
  color = &TextureComponentManager::colors_[id];

  path = TextureComponentManager::getFilePath(id);
  texture_ = SingleTexture(path.c_str());
}

void Editors::Texture::UpdateUI()
{
  ImGui::DragFloat2("uv", &uv->x, 0.01);
  ImGui::ColorEdit4("color", &color->x);
  ImGui::Text(path.c_str());

  float windowWidth = ImGui::GetWindowWidth();
  float aspectRatio = texture_.height / texture_.width;
  ImGui::Image((void*)(intptr_t)texture_.id, ImVec2(windowWidth, windowWidth * aspectRatio));
}
