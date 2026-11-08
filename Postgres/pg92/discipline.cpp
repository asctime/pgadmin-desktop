#include "Postgres/pgDiscipline.h"

static const pgIntroduced kIntro[] =
{
	{ 9, 2, PG_F_JSON }
};

extern const pgVersionModule pgMod_92 = { 9, 2, "9.2", kIntro, (int)(sizeof(kIntro) / sizeof(kIntro[0])) };
