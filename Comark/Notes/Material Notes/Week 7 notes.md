# Parallelism
## Characterizations of Parallelism
### Microscopic vs macroscopic
![[microscopic parralelism.png]]
More specific, microscopic refers to parallelism within a component for example a processor. macroscopic parallelism is within a larger system.
### Symmetric vs asymmetric
*Symmetric* is used to characterize a design that uses replications of identical elements. For example having 4 identical processors is symmetric, but if each of them is a different kind of processor, it is called *Asymetric.*
### Fine-grain vs coarse-grain
*fine-grain* is parallelism on the individual instructions and data element, *coarse-grain* is parallelism between programs and large level data.
### Explicit vs implicit
*Implicit parralelism* is when the parralelism is handled automatic wheras *explicit parralelism* is where the programmer must control each parallel unit.
## Types of parallel Architectures
**Flynn classification:**
![[Flynn classification.png]]
### Single Instruction Single Data (SISD)
This architecture does not support macroscoping parralelism.
Often called "sequential architecture" or "uniprocessor".
### Single Instruction Multiple Data (SIMD)
This specifies a system where each instruction specifies a single operation. However this instruction can affect multiple data items at the same time.
### Multiple Instructions Multiple Data
Each processor performs independent computations at the same time.


# Data Pipelining
## The concept of pipelining
![[Example of Pipelining.png]]
![[Characteristics of Pipelines.png]]
Above is a figure showing the different characteristics for a pipeline.
- **Hardware Or Software Implementation**
	Pipelines can be implemented on hardware og software level.
- **Large or Small scale**
	A pipeline can be small if it contains a few stages or it can be large if it contains many stages around a 100 stages
- **Syncronous or Asynchronous flow**
	A synchronious pipeline works like an assembly line. Everything works with a clock, and each stage is working on some specific data.
	
	Asynchronious allows a station to forward information at any time, not using a clock. Popular for systems where some stages takes longer than other.
- **Buffered or Unbuffered Flow**
	A buffer can be placed between stages. Usefull for asynchronous pipelines in which information is placed in bursts.
- **Finite Chunks or Continous Bit Streams**
	The data the pipeline is working on can be a sequence of small data items. Or A contentious long stream of data fx a contentious video feed.
-  **Automatic Data Feed or Manual Data Feed**
	Some Pipelines have have each section move the data to the next step themselves. Other have a separate program to do the moving of data items.
- **Serial or Parallel Path**
	*The large arrows in Figure 19.1 imply that a parallel path is used to move information from one stage to another. Although some hardware pipelines do use a parallel path, many use serial communication. Furthermore, communication between stages need not consist of conventional communication (e.g., stages can use a computer network or shared memory to communicate).*
- **Homogeneous or heterogeneous stages**
	A pipeline can be constructed so all stages is constructed the same way or choose a type of hardware that is appropiate for each stage.
## Hardware Pipelining
There are two distinct uses of hardware pipelins:
- **Instruction Pipeline**
	Instruction pipelines is a pipeline to decode and execute instructions. This means that a *Instruction pipeline* is a pipeline where the informations consists of machine instructions.
- **Data Pipeline**
	This pipeline is designed to pass data from stage to stage.
	![[A data pipeline.png]]
	![[Data pip.png]]
## When Pipelining can be used
There are three conditions to be met for a pipeline to perform faster than a single processor.
- **Partionable problem**
	It must be possible to partition processing into stages that can be computed independent of one another. Computations that employ a sequence of steps work well in a pipeline, but computations that involve iteration often do not.
- **Equivalent processor speed**
	It should be obvious that if the processors used in a data pipeline are slow enough, the overall time required to perform a computation will be much higher than on a single processor. Processors in the pipeline do not need to be faster than the single processor. We merely require that each processor in the pipeline is approximately as fast as the single processor. That is, the time required to perform a given computation on a pipeline processor must not exceed the time required to perform the same computation on the single processor.
- **Low overhead data movement.**
	In addition to the time required to perform computation, a data pipeline has an additional overhead: the time required to move a data item from one stage of the pipeline to the next. If moving the data incurs extremely high latency, pipelining will not increase performance.

# Power And Energy
## Definition of Power
*Power* is here defined to be the rate at which energy is consumed. Also taking definitions from physics:
$$
P(t)=V(T)\cdot I(T)
$$
## Definitions of Energy
The total *energy* consumed over a given time (from definition of power).

## Power consumption by a Digital circuit
Given that all digital circuits is created from logic gates and that these are made up of transistors, the transistors consume power in one of two ways.
- **Switching or dynamic power ($P_s,P_d$)**
	This refers to change in output in response with input.
- **Leakage power ($P_{leak}$)**
	We cannot completely keep electric charges, therefore there are always some leakage from the transistor.
	![[Leakage power.png]]![[leak.png]]

	