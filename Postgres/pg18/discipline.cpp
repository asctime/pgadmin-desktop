#include "Postgres/pgDiscipline.h"

static const pgIntroduced kIntro[] =
{
	{ 18, 0, PG_F_NOT_ENFORCED },
	{ 18, 0, PG_F_VIRTUAL_GENERATED },
	{ 18, 0, PG_F_UUIDV7 },
	{ 18, 0, PG_F_RETURNING_OLD }
};

extern const pgVersionModule pgMod_18 = { 18, 0, "18", kIntro, (int)(sizeof(kIntro) / sizeof(kIntro[0])) };
