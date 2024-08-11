#! /bin/bash

make fclean
make

echo "Test error maps:"

echo "Test 1: .ber"
./so_long assets/maps/invalid/.ber

echo "Test 2: .txt"
./so_long assets/maps/invalid/.txt

echo "Test 3: map-collectible-fail.ber"
./so_long assets/maps/invalid/map-collectible-fail.ber

echo "Test 4: map-empty-line.ber"
./so_long assets/maps/invalid/map-empty-line.ber

echo "Test 5: map-empty.ber"
./so_long assets/maps/invalid/map-empty.ber

echo "Test 6: map-extra-P.ber"
./so_long assets/maps/invalid/map-extra-P.ber

echo "Test 7: map-extra-parameter.ber"
./so_long assets/maps/invalid/map-extra-parameter.ber

echo "Test 8: map-invalid-extension.txt"
./so_long assets/maps/invalid/map-invalid-extension.txt

echo "Test 9: map-missing-C.ber"
./so_long assets/maps/invalid/map-missing-C.ber

echo "Test 10: map-missing-E.ber"
./so_long assets/maps/invalid/map-missing-E.ber

echo "Test 11: map-missing-P.ber"
./so_long assets/maps/invalid/map-missing-P.ber

echo "Test 12: map-missing-W.ber"
./so_long assets/maps/invalid/map-missing-W.ber

echo "Test 13: map-no-exit-path.ber"
./so_long assets/maps/invalid/map-no-exit-path.ber

echo "Test 14: map-not-rectangular.ber"
./so_long assets/maps/invalid/map-not-rectangular.ber

echo "Test valid maps:"

echo "Test 1: 1.ber"
./so_long assets/maps/1.ber

echo "Test 2: 2.ber"
./so_long assets/maps/2.ber