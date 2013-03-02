/*************************************************************************/
/* Copyright (C) 2012-2013 matias <mati86dl@gmail.com>			 */
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

#include "pragha-preferences.h"
#include "pragha.h"

G_DEFINE_TYPE(PraghaPreferences, pragha_preferences, G_TYPE_OBJECT)

struct _PraghaPreferencesPrivate
{
	GKeyFile  *rc_keyfile;
	gchar     *rc_filepath;

	/* Search preferences. */
	gboolean   instant_search;
	gboolean   approximate_search;
	/* LibraryPane preferences */
	gint       library_style;
	gboolean   sort_by_year;
	gboolean   fuse_folders;
	/* Playlist preferences. */
	gboolean   shuffle;
	gboolean   repeat;
	gboolean   use_hint;
	gboolean   restore_playlist;
	/* Audio preferences. */
	gchar     *audio_sink;
	gchar     *audio_device;
	gboolean   software_mixer;
	gchar     *audio_cd_device;
	/* Window preferences. */
	gboolean   lateral_panel;
	gint       sidebar_size;
	gboolean   show_album_art;
	gint       album_art_size;
	gboolean   show_status_bar;

	/* Misc preferences. */
	gboolean   add_recursively;
	gboolean   timer_remaining_mode;
};

enum
{
	PROP_0,
	PROP_INSTANT_SEARCH,
	PROP_APPROXIMATE_SEARCH,
	PROP_LIBRARY_STYLE,
	PROP_LIBRARY_SORT_BY_YEAR,
	PROP_LIBRARY_FUSE_FOLDERS,
	PROP_SHUFFLE,
	PROP_REPEAT,
	PROP_USE_HINT,
	PROP_RESTORE_PLAYLIST,
	PROP_AUDIO_SINK,
	PROP_AUDIO_DEVICE,
	PROP_SOFTWARE_MIXER,
	PROP_AUDIO_CD_DEVICE,
	PROP_LATERAL_PANEL,
	PROP_SIDEBAR_SIZE,
	PROP_SHOW_ALBUM_ART,
	PROP_ALBUM_ART_SIZE,
	PROP_SHOW_STATUS_BAR,
	PROP_ADD_RECURSIVELY,
	PROP_TIMER_REMAINING_MODE,
	LAST_PROP
};

static GParamSpec *gParamSpecs[LAST_PROP];

/**
 * pragha_preferences_get_double_list:
 *
 */
gdouble *
pragha_preferences_get_double_list (PraghaPreferences *preferences,
                                    const gchar *group_name,
                                    const gchar *key)
{
	g_return_val_if_fail(PRAGHA_IS_PREFERENCES(preferences), NULL);

	return g_key_file_get_double_list(preferences->priv->rc_keyfile,
	                                  group_name,
	                                  key,
	                                  NULL,
	                                  NULL);
}

/**
 * pragha_preferences_set_double_list
 *
 */
void
pragha_preferences_set_double_list (PraghaPreferences *preferences,
                                    const gchar *group_name,
                                    const gchar *key,
                                    gdouble list[],
                                    gsize length)
{
	g_return_if_fail(PRAGHA_IS_PREFERENCES(preferences));

	g_key_file_set_double_list(preferences->priv->rc_keyfile,
	                           group_name,
	                           key,
	                           list,
	                           length);
}

/**
 * pragha_preferences_get_integer_list:
 *
 */
gint *
pragha_preferences_get_integer_list (PraghaPreferences *preferences,
                                     const gchar *group_name,
                                     const gchar *key,
                                     gsize *length)
{
	g_return_val_if_fail(PRAGHA_IS_PREFERENCES(preferences), NULL);

	return g_key_file_get_integer_list(preferences->priv->rc_keyfile,
	                                   group_name,
	                                   key,
	                                   length,
	                                   NULL);
}

/**
 * pragha_preferences_set_integer_list
 *
 */
void
pragha_preferences_set_integer_list (PraghaPreferences *preferences,
                                     const gchar *group_name,
                                     const gchar *key,
                                     gint list[],
                                     gsize length)
{
	g_return_if_fail(PRAGHA_IS_PREFERENCES(preferences));

	g_key_file_set_integer_list(preferences->priv->rc_keyfile,
	                            group_name,
	                            key,
	                            list,
	                            length);
}

/**
 * pragha_preferences_get_string:
 *
 */
gchar *
pragha_preferences_get_string (PraghaPreferences *preferences,
                               const gchar *group_name,
                               const gchar *key)
{
	g_return_val_if_fail(PRAGHA_IS_PREFERENCES(preferences), NULL);

	return g_key_file_get_string(preferences->priv->rc_keyfile,
	                             group_name,
	                             key,
	                             NULL);
}

/**
 * pragha_preferences_set_string:
 *
 */
void
pragha_preferences_set_string (PraghaPreferences *preferences,
                               const gchar *group_name,
                               const gchar *key,
                               const gchar *string)
{
	g_return_if_fail(PRAGHA_IS_PREFERENCES(preferences));

	g_key_file_set_string(preferences->priv->rc_keyfile,
	                      group_name,
	                      key,
	                      string);
}

/**
 * pragha_preferences_get_string_list:
 *
 */
gchar **
pragha_preferences_get_string_list (PraghaPreferences *preferences,
                                    const gchar *group_name,
                                    const gchar *key,
                                    gsize *length)
{
	g_return_val_if_fail(PRAGHA_IS_PREFERENCES(preferences), NULL);

	return g_key_file_get_string_list(preferences->priv->rc_keyfile,
	                                  group_name,
	                                  key,
	                                  length,
	                                  NULL);
}

/**
 * pragha_preferences_set_string_list
 *
 */
void
pragha_preferences_set_string_list (PraghaPreferences *preferences,
                                     const gchar *group_name,
                                     const gchar *key,
                                     const gchar * const list[],
                                     gsize length)
{
	g_return_if_fail(PRAGHA_IS_PREFERENCES(preferences));

	g_key_file_set_string_list(preferences->priv->rc_keyfile,
	                           group_name,
	                           key,
	                           list,
	                           length);
}

/**
 * pragha_preferences_get_filename_list:
 *
 */
GSList *
pragha_preferences_get_filename_list (PraghaPreferences *preferences,
                                      const gchar *group_name,
                                      const gchar *key)
{
	gchar **clist;
	GSList *slist = NULL;
	gchar *filename = NULL;
	gsize i, length;
	GError *error = NULL;

	g_return_val_if_fail(PRAGHA_IS_PREFERENCES(preferences), NULL);


	clist = g_key_file_get_string_list(preferences->priv->rc_keyfile,
	                                   group_name,
	                                   key,
	                                   &length,
	                                   NULL);

	if (clist) {
		for (i = 0 ; i < length ; i++) {
			filename = g_filename_from_utf8(clist[i], -1, NULL, NULL, &error);
			if (!filename) {
				g_warning("Unable to get filename from UTF-8 string: %s", clist[i]);
				error = NULL;
				continue;
			}
			else {
				slist = g_slist_append(slist, filename);
			}
		}
		g_strfreev(clist);
	}

	return slist;
}

