#include "visuals.h"
#include "..\imgui_ex.h"
#include "..\..\..\globals.h"
#include "..\..\..\config\config.h"

#include "..\..\..\features\features.h"
#include "..\..\Lua\Clua.h"
struct Flags
{
	std::string m_text;

	Color m_color;
	Flags(std::string text, Color color) {
		m_text = text;

		m_color = color;
	}
	Flags(std::string text, float* color) {
		m_text = text;

		m_color = Color(color);
	}
};
namespace core::tabs::visuals
{
	/* enemies tab */

	void enemies_first_tab()
	{
		
		ImGui::SetCursorPosX(0.0f);
		auto cursor_pos = ImGui::GetCursorScreenPos();

	

		const ImGuiID nIndex = ImGui::GetCurrentWindow()->GetID(crypt_str("##preview.yaw"));
		ImGui::ButtonBehavior(ImRect(cursor_pos, u::dpi(ImVec2(192.0f, 252.0f) + cursor_pos)), nIndex, nullptr, nullptr);
		static float flMin = -FLOAT32_MAX;
		static float flMax = FLOAT32_MAX;





		ImGuiWindow* window = ImGui::GetCurrentWindow();

		if (window != nullptr)
		{
			if (!config->visuals.player_type[ENEMY].esp_enable)
				return;
			if (config->visuals.player_type[ENEMY].esp_box)
			{
				ImVec2 dpi1 = u::dpi(ImVec2(25.0f, 23.0f)),
					dpi2 = u::dpi(ImVec2(175.0f, 270.0f));

				window->DrawList->AddRect(window->Pos + dpi1 - ImVec2(1.0f, 1.0f),
					window->Pos + dpi2 + ImVec2(1.0f, 1.0f), IM_COL32(0, 0, 0, 100 * ImGui::GetStyle().Alpha));

				window->DrawList->AddRect(window->Pos + dpi1,
					window->Pos + dpi2, ImGui::ColorConvertFloat4ToU32(ImVec4(
						config->visuals.player_type[ENEMY].esp_box_clr[0],
						config->visuals.player_type[ENEMY].esp_box_clr[1],
						config->visuals.player_type[ENEMY].esp_box_clr[2],
						config->visuals.player_type[ENEMY].esp_box_clr[3] * ImGui::GetStyle().Alpha
					)));

				window->DrawList->AddRect(window->Pos + dpi1 + ImVec2(1.0f, 1.0f),
					window->Pos + dpi2 - ImVec2(1.0f, 1.0f), IM_COL32(0, 0, 0, 100 * ImGui::GetStyle().Alpha));
			}
			if (config->visuals.player_type[ENEMY].esp_name)
			{

				ImVec2 dpi = u::dpi(ImVec2(175.0f, 8.0f));


				ImVec2 name = ImGui::CalcTextSize(f::dinpro_l, u::dpi(14.0f), ctx->username.c_str());
				dpi.x = dpi.x / 2 - name.x / 3.5f;
				window->DrawList->AddText(f::esp_font, u::dpi(14.0f), window->Pos +
					dpi + ImVec2(0.0f, 0.5f),
					IM_COL32(86, 86, 86, (int)(255.0f * config->visuals.player_type[ENEMY].esp_name_clr[3] * ImGui::GetStyle().Alpha)),
					ctx->username.c_str());
				window->DrawList->AddText(f::esp_font, u::dpi(14.0f), window->Pos +
					dpi, ImGui::ColorConvertFloat4ToU32(ImVec4(
						config->visuals.player_type[ENEMY].esp_name_clr[0],
						config->visuals.player_type[ENEMY].esp_name_clr[1],
						config->visuals.player_type[ENEMY].esp_name_clr[2],
						config->visuals.player_type[ENEMY].esp_name_clr[3] * ImGui::GetStyle().Alpha
					)), ctx->username.c_str());



			}


			if (config->visuals.player_type[ENEMY].esp_weapon)
			{
				ImVec2 dpi = u::dpi(ImVec2(175.0f, 278.0f));
				float offset = 0.0f;;
				if (config->visuals.player_type[ENEMY].esp_weapon_arr[0])
				{
					offset += u::dpi(28.0f) / 2;
					ImVec2 weapon_icon = ImGui::CalcTextSize(f::weapon_icons, u::dpi(16.0f), crypt_str("Y"));
					dpi.x = dpi.x / 2 - weapon_icon.x / 8;
					window->DrawList->AddText(f::weapon_icons, u::dpi(16.0f), window->Pos +
						dpi + ImVec2(0.0f, 0.5f),
						IM_COL32(86, 86, 86, (int)(255.0f * config->visuals.player_type[ENEMY].esp_weapon_clr[3] * ImGui::GetStyle().Alpha)),
						crypt_str("Y"));
					window->DrawList->AddText(f::weapon_icons, u::dpi(16.0f), window->Pos +
						dpi, ImGui::ColorConvertFloat4ToU32(ImVec4(
							config->visuals.player_type[ENEMY].esp_weapon_clr[0],
							config->visuals.player_type[ENEMY].esp_weapon_clr[1],
							config->visuals.player_type[ENEMY].esp_weapon_clr[2],
							config->visuals.player_type[ENEMY].esp_weapon_clr[3] * ImGui::GetStyle().Alpha
						)), crypt_str("Y"));

				}if (config->visuals.player_type[ENEMY].esp_weapon_arr[1])
				{
					ImVec2 dpi = u::dpi(ImVec2(175.0f, 278.0f));
					dpi.y += offset;

					ImVec2 weapon_icon = ImGui::CalcTextSize(f::dinpro_l, u::dpi(14.0f), crypt_str("SCAR-20"));
					dpi.x = dpi.x / 2 - weapon_icon.x / 8.5f;
					window->DrawList->AddText(f::esp_font, u::dpi(14.0f), window->Pos +
						dpi + ImVec2(0.0f, 0.5f),
						IM_COL32(86, 86, 86, (int)(255.0f * config->visuals.player_type[ENEMY].esp_weapon_clr[3] * ImGui::GetStyle().Alpha)),
						crypt_str("SCAR-20"));
					window->DrawList->AddText(f::esp_font, u::dpi(14.0f), window->Pos +
						dpi, ImGui::ColorConvertFloat4ToU32(ImVec4(
							config->visuals.player_type[ENEMY].esp_weapon_clr[0],
							config->visuals.player_type[ENEMY].esp_weapon_clr[1],
							config->visuals.player_type[ENEMY].esp_weapon_clr[2],
							config->visuals.player_type[ENEMY].esp_weapon_clr[3] * ImGui::GetStyle().Alpha
						)), crypt_str("SCAR-20"));
				}
			}

			if (config->visuals.player_type[ENEMY].esp_hp_bar)
			{
				ImVec2 dpi1 = u::dpi(ImVec2(20.0f, 23.0f)),
					dpi2 = u::dpi(ImVec2(21.0f, 270.0f));

				window->DrawList->AddRectFilled(window->Pos + dpi1 - ImVec2(1.0f, 1.0f),
					window->Pos + dpi2 + ImVec2(1.0f, 1.0f), IM_COL32(0, 0, 0, 100 * ImGui::GetStyle().Alpha));


				ImU32 clr = config->visuals.player_type[ENEMY].esp_hp_bar_custom_color ? ImGui::ColorConvertFloat4ToU32(ImVec4(
					config->visuals.player_type[ENEMY].esp_hp_bar_color[0],
					config->visuals.player_type[ENEMY].esp_hp_bar_color[1],
					config->visuals.player_type[ENEMY].esp_hp_bar_color[2],
					config->visuals.player_type[ENEMY].esp_hp_bar_color[3] * ImGui::GetStyle().Alpha
				)) : IM_COL32(0, 255, 0, (int)(255.0f * ImGui::GetStyle().Alpha));

				window->DrawList->AddRectFilled(window->Pos + dpi1,
					window->Pos + dpi2, clr);
			}

			if (config->visuals.player_type[ENEMY].esp_ammo)
			{
				ImVec2 dpi1 = u::dpi(ImVec2(25.0f, 273.0f)),
					dpi2 = u::dpi(ImVec2(175.0f, 274.0f));

				window->DrawList->AddRectFilled(window->Pos + dpi1 - ImVec2(1.0f, 1.0f),
					window->Pos + dpi2 + ImVec2(1.0f, 1.0f), IM_COL32(112, 112, 112, 150 * ImGui::GetStyle().Alpha));

				window->DrawList->AddRectFilled(window->Pos + dpi1,
					window->Pos + dpi2, ImGui::ColorConvertFloat4ToU32(ImVec4(
						config->visuals.player_type[ENEMY].esp_ammo_clr[0],
						config->visuals.player_type[ENEMY].esp_ammo_clr[1],
						config->visuals.player_type[ENEMY].esp_ammo_clr[2],
						config->visuals.player_type[ENEMY].esp_ammo_clr[3] * ImGui::GetStyle().Alpha
					)));
			}


			if (config->visuals.player_type[ENEMY].esp_flags)
			{
				std::vector < Flags	> m_flags;

				if (config->visuals.player_type[ENEMY].esp_flags_arr[FLAGS_HELMET])
				{
					m_flags.push_back(Flags(crypt_str("HK"), config->visuals.player_type[ENEMY].esp_flags_combo_clr[FLAGS_HELMET]));
				}

				if (config->visuals.player_type[ENEMY].esp_flags_arr[FLAGS_MONEY])
				{
					m_flags.push_back(Flags(crypt_str("16000$"), config->visuals.player_type[ENEMY].esp_flags_combo_clr[FLAGS_MONEY]));
				}

				if (config->visuals.player_type[ENEMY].esp_flags_arr[FLAGS_DEFUSER])
				{
					m_flags.push_back(Flags(crypt_str("KIT"), config->visuals.player_type[ENEMY].esp_flags_combo_clr[FLAGS_DEFUSER]));
				}

				if (config->visuals.player_type[ENEMY].esp_flags_arr[FLAGS_BOMB])
				{
					m_flags.push_back(Flags(crypt_str("BOMB"), config->visuals.player_type[ENEMY].esp_flags_combo_clr[FLAGS_BOMB]));
				}

				if (config->visuals.player_type[ENEMY].esp_flags_arr[FLAGS_RELOAD])
				{
					m_flags.push_back(Flags(crypt_str("RELOAD"), config->visuals.player_type[ENEMY].esp_flags_combo_clr[FLAGS_RELOAD]));
				}

				if (config->visuals.player_type[ENEMY].esp_flags_arr[FLAGS_ZOOM])
				{
					m_flags.push_back(Flags(crypt_str("ZOOM"), config->visuals.player_type[ENEMY].esp_flags_combo_clr[FLAGS_ZOOM]));
				}

				if (config->visuals.player_type[ENEMY].esp_flags_arr[FLAGS_FLASH])
				{
					m_flags.push_back(Flags(crypt_str("FLASH"), config->visuals.player_type[ENEMY].esp_flags_combo_clr[FLAGS_FLASH]));
				}

				if (config->visuals.player_type[ENEMY].esp_flags_arr[FLAGS_DUCK])
				{
					m_flags.push_back(Flags(crypt_str("FD"), config->visuals.player_type[ENEMY].esp_flags_combo_clr[FLAGS_DUCK]));
				}

				if (config->visuals.player_type[ENEMY].esp_flags_arr[FLAGS_EXPLOIT])
				{
					m_flags.push_back(Flags(crypt_str("EXPLOIT"), config->visuals.player_type[ENEMY].esp_flags_combo_clr[FLAGS_EXPLOIT]));
				}

				if (config->visuals.player_type[ENEMY].esp_flags_arr[FLAGS_PLANT])
				{
					m_flags.push_back(Flags(crypt_str("PLANT"), config->visuals.player_type[ENEMY].esp_flags_combo_clr[FLAGS_PLANT]));
				}

				if (config->visuals.player_type[ENEMY].esp_flags_arr[FLAGS_DEFUSE])
				{
					m_flags.push_back(Flags(crypt_str("DEFUSE"), config->visuals.player_type[ENEMY].esp_flags_combo_clr[FLAGS_DEFUSE]));
				}

				if (config->visuals.player_type[ENEMY].esp_flags_arr[FLAGS_IGNORE])
				{
					m_flags.push_back(Flags(crypt_str("IGNORE"), config->visuals.player_type[ENEMY].esp_flags_combo_clr[FLAGS_IGNORE]));
				}

				float offset = 19.0f;
				static ImU32 clr_flags;
				for (auto& flag : m_flags)
				{
					ImVec2 dpi = u::dpi(ImVec2(180.0f, offset));


					clr_flags = ImGui::ColorConvertFloat4ToU32(ImVec4(
						(float)flag.m_color.r() / 255.0f,
						(float)flag.m_color.g() / 255.0f,
						(float)flag.m_color.b() / 255.0f,
						(float)flag.m_color.a() / 255.0f * ImGui::GetStyle().Alpha
					));

					window->DrawList->AddText(f::esp_font, u::dpi(12.0f), window->Pos +
						dpi + ImVec2(0.0f, 0.5f), IM_COL32(86, 86, 86, (int)(255.0f * flag.m_color.a() / 255.0f * ImGui::GetStyle().Alpha)), flag.m_text.c_str());
					window->DrawList->AddText(f::esp_font, u::dpi(12.0f), window->Pos +
						dpi, clr_flags, flag.m_text.c_str());
					offset += u::dpi(10.0f);
				}
				m_flags.clear();
			}
		}
	}

