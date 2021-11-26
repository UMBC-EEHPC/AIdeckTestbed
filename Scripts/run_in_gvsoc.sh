#!/bin/sh
gapy --target=ai_deck --platform=gvsoc --work-dir=. --config-ini="$1"/../ai_deck.ini    run --image --binary="$1"/"$2"
gapy --target=ai_deck --platform=gvsoc --work-dir=. --config-ini="$1"/../ai_deck.ini    run --flash --binary="$1"/"$2"
gapy --target=ai_deck --platform=gvsoc --work-dir=. --config-ini="$1"/../ai_deck.ini    run --exec-prepare --exec --binary="$1"/"$2"