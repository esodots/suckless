# suckless

My builds of **dwm 6.8**, **slstatus 1.1** and **st 0.9.2**, plus the small
shell scripts the bar runs. Everything here is what runs on my machine; clone
it, run one script, and the setup is back.

## Installation

### Arch Linux

Install the build dependencies:

```sh
sudo pacman -S base-devel libx11 libxft libxinerama freetype2 fontconfig harfbuzz
```

And what the keybindings and bar call at runtime:

```sh
sudo pacman -S ttf-jetbrains-mono-nerd dmenu i3lock xss-lock dunst maim xclip \
    curl jq iw pipewire wireplumber libpulse thunar
```

Then see [Building from Source](#building-from-source).

### Alpine Linux

```sh
setup-xorg-base
apk add build-base libx11-dev libxft-dev libxinerama-dev freetype-dev \
    fontconfig-dev harfbuzz-dev git
```

### BSD

Note, the `config.mk` files use Linux include paths. On FreeBSD, X11 and
freetype live under `/usr/local`, so build with:

```sh
make X11INC=/usr/local/include X11LIB=/usr/local/lib \
     FREETYPEINC=/usr/local/include/freetype2
```

The bar scripts in `bin/` read Linux `/sys` files and call `iw`, `wpctl` and
`systemctl`, so on BSD those parts of the bar show `n/a` or do nothing.

## Building from Source

```sh
git clone https://github.com/esodots/suckless
cd suckless
./install.sh
```

This builds dwm, slstatus and st and installs them, together with everything
in `bin/`, into `~/.local/bin`. No root needed. To install somewhere else:

```sh
./install.sh /usr/local
```

To rebuild one program after changing its `config.h`:

```sh
cd st
make && make PREFIX=$HOME/.local install
```

## Setting up

### Without a display manager (startx)

`xinitrc` in this repo is my `~/.xinitrc`. Copy it, or add at least:

```sh
export PATH="$HOME/.local/bin:$PATH"
slstatus &
exec dwm
```

Then start X with:

```sh
startx
```

### Weather in the bar

The weather part of the bar is off until you name NWS stations (US only) in
`~/.config/bar/weather`:

```sh
WEATHER_STATIONS="KXYZ KABC"     # tried in order
WEATHER_CONTACT="you@example.com" # NWS asks for one in the User-Agent
```

Find station IDs at https://www.weather.gov. Without this file the bar simply
leaves the weather out.

## Configuration

Like all suckless programs, configuration is `config.h` plus a recompile.
There is no runtime config file.

| Program  | File                 | Notes |
|----------|----------------------|-------|
| dwm      | `dwm/config.h`       | keys, colours, tags |
| slstatus | `slstatus/config.h`  | runs `bar` every 5 s; `pkill -USR1 slstatus` refreshes at once |
| st       | `st/config.h`        | font, colours, keys |

**Monitor names are hard-coded** in `xinitrc`: `DP-0` (the laptop panel) and
`HDMI-0`, both at 240 Hz. Change them to what `xrandr` lists on your machine.

**Machine-specific keys** go in `dwm/keys.local.h`, which git ignores.
`config.h` pulls it into its key list when it exists, so the build works
without it. One line per key, in the same form as the `keys[]` entries.

## Key Bindings

### dwm

| Binding | Action |
|---------|--------|
| Super+Q | Spawn terminal (st) |
| Super+Space | dmenu launcher |
| Super+E | File manager (thunar) |
| Super+L | Lock screen (i3lock) |
| Super+C | Kill focused window |
| Super+Shift+E | Quit dwm |
| Super+K / Super+Down | Focus next window |
| Super+Up | Focus previous window |
| Super+J / Super+Left | Shrink master area |
| Super+; / Super+Right | Grow master area |
| Super+I / Super+O | Inc/dec number of master windows |
| Super+Return | Move focused window to master |
| Super+T | Tiling layout |
| Super+F | Monocle layout |
| Super+Tab | Switch to the previous layout |
| Super+V | Toggle floating |
| Super+B | Toggle bar |
| Super+1-9, 0 | View tag 1-10 |
| Super+Shift+1-9, 0 | Move window to tag 1-10 |
| Super+Ctrl+1-9, 0 | Toggle tag view (multi-tag) |
| Super+Ctrl+Shift+1-9, 0 | Toggle window tag (sticky) |
| Super+\` | View all tags |
| Super+Shift+\` | Put window on all tags |
| Super+Comma/Period | Focus prev/next monitor |
| Super+Shift+Comma/Period | Send window to prev/next monitor |
| Super+D | Dice roller (`roll`, type `NdS`) |
| Super+Shift+S | Screenshot of a selection, to file and clipboard |
| Super+Ctrl+Shift+S | Screenshot of a selection, clipboard only |
| Print | Screenshot of the whole screen |
| Super+Print | Whole screen after 5 s |
| Volume / mute / mic / brightness keys | Change them and refresh the bar |
| Super+Button1 (drag) | Move window |
| Super+Button3 (drag) | Resize window |

### st

| Binding | Action |
|---------|--------|
| Ctrl+Shift+C / V | Copy / paste |
| Mouse wheel | Scroll history (passed to the program in full-screen apps) |
| Shift+PageUp / PageDown | Scroll history |
| Ctrl+= / Ctrl+- / Ctrl+0 | Bigger / smaller / reset font |
| Ctrl+Shift+PageUp / PageDown / Home | Same, the st defaults |

## Features

- **dwm**
  - Bar at the bottom, 10 tags
  - Clickable status text: dwm splits the slstatus text at `│` and runs
    `barclick` with the mouse button and the part clicked
  - No gaps around st in tiles (`resizehints = 0`)
  - Redraws at 240 Hz while moving/resizing windows
- **slstatus**
  - One `bar` call for weather, VPN, wifi, brightness and volume, then date,
    time and battery
  - `[shutdown]` powers off on a second click within 7 s
  - Scroll on brightness / volume to change them
- **st**
  - Patched with scrollback, scrollback-mouse and ligatures (the `.diff` files
    are in `st/`), applied in that order
  - Mouse wheel scrolls history on the normal screen and is passed to the
    program on the alternate screen
  - `clear` / Ctrl+L pushes the screen into history instead of losing it
  - Exports `COLORTERM=truecolor`
  - JetBrainsMono Nerd Font at 26 px, dark palette (`#14161b`)
  - 5000 lines of history

## License

MIT/X, the same licence as dwm, slstatus and st. Each program keeps its
upstream `LICENSE` file; my changes are under `LICENSE` at the top.
