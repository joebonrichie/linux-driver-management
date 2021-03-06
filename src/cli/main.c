/*
 * This file is part of linux-driver-management.
 *
 * Copyright © 2016-2017 Ikey Doherty
 *
 * linux-driver-management is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 */

#include <stdio.h>
#include <stdlib.h>

#include "cli.h"
#include "util.h"

static const char *prog_name = NULL;

/**
 * Main program commands
 */
static CLICommand commands[] = {
        { "configure", "Configure the system drivers", ldm_cli_configure },
        { "help", "Display the available commands and quit", ldm_cli_help },
        { "status", "Display the driver status for the system", ldm_cli_status },
        { "version", "Display the program version and quit", ldm_cli_version },
};

/**
 * Emit help for the CLI - multi function
 */
int ldm_cli_help(__ldm_unused__ int argc, __ldm_unused__ char **argv)
{
        /* TODO: Show specific help for a given command */
        for (size_t i = 0; i < ARRAY_SIZE(commands); i++) {
                CLICommand *command = &(commands[i]);
                fprintf(stdout, "%15s - %s\n", command->name, command->summary);
        }
        return EXIT_SUCCESS;
}

/**
 * Emit usage, then print out help for the commands
 */
static void print_usage(void)
{
        fprintf(stderr, "Usage: %s [subcommand]\n\n", prog_name);
        ldm_cli_help(-1, NULL);
}

/**
 * Find the command with the given name
 */
static CLICommand *ldm_cli_find_command(const char *name)
{
        for (size_t i = 0; i < ARRAY_SIZE(commands); i++) {
                CLICommand *command = &(commands[i]);
                if (streq(command->name, name)) {
                        return command;
                }
        }
        return NULL;
}

int main(int argc, char **argv)
{
        CLICommand *command = NULL;
        prog_name = argv[0];
        const char *subcommand = NULL;

        /* Forward arguments beyond prog name */
        ++argv;
        --argc;

        /* No arguments, just emit usage */
        if (argc < 1) {
                print_usage();
                return EXIT_SUCCESS;
        }
        /* Set up subcommand context */
        subcommand = argv[0];
        ++argv;
        --argc;

        /* Find command, wind the arguments */
        command = ldm_cli_find_command(subcommand);

        /* Tell them which commands *do* exist */
        if (!command) {
                fprintf(stderr, "Unknown command: '%s'\n\n", subcommand);
                ldm_cli_help(-1, NULL);
                return EXIT_FAILURE;
        }

        /* Placeholder commands */
        if (!command->exec) {
                fprintf(stderr, "Not yet implemented: '%s'\n", subcommand);
                return EXIT_FAILURE;
        }

        /* Execute the command now */
        return command->exec(argc, argv);
}

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 8
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * vi: set shiftwidth=8 tabstop=8 expandtab:
 * :indentSize=8:tabSize=8:noTabs=true:
 */
