#include "../hooks.h"

define_hook(cl_move, void, __cdecl, float accumulated_extra_samples, bool final_tick) {
	detour.original<fn>()(accumulated_extra_samples, final_tick);

	/*
		kerran heitettii päärynä vitun lujaa seinään (Juuso heitti ja se käy salilla)
		niin kuulu vaa poks eikä ollu edes mitään mössöö tai mitn missää vaa se hävis kokonaan
	*/

	if (helpers.cvar->m_misc_speed_key.get() && helpers.input->is_held(helpers.cvar->m_misc_speed_key.get())) {
		for (int n = 0; n < helpers.cvar->m_misc_speed_amount.get(); n++)
			detour.original<fn>()(accumulated_extra_samples, final_tick);
	}
}