# Reverse Engineering Activity

To complete this segment, you need to analyze the program to find the name of the statue guard. For this activity, we will use the Ghidra reverse engineering framework developed by the National Security Agency. In the club meeting we provided a VM image containing Ghidra and the programs in this repository, but these instructions should be applicable to other environments as well.

## Setup

1. Launch the VM in VirtualBox and log in as the VM User with the password `hashdump`.
2. Begin by opening a terminal and `cd` to the `ghidra_11.4.2_PUBLIC` directory.
3. Launch Ghidra by invoking the `./ghidraRun` script.
4. Create a new Ghidra project (File -> New Project). Select "Non-Shared Project", create a directory called "ghidraProject", and save the project within this directory after giving it a name.
5. Click File -> Import File, and select the `cave` binary under the `/home/vmuser/hashdump` directory. Click OK.
6. Right-click on `cave` in the project view, and click "Open in Default Tool".
7. When prompted to analyze the `cave` file, click Yes. Leave the settings at the default and click Analyze.

The Symbol Tree in the left pane allows you to see a list of functions and other symbols contained within the program. Expand the Functions list and click on "main" to jump to the main function. The middle panel will show a disassembly of the code for the "main" function, and the rightmost panel shows a C decompilation. (If the C code isn't displayed, you can click on the assembly code for `main` in the center panel to show it.)

Notice that "main" calls three functions in order: `password`, `maze`, and `door`. Each of these represents a given stage of the game.

## Part 1: Password

If you run the game by opening a terminal to `/home/vmuser/hashdump` and running `./cave`, you will quickly be stopped by a puzzle. Part 1 requires you to analyze the `password` function to identify the guard character's name. You can jump to this function from the symbol tree in the same manner as `main`.

Here are a few tips to aid in solving this stage:

- The `read_stdin` function simply reads user input and stores it in a given variable.
- The `strncmp` function returns `0` if two strings are equal, or a negative or positive integer if they differ.
- You can rename variables in the decompiled C code by right-clicking them and selecting "Rename Variable." This may assist you in tracking what variables serve what purpose.

After identifying the character's name, try running the program again and entering the name.

## Part 2: Maze

Part 2 is similar in concept to part 1, but more complex since you will need to identify a route through a maze.

- You will need to look at two functions, `maze` and `char_to_direction`.
- The return value of `read_stdin` indicates the length of the user input.
- Once again, it may be helpful to edit variable names to keep track of what is what.

## Part 3: Door

The `door` stage initially appears impossible since the player immediately loses. Probing into the decompiled function also may not lend insight at first glance since there is seemingly no win condition.

However, in its default configuration Ghidra displays a warning at the top of the decompiled C code stating that it eliminated an unreachable block. This is your first clue as to what is going on. To display this unreachable code in the decompilation, go to Edit -> Tool Options, expand the Decompiler folder, and click on Analysis. From there uncheck "Eliminate unreachable code" and click OK.

You will now notice an if statement where the condition is always false. To satisfy the win condition, you must modify the assembly code to make this condition true.

The relevant lines here are a `MOV` instruction that initializes a variable to `0x1`, and a later `CMP` that checks if it is equal to `0x0`. If the comparison succeeds, then the subsequent `JZ` jump instruction activates.
To modify an assembly instruction, select it in the editor, right-click, and click "Patch instruction". From there you can change the code to do what you want.

After modifying the assembly code, you can export the edited binary from Ghidra. Click File -> Export Program..., select the "Original File" format, and save it as `cave_patched`. Try running this program and see if you can beat the game.
