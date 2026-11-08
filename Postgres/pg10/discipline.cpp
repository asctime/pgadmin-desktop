#include "Postgres/pgDiscipline.h"

static const pgIntroduced kIntro[] =
{
	{ 10, 0, PG_F_PARTITION },
	{ 10, 0, PG_F_IDENTITY },
	{ 10, 0, PG_F_PUBLICATION },
	{ 10, 0, PG_F_PG_SEQUENCE },
	{ 10, 0, PG_F_SCRAM }
};

extern const pgVersionModule pgMod_10 = { 10, 0, "10", kIntro, (int)(sizeof(kIntro) / sizeof(kIntro[0])) };
