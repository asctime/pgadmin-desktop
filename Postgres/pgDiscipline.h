//////////////////////////////////////////////////////////////////////////
//
//
// Copyright (C) 2002 - 2016, The pgAdmin Development Team
// Copyright (C) 2026, asctime
// Copyright (C) 2027, asctime
// This software is released under the PostgreSQL Licence
//
// Runtime catalogue discipline for every PostgreSQL release this tree
// still speaks, from the legacy catalogue floor through the current
// supported release. SQL generation consults the effective version:
// the server's own version, unless a server setting overrides it.
//
//////////////////////////////////////////////////////////////////////////

#ifndef PGDISCIPLINE_H
#define PGDISCIPLINE_H

enum pgFeature
{
	PG_F_RECOVERY = 0,
	PG_F_REPLICATION_ROLE,
	PG_F_COLLATION,
	PG_F_JSON,
	PG_F_MATVIEW,
	PG_F_EVENT_TRIGGER,
	PG_F_JSONB,
	PG_F_REPL_SLOTS,
	PG_F_RLS,
	PG_F_BRIN,
	PG_F_UPSERT,
	PG_F_NO_ROLCATUPDATE,
	PG_F_PARALLEL,
	PG_F_WAIT_EVENT,
	PG_F_PARTITION,
	PG_F_IDENTITY,
	PG_F_PUBLICATION,
	PG_F_PG_SEQUENCE,
	PG_F_SCRAM,
	PG_F_PROKIND,
	PG_F_PROCEDURE,
	PG_F_INDEX_INCLUDE,
	PG_F_GENERATED_STORED,
	PG_F_NO_ADSRC,
	PG_F_NO_RELHASOIDS,
	PG_F_NO_PLTEMPLATE,
	PG_F_ATTCOMPRESSION,
	PG_F_MULTIRANGE,
	PG_F_PROC_OUT,
	PG_F_MERGE,
	PG_F_NULLS_NOT_DISTINCT,
	PG_F_NO_DATLASTSYSOID,
	PG_F_PUBLIC_NOT_OPEN,
	PG_F_GRANT_INHERIT_SET,
	PG_F_PG_STAT_IO,
	PG_F_MAINTAIN,
	PG_F_STAT_CHECKPOINTER,
	PG_F_JSON_TABLE,
	PG_F_SUBFAILOVER,
	PG_F_NOT_ENFORCED,
	PG_F_VIRTUAL_GENERATED,
	PG_F_UUIDV7,
	PG_F_RETURNING_OLD,
	PG_F_REPACK,
	PG_F_PARALLEL_AUTOVACUUM,
	PG_F_IGNORE_NULLS,
	PG_F_ON_CONFLICT_DO_SELECT,
	PG_F_COUNT
};

struct pgIntroduced
{
	int major;
	int minor;
	int feature;
};

struct pgVersionModule
{
	int major;
	int minor;
	const char *label;
	const pgIntroduced *introduced;
	int count;
};

bool pgFeatureEnabled(int major, int minor, int feature);
const char *pgFeatureName(int feature);
int pgDisciplineCount();
const pgVersionModule *pgDisciplineAt(int index);
bool pgParseDiscipline(const char *label, int *major, int *minor);
const char *pgDisciplineLabel(int major, int minor);
const char *pgDisciplineSummary(int major, int minor);
bool pgDisciplineSelfCheck();

#endif
