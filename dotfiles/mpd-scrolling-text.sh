#!/usr/bin/bash

play_emojis=(
  "🎸" "🎶" "🎧" "𝄞" "★" "🌟" "✨" "🔥" "🚀" "💃"
  "🎵" "🎼" "📻" "🕺" "🎤" "🔊" "🔉" "📀" "💿" "🎷"
  "🎺" "🥁" "🎹" "🎻" "🪕" "🎬" "🎥" "🎯" "🏆" "🌠"
  "💫" "🌀" "🔮" "🪄" "🎭" "🎪"
)

pause_emojis=(
  "⏸️" "🤫" "🛑" "🔇" "🤐" "🙊" "🔕" "😴" "💤" "🤔"
  "🥱" "🌙" "🌛" "🌜" "🌓" "🌑" "🚦" "⏳" "⌛" "📴" "📵"
  "📎" "🔗" "💭" "🧐" "📚" "✋" "🙅‍♂️" "🙅‍♀️" "🚫" "❌"
  "💔" "🙃" "😶" "😐"
)

play_emoji="${play_emojis[$(( RANDOM % ${#play_emojis[@]} ))]}"
pause_emoji="${pause_emojis[$(( RANDOM % ${#pause_emojis[@]} ))]}"

display() {
  local scrolling_title="$1"
  local status="$2"

  if [ "$status" = "[paused]" ]; then
    echo "{\"text\": \"${pause_emoji}${scrolling_title}\",\"tooltip\": \"song is paused\"}"
  elif [[ "$status" = "[playing]" ]]; then
    echo "{\"text\": \"${play_emoji}${scrolling_title}\",\"tooltip\": \"song is playing\"}"
  else
    echo "{\"text\": \"⏹ Stopped\", \"tooltip\": \"No song playing\"}"
  fi
}

title=$(mpc current --format "%title% - %artist%")
if [ -z "$title" ]; then
  title="____________.____"
fi

status=$(mpc status | grep -Eo '\[playing\]|\[paused\]')

title="      ${title}      "

pos=$(( $(date +%s) % ${#title} ))

scrolling_title="${title:pos:20}"

display "$scrolling_title" "$status"
