#!/usr/bin/env python3
import re

# Fix CPU versie
with open('src/fractal_coloring.cpp', 'r') as f:
    cpu_content = f.read()

# Vervang de drie coloring functions
cpu_content = cpu_content.replace(
    'case coloringFunctionIFS: colorIndex = colorMin * 1000.0; break;',
    '''case coloringFunctionIFS:
\t\t\t\t// colorMin is altijd 1000.0 als geen orbit trap hit - gebruik r als variabele component
\t\t\t\tcolorIndex = (colorMin < 999.9)
\t\t\t\t\t\t? colorMin * 1000.0  // orbit trap had een hit
\t\t\t\t\t\t: r * 100.0;  // geen orbit trap: gebruik radius
\t\t\t\tbreak;'''
)

cpu_content = cpu_content.replace(
    'case coloringFunctionAmazingSurf: colorIndex = colorMin * 200.0; break;',
    '''case coloringFunctionAmazingSurf:
\t\t\t\t// colorMin is altijd 1000.0 als geen orbit trap hit - gebruik r als variabele component
\t\t\t\tcolorIndex = (colorMin < 999.9)
\t\t\t\t\t\t? colorMin * 200.0  // orbit trap had een hit
\t\t\t\t\t\t: r * 100.0;  // geen orbit trap: gebruik radius
\t\t\t\tbreak;'''
)

cpu_content = cpu_content.replace(
    'case coloringFunctionDefault: colorIndex = colorMin * 5000.0; break;',
    '''case coloringFunctionDefault:
\t\t\t\t// colorMin is altijd 1000.0 bij Standard mode - gebruik r als variabele component
\t\t\t\tcolorIndex = (colorMin < 999.9)
\t\t\t\t\t\t? colorMin * 5000.0  // orbit trap had een hit
\t\t\t\t\t\t: r * 100.0;  // geen orbit trap: gebruik radius
\t\t\t\tbreak;'''
)

with open('src/fractal_coloring.cpp', 'w') as f:
    f.write(cpu_content)

print("CPU versie gefixt")

# Fix OpenCL versie
with open('opencl/engines/fractal_coloring.cl', 'r') as f:
    cl_content = f.read()

cl_content = cl_content.replace(
    'case clColoringFunctionIFS: colorIndex = colorMin * 1000.0f; break;',
    '''case clColoringFunctionIFS:
\t\t\t\t// colorMin is altijd 1000.0 als geen orbit trap hit - gebruik r als variabele component
\t\t\t\tcolorIndex = (colorMin < 999.9f)
\t\t\t\t\t\t? colorMin * 1000.0f  // orbit trap had een hit
\t\t\t\t\t\t: r * 100.0f;  // geen orbit trap: gebruik radius
\t\t\t\tbreak;'''
)

cl_content = cl_content.replace(
    'case clColoringFunctionAmazingSurf: colorIndex = colorMin * 200.0f; break;',
    '''case clColoringFunctionAmazingSurf:
\t\t\t\t// colorMin is altijd 1000.0 als geen orbit trap hit - gebruik r als variabele component
\t\t\t\tcolorIndex = (colorMin < 999.9f)
\t\t\t\t\t\t? colorMin * 200.0f  // orbit trap had een hit
\t\t\t\t\t\t: r * 100.0f;  // geen orbit trap: gebruik radius
\t\t\t\tbreak;'''
)

with open('opencl/engines/fractal_coloring.cl', 'w') as f:
    f.write(cl_content)

print("OpenCL versie gefixt")
