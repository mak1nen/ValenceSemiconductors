package valence.params

case class PhysicalParams(
  targetNode    : String,
  clockPeriodNs : Double,
  setupMarginNs : Double,
  holdMarginNs  : Double,
  voltageV      : Double,
  metalLayers   : Int,
  maxFanout     : Int,
)

case class CacheParams(
  nSets       : Int,
  nWays       : Int,
  blockBytes  : Int,
  nMSHRs      : Int,
  nTLBEntries : Int,
)

case class GEMMParams(
  enabled      : Boolean,
  tileSize     : Int,
  dataWidthBits: Int,
  nMACUnits    : Int,
  scratchpadKB : Int,
)

case class CoreParams(
  xlen          : Int,
  resetVector   : Long,
  nHarts        : Int,
  nStages       : Int,
  hasFPU        : Boolean,
  hasCompressed : Boolean,
  hasAtomic     : Boolean,
  hasVector     : Boolean,
  hasSupervisor : Boolean,
  hasMMU        : Boolean,
  hasPMP        : Boolean,
  iCache        : CacheParams,
  dCache        : CacheParams,
  gemm          : GEMMParams,
  physical      : PhysicalParams,
) {
  val xbytes    : Int = xlen / 8
  val pgLevels  : Int = if (xlen == 64) 3 else 2
  val paddrBits : Int = if (xlen == 64) 56 else 34
  val vpnBits   : Int = if (xlen == 64) 27 else 20
  val ppnBits   : Int = if (xlen == 64) 44 else 22

  require(xlen == 32 || xlen == 64,   s"xlen must be 32 or 64, got $xlen")
  require(nHarts >= 1,                s"need at least 1 hart")
  require(nStages >= 3,               s"minimum 3 pipeline stages")
  require(!hasMMU || hasSupervisor,   "MMU requires supervisor mode")
  require(physical.clockPeriodNs > 0, s"clock_period_ns must be > 0")
  require(
    gemm.tileSize > 0 && (gemm.tileSize & (gemm.tileSize - 1)) == 0,
    s"GEMM tile size must be power of 2"
  )
}