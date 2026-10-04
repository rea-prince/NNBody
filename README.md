
## N-body

An n-body simulator based on Newtonian gravitation implemented in C using Raylib.

<p align="center">
	<img width="1875" height="1055" alt="image" src="https://github.com/user-attachments/assets/c63efa84-7eed-4739-bbf1-cd3180182dc3" />
</p>

Build and run:

```bash
cmake -G "Ninja" -S . -B build
cmake --build build
./build/n_body
```

> [!Note]
> Note that this uses a modified version of raylib (particularly for the camera).

<!--## TO DO

- [x] Improve grid visibility
- [x] Improve camera view
	- [x] Speed
	- [x] Sensitivity
	- [x] Movemenet
- [x] Add velocity and acceleration arrow
- [ ] Implement body GUI view
	- [X] List of bodies
	- [ ] Controls for each body
	- [ ] Selectable body-->
