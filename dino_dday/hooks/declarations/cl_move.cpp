#include "../hooks.h"

define_hook(cl_move, void, __cdecl, float accumulated_extra_samples, bool final_tick) {
	detour.original<fn>()(accumulated_extra_samples, final_tick);

	/*
		kerran heitettii p��ryn� vitun lujaa sein��n (Juuso heitti ja se k�y salilla)
		niin kuulu vaa poks eik� ollu edes mit��n m�ss�� tai mitn miss�� vaa se h�vis kokonaan
	*/

	if (helpers.cvar->m_misc_speed_key.get() && helpers.input->is_held(helpers.cvar->m_misc_speed_key.get())) {
		for (int n = 0; n < helpers.cvar->m_misc_speed_amount.get(); n++)
			detour.original<fn>()(accumulated_extra_samples, final_tick);
	}
}