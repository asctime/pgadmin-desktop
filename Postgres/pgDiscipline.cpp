//////////////////////////////////////////////////////////////////////////
//
//
// Copyright (C) 2002 - 2016, The pgAdmin Development Team
// Copyright (C) 2026, asctime
// Copyright (C) 2027, asctime
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////

#include "Postgres/pgDiscipline.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern const pgVersionModule pgMod_84;
extern const pgVersionModule pgMod_90;
extern const pgVersionModule pgMod_91;
extern const pgVersionModule pgMod_92;
extern const pgVersionModule pgMod_93;
extern const pgVersionModule pgMod_94;
extern const pgVersionModule pgMod_95;
extern const pgVersionModule pgMod_96;
extern const pgVersionModule pgMod_10;
extern const pgVersionModule pgMod_11;
extern const pgVersionModule pgMod_12;
extern const pgVersionModule pgMod_13;
extern const pgVersionModule pgMod_14;
extern const pgVersionModule pgMod_15;
extern const pgVersionModule pgMod_16;
extern const pgVersionModule pgMod_17;
extern const pgVersionModule pgMod_18;
extern const pgVersionModule pgMod_19;

static const pgVersionModule *const kModules[] =
{
	&pgMod_84, &pgMod_90, &pgMod_91, &pgMod_92, &pgMod_93,
	&pgMod_94, &pgMod_95, &pgMod_96, &pgMod_10, &pgMod_11,
	&pgMod_12, &pgMod_13, &pgMod_14, &pgMod_15, &pgMod_16,
	&pgMod_17, &pgMod_18, &pgMod_19
};

static const int kHeadline[] =
{
	PG_F_RLS,
	PG_F_PARTITION,
	PG_F_PROCEDURE,
	PG_F_GENERATED_STORED,
	PG_F_VIRTUAL_GENERATED,
	PG_F_MERGE,
	PG_F_MAINTAIN,
	PG_F_NOT_ENFORCED,
	PG_F_REPACK
};

static bool versionAtLeast(int major, int minor, int needMajor, int needMinor)
{
	if (major > needMajor)
		return true;
	if (major < needMajor)
		return false;
	return minor >= needMinor;
}

bool pgFeatureEnabled(int major, int minor, int feature)
{
	if (feature < 0 || feature >= PG_F_COUNT)
		return false;

	for (unsigned i = 0; i < sizeof(kModules) / sizeof(kModules[0]); ++i)
	{
		const pgVersionModule *mod = kModules[i];
		for (int n = 0; n < mod->count; ++n)
		{
			if (mod->introduced[n].feature == feature)
				return versionAtLeast(major, minor, mod->introduced[n].major, mod->introduced[n].minor);
		}
	}
	return false;
}

const char *pgFeatureName(int feature)
{
	switch (feature)
	{
		case PG_F_RECOVERY: return "recovery";
		case PG_F_REPLICATION_ROLE: return "replication-role";
		case PG_F_COLLATION: return "collation";
		case PG_F_JSON: return "json";
		case PG_F_MATVIEW: return "matview";
		case PG_F_EVENT_TRIGGER: return "event-trigger";
		case PG_F_JSONB: return "jsonb";
		case PG_F_REPL_SLOTS: return "replication-slots";
		case PG_F_RLS: return "rls";
		case PG_F_BRIN: return "brin";
		case PG_F_UPSERT: return "upsert";
		case PG_F_NO_ROLCATUPDATE: return "no-rolcatupdate";
		case PG_F_PARALLEL: return "parallel";
		case PG_F_WAIT_EVENT: return "wait-event";
		case PG_F_PARTITION: return "partition";
		case PG_F_IDENTITY: return "identity";
		case PG_F_PUBLICATION: return "publication";
		case PG_F_PG_SEQUENCE: return "pg_sequence";
		case PG_F_SCRAM: return "scram";
		case PG_F_PROKIND: return "prokind";
		case PG_F_PROCEDURE: return "procedure";
		case PG_F_INDEX_INCLUDE: return "index-include";
		case PG_F_GENERATED_STORED: return "generated-stored";
		case PG_F_NO_ADSRC: return "no-adsrc";
		case PG_F_NO_RELHASOIDS: return "no-relhasoids";
		case PG_F_NO_PLTEMPLATE: return "no-pltemplate";
		case PG_F_ATTCOMPRESSION: return "compression";
		case PG_F_MULTIRANGE: return "multirange";
		case PG_F_PROC_OUT: return "procedure-out";
		case PG_F_MERGE: return "merge";
		case PG_F_NULLS_NOT_DISTINCT: return "nulls-not-distinct";
		case PG_F_NO_DATLASTSYSOID: return "no-datlastsysoid";
		case PG_F_PUBLIC_NOT_OPEN: return "public-locked-down";
		case PG_F_GRANT_INHERIT_SET: return "grant-inherit-set";
		case PG_F_PG_STAT_IO: return "pg_stat_io";
		case PG_F_MAINTAIN: return "maintain";
		case PG_F_STAT_CHECKPOINTER: return "pg_stat_checkpointer";
		case PG_F_JSON_TABLE: return "json_table";
		case PG_F_SUBFAILOVER: return "subscription-failover";
		case PG_F_NOT_ENFORCED: return "not-enforced";
		case PG_F_VIRTUAL_GENERATED: return "generated-virtual";
		case PG_F_UUIDV7: return "uuidv7";
		case PG_F_RETURNING_OLD: return "returning-old-new";
		case PG_F_REPACK: return "repack";
		case PG_F_PARALLEL_AUTOVACUUM: return "parallel-autovacuum";
		case PG_F_IGNORE_NULLS: return "ignore-nulls";
		case PG_F_ON_CONFLICT_DO_SELECT: return "on-conflict-do-select";
		default: return "";
	}
}

