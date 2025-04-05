import subprocess
import os

def compile_simulation():
    """Compile the C++ simulation code"""
    print("Compiling simulation code...")
    result = subprocess.run(['g++', '-o', 'simulation', 'main.cpp', 'server.cpp', 'queue.cpp', 'event.cpp', 'scheduler.cpp'],
                          capture_output=True, text=True)
    if result.returncode != 0:
        print("Compilation failed:")
        print(result.stderr)
        return False
    print("Compilation successful!")
    return True

def run_simulation(traffic_intensity):
    """Run the simulation for a given traffic intensity"""
    print(f"Running simulation for traffic intensity {traffic_intensity:.1f}...")
    result = subprocess.run(['./simulation', str(traffic_intensity)], 
                          capture_output=True, text=True)
    if result.returncode != 0:
        print(f"Simulation failed for traffic intensity {traffic_intensity:.1f}:")
        print(result.stderr)
        return False
    print(f"Simulation completed for traffic intensity {traffic_intensity:.1f}")
    return True

def main():
    # Compile the simulation code
    if not compile_simulation():
        return
    
    # Run simulations for different traffic intensities
    traffic_intensities = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9]
    for rho in traffic_intensities:
        if not run_simulation(rho):
            print(f"Failed to run simulation for traffic intensity {rho:.1f}")
            return
    
    print("All simulations completed successfully!")

if __name__ == "__main__":
    main() 