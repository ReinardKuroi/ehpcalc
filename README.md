# Effective HP calculator

If a unit has health HP and armour AR, calculate effective EHP based on how much damage on average is required to destroy a unit.

### Examples

Guardsman(HP 4 AR 2) will at least have 6 EHP, because a single 6 DMG attack will kill it. It is immune to 2 DMG and less attacks, since they won't penetrate. At most it will have 12 EHP, because 4 3 DMG attacks are required to kill it. Iterating over all possible damage values, we can get an average EHP value. In some cases, EHP is higher than expected. This is due to a deliberate calculation - if a unit takes 5 DMG and stays alive, it will need 2 attacks of 5 DMG to be killed, therefore making its EHP vs 5 DMG equal to 10, not 6.

### What I needed

Best way was obviously to just pre-generate a table, insert it into our excel sheet with units as a reference, and pull EHP via select. But why spend 20 minutes on a taks, if you can spend 20 hours on a task, while making it more complex.

So here I am, writing a NN-esque thingy to fit a function and get my silly little coefficients for my silly little formula. Currently I have managed to fit a polynomial-N2 and an power function, both rather poorly.