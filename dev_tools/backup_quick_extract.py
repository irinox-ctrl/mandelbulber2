#!/usr/bin/env python3
"""
BACKUP QUICK EXTRACT TOOL
==========================
Snel specifieke zaken uit backups halen!

Problem: Veel backups, goede code erin, maar moeilijk eruit te krijgen.
Solution: Quick extract met presets voor veelgebruikte scenarios!

PRESETS:
1. Haal alle shader bestanden (shader_*.cpp/.h)
2. Haal alle OpenCL files (*.cl, *_cl.hpp)
3. Haal primitives (primitive_*.cpp/ui)
4. Haal all formulas (fractal_*.cpp)
5. Haal UI files (*.ui, dock_*.cpp)
6. Haal specifieke feature (custom pattern)
7. Vergelijk 2 backups (wat is verschillend?)
8. Extract full directory tree

Author: Claude + Joeri
Version: 2.0 - QUICK & EASY
Date: 2026-04-19
"""

import os
import sys
import tarfile
import shutil
from pathlib import Path
from typing import List, Dict, Set
from dataclasses import dataclass
import tempfile
from datetime import datetime
import difflib


@dataclass
class QuickPreset:
    """Quick extraction preset"""
    name: str
    description: str
    patterns: List[str]
    target_subdir: str  # Where to put extracted files


# PRESETS - Easy access!
QUICK_PRESETS = {
    '1': QuickPreset(
        name="Shaders",
        description="All shader files (fake lights, volumetric, etc.)",
        patterns=[
            "*/src/shader_*.cpp",
            "*/src/shader_*.h",
            "*/opencl/shader*.cl"
        ],
        target_subdir="extracted_shaders"
    ),
    '2': QuickPreset(
        name="OpenCL",
        description="All OpenCL kernel files",
        patterns=[
            "*/opencl/**/*.cl",
            "*/opencl/**/*_cl.hpp",
            "*/opencl/engines/*.cl",
            "*/src/opencl_*.cpp"
        ],
        target_subdir="extracted_opencl"
    ),
    '3': QuickPreset(
        name="Primitives",
        description="All primitive files (shapes, deformations)",
        patterns=[
            "*/formula/definition/primitive_*.cpp",
            "*/formula/ui/primitive_*.ui",
            "*/src/primitive*.cpp"
        ],
        target_subdir="extracted_primitives"
    ),
    '4': QuickPreset(
        name="Formulas",
        description="All fractal formula files",
        patterns=[
            "*/formula/definition/fractal_*.cpp",
            "*/formula/opencl/fractal_*.cl"
        ],
        target_subdir="extracted_formulas"
    ),
    '5': QuickPreset(
        name="UI Files",
        description="All UI files and dock widgets",
        patterns=[
            "*/qt/*.ui",
            "*/qt/dock_*.cpp",
            "*/qt/dock_*.h"
        ],
        target_subdir="extracted_ui"
    ),
    '6': QuickPreset(
        name="Orbit Traps",
        description="Orbit trap shape system",
        patterns=[
            "*/src/orbit_trap*.cpp",
            "*/src/orbit_trap*.h",
            "*/opencl/**/orbit_trap*.cl",
            "*/formula/definition/orbit_trap_*.cpp"
        ],
        target_subdir="extracted_orbit_traps"
    ),
    '7': QuickPreset(
        name="Repeat System",
        description="Epic repeat / cloner system",
        patterns=[
            "*/src/*repeat*.cpp",
            "*/src/*repeat*.h",
            "*/src/*cloner*.cpp",
            "*/opencl/**/*repeat*.cl",
            "*/qt/*repeat*.ui"
        ],
        target_subdir="extracted_repeat_system"
    ),
    '8': QuickPreset(
        name="Deformations",
        description="Deformation system files",
        patterns=[
            "*/src/*deform*.cpp",
            "*/src/*deform*.h",
            "*/opencl/**/*deform*.cl",
            "*/formula/definition/*deform*.cpp"
        ],
        target_subdir="extracted_deformations"
    )
}