	void enemies_second_tab()
	{
		std::vector <const char*>chams_type = { "Regular","Flat" };
		const char* chams_modifiers[] = { "Glass","Glow","Wireframe" };
	/*	for (auto& mat : Lua_manager->materials)
		{
			chams_type.push_back(mat.m_name.c_str());
		}*/
		imgui_ex::checkbox(crypt_str("Chams"), &config->visuals.player_type[ENEMY].chams_enable);
		if (config->visuals.player_type[ENEMY].chams_enable) {

			imgui_ex::checkbox(crypt_str("Visible chams"), &config->visuals.player_type[ENEMY].chams_visible);
			if (config->visuals.player_type[ENEMY].chams_visible) {
				imgui_ex::color_edit4(crypt_str("##chams_clr_visible"), config->visuals.player_type[ENEMY].chams_clr_visible);
				if (config->visuals.player_type[ENEMY].chams_type_visible >= chams_type.size())
				{
					config->visuals.player_type[ENEMY].chams_type_visible = 0;
				}
				imgui_ex::combo(crypt_str("##chams_visible"), &config->visuals.player_type[ENEMY].chams_type_visible,
					&chams_type[0], chams_type.size());
				imgui_ex::checkbox(crypt_str("Chams visible modifer"), &config->visuals.player_type[ENEMY].chams_modifiers_visible);
				if (config->visuals.player_type[ENEMY].chams_modifiers_visible)
				{
					imgui_ex::mcombo_clr(crypt_str("##chams_visible_modifers"), config->visuals.player_type[ENEMY].chams_modifiers_arr_visible.data(), config->visuals.player_type[ENEMY].chams_modifiers_clr_visible,
						chams_modifiers, IM_ARRAYSIZE(chams_modifiers));
				}

			}
			{
				imgui_ex::checkbox(crypt_str("Invisible chams"), &config->visuals.player_type[ENEMY].chams_invisible);
				if (config->visuals.player_type[ENEMY].chams_invisible) {
					imgui_ex::color_edit4(crypt_str("##chams_clr_invisible"), config->visuals.player_type[ENEMY].chams_clr_invisible);
					if (config->visuals.player_type[ENEMY].chams_type_invisible >= chams_type.size())
					{
						config->visuals.player_type[ENEMY].chams_type_invisible = 0;
					}
					imgui_ex::combo(crypt_str("##chams_invisible"), &config->visuals.player_type[ENEMY].chams_type_invisible,
						&chams_type[0], chams_type.size());
					imgui_ex::checkbox(crypt_str("Chams invisible modifer"), &config->visuals.player_type[ENEMY].chams_modifiers_invisible);
					if (config->visuals.player_type[ENEMY].chams_modifiers_invisible)
					{
						imgui_ex::mcombo_clr(crypt_str("##chams_invisible_modifers"), config->visuals.player_type[ENEMY].chams_modifiers_arr_invisible.data(), config->visuals.player_type[ENEMY].chams_modifiers_clr_invisible,
							chams_modifiers, IM_ARRAYSIZE(chams_modifiers));
					}
				}
			}
			if (config->visuals.player_type[ENEMY].chams_visible)
			{
				imgui_ex::checkbox(crypt_str("Ragdoll"), &config->visuals.player_type[ENEMY].chams_ragdoll);
			}

			imgui_ex::checkbox(crypt_str("On shot chams"), &config->visuals.player_type[ENEMY].chams_shot);
			if (config->visuals.player_type[ENEMY].chams_shot)
			{
				imgui_ex::color_edit4(crypt_str("##chams_clr_shot"), config->visuals.player_type[ENEMY].chams_shot_clr);
				if (config->visuals.player_type[ENEMY].chams_shot_type >= chams_type.size())
				{
					config->visuals.player_type[ENEMY].chams_shot_type = 0;
				}
				imgui_ex::combo(crypt_str("##chams_shot"), &config->visuals.player_type[ENEMY].chams_shot_type,
					&chams_type[0], chams_type.size());
				imgui_ex::checkbox(crypt_str("On shot chams modifers"), &config->visuals.player_type[ENEMY].chams_shot_modifiers);
				if (config->visuals.player_type[ENEMY].chams_shot_modifiers)
				{
					imgui_ex::mcombo_clr(crypt_str("##chams_shot_modifers"), config->visuals.player_type[ENEMY].chams_shot_modifiers_arr.data(), config->visuals.player_type[ENEMY].chams_shot_modifiers_clr,
						chams_modifiers, IM_ARRAYSIZE(chams_modifiers));
				}
			}
			imgui_ex::checkbox(crypt_str("Backtrack chams"), &config->visuals.player_type[ENEMY].chams_ghost);
			if (config->visuals.player_type[ENEMY].chams_ghost)
			{
				imgui_ex::color_edit4(crypt_str("##chams_clr_ghost"), config->visuals.player_type[ENEMY].chams_ghost_clr);
				if (config->visuals.player_type[ENEMY].chams_ghost_type >= chams_type.size())
				{
					config->visuals.player_type[ENEMY].chams_ghost_type = 0;
				}
				imgui_ex::combo(crypt_str("##chams_ghost"), &config->visuals.player_type[ENEMY].chams_ghost_type,
					&chams_type[0], chams_type.size());
				imgui_ex::checkbox(crypt_str("Backtrack chams modifers"), &config->visuals.player_type[ENEMY].chams_ghost_modifiers);
				if (config->visuals.player_type[ENEMY].chams_ghost_modifiers)
				{
					imgui_ex::mcombo_clr(crypt_str("##chams_ghost_modifers"), config->visuals.player_type[ENEMY].chams_ghost_modifiers_arr.data(), config->visuals.player_type[ENEMY].chams_ghost_modifiers_clr,
						chams_modifiers, IM_ARRAYSIZE(chams_modifiers));
				}

			}


		}
		const char* glow_types[] = { "Outline", "Cover", "Thin" };
		imgui_ex::checkbox(crypt_str("Glow"), &config->visuals.player_type[ENEMY].glow_enable);

		if (config->visuals.player_type[ENEMY].glow_enable)
		{
			imgui_ex::color_edit4(crypt_str("##glow_clr"), config->visuals.player_type[ENEMY].glow_clr);

			imgui_ex::combo(crypt_str("##glow"), &config->visuals.player_type[ENEMY].glow_type,
				glow_types, IM_ARRAYSIZE(glow_types));
		}

		ImGui::Spacing();
	}

	void enemies_third_tab()
	{
		imgui_ex::checkbox(crypt_str("Enable ESP"), &config->visuals.player_type[ENEMY].esp_enable);

		imgui_ex::checkbox(crypt_str("Box"), &config->visuals.player_type[ENEMY].esp_box);
		imgui_ex::color_edit4(crypt_str("##box_clr"), config->visuals.player_type[ENEMY].esp_box_clr);

		imgui_ex::checkbox(crypt_str("Name"), &config->visuals.player_type[ENEMY].esp_name);
		imgui_ex::color_edit4(crypt_str("##name_clr"), config->visuals.player_type[ENEMY].esp_name_clr);

		imgui_ex::checkbox(crypt_str("Health bar"), &config->visuals.player_type[ENEMY].esp_hp_bar);

		if (config->visuals.player_type[ENEMY].esp_hp_bar)
		{
			imgui_ex::checkbox(crypt_str("Color"), &config->visuals.player_type[ENEMY].esp_hp_bar_custom_color);
			imgui_ex::color_edit4(crypt_str("##bar_clr"), config->visuals.player_type[ENEMY].esp_hp_bar_color);
		}

		imgui_ex::checkbox(crypt_str("Skeleton"), &config->visuals.player_type[ENEMY].esp_skeleton);
		imgui_ex::color_edit4(crypt_str("##skeleton_clr"), config->visuals.player_type[ENEMY].esp_skeleton_clr);

		imgui_ex::checkbox(crypt_str("Flags"), &config->visuals.player_type[ENEMY].esp_flags);
		const char* esp_flags_combo[] = {
				"Helmet", "Money" ,"Defuser",
				"Bomb/Hostage", "Reload", "Zoom","Flash", "Fake duck","Exploit", "Plant", "Defuse", "Ignore"
		};
		if (config->visuals.player_type[ENEMY].esp_flags) {
			imgui_ex::mcombo_clr(crypt_str("##flags"), config->visuals.player_type[ENEMY].esp_flags_arr.data(), config->visuals.player_type[ENEMY].esp_flags_combo_clr,
				esp_flags_combo, IM_ARRAYSIZE(esp_flags_combo));
		}

		imgui_ex::checkbox(crypt_str("Weapon"), &config->visuals.player_type[ENEMY].esp_weapon);
		if (config->visuals.player_type[ENEMY].esp_weapon) {
			imgui_ex::color_edit4(crypt_str("##weapon_clr"), config->visuals.player_type[ENEMY].esp_weapon_clr);
			const char* esp_weapon_combo[2] = { "Icon", "Text" };
			imgui_ex::mcombo(crypt_str("##weapon"), config->visuals.player_type[ENEMY].esp_weapon_arr.data(),
				esp_weapon_combo, IM_ARRAYSIZE(esp_weapon_combo));
			imgui_ex::text(crypt_str("Knife/Taser color"));
			imgui_ex::color_edit4(crypt_str("##knife_taser_clr"), config->visuals.player_type[ENEMY].esp_knife_taser_clr);
		}

		imgui_ex::checkbox(crypt_str("Ammo"), &config->visuals.player_type[ENEMY].esp_ammo);
		if (config->visuals.player_type[ENEMY].esp_ammo)
			imgui_ex::color_edit4(crypt_str("##ammo_clr"), config->visuals.player_type[ENEMY].esp_ammo_clr);

		imgui_ex::checkbox(crypt_str("Sounds"), &config->visuals.player_type[ENEMY].sounds);

		if (config->visuals.player_type[ENEMY].sounds)
		{
			imgui_ex::color_edit4(crypt_str("##sounds_color"), config->visuals.player_type[ENEMY].sounds_color);
			imgui_ex::slider_float(crypt_str("Time"), &config->visuals.player_type[ENEMY].sounds_time, 0.1f, 5.0f, crypt_str("%.1f s"));
			imgui_ex::slider_int(crypt_str("Radius"), &config->visuals.player_type[ENEMY].sounds_radius, 1, 100);
		}
#ifdef BETA
		imgui_ex::checkbox(crypt_str("Multipoints"), &config->visuals.player_type[ENEMY].multipoints);
#endif
	}

	/* local tab */

