#include "Postgres/pgDiscipline.h"

static const pgIntroduced kIntro[] =
{
	{ 9, 3, PG_F_MATVIEW },
	{ 9, 3, PG_F_EVENT_TRIGGER }
};

extern const pgVersionModule pgMod_93 = { 9, 3, "9.3", kIntro, (int)(sizeof(kIntro) / sizeof(kIntro[0])) };
