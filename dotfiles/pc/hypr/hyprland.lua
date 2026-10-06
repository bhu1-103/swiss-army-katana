-- Converted from hyprland.conf-final.bak
-- Native Hyprland Lua configuration format (Hyprland 0.55+).
--
-- Source:
--   # source = ~/.config/hypr/myColors.conf
--
-- That source line was commented out in the original, so nothing is required here.

--   ██
--   ░██       ██   ██ ██████
--   ░██      ░░██ ██ ░██░░░██ ██████
--   ░██████   ░░███  ░██  ░██░░██░░█
--   ░██░░░██   ░██   ░██████  ░██ ░
--   ░██  ░██   ██    ░██░░░   ░██
--   ░██  ░██  ██     ░██     ░███
--   ░░   ░░  ░░      ░░      ░░░

----------------
-- MONITORS
----------------

-- hl.monitor({
-- output = "",
-- mode = "preferred",
--position = "auto",
-- scale = "auto",
-- })

-- Original commented monitor alternatives:
hl.monitor({
	output = "HDMI-A-1",
	mode = "1920x1080@59.94Hz",
	position = auto,
	--position = { 0, 0 },
	scale = 1.2,
})
-- monitor=HDMI-A-1,1440x900@74.98Hz,0x0,1
-- monitor=HDMI-A-1,modeline 1600x900_75.00 151.25 1600 1704 1872 2144 900 903 908 942 -hsync +vsync,0x0,1
-- monitor=HDMI-A-1,1440x900@59.89Hz,0x0,1
-- monitor=HDMI-A-1,1600x900@60.00Hz,0x0,1
-- monitor=HDMI-A-1,800x600@60.00Hz,0x0,1
-- monitor=HDMI-A-1,1920x1080@59.94Hz,auto,0.5
-- monitor=HDMI-A-1,1920x1080@59.94Hz,0x0,1

---------------------
-- MY PROGRAMS
---------------------

-- local terminal = "kitty"
local terminal = "alacritty"
local fileManager = "nautilus"
local menu = "wofi --show drun"

-------------------
-- AUTOSTART
-------------------

hl.on("hyprland.start", function()
	hl.exec_cmd("~/.config/hypr/notif.sh")
	hl.exec_cmd("~/.config/hypr/startup.sh")
	hl.exec_cmd("cd ~/.config/quickshell/zephyr/quickshell/ && quickshell -p shell.qml")
	hl.exec_cmd("kitty")
	hl.exec_cmd("swaync")
	hl.exec_cmd("nautilus -q && nautilus &")
	hl.exec_cmd("fcitx5")
	hl.exec_cmd("listenbrainz-mpd")

	-- exec-once = swaybg -i ~/Pictures/wallpapers/wallpaper20.jpg
	-- exec-once = mpvpaper -vs -o "--no-config --no-audio --loop" HDMI-A-1 ~/Videos/wallpapers/cat-cloud.1920x1080.mp4
	-- exec-once = gslapper -vs -o "--no-config --no-audio --loop" HDMI-A-1 ~/Videos/wallpapers/cat-cloud.1920x1080.mp4
	-- exec-once = gslapper -vs -o "--no-config --no-audio --loop" HDMI-A-1 ~/Videos/wallpapers/sakura-street.1920x1080.mp4
	-- exec-once = export GTK_THEME=Dracula; export QT_QPA_PLATFORMTHEME=qt5ct
	-- exec-once = swww img ~/1.gif
end)

-------------------------------
-- ENVIRONMENT VARIABLES
-------------------------------

hl.env("XCURSOR_SIZE", "16")
hl.env("HYPRCURSOR_SIZE", "16")
hl.env("XCURSOR_THEME", "volantes_cursors")
hl.env("GTK_THEME", "Dracula")
hl.env("GTK2_RC_FILES", os.getenv("HOME") .. "/.gtkrc-2.0")
hl.env("XDG_CURRENT_DESKTOP", "Hyprland")
hl.env("GDK_BACKEND", "wayland")

hl.env("WLR_DRM_NO_MODIFIERS", "1")
hl.env("WLR_NO_HARDWARE_CURSORS", "1")
hl.env("WLR_SCALE_FILTER", "nearest")

-----------------------
-- LOOK AND FEEL
-----------------------