	void local_first_tab()
	{
		
		ImGui::SetCursorPosX(0.0f);
		auto cursor_pos = ImGui::GetCursorScreenPos();



		const ImGuiID nIndex = ImGui::GetCurrentWindow()->GetID(crypt_str("##preview.yaw"));
		ImGui::ButtonBehavior(ImRect(cursor_pos, u::dpi(ImVec2(192.0f, 252.0f) + cursor_pos)), nIndex, nullptr, nullptr);
		static float flMin = -FLOAT32_MAX;
		static float flMax = FLOAT32_MAX;

	
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		if (window != nullptr)
		{
			if (!config->visuals.player_type[LOCAL].esp_enable)
				return;
			if (config->visuals.player_type[LOCAL].esp_box)
			{
				ImVec2 dpi1 = u::dpi(ImVec2(25.0f, 23.0f)),
					dpi2 = u::dpi(ImVec2(175.0f, 270.0f));

				window->DrawList->AddRect(window->Pos + dpi1 - ImVec2(1.0f, 1.0f),
					window->Pos + dpi2 + ImVec2(1.0f, 1.0f), IM_COL32(0, 0, 0, 100 * ImGui::GetStyle().Alpha));

				window->DrawList->AddRect(window->Pos + dpi1,
					window->Pos + dpi2, ImGui::ColorConvertFloat4ToU32(ImVec4(
						config->visuals.player_type[LOCAL].esp_box_clr[0],
						config->visuals.player_type[LOCAL].esp_box_clr[1],
						config->visuals.player_type[LOCAL].esp_box_clr[2],
						config->visuals.player_type[LOCAL].esp_box_clr[3] * ImGui::GetStyle().Alpha
					)));

				window->DrawList->AddRect(window->Pos + dpi1 + ImVec2(1.0f, 1.0f),
					window->Pos + dpi2 - ImVec2(1.0f, 1.0f), IM_COL32(0, 0, 0, 100 * ImGui::GetStyle().Alpha));
			}
			if (config->visuals.player_type[LOCAL].esp_name)
			{

				ImVec2 dpi = u::dpi(ImVec2(175.0f, 8.0f));


				ImVec2 name = ImGui::CalcTextSize(f::dinpro_l, u::dpi(14.0f), ctx->username.c_str());
				dpi.x = dpi.x / 2 - name.x / 3.5f;
				window->DrawList->AddText(f::esp_font, u::dpi(14.0f), window->Pos +
					dpi + ImVec2(0.0f, 0.5f),
					IM_COL32(86, 86, 86, (int)(255.0f * config->visuals.player_type[LOCAL].esp_name_clr[3] * ImGui::GetStyle().Alpha)),
					ctx->username.c_str());
				window->DrawList->AddText(f::esp_font, u::dpi(14.0f), window->Pos +
					dpi, ImGui::ColorConvertFloat4ToU32(ImVec4(
						config->visuals.player_type[LOCAL].esp_name_clr[0],
						config->visuals.player_type[LOCAL].esp_name_clr[1],
						config->visuals.player_type[LOCAL].esp_name_clr[2],
						config->visuals.player_type[LOCAL].esp_name_clr[3] * ImGui::GetStyle().Alpha
					)), ctx->username.c_str());



			}


			if (config->visuals.player_type[LOCAL].esp_weapon)
			{
				ImVec2 dpi = u::dpi(ImVec2(175.0f, 278.0f));
				float offset = 0.0f;;
				if (config->visuals.player_type[LOCAL].esp_weapon_arr[0])
				{
					offset += u::dpi(28.0f) / 2;
					ImVec2 weapon_icon = ImGui::CalcTextSize(f::weapon_icons, u::dpi(16.0f), crypt_str("Y"));
					dpi.x = dpi.x / 2 - weapon_icon.x / 8;
					window->DrawList->AddText(f::weapon_icons, u::dpi(16.0f), window->Pos +
						dpi + ImVec2(0.0f, 0.5f),
						IM_COL32(86, 86, 86, (int)(255.0f * config->visuals.player_type[LOCAL].esp_weapon_clr[3] * ImGui::GetStyle().Alpha)),
						crypt_str("Y"));
					window->DrawList->AddText(f::weapon_icons, u::dpi(16.0f), window->Pos +
						dpi, ImGui::ColorConvertFloat4ToU32(ImVec4(
							config->visuals.player_type[LOCAL].esp_weapon_clr[0],
							config->visuals.player_type[LOCAL].esp_weapon_clr[1],
							config->visuals.player_type[LOCAL].esp_weapon_clr[2],
							config->visuals.player_type[LOCAL].esp_weapon_clr[3] * ImGui::GetStyle().Alpha
						)), crypt_str("Y"));

				}if (config->visuals.player_type[LOCAL].esp_weapon_arr[1])
				{
					ImVec2 dpi = u::dpi(ImVec2(175.0f, 278.0f));
					dpi.y += offset;

					ImVec2 weapon_icon = ImGui::CalcTextSize(f::dinpro_l, u::dpi(14.0f), crypt_str("SCAR-20"));
					dpi.x = dpi.x / 2 - weapon_icon.x / 8.5f;
					window->DrawList->AddText(f::esp_font, u::dpi(14.0f), window->Pos +
						dpi + ImVec2(0.0f, 0.5f),
						IM_COL32(86, 86, 86, (int)(255.0f * config->visuals.player_type[LOCAL].esp_weapon_clr[3] * ImGui::GetStyle().Alpha)),
						crypt_str("SCAR-20"));
					window->DrawList->AddText(f::esp_font, u::dpi(14.0f), window->Pos +
						dpi, ImGui::ColorConvertFloat4ToU32(ImVec4(
							config->visuals.player_type[LOCAL].esp_weapon_clr[0],
							config->visuals.player_type[LOCAL].esp_weapon_clr[1],
							config->visuals.player_type[LOCAL].esp_weapon_clr[2],
							config->visuals.player_type[LOCAL].esp_weapon_clr[3] * ImGui::GetStyle().Alpha
						)), crypt_str("SCAR-20"));
				}
			}

			if (config->visuals.player_type[LOCAL].esp_hp_bar)
			{
				ImVec2 dpi1 = u::dpi(ImVec2(20.0f, 23.0f)),
					dpi2 = u::dpi(ImVec2(21.0f, 270.0f));

				window->DrawList->AddRectFilled(window->Pos + dpi1 - ImVec2(1.0f, 1.0f),
					window->Pos + dpi2 + ImVec2(1.0f, 1.0f), IM_COL32(0, 0, 0, 100 * ImGui::GetStyle().Alpha));


				ImU32 clr = config->visuals.player_type[LOCAL].esp_hp_bar_custom_color ? ImGui::ColorConvertFloat4ToU32(ImVec4(
					config->visuals.player_type[LOCAL].esp_hp_bar_color[0],
					config->visuals.player_type[LOCAL].esp_hp_bar_color[1],
					config->visuals.player_type[LOCAL].esp_hp_bar_color[2],
					config->visuals.player_type[LOCAL].esp_hp_bar_color[3] * ImGui::GetStyle().Alpha
				)) : IM_COL32(0, 255, 0, (int)(255.0f * ImGui::GetStyle().Alpha));

				window->DrawList->AddRectFilled(window->Pos + dpi1,
					window->Pos + dpi2, clr);
			}

			if (config->visuals.player_type[LOCAL].esp_ammo)
			{
				ImVec2 dpi1 = u::dpi(ImVec2(25.0f, 273.0f)),
					dpi2 = u::dpi(ImVec2(175.0f, 274.0f));

				window->DrawList->AddRectFilled(window->Pos + dpi1 - ImVec2(1.0f, 1.0f),
					window->Pos + dpi2 + ImVec2(1.0f, 1.0f), IM_COL32(112, 112, 112, 150 * ImGui::GetStyle().Alpha));

				window->DrawList->AddRectFilled(window->Pos + dpi1,
					window->Pos + dpi2, ImGui::ColorConvertFloat4ToU32(ImVec4(
						config->visuals.player_type[LOCAL].esp_ammo_clr[0],
						config->visuals.player_type[LOCAL].esp_ammo_clr[1],
						config->visuals.player_type[LOCAL].esp_ammo_clr[2],
						config->visuals.player_type[LOCAL].esp_ammo_clr[3] * ImGui::GetStyle().Alpha
					)));
			}


			if (config->visuals.player_type[LOCAL].esp_flags)
			{
				std::vector < Flags	> m_flags;

				if (config->visuals.player_type[LOCAL].esp_flags_arr[FLAGS_HELMET])
				{
					m_flags.push_back(Flags(crypt_str("HK"), config->visuals.player_type[LOCAL].esp_flags_combo_clr[FLAGS_HELMET]));
				}

				if (config->visuals.player_type[LOCAL].esp_flags_arr[FLAGS_MONEY])
				{
					m_flags.push_back(Flags(crypt_str("16000$"), config->visuals.player_type[LOCAL].esp_flags_combo_clr[FLAGS_MONEY]));
				}

				if (config->visuals.player_type[LOCAL].esp_flags_arr[FLAGS_DEFUSER])
				{
					m_flags.push_back(Flags(crypt_str("KIT"), config->visuals.player_type[LOCAL].esp_flags_combo_clr[FLAGS_DEFUSER]));
				}

				if (config->visuals.player_type[LOCAL].esp_flags_arr[FLAGS_BOMB])
				{
					m_flags.push_back(Flags(crypt_str("BOMB"), config->visuals.player_type[LOCAL].esp_flags_combo_clr[FLAGS_BOMB]));
				}

				if (config->visuals.player_type[LOCAL].esp_flags_arr[FLAGS_RELOAD])
				{
					m_flags.push_back(Flags(crypt_str("RELOAD"), config->visuals.player_type[LOCAL].esp_flags_combo_clr[FLAGS_RELOAD]));
				}

				if (config->visuals.player_type[LOCAL].esp_flags_arr[FLAGS_ZOOM])
				{
					m_flags.push_back(Flags(crypt_str("ZOOM"), config->visuals.player_type[LOCAL].esp_flags_combo_clr[FLAGS_ZOOM]));
				}

				if (config->visuals.player_type[LOCAL].esp_flags_arr[FLAGS_FLASH])
				{
					m_flags.push_back(Flags(crypt_str("FLASH"), config->visuals.player_type[LOCAL].esp_flags_combo_clr[FLAGS_FLASH]));
				}

				if (config->visuals.player_type[LOCAL].esp_flags_arr[FLAGS_DUCK])
				{
					m_flags.push_back(Flags(crypt_str("FD"), config->visuals.player_type[LOCAL].esp_flags_combo_clr[FLAGS_DUCK]));
				}

				if (config->visuals.player_type[LOCAL].esp_flags_arr[FLAGS_EXPLOIT])
				{
					m_flags.push_back(Flags(crypt_str("EXPLOIT"), config->visuals.player_type[LOCAL].esp_flags_combo_clr[FLAGS_EXPLOIT]));
				}

				if (config->visuals.player_type[ENEMY].esp_flags_arr[FLAGS_PLANT])
				{
					m_flags.push_back(Flags(crypt_str("PLANT"), config->visuals.player_type[ENEMY].esp_flags_combo_clr[FLAGS_PLANT]));
				}

				if (config->visuals.player_type[ENEMY].esp_flags_arr[FLAGS_DEFUSE])
				{
					m_flags.push_back(Flags(crypt_str("DEFUSE"), config->visuals.player_type[ENEMY].esp_flags_combo_clr[FLAGS_DEFUSE]));
				}

				float offset = 19.0f;
				static ImU32 clr_flags;
				for (auto flag : m_flags)
				{
					ImVec2 dpi = u::dpi(ImVec2(180.0f, offset));

					clr_flags = ImGui::ColorConvertFloat4ToU32(ImVec4(
						(float)flag.m_color.r() / 255.0f,
						(float)flag.m_color.g() / 255.0f,
						(float)flag.m_color.b() / 255.0f,
						(float)flag.m_color.a() / 255.0f * ImGui::GetStyle().Alpha
					));

					window->DrawList->AddText(f::esp_font, u::dpi(12.0f), window->Pos +
						dpi + ImVec2(0.0f, 0.5f), IM_COL32(86, 86, 86, (int)(255.0f * flag.m_color.a() / 255.0f * ImGui::GetStyle().Alpha)), flag.m_text.c_str());
					window->DrawList->AddText(f::esp_font, u::dpi(12.0f), window->Pos +
						dpi, clr_flags, flag.m_text.c_str());
					offset += u::dpi(10.0f);
				}
				m_flags.clear();
			}
		}
	}

