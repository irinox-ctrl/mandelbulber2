#!/usr/bin/env python3
"""
PARAMETER NAMING VALIDATOR
==========================
Validate parameter naming consistency across Mandelbulber!

PROBLEEM:
- Parameters geregistreerd als "dist_min" maar geladen als "min_dist" → SILENT FAILURE!
- 3 naming layers: registration, UI widgets, load/save code
- Geen validatie tot runtime
- Moeilijk te debuggen

OPLOSSING:
- Scan alle parameter registrations (initparameters.cpp)
- Scan alle UI widget names (*.ui files)
- Scan alle parameter loads (fractparams.cpp)
- Check consistency
- Report mismatches

TIJDSBESPARING: Voorkomt uren debugging!

Author: Claude + Joeri
Version: 1.0
Date: 2026-04-19
"""

import re
import sys
from pathlib import Path
from typing import List, Dict, Set, Tuple
from dataclasses import dataclass
from collections import defaultdict


@dataclass
class ParameterDefinition:
    """Parameter definition"""
    name: str
    source_file: str
    line_number: int
    context: str  # 'registration', 'ui_widget', 'load', 'save'


@dataclass
class ValidationIssue:
    """Parameter validation issue"""
    severity: str  # 'error', 'warning', 'info'
    param_name: str
    issue_type: str
    description: str
    locations: List[Tuple[str, int]]  # [(file, line), ...]