/**
 * pragha_preferences_set_filename_list:
 *
 */
void
pragha_preferences_set_filename_list (PraghaPreferences *preferences,
                                      const gchar *group_name,
                                      const gchar *key,
                                      GSList *list)
{
	gchar **clist;
	gchar *filename = NULL;
	gsize cnt = 0, i;
	GError *error = NULL;

	cnt = g_slist_length(list);
	clist = g_new0(gchar *, cnt);

	for (i = 0 ; i < cnt ; i++) {
		filename = g_filename_to_utf8(list->data, -1, NULL, NULL, &error);
		if (!filename) {
			g_warning("Unable to convert file to UTF-8: %s", (gchar *)list->data);
			g_error_free(error);
			error = NULL;
			list = list->next;
			continue;
		}
		clist[i] = filename;
		list = list->next;
	}

	g_key_file_set_string_list(preferences->priv->rc_keyfile,
	                           group_name,
	                           key,
	                           (const gchar **)clist,
	                           cnt);

	for(i = 0; i < cnt; i++) {
		g_free(clist[i]);
	}

	g_free(clist);
}

/**
 * pragha_preferences_remove_key:
 *
 */
void
pragha_preferences_remove_key (PraghaPreferences *preferences,
                               const gchar *group_name,
                               const gchar *key)
{
	g_return_if_fail(PRAGHA_IS_PREFERENCES(preferences));

	if (g_key_file_has_group(preferences->priv->rc_keyfile, group_name) &&
	    g_key_file_has_key(preferences->priv->rc_keyfile,
	                       group_name,
	                       key,
	                       NULL))
		g_key_file_remove_key(preferences->priv->rc_keyfile,
		                      group_name,
		                      key,
		                      NULL);
}

/**
 * pragha_preferences_get_instant_search:
 *
 */
gboolean
pragha_preferences_get_instant_search (PraghaPreferences *preferences)
{
	g_return_val_if_fail(PRAGHA_IS_PREFERENCES(preferences), FALSE);

	return preferences->priv->instant_search;
}

/**
 * pragha_preferences_set_instant_search:
 *
 */
void
pragha_preferences_set_instant_search (PraghaPreferences *preferences,
                                       gboolean instant_search)
{
	g_return_if_fail(PRAGHA_IS_PREFERENCES(preferences));

	preferences->priv->instant_search = instant_search;

	g_object_notify_by_pspec(G_OBJECT(preferences), gParamSpecs[PROP_INSTANT_SEARCH]);
}


/**
 * pragha_preferences_get_approximate_search:
 *
 */
gboolean
pragha_preferences_get_approximate_search (PraghaPreferences *preferences)
{
	g_return_val_if_fail(PRAGHA_IS_PREFERENCES(preferences), FALSE);

	return preferences->priv->approximate_search;
}

/**
 * pragha_preferences_set_approximate_search:
 *
 */
void
pragha_preferences_set_approximate_search (PraghaPreferences *preferences,
                                           gboolean approximate_search)
{
	g_return_if_fail(PRAGHA_IS_PREFERENCES(preferences));

	preferences->priv->approximate_search = approximate_search;

	g_object_notify_by_pspec(G_OBJECT(preferences), gParamSpecs[PROP_APPROXIMATE_SEARCH]);
}

/**
 * pragha_preferences_get_library_style:
 *
 */
gint
pragha_preferences_get_library_style (PraghaPreferences *preferences)
{
	g_return_val_if_fail(PRAGHA_IS_PREFERENCES(preferences), 0);

	return preferences->priv->library_style;
}

/**
 * pragha_preferences_set_library_style:
 *
 */
void
pragha_preferences_set_library_style (PraghaPreferences *preferences,
                                      gint library_style)
{
	g_return_if_fail(PRAGHA_IS_PREFERENCES(preferences));

	preferences->priv->library_style = library_style;

	g_object_notify_by_pspec(G_OBJECT(preferences), gParamSpecs[PROP_LIBRARY_STYLE]);
}

/**
 * pragha_preferences_get_sort_by_year:
 *
 */
gboolean
pragha_preferences_get_sort_by_year (PraghaPreferences *preferences)
{
	g_return_val_if_fail(PRAGHA_IS_PREFERENCES(preferences), FALSE);

	return preferences->priv->sort_by_year;
}

/**
 * pragha_preferences_sort_by_year:
 *
 */
void
pragha_preferences_set_sort_by_year (PraghaPreferences *preferences,
                                     gboolean sort_by_year)
{
	g_return_if_fail(PRAGHA_IS_PREFERENCES(preferences));

	preferences->priv->sort_by_year = sort_by_year;

	g_object_notify_by_pspec(G_OBJECT(preferences), gParamSpecs[PROP_LIBRARY_SORT_BY_YEAR]);
}

/**
 * pragha_preferences_get_fuse_folders:
 *
 */
gboolean
pragha_preferences_get_fuse_folders (PraghaPreferences *preferences)
{
	g_return_val_if_fail(PRAGHA_IS_PREFERENCES(preferences), FALSE);

	return preferences->priv->fuse_folders;
}

/**
 * pragha_preferences_fuse_folders:
 *
 */
void
pragha_preferences_set_fuse_folders (PraghaPreferences *preferences,
                                     gboolean fuse_folders)
{
	g_return_if_fail(PRAGHA_IS_PREFERENCES(preferences));

	preferences->priv->fuse_folders = fuse_folders;

	g_object_notify_by_pspec(G_OBJECT(preferences), gParamSpecs[PROP_LIBRARY_FUSE_FOLDERS]);
}

/**
 * pragha_preferences_get_shuffle:
 *
 */
gboolean
pragha_preferences_get_shuffle (PraghaPreferences *preferences)
{
	g_return_val_if_fail(PRAGHA_IS_PREFERENCES(preferences), FALSE);

	return preferences->priv->shuffle;
}

/**
 * pragha_preferences_set_shuffle:
 *
 */
void
pragha_preferences_set_shuffle (PraghaPreferences *preferences,
                                gboolean shuffle)
{
	g_return_if_fail(PRAGHA_IS_PREFERENCES(preferences));

	preferences->priv->shuffle = shuffle;

	g_object_notify_by_pspec(G_OBJECT(preferences), gParamSpecs[PROP_SHUFFLE]);
}

/**
 * pragha_preferences_get_repeat:
 *
 */
gboolean
pragha_preferences_get_repeat (PraghaPreferences *preferences)
{
	g_return_val_if_fail(PRAGHA_IS_PREFERENCES(preferences), FALSE);

	return preferences->priv->repeat;
}