	void local_second_tab()
	{
		std::vector <const char*>chams_type = { "Regular","Flat" };
		const char* chams_modifiers[] = { "Glass","Glow","Wireframe" };

	/*	for (auto& mat : Lua_manager->materials)
			chams_type.push_back(mat.m_name.c_str());*/

		imgui_ex::slider_int(crypt_str("Transparency in scope"), &config->visuals.player_type[LOCAL].transparency_in_scope, 0, 100, 0, crypt_str("%d%%"));
		imgui_ex::checkbox(crypt_str("Chams"), &config->visuals.player_type[LOCAL].chams_enable);

		if (config->visuals.player_type[LOCAL].chams_enable) {

			imgui_ex::checkbox(crypt_str("Visible chams"), &config->visuals.player_type[LOCAL].chams_visible);
			if (config->visuals.player_type[LOCAL].chams_visible) {
				imgui_ex::color_edit4(crypt_str("##chams_clr_visible"), config->visuals.player_type[LOCAL].chams_clr_visible);
				if (config->visuals.player_type[LOCAL].chams_type_visible >= chams_type.size())
				{
					config->visuals.player_type[LOCAL].chams_type_visible = 0;
				}
				imgui_ex::combo(crypt_str("##chams_visible"), &config->visuals.player_type[LOCAL].chams_type_visible,
					&chams_type[0], chams_type.size());
				imgui_ex::checkbox(crypt_str("Chams visible modifer"), &config->visuals.player_type[LOCAL].chams_modifiers_visible);
				if (config->visuals.player_type[LOCAL].chams_modifiers_visible)
				{
					imgui_ex::mcombo_clr(crypt_str("##chams_visible_modifers"), config->visuals.player_type[LOCAL].chams_modifiers_arr_visible.data(), config->visuals.player_type[LOCAL].chams_modifiers_clr_visible,
						chams_modifiers, IM_ARRAYSIZE(chams_modifiers));
				}

			}

			if (config->visuals.player_type[LOCAL].chams_enable)
			{
				imgui_ex::checkbox(crypt_str("Fake chams"), &config->visuals.player_type[LOCAL].chams_fake);

				if (config->visuals.player_type[LOCAL].chams_fake)
				{
					imgui_ex::color_edit4(crypt_str("##chams_clr_fake"), config->visuals.player_type[LOCAL].chams_fake_clr);
					imgui_ex::checkbox(crypt_str("Layered"), &config->visuals.player_type[LOCAL].layered);
					imgui_ex::checkbox(crypt_str("Visualize lag"), &config->visuals.player_type[LOCAL].visualize_lag);
					if (config->visuals.player_type[LOCAL].chams_fake_type >= chams_type.size())
					{
						config->visuals.player_type[LOCAL].chams_fake_type = 0;
					}
					imgui_ex::combo(crypt_str("##chams_fake"), &config->visuals.player_type[LOCAL].chams_fake_type,
						&chams_type[0], chams_type.size());
					imgui_ex::checkbox(crypt_str("Fake chams modifiers"), &config->visuals.player_type[LOCAL].chams_fake_modifiers);
					if (config->visuals.player_type[LOCAL].chams_fake_modifiers)
					{
						imgui_ex::mcombo_clr(crypt_str("##chams_fake_modifers"), config->visuals.player_type[LOCAL].chams_fake_modifiers_arr.data(), config->visuals.player_type[LOCAL].chams_fake_modifiers_clr,
							chams_modifiers, IM_ARRAYSIZE(chams_modifiers));
					}
				}
			}


		}

		imgui_ex::checkbox(crypt_str("Hand chams"), &config->visuals.player_type[LOCAL].chams_hand);
		if (config->visuals.player_type[LOCAL].chams_hand) {
			imgui_ex::color_edit4(crypt_str("##chams_clr_hand"), config->visuals.player_type[LOCAL].chams_hand_clr);
			if (config->visuals.player_type[LOCAL].chams_hand_type >= chams_type.size())
			{
				config->visuals.player_type[LOCAL].chams_hand_type = 0;
			}
			imgui_ex::combo(crypt_str("##chams_hand"), &config->visuals.player_type[LOCAL].chams_hand_type,
				&chams_type[0], chams_type.size());
			imgui_ex::checkbox(crypt_str("Chams hand modifer"), &config->visuals.player_type[LOCAL].chams_hand_modifiers);
			if (config->visuals.player_type[LOCAL].chams_hand_modifiers)
			{
				imgui_ex::mcombo_clr(crypt_str("##chams_hand_modifers"), config->visuals.player_type[LOCAL].chams_hand_modifiers_arr.data(), config->visuals.player_type[LOCAL].chams_hand_modifiers_clr,
					chams_modifiers, IM_ARRAYSIZE(chams_modifiers));
			}
		}

		imgui_ex::checkbox(crypt_str("Weapon chams"), &config->visuals.player_type[LOCAL].chams_weapon);
		if (config->visuals.player_type[LOCAL].chams_weapon) {
			imgui_ex::color_edit4(crypt_str("##chams_clr_weapon"), config->visuals.player_type[LOCAL].chams_weapon_clr);
			if (config->visuals.player_type[LOCAL].chams_weapon_type >= chams_type.size())
			{
				config->visuals.player_type[LOCAL].chams_weapon_type = 0;
			}
			imgui_ex::combo(crypt_str("##chams_weapon"), &config->visuals.player_type[LOCAL].chams_weapon_type,
				&chams_type[0], chams_type.size());
			imgui_ex::checkbox(crypt_str("Chams weapon modifer"), &config->visuals.player_type[LOCAL].chams_weapon_modifiers);
			if (config->visuals.player_type[LOCAL].chams_weapon_modifiers)
			{
				imgui_ex::mcombo_clr(crypt_str("##chams_weapon_modifers"), config->visuals.player_type[LOCAL].chams_weapon_modifiers_arr.data(), config->visuals.player_type[LOCAL].chams_weapon_modifiers_clr,
					chams_modifiers, IM_ARRAYSIZE(chams_modifiers));
			}
		}

		const char* glow_types[] = { "Outline", "Cover", "Thin" };
		imgui_ex::checkbox(crypt_str("Glow"), &config->visuals.player_type[LOCAL].glow_enable);
		imgui_ex::color_edit4(crypt_str("##glow_clr"), config->visuals.player_type[LOCAL].glow_clr);

		imgui_ex::combo(crypt_str("##glow"), &config->visuals.player_type[LOCAL].glow_type,
			glow_types, IM_ARRAYSIZE(glow_types));

		ImGui::Spacing();
	}

	void local_third_tab()
	{
		imgui_ex::checkbox(crypt_str("Enable ESP"), &config->visuals.player_type[LOCAL].esp_enable);

		imgui_ex::checkbox(crypt_str("Box"), &config->visuals.player_type[LOCAL].esp_box);
		imgui_ex::color_edit4(crypt_str("##box_clr"), config->visuals.player_type[LOCAL].esp_box_clr);

		imgui_ex::checkbox(crypt_str("Name"), &config->visuals.player_type[LOCAL].esp_name);
		imgui_ex::color_edit4(crypt_str("##name_clr"), config->visuals.player_type[LOCAL].esp_name_clr);

		imgui_ex::checkbox(crypt_str("Health bar"), &config->visuals.player_type[LOCAL].esp_hp_bar);

		if (config->visuals.player_type[LOCAL].esp_hp_bar)
		{
			imgui_ex::checkbox(crypt_str("Color"), &config->visuals.player_type[LOCAL].esp_hp_bar_custom_color);
			imgui_ex::color_edit4(crypt_str("##bar_clr"), config->visuals.player_type[LOCAL].esp_hp_bar_color);
		}

		imgui_ex::checkbox(crypt_str("Skeleton"), &config->visuals.player_type[LOCAL].esp_skeleton);
		imgui_ex::color_edit4(crypt_str("##skeleton_clr"), config->visuals.player_type[LOCAL].esp_skeleton_clr);

		imgui_ex::checkbox(crypt_str("Flags"), &config->visuals.player_type[LOCAL].esp_flags);
		const char* esp_flags_combo[] = {
				"Helmet", "Money" ,"Defuser",
				"Bomb/Hostage", "Reload", "Zoom","Flash", "Fake duck","Exploit", "Plant", "Defuse"
		};
		if (config->visuals.player_type[LOCAL].esp_flags) {
			imgui_ex::mcombo_clr(crypt_str("##flags"), config->visuals.player_type[LOCAL].esp_flags_arr.data(), config->visuals.player_type[LOCAL].esp_flags_combo_clr,
				esp_flags_combo, IM_ARRAYSIZE(esp_flags_combo));
		}

		imgui_ex::checkbox(crypt_str("Weapon"), &config->visuals.player_type[LOCAL].esp_weapon);
		if (config->visuals.player_type[LOCAL].esp_weapon) {
			imgui_ex::color_edit4(crypt_str("##weapon_clr"), config->visuals.player_type[LOCAL].esp_weapon_clr);
			const char* esp_weapon_combo[2] = { "Icon", "Text" };
			imgui_ex::mcombo(crypt_str("##weapon"), config->visuals.player_type[LOCAL].esp_weapon_arr.data(),
				esp_weapon_combo, IM_ARRAYSIZE(esp_weapon_combo));
			imgui_ex::text(crypt_str("Knife/Taser color"));
			imgui_ex::color_edit4(crypt_str("##knife_taser_clr"), config->visuals.player_type[LOCAL].esp_knife_taser_clr);
		}

		imgui_ex::checkbox(crypt_str("Ammo"), &config->visuals.player_type[LOCAL].esp_ammo);
		if (config->visuals.player_type[LOCAL].esp_ammo)
			imgui_ex::color_edit4(crypt_str("##ammo_clr"), config->visuals.player_type[LOCAL].esp_ammo_clr);

		imgui_ex::checkbox(crypt_str("Sounds"), &config->visuals.player_type[LOCAL].sounds);

		if (config->visuals.player_type[LOCAL].sounds)
		{
			imgui_ex::color_edit4(crypt_str("##sounds_color"), config->visuals.player_type[LOCAL].sounds_color);
			imgui_ex::slider_float(crypt_str("Time"), &config->visuals.player_type[LOCAL].sounds_time, 0.1f, 5.0f, crypt_str("%.1f s"));
			imgui_ex::slider_int(crypt_str("Radius"), &config->visuals.player_type[LOCAL].sounds_radius, 1, 100);
		}

		const char* agents[]
		{
			crypt_str("Cmdr. Davida 'Goggles' Fernandez | SEAL Frogman"),//1
			crypt_str("Cmdr. Frank 'Wet Sox' Baroud | SEAL Frogman"),//2
			crypt_str("Lieutenant Rex Krikey | SEAL Frogman"),//3
			crypt_str("Michael Syfers | FBI Sniper"),//4
			crypt_str("Operator | FBI SWAT"),//5
			crypt_str("Special Agent Ava | FBI"),//6
			crypt_str("Markus Delrow | FBI HRT"),//7
			crypt_str("Sous-Lieutenant Medic | Gendarmerie Nationale"),//8
			crypt_str("Chem-Haz Capitaine | Gendarmerie Nationale"),//9
			crypt_str("Chef d'Escadron Rouchard | Gendarmerie Nationale"),//10
			crypt_str("Aspirant | Gendarmerie Nationale"),//11
			crypt_str("Officer Jacques Beltram | Gendarmerie Nationale"),//12
			crypt_str("D Squadron Officer | NZSAS"),//13
			crypt_str("B Squadron Officer | SAS"),//14
			crypt_str("Seal Team 6 Soldier | NSWC SEAL"),//15
			crypt_str("Buckshot | NSWC SEAL"),//16
			crypt_str("Lt. Commander Ricksaw | NSWC SEAL"),//17
			crypt_str("'Blueberries' Buckshot | NSWC SEAL"),//18
			crypt_str("3rd Commando Company | KSK"),//19
			crypt_str("'Two Times' McCoy | TACP Cavalry"),//20			
			crypt_str("''Two Times' McCoy | USAF TACP"),//21
			crypt_str("'Primeiro Tenente | Brazilian 1st Battalion"),//22
			crypt_str("'Cmdr. Mae 'Dead Cold' Jamison | SWAT"),//23
			crypt_str("'1st Lieutenant Farlow | SWAT"),//24
			crypt_str("'John 'Van Healen' Kask | SWAT"),//25
			crypt_str("'Bio-Haz Specialist | SWAT"),//26
			crypt_str("'Sergeant Bombson | SWAT"),//27
			crypt_str("'Chem-Haz Specialist | SWAT"),//28
			crypt_str("'Lieutenant 'Tree Hugger' Farlow | SWAT"),//29
			crypt_str("Getaway Sally | The Professionals"),//30
			crypt_str("Number K | The Professionals"),//31
			crypt_str("Little Kev | The Professionals"),//32
			crypt_str("Safecracker Voltzmann | The Professionals"),//33
			crypt_str("Bloody Darryl The apped | The Professionals"),//34
			crypt_str("Sir Bloody Loudmouth Darryl | The Professionals"),//35
			crypt_str("Sir Bloody Darryl Royale | The Professionals"),//36
			crypt_str("Sir Bloody Skullhead Darryl | The Professionals"),//37
			crypt_str("Sir Bloody Silent Darryl | The Professionals"),//38
			crypt_str("Sir Bloody Miami Darryl | The Professionals"),//39
			crypt_str("Seet Soldier | Phoenix"),//40
			crypt_str("Soldier | Phoenix"),//41
			crypt_str("Slingshot | Phoenix"),//42
			crypt_str("Enforcer | Phoenix"),//43
			crypt_str("Mr. Muhlik | Elite Crew"),//44
			crypt_str("Prof. Shahmat | Elite Crew"),//45
			crypt_str("Osiris | Elite Crew"),//46
			crypt_str("Ground Rebel | Elite Crew"),//47
			crypt_str("The Elite Mr. Muhlik | Elite Crew"),//48
			crypt_str("Trapper | Guerrilla Warfare"),//49
			crypt_str("Trapper Aggressor | Guerrilla Warfare"),//50
			crypt_str("Vypa Sista of the Revolution | Guerrilla Warfare"),//51
			crypt_str("Col. Mangos Dabisi | Guerrilla Warfare"),//52
			crypt_str("Arno The Overgrown | Guerrilla Warfare"),//53
			crypt_str("Medium Rare Crasswater | Guerrilla Warfare"),//54
			crypt_str("Crasswater The Forgotten | Guerrilla Warfare"),//55
			crypt_str("Elite Trapper Solman | Guerrilla Warfare"),//56
			crypt_str("The Doctor' Romanov | Sabre"),//57
			crypt_str("Blackwolf | Sabre"),//58
			crypt_str("Maximus | Sabre"),//59
			crypt_str("Dragomir | Sabre"),//60
			crypt_str("Rezan The Ready | Sabre"),//61
			crypt_str("Danger Zone A"),
			crypt_str("Danger Zone B"),
			crypt_str("Danger Zone C"),
			crypt_str("Pirate"),
			crypt_str("Anarhist"),
			crypt_str("Professional"),
			crypt_str("Putin")

		};

		imgui_ex::checkbox(crypt_str("Agent changer"), &config->visuals.agent_changer);

		if (config->visuals.agent_changer)
		{
			imgui_ex::combo(crypt_str("Agent ct"), &config->visuals.player_model_ct, agents, IM_ARRAYSIZE(agents));

			imgui_ex::combo(crypt_str("Agent t"), &config->visuals.player_model_t, agents, IM_ARRAYSIZE(agents));
		}
	}

