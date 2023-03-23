#!/bin/sh
# this gives you a primitive interactive client for dumbchat

NICK="ASS"
ADDRESS="localhost"

  if test -n "$MESSAGE"; then
    ./Manna "$ADDRESS" "$NICK" "$MESSAGE" # send message
  fi
done
