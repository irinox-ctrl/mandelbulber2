#!/usr/bin/env python3
"""
Mandelbulber Formula Wizard - Visual step-by-step formula generator
A PyQt5 GUI that guides users through creating a new Mandelbulber formula.
"""

import sys
import json
import os
import subprocess
from pathlib import Path

from PyQt5.QtWidgets import (
    QApplication, QWizard, QWizardPage, QVBoxLayout, QHBoxLayout,
    QLabel, QLineEdit, QComboBox, QSpinBox, QDoubleSpinBox,
    QPushButton, QTableWidget, QTableWidgetItem, QTextEdit,
    QGroupBox, QFormLayout, QMessageBox, QCheckBox, QFileDialog,
    QHeaderView, QAbstractItemView, QPlainTextEdit, QSplitter
)
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QFont


class IntroPage(QWizardPage):
    def __init__(self):
        super().__init__()
        self.setTitle("Welkom bij de Formula Wizard")
        self.setSubTitle("Deze wizard helpt je stap voor stap een nieuwe Mandelbulber formule te maken.")

        layout = QVBoxLayout()

        info = QLabel(
            "<h2>Wat gaan we doen?</h2>"
            "<p>We gaan samen alle benodigde informatie verzamelen voor je nieuwe formule:</p>"
            "<ol>"
            "<li><b>Basis informatie</b> — naam, type, display naam</li>"
            "<li><b>Parameters</b> — welke sliders/knoppen heeft je formule nodig?</li>"
            "<li><b>Formule code</b> — de wiskundige berekening</li>"
            "<li><b>Genereren</b> — alle bestanden worden automatisch aangemaakt!</li>"
            "</ol>"
            "<p><i>Tips:</i></p>"
            "<ul>"
            "<li>Transform formules beginnen meestal met <code>transf_</code></li>"
            "<li>Gebruik duidelijke namen die de functie beschrijven</li>"
            "<li>Je kunt altijd terug naar een vorige stap</li>"
            "</ul>"
        )
        info.setWordWrap(True)
        info.setTextFormat(Qt.RichText)
        layout.addWidget(info)
        self.setLayout(layout)


class BasicInfoPage(QWizardPage):
    def __init__(self):
        super().__init__()
        self.setTitle("Stap 1: Basis Informatie")
        self.setSubTitle("Vul de basisgegevens van je formule in.")

        layout = QFormLayout()

        self.name_edit = QLineEdit()
        self.name_edit.setPlaceholderText("bijv. transf_mijn_effect")
        self.name_edit.textChanged.connect(self.completeChanged)
        layout.addRow("Interne naam*:", self.name_edit)

        name_help = QLabel("<small>Gebruik kleine letters en underscores. Voorbeeld: <code>transf_rotatie_v2</code></small>")
        name_help.setStyleSheet("color: gray;")
        layout.addRow("", name_help)

        self.display_edit = QLineEdit()
        self.display_edit.setPlaceholderText("bijv. T>Mijn Effect")
        self.display_edit.textChanged.connect(self.completeChanged)
        layout.addRow("Display naam*:", self.display_edit)

        display_help = QLabel("<small>Dit is wat de gebruiker ziet in de lijst. Transforms gebruiken <code>T></code> als prefix.</small>")
        display_help.setStyleSheet("color: gray;")
        layout.addRow("", display_help)

        self.type_combo = QComboBox()
        self.type_combo.addItems(["Transform (transf_)", "Fractal (fractal_)", "Primitive (primitive_)", "Other"])
        layout.addRow("Formule type:", self.type_combo)

        self.de_combo = QComboBox()
        self.de_combo.addItems(["analyticDEType", "deltaDEType", "pseudoKleinianDEType", "customDEFunction", "withoutDEFunction"])
        layout.addRow("DE Type:", self.de_combo)

        self.bailout_spin = QDoubleSpinBox()
        self.bailout_spin.setRange(0.1, 1000000.0)
        self.bailout_spin.setValue(100.0)
        self.bailout_spin.setDecimals(1)
        layout.addRow("Default bailout:", self.bailout_spin)

        self.cpixel_combo = QComboBox()
        self.cpixel_combo.addItems(["cpixelEnabledByDefault", "cpixelDisabledByDefault", "cpixelAlreadyHas", "cpixelWithoutPar"])
        layout.addRow("Cpixel mode:", self.cpixel_combo)

        self.setLayout(layout)

    def isComplete(self):
        return bool(self.name_edit.text().strip() and self.display_edit.text().strip())

    def validatePage(self):
        name = self.name_edit.text().strip()
        if " " in name or "-" in name:
            QMessageBox.warning(self, "Ongeldige naam", "Interne naam mag geen spaties of streepjes bevatten. Gebruik underscores.")
            return False
        return True


