import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

def read_trace_file(filename):
    data = []
    with open(filename, 'r') as f:
        for line in f:
            if line.startswith(('a', 's', 'd')):
                parts = line.strip().split('\t')
                if len(parts) >= 5:
                    data.append({
                        'event': parts[0],
                        'time': float(parts[1]),
                        'id': int(parts[2]),
                        'status': int(parts[3]),
                        'queue_size': int(parts[4])
                    })
    return pd.DataFrame(data)

def read_report_file(filename):
    data = {}
    with open(filename, 'r') as f:
        for line in f:
            if ':' in line:
                key, value = line.split(':')
                data[key.strip()] = float(value.strip())
    return data

def plot_queue_lengths(trace1, trace2):
    plt.figure(figsize=(12, 6))
    
    # Plot queue lengths over time
    plt.plot(trace1[trace1['event'] == 'a']['time'], 
             trace1[trace1['event'] == 'a']['queue_size'], 
             'b-', label='Workstation 1 Queue')
    plt.plot(trace2[trace2['event'] == 'a']['time'], 
             trace2[trace2['event'] == 'a']['queue_size'], 
             'r-', label='Workstation 2 Queue')
    
    plt.xlabel('Simulation Time')
    plt.ylabel('Queue Length')
    plt.title('Queue Lengths Over Time')
    plt.legend()
    plt.grid(True)
    plt.savefig('queue_lengths.png')
    plt.close()

def plot_server_utilization(report1, report2):
    plt.figure(figsize=(8, 6))
    
    # Plot server utilization
    stations = ['Workstation 1', 'Workstation 2']
    utilizations = [report1['Average Server Utilization'], report2['Average Server Utilization']]
    
    plt.bar(stations, utilizations)
    plt.xlabel('Workstation')
    plt.ylabel('Server Utilization')
    plt.title('Server Utilization Comparison')
    plt.ylim(0, 1)
    plt.grid(True)
    plt.savefig('server_utilization.png')
    plt.close()

def plot_system_delays(report1, report2):
    plt.figure(figsize=(8, 6))
    
    # Plot system delays
    stations = ['Workstation 1', 'Workstation 2']
    queue_delays = [report1['Average Queueing Delay'], report2['Average Queueing Delay']]
    system_delays = [report1['Average System Delay'], report2['Average System Delay']]
    
    x = np.arange(len(stations))
    width = 0.35
    
    plt.bar(x - width/2, queue_delays, width, label='Queueing Delay')
    plt.bar(x + width/2, system_delays, width, label='System Delay')
    
    plt.xlabel('Workstation')
    plt.ylabel('Delay Time')
    plt.title('Queueing and System Delays')
    plt.xticks(x, stations)
    plt.legend()
    plt.grid(True)
    plt.savefig('system_delays.png')
    plt.close()

def main():
    # Read trace files
    trace1 = read_trace_file('trace_1.out')
    trace2 = read_trace_file('trace_2.out')
    
    # Read report files
    report1 = read_report_file('report_1.out')
    report2 = read_report_file('report_2.out')
    
    # Generate plots
    plot_queue_lengths(trace1, trace2)
    plot_server_utilization(report1, report2)
    plot_system_delays(report1, report2)

if __name__ == "__main__":
    main() 