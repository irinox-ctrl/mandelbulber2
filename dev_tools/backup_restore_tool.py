#!/usr/bin/env python3
"""
BACKUP RESTORE TOOL
===================
Tool om uit backups specifieke bestanden te halen en in repo te installeren.

Problem: Backups zijn er maar je kunt er niets uit halen.
Solution: Inspect, extract, diff, en selectief installeren!

Features:
- List backup contents (files + sizes)
- Extract specifieke bestanden/directories
- Diff tussen backup en current repo
- Selectief restore (alleen wat je wilt)
- Preview voor je install
- Batch operations

Author: Claude + Joeri
Version: 1.0
Date: 2026-04-19
"""

import os
import sys
import tarfile
import shutil
from pathlib import Path
from typing import List, Dict, Optional, Tuple
from dataclasses import dataclass
from datetime import datetime
import subprocess
import tempfile


@dataclass
class BackupInfo:
    """Backup file information"""
    path: Path
    name: str
    size_mb: float
    file_count: int
    created: str


@dataclass
class FileInfo:
    """File in backup"""
    path: str
    size: int
    is_dir: bool


class BackupRestoreTool:
    """
    Tool voor het inspecteren en restoren van backups
    """

    def __init__(self, base_dir: Path, repo_dir: Path):
        self.base_dir = base_dir
        self.repo_dir = repo_dir
        self.temp_dir = None

    def list_backups(self) -> List[BackupInfo]:
        """List all available backups"""
        backups = []

        for backup_file in self.base_dir.glob("**/*.tar.gz"):
            try:
                size_mb = backup_file.stat().st_size / (1024 * 1024)
                created = datetime.fromtimestamp(
                    backup_file.stat().st_mtime
                ).strftime("%Y-%m-%d %H:%M")

                # Count files in backup
                with tarfile.open(backup_file, 'r:gz') as tar:
                    file_count = len(tar.getmembers())

                backups.append(BackupInfo(
                    path=backup_file,
                    name=backup_file.name,
                    size_mb=size_mb,
                    file_count=file_count,
                    created=created
                ))
            except Exception as e:
                print(f"⚠️  Could not read {backup_file.name}: {e}")

        return sorted(backups, key=lambda b: b.created, reverse=True)

    def inspect_backup(self, backup_path: Path, filter_pattern: str = None) -> List[FileInfo]:
        """
        Inspect contents of backup

        Args:
            backup_path: Path to backup file
            filter_pattern: Only show files matching pattern (e.g., "*.cpp", "opencl/*")
        """
        files = []

        try:
            with tarfile.open(backup_path, 'r:gz') as tar:
                for member in tar.getmembers():
                    # Apply filter if provided
                    if filter_pattern:
                        if not self._matches_pattern(member.name, filter_pattern):
                            continue

                    files.append(FileInfo(
                        path=member.name,
                        size=member.size,
                        is_dir=member.isdir()
                    ))

        except Exception as e:
            print(f"❌ Error inspecting backup: {e}")
            return []

        return files

    def _matches_pattern(self, path: str, pattern: str) -> bool:
        """Check if path matches pattern"""
        import fnmatch

        # Simple patterns
        if '*' in pattern or '?' in pattern:
            return fnmatch.fnmatch(path, pattern) or fnmatch.fnmatch(Path(path).name, pattern)

        # Directory pattern
        if pattern.endswith('/'):
            return path.startswith(pattern) or pattern.rstrip('/') in path

        # Substring match
        return pattern in path

    def extract_files(
        self,
        backup_path: Path,
        file_patterns: List[str],
        output_dir: Optional[Path] = None
    ) -> Path:
        """
        Extract specific files from backup

        Args:
            backup_path: Backup file
            file_patterns: List of patterns to extract (e.g., ["*.cpp", "src/shader_*.cpp"])
            output_dir: Where to extract (default: temp directory)

        Returns:
            Path to extraction directory
        """
        if output_dir is None:
            output_dir = Path(tempfile.mkdtemp(prefix="backup_extract_"))
            self.temp_dir = output_dir

        print(f"📦 Extracting from: {backup_path.name}")
        print(f"📁 Output: {output_dir}")

        extracted_count = 0

        try:
            with tarfile.open(backup_path, 'r:gz') as tar:
                for member in tar.getmembers():
                    # Check if matches any pattern
                    if any(self._matches_pattern(member.name, pattern) for pattern in file_patterns):
                        print(f"  Extracting: {member.name}")
                        tar.extract(member, output_dir)
                        extracted_count += 1

        except Exception as e:
            print(f"❌ Extraction error: {e}")
            return None

        print(f"✅ Extracted {extracted_count} files")
        return output_dir

    def diff_files(self, backup_file: str, repo_file: str) -> Optional[str]:
        """
        Show diff between backup version and repo version

        Returns:
            Diff output or None if files identical/don't exist
        """
        backup_path = self.temp_dir / backup_file if self.temp_dir else None
        repo_path = self.repo_dir / repo_file

        if not backup_path or not backup_path.exists():
            return f"⚠️  Backup file not found: {backup_file}"

        if not repo_path.exists():
            return f"ℹ️  File doesn't exist in repo (new file): {repo_file}"

        try:
            result = subprocess.run(
                ['diff', '-u', str(repo_path), str(backup_path)],
                capture_output=True,
                text=True
            )

            if result.returncode == 0:
                return None  # Files identical

            return result.stdout

        except Exception as e:
            return f"❌ Diff error: {e}"

    def compare_with_repo(
        self,
        backup_path: Path,
        file_patterns: List[str]
    ) -> Dict[str, str]:
        """
        Compare backup files with current repo

        Returns:
            Dict of {file: status} where status is:
            - 'identical': Files are the same
            - 'modified': Files differ
            - 'new': File only in backup
            - 'missing': File only in repo
        """
        # Extract files to temp
        extract_dir = self.extract_files(backup_path, file_patterns)
        if not extract_dir:
            return {}

        comparisons = {}

        # Find all extracted files
        for backup_file in extract_dir.rglob('*'):
            if backup_file.is_dir():
                continue

            # Get relative path
            rel_path = backup_file.relative_to(extract_dir)

            # Corresponding repo file
            repo_file = self.repo_dir / rel_path

            if not repo_file.exists():
                comparisons[str(rel_path)] = 'new'
            elif self._files_identical(backup_file, repo_file):
                comparisons[str(rel_path)] = 'identical'
            else:
                comparisons[str(rel_path)] = 'modified'

        return comparisons

    def _files_identical(self, file1: Path, file2: Path) -> bool:
        """Check if two files are identical"""
        try:
            import filecmp
            return filecmp.cmp(file1, file2, shallow=False)
        except:
            return False

    def install_files(
        self,
        backup_path: Path,
        file_patterns: List[str],
        dry_run: bool = True,
        create_backup: bool = True
    ) -> Tuple[int, int]:
        """
        Install files from backup into repo

        Args:
            backup_path: Backup file
            file_patterns: Files to install
            dry_run: If True, only show what would be done
            create_backup: Create backup of overwritten files

        Returns:
            (installed_count, failed_count)
        """
        print(f"\n{'='*70}")
        print(f"{'DRY RUN - ' if dry_run else ''}INSTALLING FROM BACKUP")
        print(f"{'='*70}\n")

        # Extract to temp first
        extract_dir = self.extract_files(backup_path, file_patterns)
        if not extract_dir:
            return 0, 0

        installed = 0
        failed = 0

        # Create backup directory if needed
        backup_dir = None
        if create_backup and not dry_run:
            backup_dir = self.base_dir / f"backup_before_restore_{datetime.now().strftime('%Y%m%d_%H%M%S')}"
            backup_dir.mkdir(exist_ok=True)

        for source_file in extract_dir.rglob('*'):
            if source_file.is_dir():
                continue

            # Get relative path
            rel_path = source_file.relative_to(extract_dir)
            target_file = self.repo_dir / rel_path

            # Check if different
            if target_file.exists() and self._files_identical(source_file, target_file):
                print(f"⏭️  SKIP (identical): {rel_path}")
                continue

            status = "NEW" if not target_file.exists() else "OVERWRITE"

            if dry_run:
                print(f"📝 WOULD {status}: {rel_path}")
                installed += 1
            else:
                try:
                    # Backup existing file
                    if target_file.exists() and create_backup:
                        backup_file = backup_dir / rel_path
                        backup_file.parent.mkdir(parents=True, exist_ok=True)
                        shutil.copy2(target_file, backup_file)

                    # Copy new file
                    target_file.parent.mkdir(parents=True, exist_ok=True)
                    shutil.copy2(source_file, target_file)

                    print(f"✅ {status}: {rel_path}")
                    installed += 1

                except Exception as e:
                    print(f"❌ FAILED: {rel_path} - {e}")
                    failed += 1

        if not dry_run and backup_dir and installed > 0:
            print(f"\n💾 Original files backed up to: {backup_dir}")

        return installed, failed

    def cleanup(self):
        """Clean up temporary files"""
        if self.temp_dir and self.temp_dir.exists():
            shutil.rmtree(self.temp_dir)
            self.temp_dir = None