class ParametersPage(QWizardPage):
    def __init__(self):
        super().__init__()
        self.setTitle("Stap 2: Parameters")
        self.setSubTitle("Voeg de parameters (sliders, knoppen, etc.) toe die je formule nodig heeft.")

        layout = QVBoxLayout()

        # Table
        self.table = QTableWidget()
        self.table.setColumnCount(6)
        self.table.setHorizontalHeaderLabels(["Naam", "Type", "Label", "Default", "Min", "Max"])
        self.table.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.table.setSelectionBehavior(QAbstractItemView.SelectRows)
        self.table.setAlternatingRowColors(True)
        layout.addWidget(self.table)

        # Buttons
        btn_layout = QHBoxLayout()
        self.add_btn = QPushButton("+ Parameter toevoegen")
        self.add_btn.setStyleSheet("background-color: #4CAF50; color: white; font-weight: bold;")
        self.add_btn.clicked.connect(self.add_parameter)

        self.remove_btn = QPushButton("- Verwijder geselecteerde")
        self.remove_btn.setStyleSheet("background-color: #f44336; color: white;")
        self.remove_btn.clicked.connect(self.remove_parameter)

        self.example_btn = QPushButton("Laad voorbeeld")
        self.example_btn.clicked.connect(self.load_example)

        btn_layout.addWidget(self.add_btn)
        btn_layout.addWidget(self.remove_btn)
        btn_layout.addStretch()
        btn_layout.addWidget(self.example_btn)
        layout.addLayout(btn_layout)

        # Help
        help_text = QLabel(
            "<b>Type uitleg:</b><br>"
            "<code>double</code> — decimaal getal (slider)<br>"
            "<code>cvector3</code> — 3D vector (x, y, z)<br>"
            "<code>cvector4</code> — 4D vector (x, y, z, w)<br>"
            "<code>int</code> — geheel getal<br>"
            "<code>bool</code> — aan/uit vinkje<br>"
            "<code>color</code> — kleurselector"
        )
        help_text.setStyleSheet("background-color: #f5f5f5; padding: 10px; border-radius: 5px;")
        layout.addWidget(help_text)

        self.setLayout(layout)

    def add_parameter(self):
        row = self.table.rowCount()
        self.table.insertRow(row)

        # Name
        self.table.setItem(row, 0, QTableWidgetItem("param_" + str(row + 1)))

        # Type combo
        type_combo = QComboBox()
        type_combo.addItems(["double", "cvector3", "cvector4", "int", "bool", "color"])
        self.table.setCellWidget(row, 1, type_combo)

        # Label
        self.table.setItem(row, 2, QTableWidgetItem("Parameter " + str(row + 1)))

        # Default
        self.table.setItem(row, 3, QTableWidgetItem("1.0"))

        # Min
        self.table.setItem(row, 4, QTableWidgetItem("0.0"))

        # Max
        self.table.setItem(row, 5, QTableWidgetItem("10.0"))

    def remove_parameter(self):
        row = self.table.currentRow()
        if row >= 0:
            self.table.removeRow(row)

    def load_example(self):
        self.table.setRowCount(0)
        examples = [
            ("scale", "double", "Scale", "2.0", "0.001", "100.0"),
            ("offset", "cvector3", "Offset", "0.0;0.0;0.0", "-100.0", "100.0"),
            ("iterations", "int", "Iterations", "10", "1", "250"),
            ("enabled", "bool", "Enable", "true", "", ""),
        ]
        for name, ptype, label, default, minv, maxv in examples:
            row = self.table.rowCount()
            self.table.insertRow(row)
            self.table.setItem(row, 0, QTableWidgetItem(name))
            type_combo = QComboBox()
            type_combo.addItems(["double", "cvector3", "cvector4", "int", "bool", "color"])
            type_combo.setCurrentText(ptype)
            self.table.setCellWidget(row, 1, type_combo)
            self.table.setItem(row, 2, QTableWidgetItem(label))
            self.table.setItem(row, 3, QTableWidgetItem(default))
            self.table.setItem(row, 4, QTableWidgetItem(minv))
            self.table.setItem(row, 5, QTableWidgetItem(maxv))


