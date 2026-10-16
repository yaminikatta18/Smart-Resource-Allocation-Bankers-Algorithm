#!/usr/bin/env bash

set -e

cd "$(dirname "$0")/.."

make

output=$(printf '2\n4\n' | ./bankers)

if echo "$output" | grep -q "SAFE STATE"; then
    echo "PASS: Safe state detection works."
else
    echo "FAIL: Safe state detection failed."
    exit 1
fi

output=$(printf '3\n0\n8 0 0\n4\n' | ./bankers)

if echo "$output" | grep -q "exceeds process need"; then
    echo "PASS: Invalid resource request rejected."
else
    echo "FAIL: Resource request validation failed."
    exit 1
fi

echo "All tests passed."
