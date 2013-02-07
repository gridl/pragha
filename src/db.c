/*************************************************************************/
/* Copyright (C) 2007-2009 sujith <m.sujith@gmail.com>			 */
/* Copyright (C) 2009-2010 matias <mati86dl@gmail.com>			 */
/* 									 */
/* This program is free software: you can redistribute it and/or modify	 */
/* it under the terms of the GNU General Public License as published by	 */
/* the Free Software Foundation, either version 3 of the License, or	 */
/* (at your option) any later version.					 */
/* 									 */
/* This program is distributed in the hope that it will be useful,	 */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of	 */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	 */
/* GNU General Public License for more details.				 */
/* 									 */
/* You should have received a copy of the GNU General Public License	 */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>. */
/*************************************************************************/

#include "pragha.h"

static void db_add_new_track(PraghaDatabase *database,
			     gint location_id,
			     gint artist_id,
			     gint album_id,
			     gint genre_id,
			     gint year_id,
			     gint comment_id,
			     guint track_no,
			     gint length,
			     gint channels,
			     gint bitrate,
			     gint samplerate,
			     gint file_type,
			     const gchar *title)
{
	const gchar *sql = "INSERT INTO TRACK ("
				"location, "
				"track_no, "
				"artist, "
				"album, "
				"genre, "
				"year, "
				"comment, "
				"bitrate, "
				"samplerate, "
				"length, "
				"channels, "
				"file_type, "
				"title) "
				"VALUES "
				"(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

	PraghaPreparedStatement *statement = pragha_database_create_statement (database, sql);
	pragha_prepared_statement_bind_int (statement, 1, location_id);
	pragha_prepared_statement_bind_int (statement, 2, track_no);
	pragha_prepared_statement_bind_int (statement, 3, artist_id);
	pragha_prepared_statement_bind_int (statement, 4, album_id);
	pragha_prepared_statement_bind_int (statement, 5, genre_id);
	pragha_prepared_statement_bind_int (statement, 6, year_id);
	pragha_prepared_statement_bind_int (statement, 7, comment_id);
	pragha_prepared_statement_bind_int (statement, 8, bitrate);
	pragha_prepared_statement_bind_int (statement, 9, samplerate);
	pragha_prepared_statement_bind_int (statement, 10, length);
	pragha_prepared_statement_bind_int (statement, 11, channels);
	pragha_prepared_statement_bind_int (statement, 12, file_type);
	pragha_prepared_statement_bind_string (statement, 13, title);
	pragha_prepared_statement_step (statement);
	pragha_prepared_statement_free (statement);
}

static void import_playlist_from_file_db(const gchar *playlist_file, PraghaDatabase *cdbase)
{
	gchar *playlist = NULL;
	gint playlist_id = 0;
	GSList *list = NULL, *i = NULL;

	playlist = get_display_filename(playlist_file, FALSE);

	if (pragha_database_find_playlist (cdbase, playlist))
		goto bad;

	playlist_id = pragha_database_add_new_playlist (cdbase, playlist);

#ifdef HAVE_PLPARSER
	gchar *uri = g_filename_to_uri (playlist_file, NULL, NULL);
	list = pragha_totem_pl_parser_parse_from_uri(uri);
	g_free (uri);
#else
	list = pragha_pl_parser_parse_from_file_by_extension (playlist_file);
#endif

	if(list) {
		for (i=list; i != NULL; i = i->next) {
			pragha_database_add_playlist_track (cdbase, playlist_id, i->data);
			g_free(i->data);
		}
		g_slist_free(list);
	}

bad:
	g_free(playlist);
}