class CodePage(QWizardPage):
    def __init__(self):
        super().__init__()
        self.setTitle("Stap 3: Formule Code")
        self.setSubTitle("Schrijf de C++ code voor je formule berekening.")

        layout = QVBoxLayout()

        help_label = QLabel(
            "<p>Schrijf hier de code die in <code>void FormulaCode(...)</code> komt.</p>"
            "<p>Beschikbare variabelen: <code>z</code> (CVector4), <code>aux</code> (sExtendedAux), "
            "<code>fractal</code> (const sFractal*), <code>c</code> (CVector4)</p>"
            "<p>Gebruik <code>\t</code> voor inspringing. Je hoeft geen accolades of functie-header te schrijven.</p>"
        )
        help_label.setWordWrap(True)
        layout.addWidget(help_label)

        self.code_edit = QPlainTextEdit()
        self.code_edit.setPlaceholderText(
            "// Voorbeeld: scale transform\n"
            "z *= fractal->transformCommon.scale;\n"
            "aux.DE = aux.DE * fabs(fractal->transformCommon.scale) + 1.0;"
        )
        font = QFont("Consolas", 10)
        font.setFixedPitch(True)
        self.code_edit.setFont(font)
        self.code_edit.setMinimumHeight(200)
        layout.addWidget(self.code_edit)

        # Example buttons
        example_layout = QHBoxLayout()
        examples = [
            ("Scale", "z *= fractal->transformCommon.scale;\n\taux.DE = aux.DE * fabs(fractal->transformCommon.scale) + 1.0;"),
            ("Rotation", "z = fractal->transformCommon.rotationMatrix.RotateVector(z);"),
            ("Offset", "z += fractal->transformCommon.offset;"),
        ]
        for name, code in examples:
            btn = QPushButton(name)
            btn.clicked.connect(lambda checked, c=code: self.code_edit.setPlainText(c))
            example_layout.addWidget(btn)
        example_layout.addStretch()
        layout.addLayout(example_layout)

        self.setLayout(layout)


