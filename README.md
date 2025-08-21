# 🚗 Parking Lot Solver – BFS Algorithm

## 🖊 Author
**Lefkopoulos Miltiadis**

---

## 📄 Project Description

This project implements a solution to the **Parking Lot Clearance Problem** using **Breadth-First Search (BFS)** in C++.

### 🅿️ Problem Overview

- The parking lot is represented as an `M×N` grid.
- Each cell can contain:
  - 🧱 **Obstacles** – cannot be moved into
  - 🚘 **Cars** – with either **North/South (vertical)** or **East/West (horizontal)** orientation
  - ⬜ **Empty spaces** – available for car movement

**Goal:** Clear all cars from the parking lot while respecting movement rules.

**Allowed Moves:**
- Vertical cars: move ⬆️ up or ⬇️ down
- Horizontal cars: move ⬅️ left or ➡️ right
- Moves are only valid if the destination cell is empty

---

## 🛠 Problem Representation

Cars are represented using a `pair<pair<int,int>, bool>`:

```cpp
pair<pair<int, int>, bool> car;
```

Where:

(x, y) – coordinates of the car

horizontal – true for horizontal, false for vertical

The Maze class stores:

- 📋 Vector of cars

- 🧱 Positions of obstacles (including cars)

- 🔙 The previous move

- 🧩 Previous maze state (used to reconstruct the solution path)

## 🔍 BFS Implementation

Two **BFS** variations are implemented:

- **BFS()** – Uses a vector to store child states.

- **BFS2()** – Uses an unordered_map to track visited states.

In **BFS2()**, each maze state is encoded as a long long key representing the coordinates and orientations of all cars, allowing fast lookups.

🚦 Expansion of Moves

For each car, possible moves are checked:

Horizontal cars:

- ⬅️ goLeft()

- ➡️ goRight()

Vertical cars:

- ⬆️ goUp()

- ⬇️ goDown()

Each move checks if:

The car has reached the edge (and exits the maze)

The target cell is free (updates the obstacle table accordingly)