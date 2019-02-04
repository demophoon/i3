/*
 * vim:ts=4:sw=4:expandtab
 *
 * i3 - an improved dynamic tiling window manager
 * © 2009 Michael Stapelberg and contributors (see also: LICENSE)
 *
 * config_parser.h: config parser-related definitions
 *
 */
#pragma once

#include <config.h>

#include <yajl/yajl_gen.h>

SLIST_HEAD(variables_head, Variable);
extern pid_t config_error_nagbar_pid;

/**
 * An intermediate reprsentation of the result of a parse_config call.
 * Currently unused, but the JSON output will be useful in the future when we
 * implement a config parsing IPC command.
 *
 */
struct ConfigResultIR {
    /* The JSON generator to append a reply to. */
    yajl_gen json_gen;

    /* The next state to transition to. Passed to the function so that we can
     * determine the next state as a result of a function call, like
     * cfg_criteria_pop_state() does. */
    int next_state;
};

struct ConfigResultIR *parse_config(const char *input, struct context *context);

/**
 * launch nagbar to indicate errors in the configuration file.
 */
void start_config_error_nagbar(const char *configpath, bool has_errors);

/**
 * Parses the given file by first replacing the variables, then calling
 * parse_config and launching i3-nagbar if use_nagbar is true.
 *
 * The return value is a boolean indicating whether there were errors during
 * parsing.
 *
 */
bool parse_file(const char *f, bool use_nagbar);
bool rec_parse_file(struct variables_head *variables, const char *f, bool use_nagbar, int load_depth);
