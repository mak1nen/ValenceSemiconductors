# Valence — Chip Config System

## How it works

```bash
config/chips/your_chip.yaml               # you edit this
        ↓
scripts/generate_params_master.py         # validates + renders
        ↓
hardware/src/.../params/GeneratedParams.scala  # auto-generated
        ↓
sbt hardware/compile                      # compile the chip
```

## Adding a new chip

1. Copy the nearest config:

```bash
cp config/chips/sky130.yaml config/chips/my_chip.yaml
```

2. Edit the values — every field is defined in `schema/master_schema.yaml`

3. Generate and compile:

```bash
python3 scripts/generate_params_master.py config/chips/my_chip.yaml
sbt hardware/compile
```

## Files

```
config/
├── schema/
│   └── master_schema.yaml   # defines all valid params and ranges
├── chips/
│   ├── sim.yaml             # minimal, fast simulation
│   └── sky130.yaml          # full featured, sky130 verification
└── templates/
    └── CoreParams.scala     # Jinja template, do not edit by hand
```

## Adding a new process node

Only add a node when you have real PDK data for it.

1. Add the node to `schema/master_schema.yaml` under `physical.node.allowed`
2. Add real clock, voltage, metal layer values in the notes
3. Create `config/chips/v1_newnode.yaml` with real values
4. Generate and compile to verify

## Rules

- Never edit `GeneratedParams.scala` by hand — always overwritten
- Never guess physical params — only use real PDK values
- `CoreParams.scala` defines structure only — never add values there