void add_new_musicobject_db(PraghaDatabase *cdbase, PraghaMusicobject *mobj)
{
	const gchar *file, *artist, *album, *genre, *comment;
	gint location_id = 0, artist_id = 0, album_id = 0, genre_id = 0, year_id = 0, comment_id;

	if (mobj) {
		file = pragha_musicobject_get_file (mobj);
		artist = pragha_musicobject_get_artist (mobj);
		album = pragha_musicobject_get_album (mobj);
		genre = pragha_musicobject_get_genre (mobj);
		comment = pragha_musicobject_get_comment (mobj);

		/* Write location */

		if ((location_id = pragha_database_find_location (cdbase, file)) == 0)
			location_id = pragha_database_add_new_location (cdbase, file);

		/* Write artist */

		if ((artist_id = pragha_database_find_artist (cdbase, artist)) == 0)
			artist_id = pragha_database_add_new_artist (cdbase, artist);

		/* Write album */

		if ((album_id = pragha_database_find_album (cdbase, album)) == 0)
			album_id = pragha_database_add_new_album (cdbase, album);

		/* Write genre */

		if ((genre_id = pragha_database_find_genre (cdbase, genre)) == 0)
			genre_id = pragha_database_add_new_genre (cdbase, genre);

		/* Write year */

		if ((year_id = pragha_database_find_year (cdbase, pragha_musicobject_get_year (mobj))) == 0)
			year_id = pragha_database_add_new_year (cdbase, pragha_musicobject_get_year (mobj));

		/* Write comment */

		if ((comment_id = pragha_database_find_comment (cdbase, comment)) == 0)
			comment_id = pragha_database_add_new_comment (cdbase, comment);

		/* Write track */

		db_add_new_track(cdbase,
				 location_id,
				 artist_id,
				 album_id,
				 genre_id,
				 year_id,
				 comment_id,
				 pragha_musicobject_get_track_no(mobj),
				 pragha_musicobject_get_length(mobj),
				 pragha_musicobject_get_channels(mobj),
				 pragha_musicobject_get_bitrate(mobj),
				 pragha_musicobject_get_samplerate(mobj),
				 pragha_musicobject_get_file_type(mobj),
				 pragha_musicobject_get_title(mobj));
	}
}

static void add_new_musicobject_from_file_db(const gchar *file, PraghaDatabase *cdbase)
{
	PraghaMusicobject *mobj = NULL;

	mobj = new_musicobject_from_file(file);
	if (mobj) {
		add_new_musicobject_db(cdbase, mobj);
		g_object_unref(mobj);
	}
}

void pragha_database_add_new_file(PraghaDatabase *cdbase, const gchar *file)
{
	if (pragha_pl_parser_guess_format_from_extension(file) != PL_FORMAT_UNKNOWN) {
		import_playlist_from_file_db(file, cdbase);
	}
	else {
		add_new_musicobject_from_file_db(file, cdbase);
	}
}

/**************/
/* Public API */
/**************/

gchar *
pragha_database_get_filename_from_location_id(PraghaDatabase *cdbase, gint location_id)
{
	PraghaPreparedStatement *statement;
	const gchar *sql;
	gchar *file = NULL;

	sql = "SELECT name FROM LOCATION WHERE id = ?";
	statement = pragha_database_create_statement (cdbase, sql);
	pragha_prepared_statement_bind_int (statement, 1, location_id);

	if(pragha_prepared_statement_step (statement))
		file = g_strdup(pragha_prepared_statement_get_string(statement, 0));
	else
		g_warning("Unable to find filename for location id: %d", location_id);

	pragha_prepared_statement_free (statement);

	return file;
}

gint delete_location_hdd(gint location_id, PraghaDatabase *cdbase)
{
	gint ret = 0;
	gchar *file = NULL;

	file = pragha_database_get_filename_from_location_id(cdbase, location_id);

	if (file) {
		ret = g_unlink(file);
		if (ret != 0)
			g_warning("%s", strerror(ret));
		else
			CDEBUG(DBG_VERBOSE, "Deleted file: %s", file);
		g_free(file);
	}

	return ret;
}

