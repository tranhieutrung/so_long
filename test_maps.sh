#! /bin/bash

# Suppress output for make commands
# make fclean > /dev/null
make > /dev/null

# Define color and bold formatting
GREEN='\033[1;32m'  # Green color
NC='\033[0m'        # No Color (reset)
BOLD='\033[1m'      # Bold formatting

# Print headers with green color and bold formatting
echo -e
echo -e "${GREEN}${BOLD}TEST ERRORS:${NC}"
echo -e

echo -e "${GREEN}${BOLD}1. TEST ERROR FILES:${NC}"
echo -e

echo "Test 1: No args"
./so_long
echo -e

echo "Test 2: NULL"
./so_long ""
echo -e

echo "Test 3: All spaces"
./so_long "    "
echo -e

echo "Test 4: no-existing-file.ber"
./so_long assets/maps/invalid/no-existing-file.ber
echo -e

touch  assets/maps/invalid/map-unreadable.ber > /dev/null
chmod -r assets/maps/invalid/map-unreadable.ber > /dev/null
echo "Test 5: map-unreadable.ber"
./so_long assets/maps/invalid/map-unreadable.ber
rm -rf  assets/maps/invalid/map-unreadable.ber > /dev/null
echo -e

echo "Test 6: .map-hidden.ber"
./so_long assets/maps/invalid/.map-hidden.ber
echo -e

echo "Test 7: map-invalid-extension.txt"
./so_long assets/maps/invalid/map-invalid-extension.txt
echo -e

echo -e "${GREEN}${BOLD}2. TEST ERROR MAPS:${NC}"
echo -e

echo "Test 1: map-empty-line.ber"
./so_long assets/maps/invalid/map-empty-line.ber
echo -e

echo "Test 2: map-empty.ber"
./so_long assets/maps/invalid/map-empty.ber
echo -e

echo "Test 3: map-invalid-character.ber"
./so_long assets/maps/invalid/map-invalid-character.ber
echo -e

echo "Test 4: map-missing-C.ber"
./so_long assets/maps/invalid/map-missing-C.ber
echo -e

echo "Test 5: map-missing-E.ber"
./so_long assets/maps/invalid/map-missing-E.ber
echo -e

echo "Test 6: map-missing-P.ber"
./so_long assets/maps/invalid/map-missing-P.ber
echo -e

echo "Test 7: map-missing-W.ber"
./so_long assets/maps/invalid/map-missing-W.ber
echo -e

echo "Test 8: map-extra-P.ber"
./so_long assets/maps/invalid/map-extra-P.ber
echo -e

echo "Test 9: map-extra-E.ber"
./so_long assets/maps/invalid/map-extra-E.ber
echo -e

echo "Test 10: map-not-rectangular.ber"
./so_long assets/maps/invalid/map-not-rectangular.ber
echo -e

echo "Test 11: map-no-exit-path.ber"
./so_long assets/maps/invalid/map-no-exit-path.ber
echo -e

echo "Test 12: map-collectible-fail.ber"
./so_long assets/maps/invalid/map-collectible-fail.ber
echo -e

# # Print valid map tests with green color and bold formatting
# echo -e "${GREEN}${BOLD}TEST VALID MAPS:${NC}"
# echo -e

# echo "Test 1: 1.ber"
# ./so_long assets/maps/1.ber
# echo -e

# echo "Test 2: 2.ber"
# ./so_long assets/maps/2.ber
# echo -e

# make fclean > /dev/null