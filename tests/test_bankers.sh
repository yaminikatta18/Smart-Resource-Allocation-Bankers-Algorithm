#!/usr/bin/env bash

set -e

cd "$(dirname "$0")/.."

make

# Test 1: Safe-state detection
output=$(printf '2\n4\n' | ./bankers)

if echo "$output" | grep -q "SAFE STATE"; then
    echo "PASS: Safe state detection works."
else
    echo "FAIL: Safe state detection failed."
    echo "$output"
    exit 1
fi

# Test 2: Reject a request exceeding process need
output=$(printf '3\n0\n8 0 0\n4\n' | ./bankers)

if echo "$output" | grep -q "exceeds process need"; then
    echo "PASS: Invalid resource request rejected."
else
    echo "FAIL: Process need validation failed."
    echo "$output"
    exit 1
fi

# Test 3: Reject a request exceeding available resources
# P1 needs (1,2,2), but only (3,3,2) is available.
# Request (1,2,3) exceeds P1's need for resource C,
# so use P2, whose need is (6,0,0), instead.
# Request (4,0,0) exceeds P2's available resource A? No:
# available A is 3, so this exceeds available resources.
output=$(printf '3\n2\n4 0 0\n4\n' | ./bankers)

if echo "$output" | grep -q "Resources unavailable"; then
    echo "PASS: Request exceeding available resources rejected."
else
    echo "FAIL: Resource availability validation failed."
    echo "$output"
    exit 1
fi

echo "All tests passed."
