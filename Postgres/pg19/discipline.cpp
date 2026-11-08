#include "Postgres/pgDiscipline.h"

static const pgIntroduced kIntro[] =
{
	{ 19, 0, PG_F_REPACK },
	{ 19, 0, PG_F_PARALLEL_AUTOVACUUM },
	{ 19, 0, PG_F_IGNORE_NULLS },
	{ 19, 0, PG_F_ON_CONFLICT_DO_SELECT }
};

extern const pgVersionModule pgMod_19 = { 19, 0, "19", kIntro, (int)(sizeof(kIntro) / sizeof(kIntro[0])) };
