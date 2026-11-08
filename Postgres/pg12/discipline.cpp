#include "Postgres/pgDiscipline.h"

static const pgIntroduced kIntro[] =
{
	{ 12, 0, PG_F_GENERATED_STORED },
	{ 12, 0, PG_F_NO_ADSRC },
	{ 12, 0, PG_F_NO_RELHASOIDS }
};

extern const pgVersionModule pgMod_12 = { 12, 0, "12", kIntro, (int)(sizeof(kIntro) / sizeof(kIntro[0])) };
