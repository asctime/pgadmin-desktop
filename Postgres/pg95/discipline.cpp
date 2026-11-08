#include "Postgres/pgDiscipline.h"

static const pgIntroduced kIntro[] =
{
	{ 9, 5, PG_F_RLS },
	{ 9, 5, PG_F_BRIN },
	{ 9, 5, PG_F_UPSERT },
	{ 9, 5, PG_F_NO_ROLCATUPDATE }
};

extern const pgVersionModule pgMod_95 = { 9, 5, "9.5", kIntro, (int)(sizeof(kIntro) / sizeof(kIntro[0])) };
