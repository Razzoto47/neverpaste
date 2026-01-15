#include "../../nem.hpp"

enum e_lua_fonts
{
	e_museo_sans,
	e_tahoma,
	e_segoe_ui,
	e_04B03
};


namespace renderer
{
	vec3_t world_to_screen ( const vec3_t& world ) {

		vec3_t to;

		if ( !render::world_to_screen ( world, to ) )
			return vec3_t ( );

		return to;
	}

	void text ( float x, float y, col_t clr, const std::string_view text, int font_, bool outline ) { 

		ImFont* font = nem::hacks::g_visuals->m_fonts.m_skeet_font_esp;

		switch ( font_ )
		{
			case e_museo_sans:
			{
				font = nem::hacks::g_visuals->m_fonts.m_museo_sans_name;
				break;
			}
			case e_tahoma:
			{
				font = nem::hacks::g_visuals->m_fonts.m_tahoma14;
				break;
			}
			case e_segoe_ui:
			{
				font = nem::hacks::g_visuals->m_fonts.m_segoe_ui_esp;
				break;
			}
			case e_04B03:
			{
				font = nem::hacks::g_visuals->m_fonts.m_skeet_font_esp;
				break;
			}
			default:
				break;
		}

		render::text ( text, vec2_t ( x, y ), clr, font, outline ? FONT_OUTLINE : FONT_NONE );
	}

	void draw_line ( float x, float y, float x_1, float y_1, col_t clr ) {
		render::draw_line ( x, y, x_1, y_1, clr );
	}

	void draw_rect ( float x, float y, float x_1, float y_1, col_t clr ) {
		render::draw_rect ( x, y, x_1, y_1, clr );
	}

	void draw_rect_filled ( float x, float y, float w, float h, col_t clr, float rounding ) {
		render::draw_rect_filled ( x, y, w, h, clr, rounding );
	}
}

namespace misc_
{
	bool get_double_tap_state ( )
	{
		if ( nem::hacks::g_aim_bot->cfg ( ).m_bDoubleTap )
			return true;

		return false;
	}

	bool get_hide_shots_state ( )
	{
		if ( nem::hacks::g_aim_bot->cfg ( ).m_bHideShots )
			return true;

		return false;
	}

	bool get_roll_extension_state ( )
	{
		if ( nem::hacks::g_aim_bot->cfg ( ).m_bRollEnabled )
			return true;

		return false;
	}

	bool get_slow_walk_state ( )
	{
		if ( nem::hacks::g_aim_bot->cfg ( ).m_bSlowWalk )
			return true;

		return false;
	}

	bool get_third_person_state ( )
	{
		if ( nem::hacks::g_aim_bot->cfg ( ).m_bThirdPerson )
			return true;

		return false;
	}

	bool get_dmg_override_state ( ) {
		if ( nem::hacks::g_aim_bot->cfg ( ).m_bOverrideMinDamage )
			return true;

		return false;
	}

	bool get_flipped_state ( ) { 
		if ( nem::hacks::g_aim_bot->cfg ( ).m_bInverter )
			return true;

		return false;
	}

	float get_screen_width ( ) {
		int x, y;

		valve___g_engine->get_screen_size ( x, y );

		return x;
	}

	float get_screen_height ( )
	{
		int x, y;

		valve___g_engine->get_screen_size ( x, y );

		return y;
	}
}

namespace anti_aims_
{
	void change_jitter_value ( float val ) {
		nem::hacks::g_aim_bot->cfg ( ).m_iJitterAmount = val;
	}

	void change_desync_value ( float val ) {
		nem::hacks::g_aim_bot->cfg ( ).m_iDesyncDelta = val;
	}

	void change_roll_value ( float val ) {
		nem::hacks::g_aim_bot->cfg ( ).m_iRollLimit = val;
	}

	void change_fake_lags_value ( int val ) {
		nem::hacks::g_aim_bot->cfg ( ).m_iFakeLagsLimit = val;
	} 