/**
 * pragha_preferences_set_repeat:
 *
 */
void
pragha_preferences_set_repeat (PraghaPreferences *preferences,
                               gboolean repeat)
{
	g_return_if_fail(PRAGHA_IS_PREFERENCES(preferences));

	preferences->priv->repeat = repeat;

	g_object_notify_by_pspec(G_OBJECT(preferences), gParamSpecs[PROP_REPEAT]);
}

/**
 * pragha_preferences_get_use_hint:
 *
 */
gboolean
pragha_preferences_get_use_hint (PraghaPreferences *preferences)
{
	g_return_val_if_fail(PRAGHA_IS_PREFERENCES(preferences), FALSE);

	return preferences->priv->use_hint;
}

/**
 * pragha_preferences_set_use_hint:
 *
 */
void
pragha_preferences_set_use_hint (PraghaPreferences *preferences,
                                 gboolean use_hint)
{
	g_return_if_fail(PRAGHA_IS_PREFERENCES(preferences));

	preferences->priv->use_hint = use_hint;

	g_object_notify_by_pspec(G_OBJECT(preferences), gParamSpecs[PROP_USE_HINT]);
}

/**
 * pragha_preferences_get_restore_playlist:
 *
 */
gboolean
pragha_preferences_get_restore_playlist (PraghaPreferences *preferences)
{
	g_return_val_if_fail(PRAGHA_IS_PREFERENCES(preferences), FALSE);

	return preferences->priv->restore_playlist;
}

/**
 * pragha_preferences_set_restore_playlist:
 *
 */
void
pragha_preferences_set_restore_playlist (PraghaPreferences *preferences,
                                         gboolean restore_playlist)
{
	g_return_if_fail(PRAGHA_IS_PREFERENCES(preferences));

	preferences->priv->restore_playlist = restore_playlist;

	g_object_notify_by_pspec(G_OBJECT(preferences), gParamSpecs[PROP_RESTORE_PLAYLIST]);
}

/**
 * pragha_preferences_get_audio_sink:
 *
 */
const gchar *
pragha_preferences_get_audio_sink (PraghaPreferences *preferences)
{
	g_return_val_if_fail(PRAGHA_IS_PREFERENCES(preferences), NULL);

	return preferences->priv->audio_sink;
}

/**
 * pragha_preferences_set_audio_sink:
 *
 */
void
pragha_preferences_set_audio_sink (PraghaPreferences *preferences,
                                   const gchar *audio_sink)
{
	g_return_if_fail(PRAGHA_IS_PREFERENCES(preferences));

	g_free(preferences->priv->audio_sink);
	preferences->priv->audio_sink = g_strdup(audio_sink);

	g_object_notify_by_pspec(G_OBJECT(preferences), gParamSpecs[PROP_AUDIO_SINK]);
}

/**
 * pragha_preferences_get_audio_device:
 *
 */
const gchar *
pragha_preferences_get_audio_device (PraghaPreferences *preferences)
{
	g_return_val_if_fail(PRAGHA_IS_PREFERENCES(preferences), NULL);

	return preferences->priv->audio_device;
}

/**
 * pragha_preferences_set_audio_device:
 *
 */
void
pragha_preferences_set_audio_device (PraghaPreferences *preferences,
                                     const gchar *audio_device)
{
	g_return_if_fail(PRAGHA_IS_PREFERENCES(preferences));

	g_free(preferences->priv->audio_device);
	preferences->priv->audio_device = g_strdup(audio_device);

	g_object_notify_by_pspec(G_OBJECT(preferences), gParamSpecs[PROP_AUDIO_DEVICE]);
}

/**
 * pragha_preferences_get_software_mixer:
 *
 */
gboolean
pragha_preferences_get_software_mixer (PraghaPreferences *preferences)
{
	g_return_val_if_fail(PRAGHA_IS_PREFERENCES(preferences), FALSE);

	return preferences->priv->software_mixer;
}

/**
 * pragha_preferences_set_software_mixer:
 *
 */
void
pragha_preferences_set_software_mixer (PraghaPreferences *preferences,
                                       gboolean software_mixer)
{
	g_return_if_fail(PRAGHA_IS_PREFERENCES(preferences));

	preferences->priv->software_mixer = software_mixer;

	g_object_notify_by_pspec(G_OBJECT(preferences), gParamSpecs[PROP_SOFTWARE_MIXER]);
}

/**
 * pragha_preferences_get_audio_cd_device:
 *
 */
const gchar *
pragha_preferences_get_audio_cd_device (PraghaPreferences *preferences)
{
	g_return_val_if_fail(PRAGHA_IS_PREFERENCES(preferences), NULL);

	return preferences->priv->audio_cd_device;
}

/**
 * pragha_preferences_set_audio_cd_device:
 *
 */
void
pragha_preferences_set_audio_cd_device (PraghaPreferences *preferences,
                                        const gchar *audio_cd_device)
{
	g_return_if_fail(PRAGHA_IS_PREFERENCES(preferences));

	g_free(preferences->priv->audio_cd_device);
	preferences->priv->audio_cd_device = g_strdup(audio_cd_device);

	g_object_notify_by_pspec(G_OBJECT(preferences), gParamSpecs[PROP_AUDIO_CD_DEVICE]);
}

/**
 * pragha_preferences_get_lateral_panel:
 *
 */
gboolean
pragha_preferences_get_lateral_panel (PraghaPreferences *preferences)
{
	g_return_val_if_fail(PRAGHA_IS_PREFERENCES(preferences), FALSE);

	return preferences->priv->lateral_panel;
}

/**
 * pragha_preferences_set_lateral_panel:
 *
 */
void
pragha_preferences_set_lateral_panel (PraghaPreferences *preferences,
                                      gboolean lateral_panel)
{
	g_return_if_fail(PRAGHA_IS_PREFERENCES(preferences));

	preferences->priv->lateral_panel = lateral_panel;

	g_object_notify_by_pspec(G_OBJECT(preferences), gParamSpecs[PROP_LATERAL_PANEL]);
}

/**
 * pragha_preferences_get_sidebar_size:
 *
 */
gint
pragha_preferences_get_sidebar_size (PraghaPreferences *preferences)
{
	g_return_val_if_fail(PRAGHA_IS_PREFERENCES(preferences), DEFAULT_SIDEBAR_SIZE);

	return preferences->priv->sidebar_size;
}

/**
 * pragha_preferences_set_sidebar_size:
 *
 */
void
pragha_preferences_set_sidebar_size (PraghaPreferences *preferences,
                                     gint sidebar_size)
{
	g_return_if_fail(PRAGHA_IS_PREFERENCES(preferences));

	preferences->priv->sidebar_size = sidebar_size;

	g_object_notify_by_pspec(G_OBJECT(preferences), gParamSpecs[PROP_SIDEBAR_SIZE]);
}

