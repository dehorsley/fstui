# FS TUI 

A terminal client for the VLBI Field System display server.

Based on [dvtm](http://www.brain-dump.org/projects/dvtm/).

WIP. Some hacking of `fs.c` required for cutomization.


## FAQ

### Detach / reattach functionality

dvtm doesn't have session support built in. Use
[abduco](http://www.brain-dump.org/projects/abduco/) instead.

    $ abduco -c dvtm-session

Detach using `CTRL-\` and later reattach with

    $ abduco -a dvtm-session

### Copy / Paste does not work under X

If you have mouse support enabled, which is the case with the
default settings, you need to hold down shift while selecting
and inserting text. In case you don't like this behaviour either
run dvtm with the `-M` command line argument, disable it at run
time with `MOD+M` or modify `config.def.h` to disable it completely
at compile time. You will however no longer be able to perform
other mouse actions like selecting windows etc.

### How to change the key bindings?

The configuration of dvtm is done by creating a custom `config.h`
and (re)compiling the source code. See the default `config.def.h`
as an example, adapting it to your preference should be straightforward.
You basically define a set of layouts and keys which dvtm will use.
There are some pre defined macros to ease configuration.

### WARNING: terminal is not fully functional

This means you haven't installed the `dvtm.info` terminfo description
which can be done with `tic -s dvtm.info`. If for some reason you
can't install new terminfo descriptions set the `DVTM_TERM` environment
variable to a known terminal when starting `dvtm` as in

    $ DVTM_TERM=rxvt dvtm

This will instruct dvtm to use rxvt as `$TERM` value within its windows.

### How to set the window title?

The window title can be changed by means of a
[xterm extension](http://tldp.org/HOWTO/Xterm-Title-3.html#ss3.2)
terminal escape sequence

    $ echo -ne "\033]0;Your title here\007"

So for example in `bash` if you want to display the current working
directory in the window title this can be accomplished by means of
the following section in your startup files.

    # If this is an xterm set the title to user@host:dir
    case "$TERM" in
    dvtm*|xterm*|rxvt*)
        PROMPT_COMMAND='echo -ne "\033]0;${USER}@${HOSTNAME}: ${PWD/$HOME/~}\007"'
        ;;
    *)
        ;;
    esac

Other shells provide similar functionality, zsh as an example has a
[precmd function](http://zsh.sourceforge.net/Doc/Release/Functions.html#Hook-Functions)
which can be used to achieve the same effect.

### Something is wrong with the displayed colors

Make sure you have set `$TERM` correctly for example if you want to
use 256 color profiles you probably have to append `-256color` to
your regular terminal name. Also due to limitations of ncurses by
default you can only use 255 color pairs simultaneously. If you
need more than 255 different color pairs at the same time, then you
have to rebuild ncurses with

    $ ./configure ... --enable-ext-colors

Note that this changes the ABI and therefore sets SONAME of the
library to 6 (i.e. you have to link against `libncursesw.so.6`).

### Some characters are displayed like garbage

Make sure you compiled dvtm against a unicode aware curses library
(in case of ncurses this would be `libncursesw`). Also make sure
that your locale settings contain UTF-8.

### The numeric keypad does not work with Putty

Disable [application keypad mode](http://the.earth.li/~sgtatham/putty/0.64/htmldoc/Chapter4.html#config-features-application)
in the Putty configuration under `Terminal => Features => Disable application keypad mode`.

### Unicode characters do not work within Putty

You have to tell Putty in which
[character encoding](http://the.earth.li/~sgtatham/putty/0.64/htmldoc/Chapter4.html#config-translation)
the received data is. Set the dropdown box under `Window => Translation`
to UTF-8. In order to get proper line drawing characters you proabably
also want to set the TERM environment variable to `putty` or `putty-256color`.
If that still doesn't do the trick then try running dvtm with the
following ncurses related environment variable set `NCURSES_NO_UTF8_ACS=1`.

## Development

You can always fetch the current code base from the git repository.

    git clone https://github.com/martanne/dvtm.git

or

    git clone git://repo.or.cz/dvtm.git

If you have comments, suggestions, ideas, a bug report, a patch or something
else related to abduco then write to the
[suckless developer mailing list](http://suckless.org/community)
or contact me directly mat[at]brain-dump.org.

[![Build Status](https://travis-ci.org/martanne/dvtm.svg?branch=master)](https://travis-ci.org/martanne/dvtm)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/4256/badge.svg)](https://scan.coverity.com/projects/4256)

## License

Based on dvtm; dvtm reuses some code of dwm and is released under the same
[MIT/X11 license](https://raw.githubusercontent.com/martanne/dvtm/master/LICENSE).
The terminal emulation part is licensed under the ISC license.