def interactive_menu(tool: BackupRestoreTool):
    """Interactive menu for backup restore"""
    print("╔" + "═"*68 + "╗")
    print("║" + " "*20 + "BACKUP RESTORE TOOL v1.0" + " "*24 + "║")
    print("╚" + "═"*68 + "╝\n")

    while True:
        print("\n" + "─"*70)
        print("MENU:")
        print("─"*70)
        print("1. List all backups")
        print("2. Inspect backup contents")
        print("3. Extract files from backup")
        print("4. Compare backup with repo")
        print("5. Install files from backup (dry-run)")
        print("6. Install files from backup (REAL)")
        print("7. Exit")
        print("─"*70)

        choice = input("\nChoice: ").strip()

        if choice == '1':
            list_backups_menu(tool)
        elif choice == '2':
            inspect_backup_menu(tool)
        elif choice == '3':
            extract_files_menu(tool)
        elif choice == '4':
            compare_menu(tool)
        elif choice == '5':
            install_menu(tool, dry_run=True)
        elif choice == '6':
            install_menu(tool, dry_run=False)
        elif choice == '7':
            print("\n👋 Bye!")
            break
        else:
            print("❌ Invalid choice")


def list_backups_menu(tool: BackupRestoreTool):
    """List backups menu"""
    print("\n" + "="*70)
    print("AVAILABLE BACKUPS")
    print("="*70 + "\n")

    backups = tool.list_backups()

    if not backups:
        print("⚠️  No backups found")
        return

    for i, backup in enumerate(backups, 1):
        print(f"[{i}] {backup.name}")
        print(f"    Size: {backup.size_mb:.1f} MB")
        print(f"    Files: {backup.file_count}")
        print(f"    Created: {backup.created}")
        print()


