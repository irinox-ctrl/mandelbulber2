#!/usr/bin/env python3
"""
MAP TRANSFORM SYSTEMS FROM BACKUPS
===================================
Scan backups voor cloner, deformers, repeats, pivot point systems!

SYSTEMEN DIE WE ZOEKEN:
- Cloner/Repeat system (epic repeat modes)
- Deformation transforms
- Pivot point / world space system
- Repeat bounds
- Transform modes (spiral, wave, brick, honeycomb, etc.)

Author: Claude + Joeri
Date: 2026-04-19
"""

import tarfile
from pathlib import Path
from typing import List, Dict, Set
from dataclasses import dataclass
from fnmatch import fnmatch
import re


@dataclass
class TransformFile:
    """Info over 1 transform system file"""
    name: str
    path: str
    backup: str
    size: int
    system: str  # "cloner", "deformer", "pivot", "repeat", etc.


class TransformSystemMapper:
    """Map alle transform systems in backups"""

    # Keywords die wijzen op transform systems
    SYSTEM_PATTERNS = {
        'cloner': [
            '*cloner*',
            '*epic_repeat*',
            '*repeat_mode*',
            '*transf_repeat*'
        ],
        'deformer': [
            '*deform*',
            '*bend*',
            '*twist*',
            '*taper*'
        ],
        'pivot': [
            '*pivot*',
            '*world_space*',
            '*world_coord*',
            '*rotation_center*'
        ],
        'repeat_bounds': [
            '*repeat_bound*',
            '*repeat_limit*'
        ],
        'repeat_modes': [
            '*spiral*',
            '*wave*',
            '*brick*',
            '*honeycomb*',
            '*radial*',
            '*shell*'
        ],
        'emission': [
            '*emission*',
            '*emitter*'
        ]
    }

    def __init__(self, backup_dir: Path, repo_dir: Path):
        self.backup_dir = backup_dir
        self.repo_dir = repo_dir
        self.files_found: List[TransformFile] = []

    def scan_all_backups(self):
        """Scan alle backups"""

        print("=" * 70)
        print("🔍 TRANSFORM SYSTEM MAPPER")
        print("=" * 70)
        print()

        # Vind alle backups
        backups = sorted(self.backup_dir.glob("*.tar.gz"))

        print(f"📁 Scanning {len(backups)} backups for transform systems...")
        print()

        for backup in backups:
            # Skip zeer grote backups voor snelheid (optioneel)
            size_mb = backup.stat().st_size / (1024 * 1024)

            print(f"  🔍 {backup.name} ({size_mb:.1f} MB)")
            self._scan_backup(backup)

        print()
        print(f"✅ Scan complete!")
        print(f"   Found {len(self.files_found)} transform system files")
        print()

    def _scan_backup(self, backup_path: Path):
        """Scan 1 backup voor transform systems"""

        try:
            with tarfile.open(backup_path, 'r:gz') as tar:
                for member in tar.getmembers():
                    if member.isdir():
                        continue

                    # Skip build artifacts
                    if '/qmake/' in member.name or '/build/' in member.name:
                        continue
                    if member.name.endswith('.o') or member.name.endswith('.a'):
                        continue

                    # Check if transform system file
                    tf = self._check_transform_file(member.name, backup_path.name, member.size)
                    if tf:
                        self.files_found.append(tf)

        except Exception as e:
            print(f"     ⚠️  Error: {e}")

    def _check_transform_file(self, path: str, backup: str, size: int) -> TransformFile | None:
        """Check if dit een transform system file is"""

        path_lower = path.lower()
        name = Path(path).name

        # Skip backups binnen backups
        if '.bak' in name or 'backup' in name:
            return None

        # Check relevante file types
        if not any(path.endswith(ext) for ext in ['.cpp', '.h', '.hpp', '.cl', '.ui']):
            return None

        # Check elk systeem
        for system, patterns in self.SYSTEM_PATTERNS.items():
            for pattern in patterns:
                if fnmatch(name.lower(), pattern.lower()):
                    return TransformFile(
                        name=name,
                        path=path,
                        backup=backup,
                        size=size,
                        system=system
                    )

        return None

    def show_overview_by_system(self):
        """Toon overzicht per systeem"""

        print("=" * 70)
        print("📊 TRANSFORM SYSTEMS OVERVIEW")
        print("=" * 70)
        print()

        # Group by system
        by_system: Dict[str, List[TransformFile]] = {}

        for tf in self.files_found:
            if tf.system not in by_system:
                by_system[tf.system] = []
            by_system[tf.system].append(tf)

        # Show per systeem
        for system in sorted(by_system.keys()):
            files = by_system[system]
            print(f"🔧 {system.upper()} SYSTEM")
            print(f"   {len(files)} files found")

            # Unique filenames
            unique_names = set(f.name for f in files)
            print(f"   {len(unique_names)} unique files")

            # Show enkele voorbeelden
            examples = sorted(unique_names)[:5]
            for ex in examples:
                print(f"     - {ex}")
            if len(unique_names) > 5:
                print(f"     ... and {len(unique_names) - 5} more")

            print()

    def show_best_backups(self):
        """Toon beste backups per systeem"""

        print("=" * 70)
        print("🏆 BEST BACKUPS PER SYSTEM")
        print("=" * 70)
        print()

        # Group by system
        by_system: Dict[str, List[TransformFile]] = {}

        for tf in self.files_found:
            if tf.system not in by_system:
                by_system[tf.system] = []
            by_system[tf.system].append(tf)

        # Voor elk systeem, vind beste backup
        for system in sorted(by_system.keys()):
            files = by_system[system]

            # Count per backup
            backup_counts: Dict[str, int] = {}
            for f in files:
                backup_counts[f.backup] = backup_counts.get(f.backup, 0) + 1

            # Sort by count
            best_backups = sorted(backup_counts.items(), key=lambda x: x[1], reverse=True)[:3]

            print(f"🔧 {system.upper()}")
            for i, (backup, count) in enumerate(best_backups, 1):
                print(f"   {i}. {backup}")
                print(f"      {count} files")
            print()

    def find_relevant_backups(self):
        """Vind meest relevante backups met transform systems"""

        print("=" * 70)
        print("🎯 MOST RELEVANT BACKUPS")
        print("=" * 70)
        print()

        # Count total transform files per backup
        backup_counts: Dict[str, int] = {}
        backup_systems: Dict[str, Set[str]] = {}

        for tf in self.files_found:
            backup_counts[tf.backup] = backup_counts.get(tf.backup, 0) + 1

            if tf.backup not in backup_systems:
                backup_systems[tf.backup] = set()
            backup_systems[tf.backup].add(tf.system)

        # Sort by count
        sorted_backups = sorted(backup_counts.items(), key=lambda x: x[1], reverse=True)

        print("Top 10 backups with most transform system files:")
        print()

        for i, (backup, count) in enumerate(sorted_backups[:10], 1):
            systems = backup_systems[backup]
            systems_str = ", ".join(sorted(systems))

            print(f"{i:2d}. {backup}")
            print(f"    Files: {count}, Systems: {len(systems)}")
            print(f"    [{systems_str}]")
            print()

    def compare_with_repo(self):
        """Vergelijk met huidige repo"""

        print("=" * 70)
        print("🔄 COMPARE WITH CURRENT REPO")
        print("=" * 70)
        print()

        repo_src = self.repo_dir / "mandelbulber2" / "src"
        repo_opencl = self.repo_dir / "mandelbulber2" / "opencl"

        if not repo_src.exists():
            print("❌ Repo src directory not found!")
            return

        # Scan repo voor transform files
        repo_files = set()

        # Check src directory
        for ext in ['.cpp', '.h', '.hpp']:
            for keyword in ['cloner', 'deform', 'pivot', 'repeat', 'emission', 'spiral', 'wave']:
                pattern = f"*{keyword}*{ext}"
                repo_files.update(f.name for f in repo_src.glob(pattern))

        # Check opencl directory
        if repo_opencl.exists():
            for ext in ['.cl', '.hpp']:
                for keyword in ['cloner', 'deform', 'pivot', 'repeat', 'emission']:
                    pattern = f"*{keyword}*{ext}"
                    repo_files.update(f.name for f in repo_opencl.glob(pattern))

        print(f"📁 Current repo has: {len(repo_files)} transform-related files")
        print()

        if repo_files:
            print("Files found in repo:")
            for f in sorted(repo_files)[:20]:
                print(f"  ✓ {f}")
            if len(repo_files) > 20:
                print(f"  ... and {len(repo_files) - 20} more")
            print()

        # Compare with backups
        backup_files = set(f.name for f in self.files_found)

        only_in_backups = backup_files - repo_files
        only_in_repo = repo_files - backup_files
        in_both = repo_files & backup_files

        print(f"📊 COMPARISON:")
        print(f"  ✅ In both: {len(in_both)} files")
        print(f"  🆕 Only in backups: {len(only_in_backups)} files")
        print(f"  ⚠️  Only in repo: {len(only_in_repo)} files")
        print()

        if only_in_backups:
            print("🆕 NEW FILES IN BACKUPS (not in repo):")
            for name in sorted(only_in_backups)[:30]:
                # Find which system
                files = [f for f in self.files_found if f.name == name]
                if files:
                    system = files[0].system
                    print(f"  + {name} [{system}]")
            if len(only_in_backups) > 30:
                print(f"  ... and {len(only_in_backups) - 30} more")
            print()

    def identify_extraction_candidates(self):
        """Identificeer welke backups we moeten extracten"""

        print("=" * 70)
        print("📦 EXTRACTION CANDIDATES")
        print("=" * 70)
        print()

        # Zoek backups met specifieke keywords in naam
        candidates = []

        for backup in set(f.backup for f in self.files_found):
            score = 0
            reasons = []

            # Check backup name voor keywords
            backup_lower = backup.lower()

            if 'cloner' in backup_lower or 'repeat' in backup_lower:
                score += 100
                reasons.append("cloner/repeat in name")

            if 'deform' in backup_lower:
                score += 100
                reasons.append("deform in name")

            if 'pivot' in backup_lower or 'world' in backup_lower:
                score += 100
                reasons.append("pivot/world in name")

            if 'epic' in backup_lower:
                score += 50
                reasons.append("epic in name")

            if 'complete' in backup_lower or 'klaar' in backup_lower:
                score += 30
                reasons.append("completion marker")

            # Count transform files
            file_count = len([f for f in self.files_found if f.backup == backup])
            score += file_count

            if score > 50:
                candidates.append((score, backup, file_count, reasons))

        # Sort by score
        candidates.sort(reverse=True)

        print("🎯 TOP CANDIDATES FOR EXTRACTION:")
        print()

        for i, (score, backup, count, reasons) in enumerate(candidates[:10], 1):
            print(f"{i:2d}. {backup}")
            print(f"    Score: {score}, Files: {count}")
            print(f"    Reasons: {', '.join(reasons)}")
            print()

        return candidates


