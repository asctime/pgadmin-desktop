#include "Postgres/pgDiscipline.h"

static const pgIntroduced kIntro[] =
{
	{ 11, 0, PG_F_PROKIND },
	{ 11, 0, PG_F_PROCEDURE },
	{ 11, 0, PG_F_INDEX_INCLUDE }
};

extern const pgVersionModule pgMod_11 = { 11, 0, "11", kIntro, (int)(sizeof(kIntro) / sizeof(kIntro[0])) };