/**
 * pragha_preferences_get_show_album_art:
 *
 */
gboolean
pragha_preferences_get_show_album_art (PraghaPreferences *preferences)
{
	g_return_val_if_fail(PRAGHA_IS_PREFERENCES(preferences), TRUE);

	return preferences->priv->show_album_art;
}

/**
 * pragha_preferences_set_show_album_art:
 *
 */
void
pragha_preferences_set_show_album_art (PraghaPreferences *preferences,
                                       gboolean show_album_art)
{
	g_return_if_fail(PRAGHA_IS_PREFERENCES(preferences));

	preferences->priv->show_album_art = show_album_art;

	g_object_notify_by_pspec(G_OBJECT(preferences), gParamSpecs[PROP_SHOW_ALBUM_ART]);
}

/**
 * pragha_preferences_get_album_art_size:
 *
 */
gint
pragha_preferences_get_album_art_size (PraghaPreferences *preferences)
{
	g_return_val_if_fail(PRAGHA_IS_PREFERENCES(preferences), DEFAULT_ALBUM_ART_SIZE);

	return preferences->priv->album_art_size;
}

/**
 * pragha_preferences_set_album_art_size:
 *
 */
void
pragha_preferences_set_album_art_size (PraghaPreferences *preferences,
                                       gint album_art_size)
{
	g_return_if_fail(PRAGHA_IS_PREFERENCES(preferences));

	preferences->priv->album_art_size = album_art_size;

	g_object_notify_by_pspec(G_OBJECT(preferences), gParamSpecs[PROP_ALBUM_ART_SIZE]);
}

/**
 * pragha_preferences_get_show_status_bar:
 *
 */
gboolean
pragha_preferences_get_show_status_bar (PraghaPreferences *preferences)
{
	g_return_val_if_fail(PRAGHA_IS_PREFERENCES(preferences), TRUE);

	return preferences->priv->show_status_bar;
}

/**
 * pragha_preferences_set_show_status_bar:
 *
 */
void
pragha_preferences_set_show_status_bar (PraghaPreferences *preferences,
                                        gboolean show_status_bar)
{
	g_return_if_fail(PRAGHA_IS_PREFERENCES(preferences));

	preferences->priv->show_status_bar = show_status_bar;

	g_object_notify_by_pspec(G_OBJECT(preferences), gParamSpecs[PROP_SHOW_STATUS_BAR]);
}

/**
 * pragha_preferences_get_add_recursively:
 *
 */
gboolean
pragha_preferences_get_add_recursively (PraghaPreferences *preferences)
{
	g_return_val_if_fail(PRAGHA_IS_PREFERENCES(preferences), FALSE);

	return preferences->priv->add_recursively;
}

/**
 * pragha_preferences_set_add_recursively:
 *
 */
void
pragha_preferences_set_add_recursively(PraghaPreferences *preferences,
                                       gboolean add_recursively)
{
	g_return_if_fail(PRAGHA_IS_PREFERENCES(preferences));

	preferences->priv->add_recursively = add_recursively;

	g_object_notify_by_pspec(G_OBJECT(preferences), gParamSpecs[PROP_ADD_RECURSIVELY]);
}

/**
 * pragha_preferences_get_timer_remaining_mode:
 *
 */
gboolean
pragha_preferences_get_timer_remaining_mode (PraghaPreferences *preferences)
{
	g_return_val_if_fail(PRAGHA_IS_PREFERENCES(preferences), FALSE);

	return preferences->priv->timer_remaining_mode;
}

/**
 * pragha_preferences_set_timer_remaining_mode:
 *
 */
void
pragha_preferences_set_timer_remaining_mode(PraghaPreferences *preferences,
                                            gboolean timer_remaining_mode)
{
	g_return_if_fail(PRAGHA_IS_PREFERENCES(preferences));

	preferences->priv->timer_remaining_mode = timer_remaining_mode;

	g_object_notify_by_pspec(G_OBJECT(preferences), gParamSpecs[PROP_TIMER_REMAINING_MODE]);
}

