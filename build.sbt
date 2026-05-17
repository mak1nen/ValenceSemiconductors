val chiselVersion     = "7.2.0"
val chiselTestVersion = "6.0.0"
val scalaTestVersion  = "3.2.19"

ThisBuild / organization := "com.valence"
ThisBuild / version      := "0.1.0-SNAPSHOT"
ThisBuild / scalaVersion := "2.13.17"

ThisBuild / scalacOptions ++= Seq(
  "-language:reflectiveCalls",
  "-deprecation",
  "-feature",
  "-Xcheckinit",
  "-Ymacro-annotations",
)

lazy val root = (project in file("."))
  .aggregate(hardware)
  .settings(
    name := "valence-riscv",
    Compile / unmanagedSourceDirectories := Seq.empty,
    Test    / unmanagedSourceDirectories := Seq.empty,
  )

lazy val hardware = (project in file("hardware"))
  .settings(
    name := "valence-riscv-hw",

    addCompilerPlugin(
      "org.chipsalliance" % "chisel-plugin" % chiselVersion cross CrossVersion.full
    ),

    Compile / scalaSource       := baseDirectory.value / "src" / "main" / "scala",
    Test    / scalaSource       := baseDirectory.value / "src" / "test" / "scala",
    Compile / resourceDirectory := baseDirectory.value / "src" / "main" / "resources",

    libraryDependencies ++= Seq(
      "org.chipsalliance" %% "chisel"     % chiselVersion,
      "edu.berkeley.cs"   %% "chiseltest" % chiselTestVersion % Test,
      "org.scalatest"     %% "scalatest"  % scalaTestVersion  % Test,
    ),

    Test / testOptions       += Tests.Argument(TestFrameworks.ScalaTest, "-oDF"),
    Test / parallelExecution := false,
    Test / fork              := true,
    Test / javaOptions       ++= Seq("-Xmx4G", "-Xss8M"),

    Compile / mainClass := Some("valence.soc.SoCElaborate"),
  )

addCommandAlias("elaborate", "hardware/run")