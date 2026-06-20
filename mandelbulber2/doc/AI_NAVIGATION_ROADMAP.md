# 3x3lion — AI-Driven Fractal Navigation Roadmap

**Founded by Iri and Devin**

This document outlines the technical architecture for transforming 3x3lion from a manual fractal explorer into a fully AI-driven exploration platform with autonomous drone networks and bot-based testing.

---

## Current State (Phase 2d Complete)

### Manual Navigation Features
- WASD keyboard controls (W=forward, S=backward, A=left, D=right, Space=up, Q/E=roll)
- Quick view presets (Home, Top, Front, Right)
- Camera bookmarks with JSON persistence (save/recall/export/import)
- Collapsible sections, copy/paste coordinates
- Mouse drag rotation/movement in Navigator window

---

## Phase 3: Smart Navigation (Foundation for AI)

### 3.1 Adaptive Step Size (DE-Based Speed Control)
**What:** Camera movement speed automatically adjusts based on distance to fractal surface.
**How:** Use the Distance Estimation (DE) value at the camera position to scale step size:
```
step = base_step * clamp(DE(camera_pos) / reference_distance, min_factor, max_factor)
```
**Why AI needs this:** Bots can navigate at maximum safe speed without overshooting into the fractal.

### 3.2 Collision Avoidance
**What:** Prevent camera from penetrating the fractal surface.
**How:** Before applying any movement:
1. Calculate DE at proposed new position
2. If DE < safety_margin, clamp movement to stay at safety_margin distance
3. Use ray marching along movement vector to find safe stopping point
```
while (DE(pos + direction * step) < safety_margin && step > 0)
    step *= 0.5;
```
**Why AI needs this:** Autonomous exploration requires guaranteed safe navigation.

### 3.3 Surface Following Mode
**What:** Camera maintains constant distance from fractal surface, following contours like a drone over terrain.
**How:**
1. Project camera forward along current direction
2. Adjust altitude (perpendicular to surface) to maintain target distance
3. Use surface normal estimation via DE gradient:
```
normal = normalize(vec3(
    DE(pos + eps_x) - DE(pos - eps_x),
    DE(pos + eps_y) - DE(pos - eps_y),
    DE(pos + eps_z) - DE(pos - eps_z)
))
offset = normal * (target_distance - DE(pos))
new_pos = pos + forward * speed + offset * correction_factor
```
**Why AI needs this:** Drones need to "fly" over fractal landscapes autonomously.

### 3.4 Interest Point Detection
**What:** Automatically identify visually interesting regions of the fractal.
**How:** Score regions based on multiple metrics:

| Metric | Formula | What it detects |
|--------|---------|-----------------|
| DE Variance | σ²(DE samples in local area) | Complex geometry, thin features |
| Iteration Gradient | ∇(iteration_count) | Boundaries between convergence zones |
| Orbit Trap Diversity | entropy(trap_values) | Color-rich regions |
| Curvature | κ = ‖∇²DE‖ / ‖∇DE‖ | Sharp edges, spikes, folds |
| Lacunarity | gap analysis of DE field | Fractal complexity at current scale |

Combined score: `interest = w1*DE_var + w2*iter_grad + w3*trap_entropy + w4*curvature + w5*lacunarity`

**Why AI needs this:** This is the "reward function" for autonomous exploration — drones maximize interest scores.

---

## Phase 4: API-Driven Camera Control

### 4.1 Command API (Local Socket / REST)
**What:** External processes can control the camera programmatically.
**Interface:**
```json
// POST /api/camera/move
{
    "camera": [3.0, -6.0, 2.0],
    "target": [0.0, 0.0, 0.0],
    "rotation": [26.565, -16.602, 0.0],
    "distance": 7.0,
    "render": true,
    "resolution": [1920, 1080]
}

// GET /api/camera/state
// Returns current camera + last render stats

// POST /api/camera/bookmark
{
    "name": "interesting_spot_42",
    "metadata": { "interest_score": 0.87, "discovered_by": "drone-7" }
}

// GET /api/render/result
// Returns rendered image as PNG/EXR
```

