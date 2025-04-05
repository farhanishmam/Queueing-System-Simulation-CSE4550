import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.gridspec import GridSpec
import os

def read_simulation_results():
    """Read simulation results from report files"""
    data = {
        'Traffic_Intensity': [],
        'J1_WS1_Queue_Length': [], 'J1_WS2_Queue_Length': [],
        'J2_WS1_Queue_Length': [], 'J2_WS2_Queue_Length': [],
        'J3_WS1_Queue_Length': [], 'J3_WS2_Queue_Length': [],
        'J1_WS1_Customers': [], 'J1_WS2_Customers': [],
        'J2_WS1_Customers': [], 'J2_WS2_Customers': [],
        'J3_WS1_Customers': [], 'J3_WS2_Customers': [],
        'J1_WS1_Queue_Delay': [], 'J1_WS2_Queue_Delay': [],
        'J2_WS1_Queue_Delay': [], 'J2_WS2_Queue_Delay': [],
        'J3_WS1_Queue_Delay': [], 'J3_WS2_Queue_Delay': [],
        'J1_WS1_System_Delay': [], 'J1_WS2_System_Delay': [],
        'J2_WS1_System_Delay': [], 'J2_WS2_System_Delay': [],
        'J3_WS1_System_Delay': [], 'J3_WS2_System_Delay': [],
        'J1_WS1_Utilization': [], 'J1_WS2_Utilization': [],
        'J2_WS1_Utilization': [], 'J2_WS2_Utilization': [],
        'J3_WS1_Utilization': [], 'J3_WS2_Utilization': []
    }
    
    # Read report files for each workstation
    for rho in [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9]:
        data['Traffic_Intensity'].append(rho)
        
        # Read WS1 report
        ws1_file = f'report_1_{rho:.1f}.out'
        if os.path.exists(ws1_file):
            with open(ws1_file, 'r') as f:
                lines = f.readlines()
                for line in lines:
                    if 'Average Number of Customers in the Queue' in line:
                        queue_length = float(line.split(':')[-1].strip())
                        data['J1_WS1_Queue_Length'].append(queue_length)
                        data['J2_WS1_Queue_Length'].append(queue_length)
                        data['J3_WS1_Queue_Length'].append(queue_length)
                    elif 'Average Server Utilization' in line:
                        util = float(line.split(':')[-1].strip())
                        data['J1_WS1_Utilization'].append(util)
                        data['J2_WS1_Utilization'].append(util)
                        data['J3_WS1_Utilization'].append(util)
                    elif 'Average Queueing Delay' in line:
                        delay = float(line.split(':')[-1].strip())
                        data['J1_WS1_Queue_Delay'].append(delay)
                        data['J2_WS1_Queue_Delay'].append(delay)
                        data['J3_WS1_Queue_Delay'].append(delay)
                    elif 'Average System Delay' in line:
                        delay = float(line.split(':')[-1].strip())
                        data['J1_WS1_System_Delay'].append(delay)
                        data['J2_WS1_System_Delay'].append(delay)
                        data['J3_WS1_System_Delay'].append(delay)
                    elif 'Average Number of Customers in the System' in line:
                        customers = float(line.split(':')[-1].strip())
                        data['J1_WS1_Customers'].append(customers)
                        data['J2_WS1_Customers'].append(customers)
                        data['J3_WS1_Customers'].append(customers)
        
        # Read WS2 report
        ws2_file = f'report_2_{rho:.1f}.out'
        if os.path.exists(ws2_file):
            with open(ws2_file, 'r') as f:
                lines = f.readlines()
                for line in lines:
                    if 'Average Number of Customers in the Queue' in line:
                        queue_length = float(line.split(':')[-1].strip())
                        data['J1_WS2_Queue_Length'].append(queue_length)
                        data['J2_WS2_Queue_Length'].append(queue_length)
                        data['J3_WS2_Queue_Length'].append(queue_length)
                    elif 'Average Server Utilization' in line:
                        util = float(line.split(':')[-1].strip())
                        data['J1_WS2_Utilization'].append(util)
                        data['J2_WS2_Utilization'].append(util)
                        data['J3_WS2_Utilization'].append(util)
                    elif 'Average Queueing Delay' in line:
                        delay = float(line.split(':')[-1].strip())
                        data['J1_WS2_Queue_Delay'].append(delay)
                        data['J2_WS2_Queue_Delay'].append(delay)
                        data['J3_WS2_Queue_Delay'].append(delay)
                    elif 'Average System Delay' in line:
                        delay = float(line.split(':')[-1].strip())
                        data['J1_WS2_System_Delay'].append(delay)
                        data['J2_WS2_System_Delay'].append(delay)
                        data['J3_WS2_System_Delay'].append(delay)
                    elif 'Average Number of Customers in the System' in line:
                        customers = float(line.split(':')[-1].strip())
                        data['J1_WS2_Customers'].append(customers)
                        data['J2_WS2_Customers'].append(customers)
                        data['J3_WS2_Customers'].append(customers)
    
    return pd.DataFrame(data)

