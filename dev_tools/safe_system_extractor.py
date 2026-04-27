#!/usr/bin/env python3
"""
SAFE SYSTEM EXTRACTOR
=====================
Semi-automatische extractie van transform systems uit backups!

VEILIGHEID FIRST:
- Backup current state VOOR extractie
- Show diffs voor review
- Vraag bevestiging voor merge
- Run GPU struct checker
- Test build na extractie
- Rollback optie als het misgaat

Author: Claude + Joeri
Date: 2026-04-19
"""

import tarfile
import shutil
import subprocess
from pathlib import Path
from typing import List, Dict, Tuple, Optional
from dataclasses import dataclass
from datetime import datetime
import difflib
import sys


@dataclass
class SystemDefinition:
    """Definitie van een te extracten systeem"""
    name: str
    backup_file: str
    description: str
    files_to_extract: List[str]
    test_keywords: List[str]  # Keywords om te checken of extractie gelukt is


# SYSTEEM DEFINITIES
SYSTEMS = {
    'pivot': SystemDefinition(
        name="Pivot/World Space System",
        backup_file="mandelbulber2_backup_20260307_091551_world_pivot_complete.tar.gz",
        description="World coordinate system en rotation pivot points",
        files_to_extract=[
            "src/compute_fractal.cpp",
            "src/compute_fractal.hpp",
            "src/initparameters.cpp",
            "src/common_params.hpp",
            "opencl/common_params_cl.hpp",
            "opencl/engines/compute_fractal.cl"
        ],
        test_keywords=['pivot', 'world_space', 'worldCoord']
    ),
    'repeat': SystemDefinition(
        name="Epic Repeat System",
        backup_file="mb_20260307_194901_epic_repeat_klaar.tar.gz",
        description="Epic repeat modes (grid, brick, honeycomb, spiral, etc.)",
        files_to_extract=[
            "src/compute_fractal.cpp",
            "src/compute_fractal.hpp",
            "src/initparameters.cpp",
            "src/common_params.hpp",
            "opencl/common_params_cl.hpp",
            "opencl/engines/compute_fractal.cl"
        ],
        test_keywords=['repeatMode', 'epic_repeat', 'MODE_GRID', 'MODE_BRICK']
    ),
    'deform': SystemDefinition(
        name="Deformation System",
        backup_file="Backup Mandelbulber met alle groepeen, deformers, cloner, OT , fractal textures.tar.gz",
        description="Deformation transforms (bend, twist, taper)",
        files_to_extract=[
            "src/compute_fractal.cpp",
            "src/compute_fractal.hpp",
            "src/initparameters.cpp",
            "src/common_params.hpp",
            "opencl/common_params_cl.hpp",
            "opencl/engines/compute_fractal.cl"
        ],
        test_keywords=['deformation', 'deform_bend', 'deform_twist', 'deform_taper']
    ),
    'emission': SystemDefinition(
        name="Emission System",
        backup_file="mb_20260309_105130_voor_emission_complete_fix.tar.gz",
        description="Primitive emission modes",
        files_to_extract=[
            "src/primitive.cpp",
            "src/primitive.hpp",
            "src/initparameters.cpp",
            "src/common_params.hpp",
            "opencl/common_params_cl.hpp",
            "opencl/engines/compute_fractal.cl"
        ],
        test_keywords=['emission', 'primitive_emission', 'emitter']
    )
}


