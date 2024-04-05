# **Memory and storage**
## **Definition of memory**
**from an architects point of view a memory is seen as a solid-state digital device that provides storage for data values.**
## **The key aspect of memory**
**There is two choices when designing a memory system.**

### **Technology**
***Technology* refers to the properties of the underlying hardware mechanism used to construct the memory system.**
***Memory technology* refers to the lowest level hardware pieces.**
### **Organization**
***Organization* refers to the way the underlying technology is used to form a working system.** 
***Memory organization* refers to how the pieces are combined to form a storage system.**


## **Four characteristics of Memory Technologies**

### **Memory Volatility**
**A memory is *volatile* if the content of the memory disappear when power is removed. *Non volatile* is the oppisite. RAM is volatile and SSD is Non volatile.**
### **Memory Access paradigm**
***Random access* all values in the memory is acessed in a fixed amount of time. This is what RAM (random access memory) is using.**
***Sequential access* Here access to the data depends on the location in memory of the data. This could for example be memories following the FIFO principle**
### **Permanence of values**
***ROM* read only memory.**
***PROM* programmable read only memory**
### **Primary and secondary memory**
***Primary memory*   fast, volatile, internal main memory.**
***Secondary memory* SSD is used for secondary storage.**

## **The Importance of a Memory Hierarchy**
**![[memory hierachy principle.png]]**


# **Physical Memory and Physical Addressing**
## **Static vs Dynamic RAM technologies**
- **Static Ram (SRAM)** 
	- **Easiest to for programmers to understand.**
	- **Stores each data bit in a *latch* as discussed in chapter 2**
	- **Has high power consumption**
- **Dynamic Ram (DRAM)**
	- **Build with capacitors that slowly lose charge, if enough time passes 1 becomes 0.**
	- **Imperfect physical Memory system**
	- **Uses a refresh circuit to read and write bits to ensure that memory is not lost.**
	- **More used than SRAM**
## **The two primary Measures of Memory Tecnology**
### **Density**
**Strict sense refers to number of memory cells per square area of silicon.**

**Often instead refers to how many bits that can be represented on a standard size chip.**

**High density is desirable due to it meaning more memory can be held at the same physical space. Although this means higher heat generation.**
### **Latency and Cycle times**
**Focuses on speed, meaning how fast the memory can respond to requests,**
**![[Hardware memory access.png]]**
**![[Latency is insufficient.png]]**
**![[read write cycle.png]]**

## **Words, Physical Addresses, And Memory Transfers**
**A block of N bits is sometimes called a *Word* and the transfer size is called *Word Size* or *"width of a word"*.**
***"Physical Memory Address"* is the unique "index" in the memory where the data is stored.**
**![[words stored in physical address.png]]**

**The controller for physical memory access supports two operations: read and write.**
**![[Physical memory.png]]**
## **Byte Addressing and mapping Bytes to Words**
**![[Byte adresses.png]]**
**If one wanted read the byte address 17, the controller must issue a read request for the word 4 and then the second byte.**
**If one wanted to write byte 17. The controller would have to rewrite the rest of the word.**
## **Memory size and Address space**
**A string of k bits can represent $2^{k}$ Values.**
# **Caches and Caching**
## **Definition of Caching**
**Refers to a optimazation technique to improve performance of hardware or software that retrieves information.**
**A cache is placed between the data storage and the requester.**
**![[Model of cache.png]]**
## **Characteristics of a cache**
- **Small**
	- To keep economic cost low, the amount of storage in a cache is much slower.
	- Typically less that 10% of the storage of the actual data storage.
- **Active**
	- Deciding which items to keep in cache.
	- Checks if requested data is in cache or should be retrieved from data storage.
 - **Transparent**
	 - Has the exact same interface as the data storage.
 - **Automatic**
	 - Uses an algorithm on how to handle a sequence of requests and uses requests to determine how to manage the cache.
## Terminology
*Cache hit* or *"abbreviated hit"* is when the data needed is already in the cache.
*Cache miss* or *"abbreviated miss"* is when the data is not in the cache and should be retrieved from the data storage.
*"high locality of reference"* is when a sequence of requests contain repetitions of the same data or memory references.
*"low locality of reference"* is the opposite of this.
## Cache replacement Policy
- Increase the cache size
	- A larger cache can store more data items before it needs to remove data items.
- Improve the replacement policy
	- Make sure that often referenced data items is not deleted as often.


## LRU Algorithm
This algorithm have a list. Whenever a item is used in the cache it moves to the front of the list. This way the data that are used least gets removed first.
![[LRU algorithm.png]]
## Multilevel Cache Hierachy
![[Multilevel cache.png]]
![[Additional cache.png]]
## L1, L2 and L3
![[L1,l2,L3.png]]
![[Size of l1,l2,l3.png]]
