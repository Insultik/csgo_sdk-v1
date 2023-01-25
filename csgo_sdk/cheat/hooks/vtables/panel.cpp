#include "../hooks.h"

void __fastcall hooks::panel::paint_traverse::fn( i_panel* vpanel, void* edx, vgui::vpanel panel_id, bool force_repaint, bool allow_force ) {
	get_original( vpanel, edx, panel_id, force_repaint, allow_force );

	static vgui::vpanel draw_panel_id = 0u;
	if ( !draw_panel_id ) {
		if ( HASH( interfaces::panel->get_name( panel_id ) ) != HASH( "MatSystemTopPanel" ) )
			return;

		draw_panel_id = panel_id;
	}

	if ( panel_id != draw_panel_id )
		return;

	render::draw( );
}