int pgDisciplineCount()
{
	return (int)(sizeof(kModules) / sizeof(kModules[0]));
}

const pgVersionModule *pgDisciplineAt(int index)
{
	if (index < 0 || index >= pgDisciplineCount())
		return 0;
	return kModules[index];
}

static int labelEqual(const char *a, const char *b)
{
	while (*a && *b)
	{
		char ca = *a;
		char cb = *b;
		if (ca >= 'A' && ca <= 'Z')
			ca = (char)(ca - 'A' + 'a');
		if (cb >= 'A' && cb <= 'Z')
			cb = (char)(cb - 'A' + 'a');
		if (ca != cb)
			return 0;
		++a;
		++b;
	}
	return *a == 0 && *b == 0;
}

bool pgParseDiscipline(const char *label, int *major, int *minor)
{
	if (!label || !label[0] || !major || !minor)
		return false;
	if (labelEqual(label, "auto"))
		return false;

	int M = 0;
	int m = 0;
	int n = sscanf(label, "%d.%d", &M, &m);
	if (n < 1 || M <= 0)
		return false;
	if (n < 2 || M >= 10)
		m = 0;
	*major = M;
	*minor = m;
	return true;
}

const char *pgDisciplineLabel(int major, int minor)
{
	for (int i = 0; i < pgDisciplineCount(); ++i)
	{
		const pgVersionModule *mod = kModules[i];
		if (mod->major == major && mod->minor == minor)
			return mod->label;
	}
	return "unknown";
}

const char *pgDisciplineSummary(int major, int minor)
{
	static char buf[512];
	buf[0] = 0;
	size_t used = 0;
	for (unsigned i = 0; i < sizeof(kHeadline) / sizeof(kHeadline[0]); ++i)
	{
		if (!pgFeatureEnabled(major, minor, kHeadline[i]))
			continue;
		const char *name = pgFeatureName(kHeadline[i]);
		size_t len = strlen(name);
		if (used && used + 2 < sizeof(buf))
		{
			buf[used++] = ',';
			buf[used++] = ' ';
		}
		if (used + len >= sizeof(buf))
			break;
		memcpy(buf + used, name, len);
		used += len;
		buf[used] = 0;
	}
	if (!buf[0])
		return "legacy";
	return buf;
}

bool pgDisciplineSelfCheck()
{
	if (!pgFeatureEnabled(9, 4, PG_F_JSONB))
		return false;
	if (pgFeatureEnabled(9, 4, PG_F_RLS))
		return false;
	if (!pgFeatureEnabled(9, 4, PG_F_MATVIEW))
		return false;
	if (pgFeatureEnabled(10, 0, PG_F_PROKIND))
		return false;
	if (!pgFeatureEnabled(11, 0, PG_F_PROCEDURE))
		return false;
	if (pgFeatureEnabled(11, 0, PG_F_GENERATED_STORED))
		return false;
	if (!pgFeatureEnabled(12, 0, PG_F_NO_ADSRC))
		return false;
	if (pgFeatureEnabled(17, 0, PG_F_NOT_ENFORCED))
		return false;
	if (!pgFeatureEnabled(18, 0, PG_F_VIRTUAL_GENERATED))
		return false;
	if (pgFeatureEnabled(18, 0, PG_F_REPACK))
		return false;
	if (!pgFeatureEnabled(19, 0, PG_F_REPACK))
		return false;
	if (!pgFeatureEnabled(19, 0, PG_F_PARTITION))
		return false;
	if (!pgFeatureEnabled(16, 0, PG_F_PARALLEL))
		return false;
	int M = 0, m = 0;
	if (!pgParseDiscipline("9.4", &M, &m) || M != 9 || m != 4)
		return false;
	if (!pgParseDiscipline("18", &M, &m) || M != 18 || m != 0)
		return false;
	if (pgParseDiscipline("Auto", &M, &m))
		return false;
	return true;
}
