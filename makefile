# ----------------------------
# Makefile Options
# ----------------------------

NAME = SANGRIA
ICON = icon.png
DESCRIPTION = "A deep and thoughtful game for the TI-84 Plus CE"
COMPRESSED = YES
ARCHIVED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
