#!/usr/bin/env python3
"""
MAP PRIMITIVES FROM BACKUPS
============================
Scan backups en map alle primitive bestanden!

Dit script:
1. Scant alle backups in ~/mandelbulber2_backups/
2. Vindt alle primitive files (*.cpp, *.ui)
3. Maakt overzicht per backup
4. Toont welke primitives gevonden zijn
5. Vergelijkt met huidige repo

Author: Claude + Joeri
Date: 2026-04-19
"""

import tarfile
from pathlib import Path
from typing import List, Dict, Set
from dataclasses import dataclass
from fnmatch import fnmatch


@dataclass
class PrimitiveFile:
    """Info over 1 primitive file"""
    name: str
    path: str
    backup: str
    size: int
    type: str  # "definition", "ui", "opencl"


class PrimitiveMapper:
    """Map alle primitives in backups"""

    def __init__(self, backup_dir: Path, repo_dir: Path):
        self.backup_dir = backup_dir
        self.repo_dir = repo_dir
        self.primitives_found: List[PrimitiveFile] = []

    def scan_all_backups(self):
        """Scan alle backups"""

        print("=" * 70)
        print("🗺️  PRIMITIVE MAPPER")
        print("=" * 70)
        print()

        # Vind alle backups
        backups = sorted(self.backup_dir.glob("*.tar.gz"))

        print(f"📁 Scanning {len(backups)} backups...")
        print()

        for backup in backups:
            print(f"  🔍 {backup.name}")
            self._scan_backup(backup)

        print()
        print(f"✅ Scan complete!")
        print(f"   Found {len(self.primitives_found)} primitive files")
        print()

    def _scan_backup(self, backup_path: Path):
        """Scan 1 backup voor primitives"""

        try:
            with tarfile.open(backup_path, 'r:gz') as tar:
                for member in tar.getmembers():
                    if member.isdir():
                        continue

                    # Check if primitive file
                    prim = self._check_primitive(member.name, backup_path.name, member.size)
                    if prim:
                        self.primitives_found.append(prim)

        except Exception as e:
            print(f"     ⚠️  Error: {e}")

    def _check_primitive(self, path: str, backup: str, size: int) -> PrimitiveFile | None:
        """Check if dit een primitive file is"""

        # Patterns voor primitives
        patterns = {
            'definition': "*/formula/definition/primitive_*.cpp",
            'ui': "*/formula/ui/primitive_*.ui",
            'opencl': "*/formula/opencl/primitive_*.cl",
        }

        for prim_type, pattern in patterns.items():
            if self._matches_glob(path, pattern):
                name = Path(path).name
                return PrimitiveFile(
                    name=name,
                    path=path,
                    backup=backup,
                    size=size,
                    type=prim_type
                )

        return None

    def _matches_glob(self, path: str, pattern: str) -> bool:
        """Match path against glob pattern"""

        # Direct match
        if fnmatch(path, pattern):
            return True

        # Match filename only
        if fnmatch(Path(path).name, Path(pattern).name):
            pattern_parts = Path(pattern).parts
            path_parts = Path(path).parts

            # Check if parent path matches
            if '*' in pattern_parts[0]:
                return True

        return False

    def show_overview(self):
        """Toon overzicht van gevonden primitives"""

        print("=" * 70)
        print("📊 PRIMITIVES OVERVIEW")
        print("=" * 70)
        print()

        # Group by name
        by_name: Dict[str, List[PrimitiveFile]] = {}

        for prim in self.primitives_found:
            if prim.name not in by_name:
                by_name[prim.name] = []
            by_name[prim.name].append(prim)

        # Show unique primitives
        print(f"Found {len(by_name)} unique primitive files:")
        print()

        for name in sorted(by_name.keys()):
            files = by_name[name]
            print(f"  📄 {name}")
            print(f"     Found in {len(files)} backup(s)")

            # Show by type
            types = set(f.type for f in files)
            for prim_type in ['definition', 'ui', 'opencl']:
                if prim_type in types:
                    count = len([f for f in files if f.type == prim_type])
                    print(f"     - {prim_type}: {count}x")

            # Show most recent backup
            newest = max(files, key=lambda f: f.backup)
            print(f"     Latest: {newest.backup}")
            print()

    def show_by_backup(self):
        """Toon primitives per backup"""

        print("=" * 70)
        print("📦 PRIMITIVES BY BACKUP")
        print("=" * 70)
        print()

        # Group by backup
        by_backup: Dict[str, List[PrimitiveFile]] = {}

        for prim in self.primitives_found:
            if prim.backup not in by_backup:
                by_backup[prim.backup] = []
            by_backup[prim.backup].append(prim)

        # Show per backup (sorted by count)
        backups_sorted = sorted(
            by_backup.items(),
            key=lambda x: len(x[1]),
            reverse=True
        )

        for backup, prims in backups_sorted[:10]:  # Top 10
            print(f"📦 {backup}")
            print(f"   {len(prims)} primitive files")

            # Count by type
            def_count = len([p for p in prims if p.type == 'definition'])
            ui_count = len([p for p in prims if p.type == 'ui'])
            cl_count = len([p for p in prims if p.type == 'opencl'])

            print(f"   - Definitions: {def_count}")
            print(f"   - UI files: {ui_count}")
            print(f"   - OpenCL: {cl_count}")
            print()

        if len(by_backup) > 10:
            print(f"... and {len(by_backup) - 10} more backups")
            print()

    def compare_with_repo(self):
        """Vergelijk met huidige repo"""

        print("=" * 70)
        print("🔄 COMPARE WITH CURRENT REPO")
        print("=" * 70)
        print()

        # Find primitives in current repo
        repo_prims = set()

        # Check formula/definition
        def_dir = self.repo_dir / "mandelbulber2" / "formula" / "definition"
        if def_dir.exists():
            repo_prims.update(f.name for f in def_dir.glob("primitive_*.cpp"))

        # Check formula/ui
        ui_dir = self.repo_dir / "mandelbulber2" / "formula" / "ui"
        if ui_dir.exists():
            repo_prims.update(f.name for f in ui_dir.glob("primitive_*.ui"))

        print(f"📁 Current repo has: {len(repo_prims)} primitive files")
        print()

        # Get unique names from backups
        backup_prims = set(p.name for p in self.primitives_found)

        print(f"💾 Backups contain: {len(backup_prims)} unique primitive files")
        print()

        # Compare
        only_in_backups = backup_prims - repo_prims
        only_in_repo = repo_prims - backup_prims
        in_both = repo_prims & backup_prims

        print(f"✅ Already in repo: {len(in_both)} files")
        print(f"🆕 Only in backups: {len(only_in_backups)} files")
        print(f"⚠️  Only in repo: {len(only_in_repo)} files")
        print()

        if only_in_backups:
            print("🆕 NEW FILES IN BACKUPS (not in current repo):")
            for name in sorted(only_in_backups):
                # Find which backup has it
                prims = [p for p in self.primitives_found if p.name == name]
                backup = max(prims, key=lambda p: p.backup).backup
                print(f"   + {name}")
                print(f"     (in {backup})")
            print()

        if only_in_repo:
            print("⚠️  FILES ONLY IN REPO (missing from backups?):")
            for name in sorted(only_in_repo):
                print(f"   - {name}")
            print()

    def get_best_backup_for_extraction(self) -> Path | None:
        """Vind beste backup voor extractie"""

        print("=" * 70)
        print("🎯 BEST BACKUP FOR EXTRACTION")
        print("=" * 70)
        print()

        # Group by backup
        by_backup: Dict[str, List[PrimitiveFile]] = {}

        for prim in self.primitives_found:
            if prim.backup not in by_backup:
                by_backup[prim.backup] = []
            by_backup[prim.backup].append(prim)

        # Find backup with most primitives AND "primitive" in name
        candidates = []

        for backup, prims in by_backup.items():
            score = len(prims)

            # Bonus for "primitive" in name
            if "primitive" in backup.lower():
                score += 100

            # Bonus for "all" in name
            if "all" in backup.lower():
                score += 50

            candidates.append((score, backup, prims))

        # Sort by score
        candidates.sort(reverse=True)

        if candidates:
            score, best_backup, prims = candidates[0]

            print(f"🏆 BEST BACKUP: {best_backup}")
            print(f"   Score: {score}")
            print(f"   Contains: {len(prims)} primitive files")
            print()

            # Show top 5 candidates
            print("Top 5 candidates:")
            for i, (s, b, p) in enumerate(candidates[:5], 1):
                print(f"  {i}. {b}")
                print(f"     Score: {s}, Files: {len(p)}")

            print()
            return self.backup_dir / best_backup

        return None


def main():
    """Main entry"""

    print()
    print("╔" + "═"*68 + "╗")
    print("║" + " "*20 + "PRIMITIVE MAPPER v1.0" + " "*28 + "║")
    print("╚" + "═"*68 + "╝")
    print()

    backup_dir = Path.home() / "mandelbulber2_backups"
    repo_dir = Path.cwd().parent  # Assuming we're in dev_tools

    if not backup_dir.exists():
        print(f"❌ Backup directory not found: {backup_dir}")
        return

    mapper = PrimitiveMapper(backup_dir, repo_dir)

    # 1. Scan all backups
    mapper.scan_all_backups()

    # 2. Show overview
    mapper.show_overview()

    # 3. Show by backup
    mapper.show_by_backup()

    # 4. Compare with repo
    mapper.compare_with_repo()

    # 5. Find best backup
    best = mapper.get_best_backup_for_extraction()

    print("=" * 70)
    print("✅ MAPPING COMPLETE!")
    print("=" * 70)
    print()

    if best:
        print(f"💡 NEXT STEP:")
        print(f"   Use backup: {best.name}")
        print(f"   To extract primitives to repo")
        print()


if __name__ == "__main__":
    main()
