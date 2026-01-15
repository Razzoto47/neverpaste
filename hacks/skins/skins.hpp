#pragma once

namespace nem::hacks {
	class c_skins {
	public:
		static constexpr auto k_max_wpns = 35u;
		static constexpr auto k_max_knives = 20u;

		__forceinline void update_gloves ( )
		{
			m_glove_data[ e_gloves::blood_hunt ].setup ( 5027,
				 ( "models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl" ),
				 ( "models/weapons/w_models/arms/glove_bloodhound/w_glove_bloodhound.mdl" ) );

			m_glove_data[ e_gloves::sporty ].setup ( 5030,
				 ( "models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl" ),
				 ( "models/weapons/w_models/arms/glove_sporty/w_glove_sporty.mdl" ) );

			m_glove_data[ e_gloves::driver ].setup ( 5031,
				 ( "models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl" ),
				 ( "models/weapons/w_models/arms/glove_slick/w_glove_slick.mdl" ) );

			m_glove_data[ e_gloves::hand_wrap ].setup ( 5032,
				 ( "models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl" ),
				 ( "models/weapons/w_models/arms/glove_handwrap_leathery/w_glove_handwrap_leathery.mdl" ) );

			m_glove_data[ e_gloves::moto ].setup ( 5033,
				 ( "models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl" ),
				 ( "models/weapons/w_models/arms/glove_motorcycle/w_glove_motorcycle.mdl" ) );

			m_glove_data[ e_gloves::special_list ].setup ( 5034,
				 ( "models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl" ),
				 ( "models/weapons/w_models/arms/glove_specialist/w_glove_specialist.mdl" ) );
		}

	private:
		bool set_paint_kit( valve::c_weapon* const weapon, const bool is_knife );

        struct weapon_t {
            valve::e_item_index m_index{};
            std::string			m_name{};
        };

		/* too lazy to write parser for item_schema */
		std::array< weapon_t, k_max_wpns >		m_weapons{
			weapon_t{ valve::e_item_index::knife, ( "knife" ) },
			{ valve::e_item_index::ak47, ( "ak47" ) },
			{ valve::e_item_index::aug, ( "aug" )},
			{ valve::e_item_index::awp, ( "awp" ) },
			{ valve::e_item_index::famas, ( "famas" ) },
			{ valve::e_item_index::g3sg1, ( "g3sg1" ) },
			{ valve::e_item_index::galil, ( "galil" ) },
			{ valve::e_item_index::m249, ( "m249" ) },
			{ valve::e_item_index::m4a1, ( "m4a1" ) },
			{ valve::e_item_index::mac10, ( "mac10" ) },
			{ valve::e_item_index::p90, ( "p90" ) },
			{ valve::e_item_index::mp5sd, ( "mp5sd" ) },
			{ valve::e_item_index::ump45, ( "ump45" ) },
			{ valve::e_item_index::xm1014, ( "xm1014" ) },
			{ valve::e_item_index::bizon, ( "bizon" ) },
			{ valve::e_item_index::mag7, ( "mag7" ) },
			{ valve::e_item_index::negev, ( "negev" ) },
			{ valve::e_item_index::sawedoff, ( "sawedoff" ) },
			{ valve::e_item_index::tec9, ( "tec9" ) },
			{ valve::e_item_index::hkp2000, ( "hkp2000" ) },
			{ valve::e_item_index::mp7, ( "mp7" ) },
			{ valve::e_item_index::mp9, ( "mp9" ) },
			{ valve::e_item_index::nova, ( "nova" ) },
			{ valve::e_item_index::p250, ( "p250" ) },
			{ valve::e_item_index::scar20, ( "scar20" ) },
			{ valve::e_item_index::sg553, ( "sg553" ) },
			{ valve::e_item_index::ssg08, ( "ssg08" ) },
			{ valve::e_item_index::cz75a, ( "cz75a" ) },
			{ valve::e_item_index::deagle, ( "deagle" ) },
			{ valve::e_item_index::elite, ( "elite" ) },
			{ valve::e_item_index::fiveseven, ( "fiveseven" ) },
			{ valve::e_item_index::glock, ( "glock" ) },
			{ valve::e_item_index::m4a1_silencer, ( "m4a1_silencer" ) },
			{ valve::e_item_index::revolver, ( "revolver" ) },
			{ valve::e_item_index::usp_silencer, ( "usp_silencer" ) }
        };

