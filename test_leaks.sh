#!/bin/bash

# Suppress output for make commands
make fclean > /dev/null
make > /dev/null

# Define color and bold formatting
GREEN='\033[1;32m'  # Green color
RED='\033[1;31m'    # Red color
NC='\033[0m'        # No Color (reset)
BOLD='\033[1m'      # Bold formatting

# Function to run valgrind and check for memory leaks
run_valgrind() 
{
    local test_name=$1
    local test_command=$2

    valgrind_output=$(valgrind --leak-check=full --log-file=valgrind_out.txt $test_command 2>&1)
	if grep -q "in use at exit: 0 bytes in 0 blocks" valgrind_out.txt && grep -q "ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)" valgrind_out.txt; then
        echo -e "$test_name: ${GREEN}${BOLD}OK${NC}"
    else
        echo -e "$test_name: ${RED}${BOLD}KO${NC}"
    fi
    echo -e

    rm -f valgrind_out.txt
}

# Print headers with green color and bold formatting
echo -e
echo -e "${GREEN}${BOLD}TEST ERRORS:${NC}"
echo -e

echo -e "${GREEN}${BOLD}1. TEST ERROR FILES:${NC}"
echo -e

run_valgrind "Test 1: NULL" "./so_long \"\""
run_valgrind "Test 2: no-existing-file.ber" "./so_long assets/maps/invalid/no-existing-file.ber"
run_valgrind "Test 3: map-unreadable.ber" "./so_long assets/maps/invalid/map-unreadable.ber"
run_valgrind "Test 4: .map-hidden.ber" "./so_long assets/maps/invalid/.map-hidden.ber"
run_valgrind "Test 5: map-invalid-extension.txt" "./so_long assets/maps/invalid/map-invalid-extension.txt"

echo -e "${GREEN}${BOLD}2. TEST ERROR MAPS:${NC}"
echo -e

run_valgrind "Test 1: map-empty-line.ber" "./so_long assets/maps/invalid/map-empty-line.ber"
run_valgrind "Test 2: map-empty.ber" "./so_long assets/maps/invalid/map-empty.ber"
run_valgrind "Test 3: map-invalid-character.ber" "./so_long assets/maps/invalid/map-invalid-character.ber"
run_valgrind "Test 4: map-missing-C.ber" "./so_long assets/maps/invalid/map-missing-C.ber"
run_valgrind "Test 5: map-missing-E.ber" "./so_long assets/maps/invalid/map-missing-E.ber"
run_valgrind "Test 6: map-missing-P.ber" "./so_long assets/maps/invalid/map-missing-P.ber"
run_valgrind "Test 7: map-missing-W.ber" "./so_long assets/maps/invalid/map-missing-W.ber"
run_valgrind "Test 8: map-extra-P.ber" "./so_long assets/maps/invalid/map-extra-P.ber"
run_valgrind "Test 9: map-extra-E.ber" "./so_long assets/maps/invalid/map-extra-E.ber"
run_valgrind "Test 10: map-not-rectangular.ber" "./so_long assets/maps/invalid/map-not-rectangular.ber"
run_valgrind "Test 11: map-no-exit-path.ber" "./so_long assets/maps/invalid/map-no-exit-path.ber"
run_valgrind "Test 12: map-collectible-fail.ber" "./so_long assets/maps/invalid/map-collectible-fail.ber"

# Print valid map tests with green color and bold formatting
echo -e "${GREEN}${BOLD}TEST VALID MAPS:${NC}"
echo -e

run_valgrind "Test 1: 1.ber" "./so_long assets/maps/1.ber"
run_valgrind "Test 2: 2.ber" "./so_long assets/maps/2.ber"

make fclean > /dev/null
