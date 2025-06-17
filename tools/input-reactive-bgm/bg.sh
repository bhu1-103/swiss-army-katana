#!/bin/bash

while true; do
    play -n \
        synth 0.1 sin 60 fade q 0.005 0.1 0.01 vol 0.8 remix - \
        pad 0 0.4 : \
        synth 0.1 noise bandpass 1800 300 fade q 0.005 0.1 0.01 vol 0.5 remix - \
        pad 0.2 0.2 : \
        synth 0.05 noise bandpass 6000 100 fade q 0.002 0.05 0.01 vol 0.2 remix - \
        pad 0.0 0.0 \
        gain -n \
        silence 1 0.3 1%  # tiny trim to ensure loop isn’t stacking
done