		std::array< weapon_t, k_max_knives >	m_knives{
			weapon_t{ valve::e_item_index::none, ( "def" ) },
			{ valve::e_item_index::knife_bayonet, ( "bayonet" )},
			{ valve::e_item_index::knife_css, ( "css" ) },
			{ valve::e_item_index::knife_skeleton, ( "skeleton" ) },
			{ valve::e_item_index::knife_outdoor, ( "outdoor" ) },
			{ valve::e_item_index::knife_cord, ( "cord" ) },
			{ valve::e_item_index::knife_canis, ( "canis" ) },
			{ valve::e_item_index::knife_flip, ( "flip" ) },
			{ valve::e_item_index::knife_gut, ( "gut" ) },
			{ valve::e_item_index::knife_karambit, ( "karambit" ) },
			{ valve::e_item_index::knife_m9_bayonet, ( "m9 bayonet" ) },
			{ valve::e_item_index::knife_tactical, ( "tactical" ) },
			{ valve::e_item_index::knife_falchion, ( "falchion" ) },
			{ valve::e_item_index::knife_survival_bowie, ( "bowie" ) },
			{ valve::e_item_index::knife_butterfly, ( "butterfly" ) },
			{ valve::e_item_index::knife_push, ( "push" ) },
			{ valve::e_item_index::knife_ursus, ( "ursus" ) },
			{ valve::e_item_index::knife_gypsy_jackknife, ( "gypsy" ) },
			{ valve::e_item_index::knife_stiletto, ( "stiletto" ) },
			{ valve::e_item_index::knife_widowmaker, ( "widowmaker" ) }
		};

		std::array< std::string, k_max_knives - 1u > m_knife_mdls{
			( "models/weapons/v_knife_bayonet.mdl" ),
			( "models/weapons/v_knife_css.mdl" ),
			( "models/weapons/v_knife_skeleton.mdl" ),
			( "models/weapons/v_knife_outdoor.mdl" ),
			( "models/weapons/v_knife_cord.mdl" ),
			( "models/weapons/v_knife_canis.mdl" ),
			( "models/weapons/v_knife_flip.mdl" ),
			( "models/weapons/v_knife_gut.mdl" ),
			( "models/weapons/v_knife_karam.mdl" ),
			( "models/weapons/v_knife_m9_bay.mdl" ),
			( "models/weapons/v_knife_tactical.mdl" ),
			( "models/weapons/v_knife_falchion_advanced.mdl" ),
			( "models/weapons/v_knife_survival_bowie.mdl" ),
			( "models/weapons/v_knife_butterfly.mdl" ),
			( "models/weapons/v_knife_push.mdl" ),
			( "models/weapons/v_knife_ursus.mdl" ),
			( "models/weapons/v_knife_gypsy_jackknife.mdl" ),
			( "models/weapons/v_knife_stiletto.mdl" ),
			( "models/weapons/v_knife_widowmaker.mdl" ),
		};

		enum e_gloves {
			blood_hunt = 1,
			sporty,
			driver,
			hand_wrap,
			moto,
			special_list,
			glove_max
		};

		struct glove_data_t {
			int         m_id;
			std::string m_model, m_world_model;
			int         m_model_index, m_world_model_index;

			__forceinline glove_data_t ( ) : m_id {}, m_model {}, m_model_index {} {}

			__forceinline void setup ( int id, const std::string& model, const std::string& world_model )
			{
				m_id = id;
				m_model = model;
				m_world_model = world_model;
				m_model_index = valve___g_model_info->lookup_model_index ( model.data ( ) );
				m_world_model_index = valve___g_model_info->lookup_model_index ( world_model.data ( ) );
			}
		};

		struct paint_kit_t {
			__forceinline constexpr paint_kit_t( ) = default;

			__forceinline paint_kit_t( const std::size_t id, std::string&& name )
				: m_id{ id }, m_name{ name } {}

			std::size_t m_id{};
			std::string m_name{};
		};

		bool									m_update_hud{},
												m_in_force_update{};
		glove_data_t                            m_glove_data[ e_gloves::glove_max ];
		std::atomic< bool >						m_force_update{};
		float									m_last_update_time{};

		std::vector< paint_kit_t >				m_paint_kits{};

		std::size_t								m_old_knife_index{};
		std::array< std::size_t, k_max_wpns >	m_old_paint_kits{};
	public:
		void init( );

		int correct_sequence( const valve::e_item_index index, const int seq ) const;

		void on_frame_stage( const valve::e_frame_stage stage );

		__forceinline const std::array< weapon_t, k_max_wpns >& weapons( );

		__forceinline const std::array< weapon_t, k_max_knives >& knives( );

		__forceinline const std::vector< paint_kit_t >& paint_kits( );

		__forceinline std::atomic< bool >& force_update( );
	};

	inline const auto g_skins = std::make_unique< c_skins >( );
}

#include "impl/skins.inl"