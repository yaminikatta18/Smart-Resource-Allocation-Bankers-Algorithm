# Banker's Algorithm

## Objective
To prevent unsafe resource allocation by checking whether
all processes can finish in a safe order.

## Data Structures
- Available: Currently available resources.
- Allocation: Resources assigned to processes.
- Maximum: Maximum resources required by processes.
- Need: Remaining resources required by processes.

## Formula
Need = Maximum - Allocation

## Safety Algorithm
1. Copy Available into Work.
2. Mark all processes unfinished.
3. Find a process whose Need is less than or equal to Work.
4. Simulate completion and release its allocated resources.
5. Repeat until all processes finish or no process can proceed.
6. If every process finishes, the state is safe.

## Resource Request Algorithm
1. Check whether the request exceeds the process's Need.
2. Check whether sufficient resources are Available.
3. Temporarily allocate the requested resources.
4. Run the safety algorithm.
5. Grant the request if the state remains safe.
6. Otherwise, restore the original state and reject the request.
