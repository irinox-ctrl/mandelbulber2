#!/usr/bin/env python3
"""
INTELLIGENT BACKUP ANALYZER
============================
Vergelijk EXACT wat in backups zit vs current repo!

Dit script:
1. Extracts key files uit meerdere backups
2. Vergelijkt met current repo
3. Toont CONCRETE verschillen (niet alleen file counts)
4. Maakt een detailed report van wat er ontbreekt

Author: Claude + Joeri
Date: 2026-04-19
"""

import tarfile
import difflib
from pathlib import Path
from typing import Dict, List, Tuple
from dataclasses import dataclass
import tempfile
import shutil


@dataclass
class FileDifference:
    """Verschil tussen backup en repo versie"""
    file_path: str
    backup_name: str
    lines_added: int
    lines_removed: int
    significant_changes: List[str]  # Descriptions van belangrijke changes


class IntelligentBackupAnalyzer:
    """Analyze exact differences between backups and repo"""

    # Key files om te checken
    KEY_FILES = [
        "src/compute_fractal.cpp",
        "src/compute_fractal.hpp",
        "src/initparameters.cpp",
        "src/common_params.hpp",
        "src/fractparams.cpp",
        "src/primitive.cpp",
        "src/pattern_line_traps.hpp",
        "opencl/common_params_cl.hpp",
        "opencl/engines/compute_fractal.cl",
        "opencl/engines/shader_pattern_line_traps.cl",
        "qt/dock_pattern_lines.ui",
    ]

    # Backups om te checken (nieuwste eerst)
    BACKUPS_TO_CHECK = [
        "Backup Mandelbulber met alle groepeen, deformers, cloner, OT , fractal textures.tar.gz",
        "mb_20260311_073620_voor_world_coord_6_10.tar.gz",
        "mb_20260307_194901_epic_repeat_klaar.tar.gz",
        "mandelbulber2_backup_20260307_091551_world_pivot_complete.tar.gz",
        "mb_20260309_105130_voor_emission_complete_fix.tar.gz"
    ]

    def __init__(self, repo_dir: Path, backup_dir: Path):
        self.repo_dir = repo_dir
        self.backup_dir = backup_dir
        self.temp_dir = Path(tempfile.mkdtemp(prefix="mb_analysis_"))
        self.differences: List[FileDifference] = []

    def analyze_all(self):
        """Run complete analysis"""

        print("=" * 70)
        print("🔍 INTELLIGENT BACKUP ANALYZER")
        print("=" * 70)
        print()

        print(f"📁 Repo: {self.repo_dir / 'mandelbulber2'}")
        print(f"💾 Backups: {self.backup_dir}")
        print(f"📊 Checking {len(self.KEY_FILES)} key files")
        print(f"📦 Against {len(self.BACKUPS_TO_CHECK)} backups")
        print()

        # Voor elk key file, vind de NIEUWSTE versie in backups
        for file_rel in self.KEY_FILES:
            print(f"Analyzing {file_rel}...")
            self._analyze_file(file_rel)

        print()
        print("✅ Analysis complete!")
        print()

        # Show results
        self._show_results()

        # Cleanup
        shutil.rmtree(self.temp_dir)

    def _analyze_file(self, file_rel: str):
        """Analyze single file across all backups"""

        current_file = self.repo_dir / "mandelbulber2" / file_rel

        if not current_file.exists():
            print(f"  ⚠️  Not in current repo, skipping")
            return

        # Read current version
        try:
            with open(current_file, 'r', encoding='utf-8', errors='ignore') as f:
                current_lines = f.readlines()
        except:
            print(f"  ❌ Cannot read current file")
            return

        # Check each backup
        best_diff = None
        best_backup = None
        max_additions = 0

        for backup_name in self.BACKUPS_TO_CHECK:
            backup_path = self.backup_dir / backup_name

            if not backup_path.exists():
                continue

            # Extract file from backup
            backup_lines = self._extract_file_from_backup(backup_path, file_rel)

            if not backup_lines:
                continue

            # Compare
            diff = list(difflib.unified_diff(
                current_lines,
                backup_lines,
                lineterm='',
                n=0  # No context lines
            ))

            if not diff:
                continue  # No differences

            # Count additions
            additions = sum(1 for line in diff if line.startswith('+') and not line.startswith('+++'))
            deletions = sum(1 for line in diff if line.startswith('-') and not line.startswith('---'))

            # If this backup has MORE additions than previous best, use it
            if additions > max_additions:
                max_additions = additions
                best_diff = diff
                best_backup = backup_name

        if best_diff and max_additions > 0:
            # Analyze significant changes
            significant = self._analyze_diff(best_diff)

            diff_obj = FileDifference(
                file_path=file_rel,
                backup_name=best_backup,
                lines_added=max_additions,
                lines_removed=sum(1 for line in best_diff if line.startswith('-') and not line.startswith('---')),
                significant_changes=significant
            )

            self.differences.append(diff_obj)
            print(f"  ✓ Found differences: +{max_additions} lines in {best_backup[:40]}...")
        else:
            print(f"  ✓ Up to date")

    def _extract_file_from_backup(self, backup_path: Path, file_rel: str) -> List[str]:
        """Extract and read file from backup"""

        try:
            with tarfile.open(backup_path, 'r:gz') as tar:
                for member in tar.getmembers():
                    if member.isdir():
                        continue

                    if member.name.endswith(file_rel):
                        # Extract
                        extracted = tar.extractfile(member)
                        if extracted:
                            content = extracted.read()
                            return content.decode('utf-8', errors='ignore').splitlines(keepends=True)

        except Exception as e:
            pass

        return []

    def _analyze_diff(self, diff: List[str]) -> List[str]:
        """Analyze diff voor significant changes"""

        significant = []
        added_lines = [line[1:] for line in diff if line.startswith('+') and not line.startswith('+++')]

        # Look for patterns
        patterns = {
            'orbit': ['orbit', 'trap', 'sample'],
            'multi': ['multi', 'center', 'weight'],
            'auto': ['auto', 'center', 'iteration'],
            'deform': ['deform', 'bend', 'twist', 'taper'],
            'repeat': ['repeat', 'mode', 'grid', 'brick'],
            'emission': ['emission', 'emitter'],
            'cloner': ['clone', 'cloner'],
            'pivot': ['pivot', 'world', 'coord']
        }

        for feature, keywords in patterns.items():
            count = 0
            for line in added_lines:
                line_lower = line.lower()
                if any(kw in line_lower for kw in keywords):
                    count += 1

            if count > 0:
                significant.append(f"{feature}: {count} related lines")

        # Check for new functions
        new_funcs = [line.strip() for line in added_lines if 'void ' in line or 'double ' in line or 'CVector' in line]
        if new_funcs:
            significant.append(f"New functions: {len(new_funcs)}")

        # Check for new struct members
        new_members = [line.strip() for line in added_lines if ('\t' in line or '  ' in line) and ';' in line and not '//' in line[:line.index(';')] if ';' in line]
        if new_members:
            significant.append(f"New struct members: {len(new_members)}")

        return significant if significant else ["General code changes"]

    def _show_results(self):
        """Show analysis results"""

        print("=" * 70)
        print("📊 ANALYSIS RESULTS")
        print("=" * 70)
        print()

        if not self.differences:
            print("✅ All files are up to date!")
            print("   Your repo matches the newest backups.")
            return

        print(f"Found differences in {len(self.differences)} files:")
        print()

        # Sort by most additions
        sorted_diffs = sorted(self.differences, key=lambda d: d.lines_added, reverse=True)

        for diff in sorted_diffs:
            print(f"📄 {diff.file_path}")
            print(f"   Source: {diff.backup_name[:60]}")
            print(f"   Changes: +{diff.lines_added} -{diff.lines_removed} lines")
            if diff.significant_changes:
                print(f"   Features:")
                for change in diff.significant_changes:
                    print(f"     • {change}")
            print()

        # Summary
        print("=" * 70)
        print("📈 SUMMARY")
        print("=" * 70)
        print()

        total_additions = sum(d.lines_added for d in self.differences)
        total_deletions = sum(d.lines_removed for d in self.differences)

        print(f"Total changes: +{total_additions} -{total_deletions} lines")
        print()

        # Group by feature
        all_features = {}
        for diff in self.differences:
            for change in diff.significant_changes:
                if ':' in change:
                    feature = change.split(':')[0]
                    all_features[feature] = all_features.get(feature, 0) + 1

        if all_features:
            print("Features found in backups:")
            for feature, count in sorted(all_features.items(), key=lambda x: x[1], reverse=True):
                print(f"  • {feature}: mentioned in {count} file(s)")
            print()

        # Recommendations
        print("=" * 70)
        print("💡 RECOMMENDATIONS")
        print("=" * 70)
        print()

        if total_additions > 200:
            print("🔴 MAJOR DIFFERENCES FOUND")
            print("   The backups contain significant new features.")
            print()

        print("Recommended actions:")
        print()

        for i, diff in enumerate(sorted_diffs[:3], 1):
            print(f"{i}. Extract {diff.file_path}")
            print(f"   From: {diff.backup_name[:55]}")
            print(f"   Adds: {', '.join(diff.significant_changes[:3])}")
            print()


def main():
    """Main entry"""

    print()
    print("╔" + "═"*68 + "╗")
    print("║" + " "*15 + "INTELLIGENT BACKUP ANALYZER v1.0" + " "*21 + "║")
    print("╚" + "═"*68 + "╝")
    print()

    repo_dir = Path.cwd()
    backup_dir = Path.home() / "mandelbulber2_backups"

    if not backup_dir.exists():
        print(f"❌ Backup directory not found: {backup_dir}")
        return

    analyzer = IntelligentBackupAnalyzer(repo_dir, backup_dir)
    analyzer.analyze_all()

    print("=" * 70)
    print("✅ ANALYSIS COMPLETE")
    print("=" * 70)
    print()
    print("Review the results above to decide what to extract.")
    print()


if __name__ == "__main__":
    main()
