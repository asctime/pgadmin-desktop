#include "Postgres/pgDiscipline.h"

static const pgIntroduced kIntro[] =
{
	{ 9, 1, PG_F_REPLICATION_ROLE },
	{ 9, 1, PG_F_COLLATION }
};

extern const pgVersionModule pgMod_91 = { 9, 1, "9.1", kIntro, (int)(sizeof(kIntro) / sizeof(kIntro[0])) };
