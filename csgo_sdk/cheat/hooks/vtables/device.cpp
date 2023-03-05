#include "../hooks.hpp"
#include "../../../menu/menu.hpp"

void hooks::device::wnd_proc::instance( ) {
	D3DDEVICE_CREATION_PARAMETERS parameters;
	interfaces::device->GetCreationParameters( &parameters );

	const auto wnd = parameters.hFocusWindow;
	if ( !wnd )
		return;

	wnd_proc = reinterpret_cast< WNDPROC >( SetWindowLongA( wnd, GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( fn ) ) );
}

long __stdcall hooks::device::wnd_proc::fn( const HWND window, const UINT msg, const WPARAM wparm, const LPARAM lparm ) {
	ImGui_ImplWin32_Init( window );

	if ( ImGui_ImplWin32_WndProcHandler( window, msg, wparm, lparm ) && ctx::m_menu_opened && !( msg == WM_LBUTTONDOWN || msg == WM_LBUTTONUP || msg == WM_MOUSEMOVE ) )
		return false;

	if ( ctx::m_menu_opened && ( msg == WM_LBUTTONDOWN || msg == WM_LBUTTONUP || msg == WM_MOUSEMOVE ) )
		return false;

	return CallWindowProcA( wnd_proc, window, msg, wparm, lparm );
}

long __stdcall  hooks::device::present::fn( IDirect3DDevice9* device, RECT* src, RECT* dest, HWND window_override, RGNDATA* dirty_region ) {
	if ( !ImGui::GetCurrentContext( ) )
		return get_original( device, src, dest, window_override, dirty_region );

	ImGui_ImplDX9_Init( device );
	menu::instance( );

	IDirect3DVertexDeclaration9* vert_declaration;
	IDirect3DVertexShader9* vert_shader;
	DWORD old_d3drs_colorwriteenable;

	device->GetRenderState( D3DRS_COLORWRITEENABLE, &old_d3drs_colorwriteenable );
	device->GetVertexDeclaration( &vert_declaration );
	device->GetVertexShader( &vert_shader );

	device->SetRenderState( D3DRS_COLORWRITEENABLE, 0xffffffff );
	device->SetRenderState( D3DRS_SRGBWRITEENABLE, false );
	device->SetSamplerState( NULL, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );
	device->SetSamplerState( NULL, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );
	device->SetSamplerState( NULL, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP );
	device->SetSamplerState( NULL, D3DSAMP_SRGBTEXTURE, NULL );

	ImGui_ImplDX9_NewFrame( );
	ImGui_ImplWin32_NewFrame( );
	ImGui::NewFrame( );

	if ( ImGui::IsKeyPressed( VK_INSERT, false ) )
		ctx::m_menu_opened = !ctx::m_menu_opened;

	menu::draw( );

	ImGui::EndFrame( );
	ImGui::Render( render::render_scene( ) );

	if ( device->BeginScene( ) == D3D_OK ) {
		ImGui_ImplDX9_RenderDrawData( ImGui::GetDrawData( ) );
		device->EndScene( );
	}

	device->SetRenderState( D3DRS_COLORWRITEENABLE, old_d3drs_colorwriteenable );
	device->SetRenderState( D3DRS_SRGBWRITEENABLE, true );
	device->SetVertexDeclaration( vert_declaration );
	device->SetVertexShader( vert_shader );

	return get_original( device, src, dest, window_override, dirty_region );
}

long __stdcall hooks::device::reset::fn( IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params ) {
	ImGui_ImplDX9_InvalidateDeviceObjects( );
	const auto og = get_original( device, params );
	ImGui_ImplDX9_CreateDeviceObjects( );

	return og;
}