hl.config({
	general = {
		gaps_in = 5,
		gaps_out = 15,
		border_size = 5,
		col = {
			active_border = {
				colors = { "rgba(d81b60aa)", "rgba(ff2f4655)" },
				angle = 315,
			},
			inactive_border = "rgba(595959aa)",
		},
		resize_on_border = true,
		allow_tearing = false,
		layout = "dwindle",
	},

	decoration = {
		rounding = 10,
		active_opacity = 1.0,
		inactive_opacity = 0.9,
		blur = {
			enabled = true,
			size = 3,
			passes = 1,
			vibrancy = 0.1696,
		},
	},

	animations = {
		enabled = true,
	},

	dwindle = {
		preserve_split = true,
	},

	master = {
		new_status = "master",
	},

	misc = {
		force_default_wallpaper = -1,
		disable_hyprland_logo = true,
	},

	input = {
		kb_layout = "us",
		kb_variant = "",
		kb_model = "",
		kb_options = "",
		kb_rules = "",
		follow_mouse = 1,
		sensitivity = 0,
		touchpad = {
			natural_scroll = true,
		},
	},

	binds = {
		allow_workspace_cycles = true,
	},
})

---------------------
-- ANIMATIONS
---------------------

hl.curve("customCurve", {
	type = "bezier",
	points = {
		{ 0.12, 0.8 },
		{ 0.72, 1.1 },
	},
})

hl.animation({
	leaf = "windows",
	enabled = true,
	speed = 7,
	bezier = "customCurve",
	style = "popin 90%",
})

hl.animation({
	leaf = "windowsOut",
	enabled = true,
	speed = 7,
	bezier = "default",
	style = "popin 90%",
})

hl.animation({
	leaf = "border",
	enabled = true,
	speed = 10,
	bezier = "default",
})

hl.animation({
	leaf = "borderangle",
	enabled = true,
	speed = 8,
	bezier = "default",
})

hl.animation({
	leaf = "fade",
	enabled = true,
	speed = 7,
	bezier = "default",
})

hl.animation({
	leaf = "workspaces",
	enabled = true,
	speed = 4,
	bezier = "customCurve",
	style = "slidefadevert 70%",
})

-- The original animations section had no active `gestures` setting.
-- Commented legacy gesture:
-- gestures {
--     workspace_swipe = true
-- }

-------------------
-- INPUT DEVICE
-------------------

hl.device({
	name = "epic-mouse-v1",
	sensitivity = -0.5,
})

---------------------
-- KEYBINDINGS
---------------------

local mainMod = "SUPER"

-- Terminal / apps
hl.bind(mainMod .. " + Return", hl.dsp.exec_cmd(terminal))
hl.bind(mainMod .. " + SHIFT + Q", hl.dsp.window.close())
hl.bind(mainMod .. " + SHIFT + M", hl.dsp.exit())
hl.bind(mainMod .. " + E", hl.dsp.exec_cmd(fileManager))
hl.bind(mainMod .. " + V", hl.dsp.window.float({ action = "toggle" }))
-- bind = $mainMod, D, exec, pkill wofi || $menu
hl.bind(mainMod .. " + D", hl.dsp.exec_cmd("/home/bhu1/.config/rofi/launchers/type-1/launcher.sh"))
hl.bind(mainMod .. " + P", hl.dsp.window.pseudo())
-- bind = $mainMod, J, togglesplit, # dwindle
hl.bind(mainMod .. " + F", hl.dsp.window.fullscreen())
hl.bind(mainMod .. " + W", hl.dsp.exec_cmd("/home/bhu1/dev/bin/wallpaper.sh"))
hl.bind(mainMod .. " + Z", hl.dsp.exec_cmd("/home/bhu1/dev/bhu3/clipboard-search.sh"))
hl.bind(mainMod .. " + A", hl.dsp.exec_cmd("/home/bhu1/dev/bhu3/ask-me-anything.sh"))

-- Audio keys
hl.bind("XF86AudioLowerVolume", hl.dsp.exec_cmd("wpctl set-volume @DEFAULT_SINK@ 5%-"))
hl.bind("XF86AudioRaiseVolume", hl.dsp.exec_cmd("wpctl set-volume @DEFAULT_SINK@ 5%+"))
hl.bind(
	"XF86AudioMute",
	hl.dsp.exec_cmd(
		[[pactl set-sink-mute @DEFAULT_SINK@ toggle & brightnessctl -d platform::mute set $(($(brightnessctl -d platform::mute get | awk '{print $1}') ^ 1))]]
	)
)
hl.bind(
	"XF86AudioMicMute",
	hl.dsp.exec_cmd(
		[[pactl set-source-mute @DEFAULT_SINK@ toggle & brightnessctl -d platform::micmute set $(($(brightnessctl -d platform::micmute get | awk '{print $1}') ^ 1))]]
	)
)

-- Media keys
-- bind = , Pause, exec, playerctl play-pause
hl.bind("XF86AudioPlay", hl.dsp.exec_cmd("playerctl play-pause"))
hl.bind("XF86AudioNext", hl.dsp.exec_cmd("playerctl next"))
hl.bind("XF86AudioPrev", hl.dsp.exec_cmd("playerctl previous"))