def inspect_backup_menu(tool: BackupRestoreTool):
    """Inspect backup menu"""
    backups = tool.list_backups()
    if not backups:
        print("⚠️  No backups found")
        return

    print("\nSelect backup:")
    for i, backup in enumerate(backups, 1):
        print(f"[{i}] {backup.name}")

    choice = input("\nBackup number: ").strip()
    try:
        idx = int(choice) - 1
        selected = backups[idx]
    except:
        print("❌ Invalid selection")
        return

    # Filter pattern
    pattern = input("\nFilter pattern (e.g., '*.cpp', 'opencl/*', or Enter for all): ").strip()
    pattern = pattern if pattern else None

    print(f"\n📦 Inspecting: {selected.name}\n")

    files = tool.inspect_backup(selected.path, pattern)

    if not files:
        print("⚠️  No files found")
        return

    # Group by directory
    dirs = {}
    for file in files:
        if file.is_dir:
            continue
        dir_name = str(Path(file.path).parent)
        if dir_name not in dirs:
            dirs[dir_name] = []
        dirs[dir_name].append(file)

    # Show organized
    for dir_name in sorted(dirs.keys()):
        print(f"\n📁 {dir_name}/")
        for file in sorted(dirs[dir_name], key=lambda f: f.path):
            size_kb = file.size / 1024
            print(f"   {Path(file.path).name:50} {size_kb:8.1f} KB")

    print(f"\n📊 Total: {len(files)} files")


def extract_files_menu(tool: BackupRestoreTool):
    """Extract files menu"""
    backups = tool.list_backups()
    if not backups:
        print("⚠️  No backups found")
        return

    print("\nSelect backup:")
    for i, backup in enumerate(backups, 1):
        print(f"[{i}] {backup.name}")

    choice = input("\nBackup number: ").strip()
    try:
        idx = int(choice) - 1
        selected = backups[idx]
    except:
        print("❌ Invalid selection")
        return

    # File patterns
    print("\nEnter file patterns to extract (one per line, empty line to finish):")
    print("Examples:")
    print("  *.cpp")
    print("  opencl/*.cl")
    print("  src/shader_*.cpp")
    print()

    patterns = []
    while True:
        pattern = input("Pattern: ").strip()
        if not pattern:
            break
        patterns.append(pattern)

    if not patterns:
        print("❌ No patterns specified")
        return

    # Extract
    output_dir = tool.extract_files(selected.path, patterns)
    if output_dir:
        print(f"\n✅ Files extracted to: {output_dir}")
        print(f"\n💡 Tip: You can now examine files before installing")