	/* teammates tab */

	void teammates_first_tab()
	{

		ImGui::SetCursorPosX(0.0f);
		auto cursor_pos = ImGui::GetCursorScreenPos();



		const ImGuiID nIndex = ImGui::GetCurrentWindow()->GetID(crypt_str("##preview.yaw"));
		ImGui::ButtonBehavior(ImRect(cursor_pos, u::dpi(ImVec2(192.0f, 252.0f) + cursor_pos)), nIndex, nullptr, nullptr);
		static float flMin = -FLOAT32_MAX;
		static float flMax = FLOAT32_MAX;

	


		ImGuiWindow* window = ImGui::GetCurrentWindow();

		if (window != nullptr)
		{
			if (!config->visuals.player_type[TEAM].esp_enable)
				return;
			if (config->visuals.player_type[TEAM].esp_box)
			{
				ImVec2 dpi1 = u::dpi(ImVec2(25.0f, 23.0f)),
					dpi2 = u::dpi(ImVec2(175.0f, 270.0f));

				window->DrawList->AddRect(window->Pos + dpi1 - ImVec2(1.0f, 1.0f),
					window->Pos + dpi2 + ImVec2(1.0f, 1.0f), IM_COL32(0, 0, 0, 100 * ImGui::GetStyle().Alpha));

				window->DrawList->AddRect(window->Pos + dpi1,
					window->Pos + dpi2, ImGui::ColorConvertFloat4ToU32(ImVec4(
						config->visuals.player_type[TEAM].esp_box_clr[0],
						config->visuals.player_type[TEAM].esp_box_clr[1],
						config->visuals.player_type[TEAM].esp_box_clr[2],
						config->visuals.player_type[TEAM].esp_box_clr[3] * ImGui::GetStyle().Alpha
					)));

				window->DrawList->AddRect(window->Pos + dpi1 + ImVec2(1.0f, 1.0f),
					window->Pos + dpi2 - ImVec2(1.0f, 1.0f), IM_COL32(0, 0, 0, 100) * ImGui::GetStyle().Alpha);
			}
			if (config->visuals.player_type[TEAM].esp_name)
			{

				ImVec2 dpi = u::dpi(ImVec2(175.0f, 8.0f));


				ImVec2 name = ImGui::CalcTextSize(f::dinpro_l, u::dpi(14.0f), ctx->username.c_str());
				dpi.x = dpi.x / 2 - name.x / 3.5f;
				window->DrawList->AddText(f::esp_font, u::dpi(14.0f), window->Pos +
					dpi + ImVec2(0.0f, 0.5f),
					IM_COL32(86, 86, 86, (int)(255.0f * config->visuals.player_type[TEAM].esp_name_clr[3] * ImGui::GetStyle().Alpha)),
					ctx->username.c_str());
				window->DrawList->AddText(f::esp_font, u::dpi(14.0f), window->Pos +
					dpi, ImGui::ColorConvertFloat4ToU32(ImVec4(
						config->visuals.player_type[TEAM].esp_name_clr[0],
						config->visuals.player_type[TEAM].esp_name_clr[1],
						config->visuals.player_type[TEAM].esp_name_clr[2],
						config->visuals.player_type[TEAM].esp_name_clr[3] * ImGui::GetStyle().Alpha
					)), ctx->username.c_str());



			}


			if (config->visuals.player_type[TEAM].esp_weapon)
			{
				ImVec2 dpi = u::dpi(ImVec2(175.0f, 278.0f));
				float offset = 0.0f;;
				if (config->visuals.player_type[TEAM].esp_weapon_arr[0])
				{
					offset += u::dpi(28.0f) / 2;
					ImVec2 weapon_icon = ImGui::CalcTextSize(f::weapon_icons, u::dpi(16.0f), crypt_str("Y"));
					dpi.x = dpi.x / 2 - weapon_icon.x / 8;
					window->DrawList->AddText(f::weapon_icons, u::dpi(16.0f), window->Pos +
						dpi + ImVec2(0.0f, 0.5f),
						IM_COL32(86, 86, 86, (int)(255.0f * config->visuals.player_type[TEAM].esp_weapon_clr[3] * ImGui::GetStyle().Alpha)),
						crypt_str("Y"));
					window->DrawList->AddText(f::weapon_icons, u::dpi(16.0f), window->Pos +
						dpi, ImGui::ColorConvertFloat4ToU32(ImVec4(
							config->visuals.player_type[TEAM].esp_weapon_clr[0],
							config->visuals.player_type[TEAM].esp_weapon_clr[1],
							config->visuals.player_type[TEAM].esp_weapon_clr[2],
							config->visuals.player_type[TEAM].esp_weapon_clr[3] * ImGui::GetStyle().Alpha
						)), crypt_str("Y"));

				}if (config->visuals.player_type[TEAM].esp_weapon_arr[1])
				{
					ImVec2 dpi = u::dpi(ImVec2(175.0f, 278.0f));
					dpi.y += offset;

					ImVec2 weapon_icon = ImGui::CalcTextSize(f::dinpro_l, u::dpi(14.0f), crypt_str("SCAR-20"));
					dpi.x = dpi.x / 2 - weapon_icon.x / 8.5f;
					window->DrawList->AddText(f::esp_font, u::dpi(14.0f), window->Pos +
						dpi + ImVec2(0.0f, 0.5f),
						IM_COL32(86, 86, 86, (int)(255.0f * config->visuals.player_type[TEAM].esp_weapon_clr[3] * ImGui::GetStyle().Alpha)),
						crypt_str("SCAR-20"));
					window->DrawList->AddText(f::esp_font, u::dpi(14.0f), window->Pos +
						dpi, ImGui::ColorConvertFloat4ToU32(ImVec4(
							config->visuals.player_type[TEAM].esp_weapon_clr[0],
							config->visuals.player_type[TEAM].esp_weapon_clr[1],
							config->visuals.player_type[TEAM].esp_weapon_clr[2],
							config->visuals.player_type[TEAM].esp_weapon_clr[3] * ImGui::GetStyle().Alpha
						)), crypt_str("SCAR-20"));
				}
			}

			if (config->visuals.player_type[TEAM].esp_hp_bar)
			{
				ImVec2 dpi1 = u::dpi(ImVec2(20.0f, 23.0f)),
					dpi2 = u::dpi(ImVec2(21.0f, 270.0f));

				window->DrawList->AddRectFilled(window->Pos + dpi1 - ImVec2(1.0f, 1.0f),
					window->Pos + dpi2 + ImVec2(1.0f, 1.0f), IM_COL32(0, 0, 0, 100 * ImGui::GetStyle().Alpha));


				ImU32 clr = config->visuals.player_type[TEAM].esp_hp_bar_custom_color ? ImGui::ColorConvertFloat4ToU32(ImVec4(
					config->visuals.player_type[TEAM].esp_hp_bar_color[0],
					config->visuals.player_type[TEAM].esp_hp_bar_color[1],
					config->visuals.player_type[TEAM].esp_hp_bar_color[2],
					config->visuals.player_type[TEAM].esp_hp_bar_color[3] * ImGui::GetStyle().Alpha
				)) : IM_COL32(0, 255, 0, (int)(255.0f * ImGui::GetStyle().Alpha));

				window->DrawList->AddRectFilled(window->Pos + dpi1,
					window->Pos + dpi2, clr);
			}

			if (config->visuals.player_type[TEAM].esp_ammo)
			{
				ImVec2 dpi1 = u::dpi(ImVec2(25.0f, 273.0f)),
					dpi2 = u::dpi(ImVec2(175.0f, 274.0f));

				window->DrawList->AddRectFilled(window->Pos + dpi1 - ImVec2(1.0f, 1.0f),
					window->Pos + dpi2 + ImVec2(1.0f, 1.0f), IM_COL32(112, 112, 112, 150 * ImGui::GetStyle().Alpha));

				window->DrawList->AddRectFilled(window->Pos + dpi1,
					window->Pos + dpi2, ImGui::ColorConvertFloat4ToU32(ImVec4(
						config->visuals.player_type[TEAM].esp_ammo_clr[0],
						config->visuals.player_type[TEAM].esp_ammo_clr[1],
						config->visuals.player_type[TEAM].esp_ammo_clr[2],
						config->visuals.player_type[TEAM].esp_ammo_clr[3] * ImGui::GetStyle().Alpha
					)));
			}


			if (config->visuals.player_type[TEAM].esp_flags)
			{
				std::vector < Flags	> m_flags;

				if (config->visuals.player_type[TEAM].esp_flags_arr[FLAGS_HELMET])
				{
					m_flags.push_back(Flags(crypt_str("HK"), config->visuals.player_type[TEAM].esp_flags_combo_clr[FLAGS_HELMET]));
				}

				if (config->visuals.player_type[TEAM].esp_flags_arr[FLAGS_MONEY])
				{
					m_flags.push_back(Flags(crypt_str("16000$"), config->visuals.player_type[TEAM].esp_flags_combo_clr[FLAGS_MONEY]));
				}

				if (config->visuals.player_type[TEAM].esp_flags_arr[FLAGS_DEFUSER])
				{
					m_flags.push_back(Flags(crypt_str("KIT"), config->visuals.player_type[TEAM].esp_flags_combo_clr[FLAGS_DEFUSER]));
				}

				if (config->visuals.player_type[TEAM].esp_flags_arr[FLAGS_BOMB])
				{
					m_flags.push_back(Flags(crypt_str("BOMB"), config->visuals.player_type[TEAM].esp_flags_combo_clr[FLAGS_BOMB]));
				}

				if (config->visuals.player_type[TEAM].esp_flags_arr[FLAGS_RELOAD])
				{
					m_flags.push_back(Flags(crypt_str("RELOAD"), config->visuals.player_type[TEAM].esp_flags_combo_clr[FLAGS_RELOAD]));
				}

				if (config->visuals.player_type[TEAM].esp_flags_arr[FLAGS_ZOOM])
				{
					m_flags.push_back(Flags(crypt_str("ZOOM"), config->visuals.player_type[TEAM].esp_flags_combo_clr[FLAGS_ZOOM]));
				}

				if (config->visuals.player_type[TEAM].esp_flags_arr[FLAGS_FLASH])
				{
					m_flags.push_back(Flags(crypt_str("FLASH"), config->visuals.player_type[TEAM].esp_flags_combo_clr[FLAGS_FLASH]));
				}

				if (config->visuals.player_type[TEAM].esp_flags_arr[FLAGS_DUCK])
				{
					m_flags.push_back(Flags(crypt_str("FD"), config->visuals.player_type[TEAM].esp_flags_combo_clr[FLAGS_DUCK]));
				}

				if (config->visuals.player_type[TEAM].esp_flags_arr[FLAGS_EXPLOIT])
				{
					m_flags.push_back(Flags(crypt_str("EXPLOIT"), config->visuals.player_type[TEAM].esp_flags_combo_clr[FLAGS_EXPLOIT]));
				}

				if (config->visuals.player_type[ENEMY].esp_flags_arr[FLAGS_PLANT])
				{
					m_flags.push_back(Flags(crypt_str("PLANT"), config->visuals.player_type[ENEMY].esp_flags_combo_clr[FLAGS_PLANT]));
				}

				if (config->visuals.player_type[ENEMY].esp_flags_arr[FLAGS_DEFUSE])
				{
					m_flags.push_back(Flags(crypt_str("DEFUSE"), config->visuals.player_type[ENEMY].esp_flags_combo_clr[FLAGS_DEFUSE]));
				}

				if (config->visuals.player_type[TEAM].esp_flags_arr[FLAGS_IGNORE])
				{
					m_flags.push_back(Flags(crypt_str("IGNORE"), config->visuals.player_type[TEAM].esp_flags_combo_clr[FLAGS_IGNORE]));
				}

				float offset = 19.0f;
				static ImU32 clr_flags;
				for (auto flag : m_flags)
				{
					ImVec2 dpi = u::dpi(ImVec2(180.0f, offset));


					clr_flags = ImGui::ColorConvertFloat4ToU32(ImVec4(
						(float)flag.m_color.r() / 255.0f,
						(float)flag.m_color.g() / 255.0f,
						(float)flag.m_color.b() / 255.0f,
						(float)flag.m_color.a() / 255.0f
					));

					window->DrawList->AddText(f::esp_font, u::dpi(12.0f), window->Pos +
						dpi + ImVec2(0.0f, 0.5f), IM_COL32(86, 86, 86, (int)(255.0f * flag.m_color.a() / 255.0f * ImGui::GetStyle().Alpha)), flag.m_text.c_str());
					window->DrawList->AddText(f::esp_font, u::dpi(12.0f), window->Pos +
						dpi, clr_flags, flag.m_text.c_str());
					offset += u::dpi(10.0f);
				}
				m_flags.clear();
			}
		}
	}

