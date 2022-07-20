#pragma once

#include "base_entity.h"

class c_base_animating : public c_base_entity {
public:
	__inline bool get_hitbox_position(const int hitbox, vector& pos) {
		const model_t* mdl = get_model();

		if (!mdl)
			return false;

		const studiohdr_t* hdr = ints.model_info->get_studio_model(mdl);

		if (!hdr)
			return false;

		const mstudiobbox_t* box = hdr->get_hitbox(hitbox, get_hitbox_set());

		if (!box || (box->bone >= maxstudiobones) || (box->bone < 0))
			return false;

		matrix3x4_t mtrx[maxstudiobones];
		if (!setup_bones(mtrx, maxstudiobones, bone_used_by_hitbox, ints.global_vars->curtime))
			return false;

		util.math->vector_transform((box->bbmax + box->bbmin) * 0.5f, mtrx[box->bone], pos);
		return true;
	}

	//todo: cache instead of doing shitass string operations on each call...
	__inline bool get_bone_position_by_name(const char* const name, vector& pos) {
		const model_t* mdl = get_model();

		if (!mdl)
			return false;

		const studiohdr_t* hdr = ints.model_info->get_studio_model(mdl);

		if (!hdr)
			return false;

		bool found = false;
		matrix3x4_t mtrx[maxstudiobones];
		for (int n = 0; n < hdr->get_bone_count(); n++) {
			const mstudiobone_t* bone = hdr->get_bone(n);

			if (!bone)
				continue;

			std::string bone_name = { bone->get_name() };

			std::transform(bone_name.begin(), bone_name.end(), bone_name.begin(),
				[](unsigned char c) { return std::tolower(c); });

			if (bone_name.find(name) != std::string_view::npos) {
				if (!setup_bones(mtrx, maxstudiobones, bone_used_by_hitbox, ints.global_vars->curtime))
					break;

				pos   = { mtrx[n][0][3], mtrx[n][1][3], mtrx[n][2][3] };
				found = true;
				break;
			}
		}

		return found;
	}

	__inline int get_hitbox_count() {
		const model_t* mdl = get_model();

		if (!mdl)
			return 0;

		studiohdr_t* hdr = ints.model_info->get_studio_model(mdl);

		if (!hdr)
			return 0;

		return hdr->get_hitbox_count(get_hitbox_set());
	}

public:
	m_netvar(get_hitbox_set, int, "CBaseAnimating", "m_nHitboxSet");
};

class c_base_animating_overlay : public c_base_animating {
public:
	m_netvar(get_sequence, int, "CBaseAnimatingOverlay", "m_nSequence");
};

class c_base_flex : public c_base_animating_overlay {
public:
	m_netvar(get_blink_toggle, bool, "CBaseFlex", "m_blinktoggle");
	m_netvar(get_view_target, vector, "CBaseFlex", "m_viewtarget");
};