# PIDSim
PIDSim is a tool for simulating and visualizing the tuning of PID controllers. It is intended as a teaching tool for new FRC robotics programmers, to allow them to familiarize themselves with PID controllers and gain an intuitive understanding of how they work and the process of tuning them.

<p align="center">
  <img src="https://raw.githubusercontent.com/brendanburkhart/PIDSim/master/readme-resources/inputgraph.png" height="250" title="Input and Setpoint">
  <img src="https://raw.githubusercontent.com/brendanburkhart/PIDSim/master/readme-resources/outputgraph.png" height="250" title="Output Breakdown">
</p>

On the left is an example screenshot of a real-time graph of the PID input and setpoint vs. time. On the right is a real-time breakdown of the PID output into its proportional, integral, and derivative components.

<p align="center">
  <img src="https://raw.githubusercontent.com/brendanburkhart/PIDSim/master/readme-resources/linear.png" height="250" title="Linear PID Sim">
  <img src="https://raw.githubusercontent.com/brendanburkhart/PIDSim/master/readme-resources/angular.png" height="250" title="Angular PID Sim">
</p>

On the left is a simulation of a PID-controlled brick. The brick is dragged down by gravity and affected by air resistance, and the PID controller outputs a force that acts on the brick.
On the right is a simulation of a continuous angular PID control model, for uses like swerve module angular control.

---

PIDSim is built using the Qt5 GUI toolkit from Qt (https://www.qt.io/) and is based in part on the work of the Qwt project (http://qwt.sf.net). To comply with the licensing requirements of Qt and Qwt, and to allow PIDSim to be distributed in a statically-linked form, PIDSim is licensed under the LGPL and all source code is available in this repository.

[input]: https://github.com/brendanburkhart/PIDSim/raw/master/readme-resources/inputgraph.png "Input Plot"
[output]: https://github.com/brendanburkhart/PIDSim/raw/master/readme-resources/outputgraph.png "Output Plot"
[linear]: https://github.com/brendanburkhart/PIDSim/raw/master/readme-resources/linear.png "Linear Model"
[angular]: https://github.com/brendanburkhart/PIDSim/raw/master/readme-resources/angular.png "Angular Model"
