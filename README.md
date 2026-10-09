# IZLO — Grid Pathfinding via SAT

A problem-reduction exercise: encode an "escape the city grid" pathfinding
instance into a Boolean formula and let a SAT solver do the work.

- Variables `step·n² + from·n + to` track position over time
- The generator builds CNF in DIMACS format and solves it with minisat
- Sat / unsat fixture tests included

## Build & test

```bash
cd code && make && make test
```

Coursework for *Logika a grafové algoritmy (IZLO)* at FIT VUT Brno.
