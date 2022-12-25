# Effective HP calculator

If a unit has health HP and armour AR, calculate effective EHP based on how much damage on average is required to destroy a unit.

### Examples

Guardsman(HP 4 AR 2) will at least have 6 EHP, because a single 6 DMG attack will kill it. It is immune to 2 DMG and less attacks, since they won't penetrate. At most it will have 12 EHP, because 4 3 DMG attacks are required to kill it. Iterating over all possible damage values, we can get an average EHP value. In some cases, EHP is higher than expected. This is due to a deliberate calculation - if a unit takes 5 DMG and stays alive, it will need 2 attacks of 5 DMG to be killed, therefore making its EHP vs 5 DMG equal to 10, not 6.

### What I needed

Best way was obviously to just pre-generate a table, insert it into our excel sheet with units as a reference, and pull EHP via select. But why spend 20 minutes on a taks, if you can spend 20 hours on a task, while making it more complex.

So here I am, writing a NN-esque thingy to fit a function and get my silly little coefficients for my silly little formula. Currently I have managed to fit a polynomial-N2 and an power function, both rather poorly.

### Current performance

### HP 50 AR 20

##### Polynomial

```
Enter HP range to test: 50
Enter AR range to test: 20
Generating a list of possible stat points...done
Fitting a function using generated point list...done
Calculating MSE for training data...done
Calculating MSE for testing data...done
For the given range of possible HP and AR combinations:
POLYNOMIAL
f(x,y) = -0.01x^2 + 1.85x + 0.06y^2 + 1.00y + 0.07xy + 0.59

        Coefficients: -0.01 1.85 0.06 1.00 0.07 0.59
        MSE on training data: 7.04215
        MSE on testing data: 6.73031

Some arbitrary examples:

Guardsman Stats:
        HP: 4.0
        AR: 2.0
        EHP: 9.0
        EHP(predicted): 10.6

Hammerhead Stats:
        HP: 30.0
        AR: 6.0
        EHP: 65.1
        EHP(predicted): 65.6

Triarch Praetorian Stats:
        HP: 10.0
        AR: 5.0
        EHP: 28.9
        EHP(predicted): 27.9
```

##### Exponential

```
Enter HP range to test: 50
Enter AR range to test: 20
Generating a list of possible stat points...done
Fitting a function using generated point list...done
Calculating MSE for training data...done
Calculating MSE for testing data...done
For the given range of possible HP and AR combinations:
EXPONENTIAL
f(x, y) = 0.98(x + 0.54)^1.14 + 0.96(y + 0.51)^1.45

        Coefficients: 0.98 0.54 1.14 0.96 0.51 1.45
        MSE on training data: 30.66326
        MSE on testing data: 37.55096

Some arbitrary examples:

Guardsman Stats:
        HP: 4.0
        AR: 2.0
        EHP: 9.0
        EHP(predicted): 9.2

Hammerhead Stats:
        HP: 30.0
        AR: 6.0
        EHP: 65.1
        EHP(predicted): 63.5

Triarch Praetorian Stats:
        HP: 10.0
        AR: 5.0
        EHP: 28.9
        EHP(predicted): 25.9
```

#### HP 100 AR 30

##### Polynomial

```
Enter HP range to test: 100
Enter AR range to test: 30
Generating a list of possible stat points...done
Fitting a function using generated point list...done
Calculating MSE for training data...done
Calculating MSE for testing data...done
MSE exceeding at   inf
Aborting...
```

##### Exponential 

```
Enter HP range to test: 100
Enter AR range to test: 30
Generating a list of possible stat points...done
Fitting a function using generated point list...done
Calculating MSE for training data...done
Calculating MSE for testing data...done
For the given range of possible HP and AR combinations:
EXPONENTIAL
f(x, y) = 1.29(x + 0.48)^1.05 + 1.18(y + 0.50)^1.38

        Coefficients: 1.29 0.48 1.05 1.18 0.50 1.38
        MSE on training data: 76.37742
        MSE on testing data: 84.41685

Some arbitrary examples:

Guardsman Stats:
        HP: 4.0
        AR: 2.0
        EHP: 9.0
        EHP(predicted): 10.4

Hammerhead Stats:
        HP: 30.0
        AR: 6.0
        EHP: 65.1
        EHP(predicted): 62.8

Triarch Praetorian Stats:
        HP: 10.0
        AR: 5.0
        EHP: 28.9
        EHP(predicted): 27.7
```