**Implementation:** Qt local socket server in 3x3lion that accepts JSON commands. Can also be exposed as HTTP via a thin wrapper for remote bots.

### 4.2 Headless Rendering Mode
**What:** Render without GUI for bot/drone operation.
**How:** Already partially supported via CLI. Extend with:
- JSON config input (camera params + fractal params)
- Image output to stdout or file
- DE field sampling at arbitrary points (for navigation without rendering)
- Batch rendering queue

### 4.3 Parameter Space Navigation
**What:** Navigate not just in 3D space but also through fractal parameter space.
**How:** Expose fractal formula parameters (scale, offset, rotation angles, Julia seed) as navigable dimensions:
```
param_space_pos = [scale, offset_x, offset_y, offset_z, julia_cx, julia_cy, julia_cz, ...]
```
Bots can explore parameter space to discover new fractal morphologies.

---

## Phase 5: Autonomous Exploration Engine

### 5.1 Explorer Bot Architecture
```
┌─────────────────────────────────────────────┐
│                 Bot Manager                  │
│  ┌─────────┐  ┌──────────┐  ┌────────────┐ │
│  │ Drone 1 │  │ Drone 2  │  │  Drone N   │ │
│  │ (3D nav)│  │ (3D nav) │  │ (param nav)│ │
│  └────┬────┘  └────┬─────┘  └─────┬──────┘ │
│       │            │               │         │
│  ┌────▼────────────▼───────────────▼──────┐ │
│  │         Exploration Memory (DB)         │ │
│  │  - Visited positions + scores           │ │
│  │  - Discovered bookmarks                 │ │
│  │  - Interest heat maps                   │ │
│  │  - Parameter space coverage             │ │
│  └────────────────────────────────────────┘ │
│                                              │
│  ┌────────────────────────────────────────┐ │
│  │         3x3lion Render Farm             │ │
│  │  - Headless instances                   │ │
│  │  - GPU cluster for parallel renders     │ │
│  │  - DE field sampling service            │ │
│  └────────────────────────────────────────┘ │
└─────────────────────────────────────────────┘
```

### 5.2 Drone Navigation Algorithms

**A. Frontier-Based Exploration (like robotic SLAM)**
1. Maintain occupancy grid of explored vs unexplored space
2. Identify frontiers (boundaries between explored and unexplored)
3. Navigate to nearest high-interest frontier
4. Score: `priority = interest_estimate / distance_to_frontier`

**B. Entropy-Guided Exploration**
1. Maintain information-theoretic model of the fractal
2. Navigate toward regions of maximum expected information gain
3. Use Gaussian Process to predict interest scores in unexplored regions
4. Select next viewpoint that maximizes expected entropy reduction

**C. Evolutionary Camera Paths**
1. Generate population of random camera trajectories
2. Render low-res previews for each
3. Score by: visual complexity + novelty (distance from known bookmarks)
4. Crossover and mutate best trajectories
5. After N generations, save best frames as bookmarks

**D. Reinforcement Learning Navigation**
1. State: camera params + low-res render + DE field sample
2. Action: 6DOF movement + zoom
3. Reward: interest_score(new_view) - α * distance_traveled
4. Agent: PPO/SAC policy trained on previous exploration data
5. Progressive training: start with simple fractals, increase complexity

### 5.3 Exploration Memory Database
**Schema:**
```sql
CREATE TABLE bookmarks (
    id UUID PRIMARY KEY,
    camera_x DOUBLE, camera_y DOUBLE, camera_z DOUBLE,
    target_x DOUBLE, target_y DOUBLE, target_z DOUBLE,
    rotation_x DOUBLE, rotation_y DOUBLE, rotation_z DOUBLE,
    distance DOUBLE,
    fractal_type TEXT,
    fractal_params JSONB,
    interest_score DOUBLE,
    de_variance DOUBLE,
    curvature DOUBLE,
    iteration_gradient DOUBLE,
    thumbnail BYTEA,
    discovered_by TEXT,
    discovered_at TIMESTAMP,
    parent_bookmark UUID REFERENCES bookmarks(id),
    exploration_depth INT
);

CREATE TABLE exploration_sessions (
    id UUID PRIMARY KEY,
    drone_id TEXT,
    start_time TIMESTAMP,
    end_time TIMESTAMP,
    total_distance DOUBLE,
    bookmarks_found INT,
    avg_interest_score DOUBLE,
    coverage_percent DOUBLE
);

CREATE TABLE heat_map (
    x_grid INT, y_grid INT, z_grid INT,
    scale_level INT,
    visit_count INT,
    max_interest DOUBLE,
    last_visited TIMESTAMP
);
```

