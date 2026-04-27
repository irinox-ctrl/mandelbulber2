#!/usr/bin/env python3
"""
Run single extraction phase with full reporting
"""

import sys
import subprocess
from pathlib import Path

def run_phase(system_id: str, phase_num: int):
    """Run extraction phase with echo input"""

    print(f"\n{'='*70}")
    print(f"STARTING PHASE {phase_num}: {system_id.upper()}")
    print(f"{'='*70}\n")

    # Run extractor with 'yes' piped to all prompts
    cmd = f"yes yes | python3 dev_tools/safe_system_extractor.py {system_id}"

    result = subprocess.run(
        cmd,
        shell=True,
        cwd=Path.cwd()
    )

    return result.returncode == 0

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python3 run_extraction_phase.py <system_id> <phase_num>")
        sys.exit(1)

    system_id = sys.argv[1]
    phase_num = int(sys.argv[2])

    success = run_phase(system_id, phase_num)
    sys.exit(0 if success else 1)