void db_update_track(PraghaDatabase *database,
		     gint location_id, gint changed,
		     gint track_no, const gchar *title,
		     gint artist_id, gint album_id, gint genre_id, gint year_id, gint comment_id)
{
	const gchar *sql;
	PraghaPreparedStatement *statement;

	if (changed & TAG_TNO_CHANGED) {
		sql = "UPDATE TRACK SET track_no = ? WHERE LOCATION = ?";
		statement = pragha_database_create_statement (database, sql);
		pragha_prepared_statement_bind_int (statement, 1, track_no);
		pragha_prepared_statement_bind_int (statement, 2, location_id);
		pragha_prepared_statement_step (statement);
		pragha_prepared_statement_free (statement);
	}
	if (changed & TAG_TITLE_CHANGED) {
		sql = "UPDATE TRACK SET title = ? WHERE LOCATION = ?";
		statement = pragha_database_create_statement (database, sql);
		pragha_prepared_statement_bind_string (statement, 1, title);
		pragha_prepared_statement_bind_int (statement, 2, location_id);
		pragha_prepared_statement_step (statement);
		pragha_prepared_statement_free (statement);
	}
	if (changed & TAG_ARTIST_CHANGED) {
		sql = "UPDATE TRACK SET artist = ? WHERE LOCATION = ?";
		statement = pragha_database_create_statement (database, sql);
		pragha_prepared_statement_bind_int (statement, 1, artist_id);
		pragha_prepared_statement_bind_int (statement, 2, location_id);
		pragha_prepared_statement_step (statement);
		pragha_prepared_statement_free (statement);
	}
	if (changed & TAG_ALBUM_CHANGED) {
		sql = "UPDATE TRACK SET album = ? WHERE LOCATION = ?";
		statement = pragha_database_create_statement (database, sql);
		pragha_prepared_statement_bind_int (statement, 1, album_id);
		pragha_prepared_statement_bind_int (statement, 2, location_id);
		pragha_prepared_statement_step (statement);
		pragha_prepared_statement_free (statement);
	}
	if (changed & TAG_GENRE_CHANGED) {
		sql = "UPDATE TRACK SET genre = ? WHERE LOCATION = ?";
		statement = pragha_database_create_statement (database, sql);
		pragha_prepared_statement_bind_int (statement, 1, genre_id);
		pragha_prepared_statement_bind_int (statement, 2, location_id);
		pragha_prepared_statement_step (statement);
		pragha_prepared_statement_free (statement);
	}
	if (changed & TAG_YEAR_CHANGED) {
		sql = "UPDATE TRACK SET year = ? WHERE LOCATION = ?";
		statement = pragha_database_create_statement (database, sql);
		pragha_prepared_statement_bind_int (statement, 1, year_id);
		pragha_prepared_statement_bind_int (statement, 2, location_id);
		pragha_prepared_statement_step (statement);
		pragha_prepared_statement_free (statement);
	}
	if (changed & TAG_COMMENT_CHANGED) {
		sql = "UPDATE TRACK SET comment = ? WHERE LOCATION = ?";
		statement = pragha_database_create_statement (database, sql);
		pragha_prepared_statement_bind_int (statement, 1, comment_id);
		pragha_prepared_statement_bind_int (statement, 2, location_id);
		pragha_prepared_statement_step (statement);
		pragha_prepared_statement_free (statement);
	}
}

void
pragha_db_update_local_files_change_tag(PraghaDatabase *cdbase, GArray *loc_arr, gint changed, PraghaMusicobject *mobj)
{
	gint track_no = 0, artist_id = 0, album_id = 0, genre_id = 0, year_id = 0, comment_id = 0;
	guint i = 0, elem = 0;

	if (!changed)
		return;

	if (!loc_arr)
		return;

	CDEBUG(DBG_VERBOSE, "Tags Changed: 0x%x", changed);

	if (changed & TAG_TNO_CHANGED) {
		track_no = pragha_musicobject_get_track_no(mobj);
	}
	if (changed & TAG_TITLE_CHANGED) {
	}
	if (changed & TAG_ARTIST_CHANGED) {
		const gchar *artist = pragha_musicobject_get_artist (mobj);
		artist_id = pragha_database_find_artist (cdbase, artist);
		if (!artist_id)
			artist_id = pragha_database_add_new_artist (cdbase, artist);
	}
	if (changed & TAG_ALBUM_CHANGED) {
		const gchar *album = pragha_musicobject_get_album (mobj);
		album_id = pragha_database_find_album (cdbase, album);
		if (!album_id)
			album_id = pragha_database_add_new_album (cdbase, album);
	}
	if (changed & TAG_GENRE_CHANGED) {
		const gchar *genre = pragha_musicobject_get_genre (mobj);
		genre_id = pragha_database_find_genre (cdbase, genre);
		if (!genre_id)
			genre_id = pragha_database_add_new_genre (cdbase, genre);
	}
	if (changed & TAG_YEAR_CHANGED) {
		year_id = pragha_database_find_year (cdbase, pragha_musicobject_get_year (mobj));
		if (!year_id)
			year_id = pragha_database_add_new_year (cdbase, pragha_musicobject_get_year (mobj));
	}
	if (changed & TAG_COMMENT_CHANGED) {
		const gchar *comment = pragha_musicobject_get_comment (mobj);
		comment_id = pragha_database_find_comment (cdbase, comment);
		if (!comment_id)
			comment_id = pragha_database_add_new_comment (cdbase, comment);
	}

	db_begin_transaction(cdbase);
	if (loc_arr) {
		elem = 0;
		for(i = 0; i < loc_arr->len; i++) {
			elem = g_array_index(loc_arr, gint, i);
			if (elem) {
				db_update_track(cdbase,
						elem, changed,
						track_no,
						pragha_musicobject_get_title (mobj),
						artist_id,
						album_id,
						genre_id,
						year_id,
						comment_id);
			}
		}
	}
	db_commit_transaction(cdbase);
}