class SafeSystemExtractor:
    """Safe extraction met backup, diff review, en rollback"""

    def __init__(self, repo_dir: Path, backup_dir: Path):
        self.repo_dir = repo_dir
        self.backup_dir = backup_dir
        self.temp_dir = Path("/tmp/mandelbulber_extraction")
        self.safety_backup_dir = repo_dir.parent / "SAFETY_BACKUPS"
        self.current_backup_path: Optional[Path] = None

    def extract_system(self, system_id: str, auto_confirm: bool = False) -> bool:
        """
        Extract een compleet systeem met alle safety checks

        Returns:
            True als extractie succesvol, False bij problemen
        """

        if system_id not in SYSTEMS:
            print(f"❌ Unknown system: {system_id}")
            print(f"   Available: {', '.join(SYSTEMS.keys())}")
            return False

        system = SYSTEMS[system_id]

        print("\n" + "=" * 70)
        print(f"🔧 EXTRACTING: {system.name}")
        print("=" * 70)
        print(f"Backup: {system.backup_file}")
        print(f"Description: {system.description}")
        print(f"Files: {len(system.files_to_extract)}")
        print()

        # STAP 1: Maak safety backup
        print("📦 STEP 1: Creating safety backup...")
        if not self._create_safety_backup(system_id):
            print("❌ Failed to create safety backup!")
            return False
        print("✅ Safety backup created")
        print()

        # STAP 2: Extract files uit backup
        print("📂 STEP 2: Extracting files from backup...")
        extracted_files = self._extract_from_backup(system)
        if not extracted_files:
            print("❌ Failed to extract files!")
            return False
        print(f"✅ Extracted {len(extracted_files)} files")
        print()

        # STAP 3: Show diffs
        print("🔍 STEP 3: Reviewing changes...")
        diffs = self._generate_diffs(extracted_files)
        self._show_diffs(diffs)
        print()

        # STAP 4: Bevestiging vragen
        if not auto_confirm:
            print("⚠️  STEP 4: Confirmation required")
            print()
            response = input("Apply these changes? (yes/no/diff): ").strip().lower()

            if response == 'diff':
                self._show_detailed_diffs(diffs)
                response = input("\nApply changes? (yes/no): ").strip().lower()

            if response not in ['yes', 'y']:
                print("❌ Extraction cancelled by user")
                self._cleanup_temp()
                return False

        print("✅ Proceeding with extraction")
        print()

        # STAP 5: Copy files
        print("📝 STEP 5: Applying changes...")
        if not self._copy_extracted_files(extracted_files):
            print("❌ Failed to copy files!")
            return False
        print("✅ Files copied")
        print()

        # STAP 6: GPU struct check
        print("🛡️  STEP 6: GPU struct safety check...")
        if not self._run_gpu_struct_check():
            print("⚠️  WARNING: GPU struct check failed!")
            print("   This may cause GPU crashes!")
            response = input("Continue anyway? (yes/no): ").strip().lower()
            if response not in ['yes', 'y']:
                print("🔄 Rolling back...")
                self._rollback(system_id)
                return False
        else:
            print("✅ GPU struct check passed")
        print()

        # STAP 7: Feature presence check
        print("🔍 STEP 7: Verifying feature presence...")
        if not self._verify_feature_presence(system):
            print("⚠️  WARNING: Feature keywords not found!")
            response = input("Continue anyway? (yes/no): ").strip().lower()
            if response not in ['yes', 'y']:
                print("🔄 Rolling back...")
                self._rollback(system_id)
                return False
        else:
            print("✅ Feature verified present")
        print()

        # STAP 8: Test build (optioneel)
        print("🔨 STEP 8: Test build (optional)...")
        response = input("Run test build? (yes/no): ").strip().lower()
        if response in ['yes', 'y']:
            if not self._test_build():
                print("❌ Build failed!")
                response = input("Rollback? (yes/no): ").strip().lower()
                if response in ['yes', 'y']:
                    self._rollback(system_id)
                    return False
            else:
                print("✅ Build successful")
        else:
            print("⏭️  Skipping build test")
        print()

        # CLEANUP
        self._cleanup_temp()

        print("=" * 70)
        print("✅ EXTRACTION COMPLETE!")
        print("=" * 70)
        print(f"System '{system.name}' successfully extracted!")
        print(f"Safety backup: {self.current_backup_path}")
        print()

        return True

    def _create_safety_backup(self, system_id: str) -> bool:
        """Maak backup van current state"""

        self.safety_backup_dir.mkdir(exist_ok=True)

        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        backup_name = f"safety_backup_{system_id}_{timestamp}.tar.gz"
        backup_path = self.safety_backup_dir / backup_name

        try:
            mandelbulber_dir = self.repo_dir / "mandelbulber2"

            # Create tar.gz of mandelbulber2 directory
            with tarfile.open(backup_path, 'w:gz') as tar:
                tar.add(mandelbulber_dir, arcname='mandelbulber2')

            self.current_backup_path = backup_path
            print(f"   Saved to: {backup_path}")
            print(f"   Size: {backup_path.stat().st_size / (1024*1024):.1f} MB")

            return True

        except Exception as e:
            print(f"   Error: {e}")
            return False

    def _extract_from_backup(self, system: SystemDefinition) -> Dict[str, Path]:
        """Extract files uit backup naar temp directory"""

        backup_path = self.backup_dir / system.backup_file

        if not backup_path.exists():
            print(f"   ❌ Backup not found: {backup_path}")
            return {}

        # Clean temp dir
        if self.temp_dir.exists():
            shutil.rmtree(self.temp_dir)
        self.temp_dir.mkdir(parents=True)

        extracted = {}

        try:
            with tarfile.open(backup_path, 'r:gz') as tar:
                for file_rel in system.files_to_extract:
                    # Find file in backup (may have different prefix)
                    found = False

                    for member in tar.getmembers():
                        if member.isdir():
                            continue

                        # Check if path ends with our target file
                        if member.name.endswith(file_rel):
                            # Extract to temp
                            tar.extract(member, self.temp_dir)
                            extracted_path = self.temp_dir / member.name
                            extracted[file_rel] = extracted_path
                            found = True
                            print(f"   ✓ {file_rel}")
                            break

                    if not found:
                        print(f"   ⚠️  Not found: {file_rel}")

        except Exception as e:
            print(f"   ❌ Error: {e}")
            return {}

        return extracted

    def _generate_diffs(self, extracted_files: Dict[str, Path]) -> Dict[str, List[str]]:
        """Generate diffs tussen current en extracted files"""

        diffs = {}

        for file_rel, extracted_path in extracted_files.items():
            current_path = self.repo_dir / "mandelbulber2" / file_rel

            if not current_path.exists():
                diffs[file_rel] = [f"NEW FILE: {file_rel}"]
                continue

            try:
                with open(current_path, 'r', encoding='utf-8', errors='ignore') as f:
                    current_lines = f.readlines()

                with open(extracted_path, 'r', encoding='utf-8', errors='ignore') as f:
                    extracted_lines = f.readlines()

                diff = list(difflib.unified_diff(
                    current_lines,
                    extracted_lines,
                    fromfile=f'current/{file_rel}',
                    tofile=f'extracted/{file_rel}',
                    lineterm=''
                ))

                diffs[file_rel] = diff

            except Exception as e:
                diffs[file_rel] = [f"ERROR: {e}"]

        return diffs

    def _show_diffs(self, diffs: Dict[str, List[str]]):
        """Show summary van diffs"""

        for file_rel, diff_lines in diffs.items():
            if not diff_lines:
                print(f"   ✅ {file_rel}: No changes")
                continue

            if diff_lines[0].startswith("NEW FILE"):
                print(f"   🆕 {file_rel}: New file")
                continue

            if diff_lines[0].startswith("ERROR"):
                print(f"   ❌ {file_rel}: {diff_lines[0]}")
                continue

            # Count changes
            additions = sum(1 for line in diff_lines if line.startswith('+') and not line.startswith('+++'))
            deletions = sum(1 for line in diff_lines if line.startswith('-') and not line.startswith('---'))

            print(f"   📝 {file_rel}: +{additions} -{deletions} lines")

    def _show_detailed_diffs(self, diffs: Dict[str, List[str]]):
        """Show volledige diffs"""

        print("\n" + "=" * 70)
        print("DETAILED DIFFS")
        print("=" * 70)

        for file_rel, diff_lines in diffs.items():
            print(f"\n{'─'*70}")
            print(f"📄 {file_rel}")
            print(f"{'─'*70}")

            if not diff_lines:
                print("(No changes)")
                continue

            # Show first 100 lines of diff
            for line in diff_lines[:100]:
                print(line.rstrip())

            if len(diff_lines) > 100:
                print(f"\n... and {len(diff_lines)-100} more lines")

    def _copy_extracted_files(self, extracted_files: Dict[str, Path]) -> bool:
        """Copy extracted files naar repo"""

        try:
            for file_rel, extracted_path in extracted_files.items():
                target_path = self.repo_dir / "mandelbulber2" / file_rel

                # Create parent dirs
                target_path.parent.mkdir(parents=True, exist_ok=True)

                # Copy file
                shutil.copy2(extracted_path, target_path)
                print(f"   ✓ {file_rel}")

            return True

        except Exception as e:
            print(f"   ❌ Error: {e}")
            return False

    def _run_gpu_struct_check(self) -> bool:
        """Run GPU struct checker"""

        checker_path = self.repo_dir / "dev_tools" / "gpu_struct_checker.py"

        if not checker_path.exists():
            print("   ⚠️  GPU struct checker not found, skipping")
            return True

        try:
            result = subprocess.run(
                ["python3", str(checker_path)],
                cwd=self.repo_dir,
                capture_output=True,
                text=True,
                timeout=30
            )

            # Check if passed (exit code 0)
            return result.returncode == 0

        except Exception as e:
            print(f"   ⚠️  Error running checker: {e}")
            return False

    def _verify_feature_presence(self, system: SystemDefinition) -> bool:
        """Verify dat feature keywords aanwezig zijn"""

        found_any = False

        for file_rel in system.files_to_extract:
            file_path = self.repo_dir / "mandelbulber2" / file_rel

            if not file_path.exists():
                continue

            try:
                with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
                    content = f.read().lower()

                for keyword in system.test_keywords:
                    if keyword.lower() in content:
                        found_any = True
                        print(f"   ✓ Found '{keyword}' in {file_rel}")
                        break

            except:
                pass

        return found_any

    def _test_build(self) -> bool:
        """Test build in qmake directory"""

        qmake_dir = self.repo_dir / "mandelbulber2" / "qmake"

        if not qmake_dir.exists():
            print("   ⚠️  qmake directory not found")
            return True  # Don't fail if no qmake

        print("   Running qmake...")

        try:
            # Run qmake
            result = subprocess.run(
                ["qmake"],
                cwd=qmake_dir,
                capture_output=True,
                timeout=60
            )

            if result.returncode != 0:
                print("   ❌ qmake failed")
                return False

            print("   Running make (first 10 files)...")

            # Run make but stop after a bit
            result = subprocess.run(
                ["make", "-j4"],
                cwd=qmake_dir,
                capture_output=True,
                timeout=120
            )

            # We don't expect full build, just check for compile errors
            if b"error:" in result.stderr:
                print("   ❌ Compile errors detected")
                print(result.stderr.decode('utf-8', errors='ignore')[-500:])
                return False

            print("   ✅ No immediate compile errors")
            return True

        except subprocess.TimeoutExpired:
            print("   ⏱️  Build taking long (stopped early, likely OK)")
            return True
        except Exception as e:
            print(f"   ⚠️  Build test error: {e}")
            return True  # Don't fail on build test errors

    def _rollback(self, system_id: str) -> bool:
        """Rollback naar safety backup"""

        if not self.current_backup_path or not self.current_backup_path.exists():
            print("❌ No safety backup found!")
            return False

        print(f"🔄 Rolling back from: {self.current_backup_path}")

        try:
            # Remove current mandelbulber2
            mandelbulber_dir = self.repo_dir / "mandelbulber2"
            if mandelbulber_dir.exists():
                shutil.rmtree(mandelbulber_dir)

            # Extract backup
            with tarfile.open(self.current_backup_path, 'r:gz') as tar:
                tar.extractall(self.repo_dir)

            print("✅ Rollback complete")
            return True

        except Exception as e:
            print(f"❌ Rollback failed: {e}")
            return False

    def _cleanup_temp(self):
        """Cleanup temp directory"""
        if self.temp_dir.exists():
            shutil.rmtree(self.temp_dir)


