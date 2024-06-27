#pragma once

#ifdef _WIN64
#define NOMINMAX
#endif

#include "common.h"

class DesubtickPlugin : public ISmmPlugin, public IMetamodListener
{
public:
	bool Load(PluginId id, ISmmAPI *ismm, char *error, size_t maxlen, bool late);
	bool Unload(char *error, size_t maxlen);
	bool Pause(char *error, size_t maxlen);
	bool Unpause(char *error, size_t maxlen);
	void AllPluginsLoaded();
public:
	const char *GetAuthor();
	const char *GetName();
	const char *GetDescription();
	const char *GetURL();
	const char *GetLicense();
	const char *GetVersion();
	const char *GetDate();
	const char *GetLogTag();
};

struct BasePB
{
	void *vftable;
	uint32_t has_bits;
	uint64_t cached_size;
};

template <typename T>
struct RepeatedPtrField
{
	struct Rep
	{
		int allocated_size;
		T *elements[(std::numeric_limits<int>::max() - 2 * sizeof(int)) / sizeof(void *)];
	};

	void *arena;
	int current_size;
	int total_size;
	Rep *rep;
};

struct CInButtonStateReal
{
	void *table;
	uint64_t buttonstate1;
	uint64_t buttonstate2;
	uint64_t buttonstate3;
	char8 pad[0x30];
};

struct CSubtickMoveStep : BasePB
{
	uint64_t button;
	bool pressed;
	float when;
};

struct CBaseUserCmdPB : BasePB
{
	RepeatedPtrField<CSubtickMoveStep> subtick_moves;
};

class CUserCmd
{
public:
	uint8_t pad[0x20];
	uint32_t tick_count;
	uint32_t unknown;
	void *inputHistory;
	CBaseUserCmdPB *base;
	CInButtonStateReal buttonState;

#ifdef _WIN64
	void* windowsMoment;
#endif
};
