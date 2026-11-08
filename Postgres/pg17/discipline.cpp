#include "Postgres/pgDiscipline.h"

static const pgIntroduced kIntro[] =
{
	{ 17, 0, PG_F_MAINTAIN },
	{ 17, 0, PG_F_STAT_CHECKPOINTER },
	{ 17, 0, PG_F_JSON_TABLE },
	{ 17, 0, PG_F_SUBFAILOVER }
};

extern const pgVersionModule pgMod_17 = { 17, 0, "17", kIntro, (int)(sizeof(kIntro) / sizeof(kIntro[0])) };
