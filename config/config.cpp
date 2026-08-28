// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#define ZLIB_WINAPI

#include "config.h"
#include "..\json.hpp"
#include "..\gui\core\core.h"
#include "..\render.h"
#include "..\features\features.h"

#include "..\features\logs.h"
#include <filesystem>
#include <thread>
#include <iomanip>
#include <gzip/compress.hpp>
#include <gzip/config.hpp>
#include <gzip/decompress.hpp>
#include <gzip/utils.hpp>
#include <gzip/version.hpp>
#include "..\Lua\Clua.h"
#include "..\sdk\ImageLoader.h"
#include "base64.h"

crypt_ptr <Config> config;

void Config::initialize() 
{
	//rage
	{
		add_item(&rage.enable, "rage.enable", ITEM_BOOL);
		add_item(&rage.field_of_view, "rage.field_of_view", ITEM_INT);
		add_item(&rage.automatic_fire, "rage.automatic_fire", ITEM_BOOL);
		add_item(&rage.automatic_wall, "rage.automatic_wall", ITEM_BOOL);
		add_item(&rage.double_tap_key, "rage.double_tap_key", ITEM_KEY_BIND);
		add_item(&rage.force_damage_key, "rage.force_damage_key", ITEM_KEY_BIND);
		add_item(&rage.hide_shots_key, "rage.hide_shots_key", ITEM_KEY_BIND);
		add_item(&rage.silent, "rage.silent", ITEM_BOOL);
		
		for (auto i = 0; i < WEAPON_CONFIG_MAX; i++)
		{
			add_item(&rage.weapon[i].automatic_stop, std::to_string(i) + "rage.weapon.automatic_stop", ITEM_BOOL);
			add_item(&rage.weapon[i].body_aim, std::to_string(i) + "rage.weapon.body_aim", ITEM_INT);
			add_item(&rage.weapon[i].body_scale, std::to_string(i) + "rage.weapon.body_scale", ITEM_FLOAT);
			add_item(&rage.weapon[i].double_tap_hit_chance, std::to_string(i) + "rage.weapon.double_tap_hit_chance", ITEM_INT);
			add_item(&rage.weapon[i].extended_teleport, std::to_string(i) + "rage.weapon.extended_teleport", ITEM_BOOL);
			add_item(&rage.weapon[i].force_body_aim_if_lethal, std::to_string(i) + "rage.weapon.force_body_aim_if_lethal", ITEM_BOOL);
			add_item(&rage.weapon[i].force_damage_value, std::to_string(i) + "rage.weapon.force_damage_value", ITEM_INT);
			add_item(&rage.weapon[i].force_safe_points_if_lethal, std::to_string(i) + "rage.weapon.force_safe_points_if_lethal", ITEM_BOOL);
			add_item(&rage.weapon[i].head_scale, std::to_string(i) + "rage.weapon.head_scale", ITEM_FLOAT);
			add_item(&rage.weapon[i].hitboxes, std::to_string(i) + "rage.weapon.hitboxes", ITEM_INT_ARRAY, 6);
			add_item(&rage.weapon[i].hit_chance, std::to_string(i) + "rage.weapon.hit_chance", ITEM_INT);
			add_item(&rage.weapon[i].lag_exploit, std::to_string(i) + "rage.weapon.lag_exploit", ITEM_BOOL);
			add_item(&rage.weapon[i].minimum_damage, std::to_string(i) + "rage.weapon.minimum_damage", ITEM_INT);
			add_item(&rage.weapon[i].modifiers, std::to_string(i) + "rage.weapon.modifiers", ITEM_INT_ARRAY, 3);
			add_item(&rage.weapon[i].safe_hitboxes, std::to_string(i) + "rage.weapon.safe_hitboxes", ITEM_INT_ARRAY, 6);
			add_item(&rage.weapon[i].static_point_scale, std::to_string(i) + "rage.weapon.static_point_scale", ITEM_BOOL);
		}
	}

	//legit
	{
		add_item(&legit.enable, "legit.enable", ITEM_BOOL);
		add_item(&legit.automatic_fire_key, "legit.automatic_fire_key", ITEM_KEY_BIND);
		add_item(&legit.automatic_wall_key, "legit.automatic_wall_key", ITEM_KEY_BIND);
		add_item(&legit.backtrack_limit, "legit.backtrack_limit", ITEM_INT);
		add_item(&legit.checks, "legit.checks", ITEM_INT_ARRAY, 2);
		add_item(&legit.enable_key, "legit.enable_key", ITEM_KEY_BIND);

		for (auto i = 0; i < WEAPON_CONFIG_MAX; i++)
		{
			add_item(&legit.weapon[i].automatic_attack, std::to_string(i) + "legit.weapon.automatic_attack", ITEM_BOOL);
			add_item(&legit.weapon[i].automatic_fire, std::to_string(i) + "legit.weapon.automatic_fire", ITEM_BOOL);
			add_item(&legit.weapon[i].automatic_stop, std::to_string(i) + "legit.weapon.automatic_stop", ITEM_BOOL);
			add_item(&legit.weapon[i].automatic_wall, std::to_string(i) + "legit.weapon.automatic_wall", ITEM_BOOL);
			add_item(&legit.weapon[i].delay, std::to_string(i) + "legit.weapon.delay", ITEM_INT);
			add_item(&legit.weapon[i].field_of_view, std::to_string(i) + "legit.weapon.field_of_view", ITEM_FLOAT);
			add_item(&legit.weapon[i].fire_delay, std::to_string(i) + "legit.weapon.fire_delay", ITEM_INT);
			add_item(&legit.weapon[i].first_shot_delay, std::to_string(i) + "legit.weapon.first_shot_delay", ITEM_INT);
			add_item(&legit.weapon[i].hitboxes, std::to_string(i) + "legit.weapon.hitboxes", ITEM_INT_ARRAY, 6);
			add_item(&legit.weapon[i].hitboxes_priority, std::to_string(i) + "legit.weapon.hitboxes_priority", ITEM_INT_ARRAY, 6);
			add_item(&legit.weapon[i].hit_chance, std::to_string(i) + "legit.weapon.hit_chance", ITEM_INT);
			add_item(&legit.weapon[i].minimum_damage, std::to_string(i) + "legit.weapon.minimum_damage", ITEM_INT);
			add_item(&legit.weapon[i].pitch_recoil, std::to_string(i) + "legit.weapon.pitch_recoil", ITEM_INT);
			add_item(&legit.weapon[i].smooth, std::to_string(i) + "legit.weapon.smooth", ITEM_INT);
			add_item(&legit.weapon[i].smooth_value, std::to_string(i) + "legit.weapon.smooth_value", ITEM_FLOAT);
			add_item(&legit.weapon[i].target_switch_delay, std::to_string(i) + "legit.weapon.target_switch_delay", ITEM_INT);
			add_item(&legit.weapon[i].yaw_recoil, std::to_string(i) + "legit.weapon.yaw_recoil", ITEM_INT);
		}
	}

	//antiaim
	{
		add_item(&anti_aim.enable, "anti_aim.enable", ITEM_BOOL);
		add_item(&anti_aim.desync_range, "anti_aim.desync_range", ITEM_INT);
		add_item(&anti_aim.desync_range_inverted, "anti_aim.desync_range_inverted", ITEM_INT);
		add_item(&anti_aim.desync_type, "anti_aim.desync_type", ITEM_INT);
		add_item(&anti_aim.disable_on_high_velocity, "anti_aim.disable_on_high_velocity", ITEM_BOOL);
		add_item(&anti_aim.enable_fake_lag, "anti_aim.enable_fake_lag", ITEM_BOOL);
		add_item(&anti_aim.fake_duck_key, "anti_aim.fake_duck_key", ITEM_KEY_BIND);
		add_item(&anti_aim.fake_lag_limit, "anti_aim.fake_lag_limit", ITEM_INT);
		add_item(&anti_aim.fake_lag_type, "anti_aim.fake_lag_type", ITEM_INT);
		add_item(&anti_aim.freestanding, "anti_aim.freestanding", ITEM_BOOL);
		add_item(&anti_aim.freestanding_key, "anti_aim.freestanding_key", ITEM_KEY_BIND);
		add_item(&anti_aim.freestanding_yaw_modifier, "anti_aim.freestanding_yaw_modifier", ITEM_INT);
		add_item(&anti_aim.freestanding_yaw_modifier_range, "anti_aim.freestanding_yaw_modifier_range", ITEM_INT);
		add_item(&anti_aim.invert_desync_key, "anti_aim.invert_desync_key", ITEM_KEY_BIND);
		add_item(&anti_aim.leg_movement, "anti_aim.leg_movement", ITEM_INT);
		add_item(&anti_aim.manual_back_key, "anti_aim.manual_back_key", ITEM_KEY_BIND);
		add_item(&anti_aim.manual_forward_key, "anti_aim.manual_forward_key", ITEM_KEY_BIND);
		add_item(&anti_aim.manual_left_key, "anti_aim.manual_left_key", ITEM_KEY_BIND);
		add_item(&anti_aim.manual_right_key, "anti_aim.manual_right_key", ITEM_KEY_BIND);
		add_item(&anti_aim.pitch, "anti_aim.pitch", ITEM_INT);
		add_item(&anti_aim.roll, "anti_aim.roll", ITEM_BOOL);
		add_item(&anti_aim.roll_range, "anti_aim.roll_range", ITEM_INT);
		add_item(&anti_aim.slow_walk_key, "anti_aim.slow_walk_key", ITEM_KEY_BIND);
		add_item(&anti_aim.target_yaw, "anti_aim.target_yaw", ITEM_INT);
		add_item(&anti_aim.yaw_modifier, "anti_aim.yaw_modifier", ITEM_INT);
		add_item(&anti_aim.yaw_modifier_range, "anti_aim.yaw_modifier_range", ITEM_INT);
		add_item(&anti_aim.yaw_offset, "anti_aim.yaw_offset", ITEM_INT);
		add_item(&anti_aim.break_local_animation, "anti_aim.break_local_animation", ITEM_INT_ARRAY, 3);
	}

	//visual
	{
		for (auto i = 0; i < 3; i++)
		{
			add_item(&visuals.player_type[i].chams_enable, std::to_string(i) + "visuals.player.chams_enable", ITEM_BOOL);
			add_item(&visuals.player_type[i].chams_clr_invisible, std::to_string(i) + "visuals.player.chams_clr_invisible", ITEM_FLOAT_COLOR_ARRAY);
			add_item(&visuals.player_type[i].chams_clr_visible, std::to_string(i) + "visuals.player.chams_clr_visible", ITEM_FLOAT_COLOR_ARRAY);
			add_item(&visuals.player_type[i].chams_fake, std::to_string(i) + "visuals.player.chams_fake", ITEM_BOOL);
			add_item(&visuals.player_type[i].chams_fake_modifiers, std::to_string(i) + "visuals.player.chams_fake_modifiers", ITEM_BOOL);
			add_item(&visuals.player_type[i].chams_fake_type, std::to_string(i) + "visuals.player.chams_fake_type", ITEM_INT);
			add_item(&visuals.player_type[i].chams_ghost, std::to_string(i) + "visuals.player.chams_ghost", ITEM_BOOL);
			add_item(&visuals.player_type[i].chams_ghost_clr, std::to_string(i) + "visuals.player.chams_ghost_clr", ITEM_FLOAT_COLOR_ARRAY);
			add_item(&visuals.player_type[i].chams_ghost_modifiers_clr, std::to_string(i) + "visuals.player.chams_ghost_modifiers_clr", ITEM_FLOAT_COLOR_ARRAY);
			add_item(&visuals.player_type[i].chams_ghost_type, std::to_string(i) + "visuals.player.chams_ghost_type", ITEM_INT);
			add_item(&visuals.player_type[i].chams_hand, std::to_string(i) + "visuals.player.chams_hand", ITEM_BOOL);
			add_item(&visuals.player_type[i].chams_hand_clr, std::to_string(i) + "visuals.player.chams_hand_clr", ITEM_FLOAT_COLOR_ARRAY);
			add_item(&visuals.player_type[i].chams_hand_modifiers, std::to_string(i) + "visuals.player.chams_hand_modifiers", ITEM_BOOL);
			add_item(&visuals.player_type[i].chams_hand_modifiers_clr, std::to_string(i) + "visuals.player.chams_hand_modifiers_clr", ITEM_FLOAT_COLOR_ARRAY);
			add_item(&visuals.player_type[i].chams_hand_type, std::to_string(i) + "visuals.player.chams_hand_type", ITEM_INT);
			add_item(&visuals.player_type[i].chams_invisible, std::to_string(i) + "visuals.player.chams_invisible", ITEM_BOOL);
			add_item(&visuals.player_type[i].chams_modifiers_clr_invisible, std::to_string(i) + "visuals.player.chams_modifiers_clr_invisible", ITEM_FLOAT_COLOR_ARRAY);
			add_item(&visuals.player_type[i].chams_modifiers_clr_visible, std::to_string(i) + "visuals.player.chams_modifiers_clr_visible", ITEM_FLOAT_COLOR_ARRAY);
			add_item(&visuals.player_type[i].chams_ragdoll, std::to_string(i) + "visuals.player.chams_ragdoll", ITEM_BOOL);
			add_item(&visuals.player_type[i].chams_shot, std::to_string(i) + "visuals.player.chams_shot", ITEM_BOOL);
			add_item(&visuals.player_type[i].chams_shot_clr, std::to_string(i) + "visuals.player.chams_shot_clr", ITEM_FLOAT_COLOR_ARRAY);
			add_item(&visuals.player_type[i].chams_shot_modifiers, std::to_string(i) + "visuals.player.chams_shot_modifiers", ITEM_BOOL);
			add_item(&visuals.player_type[i].chams_shot_modifiers_clr, std::to_string(i) + "visuals.player.chams_shot_modifiers_clr", ITEM_FLOAT_COLOR_ARRAY);
			add_item(&visuals.player_type[i].chams_shot_type, std::to_string(i) + "visuals.player.chams_shot_type", ITEM_INT);
			add_item(&visuals.player_type[i].chams_type_invisible, std::to_string(i) + "visuals.player.chams_type_invisible", ITEM_INT);
			add_item(&visuals.player_type[i].chams_type_visible, std::to_string(i) + "visuals.player.chams_type_visible", ITEM_INT);
			add_item(&visuals.player_type[i].chams_visible, std::to_string(i) + "visuals.player.chams_visible", ITEM_BOOL);
			add_item(&visuals.player_type[i].chams_weapon, std::to_string(i) + "visuals.player.chams_weapon", ITEM_BOOL);
			add_item(&visuals.player_type[i].chams_weapon_clr, std::to_string(i) + "visuals.player.chams_weapon_clr", ITEM_FLOAT_COLOR_ARRAY);
			add_item(&visuals.player_type[i].chams_weapon_modifiers, std::to_string(i) + "visuals.player.chams_weapon_modifiers", ITEM_BOOL);
			add_item(&visuals.player_type[i].chams_weapon_modifiers_clr, std::to_string(i) + "visuals.player.chams_weapon_modifiers_clr", ITEM_FLOAT_COLOR_ARRAY);
			add_item(&visuals.player_type[i].chams_weapon_type, std::to_string(i) + "visuals.player.chams_weapon_type", ITEM_INT);
			add_item(&visuals.player_type[i].chams_modifiers_arr_visible, std::to_string(i) + "visuals.player.chams_modifiers_arr_visible", ITEM_INT_ARRAY, 3);
			add_item(&visuals.player_type[i].chams_modifiers_arr_invisible, std::to_string(i) + "visuals.player.chams_modifiers_arr_invisible", ITEM_INT_ARRAY, 3);
			add_item(&visuals.player_type[i].chams_shot_modifiers_arr, std::to_string(i) + "visuals.player.chams_shot_modifiers_arr", ITEM_INT_ARRAY, 3);
			add_item(&visuals.player_type[i].chams_ghost_modifiers_arr, std::to_string(i) + "visuals.player.chams_ghost_modifiers_arr", ITEM_INT_ARRAY, 3);
			add_item(&visuals.player_type[i].chams_fake_modifiers_arr, std::to_string(i) + "visuals.player.chams_fake_modifiers_arr", ITEM_INT_ARRAY, 3);
			add_item(&visuals.player_type[i].chams_hand_modifiers_arr, std::to_string(i) + "visuals.player.chams_hand_modifiers_arr", ITEM_INT_ARRAY, 3);
			add_item(&visuals.player_type[i].chams_weapon_modifiers_arr, std::to_string(i) + "visuals.player.chams_weapon_modifiers_arr", ITEM_INT_ARRAY, 3);
			add_item(&visuals.player_type[i].esp_flags_arr, std::to_string(i) + "visuals.player.esp_flags_arr", ITEM_INT_ARRAY, 12);
			add_item(&visuals.player_type[i].esp_weapon_arr, std::to_string(i) + "visuals.player.esp_weapon_arr", ITEM_INT_ARRAY, 2);
			add_item(&visuals.player_type[i].esp_enable, std::to_string(i) + "visuals.player.esp_enable", ITEM_BOOL);
			add_item(&visuals.player_type[i].esp_ammo, std::to_string(i) + "visuals.player.esp_ammo", ITEM_BOOL);
			add_item(&visuals.player_type[i].esp_ammo_clr, std::to_string(i) + "visuals.player.esp_ammo_clr", ITEM_FLOAT_COLOR_ARRAY);
			add_item(&visuals.player_type[i].esp_box, std::to_string(i) + "visuals.player.esp_box", ITEM_BOOL);
			add_item(&visuals.player_type[i].esp_box_clr, std::to_string(i) + "visuals.player.esp_box_clr", ITEM_FLOAT_COLOR_ARRAY);
			add_item(&visuals.player_type[i].esp_flags, std::to_string(i) + "visuals.player.esp_flags", ITEM_BOOL);
			add_item(&visuals.player_type[i].esp_flags_combo_clr, std::to_string(i) + "visuals.player.esp_flags_combo_clr", ITEM_FLOAT_COLOR_ARRAY);
			add_item(&visuals.player_type[i].esp_hp_bar, std::to_string(i) + "visuals.player.esp_hp_bar", ITEM_BOOL);
			add_item(&visuals.player_type[i].esp_hp_bar_color, std::to_string(i) + "visuals.player.esp_hp_bar_color", ITEM_FLOAT_COLOR_ARRAY);
			add_item(&visuals.player_type[i].esp_hp_bar_custom_color, std::to_string(i) + "visuals.player.esp_hp_bar_custom_color", ITEM_BOOL);
			add_item(&visuals.player_type[i].esp_knife_taser_clr, std::to_string(i) + "visuals.player.esp_knife_taser_clr", ITEM_FLOAT_COLOR_ARRAY);
			add_item(&visuals.player_type[i].esp_name, std::to_string(i) + "visuals.player.esp_name", ITEM_BOOL);
			add_item(&visuals.player_type[i].esp_name_clr, std::to_string(i) + "visuals.player.esp_name_clr", ITEM_FLOAT_COLOR_ARRAY);
			add_item(&visuals.player_type[i].esp_skeleton, std::to_string(i) + "visuals.player.esp_skeleton", ITEM_BOOL);
			add_item(&visuals.player_type[i].esp_skeleton_clr, std::to_string(i) + "visuals.player.esp_skeleton_clr", ITEM_FLOAT_COLOR_ARRAY);
			add_item(&visuals.player_type[i].esp_weapon, std::to_string(i) + "visuals.player.esp_weapon", ITEM_BOOL);
			add_item(&visuals.player_type[i].esp_weapon_clr, std::to_string(i) + "visuals.player.esp_weapon_clr", ITEM_FLOAT_COLOR_ARRAY);
			add_item(&visuals.player_type[i].glow_clr, std::to_string(i) + "visuals.player.glow_clr", ITEM_FLOAT_COLOR_ARRAY);
			add_item(&visuals.player_type[i].glow_enable, std::to_string(i) + "visuals.player.glow_enable", ITEM_BOOL);
			add_item(&visuals.player_type[i].glow_type, std::to_string(i) + "visuals.player.glow_type", ITEM_INT);
			add_item(&visuals.player_type[i].layered, std::to_string(i) + "visuals.player.layered", ITEM_BOOL);
			add_item(&visuals.player_type[i].multipoints, std::to_string(i) + "visuals.player.multipoints", ITEM_BOOL);
			add_item(&visuals.player_type[i].sounds, std::to_string(i) + "visuals.player.sounds", ITEM_BOOL);
			add_item(&visuals.player_type[i].sounds_color, std::to_string(i) + "visuals.player.sounds_color", ITEM_FLOAT_COLOR_ARRAY);
			add_item(&visuals.player_type[i].sounds_radius, std::to_string(i) + "visuals.player.sounds_radius", ITEM_INT);
			add_item(&visuals.player_type[i].sounds_time, std::to_string(i) + "visuals.player.sounds_time", ITEM_FLOAT);
			add_item(&visuals.player_type[i].transparency_in_scope, std::to_string(i) + "visuals.player.transparency_in_scope", ITEM_INT);
			add_item(&visuals.player_type[i].visualize_lag, std::to_string(i) + "visuals.player.visualize_lag", ITEM_BOOL);
		}

		add_item(&visuals.agent_changer, "visuals.Agent_changer", ITEM_BOOL);
		add_item(&visuals.player_model_ct, "visuals.Agent_ct", ITEM_INT);
		add_item(&visuals.player_model_t, "visuals.Agent_t", ITEM_INT);
	}

	//world
	{
		add_item(&visuals.world.removals, "visuals.world.removals", ITEM_INT_ARRAY, 8);
		add_item(&visuals.world.bomb_timer, "visuals.world.bomb_timer", ITEM_BOOL);
		add_item(&visuals.world.bullet_tracer, "visuals.world.bullet_tracer", ITEM_BOOL);
		add_item(&visuals.world.bullet_tracer_clr, "visuals.world.bullet_trace_clr", ITEM_FLOAT_COLOR_ARRAY);
		add_item(&visuals.world.client_bullet_impacts, "visuals.world.client_bullet_impacts", ITEM_BOOL);
		add_item(&visuals.world.client_bullet_impacts_clr, "visuals.world.client_bullet_impacts_clr", ITEM_FLOAT_COLOR_ARRAY);
		add_item(&visuals.world.damage_marker, "visuals.world.damage_marker", ITEM_BOOL);
		add_item(&visuals.world.damage_marker_color, "visuals.world.damage_marker_color", ITEM_FLOAT_COLOR_ARRAY);
		add_item(&visuals.world.damage_marker_custom_color, "visuals.world.damage_marker_custom_color", ITEM_BOOL);
		add_item(&visuals.world.force_crosshair, "visuals.world.force_crosshair", ITEM_BOOL);
		add_item(&visuals.world.hit_sound, "visuals.world.hit_sound", ITEM_BOOL);
		add_item(&visuals.world.manual_anti_aim, "visuals.world.manual_anti_aim", ITEM_BOOL);
		add_item(&visuals.world.manual_anti_aim_clr, "visuals.world.manual_anti_aim_clr", ITEM_FLOAT_COLOR_ARRAY);
		add_item(&visuals.world.offscreen_color, "visuals.world.offscreen_color", ITEM_FLOAT_COLOR_ARRAY);
		add_item(&visuals.world.offscreen_color_out, "visuals.world.offscreen_color_out", ITEM_FLOAT_COLOR_ARRAY);
		add_item(&visuals.world.offscreen_distance, "visuals.world.offscreen_distance", ITEM_INT);
		add_item(&visuals.world.offscreen_enable, "visuals.world.offscreen_enable", ITEM_BOOL);
		add_item(&visuals.world.offscreen_fade, "visuals.world.offscreen_fade", ITEM_BOOL);
		add_item(&visuals.world.offscreen_size, "visuals.world.offscreen_size", ITEM_INT);
		add_item(&visuals.world.penetration_crosshair, "visuals.world.penetration_crosshair", ITEM_BOOL);

		add_item(&visuals.world.server_bullet_impacts, "visuals.world.server_bullet_impacts", ITEM_BOOL);
		add_item(&visuals.world.server_bullet_impacts_clr, "visuals.world.server_bullet_impacts_clr", ITEM_FLOAT_COLOR_ARRAY);
		add_item(&visuals.world.skybox, "visuals.world.skybox", ITEM_INT);

		add_item(&visuals.world.world_color_modulate.props_clr, "visuals.world.world_color_modulate.props_clr", ITEM_FLOAT_COLOR_ARRAY);
		add_item(&visuals.world.world_color_modulate.world, "visuals.world.world_color_modulate.world", ITEM_BOOL);
		add_item(&visuals.world.world_color_modulate.world_clr, "visuals.world.world_color_modulate.world_clr", ITEM_FLOAT_COLOR_ARRAY);

		add_item(&visuals.world.grenade_esp.enable, "visuals.world.grenade_esp.enable", ITEM_BOOL);
		add_item(&visuals.world.grenade_esp.box, "visuals.world.grenade_esp.box", ITEM_BOOL);
		add_item(&visuals.world.grenade_esp.box_clr, "visuals.world.grenade_esp.box_clr", ITEM_FLOAT_COLOR_ARRAY);	
		add_item(&visuals.world.grenade_esp.inferno_indicator, "visuals.world.grenade_esp.inferno_indicator", ITEM_BOOL);
		add_item(&visuals.world.grenade_esp.inferno_indicator_clr, "visuals.world.grenade_esp.inferno_indicator_clr", ITEM_FLOAT_COLOR_ARRAY);
		add_item(&visuals.world.grenade_esp.name, "visuals.world.grenade_esp.name", ITEM_BOOL);
		add_item(&visuals.world.grenade_esp.name_clr, "visuals.world.grenade_esp.name_clr", ITEM_FLOAT_COLOR_ARRAY);
		add_item(&visuals.world.grenade_esp.name_types, "visuals.world.grenade_esp.name_types", ITEM_INT_ARRAY, 2);
		add_item(&visuals.world.grenade_esp.prediction, "visuals.world.grenade_esp.prediction", ITEM_BOOL);
		add_item(&visuals.world.grenade_esp.prediction_clr, "visuals.world.grenade_esp.prediction_clr", ITEM_FLOAT_COLOR_ARRAY);
		add_item(&visuals.world.grenade_esp.prediction_last_point_clr, "visuals.world.grenade_esp.prediction_last_point_clr", ITEM_FLOAT_COLOR_ARRAY);
		add_item(&visuals.world.grenade_esp.prediction_points_clr, "visuals.world.grenade_esp.prediction_points_clr", ITEM_FLOAT_COLOR_ARRAY);
		add_item(&visuals.world.grenade_esp.smoke_indicator, "visuals.world.grenade_esp.smoke_indicator", ITEM_BOOL);
		add_item(&visuals.world.grenade_esp.smoke_indicator_clr, "visuals.world.grenade_esp.smoke_indicator_clr", ITEM_FLOAT_COLOR_ARRAY);
		
		for (auto i = 0; i < 3; i++)
		{
			add_item(&visuals.world.weapon_type[i].ammo, std::to_string(i) + "visuals.world.weapon.ammo", ITEM_BOOL);
			add_item(&visuals.world.weapon_type[i].ammo_clr, std::to_string(i) + "visuals.world.weapon.ammo_clr", ITEM_FLOAT_COLOR_ARRAY);
			add_item(&visuals.world.weapon_type[i].ammo_type, std::to_string(i) + "visuals.world.weapon.ammo_type", ITEM_INT_ARRAY, 2);
			add_item(&visuals.world.weapon_type[i].box, std::to_string(i) + "visuals.world.weapon.box", ITEM_BOOL);
			add_item(&visuals.world.weapon_type[i].box_clr, std::to_string(i) + "visuals.world.weapon.box_clr", ITEM_FLOAT_COLOR_ARRAY);
			add_item(&visuals.world.weapon_type[i].chams, std::to_string(i) + "visuals.world.weapon.chams", ITEM_BOOL);
			add_item(&visuals.world.weapon_type[i].chams_clr, std::to_string(i) + "visuals.world.weapon.chams_clr", ITEM_FLOAT_COLOR_ARRAY);
			add_item(&visuals.world.weapon_type[i].chams_modifer, std::to_string(i) + "visuals.world.weapon.chams_modifer", ITEM_BOOL);
			add_item(&visuals.world.weapon_type[i].chams_modifiers_arr, std::to_string(i) + "visuals.world.weapon.box_clr", ITEM_INT_ARRAY, 3);
			add_item(&visuals.world.weapon_type[i].chams_modifiers_clr, std::to_string(i) + "visuals.world.weapon.chams_modifiers_clr", ITEM_FLOAT_COLOR_ARRAY);
			add_item(&visuals.world.weapon_type[i].chams_type, std::to_string(i) + "visuals.world.weapon.chams_type", ITEM_INT);
			add_item(&visuals.world.weapon_type[i].esp, std::to_string(i) + "visuals.world.weapon.esp", ITEM_BOOL);
			add_item(&visuals.world.weapon_type[i].glow, std::to_string(i) + "visuals.world.weapon.glow", ITEM_BOOL);
			add_item(&visuals.world.weapon_type[i].glow_clr, std::to_string(i) + "visuals.world.weapon.glow_clr", ITEM_FLOAT_COLOR_ARRAY);
			add_item(&visuals.world.weapon_type[i].glow_type, std::to_string(i) + "visuals.world.weapon.glow_type", ITEM_INT);
			add_item(&visuals.world.weapon_type[i].icon, std::to_string(i) + "visuals.world.weapon.icon", ITEM_BOOL);
			add_item(&visuals.world.weapon_type[i].icon_clr, std::to_string(i) + "visuals.world.weapon.icon_clr", ITEM_FLOAT_COLOR_ARRAY);
		}
	}

	//misc
	{
		add_item(&misc.adblock, "misc.adblock", ITEM_BOOL);
		add_item(&misc.anti_untrusted, "misc.anti_untrusted", ITEM_BOOL);
		add_item(&misc.aspect_ratio, "misc.aspect_ratio", ITEM_BOOL);
		add_item(&misc.aspect_ratio_value, "misc.aspect_ratio_value", ITEM_FLOAT);
		add_item(&misc.automatic_accept, "misc.automatic_accept", ITEM_BOOL);
		add_item(&misc.automatic_buy, "misc.automatic_buy", ITEM_BOOL);
		add_item(&misc.automatic_jump, "misc.automatic_jump", ITEM_BOOL);
		add_item(&misc.automatic_peek_clr, "misc.automatic_peek_clr", ITEM_FLOAT_COLOR_ARRAY);
		add_item(&misc.automatic_strafe, "misc.automatic_strafe", ITEM_INT);
		add_item(&misc.clan_tag, "misc.clan_tag", ITEM_BOOL);
		add_item(&misc.display_lw_users, "misc.display_lw_users", ITEM_BOOL);
		add_item(&misc.fast_stop, "misc.fast_stop", ITEM_BOOL);
		add_item(&misc.field_of_view, "misc.field_of_view", ITEM_INT);
		add_item(&misc.infinite_duck, "misc.infinite_duck", ITEM_BOOL);
		add_item(&misc.key_binds, "misc.key_binds", ITEM_BOOL);
		add_item(&misc.logs_color, "misc.logs_color", ITEM_FLOAT_COLOR_ARRAY);
		add_item(&misc.preserve_killfeed, "misc.preserve_killfeed", ITEM_BOOL);
		add_item(&misc.primary, "misc.primary", ITEM_INT);
		add_item(&misc.rank_reveal, "misc.rank_reveal", ITEM_BOOL);
		add_item(&misc.secondary, "misc.secondary", ITEM_INT);
		add_item(&misc.smoothing, "misc.smoothing", ITEM_INT);
		add_item(&misc.spectator_list, "misc.spectator_list", ITEM_BOOL);
		add_item(&misc.third_person_distance, "misc.third_person_distance", ITEM_INT);
		add_item(&misc.viewmodel_changer, "misc.viewmodel_changer", ITEM_BOOL);
		add_item(&misc.viewmodel_field_of_view, "misc.viewmodel_field_of_view", ITEM_INT);
		add_item(&misc.viewmodel_roll, "misc.viewmodel_roll", ITEM_INT);
		add_item(&misc.viewmodel_x, "misc.viewmodel_x", ITEM_INT);
		add_item(&misc.viewmodel_y, "misc.viewmodel_y", ITEM_INT);
		add_item(&misc.viewmodel_z, "misc.viewmodel_z", ITEM_INT);
		add_item(&misc.watermark, "misc.watermark", ITEM_BOOL);
		add_item(&misc.edge_jump_key, "misc.edge_jump_key", ITEM_KEY_BIND);
		add_item(&misc.automatic_peek, "misc.automatic_peek", ITEM_INT_ARRAY, 2);
		add_item(&misc.logs_position, "misc.logs_position", ITEM_INT_ARRAY, 2);
		add_item(&misc.bypasses, "misc.bypasses", ITEM_INT_ARRAY, 3);
		add_item(&misc.others, "misc.others", ITEM_INT_ARRAY, 8);
		add_item(&misc.third_person_key, "misc.third_person_key", ITEM_KEY_BIND);
		add_item(&misc.automatic_peek_key, "misc.automatic_peek_key", ITEM_KEY_BIND);
		add_item(&misc.logs, "misc.logs", ITEM_INT_ARRAY, 4);
	}
}

