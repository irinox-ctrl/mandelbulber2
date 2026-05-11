#!/bin/bash
# HERSTELLEN — herstelt de repo vanuit een MASTER_BACKUP
# Gebruik: ./HERSTELLEN.sh [backup-bestand]

set -e

cd "$(dirname "$0")"

BACKUP="${1:-$(ls -t MASTER_BACKUP_*.tar.gz 2>/dev/null | head -1)}"

if [ -z "$BACKUP" ] || [ ! -f "$BACKUP" ]; then
    echo "ERROR: Geen backup gevonden."
    echo "Beschikbare backups:"
    ls -1 MASTER_BACKUP_*.tar.gz 2>/dev/null || echo "  (geen)"
    exit 1
fi

echo "=== HERSTELLEN ==="
echo "Bron: $BACKUP"

# Veiligheid: verplaats huidige repo
if [ -d "mandelbulber2" ]; then
    TIMESTAMP=$(date +%Y%m%d_%H%M%S)
    mv mandelbulber2 "mandelbulber2_pre_herstel_${TIMESTAMP}"
    echo "Huidige repo verplaatst naar: mandelbulber2_pre_herstel_${TIMESTAMP}"
fi

# Pak uit
tar -xzf "$BACKUP"

echo ""
echo "Herstel voltooid."
echo "Branch: $(cd mandelbulber2 && git branch --show-current)"
echo "Laatste commit: $(cd mandelbulber2 && git log -1 --oneline)"
echo ""
echo "OM TE BOUWEN:"
echo "  cd mandelbulber2/build"
echo "  make clean && qmake ../qmake/mandelbulber.pro && make -j\$(nproc)"