/* Get the names of all the playlists stored in the DB.
   Returned NULL terminated array of strings that has to freed by caller. */

gchar** get_playlist_names_db(PraghaDatabase *cdbase)
{
	gchar *query;
	PraghaDbResponse result;
	gchar **playlists = NULL;
	gint i, j=0;

	query = g_strdup_printf("SELECT NAME FROM PLAYLIST WHERE NAME != \"%s\";",
				SAVE_PLAYLIST_STATE);
	if (pragha_database_exec_sqlite_query(cdbase, query, &result)) {
		if (result.no_rows) {
			playlists = g_malloc0((result.no_rows+1) * sizeof(gchar *));
			for_each_result_row(result, i) {
				playlists[j] = g_strdup(result.resultp[i]);
				j++;
			}
			playlists[j] = NULL;
		}
		sqlite3_free_table(result.resultp);
	}

	return playlists;
}

/* Get the number of all the playlists stored in the DB. */

gint get_playlist_count_db(PraghaDatabase *cdbase)
{
	gchar *query;
	PraghaDbResponse result;
	gint n_playlists = 0;

	query = g_strdup_printf("SELECT COUNT() FROM PLAYLIST WHERE NAME != \"%s\";",
				SAVE_PLAYLIST_STATE);
	if (pragha_database_exec_sqlite_query(cdbase, query, &result)) {
		n_playlists = atoi(result.resultp[1]);
		sqlite3_free_table(result.resultp);
	}

	return n_playlists;
}

/* Get the number of all trackslist tracks currently in the DB. */

gint get_tracklist_count_db(PraghaDatabase *cdbase)
{
	gchar *query;
	PraghaDbResponse result;
	/* this ID should be cached during open */
	gint playlist_id = pragha_database_find_playlist (cdbase, SAVE_PLAYLIST_STATE);
	gint n_playlists = 0;
	query = g_strdup_printf("SELECT COUNT() FROM PLAYLIST_TRACKS WHERE PLAYLIST=%d;", playlist_id);
	if (pragha_database_exec_sqlite_query(cdbase, query, &result)) {
		n_playlists = atoi(result.resultp[1]);
		sqlite3_free_table(result.resultp);
	}

	return n_playlists;
}

void delete_playlist_db(const gchar *playlist, PraghaDatabase *cdbase)
{
	gint playlist_id;
	gchar *query;

	if (string_is_empty(playlist)) {
		g_warning("Playlist name is NULL");
		return;
	}

	playlist_id = pragha_database_find_playlist (cdbase, playlist);

	if (!playlist_id) {
		g_warning("Playlist doesn't exist");
		return;
	}

	query = g_strdup_printf("DELETE FROM PLAYLIST_TRACKS WHERE PLAYLIST=%d;",
				playlist_id);
	pragha_database_exec_sqlite_query(cdbase, query, NULL);

	query = g_strdup_printf("DELETE FROM PLAYLIST WHERE ID=%d;",
				playlist_id);
	pragha_database_exec_sqlite_query(cdbase, query, NULL);
}

/* Flushes all the tracks in a given playlist */

void flush_playlist_db(gint playlist_id, PraghaDatabase *cdbase)
{
	gchar *query;

	query = g_strdup_printf("DELETE FROM PLAYLIST_TRACKS WHERE PLAYLIST=%d;",
				playlist_id);
	pragha_database_exec_sqlite_query(cdbase, query, NULL);
}

