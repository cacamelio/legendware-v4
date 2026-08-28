// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "features.h"
#include "visuals.h"
#include "aim.h"
#include "penetration.h"
#include "exploits.h"
#include "movement.h"
#include "..\config\config.h"
#include "..\ImGui Render\ImGUI_Renderer.h"

void Visuals::run()
{
	if (!ctx->local()->valid())
		return;

	damage_marker();
	automatic_peek();
	manual_anti_aim();
	scope_lines();
	crosshair();
	field_of_view_circle();
}

void Visuals::crosshair()
{
	if (!config->visuals.world.penetration_crosshair)
		return;

	auto color = Color::Red;

	if (ctx->weapon_data() && ctx->weapon()->can_fire())
	{
		Vector view_angles;
		engine->GetViewAngles(view_angles);

		Vector direction;
		math::angle_vectors(view_angles, &direction, nullptr, nullptr);

		CGameTrace trace;
		CTraceFilter filter;
		Ray_t ray;

		ray.Init(ctx->shoot_position, ctx->shoot_position + direction * ctx->weapon_data()->range);
		filter.pSkip = ctx->local().get();

		enginetrace->TraceRay(ray, MASK_SHOT_HULL | CONTENTS_HITBOX, &filter, &trace);

		if (trace.fraction < 1.0f) //-V550
		{
			auto penetration_info = penetration->run(ctx->shoot_position, ctx->shoot_position + direction * ctx->weapon_data()->range, nullptr, true);

			if (!penetration_info.visible)
				color = Color::Green;
		}
	}

	renderer_imgui.RenderBoxFilled(render.width / 2 - 1, render.height / 2 - 1, render.width / 2 + 2, render.height / 2 + 2, color);
	renderer_imgui.RenderBox(render.width / 2 - 2, render.height / 2 - 2, render.width / 2 + 3, render.height / 2 + 3, Color::Black);
}

void Visuals::damage_marker()
{
	if (!config->visuals.world.damage_marker)
		return;

	if (ctx->damage_marker.empty())
		return;

	while (globals->curtime - ctx->damage_marker.back().time > 2.0f)
	{
		ctx->damage_marker.pop_back();

		if (ctx->damage_marker.empty())
			return;
	}

	for (auto& damage_marker : ctx->damage_marker)
	{
		Vector screen;

		if (!render->world_to_screen(damage_marker.position, screen))
			continue;

		damage_marker.position.z += (2.0f - (globals->curtime - damage_marker.time)) * globals->frametime * 30.0f;
		damage_marker.color.SetAlpha((int)((2.0f - (globals->curtime - damage_marker.time)) * 127.5f));

		renderer_imgui.RenderText(to_string(damage_marker.damage), ImVec2(screen.x, screen.y), u::dpi(12.0f), damage_marker.color, true);
	}
}

void Visuals::automatic_peek()
{
	if (ctx->automatic_peek_position.IsZero())
		return;

	auto delta = ctx->automatic_peek_position - ctx->local()->m_vecOrigin();
	auto retreating = delta.Length2D() >= 10.0f;

	if (ctx->automatic_peek)
		ctx->automatic_peek_radius = clamp(ctx->automatic_peek_radius + globals->frametime * 50.0f, 0.0f, 15.0f);
	else if (ctx->automatic_peek_radius != 0.0f)
		ctx->automatic_peek_radius = clamp(ctx->automatic_peek_radius - globals->frametime * 50.0f, 0.0f, 15.0f);

	auto filled_color = retreating && movement_system->holding_automatic_peek ? Color::Green : Color(config->misc.automatic_peek_clr);
	auto color = retreating && movement_system->holding_automatic_peek ? Color::Green : Color(config->misc.automatic_peek_clr);

	filled_color.SetAlpha((int)(config->misc.automatic_peek_clr[3] * 127.5f));
	color.SetAlpha((int)(config->misc.automatic_peek_clr[3] * 255.0f));

	renderer_imgui.RenderCircle3DFilled(ctx->automatic_peek_position, 144, ctx->automatic_peek_radius, filled_color);
	renderer_imgui.RenderCircle3D(ctx->automatic_peek_position, 144, ctx->automatic_peek_radius, color);
	renderer_imgui.RenderCircle3DShadow(ctx->automatic_peek_position, 144, ctx->automatic_peek_radius, color, 50.0f);
}