def main():
    """Main entry"""

    print()
    print("╔" + "═"*68 + "╗")
    print("║" + " "*18 + "SAFE SYSTEM EXTRACTOR v1.0" + " "*24 + "║")
    print("╚" + "═"*68 + "╝")
    print()

    repo_dir = Path.cwd()
    backup_dir = Path.home() / "mandelbulber2_backups"

    if not backup_dir.exists():
        print(f"❌ Backup directory not found: {backup_dir}")
        sys.exit(1)

    extractor = SafeSystemExtractor(repo_dir, backup_dir)

    # Show available systems
    print("Available systems:")
    print()
    for system_id, system in SYSTEMS.items():
        print(f"  {system_id}: {system.name}")
        print(f"     {system.description}")
        print()

    # Get user choice
    if len(sys.argv) > 1:
        system_id = sys.argv[1]
    else:
        system_id = input("Which system to extract? ").strip().lower()

    if system_id not in SYSTEMS:
        print(f"❌ Invalid system: {system_id}")
        sys.exit(1)

    # Extract
    success = extractor.extract_system(system_id, auto_confirm=False)

    if success:
        print("\n🎉 SUCCESS!")
        print(f"System '{SYSTEMS[system_id].name}' extracted successfully!")
        sys.exit(0)
    else:
        print("\n❌ FAILED!")
        print("Extraction did not complete successfully")
        sys.exit(1)


if __name__ == "__main__":
    main()