void Config::save(std::string config)
{
	std::string folder, file;

	auto get_dir = [&folder, &file, &config]() -> void
	{
		static TCHAR path[MAX_PATH];

		if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, NULL, path)))
		{
			folder = std::string(path) + crypt_str("\\legendware\\Configs\\");
			file = std::string(path) + crypt_str("\\legendware\\Configs\\") + config;
		}

		std::filesystem::create_directories(folder);
	};

	get_dir();
	nlohmann::json allJson;

	for (auto it : items)
	{
		nlohmann::json j;

		j[crypt_str("name")] = it.second.name;
		j[crypt_str("type")] = it.second.type;
		
		if (it.second.type == ITEM_BOOL)
			j[crypt_str("value")] = *(bool*)it.second.pointer.get();
		else if (it.second.type == ITEM_INT)
			j[crypt_str("value")] = *(int*)it.second.pointer.get();
		else if (it.second.type == ITEM_FLOAT)
			j[crypt_str("value")] = *(float*)it.second.pointer.get();
		else if (it.second.type == ITEM_KEY_BIND)
		{
			auto k = *(KeyBind*)(it.second.pointer.get());

			std::vector <int> a = { k.mode, k.key };
			nlohmann::json ja;

			for (auto& i : a)
				ja.push_back(i);

			j[crypt_str("value")] = ja.dump();
		}
		else if (it.second.type == ITEM_INT_ARRAY)
		{
			auto& ptr = *(std::vector<int>*)(it.second.pointer.get());
			nlohmann::json ja;

			for (auto& i : ptr)
				ja.push_back(i);

			j[crypt_str("value")] = ja.dump();
		}
		else if (it.second.type == ITEM_FLOAT_COLOR_ARRAY)
		{
			auto c = (float*)(it.second.pointer.get());

			std::vector<float> a = { c[0], c[1], c[2], c[3]};
			nlohmann::json ja;

			for (auto& i : a)
				ja.push_back(i);

			j[crypt_str("value")] = ja.dump();
		}

		allJson.push_back(j);
	}

	std::string data;

	Base64 base64;
	base64.encode(allJson.dump(), &data);

	std::ofstream ofs;
	ofs.open(file + '\0', std::ios::out | std::ios::trunc);

	ofs << std::setw(4) << data << std::endl;
	ofs.close();
}