class BackupQuickExtract:
    """Quick extraction from backups"""

    def __init__(self, backup_dir: Path, work_dir: Path):
        self.backup_dir = backup_dir
        self.work_dir = work_dir
        self.work_dir.mkdir(exist_ok=True)

    def list_backups(self, sort_by_date=True) -> List[Dict]:
        """List all backup files with metadata"""
        backups = []

        for backup_file in self.backup_dir.glob("*.tar.gz"):
            if backup_file.is_symlink():
                continue

            stat = backup_file.stat()
            backups.append({
                'path': backup_file,
                'name': backup_file.name,
                'size_mb': stat.st_size / (1024*1024),
                'modified': datetime.fromtimestamp(stat.st_mtime),
                'modified_str': datetime.fromtimestamp(stat.st_mtime).strftime("%Y-%m-%d %H:%M")
            })

        if sort_by_date:
            backups.sort(key=lambda x: x['modified'], reverse=True)

        return backups

    def extract_with_preset(
        self,
        backup_path: Path,
        preset: QuickPreset,
        output_base: Path = None
    ) -> Path:
        """Extract files using preset patterns"""

        if output_base is None:
            output_base = self.work_dir

        output_dir = output_base / preset.target_subdir
        output_dir.mkdir(parents=True, exist_ok=True)

        print(f"\n{'='*70}")
        print(f"📦 EXTRACTING: {preset.name}")
        print(f"{'='*70}")
        print(f"Backup: {backup_path.name}")
        print(f"Output: {output_dir}")
        print(f"Patterns: {len(preset.patterns)}")
        print()

        extracted_count = 0
        extracted_files = []

        try:
            with tarfile.open(backup_path, 'r:gz') as tar:
                members = tar.getmembers()

                for member in members:
                    if member.isdir():
                        continue

                    # Check against all patterns
                    matched = False
                    for pattern in preset.patterns:
                        if self._matches_glob(member.name, pattern):
                            matched = True
                            break

                    if matched:
                        # Extract preserving directory structure
                        tar.extract(member, output_dir)
                        extracted_count += 1
                        extracted_files.append(member.name)
                        print(f"  ✅ {member.name}")

        except Exception as e:
            print(f"❌ Error: {e}")
            return None

        print(f"\n✅ Extracted {extracted_count} files to: {output_dir}")

        # Create file list
        list_file = output_dir / "_extracted_files.txt"
        with open(list_file, 'w') as f:
            f.write(f"Extracted from: {backup_path.name}\n")
            f.write(f"Preset: {preset.name}\n")
            f.write(f"Date: {datetime.now()}\n")
            f.write(f"Files: {extracted_count}\n")
            f.write("\n" + "="*70 + "\n\n")
            for fname in sorted(extracted_files):
                f.write(f"{fname}\n")

        return output_dir

    def _matches_glob(self, path: str, pattern: str) -> bool:
        """Match path against glob pattern"""
        from fnmatch import fnmatch

        # Direct match
        if fnmatch(path, pattern):
            return True

        # Match filename only
        if fnmatch(Path(path).name, Path(pattern).name):
            # Check parent path matches
            pattern_parts = Path(pattern).parts
            path_parts = Path(path).parts

            # ** means any directory depth
            if '**' in pattern_parts:
                idx = pattern_parts.index('**')
                # Check parts before **
                if idx > 0:
                    before = pattern_parts[:idx]
                    if not all(b in path_parts for b in before):
                        return False
                # Check parts after **
                if idx < len(pattern_parts) - 1:
                    after = pattern_parts[idx+1:]
                    # Last part is filename, already matched
                    if len(after) > 1:
                        # Check intermediate dirs
                        pass
                return True

            # Normal path matching
            if len(pattern_parts) <= len(path_parts):
                # Check if ends match
                return all(
                    fnmatch(p, pat) or pat == '*'
                    for p, pat in zip(
                        path_parts[-len(pattern_parts):],
                        pattern_parts
                    )
                )

        return False

    def compare_backups(
        self,
        backup1: Path,
        backup2: Path,
        pattern: str = "*.cpp"
    ) -> Dict:
        """Compare two backups - what's different?"""

        print(f"\n{'='*70}")
        print(f"🔍 COMPARING BACKUPS")
        print(f"{'='*70}")
        print(f"Backup 1: {backup1.name}")
        print(f"Backup 2: {backup2.name}")
        print(f"Pattern: {pattern}")
        print()

        # Get file lists from both
        files1 = self._list_files_in_backup(backup1, pattern)
        files2 = self._list_files_in_backup(backup2, pattern)

        # Compare
        only_in_1 = files1 - files2
        only_in_2 = files2 - files1
        in_both = files1 & files2

        print(f"📊 RESULTS:")
        print(f"  Only in {backup1.name}: {len(only_in_1)} files")
        print(f"  Only in {backup2.name}: {len(only_in_2)} files")
        print(f"  In both: {len(in_both)} files")
        print()

        if only_in_1:
            print(f"\n🆕 ONLY IN {backup1.name}:")
            for f in sorted(only_in_1)[:20]:
                print(f"  + {f}")
            if len(only_in_1) > 20:
                print(f"  ... and {len(only_in_1)-20} more")

        if only_in_2:
            print(f"\n🆕 ONLY IN {backup2.name}:")
            for f in sorted(only_in_2)[:20]:
                print(f"  + {f}")
            if len(only_in_2) > 20:
                print(f"  ... and {len(only_in_2)-20} more")

        return {
            'only_in_1': only_in_1,
            'only_in_2': only_in_2,
            'in_both': in_both
        }

    def _list_files_in_backup(self, backup_path: Path, pattern: str) -> Set[str]:
        """Get list of files matching pattern in backup"""
        files = set()

        try:
            with tarfile.open(backup_path, 'r:gz') as tar:
                for member in tar.getmembers():
                    if member.isdir():
                        continue
                    if self._matches_glob(member.name, pattern):
                        # Use relative path from mandelbulber2/
                        if 'mandelbulber2/' in member.name:
                            rel = member.name.split('mandelbulber2/', 1)[1]
                            files.add(rel)
                        else:
                            files.add(member.name)
        except Exception as e:
            print(f"⚠️  Error reading {backup_path.name}: {e}")

        return files

    def smart_search(self, backup_path: Path, keyword: str) -> List[str]:
        """Search for files containing keyword"""
        print(f"\n🔍 Searching for: '{keyword}' in {backup_path.name}")

        matches = []

        try:
            with tarfile.open(backup_path, 'r:gz') as tar:
                for member in tar.getmembers():
                    if member.isdir():
                        continue

                    # Check filename
                    if keyword.lower() in member.name.lower():
                        matches.append(member.name)

        except Exception as e:
            print(f"❌ Error: {e}")

        return matches

    def install_to_repo(
        self,
        extracted_dir: Path,
        repo_dir: Path,
        dry_run: bool = True
    ) -> int:
        """Install extracted files to repo"""

        print(f"\n{'='*70}")
        print(f"{'[DRY RUN] ' if dry_run else ''}INSTALLING TO REPO")
        print(f"{'='*70}")
        print(f"Source: {extracted_dir}")
        print(f"Target: {repo_dir}")
        print()

        installed = 0

        # Find all files in extracted dir
        for source_file in extracted_dir.rglob('*'):
            if source_file.is_dir():
                continue

            if source_file.name.startswith('_'):
                continue  # Skip metadata files

            # Get path relative to extracted dir
            rel_parts = source_file.relative_to(extracted_dir).parts

            # Skip first part if it's 'mandelbulber2'
            if rel_parts[0] == 'mandelbulber2':
                rel_parts = rel_parts[1:]

            target_file = repo_dir / Path(*rel_parts)

            if dry_run:
                status = "NEW" if not target_file.exists() else "OVERWRITE"
                print(f"  📝 WOULD {status}: {'/'.join(rel_parts)}")
                installed += 1
            else:
                try:
                    target_file.parent.mkdir(parents=True, exist_ok=True)
                    shutil.copy2(source_file, target_file)
                    status = "NEW" if not target_file.exists() else "UPDATED"
                    print(f"  ✅ {status}: {'/'.join(rel_parts)}")
                    installed += 1
                except Exception as e:
                    print(f"  ❌ FAILED: {'/'.join(rel_parts)} - {e}")

        print(f"\n{'Would install' if dry_run else 'Installed'}: {installed} files")
        return installed