static void
pragha_preferences_load_from_file(PraghaPreferences *preferences)
{
	gboolean approximate_search, instant_search;
	gboolean shuffle, repeat, use_hint, restore_playlist, software_mixer;
	gboolean lateral_panel, show_album_art, show_status_bar;
	gboolean add_recursively, timer_remaining_mode;
	gchar *audio_sink, *audio_device, *audio_cd_device;
	gint library_style, sidebar_size, album_art_size;
	gboolean fuse_folders, sort_by_year;
	const gchar *user_config_dir;
	gchar *pragha_config_dir = NULL;
	GError *error = NULL;
	PraghaPreferencesPrivate *priv = preferences->priv;

	/* First check preferences folder or create it */

	user_config_dir = g_get_user_config_dir();
	pragha_config_dir = g_build_path(G_DIR_SEPARATOR_S, user_config_dir, "/pragha", NULL);

	if (g_file_test(pragha_config_dir, G_FILE_TEST_EXISTS | G_FILE_TEST_IS_DIR) == FALSE) {
		if (g_mkdir_with_parents (pragha_config_dir, S_IRWXU) == -1) {
			g_free(pragha_config_dir);
			g_critical("Unable to create preferences directory, err: %s", strerror(errno));
			return;
		}
		CDEBUG(DBG_INFO, "Created .config/pragha folder");
	}
	g_free(pragha_config_dir);

	/* Does /pragha/config exist ? */

	priv->rc_filepath = g_build_path(G_DIR_SEPARATOR_S, user_config_dir, "/pragha/config", NULL);

	if (g_file_test(priv->rc_filepath, G_FILE_TEST_EXISTS | G_FILE_TEST_IS_REGULAR) == FALSE) {
		if (g_creat(priv->rc_filepath, S_IRWXU) == -1) {
			g_free(priv->rc_filepath);
			priv->rc_filepath = NULL;
			g_critical("Unable to create config file, err: %s", strerror(errno));
			return;
		}
		CDEBUG(DBG_INFO, "Created .config/pragha/config file");
	}

	/* Open the preferences storage file */

	priv->rc_keyfile = g_key_file_new();

	if (!g_key_file_load_from_file(priv->rc_keyfile,
	                               priv->rc_filepath,
	                               G_KEY_FILE_NONE,
	                               &error)) {
		g_critical("Unable to load config file (Possible first start), err: %s", error->message);
		g_error_free(error);
		return;
	}

	/* Open last preferences */

	approximate_search = g_key_file_get_boolean(priv->rc_keyfile,
	                                            GROUP_GENERAL,
	                                            KEY_APPROXIMATE_SEARCH,
	                                            &error);
	if (error) {
		g_error_free(error);
		error = NULL;
	}
	else {
		pragha_preferences_set_approximate_search(preferences, approximate_search);
	}

	instant_search = g_key_file_get_boolean(priv->rc_keyfile,
	                                        GROUP_GENERAL,
	                                        KEY_INSTANT_SEARCH,
	                                        &error);
	if (error) {
		g_error_free(error);
		error = NULL;
	}
	else {
		pragha_preferences_set_instant_search(preferences, instant_search);
	}

	shuffle = g_key_file_get_boolean(priv->rc_keyfile,
	                                 GROUP_PLAYLIST,
	                                 KEY_SHUFFLE,
	                                 &error);
	if (error) {
		g_error_free(error);
		error = NULL;
	}
	else {
		pragha_preferences_set_shuffle(preferences, shuffle);
	}

	repeat = g_key_file_get_boolean(priv->rc_keyfile,
	                                GROUP_PLAYLIST,
	                                KEY_REPEAT,
	                                &error);
	if (error) {
		g_error_free(error);
		error = NULL;
	}
	else {
		pragha_preferences_set_repeat(preferences, repeat);
	}

	use_hint = g_key_file_get_boolean(priv->rc_keyfile,
	                                  GROUP_GENERAL,
	                                  KEY_USE_HINT,
	                                  &error);
	if (error) {
		g_error_free(error);
		error = NULL;
	}
	else {
		pragha_preferences_set_use_hint(preferences, use_hint);
	}

	library_style = g_key_file_get_integer(priv->rc_keyfile,
	                                       GROUP_LIBRARY,
	                                       KEY_LIBRARY_VIEW_ORDER,
	                                       &error);
	if (error) {
		g_error_free(error);
		error = NULL;
	}
	else {
		pragha_preferences_set_library_style(preferences, library_style);
	}

	sort_by_year = g_key_file_get_boolean(priv->rc_keyfile,
	                                      GROUP_LIBRARY,
	                                      KEY_SORT_BY_YEAR,
	                                      &error);
	if (error) {
		g_error_free(error);
		error = NULL;
	}
	else {
		pragha_preferences_set_sort_by_year(preferences, sort_by_year);
	}

	fuse_folders = g_key_file_get_boolean(priv->rc_keyfile,
	                                      GROUP_LIBRARY,
	                                      KEY_FUSE_FOLDERS,
	                                      &error);
	if (error) {
		g_error_free(error);
		error = NULL;
	}
	else {
		pragha_preferences_set_fuse_folders(preferences, fuse_folders);
	}

	restore_playlist = g_key_file_get_boolean(priv->rc_keyfile,
	                                          GROUP_PLAYLIST,
	                                          KEY_SAVE_PLAYLIST,
	                                          &error);
	if (error) {
		g_error_free(error);
		error = NULL;
	}
	else {
		pragha_preferences_set_restore_playlist(preferences, restore_playlist);
	}

	audio_sink = g_key_file_get_string(priv->rc_keyfile,
	                                   GROUP_AUDIO,
	                                   KEY_AUDIO_SINK,
	                                   &error);
	if (error) {
		g_error_free(error);
		error = NULL;
	}
	else {
		pragha_preferences_set_audio_sink(preferences, audio_sink);
	}

	audio_device = g_key_file_get_string(priv->rc_keyfile,
	                                     GROUP_AUDIO,
	                                     KEY_AUDIO_DEVICE,
	                                     &error);
	if (error) {
		g_error_free(error);
		error = NULL;
	}
	else {
		pragha_preferences_set_audio_device(preferences, audio_device);
	}

	software_mixer = g_key_file_get_boolean(priv->rc_keyfile,
	                                        GROUP_AUDIO,
	                                        KEY_SOFTWARE_MIXER,
	                                        &error);
	if (error) {
		g_error_free(error);
		error = NULL;
	}
	else {
		pragha_preferences_set_software_mixer(preferences, software_mixer);
	}

	audio_cd_device = g_key_file_get_string(priv->rc_keyfile,
	                                        GROUP_AUDIO,
	                                        KEY_AUDIO_CD_DEVICE,
	                                        &error);
	if (error) {
		g_error_free(error);
		error = NULL;
	}
	else {
		pragha_preferences_set_audio_cd_device(preferences, audio_cd_device);
	}

	lateral_panel = g_key_file_get_boolean(priv->rc_keyfile,
	                                       GROUP_WINDOW,
	                                       KEY_SIDEBAR,
	                                       &error);
	if (error) {
		g_error_free(error);
		error = NULL;
	}
	else {
		pragha_preferences_set_lateral_panel(preferences, lateral_panel);
	}

	sidebar_size = g_key_file_get_integer(priv->rc_keyfile,
	                                      GROUP_WINDOW,
	                                      KEY_SIDEBAR_SIZE,
	                                      &error);
	if (error) {
		g_error_free(error);
		error = NULL;
	}
	else {
		pragha_preferences_set_sidebar_size(preferences, sidebar_size);
	}

	show_album_art = g_key_file_get_boolean(priv->rc_keyfile,
	                                        GROUP_WINDOW,
	                                        KEY_SHOW_ALBUM_ART,
	                                        &error);
	if (error) {
		g_error_free(error);
		error = NULL;
	}
	else {
		pragha_preferences_set_show_album_art(preferences, show_album_art);
	}

	album_art_size = g_key_file_get_integer(priv->rc_keyfile,
	                                        GROUP_WINDOW,
	                                        KEY_ALBUM_ART_SIZE,
	                                        &error);
	if (error) {
		g_error_free(error);
		error = NULL;
	}
	else {
		pragha_preferences_set_album_art_size(preferences, album_art_size);
	}

	show_status_bar = g_key_file_get_boolean(priv->rc_keyfile,
	                                         GROUP_WINDOW,
	                                         KEY_STATUS_BAR,
	                                         &error);
	if (error) {
		g_error_free(error);
		error = NULL;
	}
	else {
		pragha_preferences_set_show_status_bar(preferences, show_status_bar);
	}

	add_recursively = g_key_file_get_boolean(priv->rc_keyfile,
	                                         GROUP_GENERAL,
	                                         KEY_ADD_RECURSIVELY_FILES,
	                                         &error);
	if (error) {
		g_error_free(error);
		error = NULL;
	}
	else {
		pragha_preferences_set_add_recursively(preferences, add_recursively);
	}

	timer_remaining_mode = g_key_file_get_boolean(priv->rc_keyfile,
	                                              GROUP_GENERAL,
	                                              KEY_TIMER_REMAINING_MODE,
	                                              &error);
	if (error) {
		g_error_free(error);
		error = NULL;
	}
	else {
		pragha_preferences_set_timer_remaining_mode(preferences, timer_remaining_mode);
	}

	g_free(audio_sink);
	g_free(audio_device);
	g_free(audio_cd_device);
}

