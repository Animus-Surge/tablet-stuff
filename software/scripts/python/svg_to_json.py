"""
svg_to_json.py

Custom SVG to JSON converter

Note: SVG output files are expected to be in Inkscape format
"""

import os
import json

# Argument parsing
import argparse

from lxml import etree

if __name__=="__main__":
    parser = argparse.ArgumentParser(description="Convert SVG to JSON (Custom for this project)")
    parser.add_argument("-o", "--output", type=str, help="Output JSON file")
    parser.add_argument("svg_file", type=str, help="SVG file to convert")

    args = parser.parse_args()

    # Load SVG file
    svg_file = args.svg_file
    svg_tree = etree.parse(svg_file) # TODO: error handling

    # Get root element
    root = svg_tree.getroot()
    
    pass