class PreviewPage(QWizardPage):
    def __init__(self):
        super().__init__()
        self.setTitle("Stap 4: Preview & Genereren")
        self.setSubTitle("Controleer de JSON en genereer alle bestanden.")

        layout = QVBoxLayout()

        self.preview_edit = QPlainTextEdit()
        self.preview_edit.setReadOnly(True)
        font = QFont("Consolas", 9)
        font.setFixedPitch(True)
        self.preview_edit.setFont(font)
        layout.addWidget(self.preview_edit)

        self.generate_btn = QPushButton("🚀 Genereer Alle Bestanden")
        self.generate_btn.setStyleSheet(
            "background-color: #2196F3; color: white; font-weight: bold; font-size: 14px; padding: 10px;"
        )
        self.generate_btn.clicked.connect(self.generate_files)
        layout.addWidget(self.generate_btn)

        self.result_label = QLabel("")
        self.result_label.setWordWrap(True)
        layout.addWidget(self.result_label)

        self.setLayout(layout)

    def initializePage(self):
        wizard = self.wizard()
        data = self.build_json(wizard)
        self.preview_edit.setPlainText(json.dumps(data, indent=2))

    def build_json(self, wizard):
        basic = wizard.page(1)
        params = wizard.page(2)
        code = wizard.page(3)

        # Get formula type prefix
        type_text = basic.type_combo.currentText()
        if "Transform" in type_text:
            prefix = "transf_"
        elif "Fractal" in type_text:
            prefix = "fractal_"
        elif "Primitive" in type_text:
            prefix = "primitive_"
        else:
            prefix = ""

        name = basic.name_edit.text().strip()
        if not name.startswith(prefix) and prefix:
            name = prefix + name

        # Build parameters
        parameters = []
        table = params.table
        for row in range(table.rowCount()):
            ptype = table.cellWidget(row, 1).currentText()
            pname = table.item(row, 0).text()
            plabel = table.item(row, 2).text()
            pdefault = table.item(row, 3).text()
            pmin = table.item(row, 4).text() if table.item(row, 4) else ""
            pmax = table.item(row, 5).text() if table.item(row, 5) else ""

            param = {
                "name": pname,
                "type": ptype,
                "label": plabel,
            }

            if ptype == "cvector3":
                parts = pdefault.split(";")
                if len(parts) == 3:
                    param["default"] = [float(parts[0]), float(parts[1]), float(parts[2])]
                else:
                    param["default"] = [0.0, 0.0, 0.0]
                param["min"] = float(pmin) if pmin else -100.0
                param["max"] = float(pmax) if pmax else 100.0
            elif ptype == "cvector4":
                parts = pdefault.split(";")
                if len(parts) == 4:
                    param["default"] = [float(parts[0]), float(parts[1]), float(parts[2]), float(parts[3])]
                else:
                    param["default"] = [0.0, 0.0, 0.0, 0.0]
                param["min"] = float(pmin) if pmin else -100.0
                param["max"] = float(pmax) if pmax else 100.0
            elif ptype == "bool":
                param["default"] = pdefault.lower() == "true"
            elif ptype == "int":
                param["default"] = int(pdefault) if pdefault else 0
                param["min"] = int(pmin) if pmin else 0
                param["max"] = int(pmax) if pmax else 250
            elif ptype == "color":
                param["default"] = [255, 255, 255]
            else:
                param["default"] = float(pdefault) if pdefault else 1.0
                param["min"] = float(pmin) if pmin else 0.0
                param["max"] = float(pmax) if pmax else 100.0

            parameters.append(param)

        data = {
            "formula": {
                "internal_name": name,
                "display_name": basic.display_edit.text().strip(),
                "de_type": basic.de_combo.currentText(),
                "de_function": "linearDEFunction",
                "cpixel_addition": basic.cpixel_combo.currentText(),
                "default_bailout": basic.bailout_spin.value(),
                "de_analytic_function": "analyticFunctionLinear",
                "coloring_function": "coloringFunctionDefault"
            },
            "parameters": parameters,
            "formula_code": code.code_edit.toPlainText()
        }
        return data

    def generate_files(self):
        wizard = self.wizard()
        data = self.build_json(wizard)

        # Save JSON temp file
        temp_json = Path("/tmp/formula_wizard_temp.json")
        with open(temp_json, "w") as f:
            json.dump(data, f, indent=2)

        # Run generator
        script_dir = Path(__file__).parent
        generator = script_dir / "generate_complete_formula.py"

        try:
            result = subprocess.run(
                [sys.executable, str(generator), "--input", str(temp_json)],
                capture_output=True,
                text=True,
                cwd=str(script_dir)
            )

            if result.returncode == 0:
                self.result_label.setText(
                    f"<h2 style='color: green;'>✅ Succes!</h2>"
                    f"<pre>{result.stdout}</pre>"
                    f"<p><b>Volgende stap:</b> Open de gegenereerde C++ file en implementeer de formule logica in <code>FormulaCode()</code>.</p>"
                )
            else:
                self.result_label.setText(
                    f"<h2 style='color: red;'>❌ Fout</h2>"
                    f"<pre>{result.stderr}</pre>"
                )
        except Exception as e:
            self.result_label.setText(f"<h2 style='color: red;'>❌ Fout: {e}</h2>")


class FormulaWizard(QWizard):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Mandelbulber Formula Wizard")
        self.setMinimumSize(800, 600)

        self.addPage(IntroPage())
        self.addPage(BasicInfoPage())
        self.addPage(ParametersPage())
        self.addPage(CodePage())
        self.addPage(PreviewPage())

        self.setWizardStyle(QWizard.ModernStyle)
        self.setOption(QWizard.HaveHelpButton, False)
        self.setOption(QWizard.HaveFinishButtonOnEarlyPages, False)


def main():
    app = QApplication(sys.argv)
    wizard = FormulaWizard()
    wizard.show()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()