def interactive_quick_menu():
    """Quick interactive menu"""

    backup_dir = Path.home() / "mandelbulber2_backups"
    if not backup_dir.exists():
        backup_dir = Path(__file__).parent.parent
        print(f"⚠️  Using backup dir: {backup_dir}")

    work_dir = Path(__file__).parent / "extracted_from_backups"
    repo_dir = Path(__file__).parent.parent / "mandelbulber2"

    tool = BackupQuickExtract(backup_dir, work_dir)

    print("╔" + "═"*68 + "╗")
    print("║" + " "*18 + "BACKUP QUICK EXTRACT v2.0" + " "*25 + "║")
    print("╚" + "═"*68 + "╝\n")

    while True:
        print("\n" + "─"*70)
        print("QUICK PRESETS:")
        print("─"*70)
        for key, preset in QUICK_PRESETS.items():
            print(f"{key}. {preset.name:20} - {preset.description}")

        print("\n" + "─"*70)
        print("OTHER OPTIONS:")
        print("─"*70)
        print("l. List all backups")
        print("c. Compare two backups")
        print("s. Search for keyword")
        print("i. Install extracted files to repo")
        print("q. Quit")
        print("─"*70)

        choice = input("\nChoice: ").strip().lower()

        if choice == 'q':
            print("\n👋 Done!")
            break

        elif choice == 'l':
            list_backups_quick(tool)

        elif choice == 'c':
            compare_backups_quick(tool)

        elif choice == 's':
            search_keyword_quick(tool)

        elif choice == 'i':
            install_quick(tool, repo_dir)

        elif choice in QUICK_PRESETS:
            extract_with_preset_quick(tool, QUICK_PRESETS[choice])

        else:
            print("❌ Invalid choice")


