#!/bin/sh
# X session for `startx`. No display manager.
# The xinitrc.d scripts matter: 50-systemd-user.sh hands DISPLAY/XAUTHORITY to
# the systemd user manager and D-Bus, which D-Bus-activated services need.
if [ -d /etc/X11/xinit/xinitrc.d ]; then
    for f in /etc/X11/xinit/xinitrc.d/?*.sh; do
        [ -x "$f" ] && . "$f"
    done
    unset f
fi

# Without systemd (Artix) there is no user manager, so what it starts on Arch
# is started here: a session bus, the sound servers and the cooler daemon.
# On Arch this whole block is skipped.
if [ ! -d /run/systemd/system ]; then
    if [ -z "${DBUS_SESSION_BUS_ADDRESS:-}" ] && [ -z "${XINITRC_IN_BUS:-}" ]; then
        XINITRC_IN_BUS=1 exec dbus-run-session -- sh "$HOME/.xinitrc"
    fi
    if ! pgrep -x pipewire >/dev/null; then
        pipewire &
        pipewire-pulse &
        wireplumber &
    fi
    lpp=$HOME/eluktronics-lpp-linux/linux-lpp-ctl
    if [ -x "$lpp/.venv/bin/python" ] && ! pgrep -f "$lpp/lpp_daemon.py" >/dev/null; then
        "$lpp/.venv/bin/python" "$lpp/lpp_daemon.py" >/dev/null 2>&1 &
    fi
    unset lpp
fi

# dwm is the default (2026-10-26, ~/build/arch-dwm); `WM=qtile startx` from
# the console runs qtile instead.
case ${WM:-dwm} in
qtile)
    exec /usr/bin/qtile start ;;
*)
    export PATH="$HOME/.local/bin:$PATH"   # dwm does not add it; bar scripts live there
    xrandr --output DP-0 --primary --mode 2560x1600 --rate 240
    xrandr --output HDMI-0 --mode 2560x1440 --rate 240   # fails harmlessly when unplugged
    "$HOME/.local/bin/wallpaper" --restore
    xss-lock --transfer-sleep-lock -- i3lock --nofork -c 14161b &
    dunst &
    /usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &
    slstatus &
    exec "$HOME/.local/bin/dwm" ;;
esac
