##config/chips/your_chip.yaml        ← you edit this
            ↓
##scripts/generate_params_master.py  ← validates + renders
            ↓
##hardware/.../params/GeneratedParams.scala  ← auto-generated
            ↓
##sbt hardware/compile               ← compile the chip