-- Brightness
hl.bind("XF86MonBrightnessUp", hl.dsp.exec_cmd("/home/bhu1/dev/bin/brightness_increase.sh"))
hl.bind("XF86MonBrightnessDown", hl.dsp.exec_cmd("/home/bhu1/dev/bin/brightness_decrease.sh"))
hl.bind(mainMod .. " + XF86MonBrightnessUp", hl.dsp.exec_cmd("brightnessctl sset 1060"))
hl.bind(
	mainMod .. " + XF86MonBrightnessDown",
	hl.dsp.exec_cmd("brightnessctl sset 1 & xrandr --output eDP-1 --brightness 0.5")
)

-- Screenshot
hl.bind("Print", hl.dsp.exec_cmd("/home/bhu1/dev/bin/screenshot-wayland.sh"))
-- bind = $mainMod, Print, exec, /home/bhu1/dev/bin/screenshot-select-wayland.sh
hl.bind(mainMod .. " + Print", hl.dsp.exec_cmd("/home/bhu1/dev/bin/screenshot-select-wayland.sh"))

-- Move focus with mainMod + arrow keys
hl.bind(mainMod .. " + left", hl.dsp.focus({ direction = "left" }))
hl.bind(mainMod .. " + right", hl.dsp.focus({ direction = "right" }))
hl.bind(mainMod .. " + up", hl.dsp.focus({ direction = "up" }))
hl.bind(mainMod .. " + down", hl.dsp.focus({ direction = "down" }))

-- Switch workspaces with mainMod + [0-9]
for i = 1, 10 do
	local key = i % 10
	hl.bind(mainMod .. " + " .. key, hl.dsp.focus({ workspace = i }))
end

-- Move active window to a workspace with mainMod + SHIFT + [0-9]
for i = 1, 10 do
	local key = i % 10
	hl.bind(mainMod .. " + SHIFT + " .. key, hl.dsp.window.move({ workspace = i }))
end

-- Special workspace (scratchpad)
hl.bind(mainMod .. " + S", hl.dsp.workspace.toggle_special("magic"))
hl.bind(mainMod .. " + SHIFT + S", hl.dsp.window.move({ workspace = "special:magic" }))

-- Scroll through existing workspaces with mainMod + scroll
hl.bind(mainMod .. " + mouse_down", hl.dsp.focus({ workspace = "e+1" }))
hl.bind(mainMod .. " + mouse_up", hl.dsp.focus({ workspace = "e-1" }))

-- Move/resize windows with mainMod + LMB/RMB and dragging
hl.bind(mainMod .. " + mouse:272", hl.dsp.window.drag(), { mouse = true })
hl.bind(mainMod .. " + mouse:273", hl.dsp.window.resize(), { mouse = true })

----------------------------
-- WINDOWS AND WORKSPACES
----------------------------

-- Example window rules retained from the source as comments:
-- windowrule = float, ^(kitty)$
-- windowrulev2 = float,class:^(kitty)$,title:^(kitty)$
-- windowrulev2 = suppressevent maximize, class:.* # You'll probably like this.
-- windowrulev2 = float,class:^(GLava)$
-- windowrulev2 = pin,class:^(GLava)$
-- windowrulev2 = size 200 030,class:^(GLava)$
-- windowrulev2 = move 1250 15,class:^(GLava)$
-- windowrulev2 = noborder,class:^(GLava)$
-- windowrulev2 = nofocus,class:^(GLava)$

hl.window_rule({
	match = {
		class = "^(com\\.gabm\\.satty)$",
	},
	float = true,
	size = { 800, 600 },
	center = true,
})

------------------
-- CUSTOM
------------------

-- The source repeated the SUPER + mouse:272 and SUPER + mouse:273 binds here.
-- Those are already defined above, so only the additional touchpad-friendly
-- modifier-key binds need to be emitted here. This avoids duplicate Lua binds.
hl.bind(mainMod .. " + CONTROL_L", hl.dsp.window.drag(), { mouse = true })
hl.bind(mainMod .. " + ALT_L", hl.dsp.window.resize(), { mouse = true })

-- Original:
-- bindr=SUPER, , exec, pkill wofi || wofi
--
-- Standard modifier-only release form is SUPER + SUPER_L.
-- This maps that intended "release SUPER to launch/toggle Wofi" behavior.
hl.bind(mainMod .. " + SUPER_L", hl.dsp.exec_cmd("pkill wofi || wofi"), { release = true })

-- Multiple Lua binds may share the same key; Hyprland executes them top-to-bottom.
-- Preserve the original cyclenext -> bringactivetotop ordering directly.
hl.bind(mainMod .. " + Tab", hl.dsp.window.cycle_next())
hl.bind(mainMod .. " + Tab", hl.dsp.window.bring_to_top())

-- bind = SUPER, grave, exec, hyprctl dispatch workspace next
-- bind = SUPER, grave, exec, hyprctl dispatch workspace prev
hl.bind(mainMod .. " + grave", hl.dsp.focus({ workspace = "previous" }))
