#!/usr/bin/env bash

set -e

eval "$(/home/linuxbrew/.linuxbrew/bin/brew shellenv)"
make

echo "Dev container created successfully"