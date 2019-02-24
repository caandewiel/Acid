﻿#include "OverlayDebug.hpp"

#include <Maths/Visual/DriverConstant.hpp>
#include <Scenes/Scenes.hpp>
#include <Guis/Gui.hpp>

namespace test
{
	OverlayDebug::OverlayDebug(UiObject *parent) :
		UiObject(parent, UiBound::Screen),
		m_textFrameTime(CreateStatus("Frame Time: 0ms", 0.998f, 0.998f, Text::Justify::Left)),
		m_textFps(CreateStatus("FPS: 0", 0.998f, 0.978f, Text::Justify::Left)),
		m_textUps(CreateStatus("UPS: 0", 0.998f, 0.958f, Text::Justify::Left))
	{
	}

	void OverlayDebug::UpdateObject()
	{
		m_textFrameTime->SetString("Frame Time: " + String::To(1000.0f / Engine::Get()->GetFps()) + "ms");
		m_textFps->SetString("FPS: " + String::To(Engine::Get()->GetFps()));
		m_textUps->SetString("UPS: " + String::To(Engine::Get()->GetUps()));
	}

	std::unique_ptr<Text> OverlayDebug::CreateStatus(const std::string &content, const float &positionX, const float &positionY, const Text::Justify &justify)
	{
		auto result = std::make_unique<Text>(this, UiBound(Vector2(positionX, positionY), UiReference::BottomRight), 1.1f, content, FontType::Create("Fonts/ProximaNova", "Regular"), justify);
		result->SetTextColour(Colour("#ffffff"));
		result->SetBorderColour(Colour("#262626"));
		result->SetBorderDriver<DriverConstant<float>>(0.04f);
		return result;
	}
}