	float desync_delta ( ) {
		//return nem::valve::g_local_player->max_delta ( ) * ( nem::hacks::g_anti_aim->cfg ( ).m_desync_limit / nem::valve::g_local_player->max_delta ( ) );
		return 58.f;
	}
}

namespace nem {
	void c_lua::init( ) {
		m_state.open_libraries(
			sol::lib::base, sol::lib::string,
			sol::lib::table, sol::lib::math,
			sol::lib::debug, sol::lib::bit32,
			sol::lib::ffi, sol::lib::package
		);

		m_state.new_usertype< vec3_t >(
			( "vector" ),
			sol::constructors< vec3_t( ), vec3_t( float, float, float ) >( ),
			std::string_view{ ( "x" ) }, &vec3_t::x,
			std::string_view{ ( "y" ) }, &vec3_t::y,
			std::string_view{ ( "z" ) }, &vec3_t::z,
			std::string_view{ ( "length" ) }, &vec3_t::length,
			std::string_view{ ( "length_sqr" ) }, &vec3_t::length_sqr,
			std::string_view{ ( "length_2d" ) }, &vec3_t::length_2d,
			std::string_view{ ( "length_sqr_2d" ) }, &vec3_t::length_sqr_2d,
			std::string_view{ ( "normalize" ) }, &vec3_t::normalize
		);

		m_state.new_usertype <col_t> (  ( "color" ), sol::constructors <col_t ( ), col_t ( int, int, int ), col_t ( int, int, int, int )> ( ),
			( std::string ) ( "r" ), &col_t::r,
			( std::string ) ( "g" ), &col_t::g,
			( std::string ) ( "b" ), &col_t::b,
			( std::string ) ( "a" ), &col_t::a
			);

		m_state.new_usertype< valve::cvar_t >(
			( "con_var" ),
			std::string_view{ ( "get_int" ) }, &valve::cvar_t::get_int,
			std::string_view{ ( "get_float" ) }, &valve::cvar_t::get_float,
			std::string_view{ ( "get_string" ) }, &valve::cvar_t::get_str,
			std::string_view{ ( "set_int" ) }, &valve::cvar_t::set_int,
			std::string_view{ ( "set_float" ) }, &valve::cvar_t::set_float,
			std::string_view{ ( "set_string" ) }, &valve::cvar_t::set_str
		);
		
		m_state.new_usertype< lua_user_cmd_t >(
			( "user_cmd" ),
			std::string_view{ ( "cmd_number" ) }, &lua_user_cmd_t::m_cmd_number,
			std::string_view{  ( "tick_count" ) }, &lua_user_cmd_t::m_tick_count,
			std::string_view{ ( "pitch" ) }, &lua_user_cmd_t::m_pitch,
			std::string_view{ ( "yaw" ) }, &lua_user_cmd_t::m_yaw,
			std::string_view{ ( "fwd_move" ) }, &lua_user_cmd_t::m_fwd_move,
			std::string_view{ ( "side_move" ) }, &lua_user_cmd_t::m_side_move,
#define ADD_FLAG( var ) std::string_view{ ( #var ) }, &lua_user_cmd_t::m_##var
			ADD_FLAG( in_attack ), ADD_FLAG( in_jump ), ADD_FLAG( in_duck ),
			ADD_FLAG( in_forward ), ADD_FLAG( in_back ), ADD_FLAG( in_use ),
			ADD_FLAG( in_cancel ), ADD_FLAG( in_left ), ADD_FLAG( in_right ),
			ADD_FLAG( in_move_left ), ADD_FLAG( in_move_right ), ADD_FLAG( in_attack2 ),
			ADD_FLAG( in_run ), ADD_FLAG( in_reload ), ADD_FLAG( in_alt1 ),
			ADD_FLAG( in_alt2 ), ADD_FLAG( in_score ), ADD_FLAG( in_speed ),
			ADD_FLAG( in_walk ), ADD_FLAG( in_zoom ), ADD_FLAG( in_weapon1 ),
			ADD_FLAG( in_weapon2 ), ADD_FLAG( in_bullrush ), ADD_FLAG( in_grenade1 ),
			ADD_FLAG( in_grenade2 ), ADD_FLAG( in_attack3 )
#undef ADD_FLAG
		);

		{
			auto entity = m_state.create_table( );

			entity[ ( "get_ents" ) ] = [ ] ( const char* class_name ) {
				std::vector< int > ret{};

				for ( int i{}; i <= valve___g_entity_list->highest_index( ); ++i ) {
					const auto entity = valve___g_entity_list->find_entity( i );
					if ( !entity )
						continue;

					const auto client_class = entity->client_class( );
					if ( !client_class
						|| std::string_view{ client_class->m_network_name }.find( class_name ) == std::string::npos )
						continue;

					ret.emplace_back( i );
				}

				return ret;
			};
			entity[ ( "get_players" ) ] = [] ( const bool enemies_only ) {
				std::vector< int > ret{};

				for ( auto i = 1; i <= valve___g_global_vars->m_max_clients; ++i ) {
					const auto entity = valve___g_entity_list->find_entity( i );
					if ( !entity
						|| ( enemies_only && entity->friendly( ) ) )
						continue;

					ret.emplace_back( i );
				}

				return ret;
			};
			entity[ ( "get_class_name" ) ] = [ ] ( const int index ) {
				const auto entity = valve___g_entity_list->find_entity( index );
				if ( !entity )
					return "";

				const auto client_class = entity->client_class( );
				if ( !client_class )
					return "";

				return client_class->m_network_name;
			};
			entity[ ( "get_local_player" ) ] = [ ] ( ) { return valve___g_engine->local_player_index( ); };
			entity[ ( "get_origin" ) ] = [ ] ( const int index ) {
				const auto entity = valve___g_entity_list->find_entity( index );
				if ( !entity )
					return vec3_t{};

				return entity->origin( );
			};
			entity[  ( "get_velocity" ) ] = [ ] ( const int index ) {
				const auto entity = valve___g_entity_list->find_entity ( index );
				if ( !entity )
					return vec3_t {};

				return ( ( valve::c_player* ) entity )->velocity ( );
			};
			entity[ ( "get_player_name" ) ] = [] ( const int index ) {
				const auto player_info = valve___g_engine->player_info( index );
				if ( !player_info.has_value( ) )
					return "";

				return player_info->m_name;
			};
			entity[ ( "is_alive" ) ] = [] ( const int index ) {
				const auto entity = valve___g_entity_list->find_entity( index );
				if ( !entity )
					return false;

				return static_cast< valve::c_player* >( entity )->alive( );
			};
			entity[ ( "is_dormant" ) ] = [] ( const int index ) {
				const auto entity = valve___g_entity_list->find_entity( index );
				if ( !entity )
					return false;

				return entity->dormant( );
			};
			entity[  ( "is_local_being_observer_target" ) ] = [ ] ( const int index ) {
				const auto entity = valve___g_entity_list->find_entity ( index );
				if ( !entity )
					return false;

				auto observer_target = valve___g_entity_list->find_entity ( ( ( valve::c_player* )entity )->observer_target ( ) );

				if ( !observer_target )
					return false;

				return observer_target == valve::g_local_player;
			};
			entity[ ( "is_enemy" ) ] = [] ( const int index ) {
				const auto entity = valve___g_entity_list->find_entity( index );
				if ( !entity )
					return false;

				return !entity->friendly( );
			};
			entity[  ( "is_scoped" ) ] = [ ] ( const int index ) {
				const auto entity = valve___g_entity_list->find_entity ( index );
				if ( !entity )
					return false;

				return ( ( valve::c_player* )entity )->scoped ( );
			};

			entity[ ( "set_prop" ) ] = [ ] ( const int index, const char* prop_name, const std::variant< vec3_t, int, float >& value, const std::size_t array_index = 0u ) {
				const auto entity = valve___g_entity_list->find_entity( index );
				if ( !entity )
					return;
				
				const auto& net_var = valve::g_net_vars->entry( prop_name );

				switch ( net_var.first->m_send_type ) {
				case valve::e_send_prop_type::_int:
					*reinterpret_cast< int* >( reinterpret_cast< std::uintptr_t >( entity ) + net_var.second + sizeof( int ) * array_index ) = std::get< int >( value );
					break;
				case valve::e_send_prop_type::_float:
					*reinterpret_cast< float* >( reinterpret_cast< std::uintptr_t >( entity ) + net_var.second + sizeof( float ) * array_index ) = std::get< float >( value );
					break;
				case valve::e_send_prop_type::vec3d:
					*reinterpret_cast< vec3_t* >( reinterpret_cast< std::uintptr_t >( entity ) + net_var.second + sizeof( vec3_t ) * array_index ) = std::get< vec3_t >( value );				
					break;
				}
			};

			entity[ ( "get_prop" ) ] = [ ] ( const int index, const char* prop_name, const std::size_t array_index = 0u ) {
				std::variant< vec3_t, int, float > ret{};

				const auto entity = valve___g_entity_list->find_entity( index );
				if ( !entity )
					return ret;

				const auto& net_var = valve::g_net_vars->entry( prop_name );

				switch ( net_var.first->m_send_type ) {
				case valve::e_send_prop_type::_int: ret = *reinterpret_cast< int* >( reinterpret_cast< std::uintptr_t >( entity ) + net_var.second ); break;
				case valve::e_send_prop_type::_float: ret = *reinterpret_cast< float* >( reinterpret_cast< std::uintptr_t >( entity ) + net_var.second ); break;
				case valve::e_send_prop_type::vec3d: ret = *reinterpret_cast< vec3_t* >( reinterpret_cast< std::uintptr_t >( entity ) + net_var.second ); break;
				}

				return ret;
			};

			m_state[ ( "entity" ) ] = entity;
		}

		{
			auto globals = m_state.create_table( );

			globals[ ( "abs_frame_time" ) ] = [ ] ( ) { return valve___g_global_vars->m_absolute_frame_time; };
			globals[ ( "cur_time" ) ] = [ ] ( ) { return valve___g_global_vars->m_cur_time; };
			globals[ ( "frame_count" ) ] = [ ] ( ) { return valve___g_global_vars->m_frame_count; };
			globals[ ( "frame_time" ) ] = [ ] ( ) { return valve___g_global_vars->m_frame_time; };
			globals[ ( "max_client" ) ] = [ ] ( ) { return valve___g_global_vars->m_max_clients; };
			globals[ ( "real_time" ) ] = [ ] ( ) { return valve___g_global_vars->m_real_time; };
			globals[ ( "tick_count" ) ] = [ ] ( ) { return valve___g_global_vars->m_tick_count; };
			globals[ ( "interval_per_tick" ) ] = [ ] ( ) { return valve___g_global_vars->m_interval_per_tick; };

			m_state[ ( "globals" ) ] = globals;
		}


		{
			auto client = m_state.create_table( );

			client[  ( "get_screen_width" ) ] = [ ] ( ) { misc_::get_screen_width ( ); };
			client[  ( "get_screen_height" ) ] = [ ] ( ) { misc_::get_screen_height ( ); };
			client[ ( "exec" ) ] = [ ] ( const char* cmd ) { valve___g_engine->exec_cmd( cmd ); };
			client[ ( "eye_position" ) ] = [ ] ( ) { return g_context->shoot_pos( ); };
			client[  ( "add_log" ) ] = [ ] ( std::string_view str, col_t& clr ) { nem::hacks::g_logs->push_log ( std::string ( str ),  ( "d" ), clr ); };
			client[ ( "random_float" ) ] = [ ] ( const float min, const float max ) { return g_context->addresses( ).m_random_float.get( )( min, max ); };
			client[ ( "random_int" ) ] = [ ] ( const int min, const int max ) { return g_context->addresses( ).m_random_int.get( )( min, max ); };
			client[  ( "in_game" ) ] = [ ] ( ) { return valve___g_engine->in_game ( ); };
			client[  ( "get_desync_delta" ) ] = [ ] ( ) { return anti_aims_::desync_delta ( ); };
		
			client[ "add_callback" ] = [ & ]( const char* event_name, const sol::protected_function& callback ) {
				const auto event = m_events.find( event_name );
				if ( event == m_events.end( ) )
					return;

				sol::function getinfo = m_state[ "debug" ][ "getinfo" ];
				sol::table debug_info = getinfo( 2, "S" );

				std::string source_path = debug_info[ "source" ];
				source_path = source_path.substr( 1 );

				auto file_name = std::filesystem::path( source_path ).filename( ).string( );

				event->second.emplace_back( callback, util::hash( file_name.data( ) ) );
				};

			m_state[ ( "client" ) ] = client;	
		}

		{
			auto render = m_state.create_table ( );

			render[  ( "world_to_screen" ) ] = [ ] ( vec3_t& world ) { return renderer::world_to_screen ( world ); };
			render[  ( "draw_text" ) ] = [ ] ( float x, float y, col_t& clr, std::string_view str, int font, bool outline ) { return renderer::text ( x, y, clr, str, font, outline ); };
			render[  ( "draw_line" ) ] = [ ] ( float x, float y, float x_, float y_, col_t& clr ) { return renderer::draw_line ( x, y, x_, y_, clr ); };
			render[  ( "draw_rect" ) ] = [ ] ( float x, float y, float x_, float y_, col_t& clr ) { return renderer::draw_rect ( x, y, x_, y_, clr ); };
			render[  ( "draw_rect_filled" ) ] = [ ] ( float x, float y, float h, float w, col_t& clr, float rounding ) { return renderer::draw_rect_filled ( x, y, w, h, clr, rounding ); };
			
			m_state[  ( "render" ) ] = render;
		}

		{
			auto cvar = m_state.create_table( );

			cvar[ ( "find" ) ] = [ ] ( const char* name ) { return valve___g_cvar->find_var( name ); };

			m_state[ ( "cvar" ) ] = cvar;
		}

		{
			auto key_binds = m_state.create_table ( );

			key_binds[  ( "get_dt_state" ) ] = [ ] ( ) { return misc_::get_double_tap_state ( ); };
			key_binds[  ( "get_hs_state" ) ] = [ ] ( ) { return misc_::get_hide_shots_state ( ); };
			key_binds[  ( "get_roll_lean_state" ) ] = [ ] ( ) { return misc_::get_roll_extension_state ( ); };
			key_binds[  ( "get_slow_walk_state" ) ] = [ ] ( ) { return misc_::get_slow_walk_state ( ); };
			key_binds[  ( "get_third_person_state" ) ] = [ ] ( ) { return misc_::get_third_person_state ( ); };
			key_binds[  ( "get_dmg_override_state" ) ] = [ ] ( ) { return misc_::get_dmg_override_state ( ); };
			key_binds[  ( "get_desync_flip_state" ) ] = [ ] ( ) { return misc_::get_flipped_state ( ); };
			m_state[  ( "keys" ) ] = key_binds;
		}

		{
			auto anti_aims = m_state.create_table ( );
			anti_aims[  ( "change_jitter_value" ) ] = [ ] ( float value ) { return anti_aims_::change_jitter_value ( value ); };
			anti_aims[  ( "change_desync_value" ) ] = [ ] ( float value ) { return anti_aims_::change_desync_value ( value ); };
			anti_aims[  ( "change_roll_value" ) ] = [ ] ( float value ) { return anti_aims_::change_roll_value ( value ); };
			anti_aims[  ( "change_fake_lags_value" ) ] = [ ] ( float value ) { return anti_aims_::change_fake_lags_value ( value ); };
			m_state[  ( "anti_aims" ) ] = anti_aims;
		}

		m_events[ ( "on_create_move" ) ] = {};
		m_events[  ( "on_paint" ) ] = {};
	}
}