static void
pragha_preferences_finalize (GObject *object)
{
	gchar *data = NULL;
	gsize length;
	GError *error = NULL;

	PraghaPreferences *preferences = PRAGHA_PREFERENCES(object);
	PraghaPreferencesPrivate *priv = preferences->priv;

	/* Store new preferences */

	g_key_file_set_boolean(priv->rc_keyfile,
	                       GROUP_GENERAL,
	                       KEY_INSTANT_SEARCH,
	                        priv->instant_search);
	g_key_file_set_boolean(priv->rc_keyfile,
	                       GROUP_GENERAL,
	                       KEY_APPROXIMATE_SEARCH,
	                       priv->approximate_search);

	g_key_file_set_integer(priv->rc_keyfile,
	                       GROUP_LIBRARY,
	                       KEY_LIBRARY_VIEW_ORDER,
	                       priv->library_style);
	g_key_file_set_boolean(priv->rc_keyfile,
	                       GROUP_LIBRARY,
	                       KEY_SORT_BY_YEAR,
	                       priv->sort_by_year);
	g_key_file_set_boolean(priv->rc_keyfile,
	                       GROUP_LIBRARY,
	                       KEY_FUSE_FOLDERS,
	                       priv->fuse_folders);

	g_key_file_set_boolean(priv->rc_keyfile,
	                       GROUP_PLAYLIST,
	                       KEY_SHUFFLE,
	                       priv->shuffle);
	g_key_file_set_boolean(priv->rc_keyfile,
	                       GROUP_PLAYLIST,
	                       KEY_REPEAT,
	                       priv->repeat);
	g_key_file_set_boolean(priv->rc_keyfile,
	                       GROUP_GENERAL,
	                       KEY_USE_HINT,
	                       priv->use_hint);
	g_key_file_set_boolean(priv->rc_keyfile,
	                       GROUP_PLAYLIST,
	                       KEY_SAVE_PLAYLIST,
	                       priv->restore_playlist);
	g_key_file_set_string(priv->rc_keyfile,
	                      GROUP_AUDIO,
	                      KEY_AUDIO_SINK,
	                      priv->audio_sink);
	g_key_file_set_string(priv->rc_keyfile,
	                      GROUP_AUDIO,
	                      KEY_AUDIO_DEVICE,
	                      priv->audio_device);
	g_key_file_set_boolean(priv->rc_keyfile,
	                       GROUP_AUDIO,
	                       KEY_SOFTWARE_MIXER,
	                       priv->software_mixer);
	if (string_is_not_empty(priv->audio_cd_device))
		g_key_file_set_string(priv->rc_keyfile,
		                      GROUP_AUDIO,
		                      KEY_AUDIO_CD_DEVICE,
		                      priv->audio_cd_device);
	else
		pragha_preferences_remove_key(preferences,
		                              GROUP_AUDIO,
		                              KEY_AUDIO_CD_DEVICE);

	g_key_file_set_boolean(priv->rc_keyfile,
	                       GROUP_WINDOW,
	                       KEY_SIDEBAR,
	                       priv->lateral_panel);
	g_key_file_set_integer(priv->rc_keyfile,
	                       GROUP_WINDOW,
	                       KEY_SIDEBAR_SIZE,
	                       priv->sidebar_size);
	g_key_file_set_boolean(priv->rc_keyfile,
	                       GROUP_WINDOW,
	                       KEY_SHOW_ALBUM_ART,
	                       priv->show_album_art);
	g_key_file_set_integer(priv->rc_keyfile,
	                       GROUP_WINDOW,
	                       KEY_ALBUM_ART_SIZE,
	                       priv->album_art_size);
	g_key_file_set_boolean(priv->rc_keyfile,
	                       GROUP_WINDOW,
	                       KEY_STATUS_BAR,
	                       priv->show_status_bar);

	g_key_file_set_boolean(priv->rc_keyfile,
	                       GROUP_GENERAL,
	                       KEY_ADD_RECURSIVELY_FILES,
	                       priv->add_recursively);
	g_key_file_set_boolean(priv->rc_keyfile,
	                       GROUP_GENERAL,
	                       KEY_TIMER_REMAINING_MODE,
	                       priv->timer_remaining_mode);

	/* Save to key file */

	data = g_key_file_to_data(priv->rc_keyfile, &length, NULL);
	if(!g_file_set_contents(priv->rc_filepath, data, length, &error))
		g_critical("Unable to write preferences file : %s", error->message);

	g_free(data);
	g_key_file_free(priv->rc_keyfile);
	g_free(priv->rc_filepath);
	g_free(priv->audio_sink);
	g_free(priv->audio_device);
	g_free(priv->audio_cd_device);

	G_OBJECT_CLASS(pragha_preferences_parent_class)->finalize(object);
}

static void
pragha_preferences_get_property (GObject *object,
                                 guint prop_id,
                                 GValue *value,
                                 GParamSpec *pspec)
{
	PraghaPreferences *preferences = PRAGHA_PREFERENCES(object);

	switch (prop_id) {
		case PROP_INSTANT_SEARCH:
			g_value_set_boolean (value, pragha_preferences_get_instant_search(preferences));
			break;
		case PROP_APPROXIMATE_SEARCH:
			g_value_set_boolean (value, pragha_preferences_get_instant_search(preferences));
			break;
		case PROP_LIBRARY_STYLE:
			g_value_set_int (value, pragha_preferences_get_library_style(preferences));
			break;
		case PROP_LIBRARY_SORT_BY_YEAR:
			g_value_set_boolean (value, pragha_preferences_get_sort_by_year(preferences));
			break;
		case PROP_LIBRARY_FUSE_FOLDERS:
			g_value_set_boolean (value, pragha_preferences_get_fuse_folders(preferences));
			break;
		case PROP_SHUFFLE:
			g_value_set_boolean (value, pragha_preferences_get_shuffle(preferences));
			break;
		case PROP_REPEAT:
			g_value_set_boolean (value, pragha_preferences_get_repeat(preferences));
			break;
		case PROP_USE_HINT:
			g_value_set_boolean (value, pragha_preferences_get_use_hint(preferences));
			break;
		case PROP_RESTORE_PLAYLIST:
			g_value_set_boolean (value, pragha_preferences_get_restore_playlist(preferences));
			break;
		case PROP_AUDIO_SINK:
			g_value_set_string (value, pragha_preferences_get_audio_sink(preferences));
			break;
		case PROP_AUDIO_DEVICE:
			g_value_set_string (value, pragha_preferences_get_audio_device(preferences));
			break;
		case PROP_SOFTWARE_MIXER:
			g_value_set_boolean (value, pragha_preferences_get_software_mixer(preferences));
			break;
		case PROP_AUDIO_CD_DEVICE:
			g_value_set_string (value, pragha_preferences_get_audio_cd_device(preferences));
			break;
		case PROP_LATERAL_PANEL:
			g_value_set_boolean (value, pragha_preferences_get_lateral_panel(preferences));
			break;
		case PROP_SIDEBAR_SIZE:
			g_value_set_int (value, pragha_preferences_get_sidebar_size(preferences));
			break;
		case PROP_SHOW_ALBUM_ART:
			g_value_set_boolean (value, pragha_preferences_get_show_album_art(preferences));
			break;
		case PROP_ALBUM_ART_SIZE:
			g_value_set_int (value, pragha_preferences_get_album_art_size(preferences));
			break;
		case PROP_SHOW_STATUS_BAR:
			g_value_set_boolean (value, pragha_preferences_get_show_status_bar(preferences));
			break;
		case PROP_ADD_RECURSIVELY:
			g_value_set_boolean (value, pragha_preferences_get_add_recursively(preferences));
			break;
		case PROP_TIMER_REMAINING_MODE:
			g_value_set_boolean (value, pragha_preferences_get_timer_remaining_mode(preferences));
			break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
	}
}

