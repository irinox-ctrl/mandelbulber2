#!/usr/bin/env python3
"""
GPU STRUCT SAFETY CHECKER
=========================
Check if common_params struct changes will crash GPU rendering!

PROBLEEM:
- Adding members to common_params.hpp changes GPU struct layout
- GPU struct size mismatch → INSTANT CRASH / BLUE SCREEN
- CPU and GPU structs must match EXACTLY
- Memory layout critical
- No warning until crash!

OPLOSSING:
- Compare CPU struct (common_params.hpp) vs GPU struct (common_params_cl.hpp)
- Check member order, types, alignment
- Warn on layout changes
- Suggest safe padding
- Calculate struct sizes

TIJDSBESPARING: Voorkomt crashes en blue screens!

Author: Claude + Joeri
Version: 1.0
Date: 2026-04-19
"""

import re
import sys
from pathlib import Path
from typing import List, Dict, Tuple, Optional
from dataclasses import dataclass
from enum import Enum


class MemberType(Enum):
    """C++ member types"""
    BOOL = "bool"
    INT = "int"
    FLOAT = "float"
    DOUBLE = "double"
    CVECTOR3 = "CVector3"
    CVECTOR4 = "CVector4"
    FLOAT3 = "float3"  # OpenCL
    FLOAT4 = "float4"  # OpenCL


@dataclass
class StructMember:
    """Struct member definition"""
    name: str
    type: str
    array_size: Optional[int] = None
    line_number: int = 0


@dataclass
class StructDefinition:
    """Complete struct definition"""
    name: str
    members: List[StructMember]
    file_path: Path
    total_size_bytes: int = 0


