package valence.soc

import chisel3._
import circt.stage.ChiselStage
import valence.params.GeneratedParams

// =============================================================================
// SoCElaborate — dynamic elaboration entry point
//
// Reads params from GeneratedParams.scala which is auto-generated from YAML:
//   python3 scripts/generate_params_master.py config/chips/sim.yaml
//   sbt elaborate
//
// To target a different node:
//   python3 scripts/generate_params_master.py config/chips/sky130.yaml
//   sbt elaborate
// =============================================================================

object SoCElaborate extends App {
  // all params come from GeneratedParams — generated from YAML
  val p = GeneratedParams.core

  ChiselStage.emitSystemVerilogFile(
    new SoC(p),
    firtoolOpts = Array("--strip-debug-info"),
    args        = Array("--target-dir", "hardware/generated")
  )

  println(s"Elaborated: ${p.physical.targetNode} @ ${1000.0 / p.physical.clockPeriodNs}MHz")
  println(s"xlen:       ${p.xlen}-bit")
  println(s"harts:      ${p.nHarts}")
  println(s"GEMM:       ${p.gemm.enabled}")
}