	void teammates_second_tab()
	{
		std::vector <const char*>chams_type = { "Regular","Flat" };
		const char* chams_modifiers[] = { "Glass","Glow","Wireframe" };
	/*	for (auto& mat : Lua_manager->materials)
		{
			chams_type.push_back(mat.m_name.c_str());
		}*/
		imgui_ex::checkbox(crypt_str("Chams"), &config->visuals.player_type[TEAM].chams_enable);
		if (config->visuals.player_type[TEAM].chams_enable) {

			imgui_ex::checkbox(crypt_str("Visible chams"), &config->visuals.player_type[TEAM].chams_visible);
			if (config->visuals.player_type[TEAM].chams_visible) {
				imgui_ex::color_edit4(crypt_str("##chams_clr_visible"), config->visuals.player_type[TEAM].chams_clr_visible);
				if (config->visuals.player_type[TEAM].chams_type_visible >= chams_type.size())
				{
					config->visuals.player_type[TEAM].chams_type_visible = 0;
				}
				imgui_ex::combo(crypt_str("##chams_visible"), &config->visuals.player_type[TEAM].chams_type_visible,
					&chams_type[0], chams_type.size());
				imgui_ex::checkbox(crypt_str("Chams visible modifer"), &config->visuals.player_type[TEAM].chams_modifiers_visible);
				if (config->visuals.player_type[TEAM].chams_modifiers_visible)
				{
					imgui_ex::mcombo_clr(crypt_str("##chams_visible_modifers"), config->visuals.player_type[TEAM].chams_modifiers_arr_visible.data(), config->visuals.player_type[TEAM].chams_modifiers_clr_visible,
						chams_modifiers, IM_ARRAYSIZE(chams_modifiers));
				}

			}
			{
				imgui_ex::checkbox(crypt_str("Invisible chams"), &config->visuals.player_type[TEAM].chams_invisible);
				if (config->visuals.player_type[TEAM].chams_invisible) {
					imgui_ex::color_edit4(crypt_str("##chams_clr_invisible"), config->visuals.player_type[TEAM].chams_clr_invisible);
					if (config->visuals.player_type[TEAM].chams_type_invisible >= chams_type.size())
					{
						config->visuals.player_type[TEAM].chams_type_invisible = 0;
					}
					imgui_ex::combo(crypt_str("##chams_invisible"), &config->visuals.player_type[TEAM].chams_type_invisible,
						&chams_type[0], chams_type.size());
					imgui_ex::checkbox(crypt_str("Chams invisible modifer"), &config->visuals.player_type[TEAM].chams_modifiers_invisible);
					if (config->visuals.player_type[TEAM].chams_modifiers_invisible)
					{
						imgui_ex::mcombo_clr(crypt_str("##chams_invisible_modifers"), config->visuals.player_type[TEAM].chams_modifiers_arr_invisible.data(), config->visuals.player_type[TEAM].chams_modifiers_clr_invisible,
							chams_modifiers, IM_ARRAYSIZE(chams_modifiers));
					}
				}
			}


		}
		const char* glow_types[] = { "Outline", "Cover", "Thin" };
		imgui_ex::checkbox(crypt_str("Glow"), &config->visuals.player_type[TEAM].glow_enable);
		imgui_ex::color_edit4(crypt_str("##glow_clr"), config->visuals.player_type[TEAM].glow_clr);

		imgui_ex::combo(crypt_str("##glow"), &config->visuals.player_type[TEAM].glow_type,
			glow_types, IM_ARRAYSIZE(glow_types));

		ImGui::Spacing();
	}

	void teammates_third_tab()
	{
		imgui_ex::checkbox(crypt_str("Enable ESP"), &config->visuals.player_type[TEAM].esp_enable);

		imgui_ex::checkbox(crypt_str("Box"), &config->visuals.player_type[TEAM].esp_box);
		imgui_ex::color_edit4(crypt_str("##box_clr"), config->visuals.player_type[TEAM].esp_box_clr);

		imgui_ex::checkbox(crypt_str("Name"), &config->visuals.player_type[TEAM].esp_name);
		imgui_ex::color_edit4(crypt_str("##name_clr"), config->visuals.player_type[TEAM].esp_name_clr);

		imgui_ex::checkbox(crypt_str("Health bar"), &config->visuals.player_type[TEAM].esp_hp_bar);

		if (config->visuals.player_type[TEAM].esp_hp_bar)
		{
			imgui_ex::checkbox(crypt_str("Color"), &config->visuals.player_type[TEAM].esp_hp_bar_custom_color);
			imgui_ex::color_edit4(crypt_str("##bar_clr"), config->visuals.player_type[TEAM].esp_hp_bar_color);
		}

		imgui_ex::checkbox(crypt_str("Skeleton"), &config->visuals.player_type[TEAM].esp_skeleton);
		imgui_ex::color_edit4(crypt_str("##skeleton_clr"), config->visuals.player_type[TEAM].esp_skeleton_clr);

		imgui_ex::checkbox(crypt_str("Flags"), &config->visuals.player_type[TEAM].esp_flags);
		const char* esp_flags_combo[] = {
				"Helmet", "Money" ,"Defuser",
				"Bomb/Hostage", "Reload", "Zoom","Flash", "Fake duck", "Exploit", "Plant", "Defuse"
		};
		if (config->visuals.player_type[TEAM].esp_flags) {
			imgui_ex::mcombo_clr(crypt_str("##flags"), config->visuals.player_type[TEAM].esp_flags_arr.data(), config->visuals.player_type[TEAM].esp_flags_combo_clr,
				esp_flags_combo, IM_ARRAYSIZE(esp_flags_combo));
		}

		imgui_ex::checkbox(crypt_str("Weapon"), &config->visuals.player_type[TEAM].esp_weapon);
		if (config->visuals.player_type[TEAM].esp_weapon) {
			imgui_ex::color_edit4(crypt_str("##weapon_clr"), config->visuals.player_type[TEAM].esp_weapon_clr);
			const char* esp_weapon_combo[2] = { "Icon", "Text" };
			imgui_ex::mcombo(crypt_str("##weapon"), config->visuals.player_type[TEAM].esp_weapon_arr.data(),
				esp_weapon_combo, IM_ARRAYSIZE(esp_weapon_combo));
			imgui_ex::text(crypt_str("Knife/Taser color"));
			imgui_ex::color_edit4(crypt_str("##knife_taser_clr"), config->visuals.player_type[TEAM].esp_knife_taser_clr);
		}

		imgui_ex::checkbox(crypt_str("Ammo"), &config->visuals.player_type[TEAM].esp_ammo);
		if (config->visuals.player_type[TEAM].esp_ammo)
			imgui_ex::color_edit4(crypt_str("##ammo_clr"), config->visuals.player_type[TEAM].esp_ammo_clr);

		imgui_ex::checkbox(crypt_str("Sounds"), &config->visuals.player_type[TEAM].sounds);

		if (config->visuals.player_type[TEAM].sounds)
		{
			imgui_ex::color_edit4(crypt_str("##sounds_color"), config->visuals.player_type[TEAM].sounds_color);
			imgui_ex::slider_float(crypt_str("Time"), &config->visuals.player_type[TEAM].sounds_time, 0.1f, 5.0f, crypt_str("%.1f s"));
			imgui_ex::slider_int(crypt_str("Radius"), &config->visuals.player_type[TEAM].sounds_radius, 1, 100);
		}
	}

	/* world tab */


	void world_first_tab()
	{
		ImGui::GetWindowDrawList()->AddShadowRect(ImGui::GetWindowPos() + u::dpi(ImVec2(0.0f, 25.0f)),
			ImGui::GetWindowPos() + u::dpi(ImVec2(250.0f, 25.0f)), IM_COL32(0, 0, 0, 100), 25.0f, ImVec2(0, 0), 0, 3.0f, ImDrawCornerFlags_Top);

		ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetWindowPos() + u::dpi(ImVec2(0.0f, 0.0f)),
			ImGui::GetWindowPos() + u::dpi(ImVec2(250.0f, 25.0f)), ImGui::GetColorU32(ImGuiCol_ChildBg), 3.0f, ImDrawCornerFlags_Top);

		{
			ImGui::SetCursorPos(ImVec2(15.0f, 0.0f));

			imgui_ex::tab(crypt_str("Weapon"), ImVec2(78.0f, 25.0f), s::visuals_world_subtab, 0);

			ImGui::SetCursorPos(u::dpi(ImVec2(93.0f, 0.0f)));

			imgui_ex::tab(crypt_str("Grenade"), ImVec2(77.0f, 25.0f), s::visuals_world_subtab, 1);

			ImGui::SetCursorPos(u::dpi(ImVec2(170.0f, 0.0f)));

			imgui_ex::tab(crypt_str("Bomb"), ImVec2(65.0f, 25.0f), s::visuals_world_subtab, 2);
		}


