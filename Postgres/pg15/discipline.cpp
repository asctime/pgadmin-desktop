#include "Postgres/pgDiscipline.h"

static const pgIntroduced kIntro[] =
{
	{ 15, 0, PG_F_MERGE },
	{ 15, 0, PG_F_NULLS_NOT_DISTINCT },
	{ 15, 0, PG_F_NO_DATLASTSYSOID },
	{ 15, 0, PG_F_PUBLIC_NOT_OPEN }
};

extern const pgVersionModule pgMod_15 = { 15, 0, "15", kIntro, (int)(sizeof(kIntro) / sizeof(kIntro[0])) };