def main():
    """Main entry"""

    print()
    print("╔" + "═"*68 + "╗")
    print("║" + " "*15 + "TRANSFORM SYSTEM MAPPER v1.0" + " "*25 + "║")
    print("╚" + "═"*68 + "╝")
    print()

    backup_dir = Path.home() / "mandelbulber2_backups"
    repo_dir = Path.cwd()  # Current directory

    if not backup_dir.exists():
        print(f"❌ Backup directory not found: {backup_dir}")
        return

    mapper = TransformSystemMapper(backup_dir, repo_dir)

    # 1. Scan all backups
    mapper.scan_all_backups()

    # 2. Show overview by system
    mapper.show_overview_by_system()

    # 3. Show best backups per system
    mapper.show_best_backups()

    # 4. Find most relevant backups
    mapper.find_relevant_backups()

    # 5. Compare with repo
    mapper.compare_with_repo()

    # 6. Identify extraction candidates
    candidates = mapper.identify_extraction_candidates()

    print("=" * 70)
    print("✅ MAPPING COMPLETE!")
    print("=" * 70)
    print()

    if candidates:
        print(f"💡 NEXT STEP:")
        print(f"   Extract from top candidate: {candidates[0][1]}")
        print(f"   This backup contains {candidates[0][2]} transform system files")
        print()


if __name__ == "__main__":
    main()
