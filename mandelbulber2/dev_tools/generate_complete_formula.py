#!/usr/bin/env python3
"""
Mandelbulber Complete Formula Generator
========================================
Generates ALL files needed for a new Mandelbulber formula:
- C++ formula class (.cpp + .h)
- Enum entry
- Factory registration
- Parameter registration
- UI file (.ui)
- OpenCL stub (.cl)

Usage:
    python3 generate_complete_formula.py --input formula_spec.json

JSON Format:
    {
      "formula": {
        "internal_name": "transf_my_transform",
        "display_name": "T>My Transform",
        "type": "transform",
        "de_type": "analyticDEType",
        "de_function": "linearDEFunction",
        "cpixel_addition": "cpixelEnabledByDefault",
        "default_bailout": 100.0,
        "de_analytic_function": "analyticFunctionLinear",
        "coloring_function": "coloringFunctionDefault"
      },
      "parameters": [
        {
          "name": "scale",
          "type": "double",
          "label": "Scale",
          "default": 1.0,
          "min": 0.001,
          "max": 100.0,
          "morph": "morphAkima"
        }
      ],
      "formula_code": "z = z * fractal->transformCommon.scale;"
    }
"""

import argparse
import json
import re
import sys
from pathlib import Path


class CompleteFormulaGenerator:
    def __init__(self, project_root: Path):
        self.project_root = Path(project_root)
        self.formula_dir = self.project_root / "formula" / "definition"
        self.src_dir = self.project_root / "src"
        self.ui_dir = self.project_root / "deploy" / "share" / "mandelbulber2" / "formula" / "ui"
        self.opencl_dir = self.project_root / "deploy" / "share" / "mandelbulber2" / "formula" / "opencl"
        self.ui_dir.mkdir(parents=True, exist_ok=True)
        self.opencl_dir.mkdir(parents=True, exist_ok=True)

    def generate(self, spec: dict) -> bool:
        formula = spec["formula"]
        params = spec.get("parameters", [])
        code = spec.get("formula_code", "")
        internal_name = formula["internal_name"]
        display_name = formula["display_name"]
        class_name = self._to_class_name(internal_name)

        print(f"\n{'='*60}")
        print(f"Generating formula: {display_name}")
        print(f"Internal name: {internal_name}")
        print(f"Class name: {class_name}")
        print(f"Parameters: {len(params)}")
        print(f"{'='*60}\n")

        enum_id = self._get_next_enum_id()
        enum_name = self._to_enum_name(internal_name)
        print(f"Next enum ID: {enum_id} ({enum_name})")

        self._add_enum_entry(enum_name, enum_id)
        print(f"  Added enum entry")

        self._add_fractal_class(class_name)
        print(f"  Added FRACTAL_CLASS declaration")

        self._add_factory_entry(class_name)
        print(f"  Added factory registration")

        self._add_parameter_registration(internal_name, params)
        print(f"  Added parameter registration")

        self._generate_cpp_files(class_name, internal_name, display_name, formula, params, code)
        print(f"  Generated C++ files")

        self._generate_ui_file(internal_name, display_name, params)
        print(f"  Generated UI file")

        self._generate_opencl_stub(internal_name)
        print(f"  Generated OpenCL stub")

        print(f"\n{'='*60}")
        print(f"SUCCESS! All files generated for {display_name}")
        print(f"{'='*60}")
        print(f"\nNext steps:")
        print(f"1. Review generated code in:")
        print(f"   - {self.formula_dir}/fractal_{internal_name}.cpp")
        print(f"   - {self.formula_dir}/fractal_{internal_name}.h")
        print(f"2. Implement FormulaCode() with your formula logic")
        print(f"3. Build: make -j$(nproc)")
        print(f"4. Test in Mandelbulber")
        return True

    def _to_class_name(self, internal_name: str) -> str:
        parts = internal_name.split("_")
        return "cFractal" + "".join(p.capitalize() for p in parts)

    def _to_enum_name(self, internal_name: str) -> str:
        parts = internal_name.split("_")
        return parts[0] + "".join(p.capitalize() for p in parts[1:])

    def _get_next_enum_id(self) -> int:
        enums_file = self.formula_dir / "all_fractal_list_enums.hpp"
        text = enums_file.read_text(encoding="utf-8")
        ids = []
        for match in re.finditer(r'=\s*(\d+)', text):
            val = int(match.group(1))
            if val < 9999:
                ids.append(val)
        return max(ids) + 1 if ids else 2106

    def _add_enum_entry(self, enum_name: str, enum_id: int):
        enums_file = self.formula_dir / "all_fractal_list_enums.hpp"
        text = enums_file.read_text(encoding="utf-8")
        lines = text.splitlines()
        insert_idx = None
        for i, line in enumerate(lines):
            if 'custom = 10000' in line:
                insert_idx = i
                break
        if insert_idx is not None:
            lines.insert(insert_idx, f"\t{enum_name} = {enum_id},")
            enums_file.write_text("\n".join(lines) + "\n", encoding="utf-8")

    def _add_fractal_class(self, class_name: str):
        defs_file = self.formula_dir / "all_fractal_definitions.h"
        text = defs_file.read_text(encoding="utf-8")
        lines = text.splitlines()
        last_idx = None
        for i, line in enumerate(lines):
            if 'FRACTAL_CLASS(' in line:
                last_idx = i
        if last_idx is not None:
            lines.insert(last_idx + 1, f"FRACTAL_CLASS({class_name})")
            defs_file.write_text("\n".join(lines) + "\n", encoding="utf-8")

    def _add_factory_entry(self, class_name: str):
        factory_file = self.formula_dir / "all_fractal_list.cpp"
        text = factory_file.read_text(encoding="utf-8")
        lines = text.splitlines()
        last_idx = None
        for i, line in enumerate(lines):
            if 'fractalList->append(new cFractal' in line:
                last_idx = i
        if last_idx is not None:
            lines.insert(last_idx + 1, f"\tfractalList->append(new {class_name}());")
            factory_file.write_text("\n".join(lines) + "\n", encoding="utf-8")

    def _add_parameter_registration(self, internal_name: str, params: list):
        init_file = self.src_dir / "initparameters.cpp"
        text = init_file.read_text(encoding="utf-8")
        lines = text.splitlines()
        insert_idx = None
        for i in range(len(lines) - 1, -1, -1):
            if 'par->addParam(' in lines[i]:
                if any(prefix in lines[i] for prefix in ['transf_', 'mandelbox', 'mandelbulb', 'abox', 'folding']):
                    insert_idx = i + 1
                    break
        if insert_idx is None:
            for i in range(len(lines) - 1, -1, -1):
                if 'void InitFractalParams' in lines[i]:
                    insert_idx = i + 5
                    break
        if insert_idx:
            new_lines = [f"\t// {internal_name} parameters"]
            for p in params:
                reg = self._generate_param_registration(internal_name, p)
                new_lines.append(f"\t{reg}")
            new_lines.append("")
            for j, line in enumerate(new_lines):
                lines.insert(insert_idx + j, line)
            init_file.write_text("\n".join(lines) + "\n", encoding="utf-8")

    def _generate_param_registration(self, prefix: str, param: dict) -> str:
        name = f"{prefix}_{param['name']}"
        ptype = param.get("type", "double")
        default = param.get("default")
        morph = param.get("morph", "morphAkima")
        if ptype == "double":
            min_val = param.get("min", "-1e10")
            max_val = param.get("max", "1e10")
            return f'par->addParam("{name}", {default}, {min_val}, {max_val}, {morph}, paramStandard);'
        elif ptype == "cvector3":
            if isinstance(default, (list, tuple)) and len(default) == 3:
                return f'par->addParam("{name}", CVector3({default[0]}, {default[1]}, {default[2]}), {morph}, paramStandard);'
            return f'par->addParam("{name}", CVector3(0.0, 0.0, 0.0), {morph}, paramStandard);'
        elif ptype == "cvector4":
            if isinstance(default, (list, tuple)) and len(default) == 4:
                return f'par->addParam("{name}", CVector4({default[0]}, {default[1]}, {default[2]}, {default[3]}), {morph}, paramStandard);'
            return f'par->addParam("{name}", CVector4(0.0, 0.0, 0.0, 0.0), {morph}, paramStandard);'
        elif ptype == "int":
            min_val = int(param.get("min", 0))
            max_val = int(param.get("max", 999999))
            return f'par->addParam("{name}", {int(default)}, {min_val}, {max_val}, morphLinear, paramStandard);'
        elif ptype == "bool":
            val = "true" if default else "false"
            return f'par->addParam("{name}", {val}, morphLinear, paramStandard);'
        else:
            return f'par->addParam("{name}", {default}, {morph}, paramStandard);'

    def _generate_cpp_files(self, class_name: str, internal_name: str, display_name: str,
                            formula: dict, params: list, code: str):
        de_type = formula.get("de_type", "analyticDEType")
        de_function = formula.get("de_function", "linearDEFunction")
        cpixel = formula.get("cpixel_addition", "cpixelEnabledByDefault")
        bailout = formula.get("default_bailout", 100.0)
        de_analytic = formula.get("de_analytic_function", "analyticFunctionLinear")
        coloring = formula.get("coloring_function", "coloringFunctionDefault")

        header_content = f"""/**
 * {display_name} formula
 * Generated by generate_complete_formula.py
 */

#ifndef MANDELBULBER2_FORMULA_DEFINITION_FRACTAL_{internal_name.upper()}_H_
#define MANDELBULBER2_FORMULA_DEFINITION_FRACTAL_{internal_name.upper()}_H_

#include "all_fractal_definitions.h"

class {class_name} : public cAbstractFractal
{{
public:
	{class_name}();
	void FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux) override;
}};

#endif
"""

        param_comments = "\n".join(
            f"\t//   fractal->transformCommon.{p['name']} ({p.get('type', 'double')})"
            for p in params
        ) if params else "\t//   (no parameters defined)"

        source_content = f"""/**
 * {display_name} formula
 * Generated by generate_complete_formula.py
 */

#include "fractal_{internal_name}.h"

{class_name}::{class_name}() : cAbstractFractal()
{{
	nameInComboBox = "{display_name}";
	internalName = "{internal_name}";
	internalID = fractal::{self._to_enum_name(internal_name)};
	DEType = {de_type};
	DEFunctionType = {de_function};
	cpixelAddition = {cpixel};
	defaultBailout = {bailout};
	DEAnalyticFunction = {de_analytic};
	coloringFunction = {coloring};
}}

void {class_name}::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{{
	// TODO: Implement your formula here
	// Available parameters:
{param_comments}

{code if code else '\tz = z;\n\taux.DE = aux.DE + 1.0;'}
}}
"""

        (self.formula_dir / f"fractal_{internal_name}.h").write_text(header_content, encoding="utf-8")
        (self.formula_dir / f"fractal_{internal_name}.cpp").write_text(source_content, encoding="utf-8")

    def _generate_ui_file(self, internal_name: str, display_name: str, params: list):
        sys.path.insert(0, str(self.project_root / "designer"))
        from generate_formula_ui import FormulaUIGenerator
        generator = FormulaUIGenerator(internal_name, display_name)
        xml = generator.generate(params)
        (self.ui_dir / f"{internal_name}.ui").write_text(xml, encoding="utf-8")

    def _generate_opencl_stub(self, internal_name: str):
        content = f"""/**
 * {internal_name} OpenCL kernel stub
 * Generated by generate_complete_formula.py
 */

// TODO: Implement OpenCL version of your formula
"""
        (self.opencl_dir / f"{internal_name}.cl").write_text(content, encoding="utf-8")


def main():
    parser = argparse.ArgumentParser(description="Generate complete Mandelbulber formula")
    parser.add_argument("--input", "-i", required=True, help="JSON specification file")
    parser.add_argument("--project-root", "-r",
                        default="/home/joeri/mandelbulber2_v2_experiment/mandelbulber2",
                        help="Path to mandelbulber2 source root")
    args = parser.parse_args()

    with open(args.input, "r", encoding="utf-8") as f:
        spec = json.load(f)

    generator = CompleteFormulaGenerator(Path(args.project_root))
    success = generator.generate(spec)
    sys.exit(0 if success else 1)


if __name__ == "__main__":
    main()