static void
pragha_preferences_set_property (GObject *object,
                                 guint prop_id,
                                 const GValue *value,
                                 GParamSpec *pspec)
{
	PraghaPreferences *preferences = PRAGHA_PREFERENCES(object);

	switch (prop_id) {
		case PROP_INSTANT_SEARCH:
			pragha_preferences_set_instant_search(preferences, g_value_get_boolean(value));
			break;
		case PROP_APPROXIMATE_SEARCH:
			pragha_preferences_set_approximate_search(preferences, g_value_get_boolean(value));
			break;
		case PROP_LIBRARY_STYLE:
			pragha_preferences_set_library_style(preferences, g_value_get_int(value));
			break;
		case PROP_LIBRARY_SORT_BY_YEAR:
			pragha_preferences_set_sort_by_year(preferences, g_value_get_boolean(value));
			break;
		case PROP_LIBRARY_FUSE_FOLDERS:
			pragha_preferences_set_fuse_folders(preferences, g_value_get_boolean(value));
			break;
		case PROP_SHUFFLE:
			pragha_preferences_set_shuffle(preferences, g_value_get_boolean(value));
			break;
		case PROP_REPEAT:
			pragha_preferences_set_repeat(preferences, g_value_get_boolean(value));
			break;
		case PROP_USE_HINT:
			pragha_preferences_set_use_hint(preferences, g_value_get_boolean(value));
			break;
		case PROP_RESTORE_PLAYLIST:
			pragha_preferences_set_restore_playlist(preferences, g_value_get_boolean(value));
			break;
		case PROP_AUDIO_SINK:
			pragha_preferences_set_audio_sink(preferences, g_value_get_string(value));
			break;
		case PROP_AUDIO_DEVICE:
			pragha_preferences_set_audio_device(preferences, g_value_get_string(value));
			break;
		case PROP_SOFTWARE_MIXER:
			pragha_preferences_set_software_mixer(preferences, g_value_get_boolean(value));
			break;
		case PROP_AUDIO_CD_DEVICE:
			pragha_preferences_set_audio_cd_device(preferences, g_value_get_string(value));
			break;
		case PROP_LATERAL_PANEL:
			pragha_preferences_set_lateral_panel(preferences, g_value_get_boolean(value));
			break;
		case PROP_SIDEBAR_SIZE:
			pragha_preferences_set_sidebar_size(preferences, g_value_get_int(value));
			break;
		case PROP_SHOW_ALBUM_ART:
			pragha_preferences_set_show_album_art(preferences, g_value_get_boolean(value));
			break;
		case PROP_ALBUM_ART_SIZE:
			pragha_preferences_set_album_art_size(preferences, g_value_get_int(value));
			break;
		case PROP_SHOW_STATUS_BAR:
			pragha_preferences_set_show_status_bar(preferences, g_value_get_boolean(value));
			break;
		case PROP_ADD_RECURSIVELY:
			pragha_preferences_set_add_recursively(preferences, g_value_get_boolean(value));
			break;
		case PROP_TIMER_REMAINING_MODE:
			pragha_preferences_set_timer_remaining_mode(preferences, g_value_get_boolean(value));
			break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
	}
}

static GObject *
pragha_preferences_constructor (GType type, guint n_construct_properties, GObjectConstructParam *construct_properties)
{
	GObject *object = G_OBJECT_CLASS (pragha_preferences_parent_class)->
		constructor (type, n_construct_properties, construct_properties);

	PraghaPreferences *preferences = PRAGHA_PREFERENCES (object);
	pragha_preferences_load_from_file (preferences);

	return object;
}