void Visuals::manual_anti_aim()
{
	if (!config->anti_aim.enable)
		return;

	if (!config->visuals.world.manual_anti_aim)
		return;

	if (config->anti_aim.manual_forward_key.state)
		renderer_imgui.RenderTriangleFilled((float)render.width / 2.0f, (float)render.height / 2.0f - 80.0f, (float)render.width / 2.0f - 10.0f, (float)render.height / 2.0f - 60.0f, (float)render.width / 2.0f + 10.0f, (float)render.height / 2.0f - 60.0f, Color(config->visuals.world.manual_anti_aim_clr[0], config->visuals.world.manual_anti_aim_clr[1], config->visuals.world.manual_anti_aim_clr[2], config->visuals.world.manual_anti_aim_clr[3]));

	if (config->anti_aim.manual_back_key.state)
		renderer_imgui.RenderTriangleFilled((float)render.width / 2.0f, (float)render.height / 2.0f + 80.0f, (float)render.width / 2.0f - 10.0f, (float)render.height / 2.0f + 60.0f, (float)render.width / 2.0f + 10.0f, (float)render.height / 2.0f + 60.0f, Color(config->visuals.world.manual_anti_aim_clr[0], config->visuals.world.manual_anti_aim_clr[1], config->visuals.world.manual_anti_aim_clr[2], config->visuals.world.manual_anti_aim_clr[3]));

	if (config->anti_aim.manual_left_key.state)
		renderer_imgui.RenderTriangleFilled((float)render.width / 2.0f - 55.0f, (float)render.height / 2.0f + 10.0f, (float)render.width / 2.0f - 75.0f, (float)render.height / 2.0f, (float)render.width / 2.0f - 55.0f, (float)render.height / 2.0f - 10.0f, Color(config->visuals.world.manual_anti_aim_clr[0], config->visuals.world.manual_anti_aim_clr[1], config->visuals.world.manual_anti_aim_clr[2], config->visuals.world.manual_anti_aim_clr[3]));

	if (config->anti_aim.manual_right_key.state)
		renderer_imgui.RenderTriangleFilled((float)render.width / 2.0f + 55.0f, (float)render.height / 2.0f - 10.0f, (float)render.width / 2.0f + 75.0f, (float)render.height / 2.0f, (float)render.width / 2.0f + 55.0f, (float)render.height / 2.0f + 10.0f, Color(config->visuals.world.manual_anti_aim_clr[0], config->visuals.world.manual_anti_aim_clr[1], config->visuals.world.manual_anti_aim_clr[2], config->visuals.world.manual_anti_aim_clr[3]));
}

void Visuals::scope_lines()
{
	if (!config->visuals.world.removals[REMOVALS_SCOPE])
		return;

	if (!ctx->local()->m_bIsScoped())
		return;

	auto valid_weapon = true;

	if (ctx->weapon() && (ctx->weapon()->m_iItemDefinitionIndex() == WEAPON_AUG || ctx->weapon()->m_iItemDefinitionIndex() == WEAPON_SG553))
		valid_weapon = false;

	if (!valid_weapon && !input->m_fCameraInThirdPerson)
		return;

	renderer_imgui.RenderLine(render.width / 2, 0, render.width / 2, render.height, Color::Black);
	renderer_imgui.RenderLine(0, render.height / 2, render.width, render.height / 2, Color::Black);
}