void Config::load(std::string config)
{
	std::string folder, file;

	auto get_dir = [&folder, &file, &config]() ->void
	{
		static TCHAR path[MAX_PATH];

		if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, NULL, path)))
		{
			folder = std::string(path) + crypt_str("\\legendware\\Configs\\");
			file = std::string(path) + crypt_str("\\legendware\\Configs\\") + config;
		}

		std::filesystem::create_directories(folder);
	};

	get_dir();
	std::string data;

	std::ifstream ifs;
	ifs.open(file + '\0');

	ifs >> data;
	ifs.close();

	if (data.empty())
		return;

	Base64 base64;

	std::string decoded_data;
	base64.decode(data, &decoded_data);

	std::ofstream ofs;
	ofs.open(file + '\0', std::ios::out | std::ios::trunc);

	ofs << decoded_data;
	ofs.close();

	nlohmann::json allJson;

	std::ifstream ifs_final;
	ifs_final.open(file + '\0');

	ifs_final >> allJson;
	ifs_final.close();

	base64.encode(allJson.dump(), &data);

	std::ofstream final_ofs;
	final_ofs.open(file + '\0', std::ios::out | std::ios::trunc);

	final_ofs << data;
	final_ofs.close();

	for (auto it = allJson.begin(); it != allJson.end(); ++it)
	{
		nlohmann::json j = *it;

		std::string name = j[crypt_str("name")];
		int type = j[crypt_str("type")].get<int>();
		
		auto item = items.at(name);
		
		if (type == ITEM_INT)
			*(int*)item.pointer.get() = j[crypt_str("value")].get<int>(); //-V206
		else if (type == ITEM_FLOAT)
			*(float*)item.pointer.get() = j[crypt_str("value")].get<float>();
		else if (type == ITEM_BOOL)
			*(bool*)item.pointer.get() = j[crypt_str("value")].get<bool>();
		else if (type == ITEM_KEY_BIND)
		{
			std::vector<int> a;
			nlohmann::json ja = nlohmann::json::parse(j[crypt_str("value")].get<std::string>().c_str());

			for (nlohmann::json::iterator it = ja.begin(); it != ja.end(); ++it)
				a.push_back(*it);

			*(KeyBind*)item.pointer.get() = KeyBind(name, (int)a[0], DEPENDENCE_NONE, (int)a[1]);
		}
		else if (type == ITEM_FLOAT_COLOR_ARRAY)
		{
			std::vector<float> a;
			nlohmann::json ja = nlohmann::json::parse(j[crypt_str("value")].get<std::string>().c_str());

			for (nlohmann::json::iterator it = ja.begin(); it != ja.end(); ++it)
				a.push_back(*it);

			memcpy(item.pointer.get(), a.data(), sizeof(float) * 4);
		}
		else if (type == ITEM_INT_ARRAY)
		{
			auto ptr = static_cast<std::vector <int>*> (item.pointer.get());
			ptr->clear();

			nlohmann::json ja = nlohmann::json::parse(j[crypt_str("value")].get<std::string>().c_str());

			for (nlohmann::json::iterator it = ja.begin(); it != ja.end(); ++it)
				ptr->push_back(*it);
		}
	}
}