def plot_queue_lengths(df):
    plt.figure(figsize=(12, 8))
    for job in ['J1', 'J2', 'J3']:
        plt.plot(df['Traffic_Intensity'], df[f'{job}_WS1_Queue_Length'], 
                label=f'Job {job[-1]} - WS1', linestyle='-')
        plt.plot(df['Traffic_Intensity'], df[f'{job}_WS2_Queue_Length'], 
                label=f'Job {job[-1]} - WS2', linestyle='--')
    plt.xlabel('Traffic Intensity (ρ)')
    plt.ylabel('Average Queue Length')
    plt.title('Queue Length vs Traffic Intensity by Job Type')
    plt.grid(True)
    plt.legend()
    plt.savefig('queue_length_vs_traffic.png', dpi=300, bbox_inches='tight')
    plt.close()

def plot_customers_in_queue(df):
    plt.figure(figsize=(12, 8))
    for job in ['J1', 'J2', 'J3']:
        plt.plot(df['Traffic_Intensity'], df[f'{job}_WS1_Customers'], 
                label=f'Job {job[-1]} - WS1', linestyle='-')
        plt.plot(df['Traffic_Intensity'], df[f'{job}_WS2_Customers'], 
                label=f'Job {job[-1]} - WS2', linestyle='--')
    plt.xlabel('Traffic Intensity (ρ)')
    plt.ylabel('Average Number of Customers in Queue')
    plt.title('Customers in Queue vs Traffic Intensity by Job Type')
    plt.grid(True)
    plt.legend()
    plt.savefig('customers_vs_traffic.png', dpi=300, bbox_inches='tight')
    plt.close()

def plot_queue_delays(df):
    plt.figure(figsize=(12, 8))
    for job in ['J1', 'J2', 'J3']:
        plt.plot(df['Traffic_Intensity'], df[f'{job}_WS1_Queue_Delay'], 
                label=f'Job {job[-1]} - WS1', linestyle='-')
        plt.plot(df['Traffic_Intensity'], df[f'{job}_WS2_Queue_Delay'], 
                label=f'Job {job[-1]} - WS2', linestyle='--')
    plt.xlabel('Traffic Intensity (ρ)')
    plt.ylabel('Average Queue Delay')
    plt.title('Queue Delay vs Traffic Intensity by Job Type')
    plt.grid(True)
    plt.legend()
    plt.savefig('queue_delay_vs_traffic.png', dpi=300, bbox_inches='tight')
    plt.close()

def plot_system_delays(df):
    plt.figure(figsize=(12, 8))
    for job in ['J1', 'J2', 'J3']:
        plt.plot(df['Traffic_Intensity'], df[f'{job}_WS1_System_Delay'], 
                label=f'Job {job[-1]} - WS1', linestyle='-')
        plt.plot(df['Traffic_Intensity'], df[f'{job}_WS2_System_Delay'], 
                label=f'Job {job[-1]} - WS2', linestyle='--')
    plt.xlabel('Traffic Intensity (ρ)')
    plt.ylabel('Average System Delay')
    plt.title('System Delay vs Traffic Intensity by Job Type')
    plt.grid(True)
    plt.legend()
    plt.savefig('system_delay_vs_traffic.png', dpi=300, bbox_inches='tight')
    plt.close()

def plot_server_utilization(df):
    plt.figure(figsize=(12, 8))
    for job in ['J1', 'J2', 'J3']:
        plt.plot(df['Traffic_Intensity'], df[f'{job}_WS1_Utilization'], 
                label=f'Job {job[-1]} - WS1', linestyle='-')
        plt.plot(df['Traffic_Intensity'], df[f'{job}_WS2_Utilization'], 
                label=f'Job {job[-1]} - WS2', linestyle='--')
    plt.xlabel('Traffic Intensity (ρ)')
    plt.ylabel('Server Utilization')
    plt.title('Server Utilization vs Traffic Intensity by Job Type')
    plt.grid(True)
    plt.legend()
    plt.savefig('utilization_vs_traffic.png', dpi=300, bbox_inches='tight')
    plt.close()