void delete_radio_db(const gchar *radio, PraghaDatabase *cdbase)
{
	gint radio_id;
	gchar *query;

	if (string_is_empty(radio)) {
		g_warning("Radio name is NULL");
		return;
	}

	radio_id = pragha_database_find_radio (cdbase, radio);

	if (!radio_id) {
		g_warning("Radio doesn't exist");
		return;
	}

	query = g_strdup_printf("DELETE FROM RADIO_TRACKS WHERE RADIO=%d;",
				radio_id);
	pragha_database_exec_sqlite_query(cdbase, query, NULL);

	query = g_strdup_printf("DELETE FROM RADIO WHERE ID=%d;",
				radio_id);
	pragha_database_exec_sqlite_query(cdbase, query, NULL);
}

/* Flushes all the tracks in a given playlist */

void flush_radio_db(gint radio_id, PraghaDatabase *cdbase)
{
	gchar *query;

	query = g_strdup_printf("DELETE FROM RADIO_TRACKS WHERE RADIO=%d;",
				radio_id);
	pragha_database_exec_sqlite_query(cdbase, query, NULL);
}

void flush_db(PraghaDatabase *cdbase)
{
	pragha_database_exec_query (cdbase, "DELETE FROM TRACK");
	pragha_database_exec_query (cdbase, "DELETE FROM LOCATION");
	pragha_database_exec_query (cdbase, "DELETE FROM ARTIST");
	pragha_database_exec_query (cdbase, "DELETE FROM ALBUM");
	pragha_database_exec_query (cdbase, "DELETE FROM GENRE");
	pragha_database_exec_query (cdbase, "DELETE FROM YEAR");
	pragha_database_exec_query (cdbase, "DELETE FROM COMMENT");
}

/* Flush unused artists, albums, genres, years */

void flush_stale_entries_db(PraghaDatabase *cdbase)
{
	pragha_database_exec_query (cdbase, "DELETE FROM ARTIST WHERE id NOT IN (SELECT artist FROM TRACK);");
	pragha_database_exec_query (cdbase, "DELETE FROM ALBUM WHERE id NOT IN (SELECT album FROM TRACK);");
	pragha_database_exec_query (cdbase, "DELETE FROM GENRE WHERE id NOT IN (SELECT genre FROM TRACK);");
	pragha_database_exec_query (cdbase, "DELETE FROM YEAR WHERE id NOT IN (SELECT year FROM TRACK);");
	pragha_database_exec_query (cdbase, "DELETE FROM COMMENT WHERE id NOT IN (SELECT comment FROM TRACK);");
}

gint drop_dbase_schema(PraghaDatabase *cdbase)
{
	gint i, ret = 0;

	const gchar *queries[] = {
		"DROP TABLE ALBUM",
		"DROP TABLE ARTIST",
		"DROP TABLE GENRE",
		"DROP TABLE LOCATION",
		"DROP TABLE TRACK",
		"DROP TABLE YEAR",
		"DROP TABLE COMMENT"
	};

	for (i = 0; i < G_N_ELEMENTS(queries); i++) {
		if (!pragha_database_exec_query (cdbase, queries[i]))
			ret = -1;
	}

	return ret;
}

static gint db_get_table_count(PraghaDatabase *cdbase, const gchar *table)
{
	gchar *query;
	PraghaDbResponse result;
	gint ret = 0;

	query = g_strdup_printf("SELECT COUNT() FROM %s;", table);
	if (pragha_database_exec_sqlite_query(cdbase, query, &result)) {
		ret = atoi(result.resultp[1]);
		sqlite3_free_table(result.resultp);
	}

	return ret;
}

gint db_get_artist_count(PraghaDatabase *cdbase)
{
	return db_get_table_count (cdbase, "ARTIST");
}

gint db_get_album_count(PraghaDatabase *cdbase)
{
	return db_get_table_count (cdbase, "ALBUM");
}

gint db_get_track_count(PraghaDatabase *cdbase)
{
	return db_get_table_count (cdbase, "TRACK");
}

void db_begin_transaction(PraghaDatabase *cdbase)
{
	pragha_database_exec_query (cdbase, "BEGIN TRANSACTION");
}

void db_commit_transaction(PraghaDatabase *cdbase)
{
	pragha_database_exec_query (cdbase, "END TRANSACTION");
}
