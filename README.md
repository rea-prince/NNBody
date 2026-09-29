
## N-body

Build and run:

```bash
cmake -G "Ninja" -S . -B build
cmake --build build
./build/n_body
```

> [!Note]
> Note that this uses a modified version of raylib (particularly for the camera).

## TO DO

- [x] Improve grid visibility
- [X] Improve camera view
	- [x] Speed
	- [X] Sensitivity
	- [x] Movemenet
- [ ] Add velocity and acceleration arrow
- [ ] Implement body GUI view
	- [ ] List of bodies
	- [ ] Controls for each body
	- [ ] Selectable body
