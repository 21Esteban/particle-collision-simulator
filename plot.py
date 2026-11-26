# lee simulation.txt y grafica las trayectorias y los choques
# se corre con: python plot.py
import matplotlib.pyplot as plt
import matplotlib.patches as patches

width, height = 800, 600
obstacles = []
paths = {}   # id -> ([x], [y])
collisions = {"wall": [], "obstacle": [], "merge": []}

with open("simulation.txt") as f:
    for line in f:
        parts = line.split()
        if not parts or parts[0] == "#":
            continue
        if parts[0] == "B":
            width, height = float(parts[1]), float(parts[2])
        elif parts[0] == "O":
            obstacles.append([float(v) for v in parts[2:5]])
        elif parts[0] == "P":
            pid = int(parts[2])
            paths.setdefault(pid, ([], []))
            paths[pid][0].append(float(parts[3]))
            paths[pid][1].append(float(parts[4]))
        elif parts[0] == "C":
            kind = parts[2]
            # la posicion va despues del lado
            if kind == "wall":
                x, y = float(parts[5]), float(parts[6])
            elif kind == "obstacle":
                x, y = float(parts[6]), float(parts[7])
            else:
                x, y = float(parts[5]), float(parts[6])
            collisions[kind].append((x, y))

fig, ax = plt.subplots(figsize=(10, 7.5))
ax.add_patch(patches.Rectangle((0, 0), width, height, fill=False, linewidth=2))
for x, y, size in obstacles:
    ax.add_patch(patches.Rectangle((x, y), size, size, color="gray"))

for pid, (xs, ys) in paths.items():
    ax.plot(xs, ys, linewidth=1, label=f"particle {pid}")
    ax.plot(xs[0], ys[0], "o", color="black", markersize=4)

styles = {"wall": ("s", "blue"), "obstacle": ("^", "orange"), "merge": ("*", "red")}
for kind, points in collisions.items():
    if points:
        marker, color = styles[kind]
        xs = [p[0] for p in points]
        ys = [p[1] for p in points]
        ax.scatter(xs, ys, marker=marker, color=color, s=60, zorder=3, label=f"collision: {kind}")

ax.set_xlim(-10, width + 10)
ax.set_ylim(height + 10, -10)   # y grows downwards like in the program
ax.set_aspect("equal")
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_title("Particle trajectories and collisions")
ax.legend(loc="upper left", bbox_to_anchor=(1.01, 1), fontsize=8)
ax.grid(alpha=0.3)

plt.savefig("trajectories.png", dpi=120, bbox_inches="tight")
print("saved trajectories.png")
plt.show()
