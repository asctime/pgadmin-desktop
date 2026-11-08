#include "Postgres/pgDiscipline.h"

static const pgIntroduced kIntro[] =
{
	{ 16, 0, PG_F_GRANT_INHERIT_SET },
	{ 16, 0, PG_F_PG_STAT_IO }
};

extern const pgVersionModule pgMod_16 = { 16, 0, "16", kIntro, (int)(sizeof(kIntro) / sizeof(kIntro[0])) };
