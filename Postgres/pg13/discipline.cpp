#include "Postgres/pgDiscipline.h"

static const pgIntroduced kIntro[] =
{
	{ 13, 0, PG_F_NO_PLTEMPLATE }
};

extern const pgVersionModule pgMod_13 = { 13, 0, "13", kIntro, (int)(sizeof(kIntro) / sizeof(kIntro[0])) };
