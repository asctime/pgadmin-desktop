#include "Postgres/pgDiscipline.h"

static const pgIntroduced kIntro[] =
{
	{ 9, 4, PG_F_JSONB },
	{ 9, 4, PG_F_REPL_SLOTS }
};

extern const pgVersionModule pgMod_94 = { 9, 4, "9.4", kIntro, (int)(sizeof(kIntro) / sizeof(kIntro[0])) };