void Visuals::field_of_view_circle()
{
	if (!config->legit.enable)
		return;

	if (!core::s::is_opened)
		return;

	int width, height;
	engine->GetScreenSize(width, height);

	auto aim_field_of_view_radians = DirectX::XMConvertToRadians(config->legit.weapon[ctx->weapon_config].field_of_view * 0.8f);
	auto view_field_of_view_radians = DirectX::XMConvertToRadians(ctx->field_of_view);

	auto radius = tan(aim_field_of_view_radians * 0.5f) / tan(view_field_of_view_radians * 0.5f) * (float)width;

	if (radius <= 0.0f)
		return;

	renderer_imgui.RenderCircleFilled((float)width * 0.5f, (float)height * 0.5f, radius, 144, Color(255, 255, 255, 127));
}

static const char* player_model_index_agent[] =
{
	crypt_str("models/player/custom_player/legacy/ctm_diver_varianta.mdl"), // Cmdr. Davida 'Goggles' Fernandez | SEAL Frogman
	crypt_str("models/player/custom_player/legacy/ctm_diver_variantb.mdl"), // Cmdr. Frank 'Wet Sox' Baroud | SEAL Frogman"models/player/custom_player/legacy/ctm_diver_variantc.mdl", // Lieutenant Rex Krikey | SEAL Frogman
	crypt_str("models/player/custom_player/legacy/ctm_fbi_varianth.mdl"), // Michael Syfers | FBI Sniper
	crypt_str("models/player/custom_player/legacy/ctm_fbi_variantf.mdl"), // Operator | FBI SWAT
	crypt_str("models/player/custom_player/legacy/ctm_fbi_variantb.mdl"), // Special Agent Ava | FBI
	crypt_str("models/player/custom_player/legacy/ctm_fbi_variantg.mdl"), // Markus Delrow | FBI HRT
	crypt_str("models/player/custom_player/legacy/ctm_gendarmerie_varianta.mdl"), // Sous-Lieutenant Medic | Gendarmerie Nationale
	crypt_str("models/player/custom_player/legacy/ctm_gendarmerie_variantb.mdl"), // Chem-Haz Capitaine | Gendarmerie Nationale
	crypt_str("models/player/custom_player/legacy/ctm_gendarmerie_variantc.mdl"), // Chef d'Escadron Rouchard | Gendarmerie Nationale
	crypt_str("models/player/custom_player/legacy/ctm_gendarmerie_variantd.mdl"), // Aspirant | Gendarmerie Nationale
	crypt_str("models/player/custom_player/legacy/ctm_gendarmerie_variante.mdl"), // Officer Jacques Beltram | Gendarmerie Nationale
	crypt_str("models/player/custom_player/legacy/ctm_sas_variantg.mdl"), // D Squadron Officer | NZSAS
	crypt_str("models/player/custom_player/legacy/ctm_sas_variantf.mdl"), // B Squadron Officer | SAS
	crypt_str("models/player/custom_player/legacy/ctm_st6_variante.mdl"), // Seal Team 6 Soldier | NSWC SEAL
	crypt_str("models/player/custom_player/legacy/ctm_st6_variantg.mdl"), // Buckshot | NSWC SEAL
	crypt_str("models/player/custom_player/legacy/ctm_st6_varianti.mdl"), // Lt. Commander Ricksaw | NSWC SEAL
	crypt_str("models/player/custom_player/legacy/ctm_st6_variantj.mdl"), // 'Blueberries' Buckshot | NSWC SEAL
	crypt_str("models/player/custom_player/legacy/ctm_st6_variantk.mdl"), // 3rd Commando Company | KSK
	crypt_str("models/player/custom_player/legacy/ctm_st6_variantl.mdl"), // 'Two Times' McCoy | TACP Cavalry
	crypt_str("models/player/custom_player/legacy/ctm_st6_variantm.mdl"), // 'Two Times' McCoy | USAF TACP
	crypt_str("models/player/custom_player/legacy/ctm_st6_variantn.mdl"), // Primeiro Tenente | Brazilian 1st Battalion
	crypt_str("models/player/custom_player/legacy/ctm_swat_variante.mdl"), // Cmdr. Mae 'Dead Cold' Jamison | SWAT
	crypt_str("models/player/custom_player/legacy/ctm_swat_variantf.mdl"), // 1st Lieutenant Farlow | SWAT
	crypt_str("models/player/custom_player/legacy/ctm_swat_variantg.mdl"), // John 'Van Healen' Kask | SWAT
	crypt_str("models/player/custom_player/legacy/ctm_swat_varianth.mdl"), // Bio-Haz Specialist | SWAT
	crypt_str("models/player/custom_player/legacy/ctm_swat_varianti.mdl"), // Sergeant Bombson | SWAT
	crypt_str("models/player/custom_player/legacy/ctm_swat_variantj.mdl"), // Chem-Haz Specialist | SWAT
	crypt_str("models/player/custom_player/legacy/ctm_swat_variantk.mdl"), // Lieutenant 'Tree Hugger' Farlow | SWAT
	crypt_str("models/player/custom_player/legacy/tm_professional_varj.mdl"), // Getaway Sally | The Professionals
	crypt_str("models/player/custom_player/legacy/tm_professional_vari.mdl"), // Number K | The Professionals
	crypt_str("models/player/custom_player/legacy/tm_professional_varh.mdl"), // Little Kev | The Professionals
	crypt_str("models/player/custom_player/legacy/tm_professional_varg.mdl"), // Safecracker Voltzmann | The Professionals
	crypt_str("models/player/custom_player/legacy/tm_professional_varf5.mdl"), // Bloody Darryl The apped | The Professionals
	crypt_str("models/player/custom_player/legacy/tm_professional_varf4.mdl"), // Sir Bloody Loudmouth Darryl | The Professionals
	crypt_str("models/player/custom_player/legacy/tm_professional_varf3.mdl"), // Sir Bloody Darryl Royale | The Professionals
	crypt_str("models/player/custom_player/legacy/tm_professional_varf2.mdl"), // Sir Bloody Skullhead Darryl | The Professionals
	crypt_str("models/player/custom_player/legacy/tm_professional_varf1.mdl"), // Sir Bloody Silent Darryl | The Professionals
	crypt_str("models/player/custom_player/legacy/tm_professional_varf.mdl"), // Sir Bloody Miami Darryl | The Professionals
	crypt_str("models/player/custom_player/legacy/tm_phoenix_varianti.mdl"), // crypt_street Soldier | Phoenix
	crypt_str("models/player/custom_player/legacy/tm_phoenix_varianth.mdl"), // Soldier | Phoenix
	crypt_str("models/player/custom_player/legacy/tm_phoenix_variantg.mdl"), // Slingshot | Phoenix
	crypt_str("models/player/custom_player/legacy/tm_phoenix_variantf.mdl"), // Enforcer | Phoenix
	crypt_str("models/player/custom_player/legacy/tm_leet_variantj.mdl"), // Mr. Muhlik | Elite Crew
	crypt_str("models/player/custom_player/legacy/tm_leet_varianti.mdl"), // Prof. Shahmat | Elite Crew
	crypt_str("models/player/custom_player/legacy/tm_leet_varianth.mdl"), // Osiris | Elite Crew
	crypt_str("models/player/custom_player/legacy/tm_leet_variantg.mdl"), // Ground Rebel | Elite Crew
	crypt_str("models/player/custom_player/legacy/tm_leet_variantf.mdl"), // The Elite Mr. Muhlik | Elite Crew
	crypt_str("models/player/custom_player/legacy/tm_jungle_raider_variantf2.mdl"), // Trapper | Guerrilla Warfare
	crypt_str("models/player/custom_player/legacy/tm_jungle_raider_variantf.mdl"), // Trapper Aggressor | Guerrilla Warfare
	crypt_str("models/player/custom_player/legacy/tm_jungle_raider_variante.mdl"), // Vypa Sista of the Revolution | Guerrilla Warfare
	crypt_str("models/player/custom_player/legacy/tm_jungle_raider_variantd.mdl"), // Col. Mangos Dabisi | Guerrilla Warfare
	crypt_str("models/player/custom_player/legacy/tm_jungle_raider_variantñ.mdl"), // Arno The Overgrown | Guerrilla Warfare
	crypt_str("models/player/custom_player/legacy/tm_jungle_raider_variantb2.mdl"), // 'Medium Rare' Crasswater | Guerrilla Warfare
	crypt_str("models/player/custom_player/legacy/tm_jungle_raider_variantb.mdl"), // Crasswater The Forgotten | Guerrilla Warfare
	crypt_str("models/player/custom_player/legacy/tm_jungle_raider_varianta.mdl"), // Elite Trapper Solman | Guerrilla Warfare
	crypt_str("models/player/custom_player/legacy/tm_balkan_varianth.mdl"), // 'The Doctor' Romanov | Sabre
	crypt_str("models/player/custom_player/legacy/tm_balkan_variantj.mdl"), // Blackwolf | Sabre
	crypt_str("models/player/custom_player/legacy/tm_balkan_varianti.mdl"), // Maximus | Sabre
	crypt_str("models/player/custom_player/legacy/tm_balkan_variantf.mdl"), // Dragomir | Sabre
	crypt_str("models/player/custom_player/legacy/tm_balkan_variantg.mdl"), // Rezan The Ready | Sabre
	crypt_str("models/player/custom_player/legacy/tm_jumpsuit_varianta.mdl"),//denger zone mila
	crypt_str("models/player/custom_player/legacy/tm_jumpsuit_variantb.mdl"),//denger zone choi
	crypt_str("models/player/custom_player/legacy/tm_jumpsuit_variantc.mdl"),//denger zone lysiy
	crypt_str("models/player/custom_player/legacy/tm_pirate_varianta.mdl"),//pirate
	crypt_str("models/player/custom_player/legacy/tm_anarchist_varianta.mdl"),//anarhist
	crypt_str("models/player/custom_player/legacy/tm_professional_var1.mdl"),//putin
	crypt_str("models/player/custom_player/night_fighter/putin/putin.mdl")
};