def list_backups_quick(tool: BackupQuickExtract):
    """Quick list backups"""
    print(f"\n{'='*70}")
    print("AVAILABLE BACKUPS (sorted by date)")
    print(f"{'='*70}\n")

    backups = tool.list_backups()

    for i, backup in enumerate(backups[:15], 1):  # Show first 15
        size_str = f"{backup['size_mb']:.1f}MB" if backup['size_mb'] < 1000 else f"{backup['size_mb']/1024:.2f}GB"
        print(f"[{i:2}] {backup['modified_str']}  {size_str:>10}  {backup['name']}")

    if len(backups) > 15:
        print(f"\n... and {len(backups)-15} more backups")

    print(f"\n📊 Total: {len(backups)} backups")


def extract_with_preset_quick(tool: BackupQuickExtract, preset: QuickPreset):
    """Quick extract with preset"""
    backups = tool.list_backups()

    print(f"\n📦 PRESET: {preset.name}")
    print(f"Description: {preset.description}")
    print(f"\nSelect backup (showing last 10):\n")

    for i, backup in enumerate(backups[:10], 1):
        print(f"[{i}] {backup['modified_str']}  {backup['name'][:60]}")

    choice = input("\nBackup number (or 'all' for most recent): ").strip()

    if choice.lower() == 'all' or choice == '1':
        selected = backups[0]
    else:
        try:
            idx = int(choice) - 1
            selected = backups[idx]
        except:
            print("❌ Invalid selection")
            return

    # Extract!
    output_dir = tool.extract_with_preset(selected['path'], preset)

    if output_dir:
        print(f"\n🎉 SUCCESS!")
        print(f"Files extracted to: {output_dir}")
        print(f"\n💡 Next: Use option 'i' to install to repo")


def compare_backups_quick(tool: BackupQuickExtract):
    """Quick compare backups"""
    backups = tool.list_backups()

    print("\nSelect FIRST backup:")
    for i, backup in enumerate(backups[:10], 1):
        print(f"[{i}] {backup['modified_str']}  {backup['name'][:50]}")

    choice1 = input("\nFirst backup: ").strip()
    try:
        backup1 = backups[int(choice1)-1]
    except:
        print("❌ Invalid")
        return

    print("\nSelect SECOND backup:")
    for i, backup in enumerate(backups[:10], 1):
        print(f"[{i}] {backup['modified_str']}  {backup['name'][:50]}")

    choice2 = input("\nSecond backup: ").strip()
    try:
        backup2 = backups[int(choice2)-1]
    except:
        print("❌ Invalid")
        return

    pattern = input("\nPattern (default: *.cpp): ").strip() or "*.cpp"

    tool.compare_backups(backup1['path'], backup2['path'], pattern)


def search_keyword_quick(tool: BackupQuickExtract):
    """Quick search"""
    backups = tool.list_backups()

    print("\nSelect backup:")
    for i, backup in enumerate(backups[:10], 1):
        print(f"[{i}] {backup['name'][:60]}")

    choice = input("\nBackup: ").strip()
    try:
        selected = backups[int(choice)-1]
    except:
        print("❌ Invalid")
        return

    keyword = input("Search keyword (e.g., 'fake_lights', 'orbit_trap'): ").strip()

    matches = tool.smart_search(selected['path'], keyword)

    print(f"\n🔍 Found {len(matches)} matches:")
    for match in sorted(matches)[:30]:
        print(f"  {match}")

    if len(matches) > 30:
        print(f"  ... and {len(matches)-30} more")


def install_quick(tool: BackupQuickExtract, repo_dir: Path):
    """Quick install"""
    extracted_dirs = list(tool.work_dir.glob("extracted_*"))

    if not extracted_dirs:
        print("\n⚠️  No extracted directories found!")
        print("First extract files using presets (1-8)")
        return

    print("\nAvailable extracted directories:")
    for i, edir in enumerate(extracted_dirs, 1):
        file_count = len(list(edir.rglob('*.cpp'))) + len(list(edir.rglob('*.h')))
        print(f"[{i}] {edir.name}  ({file_count} files)")

    choice = input("\nDirectory to install: ").strip()
    try:
        selected = extracted_dirs[int(choice)-1]
    except:
        print("❌ Invalid")
        return

    print(f"\n⚠️  This will copy files to: {repo_dir}")
    print("First showing what would be installed (dry run)...")

    # Dry run first
    count = tool.install_to_repo(selected, repo_dir, dry_run=True)

    if count == 0:
        print("⚠️  No files to install")
        return

    confirm = input(f"\nInstall {count} files for REAL? (yes/no): ").strip().lower()

    if confirm == 'yes':
        tool.install_to_repo(selected, repo_dir, dry_run=False)
        print(f"\n🎉 Installed {count} files!")
        print(f"\n💡 Next: Rebuild Mandelbulber")
        print(f"cd {repo_dir.parent}/mandelbulber2/qmake && qmake && make")
    else:
        print("❌ Cancelled")


if __name__ == "__main__":
    interactive_quick_menu()
