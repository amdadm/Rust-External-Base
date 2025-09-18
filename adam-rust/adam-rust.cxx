#include <impl/includes.h>

/*===============================================================================================
  Project         : Rust External Base 

  Original Author : amdadm
  GitHub          : https://github.com/amdadm
  Created         : 2025-09-18

  Description     : Simple cheat base for Rust.

  License         : MIT License
===============================================================================================*/

int main( ) {
    SetConsoleTitleA( encrypt( "adam-rust" ) );
    SetUnhandledExceptionFilter( exception::exception_filter );

    if ( !g_lib->setup( ) ) {
        logging::print( encrypt( "Failed to init libcrypt." ) );
        return std::getchar( );
    } else { logging::print( encrypt( "Libcrypt initialized." ) ); }

    if (!g_driver->setup( ) )
        return std::getchar( );

    g_driver->m_process_id = g_driver->get_process_id( L"RustClient.exe" );

    logging::print( encrypt( "Process PID: %i" ), g_driver->m_process_id );

    g_driver->m_base_address = g_driver->get_base_address( );

    logging::print( encrypt( "Base Address: %llx" ), g_driver->m_base_address );

    g_driver->m_dtb = g_driver->get_dtb( );

    g_driver->m_game_assembly = g_driver->get_module_address(encrypt("GameAssembly.dll"));

    logging::print(encrypt("GameAssembly: %llx"), g_driver->m_game_assembly);

    std::thread([] { world::loop_actors(); }).detach();

    if (!g_drawing->hijack()) {
        logging::print(encrypt("Failed to find overlay."));
        g_driver->unload();
        return std::getchar();
    }

    if (!g_drawing->setup()) {
        logging::print(encrypt("Failed to setup drawing."));
        g_driver->unload();
        return std::getchar();
    }

    drawing::render();

    return std::getchar( );
}