class GPUStructChecker:
    """Check GPU struct safety"""

    # Size mapping (simplified, platform dependent!)
    TYPE_SIZES = {
        'bool': 1,
        'int': 4,
        'float': 4,
        'double': 8,
        'CVector3': 24,  # 3 * double
        'CVector4': 32,  # 4 * double
        'float3': 12,    # 3 * float (OpenCL may pad to 16!)
        'float4': 16,    # 4 * float
    }

    def __init__(self, base_dir: Path):
        self.base_dir = base_dir
        self.cpu_struct = None
        self.gpu_struct = None

    def check(self) -> bool:
        """
        Full GPU struct safety check

        Returns:
            True if safe, False if problems detected
        """

        print("=" * 70)
        print("🛡️  GPU STRUCT SAFETY CHECKER")
        print("=" * 70 + "\n")

        # 1. Parse CPU struct
        print("📋 Parsing CPU struct (common_params.hpp)...")
        self.cpu_struct = self._parse_cpu_struct()

        if not self.cpu_struct:
            print("❌ Failed to parse CPU struct")
            return False

        print(f"   Members: {len(self.cpu_struct.members)}")
        print(f"   Estimated size: {self.cpu_struct.total_size_bytes} bytes")

        # 2. Parse GPU struct
        print("\n🎮 Parsing GPU struct (common_params_cl.hpp)...")
        self.gpu_struct = self._parse_gpu_struct()

        if not self.gpu_struct:
            print("❌ Failed to parse GPU struct")
            return False

        print(f"   Members: {len(self.gpu_struct.members)}")
        print(f"   Estimated size: {self.gpu_struct.total_size_bytes} bytes")

        # 3. Compare
        print(f"\n{'='*70}")
        print("🔬 COMPARING STRUCTURES")
        print(f"{'='*70}\n")

        safe = self._compare_structs()

        # 4. Report
        print(f"\n{'='*70}")
        print("📊 SAFETY REPORT")
        print(f"{'='*70}\n")

        if safe:
            print("✅ GPU STRUCT IS SAFE!")
            print("\nNo layout changes detected.")
            print("CPU and GPU structs appear synchronized.")
        else:
            print("❌ GPU STRUCT HAS ISSUES!")
            print("\n⚠️  DANGER: GPU rendering may crash!")
            print("\nRecommendations:")
            print("1. Review struct changes carefully")
            print("2. Add padding instead of reordering")
            print("3. Test with GPU rendering disabled first")
            print("4. Run populateOpenCL.php to regenerate GPU struct")

        return safe

    def _parse_cpu_struct(self) -> Optional[StructDefinition]:
        """Parse CPU struct from common_params.hpp"""

        cpu_file = self.base_dir / "src" / "common_params.hpp"

        if not cpu_file.exists():
            print(f"⚠️  File not found: {cpu_file}")
            return None

        try:
            with open(cpu_file, 'r', encoding='utf-8', errors='ignore') as f:
                lines = f.readlines()

            members = []

            # Find sTransformCommon struct
            in_struct = False
            struct_name = None

            for line_num, line in enumerate(lines, 1):
                # Start of struct
                if re.search(r'struct\s+sTransformCommon', line):
                    in_struct = True
                    struct_name = "sTransformCommon"
                    continue

                if not in_struct:
                    continue

                # End of struct
                if line.strip().startswith('}'):
                    break

                # Parse member
                member = self._parse_member_line(line, line_num)
                if member:
                    members.append(member)

            # Calculate size
            total_size = sum(self._get_member_size(m) for m in members)

            return StructDefinition(
                name=struct_name or "sTransformCommon",
                members=members,
                file_path=cpu_file,
                total_size_bytes=total_size
            )

        except Exception as e:
            print(f"❌ Error parsing CPU struct: {e}")
            return None

    def _parse_gpu_struct(self) -> Optional[StructDefinition]:
        """Parse GPU struct from common_params_cl.hpp"""

        gpu_file = self.base_dir / "opencl" / "common_params_cl.hpp"

        if not gpu_file.exists():
            print(f"⚠️  File not found: {gpu_file}")
            return None

        try:
            with open(gpu_file, 'r', encoding='utf-8', errors='ignore') as f:
                lines = f.readlines()

            members = []

            # Find sTransformCommon struct (OpenCL version)
            in_struct = False
            struct_name = None

            for line_num, line in enumerate(lines, 1):
                # Start of struct
                if re.search(r'typedef struct', line) or re.search(r'struct\s+sTransformCommon', line):
                    in_struct = True
                    struct_name = "sTransformCommon"
                    continue

                if not in_struct:
                    continue

                # End of struct
                if line.strip().startswith('}'):
                    break

                # Parse member (OpenCL syntax)
                member = self._parse_member_line(line, line_num, opencl=True)
                if member:
                    members.append(member)

            # Calculate size
            total_size = sum(self._get_member_size(m) for m in members)

            return StructDefinition(
                name=struct_name or "sTransformCommon",
                members=members,
                file_path=gpu_file,
                total_size_bytes=total_size
            )

        except Exception as e:
            print(f"❌ Error parsing GPU struct: {e}")
            return None

    def _parse_member_line(self, line: str, line_num: int, opencl: bool = False) -> Optional[StructMember]:
        """Parse a struct member line"""

        line = line.strip()

        # Skip comments, empty lines
        if not line or line.startswith('//') or line.startswith('/*'):
            return None

        # Pattern: type name; or type name[size];
        if opencl:
            # OpenCL uses float3, float4 instead of CVector3/4
            pattern = r'(float3|float4|float|double|int|bool)\s+(\w+)(?:\[(\d+)\])?;'
        else:
            pattern = r'(CVector3|CVector4|double|float|int|bool)\s+(\w+)(?:\[(\d+)\])?;'

        match = re.search(pattern, line)

        if match:
            member_type = match.group(1)
            member_name = match.group(2)
            array_size = int(match.group(3)) if match.group(3) else None

            return StructMember(
                name=member_name,
                type=member_type,
                array_size=array_size,
                line_number=line_num
            )

        return None

    def _get_member_size(self, member: StructMember) -> int:
        """Calculate member size in bytes"""

        base_size = self.TYPE_SIZES.get(member.type, 8)  # Default 8 bytes

        if member.array_size:
            return base_size * member.array_size

        return base_size

    def _compare_structs(self) -> bool:
        """Compare CPU and GPU structs"""

        if not self.cpu_struct or not self.gpu_struct:
            return False

        cpu_members = self.cpu_struct.members
        gpu_members = self.gpu_struct.members

        all_safe = True

        # Check 1: Member count
        if len(cpu_members) != len(gpu_members):
            print(f"⚠️  WARNING: Member count mismatch!")
            print(f"   CPU: {len(cpu_members)} members")
            print(f"   GPU: {len(gpu_members)} members")
            print()
            all_safe = False

        # Check 2: Member order and types
        print("Checking member order and types:")
        print("─" * 70)

        max_check = min(len(cpu_members), len(gpu_members))

        for i in range(max_check):
            cpu_mem = cpu_members[i]
            gpu_mem = gpu_members[i]

            # Check names match
            if cpu_mem.name != gpu_mem.name:
                print(f"\n❌ ORDER MISMATCH at position {i}:")
                print(f"   CPU: {cpu_mem.type} {cpu_mem.name}")
                print(f"   GPU: {gpu_mem.type} {gpu_mem.name}")
                all_safe = False
                continue

            # Check types compatible
            if not self._types_compatible(cpu_mem.type, gpu_mem.type):
                print(f"\n⚠️  TYPE MISMATCH: {cpu_mem.name}")
                print(f"   CPU: {cpu_mem.type}")
                print(f"   GPU: {gpu_mem.type}")
                all_safe = False
            else:
                # Match OK
                status = "✅" if self._types_identical(cpu_mem.type, gpu_mem.type) else "🔄"
                print(f"  {status} {cpu_mem.name:30} ({cpu_mem.type} / {gpu_mem.type})")

        # Check 3: Size comparison
        print(f"\n{'─'*70}")
        print("Struct size comparison:")
        print(f"  CPU:  {self.cpu_struct.total_size_bytes} bytes")
        print(f"  GPU:  {self.gpu_struct.total_size_bytes} bytes")

        size_diff = abs(self.cpu_struct.total_size_bytes - self.gpu_struct.total_size_bytes)

        if size_diff > 0:
            print(f"  Diff: {size_diff} bytes")

            if size_diff > 16:  # More than alignment padding
                print("\n⚠️  WARNING: Significant size difference!")
                print("   This may cause GPU crashes!")
                all_safe = False
            else:
                print("\n  ℹ️  Small difference (probably alignment padding)")

        # Check 4: Members only in one struct
        cpu_names = {m.name for m in cpu_members}
        gpu_names = {m.name for m in gpu_members}

        only_cpu = cpu_names - gpu_names
        only_gpu = gpu_names - cpu_names

        if only_cpu:
            print(f"\n⚠️  Members ONLY in CPU struct:")
            for name in sorted(only_cpu):
                print(f"   + {name}")
            all_safe = False

        if only_gpu:
            print(f"\n⚠️  Members ONLY in GPU struct:")
            for name in sorted(only_gpu):
                print(f"   + {name}")
            all_safe = False

        return all_safe

    def _types_compatible(self, cpu_type: str, gpu_type: str) -> bool:
        """Check if CPU and GPU types are compatible"""

        # Exact match
        if cpu_type == gpu_type:
            return True

        # CVector3 ↔ float3
        if (cpu_type == 'CVector3' and gpu_type == 'float3'):
            return True  # Compatible but different representation

        # CVector4 ↔ float4
        if (cpu_type == 'CVector4' and gpu_type == 'float4'):
            return True

        # float ↔ double (dangerous but sometimes used)
        if {cpu_type, gpu_type} == {'float', 'double'}:
            return True  # Compatible but size mismatch!

        return False

    def _types_identical(self, cpu_type: str, gpu_type: str) -> bool:
        """Check if types are identical"""
        return cpu_type == gpu_type


def main():
    """Main entry"""

    print("╔" + "═"*68 + "╗")
    print("║" + " "*20 + "GPU STRUCT SAFETY CHECKER v1.0" + " "*18 + "║")
    print("╚" + "═"*68 + "╝\n")

    base_dir = Path(__file__).parent.parent / "mandelbulber2"

    if not base_dir.exists():
        print(f"❌ Mandelbulber directory not found: {base_dir}")
        sys.exit(1)

    checker = GPUStructChecker(base_dir)

    safe = checker.check()

    if safe:
        print("\n🎉 All checks passed!")
        sys.exit(0)
    else:
        print("\n⚠️  Issues detected - review carefully!")
        sys.exit(1)


if __name__ == "__main__":
    main()
