#include "Postgres/pgDiscipline.h"

static const pgIntroduced kIntro[] =
{
	{ 9, 6, PG_F_PARALLEL },
	{ 9, 6, PG_F_WAIT_EVENT }
};

extern const pgVersionModule pgMod_96 = { 9, 6, "9.6", kIntro, (int)(sizeof(kIntro) / sizeof(kIntro[0])) };