static void
pragha_preferences_class_init (PraghaPreferencesClass *klass)
{
	GObjectClass *object_class;
	const GParamFlags PRAGHA_PREF_PARAMS = G_PARAM_READWRITE | G_PARAM_CONSTRUCT | G_PARAM_STATIC_STRINGS;

	object_class = G_OBJECT_CLASS(klass);
	object_class->constructor = pragha_preferences_constructor;
	object_class->finalize = pragha_preferences_finalize;
	object_class->get_property = pragha_preferences_get_property;
	object_class->set_property = pragha_preferences_set_property;
	g_type_class_add_private(object_class, sizeof(PraghaPreferencesPrivate));

	/**
	  * PraghaPreferences:instant_search:
	  *
	  */
	gParamSpecs[PROP_INSTANT_SEARCH] =
		g_param_spec_boolean("instant-search",
		                     "InstantSearch",
		                     "Instant Search Preference",
		                      TRUE,
		                      PRAGHA_PREF_PARAMS);

	/**
	  * PraghaPreferences:approximate_searches:
	  *
	  */
	gParamSpecs[PROP_APPROXIMATE_SEARCH] =
		g_param_spec_boolean("approximate-searches",
		                     "ApproximateSearches",
		                     "Approximate Searches Preference",
		                      FALSE,
		                      PRAGHA_PREF_PARAMS);

	/**
	  * PraghaPreferences:library_style:
	  *
	  */
	gParamSpecs[PROP_LIBRARY_STYLE] =
		g_param_spec_int ("library-style",
		                  "LibraryStyle",
		                  "Library Style Preferences",
		                  0,
		                  LAST_LIBRARY_STYLE,
		                  FOLDERS,
		                  PRAGHA_PREF_PARAMS);

	/**
	 * PraghaPreferences:sort_by_year:
	 *
	 */
	gParamSpecs[PROP_LIBRARY_SORT_BY_YEAR] =
		g_param_spec_boolean("sort-by-year",
		                     "SortByYear",
		                     "Sort By Year Preference",
		                     FALSE,
		                     PRAGHA_PREF_PARAMS);

	/**
	  * PraghaPreferences:fuse_folders:
	  *
	  */
	gParamSpecs[PROP_LIBRARY_FUSE_FOLDERS] =
		g_param_spec_boolean("fuse-folders",
		                     "FuseFolders",
		                     "Fuse Folders Preference",
		                     FALSE,
		                     PRAGHA_PREF_PARAMS);

	/**
	  * PraghaPreferences:shuffle:
	  *
	  */
	gParamSpecs[PROP_SHUFFLE] =
		g_param_spec_boolean("shuffle",
		                     "Shuffle",
		                     "Shuffle Preference",
		                     FALSE,
		                     PRAGHA_PREF_PARAMS);

	/**
	  * PraghaPreferences:repeat:
	  *
	  */
	gParamSpecs[PROP_REPEAT] =
		g_param_spec_boolean("repeat",
		                     "Repeat",
		                     "Repeat Preference",
		                     FALSE,
		                     PRAGHA_PREF_PARAMS);

	/**
	  * PraghaPreferences:use_hint:
	  *
	  */
	gParamSpecs[PROP_USE_HINT] =
		g_param_spec_boolean("use-hint",
		                     "UseHint",
		                     "Use hint Preference",
		                     TRUE,
		                     PRAGHA_PREF_PARAMS);

	/**
	  * PraghaPreferences:restore_playlist:
	  *
	  */
	gParamSpecs[PROP_RESTORE_PLAYLIST] =
		g_param_spec_boolean("restore-playlist",
		                     "RestorePlaylist",
		                     "Restore Playlist Preference",
		                     TRUE,
		                     PRAGHA_PREF_PARAMS);

	/**
	  * PraghaPreferences:audio_sink:
	  *
	  */
	gParamSpecs[PROP_AUDIO_SINK] =
		g_param_spec_string("audio-sink",
		                    "AudioSink",
		                    "Audio Sink",
		                    DEFAULT_SINK,
		                    PRAGHA_PREF_PARAMS);

	/**
	  * PraghaPreferences:audio_device:
	  *
	 */
	gParamSpecs[PROP_AUDIO_DEVICE] =
		g_param_spec_string("audio-device",
		                    "AudioDevice",
		                    "Audio Device",
		                    ALSA_DEFAULT_DEVICE,
		                    PRAGHA_PREF_PARAMS);

	/**
	  * PraghaPreferences:software_mixer:
	  *
	  */
	gParamSpecs[PROP_SOFTWARE_MIXER] =
		g_param_spec_boolean("software-mixer",
		                     "SoftwareMixer",
		                     "Use Software Mixer",
		                     FALSE,
		                     PRAGHA_PREF_PARAMS);

	/**
	  * PraghaPreferences:audio_cd_device:
	  *
	  */
	gParamSpecs[PROP_AUDIO_CD_DEVICE] =
		g_param_spec_string("audio-cd-device",
		                    "AudioCDDevice",
		                    "Audio CD Device",
		                    NULL,
		                    PRAGHA_PREF_PARAMS);

	/**
	  * PraghaPreferences:lateral_panel:
	  *
	  */
	gParamSpecs[PROP_LATERAL_PANEL] =
		g_param_spec_boolean("lateral-panel",
		                     "LateralPanel",
		                     "Show Lateral Panel Preference",
		                     TRUE,
		                     PRAGHA_PREF_PARAMS);
	/**
	  * PraghaPreferences:sidebar_size:
	  *
	  */
	gParamSpecs[PROP_SIDEBAR_SIZE] =
		g_param_spec_int ("sidebar-size",
		                  "SidebarSize",
		                  "Sidebar Size Preferences",
		                  0,
		                  G_MAXINT,
		                  DEFAULT_SIDEBAR_SIZE,
		                  PRAGHA_PREF_PARAMS);
	/**
	  * PraghaPreferences:show_album_art:
	  *
	  */
	gParamSpecs[PROP_SHOW_ALBUM_ART] =
		g_param_spec_boolean("show-album-art",
		                     "ShowAlbumArt",
		                     "show Album Art Preference",
		                      TRUE,
		                      PRAGHA_PREF_PARAMS);
	/**
	  * PraghaPreferences:album_art_size:
	  *
	  */
	gParamSpecs[PROP_ALBUM_ART_SIZE] =
		g_param_spec_int ("album-art-size",
		                  "AlbumArtSize",
		                  "Album Art Size Preferences",
		                  24,
		                  128,
		                  DEFAULT_ALBUM_ART_SIZE,
		                  PRAGHA_PREF_PARAMS);
	/**
	  * PraghaPreferences:show_status_bar:
	  *
	  */
	gParamSpecs[PROP_SHOW_STATUS_BAR] =
		g_param_spec_boolean("show-status-bar",
		                     "ShowStatusBar",
		                     "Show Status Bar Preference",
		                      TRUE,
		                      PRAGHA_PREF_PARAMS);

	/**
	  * PraghaPreferences:add_recursively:
	  *
	  */
	gParamSpecs[PROP_ADD_RECURSIVELY] =
		g_param_spec_boolean("add-recursively",
		                     "AddRecursively",
		                     "Add Recursively Preference",
		                     FALSE,
		                     PRAGHA_PREF_PARAMS);

	/**
	 * PraghaPreferences:timer_remaining_mode:
	 *
	 */
	gParamSpecs[PROP_TIMER_REMAINING_MODE] =
		g_param_spec_boolean("timer-remaining-mode",
		                     "TimerRemainingMode",
		                     "Timer Remaining Mode Preference",
		                      FALSE,
		                      PRAGHA_PREF_PARAMS);

	g_object_class_install_properties(object_class, LAST_PROP, gParamSpecs);
}

static void
pragha_preferences_init (PraghaPreferences *preferences)
{
	preferences->priv = G_TYPE_INSTANCE_GET_PRIVATE(preferences,
	                                                PRAGHA_TYPE_PREFERENCES,
	                                                PraghaPreferencesPrivate);
}

GKeyFile*
pragha_preferences_share_key_file(PraghaPreferences *preferences)
{
	return preferences->priv->rc_keyfile;
}

gchar*
pragha_preferences_share_filepath(PraghaPreferences *preferences)
{
	return preferences->priv->rc_filepath;
}

/**
 * pragha_preferences_get:
 *
 * Queries the global #PraghaPreferences instance, which is shared
 * by all modules. The function automatically takes a reference
 * for the caller, so you'll need to call g_object_unref() when
 * you're done with it.
 *
 * Return value: the global #PraghaPreferences instance.
 **/
PraghaPreferences*
pragha_preferences_get (void)
{
	static PraghaPreferences *preferences = NULL;

	if (G_UNLIKELY (preferences == NULL)) {
		preferences = g_object_new(PRAGHA_TYPE_PREFERENCES, NULL);
		g_object_add_weak_pointer(G_OBJECT (preferences),
		                          (gpointer) &preferences);
	}
	else {
		g_object_ref (G_OBJECT (preferences));
	}

	return preferences;
}