void Config::remove(std::string config)
{
	std::string folder, file;

	auto get_dir = [&folder, &file, &config]() -> void
	{
		static TCHAR path[MAX_PATH];

		if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, NULL, path)))
		{
			folder = std::string(path) + crypt_str("\\legendware\\Configs\\");
			file = std::string(path) + crypt_str("\\legendware\\Configs\\") + config;
		}

		std::filesystem::create_directories(folder);
	};

	get_dir();

	std::string path = file + '\0';
	std::remove(path.c_str());
}

void Config::config_files()
{
	std::string folder;

	auto get_dir = [&folder]() -> void
	{
		static TCHAR path[MAX_PATH];

		if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, NULL, path)))
			folder = std::string(path) + crypt_str("\\legendware\\Configs\\");

		std::filesystem::create_directories(folder);
	};

	get_dir();
	files.clear();

	std::string path = folder + crypt_str("/*");
	WIN32_FIND_DATA fd;

	HANDLE hFind = FindFirstFile(path.c_str(), &fd);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				files.push_back(fd.cFileName);
		} while (FindNextFile(hFind, &fd));

		FindClose(hFind);
	}
}


void Config::add_item(void* pointer, const string& name, int type, int array_size, bool save, bool show) 
{
	items.emplace(name, ConfigItem(name, pointer, type, array_size, save, show));

	if (type == ITEM_INT_ARRAY)
	{
		auto vec_ptr = static_cast<std::vector <int>*> (pointer);
		vec_ptr->clear();
		//vec_ptr->reserve(array_size);

		for (int i = 0; i < array_size; i++)
			vec_ptr->push_back(FALSE);
	}
}


