#!/bin/bash

EXEC=./cube3D
MAP_DIR="./test_MAP"
LOG_DIR="valgrind_logs"

mkdir -p "$LOG_DIR"

echo "🧪 Début des tests Valgrind sur les maps .cub dans $MAP_DIR..."

for map in $MAP_DIR/*.cub; do
  mapname=$(basename "$map")
  log="$LOG_DIR/${mapname}.log"

  echo "→ Test de $mapname..."
  valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all \
           --track-origins=yes "$EXEC" "$map" &> "$log"
done

echo -e "\n✅ Tous les tests sont terminés.\n"

# Résumé détaillé
echo "📋 Résumé des fuites et allocations :"
for log in "$LOG_DIR"/*.log; do
  logname=$(basename "$log")

  echo -e "\n🔎 $logname"

  # ERROR SUMMARY
  grep "ERROR SUMMARY" "$log" | head -n1

  # LEAK SUMMARY
  grep -A5 "LEAK SUMMARY:" "$log"

  # HEAP SUMMARY (allocs / frees)
  grep "in use at exit" "$log"
  grep "total heap usage" "$log"

  # STILL REACHABLE
  grep "still reachable" "$log"
done

