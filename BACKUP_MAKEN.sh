#!/bin/bash
# BACKUP_MAKEN — maakt een nieuwe MASTER_BACKUP van de huidige repo
# Gebruik: ./BACKUP_MAKEN.sh [label]

set -e

cd "$(dirname "$0")"

LABEL="${1:-$(date +%Y%m%d_%H%M%S)}"
BACKUP_NAME="MASTER_BACKUP_${LABEL}.tar.gz"

echo "=== BACKUP MAKEN ==="
echo "Bestand: $BACKUP_NAME"

# Verwijder oude master backups (behoudt de laatste 2)
ls -t MASTER_BACKUP_*.tar.gz 2>/dev/null | tail -n +3 | xargs -r rm -f

# Maak nieuwe backup
tar -czf "$BACKUP_NAME" mandelbulber2/

echo "Backup klaar: $(ls -lh $BACKUP_NAME | awk '{print $5, $9}')"
echo ""
echo "Beschikbare backups:"
ls -lh MASTER_BACKUP_*.tar.gz 2>/dev/null || echo "Geen backups gevonden"
