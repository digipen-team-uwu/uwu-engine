/******************************************************************************/
/*!
\par        Project Umbra
\file       EditorHelper.cpp
\author     Yi Qian
\date       2019/12/28
\brief      Editor Helper widgets

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Editor/EditorHelper.h>
#include <imgui.h>

// Helper to display a little (?) mark which shows a tooltip when hovered.
// In your own code you may want to display an actual icon if you are using a merged icon fonts (see docs/FONTS.txt)
void Editors::HelpMarker(const char* desc)
{
  ImGui::TextDisabled("(?)");
  if (ImGui::IsItemHovered())
  {
    ImGui::BeginTooltip();
    ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
    ImGui::TextUnformatted(desc);
    ImGui::PopTextWrapPos();
    ImGui::EndTooltip();
  }
}

struct InputTextCallback_UserData
{
  std::string* Str;
  ImGuiInputTextCallback  ChainCallback;
  void* ChainCallbackUserData;
};

static int InputTextCallback(ImGuiInputTextCallbackData* data)
{
  InputTextCallback_UserData* user_data = (InputTextCallback_UserData*)data->UserData;
  if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
  {
    // Resize string callback
    // If for some reason we refuse the new length (BufTextLen) and/or capacity (BufSize) we need to set them back to what we want.
    std::string* str = user_data->Str;
    IM_ASSERT(data->Buf == str->c_str());
    str->resize(data->BufTextLen);
    data->Buf = (char*)str->c_str();
  }
  else if (user_data->ChainCallback)
  {
    // Forward to user callback, if any
    data->UserData = user_data->ChainCallbackUserData;
    return user_data->ChainCallback(data);
  }
  return 0;
}

bool Editors::InputText(const char* label, std::string* str, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
{
  IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
  flags |= ImGuiInputTextFlags_CallbackResize;

  InputTextCallback_UserData cb_user_data;
  cb_user_data.Str = str;
  cb_user_data.ChainCallback = callback;
  cb_user_data.ChainCallbackUserData = user_data;
  return ImGui::InputText(label, (char*)str->c_str(), str->capacity() + 1, flags, InputTextCallback, &cb_user_data);
}

bool Editors::InputTextMultiline(const char* label, std::string* str, const ImVec2& size, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
{
  IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
  flags |= ImGuiInputTextFlags_CallbackResize;

  InputTextCallback_UserData cb_user_data;
  cb_user_data.Str = str;
  cb_user_data.ChainCallback = callback;
  cb_user_data.ChainCallbackUserData = user_data;
  return ImGui::InputTextMultiline(label, (char*)str->c_str(), str->capacity() + 1, size, flags, InputTextCallback, &cb_user_data);
}

bool Editors::InputTextWithHint(const char* label, const char* hint, std::string* str, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
{
  IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
  flags |= ImGuiInputTextFlags_CallbackResize;

  InputTextCallback_UserData cb_user_data;
  cb_user_data.Str = str;
  cb_user_data.ChainCallback = callback;
  cb_user_data.ChainCallbackUserData = user_data;
  return ImGui::InputTextWithHint(label, hint, (char*)str->c_str(), str->capacity() + 1, flags, InputTextCallback, &cb_user_data);
}

