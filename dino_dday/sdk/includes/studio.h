#pragma once

#include "globalvars_base.h"

#define maxstudiobones 128
#define bone_used_by_hitbox 0x00000100

struct mstudiobbox_t {
public:
	/*
	__inline char* get_hitbox_name() const {
		if (szhitboxnameindex == 0)
			return '\0';

		return ((char*)this) + szhitboxnameindex;
	}
	*/

	__inline std::string get_hitbox_name() {
		if (szhitboxnameindex == 0)
			return "null_hitbox";

		return std::string(((char*)this) + szhitboxnameindex);
	}

public:
	int bone;
	int group;
	vector bbmin;
	vector bbmax;
	int szhitboxnameindex;
private:
	char __pad00[12];

public:
	float radius;

private:
	char __pad01[16];
};

struct mstudiobone_t {
public:
	__inline const char* get_name() const {
		return ((char*)this) + sznameindex;
	}

	__inline void* get_procedure() const {
		if (procindex == 0)
			return nullptr;

		return reinterpret_cast<void*>(((unsigned char*)this) + procindex);
	}

	__inline const char* get_surface_props() const {
		return ((char*)this) + surfacepropidx;
	}

public:
	int sznameindex;
	int parent;
	int bonecontroller[6];
	vector pos;
	float quat[4];
	vector rot;
	vector posscale;
	vector rotscale;
	matrix3x4_t pose_to_bone;
	float q_alignment[4];
	int flags;
	int proctype;
	int procindex;
	int physicsbone;
	int surfacepropidx;
	int contents;
private:
	char __pad00[32];
};

struct mstudiohitboxset_t {
public:
	__inline const char* get_name() const {
		return ((char*)this) + sznameindex;
	}

	__inline mstudiobbox_t* get_hitbox(const int n) const {
		return (mstudiobbox_t*)(((unsigned char*)this) + hitboxindex) + n;
	}

public:
	int sznameindex;
	int numhitboxes;
	int hitboxindex;
};

struct studiohdr_t {
public:
	__inline mstudiobone_t* get_bone(const int n) const {
		return (mstudiobone_t*)(((unsigned char*)this) + boneindex) + n;
	}

	__inline mstudiohitboxset_t* get_hitbox_set(const int n) const {
		return (mstudiohitboxset_t*)(((unsigned char*)this) + hitboxsetindex) + n;
	}

	__inline mstudiobbox_t* get_hitbox(const int n, const int set) const {
		const mstudiohitboxset_t* s = get_hitbox_set(set);

		return s ? s->get_hitbox(n) : nullptr;
	}

	__inline int get_hitbox_count(const int set) const {
		const mstudiohitboxset_t* s = get_hitbox_set(set);

		return s ? s->numhitboxes : 0;
	}

	__inline int get_bone_count() const {
		return numbones;
	}

public:
	int id;
	int version;
	int checksum;
	char name[64];
	int length;
	vector eye_position;
	vector illum_position;
	vector hull_min;
	vector hull_max;
	vector view_bbmin;
	vector view_bbmax;
	int flags;
	int numbones;
	int boneindex;
	int num_bonecontrollers;
	int bonecontrollerindex;
	int numhitboxsets;
	int hitboxsetindex;
	int numlocalanim;
	int localanimindex;
	int numlocalseq;
	int localseqindex;
	int activitylistversion;
	int eventsindexed;
	int numtextures;
	int textureindex;
	int numcdtextures;
	int cdtextureindex;
	int numskinref;
	int numskinfamilies;
	int skinindex;
	int numbodyparts;
	int bodypartindex;
	int numlocalattachments;
	int localattachmentindex;
	int numlocalnodes;
	int localnodeindex;
	int localnodenameindex;
	int numflexdesc;
	int flexdescindex;
	int numflexcontrollers;
	int flexcontrollerindex;
	int numflexrules;
	int flexruleindex;
	int numikchains;
	int ikchainindex;
	int nummouths;
	int mouthindex;
	int numlocalposeparameters;
	int localposeparameterindex;
	int surfacepropindex;
	int keyvalueindex;
	int keyvaluesize;
	int numlocalikautoplaylocks;
	int localikautoplaylockindex;
	float mass;
	int contents;
	int numincludemodels;
	int includemodelindex;
	void* virtual_model;
	int szanimblocknameindex;
	int numanimblocks;
	int animblockindex;
	void* anim_block_model;
	int bonetablebynameindex;
	void* vertex_base;
	void* index_base;
	unsigned char constdirectionallightdot;
	unsigned char root_lod;
	unsigned char num_allowed_root_lods;

private:
	unsigned char __pad00[5];

public:
	int numflexcontrollerui;
	int flexcontrolleruiindex;
	float vert_anim_fixed_point_scale;

private:
	unsigned char __pad01[4];

public:
	int studiohdr2index;
	
private:
	unsigned char __pad02[4];
};