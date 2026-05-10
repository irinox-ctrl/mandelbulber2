#!/bin/bash
# ROLLBACK script — herstelt de volledige repo vanuit de complete backup
# Gebruik: ./ROLLBACK_NAAR_STABIEL.sh

set -e

BACKUP="mandelbulber2_COMPLETE_REPO_BACKUP_20260510_130836.tar.gz"
REPO_DIR="mandelbulber2"

cd "$(dirname "$0")"

if [ ! -f "$BACKUP" ]; then
    echo "ERROR: Backup niet gevonden: $BACKUP"
    exit 1
fi

echo "Rollback starten vanuit $BACKUP..."

# Veiligheid: timestamp de huidige staat als die bestaat
if [ -d "$REPO_DIR" ]; then
    TIMESTAMP=$(date +%Y%m%d_%H%M%S)
    mv "$REPO_DIR" "${REPO_DIR}_pre_rollback_${TIMESTAMP}"
    echo "Huidige repo verplaatst naar ${REPO_DIR}_pre_rollback_${TIMESTAMP}"
fi

# Pak uit
tar -xzf "$BACKUP"

echo "Rollback voltooid. Repo staat klaar in $REPO_DIR/"
echo "Branch: $(cd $REPO_DIR && git branch --show-current)"
echo "Laatste commit: $(cd $REPO_DIR && git log -1 --oneline)"