def generate_statistics_report(df):
    with open('statistics_report.txt', 'w') as f:
        f.write("Job Shop Model Simulation Statistics Report\n")
        f.write("=========================================\n\n")
        
        for job in ['J1', 'J2', 'J3']:
            f.write(f"Job {job[-1]} Statistics:\n")
            f.write("------------------------\n")
            
            # Queue Length Statistics
            f.write("1. Queue Length Statistics:\n")
            f.write(f"   Workstation 1:\n")
            f.write(f"   - Maximum queue length: {df[f'{job}_WS1_Queue_Length'].max():.2f}\n")
            f.write(f"   - Average queue length: {df[f'{job}_WS1_Queue_Length'].mean():.2f}\n")
            f.write(f"   Workstation 2:\n")
            f.write(f"   - Maximum queue length: {df[f'{job}_WS2_Queue_Length'].max():.2f}\n")
            f.write(f"   - Average queue length: {df[f'{job}_WS2_Queue_Length'].mean():.2f}\n\n")
            
            # Customer Statistics
            f.write("2. Customer Statistics:\n")
            f.write(f"   Workstation 1:\n")
            f.write(f"   - Maximum customers: {df[f'{job}_WS1_Customers'].max():.2f}\n")
            f.write(f"   - Average customers: {df[f'{job}_WS1_Customers'].mean():.2f}\n")
            f.write(f"   Workstation 2:\n")
            f.write(f"   - Maximum customers: {df[f'{job}_WS2_Customers'].max():.2f}\n")
            f.write(f"   - Average customers: {df[f'{job}_WS2_Customers'].mean():.2f}\n\n")
            
            # Delay Statistics
            f.write("3. Delay Statistics:\n")
            f.write(f"   Workstation 1:\n")
            f.write(f"   - Maximum queue delay: {df[f'{job}_WS1_Queue_Delay'].max():.2f}\n")
            f.write(f"   - Average queue delay: {df[f'{job}_WS1_Queue_Delay'].mean():.2f}\n")
            f.write(f"   - Maximum system delay: {df[f'{job}_WS1_System_Delay'].max():.2f}\n")
            f.write(f"   - Average system delay: {df[f'{job}_WS1_System_Delay'].mean():.2f}\n")
            f.write(f"   Workstation 2:\n")
            f.write(f"   - Maximum queue delay: {df[f'{job}_WS2_Queue_Delay'].max():.2f}\n")
            f.write(f"   - Average queue delay: {df[f'{job}_WS2_Queue_Delay'].mean():.2f}\n")
            f.write(f"   - Maximum system delay: {df[f'{job}_WS2_System_Delay'].max():.2f}\n")
            f.write(f"   - Average system delay: {df[f'{job}_WS2_System_Delay'].mean():.2f}\n\n")
            
            # Utilization Statistics
            f.write("4. Utilization Statistics:\n")
            f.write(f"   Workstation 1:\n")
            f.write(f"   - Maximum utilization: {df[f'{job}_WS1_Utilization'].max():.2f}\n")
            f.write(f"   - Average utilization: {df[f'{job}_WS1_Utilization'].mean():.2f}\n")
            f.write(f"   Workstation 2:\n")
            f.write(f"   - Maximum utilization: {df[f'{job}_WS2_Utilization'].max():.2f}\n")
            f.write(f"   - Average utilization: {df[f'{job}_WS2_Utilization'].mean():.2f}\n\n")
            
            f.write("----------------------------------------\n\n")

def main():
    # Read simulation results
    df = read_simulation_results()
    
    # Generate plots
    plot_queue_lengths(df)
    plot_customers_in_queue(df)
    plot_queue_delays(df)
    plot_system_delays(df)
    plot_server_utilization(df)
    
    # Generate statistics report
    generate_statistics_report(df)
    
    print("Analysis complete! Generated files:")
    print("- queue_length_vs_traffic.png")
    print("- customers_vs_traffic.png")
    print("- queue_delay_vs_traffic.png")
    print("- system_delay_vs_traffic.png")
    print("- utilization_vs_traffic.png")
    print("- statistics_report.txt")

if __name__ == "__main__":
    main() 