#include "lua.h"
#include "..\imgui_ex.h"
#include "..\..\Lua\Clua.h"
#include "../../../features/logs.h"
#include "../../../features/features.cpp"

namespace core::tabs::lua
{
	void first_tab()
	{
		if (!Lua_manager)
		{
			imgui_ex::text(crypt_str("Lua manager not found, initializing..."));
			c_lua* new_manager = new c_lua();
			if (new_manager)
			{
				Lua_manager.set(new_manager);
				new_manager->initialize();
			}
			return;
		}

		try {
			auto previous_check_box = false;
			for (auto& current : Lua_manager->scripts)
			{
				int script_id = Lua_manager->get_script_id(current);
				if (script_id < 0 || script_id >= Lua_manager->items.size())
					continue;
				
				auto& items = Lua_manager->items.at(script_id);

				for (auto& item : items)
				{
					std::string item_name;

					auto first_point = false;
					auto item_str = false;

					for (auto& c : item.first)
					{
						if (c == '.')
						{
							if (first_point)
							{
								item_str = true;
								continue;
							}
							else
								first_point = true;
						}

						if (item_str)
							item_name.push_back(c);
					}
					char** arr;
					switch (item.second.type)
					{
					case NEXT_LINE:
						previous_check_box = false;
						break;
					case CHECK_BOX:
						previous_check_box = true;
						imgui_ex::checkbox(item_name.c_str(), &item.second.check_box_value);
						break;
					case COMBO_BOX:
						previous_check_box = false;
						 arr = new char* [item.second.combo_box_labels.size()];
						for (size_t i = 0; i < item.second.combo_box_labels.size(); i++) {
							arr[i] = new char[item.second.combo_box_labels[i].size() + 1];
							strcpy(arr[i], item.second.combo_box_labels[i].c_str());
						}

						imgui_ex::combo(item_name.c_str(), &item.second.combo_box_value, arr, item.second.combo_box_labels.size());
						for (size_t i = 0; i < item.second.combo_box_labels.size(); i++) {
							delete[] arr[i];
						}
						delete[] arr;
						break;
					case SLIDER_INT:
						previous_check_box = false;
						imgui_ex::slider_int(item_name.c_str(), &item.second.slider_int_value, item.second.slider_int_min, item.second.slider_int_max);
						break;
					case SLIDER_FLOAT:
						previous_check_box = false;
						imgui_ex::slider_float(item_name.c_str(), &item.second.slider_float_value, item.second.slider_float_min, item.second.slider_float_max);
						break;
					case COLOR_PICKER:
						if (previous_check_box)
							previous_check_box = false;
						else
							imgui_ex::text((item_name + ' ').c_str());

						ImGui::SameLine();
						imgui_ex::color_edit4((crypt_str("##") + item_name).c_str(), &item.second.color_picker_value);
						break;
					case KEY_BIND:
						if (previous_check_box)
							previous_check_box = false;
						else
							imgui_ex::text((item_name + ' ').c_str());

						ImGui::SameLine();
						imgui_ex::hotkey((crypt_str("##") + item_name).c_str(), item.second.m_bind);
						break;
					case BUTTON:
						previous_check_box = false;

						if (imgui_ex::button(item_name.c_str(), ImVec2(206.0f, 30.0f)))
						{
							//if (item.second.m_callback != sol::nil)
							{
								item.second.m_callback();
							}
						}

						break;
					}
				}
			}
		}
		catch (const std::exception& e) {
			// Log the specific exception
			if (logs)
				logs->add(crypt_str("Lua error in GUI: ") + std::string(e.what()), Color::Red, crypt_str("[ LUA ] "), true);
				
			// Show error in UI
			imgui_ex::text(crypt_str("An error occurred while processing the scripts:"));
			imgui_ex::text(e.what());
		}
		catch (...) {
			// Handle any exceptions that might occur
			if (logs)
				logs->add(crypt_str("Unknown Lua error in GUI"), Color::Red, crypt_str("[ LUA ] "), true);
				
			imgui_ex::text(crypt_str("An error occurred while processing the scripts."));
		}

		ImGui::Spacing();
	}

	void second_tab()
	{
		imgui_ex::checkbox(crypt_str("Developer mode"), &config->scripts.developer_mode);
		imgui_ex::checkbox(crypt_str("Allow file edit"), &config->scripts.allow_file);
		imgui_ex::checkbox(crypt_str("Allow HTTP requests"), &config->scripts.allow_http);
	}
}
