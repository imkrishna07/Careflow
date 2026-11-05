<h1 align="centre">CareFlow - Hospital Patient Management System </h1>

A full-stack emergency queue mini-project demonstrating a custom C++17 Binary Max Heap with a responsive React dashboard.

## Architecture

- **Backend:** C++17, custom `MaxHeap` over `std::vector<Patient>`, hand-written lightweight HTTP/JSON API, persistent SQLite database.
- **Frontend:** React, Vite, Tailwind CSS, Lucide React and Recharts.
- **Scheduling:** Severity descending; arrival timestamp ascending; patient ID ascending as deterministic tie-breaker.
- Heap index map is maintained on every swap. Queue snapshots are extracted from a copy of the heap so the live scheduler remains intact.

## Run locally (macOS Apple Silicon)

Requirements: Xcode Command Line Tools (clang++ and SQLite), Node.js 20+ and npm.

```sh
cd backend
clang++ -std=c++17 -O2 -Iinclude src/main.cpp src/MaxHeap.cpp src/Database.cpp -lsqlite3 -o hospital-api
./hospital-api
```

In another terminal:

```sh
cd frontend
npm install
npm run dev
```

Open http://localhost:5173. The API listens on port 8080 and creates `hospital.db` in its current working directory. Stop and restart the API to verify waiting patient recovery. Keep the backend running while using the site.

## Demo records

Example intake records are provided in `backend/sample-patients.json`. Register them through the website or send each object as JSON to `POST /api/patients`; the API assigns IDs and arrival timestamps.

## REST API

| Method | Endpoint | Purpose |
|---|---|---|
| GET | `/api/dashboard` | Live counts, queue and waiting time summary |
| GET | `/api/patients/queue` | Priority-ordered waiting snapshot |
| GET | `/api/patients/:id` | Patient lookup by ID |
| POST | `/api/patients` | Register / heap insert |
| DELETE | `/api/patients/:id` | Remove waiting patient |
| PUT | `/api/patients/:id/severity` | Update waiting severity |
| POST | `/api/patients/treat-next` | Extract heap maximum and record treatment |
| GET | `/api/patients/history` | Treated patient history |

## DSA operations and complexity

| Operation | Complexity |
|---|---|
| Insert | O(log n) |
| Peek / next patient | O(1) |
| Extract maximum / treat | O(log n) |
| Search by ID | O(1) using the index map (name search can scan in O(n)) |
| Remove by ID | O(log n) after lookup |
| Severity update | O(log n) after lookup |
| Build heap | O(n) |
| Space | O(n) |

The product ordering is lexicographic: higher severity wins, then lower arrival epoch, then lexicographically smaller ID. A normal FIFO queue cannot promote a high-severity case that arrived later.

## Tests

The heap and SQLite persistence tests cover priority ordering, tie-breaks, extraction, updates, deletion, index consistency and reload after database reopen. Run both with CMake/CTest:

```sh
cd backend
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Or compile both test programs directly:

```sh
cd backend
clang++ -std=c++17 -Iinclude tests/heap_tests.cpp src/MaxHeap.cpp -o heap-tests
./heap-tests
clang++ -std=c++17 -Iinclude tests/database_tests.cpp src/Database.cpp -lsqlite3 -o database-tests
./database-tests
```

Tests cover priority/tie ordering, extraction, severity update in either direction, arbitrary deletion, searching and index-map invariants over repeated operations.

## Notes

The API uses a small POSIX socket server and SQLite, both available with the standard macOS developer toolchain. It binds to loopback for local-only access; set `HOSPITAL_PORT` to change port 8080. It is intended for a local educational demo, not deployment as a clinical system. Treatment timestamps, original severity and measured wait durations are captured in the persisted history.
