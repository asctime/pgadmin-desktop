#include "Postgres/pgDiscipline.h"

static const pgIntroduced kIntro[] =
{
	{ 9, 0, PG_F_RECOVERY }
};

extern const pgVersionModule pgMod_90 = { 9, 0, "9.0", kIntro, (int)(sizeof(kIntro) / sizeof(kIntro[0])) };
