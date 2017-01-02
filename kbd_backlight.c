/*
 * Copyright (c) 2016 Jeff Spaulding <sarnet@gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>

void
print_help()
{
	printf("Usage:\n");
	printf("kbd_backlight [-i | -d | -l<level>]\n");
	printf("  where <level> is a number between 0 and 3.\n");
	printf("  -i increment\n");
	printf("  -d decrement\n");
}

int
main(int argc, char *argv[])
{
	int ch;
	int iflg, dflg, lflg;
	int level = -1;
	char level_str[4] = "";
	int fd;
	const char *kbd_file = "/sys/class/leds/asus::kbd_backlight/brightness";

	iflg = dflg = lflg = 0;

	while ((ch = getopt(argc, argv, "idhl:")) != -1) {
		switch (ch) {
		case 'i':
			iflg = 1;
			break;
		case 'd':
			dflg = 1;
			break;
		case 'l':
			lflg = 1;
			level = atoi(optarg);
			break;
		case '?':
		case 'h':
		default:
			print_help();
			return EXIT_FAILURE;
		}
	}

  if (!(iflg || dflg || lflg)) {
    print_help();
    return EXIT_FAILURE;
  }

	if (iflg || dflg) {
    fd = open(kbd_file, O_RDONLY);
    if (fd == -1) {
      err(1, "%s", kbd_file);
    }

    int bread=read(fd, level_str, sizeof(level_str));

    int original_level = atoi(level_str);

    if (original_level < 0 || original_level > 3) {
	    printf("Unable to read brightness.\n");
      return EXIT_FAILURE;
    }

    if (iflg) {
      level = original_level + 1;
    } else {
      level = original_level - 1;
    }

    close(fd);
  }

  if (level < 0 || level > 3) {
    print_help();
    return EXIT_FAILURE;
  }

	snprintf(level_str, sizeof level_str, "%d", level);

	fd = open(kbd_file, O_TRUNC | O_WRONLY);

	if (fd == -1) {
		err(1, "%s", kbd_file);
	}

	write(fd, level_str, strlen(level_str));

	close(fd);
  printf("%d", level);
}
