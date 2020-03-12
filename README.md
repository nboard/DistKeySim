# ADAK - Distributed Keying Distribution

## Build Instructions
1) `mkdir build`
2) `cd build`
3) `cmake .. -DBUILD_TESTING=0`
    - **Note**: The `-DBUILD_TESTING=0` flag disables building unit tests. Building the unittests adds a decent bit of
    time to a clean compile and is not currently working.
4) `make -j4 -DBUILD_TESTING=0`
5) The build will be completed at this point, executable is `bin/`

NOTE: a script is included in the scripts folder in this repository but is not guaranteed to work on every system. It is an example script that is used with the development environment. 

## Configuration for simulation
The project is configurable via the Config class (`include/config.hpp`, `src/config.cpp`) via JSON. The simulation will
look in the same directory as the executable for `config.json`.

There are 3 connection modes. To change the connection mode, alter connModeStr in the config file. The three options for the connection mode are: `"full"`, `"partial"`, and `"single"`.
* Full connection mode: creates a full connected graph out of the nodes.
* Partial connection mode: randomly connected graph (dependent on Config.visiblePeer's percentage connected).
* Single connection mode: randomly connected MST (one connection only per node determined on creation).

### Example `config.json`
```json
{
    "numNodes": 10,
    "connModeStr": "full",
    "csvOutputPath": "out.csv",
    "creationRate": 1.0,
    "networkScale": 0.3
}
```
## Configuration for visual analytics
The visualizations created by the project require Python as well as the `pandas` and `plotly` modules to be installed. This assumes that PIP has been installed to manage Python packages.
1) `pip install pandas`
2) `pip install plotly==4.5.4`

Alternatively, if pip does not work well on your machine, here are alternate instructions. 
1) `sudo-apt install python3-pandas`

For more information on [plotyl](https://plot.ly/python/getting-started/).
For more information on [pandas](https://pandas.pydata.org/pandas-docs/stable/getting_started/install.html).

## Configuration for User Interface 
(also requires the configuration for visual analytics for the visual analytics to work properly through the UI)
The User Interface created requires Python as well as the tkinter interface and sshpass. To install tkinter and sshpass on linux use: 
1) `sudo apt-get install python3-tk`
2) `sudo apt install sshpass`

## User Interface
Different parameters in the simulation are controlled by inputs from the UI. Below is a description of each of those inputs as well as how they will be used. Several of these inputs are used as parameters into statistical distributions from which we sample. We describe the distributions and their parameters.
 
 * **Visible Peers \(connected % \)** : *This input field only influences the simulation when the connection mode is set to `partial` in the config file.* When a new node is added, this is the \% chance that the new node is connected to another node. For example, if you desired there to be a 75\% chance that a new node is connected to another node, then you would enter 75. 

In the simulation, nodes are randomly selected to disconnect and reconnect. The disconnect/reconnect times are randomly generated from a geometric distribution, and the disconnect/reconnect times are measured in time steps (each time step represents a second of "real time" passing; currently the time step is controlled by the TIMESTEP variable which equals 1). Nodes that are selected to disconnect/reconnect are handed a message that describes when to disconnect and then subsequently reconnect.

+ **Lambda 1 (time offline)** : Expected time for nodes to go from online to offline in (real world) seconds \(&lambda;<sub>1</sub>\). For each selected node, a time in seconds is randomly generated by sampling from a distribution that is geom\(&lambda;<sub>1</sub>\/TIMESTEP\). This value represents in how many seconds from the current time the node will disconnect.
+ **Lambda 2 (time online)** : Expected time for nodes to go from offline back to online in (real world) seconds \(&lambda;<sub>2</sub>\). For each selected node, a time in seconds is randomly generated by sampling from a distribution that is geom(&lambda;<sub>2</sub>\/TIMESTEP). This value represents the total amount of time the node will remain disconnected.  

 * **Lambda 3 (time between creating objects)** : Expected time for nodes between creating objects; how expected much time passes for nodes between creating one object and creating the next object \(&lambda;<sub>3</sub>\). Upon creation of each node, a time in seconds is randomly generated by sampling from a distribution that is geom\(&lambda;<sub>3</sub>\/TIMESTEP\). This time represents the amount of time this node takes between creating objects.
 * ** Chunkiness (\# of keys to shift) ** :
 * **Heartbeat Period** : Distance in time in seconds between two consecutive hearbeats. A heartbeat is a message that is broadcasted to all connected nodes to indicate that a particular node is online and connected. A heartbeat is different from a time step in that a time step is a unit of time passage in the simulation. In this simulation a real world clock is used with each time step representing a second of "real-time" passing.
 
 ## Visualizations
 It's important to know what you're looking at when analyzing the analytics that are produced. 
 1.
 2.
 3.

## Branches
We kept master as our stable branch. We worked solely on develop and then merged things that are fully functional to
master. It is not 100% functionality, release candidate level, but they are stable and will compile/run without trouble.

# Class Diagram Link
https://drive.google.com/file/d/1Czub9HZ2K6M838bzI8IzAxKO0jYjQAwj/view?usp=sharing

# MEMES
<img src="/memes/Compiler_Errors.jpg" height="400" />
<img src="/memes/Prayer.jpg" height="400" />
<img src="/memes/google_programmer.jpg" height="400" />
<img src="/memes/geek_vs_programmers.jpg" height="400" />
<img src="/memes/memeForLightSys.png" height="400" />
<img src="/memes/meme1.jpg" height="400" />
<img src="/memes/meme2.jpg" height="400" />
<img src="/memes/meme3.png" height="400" />
<img src="/memes/meme4.png" height="400" />                                        
<img src="/memes/meme5.png" height="400" />
<img src="/memes/meme6.jpg" height="400" />
