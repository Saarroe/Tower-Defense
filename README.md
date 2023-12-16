# cpp_tower_defence

## Folders:

Each folder has its own Readme file with detailed descriptions. 

### doc/
Includes the project documentation pdf file. 

### plan/
Includes the project plan pdf file.

### src/
Includes all the c++ code files used for building the project. The source code is located in the subdirectory src/tower_defence along with a readme-file.

### tests/
Includes few test files that were used in the testing phase of the program.

## Getting started:

To run the code download the git folder and open the cmakelist.txt file using QT Creator.

For detailed descriptions check the doc/ folder and project documentation.

## Git instructions: 

Every time you start programming, **first run**:
```python
 git switch main
 git pull
```
If no changes have been made to main, the output will be "Already up to date". In that case, there is no need for rebasing. If there have been changes, run:

```python
git switch <your-branch>
git rebase origin/main <your-branch>
```
This is how you update your working branch after others have made changes to main.

After you push things into git from your branch, go to gitlab and push merge pull reguest ( or something like that)