def compare_menu(tool: BackupRestoreTool):
    """Compare backup with repo"""
    backups = tool.list_backups()
    if not backups:
        print("⚠️  No backups found")
        return

    print("\nSelect backup:")
    for i, backup in enumerate(backups, 1):
        print(f"[{i}] {backup.name}")

    choice = input("\nBackup number: ").strip()
    try:
        idx = int(choice) - 1
        selected = backups[idx]
    except:
        print("❌ Invalid selection")
        return

    # Patterns
    print("\nEnter file patterns to compare:")
    patterns = []
    while True:
        pattern = input("Pattern (empty to finish): ").strip()
        if not pattern:
            break
        patterns.append(pattern)

    if not patterns:
        print("❌ No patterns specified")
        return

    print(f"\n🔍 Comparing backup with repo...\n")

    comparisons = tool.compare_with_repo(selected.path, patterns)

    # Group by status
    new_files = [f for f, s in comparisons.items() if s == 'new']
    modified_files = [f for f, s in comparisons.items() if s == 'modified']
    identical_files = [f for f, s in comparisons.items() if s == 'identical']

    print("="*70)
    print("COMPARISON RESULTS")
    print("="*70 + "\n")

    if new_files:
        print(f"🆕 NEW FILES ({len(new_files)}):")
        for f in sorted(new_files):
            print(f"   + {f}")
        print()

    if modified_files:
        print(f"✏️  MODIFIED FILES ({len(modified_files)}):")
        for f in sorted(modified_files):
            print(f"   ~ {f}")
        print()

    if identical_files:
        print(f"✅ IDENTICAL FILES ({len(identical_files)}):")
        for f in sorted(identical_files)[:10]:  # Show first 10
            print(f"   = {f}")
        if len(identical_files) > 10:
            print(f"   ... and {len(identical_files)-10} more")
        print()

    print(f"📊 Total: {len(comparisons)} files compared")


def install_menu(tool: BackupRestoreTool, dry_run: bool):
    """Install files menu"""
    backups = tool.list_backups()
    if not backups:
        print("⚠️  No backups found")
        return

    print("\nSelect backup:")
    for i, backup in enumerate(backups, 1):
        print(f"[{i}] {backup.name}")

    choice = input("\nBackup number: ").strip()
    try:
        idx = int(choice) - 1
        selected = backups[idx]
    except:
        print("❌ Invalid selection")
        return

    # Patterns
    print("\nEnter file patterns to install:")
    patterns = []
    while True:
        pattern = input("Pattern (empty to finish): ").strip()
        if not pattern:
            break
        patterns.append(pattern)

    if not patterns:
        print("❌ No patterns specified")
        return

    if not dry_run:
        print("\n⚠️  WARNING: This will OVERWRITE files in your repo!")
        print("Original files will be backed up.")
        confirm = input("Type 'YES' to continue: ").strip()
        if confirm != 'YES':
            print("❌ Cancelled")
            return

    # Install
    installed, failed = tool.install_files(
        selected.path,
        patterns,
        dry_run=dry_run,
        create_backup=True
    )

    print(f"\n{'='*70}")
    print("SUMMARY")
    print(f"{'='*70}\n")
    print(f"✅ Installed: {installed}")
    print(f"❌ Failed: {failed}")

    if dry_run:
        print(f"\n💡 This was a DRY RUN. Use option 6 to actually install.")


def main():
    """Main entry point"""
    base_dir = Path(__file__).parent.parent
    repo_dir = base_dir / "mandelbulber2"

    if not repo_dir.exists():
        print(f"❌ Mandelbulber directory not found: {repo_dir}")
        sys.exit(1)

    tool = BackupRestoreTool(base_dir, repo_dir)

    try:
        interactive_menu(tool)
    finally:
        tool.cleanup()


if __name__ == "__main__":
    main()