void Visuals::agent_changer() 
{
	if (!ctx->local())
		return;

	static auto backup_model_index = -1;

	if (config->visuals.agent_changer)
	{
		const char** player_model_index = nullptr;
		auto player_model = 0;

		switch (ctx->local()->m_iTeamNum())
		{
		case 2:
			player_model_index = player_model_index_agent;
			player_model = config->visuals.player_model_t;
			break;
		case 3:
			player_model_index = player_model_index_agent;
			player_model = config->visuals.player_model_ct;
			break;
		}

		if (player_model)
		{
			if (!ctx->backup_model)
			{
				auto model = ctx->local()->GetModel();

				if (model)
				{
					auto studio_model = modelinfo->GetStudioModel(model);

					if (studio_model)
					{
						auto name = crypt_str("models/") + (std::string)studio_model->szName;
						backup_model_index = modelinfo->GetModelIndex(name.c_str());
					}
				}
			}

			if (player_model_indexes.find(player_model_index[player_model - 1]) == player_model_indexes.end()) //-V522
				player_model_indexes.emplace(player_model_index[player_model - 1], modelinfo->GetModelIndex(player_model_index[player_model - 1]));

			ctx->local()->set_model_index(player_model_indexes[player_model_index[player_model - 1]]);
			ctx->backup_model = true;
		}
		else if (ctx->backup_model)
		{
			ctx->local()->set_model_index(backup_model_index);
			ctx->backup_model = false;
		}
	}
}