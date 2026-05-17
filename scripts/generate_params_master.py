#!/usr/bin/env python3
# =============================================================================
# Valence RISC-V — param generator
#
# 1. Loads chip_schema.yaml     — master schema (what params are valid)
# 2. Loads your chip YAML       — instance (actual values)
# 3. Validates YAML vs schema   — catches errors before compile
# 4. Renders Jinja template     — generates GeneratedParams.scala
#
# Usage:
#   python3 scripts/generate_params.py config/chips/sim.yaml
#   python3 scripts/generate_params.py config/chips/sky130.yaml
# =============================================================================

import sys
import os
import yaml
from jinja2 import Environment, FileSystemLoader
from pathlib import Path

SCHEMA_FILE  = Path("config/schema/master_schema.yaml")
TEMPLATE_DIR = Path("config/templates")
TEMPLATE_FILE = "CoreParams.scala"
OUTPUT_FILE  = Path("hardware/src/main/scala/valence/params/GeneratedParams.scala")

# ---------------------------------------------------------------------------
# Load
# ---------------------------------------------------------------------------
def load_yaml(path: Path) -> dict:
    with open(path) as f:
        return yaml.safe_load(f)

# ---------------------------------------------------------------------------
# Validate chip YAML against schema
# ---------------------------------------------------------------------------
def validate(config: dict, schema: dict):
    errors = []

    # Required top-level sections
    for section in schema.keys():
        if section not in config:
            errors.append(f"Missing required section: '{section}'")

    if errors:
        raise ValueError("\n".join(errors))

    # Physical node must be in schema allowed list
    node = config["physical"]["node"]
    allowed_nodes = schema["physical"]["node"]["allowed"]
    if node not in allowed_nodes:
        errors.append(f"Unknown node '{node}'. Allowed: {allowed_nodes}")

    # xlen must be allowed
    xlen = config["isa"]["xlen"]
    if xlen not in schema["isa"]["xlen"]["allowed"]:
        errors.append(f"xlen must be 32 or 64, got {xlen}")

    # MMU requires supervisor
    if config["privilege"]["mmu"] and not config["privilege"]["supervisor"]:
        errors.append("mmu=true requires supervisor=true")

    # GEMM tile size must be power of 2
    tile = config["gemm"]["tile_size"]
    if not (tile > 0 and (tile & (tile - 1)) == 0):
        errors.append(f"gemm.tile_size must be power of 2, got {tile}")

    # GEMM data width must be allowed
    dw = config["gemm"]["data_width"]
    if dw not in schema["gemm"]["data_width"]["allowed"]:
        errors.append(f"gemm.data_width must be 8 or 16, got {dw}")

    # Cache sets must be power of 2
    for cache in ["icache", "dcache"]:
        sets = config[cache]["sets"]
        if not (sets > 0 and (sets & (sets - 1)) == 0):
            errors.append(f"{cache}.sets must be power of 2, got {sets}")

    # Pipeline stages
    stages = config["pipeline"]["stages"]
    if stages < schema["pipeline"]["stages"]["min"]:
        errors.append(f"pipeline.stages must be >= 3, got {stages}")

    if errors:
        raise ValueError("\n  ".join(["Validation failed:"] + errors))

    # Print what validated
    print(f"  ✓ node          = {node}")
    print(f"  ✓ xlen          = {xlen}")
    print(f"  ✓ supervisor    = {config['privilege']['supervisor']}")
    print(f"  ✓ mmu           = {config['privilege']['mmu']}")
    print(f"  ✓ gemm.enabled  = {config['gemm']['enabled']}")
    print(f"  ✓ gemm.tile     = {tile}x{tile}")
    print(f"  ✓ pipeline      = {stages} stages")

# ---------------------------------------------------------------------------
# Render Jinja template
# ---------------------------------------------------------------------------
def render(config: dict, source_file: str) -> str:
    env = Environment(
        loader=FileSystemLoader(str(TEMPLATE_DIR)),
        trim_blocks=True,
        lstrip_blocks=True,
    )
    template = env.get_template(TEMPLATE_FILE)
    return template.render(**config, source_file=source_file)

# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------
def main():
    if len(sys.argv) != 2:
        print("Usage: python3 scripts/generate_params.py <config/chips/xxx.yaml>")
        sys.exit(1)

    config_path = Path(sys.argv[1])
    if not config_path.exists():
        print(f"Error: config not found: {config_path}")
        sys.exit(1)

    if not SCHEMA_FILE.exists():
        print(f"Error: schema not found: {SCHEMA_FILE}")
        sys.exit(1)

    print(f"\n── Loading ──────────────────────────────")
    print(f"  config : {config_path}")
    print(f"  schema : {SCHEMA_FILE}")

    config = load_yaml(config_path)
    schema = load_yaml(SCHEMA_FILE)

    print(f"\n── Validating ───────────────────────────")
    validate(config, schema)

    print(f"\n── Generating ───────────────────────────")
    output = render(config, source_file=str(config_path))
    OUTPUT_FILE.parent.mkdir(parents=True, exist_ok=True)
    OUTPUT_FILE.write_text(output)
    print(f"  ✓ {OUTPUT_FILE}")

    print(f"\n── Ready ────────────────────────────────")
    print(f"  Chip    : {config['chip']['name']} v{config['chip']['version']}")
    print(f"  Node    : {config['physical']['node']}")
    print(f"  Run     : sbt \"hardware/compile\"")
    print(f"────────────────────────────────────────\n")

if __name__ == "__main__":
    main()