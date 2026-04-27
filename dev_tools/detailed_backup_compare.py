#!/usr/bin/env python3
"""
DETAILED BACKUP COMPARISON
===========================
Vergelijk EXACT wat in backup zit vs current repo!

Author: Claude + Joeri
Date: 2026-04-19
"""

import tarfile
from pathlib import Path
from typing import Set
import subprocess

def get_backup_files(backup_path: Path) -> Set[str]:
    """Get all source files from backup"""
    files = set()

    print(f"📦 Extracting file list from {backup_path.name}...")

    try:
        with tarfile.open(backup_path, 'r:gz') as tar:
            for member in tar.getmembers():
                if member.isdir():
                    continue

                # Only source files
                if not any(member.name.endswith(ext) for ext in ['.cpp', '.hpp', '.h', '.cl', '.ui']):
                    continue

                # Skip build artifacts
                if '/qmake/' in member.name or '/build/' in member.name:
                    continue
                if '.bak' in member.name or 'backup' in member.name.lower():
                    continue
                if member.name.endswith('.o') or member.name.endswith('.a'):
                    continue

                # Get just the filename
                filename = Path(member.name).name
                files.add(filename)

    except Exception as e:
        print(f"❌ Error: {e}")

    return files

def get_repo_files(repo_dir: Path) -> Set[str]:
    """Get all source files from repo"""
    files = set()

    print(f"📁 Scanning current repo...")

    for ext in ['*.cpp', '*.hpp', '*.h', '*.cl', '*.ui']:
        for f in repo_dir.rglob(ext):
            # Skip build artifacts
            if '/qmake/' in str(f) or '/build/' in str(f):
                continue
            if '.bak' in f.name or 'backup' in f.name.lower():
                continue

            files.add(f.name)

    return files

def categorize_files(files: Set[str]) -> dict:
    """Categorize files by type"""

    categories = {
        'formulas': set(),
        'ui_files': set(),
        'opencl': set(),
        'core_cpp': set(),
        'core_headers': set(),
    }

    for f in files:
        if f.endswith('.ui'):
            categories['ui_files'].add(f)
        elif f.endswith('.cl'):
            categories['opencl'].add(f)
        elif f.startswith('fractal_') and f.endswith('.cpp'):
            categories['formulas'].add(f)
        elif f.endswith('.cpp'):
            categories['core_cpp'].add(f)
        elif f.endswith(('.h', '.hpp')):
            categories['core_headers'].add(f)

    return categories

def main():
    print()
    print("=" * 70)
    print("🔍 DETAILED BACKUP vs REPO COMPARISON")
    print("=" * 70)
    print()

    backup_dir = Path.home() / "mandelbulber2_backups"
    repo_dir = Path.cwd().parent / "mandelbulber2"

    # Use the complete backup
    backup_name = "Backup Mandelbulber met alle groepeen, deformers, cloner, OT , fractal textures.tar.gz"
    backup_path = backup_dir / backup_name

    if not backup_path.exists():
        print(f"❌ Backup not found: {backup_path}")
        return

    # Get file lists
    backup_files = get_backup_files(backup_path)
    repo_files = get_repo_files(repo_dir)

    print(f"\n📊 FILES FOUND:")
    print(f"   Backup: {len(backup_files)} files")
    print(f"   Repo:   {len(repo_files)} files")
    print()

    # Compare
    only_in_backup = backup_files - repo_files
    only_in_repo = repo_files - backup_files
    in_both = backup_files & repo_files

    print(f"✅ In both:        {len(in_both)} files")
    print(f"🆕 Only in backup: {len(only_in_backup)} files")
    print(f"⚠️  Only in repo:   {len(only_in_repo)} files")
    print()

    # Categorize missing files
    print("=" * 70)
    print("🆕 MISSING FILES (in backup but NOT in repo)")
    print("=" * 70)
    print()

    missing_categories = categorize_files(only_in_backup)

    print(f"📝 FORMULAS: {len(missing_categories['formulas'])} missing")
    if missing_categories['formulas']:
        for f in sorted(missing_categories['formulas'])[:20]:
            print(f"   - {f}")
        if len(missing_categories['formulas']) > 20:
            print(f"   ... and {len(missing_categories['formulas'])-20} more")
    print()

    print(f"🎨 UI FILES: {len(missing_categories['ui_files'])} missing")
    if missing_categories['ui_files']:
        for f in sorted(missing_categories['ui_files'])[:20]:
            print(f"   - {f}")
        if len(missing_categories['ui_files']) > 20:
            print(f"   ... and {len(missing_categories['ui_files'])-20} more")
    print()

    print(f"🎮 OPENCL: {len(missing_categories['opencl'])} missing")
    if missing_categories['opencl']:
        for f in sorted(missing_categories['opencl'])[:20]:
            print(f"   - {f}")
        if len(missing_categories['opencl']) > 20:
            print(f"   ... and {len(missing_categories['opencl'])-20} more")
    print()

    print(f"⚙️  CORE CPP: {len(missing_categories['core_cpp'])} missing")
    if missing_categories['core_cpp']:
        for f in sorted(missing_categories['core_cpp'])[:20]:
            print(f"   - {f}")
        if len(missing_categories['core_cpp']) > 20:
            print(f"   ... and {len(missing_categories['core_cpp'])-20} more")
    print()

    print(f"📋 HEADERS: {len(missing_categories['core_headers'])} missing")
    if missing_categories['core_headers']:
        for f in sorted(missing_categories['core_headers'])[:20]:
            print(f"   - {f}")
        if len(missing_categories['core_headers']) > 20:
            print(f"   ... and {len(missing_categories['core_headers'])-20} more")
    print()

    # Total
    total_missing = sum(len(v) for v in missing_categories.values())

    print("=" * 70)
    print(f"📈 SUMMARY")
    print("=" * 70)
    print(f"Total files missing from repo: {total_missing}")
    print()
    print(f"💡 RECOMMENDATION:")
    print(f"   Extract from: {backup_name}")
    print(f"   This will add {total_missing} files to your repo")
    print()

if __name__ == "__main__":
    main()
