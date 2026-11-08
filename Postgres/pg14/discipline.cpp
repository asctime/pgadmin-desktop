#include "Postgres/pgDiscipline.h"

static const pgIntroduced kIntro[] =
{
	{ 14, 0, PG_F_ATTCOMPRESSION },
	{ 14, 0, PG_F_MULTIRANGE },
	{ 14, 0, PG_F_PROC_OUT }
};

extern const pgVersionModule pgMod_14 = { 14, 0, "14", kIntro, (int)(sizeof(kIntro) / sizeof(kIntro[0])) };