class ParameterValidator:
    """Validate parameter naming consistency"""

    def __init__(self, base_dir: Path):
        self.base_dir = base_dir
        self.registered_params = {}  # name -> ParameterDefinition
        self.ui_widgets = {}  # widget_name -> ParameterDefinition
        self.loaded_params = {}  # name -> ParameterDefinition
        self.issues = []

    def validate(self) -> List[ValidationIssue]:
        """
        Full validation

        Returns:
            List of validation issues
        """

        print("=" * 70)
        print("🔍 PARAMETER NAMING VALIDATOR")
        print("=" * 70 + "\n")

        # 1. Scan registrations
        print("📋 Scanning parameter registrations...")
        self._scan_registrations()
        print(f"   Found: {len(self.registered_params)} registered parameters")

        # 2. Scan UI widgets
        print("🎨 Scanning UI widgets...")
        self._scan_ui_widgets()
        print(f"   Found: {len(self.ui_widgets)} UI widgets")

        # 3. Scan parameter loads
        print("📥 Scanning parameter loads...")
        self._scan_parameter_loads()
        print(f"   Found: {len(self.loaded_params)} loaded parameters")

        # 4. Cross-check
        print("\n🔬 Cross-checking consistency...")
        self._check_consistency()

        # 5. Report
        print(f"\n{'='*70}")
        print("📊 VALIDATION RESULTS")
        print(f"{'='*70}\n")

        self._print_report()

        return self.issues

    def _scan_registrations(self):
        """Scan initparameters.cpp for addParam calls"""

        init_file = self.base_dir / "src" / "initparameters.cpp"

        if not init_file.exists():
            print(f"⚠️  initparameters.cpp not found")
            return

        try:
            with open(init_file, 'r', encoding='utf-8', errors='ignore') as f:
                lines = f.readlines()

            # Pattern: par->addParam("param_name", ...)
            pattern = r'par->addParam\("([^"]+)"'

            for line_num, line in enumerate(lines, 1):
                match = re.search(pattern, line)
                if match:
                    param_name = match.group(1)

                    self.registered_params[param_name] = ParameterDefinition(
                        name=param_name,
                        source_file=str(init_file),
                        line_number=line_num,
                        context='registration'
                    )

        except Exception as e:
            print(f"❌ Error scanning registrations: {e}")

    def _scan_ui_widgets(self):
        """Scan .ui files for parameter widgets"""

        ui_dir = self.base_dir / "formula" / "ui"

        if not ui_dir.exists():
            ui_dir = self.base_dir / "qt"

        if not ui_dir.exists():
            print(f"⚠️  UI directory not found")
            return

        ui_files = list(ui_dir.glob("*.ui"))

        # Patterns for different widget types
        patterns = [
            r'<widget[^>]*name="spinboxd3_([^"]+)"',  # CVector3
            r'<widget[^>]*name="spinboxd4_([^"]+)"',  # CVector4
            r'<widget[^>]*name="spinboxd_([^"]+)"',   # double
            r'<widget[^>]*name="spinbox_([^"]+)"',    # int
            r'<widget[^>]*name="checkBox_([^"]+)"',   # bool
            r'<widget[^>]*name="comboBox_([^"]+)"',   # enum
            r'<widget[^>]*name="colorButton_([^"]+)"', # color
        ]

        for ui_file in ui_files:
            try:
                with open(ui_file, 'r', encoding='utf-8', errors='ignore') as f:
                    content = f.read()

                for pattern in patterns:
                    matches = re.finditer(pattern, content)
                    for match in matches:
                        widget_full_name = match.group(0)
                        param_name = match.group(1)

                        # Extract just parameter name (remove _x, _y, _z suffixes)
                        base_param = re.sub(r'_[xyzw]$', '', param_name)

                        self.ui_widgets[base_param] = ParameterDefinition(
                            name=base_param,
                            source_file=str(ui_file),
                            line_number=0,  # Don't track line in XML
                            context='ui_widget'
                        )

            except Exception as e:
                print(f"⚠️  Error scanning {ui_file.name}: {e}")

    def _scan_parameter_loads(self):
        """Scan fractparams.cpp for parameter loads"""

        fract_file = self.base_dir / "src" / "fractparams.cpp"

        if not fract_file.exists():
            print(f"⚠️  fractparams.cpp not found")
            return

        try:
            with open(fract_file, 'r', encoding='utf-8', errors='ignore') as f:
                lines = f.readlines()

            # Patterns for parameter loads
            patterns = [
                r'params\.Get<[^>]+>\("([^"]+)"',  # params.Get<T>("name")
                r'par->get<[^>]+>\("([^"]+)"',     # par->get<T>("name")
            ]

            for line_num, line in enumerate(lines, 1):
                for pattern in patterns:
                    matches = re.finditer(pattern, line)
                    for match in matches:
                        param_name = match.group(1)

                        self.loaded_params[param_name] = ParameterDefinition(
                            name=param_name,
                            source_file=str(fract_file),
                            line_number=line_num,
                            context='load'
                        )

        except Exception as e:
            print(f"❌ Error scanning parameter loads: {e}")

    def _check_consistency(self):
        """Check consistency between registration, UI, and loads"""

        # Check 1: Registered but never loaded
        registered_names = set(self.registered_params.keys())
        loaded_names = set(self.loaded_params.keys())

        never_loaded = registered_names - loaded_names

        for param_name in never_loaded:
            if param_name.startswith('transf_') or param_name.startswith('fold_'):
                # These are often shared parameters, skip warning
                continue

            self.issues.append(ValidationIssue(
                severity='warning',
                param_name=param_name,
                issue_type='unused_parameter',
                description='Parameter registered but never loaded',
                locations=[(self.registered_params[param_name].source_file,
                           self.registered_params[param_name].line_number)]
            ))

        # Check 2: Loaded but never registered
        never_registered = loaded_names - registered_names

        for param_name in never_registered:
            self.issues.append(ValidationIssue(
                severity='error',
                param_name=param_name,
                issue_type='missing_registration',
                description='Parameter loaded but never registered!',
                locations=[(self.loaded_params[param_name].source_file,
                           self.loaded_params[param_name].line_number)]
            ))

        # Check 3: Similar names (potential typos)
        self._check_similar_names()

        # Check 4: UI widgets without matching parameters
        ui_param_names = set(self.ui_widgets.keys())

        # Extract base parameter name from UI widget names
        # e.g., "transf_rotation_x" → "transf_rotation"
        ui_base_params = set()
        for widget_name in ui_param_names:
            # Try to match to registered parameters
            base = widget_name
            found = False

            # Check if any registered param is a prefix
            for reg_param in registered_names:
                if widget_name.startswith(reg_param):
                    found = True
                    break

            if not found:
                # Widget doesn't match any registered parameter
                self.issues.append(ValidationIssue(
                    severity='warning',
                    param_name=widget_name,
                    issue_type='orphan_widget',
                    description='UI widget without matching registered parameter',
                    locations=[(self.ui_widgets[widget_name].source_file, 0)]
                ))

    def _check_similar_names(self):
        """Check for similar parameter names (potential typos)"""

        all_names = list(self.registered_params.keys()) + list(self.loaded_params.keys())

        for i, name1 in enumerate(all_names):
            for name2 in all_names[i+1:]:
                if self._are_similar(name1, name2):
                    # Check if one is registered and other is loaded
                    if (name1 in self.registered_params and name2 in self.loaded_params) or \
                       (name2 in self.registered_params and name1 in self.loaded_params):

                        self.issues.append(ValidationIssue(
                            severity='warning',
                            param_name=f"{name1} / {name2}",
                            issue_type='similar_names',
                            description=f'Similar parameter names (potential typo?)',
                            locations=[]
                        ))

    def _are_similar(self, name1: str, name2: str) -> bool:
        """Check if two names are similar (Levenshtein distance)"""

        if name1 == name2:
            return False

        # Quick check: if one contains the other
        if name1 in name2 or name2 in name1:
            return True

        # Levenshtein distance
        distance = self._levenshtein(name1, name2)

        # Consider similar if distance is small relative to length
        max_len = max(len(name1), len(name2))

        return distance <= max(2, max_len * 0.2)

    def _levenshtein(self, s1: str, s2: str) -> int:
        """Calculate Levenshtein distance"""

        if len(s1) < len(s2):
            return self._levenshtein(s2, s1)

        if len(s2) == 0:
            return len(s1)

        previous_row = range(len(s2) + 1)

        for i, c1 in enumerate(s1):
            current_row = [i + 1]

            for j, c2 in enumerate(s2):
                insertions = previous_row[j + 1] + 1
                deletions = current_row[j] + 1
                substitutions = previous_row[j] + (c1 != c2)

                current_row.append(min(insertions, deletions, substitutions))

            previous_row = current_row

        return previous_row[-1]

    def _print_report(self):
        """Print validation report"""

        if not self.issues:
            print("✅ NO ISSUES FOUND!")
            print(f"\nAll {len(self.registered_params)} parameters are consistent!")
            return

        # Group by severity
        errors = [i for i in self.issues if i.severity == 'error']
        warnings = [i for i in self.issues if i.severity == 'warning']
        infos = [i for i in self.issues if i.severity == 'info']

        # Print errors
        if errors:
            print(f"❌ ERRORS ({len(errors)}):")
            print("─" * 70)
            for issue in errors[:20]:  # Show first 20
                print(f"\n  Parameter: {issue.param_name}")
                print(f"  Issue: {issue.description}")
                if issue.locations:
                    for loc_file, loc_line in issue.locations[:3]:
                        print(f"    Location: {Path(loc_file).name}:{loc_line}")
            if len(errors) > 20:
                print(f"\n  ... and {len(errors)-20} more errors")
            print()

        # Print warnings
        if warnings:
            print(f"⚠️  WARNINGS ({len(warnings)}):")
            print("─" * 70)
            for issue in warnings[:20]:  # Show first 20
                print(f"\n  Parameter: {issue.param_name}")
                print(f"  Issue: {issue.description}")
                if issue.locations:
                    for loc_file, loc_line in issue.locations[:2]:
                        print(f"    Location: {Path(loc_file).name}:{loc_line}")
            if len(warnings) > 20:
                print(f"\n  ... and {len(warnings)-20} more warnings")
            print()

        # Summary
        print("─" * 70)
        print("SUMMARY:")
        print(f"  ❌ Errors: {len(errors)}")
        print(f"  ⚠️  Warnings: {len(warnings)}")
        print(f"  ℹ️  Info: {len(infos)}")
        print(f"\n  Total Issues: {len(self.issues)}")


def main():
    """Main entry"""

    print("╔" + "═"*68 + "╗")
    print("║" + " "*17 + "PARAMETER NAMING VALIDATOR v1.0" + " "*20 + "║")
    print("╚" + "═"*68 + "╝\n")

    base_dir = Path(__file__).parent.parent / "mandelbulber2"

    if not base_dir.exists():
        print(f"❌ Mandelbulber directory not found: {base_dir}")
        sys.exit(1)

    validator = ParameterValidator(base_dir)

    issues = validator.validate()

    # Exit code
    errors = [i for i in issues if i.severity == 'error']

    if errors:
        sys.exit(1)
    else:
        sys.exit(0)


if __name__ == "__main__":
    main()
