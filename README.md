# Simulation of Queueing Systems

*This repository contains my implementation of several queueing systems for the lab course CSE: 4550 Simulation and Modeling Lab.*

## Overview

- **Single Server Queueing System:** A system where one server processes items or customers from a single queue following first-come first-serve.
- **Multi Server Queueing System:** Multiple independent servers processing the items.
  - **Parallel Servers Single Queue:** Multiple servers will simultaneously serve a single queue.
  - **Parallel Servers Multi Queues:** Items or customers from multiple queues will be processed whenever a server is free.
  - **Sequential Servers (Multi-Layer/Tandem Queue):** Customer or item will be passed through multiple stages, each with its server and in a sequential manner.
- **Job Shop Model:** A system where multiple servers with their queues will process customers or items in a non-sequential manner based on the requirement of that customer or item.

## Code Overview

The simulation includes handling arrival and departure events for tasks in a server environment, using a scheduler to manage the sequence of events, and a queue to manage tasks waiting to be processed. The code has been written in `C++`.

- `main.cpp`: The entry point of the application. This file initializes the scheduler and server, runs the simulation, and generates a report.
- `Event`: Derived classes `ArrivalEvent` and `DepartureEvent`. These classes represent different types of events that occur within the simulation.
- `Queue`: Manages the queue of tasks or events waiting to be processed by the server.
- `Scheduler`: Responsible for managing and triggering events in the correct order.
- `Server`: Simulates a server processing events. It includes methods for initializing the server, processing events, and generating output.
- `Trace`: A sample output file generated by the simulation, showing a trace of events with timestamps, event types, and other relevant data.

## Getting Started

### Prerequisites
- C++ compiler (e.g., g++)
- Terminal or Command Prompt

### Installation

1. Clone this repository.

   ```
   git clone https://github.com/farhanishmam/Queueing-System-Simulation-CSE4550.git
   ```
   
3. Navigate to the project directory. `SimulationType` is a placeholder for the type of simulation system that you will run.

    ```
   cd Queueing-System-Simulation-CSE4550/SimulationType
    ```

### Building the Project

To compile the project, run the following command in your terminal.

```
g++ main.cpp -o simulation
```

### Run

After compiling, you can run the simulation.

```
./simulation
```

### Output

A `report.out` file will be generated as the output of the simulation.
  
## Data Analysis 

The data analysis and visualization has been done using Microsoft Excel. The data has been collected from the `trace.out` and the `report.out` files. Reports on the analysis have also been included in this repo.

*Sample visualization of the comparison of the average number of customers in the queue in analytical and simulated systems.*

<img src="Assets/sampleResult.PNG" alt="Alt text" width="500"/>

## Contributing

Feel free to contribute to this project by:
- Fork the repository
- Create your feature branch `git checkout -b feature/AmazingFeature`
- Commit your changes `git commit -m AmazingFeatureCommit`
- Push to the branch `git push origin feature/AmazingFeature`
- Open a Pull Request
  
## License

Distributed under the MIT License. See LICENSE for more information.
