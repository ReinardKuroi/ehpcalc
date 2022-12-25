I have this basic function that calculates EHP of a unit with given stats. I really want to fit a function that will give me a consistent result without having to iterate over every damage value.

I have tried fitting it to a plane a*x + b*y + c = z, where x - health, y - armour, z - effective hp. This did not work. I was considering other function types, most likely either quadratic or exp.

This task looks somewhat akin to the creation of a neural network. The only difference is, I need coefficients, because I want to use a formula myself in a different application.

I will try to implement multiple nonlinear regression, being the dumbass that I am, from scratch, because why not.

For a starting point, let's think for a bit. EHP depends on HP and AR, the higher HP - the higher EHP, the higher AR - the higher EHP. Doubling HP roughly doubles EHP. It also seems that higher values of HP affect the result a bit less, so it's probably also in some way of stuff*HP^a where a is less than 1.

EHP also depends on AR, but doubling AR is very effective - higher AR means higher multiplier in comparison to lower AR. E.g. if HP = 20, AR 2 -> 4 = +24%, AR 4 -> 8 = +39%, AR 8 -> 16 = +56%, e.c.t. This might imply that AR is in some form of AR^b, where b > 1.

I have tried w1*x^2 + w2*x + w3*y^2 + w4*y + w5*x*y + w6 = z, it kinda works. On large datasets though, MSE quickly rushes to inf.

When I try higher ranges, coefficients of x^2 and y^2 are approaching zero. I feel like polynomial might not be the correct approach here.