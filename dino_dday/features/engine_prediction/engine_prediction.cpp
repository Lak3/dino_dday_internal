#include "engine_prediction.h"

c_engine_prediction::c_engine_prediction() {
	m_old_curtime    = 0.0f;
	m_old_frametime  = 0.0f;
	m_old_tick_count = 0;
	m_old_tick_base  = 0;
	m_old_flags      = 0;
	m_local          = nullptr;
	m_move_data      = { };
}

c_engine_prediction::~c_engine_prediction() {
	m_old_curtime    = 0.0f;
	m_old_frametime  = 0.0f;
	m_old_tick_count = 0;
	m_old_tick_base  = 0;
	m_old_flags      = 0;
	m_local          = nullptr;
	m_move_data      = { };
}

void c_engine_prediction::start(c_user_cmd* cmd) {
	m_local = get_local();

	if (!ints.move_helper || !m_local || m_local->get_deadflag()) {
		m_local = nullptr; //finish wont be ran either since m_local is nullptr
		return;
	}

	cmd->random_seed = (md5.pseudo_random(cmd->command_number) & std::numeric_limits<int>::max());

	m_local->set_current_command(cmd);
	c_base_entity::set_prediction_random_seed(cmd);

	m_old_curtime    = ints.global_vars->curtime;
	m_old_frametime  = ints.global_vars->frametime;
	m_old_tick_count = ints.global_vars->tickcount;

	m_old_flags     = m_local->get_flags();
	m_old_tick_base = m_local->get_tick_base();

	const int new_tick_base = get_tick_base(cmd);

	ints.global_vars->curtime   = ticks_to_time(new_tick_base);
	ints.global_vars->frametime = tick_interval;
	ints.global_vars->tickcount = new_tick_base;

	m_local->update_button_state(cmd->buttons);

	ints.prediction->set_local_view_angles(cmd->viewangles);

	ints.prediction->setup_move(m_local, cmd, ints.move_helper, &m_move_data);
	ints.game_movement->process_movement(m_local, &m_move_data);
	ints.prediction->finish_move(m_local, cmd, &m_move_data);

	m_local->set_flags(m_old_flags);
	m_local->set_tick_base(m_old_tick_base);
}

void c_engine_prediction::finish() {
	if (!m_local) //only when m_local is valid we have ran start, and need to finish.
		return;

	ints.global_vars->curtime   = m_old_curtime;
	ints.global_vars->frametime = m_old_frametime;
	ints.global_vars->tickcount = m_old_tick_count;

	m_local->set_current_command(nullptr);
	c_base_entity::set_prediction_random_seed(nullptr);
}

int c_engine_prediction::get_tick_base(c_user_cmd* cmd) {
	static int s_tick        = 0;
	static c_user_cmd* s_cmd = nullptr;

	if (cmd) {
		if (!s_cmd || s_cmd->hasbeenpredicted)
			s_tick = m_local->get_tick_base();
		else
			s_tick++;

		s_cmd = cmd;
	}

	return s_tick;
}