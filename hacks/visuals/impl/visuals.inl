#pragma once
#define max_edict_bits 11

#define max_edicts  ( 1<<max_edict_bits )

#include "../visuals.hpp"

namespace nem::hacks {
	__forceinline float& c_visuals::last_hurt_time( ) { return m_last_hurt_time; }

	__forceinline std::vector< vec3_t >& c_visuals::player_sounds( ) { return m_player_sounds; }

	__forceinline std::vector< c_visuals::bullet_impact_t >& c_visuals::bullet_impacts( ) { return m_bullet_impacts; }
}