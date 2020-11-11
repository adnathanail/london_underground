# London underground journey planner
## Compile
```bash
gcc src/main.c src/data_proc.c src/data_proc.h src/data_structures.c src/data_structures.h src/user_interaction.c src/user_interaction.h src/utils.c src/utils.h src/xterm_codes.h data/data.c data/data.h
```

## Run
```bash
./a.out
```

## Use
1. You will be greeted by a prompt for the origin saying `Enter station ID or -1 to search stations:`
   - If you already know the ID of the station you want to start from, enter it
   - If you want to search for station ID's enter `-1`
     - Enter any string and you will receive a list of stations whose name contains that string (case-insensitive)
     - You can keep searching for stations until you enter `-1`
     - When you enter `-1` you will be taken back to the prompt asking for a station ID where you can enter any of the ID's of the stations you searched for
2. You will then see a second prompt asking for the ID of your destination station, where you can open the station search in the same manner (`-1`)
3. You will be shown your route with:
   - Journey time
   - Which zones you need tickets for
   - How many changes you will have to make

## Limitations
Finding a good dataset was difficult so:
- This route planner only takes into account the tube network
- It doesn't have data for long it takes to change line at stations so it can offer strange routes where you change line multiple times

## Planned improvements
- Display tube line colours with 256-bit xterm colours
- Include walking time at stations
- Include overground, DLR and the bus network

## References
**Choosing navigation algorithm**

https://en.wikipedia.org/wiki/Shortest_path_problem#Algorithms

**Implementing Dijkstra's shortest path**

https://brilliant.org/wiki/dijkstras-short-path-finder

**Tube network data**

https://github.com/nicola/tubemaps