### 5.4 Bot Testing Network
**What:** Automated testing of 3x3lion features via bot network.
**How:**
1. Test bots navigate to known bookmarks and verify renders match expected output
2. Regression detection: compare renders across versions
3. Performance benchmarking: measure render times at standard viewpoints
4. Crash detection: navigate to extreme zoom levels, boundary conditions
5. Parameter sweep: test all 1600+ transformations systematically

---

## Phase 6: Distributed Drone Network

### 6.1 Network Architecture
```
                    ┌──────────────────┐
                    │  Central Server   │
                    │  (Coordinator)    │
                    └────────┬─────────┘
                             │
            ┌────────────────┼────────────────┐
            │                │                │
    ┌───────▼──────┐ ┌──────▼───────┐ ┌──────▼───────┐
    │   Node A      │ │   Node B      │ │   Node C      │
    │ 4× GPU        │ │ 8× GPU        │ │ 2× GPU        │
    │ 12 drones     │ │ 24 drones     │ │ 6 drones      │
    └──────┬───────┘ └──────┬────────┘ └──────┬────────┘
           │                │                  │
           └────────────────┼──────────────────┘
                            │
                    ┌───────▼────────┐
                    │  Shared Memory  │
                    │  (PostgreSQL +  │
                    │   Redis cache)  │
                    └────────────────┘
```

### 6.2 Drone Communication Protocol
- **Heartbeat:** Every drone reports status every 5 seconds
- **Claim:** Drone claims a region of space to explore (prevents duplicate work)
- **Report:** Drone reports discovered bookmarks with interest scores
- **Share:** High-interest discoveries broadcast to all drones for collaborative deep-dive
- **Balance:** Coordinator redistributes drones based on interest density

### 6.3 Scaling Strategy
1. **Phase 6a:** Single machine, multiple threads (current bookmarks system is the foundation)
2. **Phase 6b:** Single machine, multiple GPU-accelerated headless instances
3. **Phase 6c:** LAN cluster with central coordinator
4. **Phase 6d:** Cloud-based elastic scaling (spin up GPU instances on demand)

---

## Implementation Priority

| Phase | Feature | Complexity | Impact | Priority |
|-------|---------|-----------|--------|----------|
| 3.1 | Adaptive step size | Low | High | P0 |
| 3.2 | Collision avoidance | Low | High | P0 |
| 3.3 | Surface following | Medium | High | P1 |
| 3.4 | Interest point detection | Medium | Critical | P1 |
| 4.1 | Command API | Medium | Critical | P1 |
| 4.2 | Headless rendering | Low | Critical | P0 |
| 4.3 | Parameter space nav | Medium | High | P2 |
| 5.1 | Explorer bot arch | High | Critical | P2 |
| 5.2 | Navigation algorithms | High | High | P2 |
| 5.3 | Exploration memory | Medium | Critical | P1 |
| 5.4 | Bot testing network | Medium | High | P2 |
| 6.x | Distributed network | Very High | Game-changing | P3 |

---

## Key Technical Decisions

1. **JSON for all data exchange** — bookmarks, API, configs (already implemented)
2. **DE as primary navigation signal** — distance estimation is the compass for all autonomous navigation
3. **PostgreSQL for exploration memory** — scales from single machine to distributed cluster
4. **WebSocket for drone communication** — real-time, bidirectional, low overhead
5. **OpenCL for DE sampling** — GPU-accelerated distance field queries without full rendering
6. **Docker containers for drone instances** — easy scaling, isolation, reproducibility

---

*This document will be updated as we progress through each phase. The camera bookmarks system (JSON persistence + export/import) implemented in Phase 2d is the first building block of the exploration memory system.*