		switch (s::visuals_world_subtab)
		{
		case 0:
		{
	
			float offset_y_min = 45.0f;
			float offset_y_max = 170.0f;

			ImGui::SetCursorPos(u::dpi(ImVec2(23.0f, offset_y_min)));
			auto cursor_pos = ImGui::GetCursorScreenPos();


			const ImGuiID nIndex = ImGui::GetCurrentWindow()->GetID(crypt_str("##preview.yaw"));
			ImGui::ButtonBehavior(ImRect(cursor_pos, u::dpi(ImVec2(200.0f, 150.0f) + cursor_pos)), nIndex, nullptr, nullptr);
			static float flMin = -FLOAT32_MAX;
			static float flMax = FLOAT32_MAX;


			ImGuiWindow* window = ImGui::GetCurrentWindow();

			if (window != nullptr)
			{
				if (config->visuals.world.weapon_type[WEAPON].esp) {
					if (config->visuals.world.weapon_type[WEAPON].box)
					{
						ImVec2 dpi1 = u::dpi(ImVec2(23, 65)), // 23 65
							dpi2 = u::dpi(ImVec2(227, 175));  // 227 175

						window->DrawList->AddRect(window->Pos + dpi1 - ImVec2(1.0f, 1.0f),
							window->Pos + dpi2 + ImVec2(1.0f, 1.0f), IM_COL32(0, 0, 0, 100 * ImGui::GetStyle().Alpha));

						window->DrawList->AddRect(window->Pos + dpi1,
							window->Pos + dpi2, ImGui::ColorConvertFloat4ToU32(ImVec4(
								config->visuals.world.weapon_type[WEAPON].box_clr[0],
								config->visuals.world.weapon_type[WEAPON].box_clr[1],
								config->visuals.world.weapon_type[WEAPON].box_clr[2],
								config->visuals.world.weapon_type[WEAPON].box_clr[3] * ImGui::GetStyle().Alpha
							)));

						window->DrawList->AddRect(window->Pos + dpi1 + ImVec2(1.0f, 1.0f),
							window->Pos + dpi2 - ImVec2(1.0f, 1.0f), IM_COL32(0, 0, 0, 100 * ImGui::GetStyle().Alpha));
					}
					Color clr_ammo(config->visuals.world.weapon_type[WEAPON].ammo_clr);
					if (config->visuals.world.weapon_type[WEAPON].ammo)
					{
						if (config->visuals.world.weapon_type[WEAPON].ammo_type[0])
						{
							ImVec2 dpi1 = u::dpi(ImVec2(23.0f, 178.0f)),
								dpi2 = u::dpi(ImVec2(227.0f, 179.0f));

							window->DrawList->AddRectFilled(window->Pos + dpi1 - ImVec2(1.0f, 1.0f),
								window->Pos + dpi2 + ImVec2(1.0f, 1.0f), IM_COL32(112, 112, 112, clr_ammo.a() * ImGui::GetStyle().Alpha));

							window->DrawList->AddRectFilled(window->Pos + dpi1,
								window->Pos + dpi2, IM_COL32(clr_ammo.r(), clr_ammo.g(), clr_ammo.b(), clr_ammo.a() * ImGui::GetStyle().Alpha));
						}

						if (config->visuals.world.weapon_type[WEAPON].ammo_type[1])
						{

							ImVec2 dpi = u::dpi(ImVec2(23, 180.0f));

							float dpi2 = u::dpi(227);
							float center = (dpi2 - dpi.x) / 2.0f;

							ImVec2 text = ImGui::CalcTextSize(f::esp_font, u::dpi(14.0f), crypt_str("10/30"));

							dpi.x = center;

							window->DrawList->AddText(f::esp_font, u::dpi(14.0f), window->Pos +
								dpi + ImVec2(0.0f, 0.5f), IM_COL32(86, 86, 86, clr_ammo.a() * ImGui::GetStyle().Alpha), crypt_str("10/30"));

							window->DrawList->AddText(f::esp_font, u::dpi(14.0f),
								window->Pos + dpi, IM_COL32(clr_ammo.r(), clr_ammo.g(), clr_ammo.b(), clr_ammo.a() * ImGui::GetStyle().Alpha), crypt_str("10/30"));
						}
					}
					float offset = 0;
					if (config->visuals.world.weapon_type[WEAPON].ammo && config->visuals.world.weapon_type[WEAPON].ammo_type[1])
					{
						offset = u::dpi(15);
					}
					if (config->visuals.world.weapon_type[WEAPON].icon) {
						ImVec2 dpi = u::dpi(ImVec2(23, 180.0f));

						float dpi2 = u::dpi(227);
						float center = (dpi2 - dpi.x) / 2.0f;

						ImVec2 text = ImGui::CalcTextSize(f::weapon_icons, u::dpi(14.0f), crypt_str("W"));

						dpi.x = center;
						dpi.y += offset;
						Color temp = Color(config->visuals.world.weapon_type[WEAPON].icon_clr);
						window->DrawList->AddText(f::weapon_icons, u::dpi(14.0f), window->Pos +
							dpi + ImVec2(0.0f, 0.5f), IM_COL32(86, 86, 86, temp.a() * ImGui::GetStyle().Alpha), crypt_str("W"));

						window->DrawList->AddText(f::weapon_icons, u::dpi(14.0f),
							window->Pos + dpi, IM_COL32(temp.r(), temp.g(), temp.b(), temp.a() * ImGui::GetStyle().Alpha), crypt_str("W"));
					}
				}
			}

			break;
		}

		case 1:
		{


			float offset_y_min = 45.0f;
			float offset_y_max = 170.0f;

			ImGui::SetCursorPos(u::dpi(ImVec2(23.0f, offset_y_min)));
			auto cursor_pos = ImGui::GetCursorScreenPos();


			const ImGuiID nIndex = ImGui::GetCurrentWindow()->GetID(crypt_str("##previewnade.yaw"));
			ImGui::ButtonBehavior(ImRect(cursor_pos, u::dpi(ImVec2(200.0f, 150.0f) + cursor_pos)), nIndex, nullptr, nullptr);
			static float flMin = -FLOAT32_MAX;
			static float flMax = FLOAT32_MAX;



			ImGuiWindow* window = ImGui::GetCurrentWindow();

			if (window != nullptr)
			{
				if (config->visuals.world.grenade_esp.enable) {
					if (config->visuals.world.grenade_esp.box)
					{
						ImVec2 dpi1 = u::dpi(ImVec2(94, 107)),
							dpi2 = u::dpi(ImVec2(152, 165));

						window->DrawList->AddRect(window->Pos + dpi1 - ImVec2(1.0f, 1.0f),
							window->Pos + dpi2 + ImVec2(1.0f, 1.0f), IM_COL32(0, 0, 0, 100 * ImGui::GetStyle().Alpha));

						window->DrawList->AddRect(window->Pos + dpi1,
							window->Pos + dpi2, ImGui::ColorConvertFloat4ToU32(ImVec4(
								config->visuals.world.grenade_esp.box_clr[0],
								config->visuals.world.grenade_esp.box_clr[1],
								config->visuals.world.grenade_esp.box_clr[2],
								config->visuals.world.grenade_esp.box_clr[3] * ImGui::GetStyle().Alpha
							)));

						window->DrawList->AddRect(window->Pos + dpi1 + ImVec2(1.0f, 1.0f),
							window->Pos + dpi2 - ImVec2(1.0f, 1.0f), IM_COL32(0, 0, 0, 100 * ImGui::GetStyle().Alpha));
					}
					Color clr_temp(config->visuals.world.grenade_esp.name_clr);
					if (config->visuals.world.grenade_esp.name)
					{
						float offset = 0.0f;
						if (config->visuals.world.grenade_esp.name_types[0])
						{
							ImVec2 dpi = u::dpi(ImVec2(23, 170.0f));

							float dpi2 = u::dpi(260);
							float center = (dpi2 - dpi.x) / 2.0f;
							offset += u::dpi(28.0f) / 2;
							ImVec2 text = ImGui::CalcTextSize(f::weapon_icons, u::dpi(14.0f), crypt_str("j"));

							dpi.x = center;
							Color temp = Color(config->visuals.world.grenade_esp.name_clr);
							window->DrawList->AddText(f::weapon_icons, u::dpi(14.0f), window->Pos +
								dpi + ImVec2(0.0f, 0.5f), IM_COL32(86, 86, 86, temp.a() * ImGui::GetStyle().Alpha), crypt_str("j"));

							window->DrawList->AddText(f::weapon_icons, u::dpi(14.0f),
								window->Pos + dpi, IM_COL32(temp.r(), temp.g(), temp.b(), temp.a() * ImGui::GetStyle().Alpha), crypt_str("j"));
						}
						if (config->visuals.world.grenade_esp.name_types[1])
						{

							ImVec2 dpi = u::dpi(ImVec2(94, 170.0f));
							dpi.y += offset;

							ImVec2 weapon_icon = ImGui::CalcTextSize(f::dinpro_l, u::dpi(14.0f), crypt_str("HE GRENADE"));

							float dpi2 = u::dpi(152);

							dpi.x = (dpi.x + ((dpi2 - dpi.x) / 2.0f)) - weapon_icon.x / 2.0f;
							window->DrawList->AddText(f::esp_font, u::dpi(14.0f), window->Pos +
								dpi + ImVec2(0.0f, 0.5f),
								IM_COL32(86, 86, 86, (int)(255.0f * config->visuals.world.grenade_esp.name_clr[3])),
								crypt_str("HE GRENADE"));
							window->DrawList->AddText(f::esp_font, u::dpi(14.0f), window->Pos +
								dpi, ImGui::ColorConvertFloat4ToU32(ImVec4(
									config->visuals.world.grenade_esp.name_clr[0],
									config->visuals.world.grenade_esp.name_clr[1],
									config->visuals.world.grenade_esp.name_clr[2],
									config->visuals.world.grenade_esp.name_clr[3] * ImGui::GetStyle().Alpha
								)), crypt_str("HE GRENADE"));

						}
					}

				}
			}

			break;
		}

		case 2:
		{

			float offset_y_min = 45.0f;
			float offset_y_max = 170.0f;

			ImGui::SetCursorPos(u::dpi(ImVec2(23.0f, offset_y_min)));
			auto cursor_pos = ImGui::GetCursorScreenPos();


			const ImGuiID nIndex = ImGui::GetCurrentWindow()->GetID(crypt_str("##previewnade.yaw"));
			ImGui::ButtonBehavior(ImRect(cursor_pos, u::dpi(ImVec2(200.0f, 150.0f) + cursor_pos)), nIndex, nullptr, nullptr);
			static float flMin = -FLOAT32_MAX;
			static float flMax = FLOAT32_MAX;



			ImGuiWindow* window = ImGui::GetCurrentWindow();

			if (window != nullptr)
			{
				if (config->visuals.world.weapon_type[C4].esp) {
					if (config->visuals.world.weapon_type[C4].box)
					{
						ImVec2 dpi1 = u::dpi(ImVec2(64, 67)),
							dpi2 = u::dpi(ImVec2(182, 175));

						window->DrawList->AddRect(window->Pos + dpi1 - ImVec2(1.0f, 1.0f),
							window->Pos + dpi2 + ImVec2(1.0f, 1.0f), IM_COL32(0, 0, 0, 100 * ImGui::GetStyle().Alpha));

						window->DrawList->AddRect(window->Pos + dpi1,
							window->Pos + dpi2, ImGui::ColorConvertFloat4ToU32(ImVec4(
								config->visuals.world.weapon_type[C4].box_clr[0],
								config->visuals.world.weapon_type[C4].box_clr[1],
								config->visuals.world.weapon_type[C4].box_clr[2],
								config->visuals.world.weapon_type[C4].box_clr[3] * ImGui::GetStyle().Alpha
							)));

						window->DrawList->AddRect(window->Pos + dpi1 + ImVec2(1.0f, 1.0f),
							window->Pos + dpi2 - ImVec2(1.0f, 1.0f), IM_COL32(0, 0, 0, 100 * ImGui::GetStyle().Alpha));
					}
					if (config->visuals.world.weapon_type[C4].icon)
					{


						ImVec2 dpi = u::dpi(ImVec2(64, 180.0f));


						ImVec2 weapon_icon = ImGui::CalcTextSize(f::icons_weapon, u::dpi(16.0f), (char*)u8"\ue031");

						float dpi2 = u::dpi(182);

						dpi.x = (dpi.x + ((dpi2 - dpi.x) / 2.0f)) - weapon_icon.x / 2.0f;
						window->DrawList->AddText(f::icons_weapon, u::dpi(16.0f), window->Pos +
							dpi + ImVec2(0.0f, 0.5f),
							IM_COL32(86, 86, 86, (int)(255.0f * config->visuals.world.weapon_type[C4].icon_clr[3])),
							(char*)u8"\ue031");
						window->DrawList->AddText(f::icons_weapon, u::dpi(16.0f), window->Pos +
							dpi, ImGui::ColorConvertFloat4ToU32(ImVec4(
								config->visuals.world.weapon_type[C4].icon_clr[0],
								config->visuals.world.weapon_type[C4].icon_clr[1],
								config->visuals.world.weapon_type[C4].icon_clr[2],
								config->visuals.world.weapon_type[C4].icon_clr[3] * ImGui::GetStyle().Alpha
							)), ((char*)u8"\ue031"));


					}
				}
			}
			break;
		}

		default:
			s::visuals_world_subtab = 0;
			break;
		}
	}

	void world_second_tab()
	{
		switch (s::visuals_world_subtab)
		{
		case 0:
			
			imgui_ex::checkbox(crypt_str("Enable ESP"), &config->visuals.world.weapon_type[WEAPON].esp);

			imgui_ex::checkbox(crypt_str("Box"), &config->visuals.world.weapon_type[WEAPON].box);

			if (config->visuals.world.weapon_type[WEAPON].box)
				imgui_ex::color_edit4(crypt_str("Box clr"), config->visuals.world.weapon_type[WEAPON].box_clr);

			imgui_ex::checkbox(crypt_str("Ammo"), &config->visuals.world.weapon_type[WEAPON].ammo);

			if (config->visuals.world.weapon_type[WEAPON].ammo)
			{
				const char* ammo[] = { "Bar", "Text"};
				imgui_ex::color_edit4(crypt_str("Ammo clr"), config->visuals.world.weapon_type[WEAPON].ammo_clr);
				imgui_ex::mcombo(crypt_str("Ammo type"), config->visuals.world.weapon_type[WEAPON].ammo_type.data(), ammo, IM_ARRAYSIZE(ammo));
			}

			imgui_ex::checkbox(crypt_str("Icon"), &config->visuals.world.weapon_type[WEAPON].icon);

			if (config->visuals.world.weapon_type[WEAPON].icon)
				imgui_ex::color_edit4(crypt_str("Icon clr"), config->visuals.world.weapon_type[WEAPON].icon_clr);

			imgui_ex::checkbox(crypt_str("Chams"), &config->visuals.world.weapon_type[WEAPON].chams);

			if (config->visuals.world.weapon_type[WEAPON].chams)
			{
				imgui_ex::color_edit4(crypt_str("Chams clr"), config->visuals.world.weapon_type[WEAPON].chams_clr);

				const char* chams[] = { "Regular", "Flat" };
				imgui_ex::mcombo(crypt_str("Chams type"), &config->visuals.world.weapon_type[WEAPON].chams_type, chams, IM_ARRAYSIZE(chams));

				imgui_ex::checkbox(crypt_str("Chams modifers"), &config->visuals.world.weapon_type[WEAPON].chams_modifer);
				const char* chams_modifers[] = { "Glass", "Glow", "Wiriframe"};
				imgui_ex::mcombo_clr(crypt_str("Chams modifers arr"), config->visuals.world.weapon_type[WEAPON].chams_modifiers_arr.data(), config->visuals.world.weapon_type[WEAPON].chams_modifiers_clr, chams_modifers, IM_ARRAYSIZE(chams_modifers));
			}

			imgui_ex::checkbox(crypt_str("Glow"), &config->visuals.world.weapon_type[WEAPON].glow);

			if (config->visuals.world.weapon_type[WEAPON].glow)
			{
				const char* glow[] = { "Outline", "Cover", "Thin" };
				imgui_ex::color_edit4(crypt_str("Glow clr"), config->visuals.world.weapon_type[WEAPON].glow_clr);
				imgui_ex::mcombo(crypt_str("Glow type"), &config->visuals.world.weapon_type[WEAPON].glow_type, glow, IM_ARRAYSIZE(glow));
			}
			
			 break;
		case 1:
			imgui_ex::checkbox(crypt_str("Enable ESP"), &config->visuals.world.grenade_esp.enable);

			imgui_ex::checkbox(crypt_str("Box"), &config->visuals.world.grenade_esp.box);

			if (config->visuals.world.grenade_esp.box)
				imgui_ex::color_edit4(crypt_str("Box clr"), config->visuals.world.grenade_esp.box_clr);

			imgui_ex::checkbox(crypt_str("Name"), &config->visuals.world.grenade_esp.name);

			if (config->visuals.world.grenade_esp.name)
			{
				const char* name[] = { "Icon", "Text" };
				imgui_ex::color_edit4(crypt_str("Name"), config->visuals.world.grenade_esp.name_clr);
				imgui_ex::mcombo(crypt_str("Name type"), config->visuals.world.grenade_esp.name_types.data(), name, IM_ARRAYSIZE(name));
			}		

			imgui_ex::checkbox(crypt_str("Predition"), &config->visuals.world.grenade_esp.prediction);

			if (config->visuals.world.grenade_esp.prediction)
			{
				imgui_ex::color_edit4(crypt_str("Prediction clr"), config->visuals.world.grenade_esp.prediction_clr);
				//imgui_ex::color_edit4(crypt_str("Prediction clr last"), config->visuals.world.grenade_esp.prediction_last_point_clr);
				//imgui_ex::color_edit4(crypt_str("Prediction clr point"), config->visuals.world.grenade_esp.prediction_points_clr);
			}

			imgui_ex::checkbox(crypt_str("Inferno indicator"), &config->visuals.world.grenade_esp.inferno_indicator);

			if (config->visuals.world.grenade_esp.inferno_indicator)
				imgui_ex::color_edit4(crypt_str("Inferno clr"), config->visuals.world.grenade_esp.inferno_indicator_clr);

			imgui_ex::checkbox(crypt_str("Smoke indicator"), &config->visuals.world.grenade_esp.smoke_indicator);

			if (config->visuals.world.grenade_esp.smoke_indicator)
				imgui_ex::color_edit4(crypt_str("Smoke clr"), config->visuals.world.grenade_esp.smoke_indicator_clr);

			imgui_ex::checkbox(crypt_str("Chams"), &config->visuals.world.weapon_type[NADE].chams);

			if (config->visuals.world.weapon_type[NADE].chams)
			{
				imgui_ex::color_edit4(crypt_str("Chams clr"), config->visuals.world.weapon_type[NADE].chams_clr);
				const char* chams[] = { "Regular", "Flat" };
				imgui_ex::mcombo(crypt_str("Chams type"), &config->visuals.world.weapon_type[NADE].chams_type, chams, IM_ARRAYSIZE(chams));

				const char* chams_modifers[] = { "Glass", "Glow", "Wiriframe" };
				imgui_ex::checkbox(crypt_str("Chams modifers"), &config->visuals.world.weapon_type[NADE].chams_modifer);
				imgui_ex::mcombo_clr(crypt_str("Chams modifers arr"), config->visuals.world.weapon_type[NADE].chams_modifiers_arr.data(), config->visuals.world.weapon_type[WEAPON].chams_modifiers_clr, chams_modifers, IM_ARRAYSIZE(chams_modifers));
			}

			imgui_ex::checkbox(crypt_str("Glow"), &config->visuals.world.weapon_type[NADE].glow);

			if (config->visuals.world.weapon_type[NADE].glow)
			{
				const char* glow[] = { "Outline", "Cover", "Thin" };
				imgui_ex::color_edit4(crypt_str("Glow clr"), config->visuals.world.weapon_type[NADE].glow_clr);
				imgui_ex::mcombo(crypt_str("Glow type"), &config->visuals.world.weapon_type[NADE].glow_type, glow, IM_ARRAYSIZE(glow));
			}

			break;
		case 2:

			imgui_ex::checkbox(crypt_str("Enable ESP"), &config->visuals.world.weapon_type[C4].esp);

			imgui_ex::checkbox(crypt_str("Box"), &config->visuals.world.weapon_type[C4].box);

			if (config->visuals.world.weapon_type[C4].box)
				imgui_ex::color_edit4(crypt_str("Box clr"), config->visuals.world.weapon_type[C4].box_clr);

			imgui_ex::checkbox(crypt_str("Icon"), &config->visuals.world.weapon_type[C4].icon);

			if (config->visuals.world.weapon_type[C4].icon)
				imgui_ex::color_edit4(crypt_str("Icon clr"), config->visuals.world.weapon_type[C4].icon_clr);

			imgui_ex::checkbox(crypt_str("Timer"), &config->visuals.world.bomb_timer);

			imgui_ex::checkbox(crypt_str("Chams"), &config->visuals.world.weapon_type[C4].chams);

			if (config->visuals.world.weapon_type[C4].chams)
			{
				imgui_ex::color_edit4(crypt_str("Chams clr"), config->visuals.world.weapon_type[C4].chams_clr);
				const char* chams[] = { "Regular", "Flat" };
				imgui_ex::mcombo(crypt_str("Chams type"), &config->visuals.world.weapon_type[C4].chams_type, chams, IM_ARRAYSIZE(chams));

				const char* chams_modifers[] = { "Glass", "Glow", "Wiriframe" };
				imgui_ex::checkbox(crypt_str("Chams modifers"), &config->visuals.world.weapon_type[C4].chams_modifer);
				imgui_ex::mcombo_clr(crypt_str("Chams modifers arr"), config->visuals.world.weapon_type[C4].chams_modifiers_arr.data(), config->visuals.world.weapon_type[WEAPON].chams_modifiers_clr, chams_modifers, IM_ARRAYSIZE(chams_modifers));
			}

			imgui_ex::checkbox(crypt_str("Glow"), &config->visuals.world.weapon_type[C4].glow);

			if (config->visuals.world.weapon_type[C4].glow)
			{
				const char* glow[] = { "Outline", "Cover", "Thin" };
				imgui_ex::color_edit4(crypt_str("Glow clr"), config->visuals.world.weapon_type[C4].glow_clr);
				imgui_ex::mcombo(crypt_str("Glow type"), &config->visuals.world.weapon_type[C4].glow_type, glow, IM_ARRAYSIZE(glow));
			}

			break;		
		}	
	}

	void world_third_tab()
	{
	}

	void world_forth_tab()
	{
	}

	void world_sixth_tab()
	{
	}

	void world_fifth_tab()
	{
		if (config->anti_aim.enable)
		{
			imgui_ex::checkbox(crypt_str("Manual anti-aim"), &config->visuals.world.manual_anti_aim);

			if (config->visuals.world.manual_anti_aim)
				imgui_ex::color_edit4(crypt_str("##manual_anti_aim_clr"), config->visuals.world.manual_anti_aim_clr);
		}

		imgui_ex::checkbox(crypt_str("Offscreen indicator"), &config->visuals.world.offscreen_enable);

		if (config->visuals.world.offscreen_enable)
		{
			imgui_ex::color_edit4(crypt_str("##offscreen_clr"), config->visuals.world.offscreen_color);

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, u::dpi(ImVec2(0.0f, 15.0f)));
			imgui_ex::text(crypt_str("Outline color"));
			imgui_ex::color_edit4(crypt_str("##offscreen_out_clr"), config->visuals.world.offscreen_color_out);
			ImGui::PopStyleVar();

			imgui_ex::checkbox(crypt_str("Fade"), &config->visuals.world.offscreen_fade);
			imgui_ex::slider_int(crypt_str("Distance"), &config->visuals.world.offscreen_distance, 1, 100);
			imgui_ex::slider_int(crypt_str("Size"), &config->visuals.world.offscreen_size, 1, 100);
		}

		imgui_ex::checkbox(crypt_str("Force crosshair"), &config->visuals.world.force_crosshair);
		imgui_ex::checkbox(crypt_str("Penetration crosshair"), &config->visuals.world.penetration_crosshair);
		imgui_ex::checkbox(crypt_str("Client bullet impacts"), &config->visuals.world.client_bullet_impacts);

		if (config->visuals.world.client_bullet_impacts)
			imgui_ex::color_edit4(crypt_str("##client_bullet_impacts_clr"), config->visuals.world.client_bullet_impacts_clr);

		imgui_ex::checkbox(crypt_str("Server bullet impacts"), &config->visuals.world.server_bullet_impacts);

		if (config->visuals.world.server_bullet_impacts)
			imgui_ex::color_edit4(crypt_str("##server_bullet_impacts_clr"), config->visuals.world.server_bullet_impacts_clr);

		imgui_ex::checkbox(crypt_str("Bullet tracer"), &config->visuals.world.bullet_tracer);

		if (config->visuals.world.bullet_tracer)
			imgui_ex::color_edit4(crypt_str("##bullet_tracer_clr"), config->visuals.world.bullet_tracer_clr);

		imgui_ex::checkbox(crypt_str("Hit sound"), &config->visuals.world.hit_sound);
		imgui_ex::checkbox(crypt_str("Damage marker"), &config->visuals.world.damage_marker);

		if (config->visuals.world.damage_marker)
		{
			imgui_ex::checkbox(crypt_str("Color"), &config->visuals.world.damage_marker_custom_color);
			imgui_ex::color_edit4(crypt_str("##bar_clr"), config->visuals.world.damage_marker_color);
		}

		const char* removals[] = { "Scope", "Zoom", "Smoke", "Flash", "Recoil", "Landing bob", "Postprocessing", "Fog" };
		imgui_ex::mcombo(crypt_str("Removals"), config->visuals.world.removals.data(), removals, IM_ARRAYSIZE(removals));

		const char* skybox[] = { "None", "Baggage", "Tibet", "Clear sky", "Clear sky HD", "Embassy", "Italy", "Daylight 1", "Daylight 2", "Daylight 3", "Daylight 4", "Cloudy", "Night 1", "Night 2", "Night flat", "Day HD", "Day", "Rural", "Vertigo HD", "Vertigo blue HD", "Vertigo", "Vietnam", "Dusty sky", "Jungle", "Nuke", "Office" };
		imgui_ex::combo(crypt_str("Skybox"), &config->visuals.world.skybox, skybox, IM_ARRAYSIZE(skybox));

		imgui_ex::checkbox(crypt_str("Color modulation"), &config->visuals.world.world_color_modulate.world);

		if (config->visuals.world.world_color_modulate.world)
		{
			imgui_ex::text(crypt_str("World color"));
			imgui_ex::color_edit4(crypt_str("##world_color"), config->visuals.world.world_color_modulate.world_clr);

			imgui_ex::text(crypt_str("Props color"));
			imgui_ex::color_edit4(crypt_str("##props_color"), config->visuals.world.world_color_modulate.props_clr);
		}

		ImGui::Spacing();
	}
}
